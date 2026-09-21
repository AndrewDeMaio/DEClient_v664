using System;
using System.Collections.Generic;
using System.IO;

namespace DarkEden.Updater
{
    // Brings the files INSIDE darkeden.dpk into line with the server's entry list,
    // one file at a time, instead of downloading the whole archive for any change.
    //
    // The server publishes (manifest.txt):
    //   base    the archive pair as first published - fetched only when the local
    //           pair is missing or unusable
    //   entries archive/entries.txt - every file the archive should hold, with its
    //           sha256; P rows are hosted singly at files/archive/<vpath>, B rows only
    //           exist inside the base archive
    //
    // The updater keeps a record of what its own archive holds (Archive.state). Each
    // run, in this order:
    //   1. the game must not be running (it holds the archive open)
    //   2. an update that stopped half way is undone: the index is put back
    //   3. the index is checked before anything else: a pair that is not an archive
    //      is replaced whole and never written to
    //   4. the server's list is fetched
    //   5. the record is loaded - or rebuilt by reading every entry (~20 s), when it
    //      is missing, the pair changed behind the updater's back, or on /repair
    //   6. only if the lists differ is the archive touched: the changed files are
    //      downloaded, then written in batches, each batch with the index backed up
    //      first, a journal while it runs, and every file read back and checked after
    //
    // Writing reuses the space of the entry it replaces (dpkput add), so patching
    // does not grow the archive beyond the size of what is really new.
    //
    // If a write is killed part way, putting the index back leaves every other entry
    // intact (tested: 76 of 76 after a kill mid-payload) - but the entries that were
    // being written may be damaged, because the new copy reused their space. Those
    // are remembered as suspects (Archive.suspect): never trusted, rewritten first.
    sealed class ArchivePatcher
    {
        const string StateName = "Archive.state";
        const string SuspectName = "Archive.suspect";
        const string JournalName = "Archive.journal";
        const string ListName = "entries.txt";
        const string IndexBackupName = "darkeden.dpi.bak";
        const string StageDir = "stage";
        const int WriteBatch = 100;
        const long MaxDpk = 2147483647L;    // the client seeks the .dpk with an int

        readonly UpdateEngine m_engine;
        readonly Manifest m_manifest;
        readonly HashCache m_cache;
        readonly bool m_repair;
        DpkTools m_tools;

        public ArchivePatcher(UpdateEngine engine, Manifest manifest, HashCache cache, bool repair)
        {
            m_engine = engine;
            m_manifest = manifest;
            m_cache = cache;
            m_repair = repair;
        }

        string Book(string name)
        {
            return BookFiles.PathOf(m_engine.GameDir, name);
        }

        public void Run()
        {
            m_engine.Status = "Checking the game archive...";
            m_engine.Detail = "";
            m_tools = new DpkTools(m_engine.GameDir);

            // 1
            if (m_tools.IsGameRunning())
                throw new IOException("The game is running. Close it and run the updater again.");

            // 2
            RecoverJournal();

            // 3
            string why = m_tools.CheckPair();
            if (why != null)
            {
                m_engine.Log("Archive: " + why + " - fetching the full archive.");
                DownloadBase(true);
            }

            // 4
            EntryList current = FetchCurrentList();

            // 5
            EntryList record = LoadRecord();
            if (record == null)
                record = BuildRecord(current.Rows.Count);

            // 6
            List<EntryRow> wanted;
            List<string> removed;
            Diff(current, record, out wanted, out removed);

            if (wanted.Exists(delegate(EntryRow r) { return !r.Hosted; }))
            {
                // the archive differs from the base in files the server has no single copy of
                int n = wanted.FindAll(delegate(EntryRow r) { return !r.Hosted; }).Count;
                m_engine.Log("Archive: " + n + " files differ from the base archive and are not hosted singly - fetching the full archive.");
                DownloadBase(false);
                record = BuildRecord(current.Rows.Count);
                Diff(current, record, out wanted, out removed);
                if (wanted.Exists(delegate(EntryRow r) { return !r.Hosted; }))
                    throw new InvalidDataException("The server's base archive does not match its own file list. Tell the server admin.");
            }

            if (wanted.Count == 0 && removed.Count == 0)
            {
                SaveRecord(record);
                m_engine.Log("Archive up to date (" + record.Rows.Count + " files).");
                return;
            }

            long bytes = 0;
            foreach (EntryRow row in wanted)
                bytes += row.Size;
            m_engine.Log("Archive: " + wanted.Count + " files to patch (" + UpdateEngine.FormatBytes(bytes) + "), " + removed.Count + " to remove.");

            Preflight(wanted, bytes);
            Stage(wanted, bytes);
            Write(wanted, record);
            Remove(removed, record);

            // the whole-file hashes of the pair no longer mean anything
            m_cache.Forget(Manifest.DpkPath);
            m_cache.Forget(Manifest.DpiPath);
            TryDeleteDir(Book(StageDir));

            m_engine.Log("Archive: patched " + wanted.Count + " files, removed " + removed.Count + ".");
        }

        // ---- 2. an interrupted write

        void RecoverJournal()
        {
            string journal = Book(JournalName);
            if (!File.Exists(journal))
                return;

            string[] lines = File.ReadAllLines(journal);
            string backup = Book(IndexBackupName);
            if (IsIndex(backup))
            {
                File.Copy(backup, m_tools.DpiFile, true);
                m_engine.Log("Archive: the last update stopped while writing; the index was put back.");
            }
            else
                m_engine.Log("Archive: the last update stopped while writing and left no usable index backup.");

            // files being written may be damaged; files being removed are not (a
            // removal only touches the index, which is back as it was)
            if (lines.Length > 0 && lines[0] == "adding")
            {
                List<string> suspects = new List<string>(lines);
                suspects.RemoveAt(0);
                AddSuspects(suspects);
            }

            // what the archive holds now is not known: read it again
            TryDelete(Book(StateName));
            TryDelete(backup);
            TryDelete(journal);
        }

        // ---- suspects: entries a killed write may have damaged

        HashSet<string> LoadSuspects()
        {
            HashSet<string> set = new HashSet<string>(StringComparer.Ordinal);
            string path = Book(SuspectName);
            if (File.Exists(path))
            {
                foreach (string line in File.ReadAllLines(path))
                {
                    if (EntryList.IsValidVPath(line.Trim()))
                        set.Add(line.Trim());
                }
            }
            return set;
        }

        void SaveSuspects(HashSet<string> set)
        {
            string path = Book(SuspectName);
            if (set.Count == 0)
                TryDelete(path);
            else
            {
                List<string> lines = new List<string>(set);
                lines.Sort(StringComparer.Ordinal);
                File.WriteAllLines(path, lines.ToArray());
            }
        }

        void AddSuspects(IEnumerable<string> vpaths)
        {
            HashSet<string> set = LoadSuspects();
            set.UnionWith(vpaths);
            SaveSuspects(set);
        }

        void ClearSuspects(IEnumerable<string> vpaths)
        {
            HashSet<string> set = LoadSuspects();
            int before = set.Count;
            set.ExceptWith(vpaths);
            if (set.Count != before)
                SaveSuspects(set);
        }

        static bool IsIndex(string path)
        {
            try
            {
                if (!File.Exists(path) || new FileInfo(path).Length < 8)
                    return false;
                byte[] magic = new byte[4];
                using (FileStream f = File.OpenRead(path))
                    f.Read(magic, 0, 4);
                return magic[0] == 'A' && magic[1] == 'B' && magic[2] == 'C' && magic[3] == 'D';
            }
            catch (IOException) { return false; }
        }

        // ---- 3. the whole archive, when it has to come fresh

        void DownloadBase(bool broken)
        {
            // an unusable pair is only in the way; a usable one stays until its
            // replacement is complete
            if (broken)
            {
                TryDelete(m_tools.DpkFile);
                TryDelete(m_tools.DpiFile);
            }
            TryDelete(Path.Combine(m_tools.DataDir, "darkeden.dpl"));
            TryDelete(Book(StateName));
            TryDelete(Book(SuspectName));   // a fresh archive has no damaged entries

            foreach (ManifestEntry entry in new[] { m_manifest.BaseDpi, m_manifest.BaseDpk })
            {
                m_engine.Status = "Downloading the game archive (" + Path.GetFileName(entry.Path) + ")";
                m_engine.Download(entry, delegate(long done)
                {
                    m_engine.FileFraction = m_engine.TotalFraction = UpdateEngine.Fraction(done, entry.Size);
                    m_engine.Detail = UpdateEngine.FormatBytes(done) + " of " + UpdateEngine.FormatBytes(entry.Size);
                });
            }
            // both are verified; only now replace the old pair, index last
            m_engine.Install(m_manifest.BaseDpk, m_cache);
            m_engine.Install(m_manifest.BaseDpi, m_cache);
            m_engine.Log("Archive: fetched the full archive.");

            string why = m_tools.CheckPair();
            if (why != null)
                throw new InvalidDataException("The downloaded archive is not usable: " + why + ".");
        }

        // ---- 4. the server's list

        EntryList FetchCurrentList()
        {
            string local = Book(ListName);
            ManifestEntry list = m_manifest.Entries;

            if (!File.Exists(local) || new FileInfo(local).Length != list.Size || HashCache.HashFile(local, null) != list.Hash)
            {
                m_engine.Status = "Downloading the archive's file list...";
                m_engine.Download("files/" + list.Path, local + ".part", list.Hash, list.Size, list.Path, null);
                TryDelete(local);
                File.Move(local + ".part", local);
            }

            EntryList current = EntryList.Load(local);
            if (current.Rows.Count == 0)
                throw new InvalidDataException("The server's archive file list is empty.");
            return current;
        }

        // ---- 5. what the archive holds

        string PairSignature()
        {
            FileInfo dpk = new FileInfo(m_tools.DpkFile), dpi = new FileInfo(m_tools.DpiFile);
            return dpk.Length + " " + dpk.LastWriteTimeUtc.Ticks + " " + dpi.Length + " " + dpi.LastWriteTimeUtc.Ticks;
        }

        EntryList LoadRecord()
        {
            string path = Book(StateName);
            if (m_repair || !File.Exists(path))
                return null;

            try
            {
                EntryList record = EntryList.Load(path);
                if (record.Pair != PairSignature())
                {
                    m_engine.Log("Archive: the archive changed since the last check; reading it again.");
                    return null;
                }
                // a suspect is never believed: leaving it out of the record gets it rewritten
                foreach (string suspect in LoadSuspects())
                    record.Rows.Remove(suspect);
                return record;
            }
            catch (InvalidDataException e)
            {
                m_engine.Log("Archive: the record is damaged (" + e.Message + "); reading the archive again.");
                return null;
            }
        }

        EntryList BuildRecord(int expected)
        {
            m_engine.Status = "Checking every file in the game archive (one time)...";
            Dictionary<string, EntryRow> rows;
            List<string> damaged = new List<string>();
            Action<int> progress = delegate(int n)
            {
                if ((n & 255) == 0)
                {
                    m_engine.Detail = n + " / " + expected;
                    m_engine.FileFraction = m_engine.TotalFraction = UpdateEngine.Fraction(n, expected);
                }
            };

            try
            {
                rows = m_tools.Hash(null, null, damaged, progress);
            }
            catch (InvalidDataException e)
            {
                // not one bad entry but an archive that cannot be read: only a fresh one helps
                m_engine.Log("Archive: " + e.Message + " - fetching the full archive.");
                DownloadBase(true);
                damaged.Clear();
                rows = m_tools.Hash(null, null, damaged, progress);
            }

            // unreadable entries stay out of the record, so they are rewritten
            if (damaged.Count > 0)
                m_engine.Log("Archive: " + damaged.Count + " files could not be read (" + damaged[0] + (damaged.Count > 1 ? ", ..." : "") + "); they will be rewritten.");

            EntryList record = new EntryList();
            HashSet<string> suspects = LoadSuspects();
            foreach (EntryRow row in rows.Values)
            {
                if (!suspects.Contains(row.VPath))
                    record.Rows[row.VPath] = row;
            }
            SaveRecord(record);
            m_engine.Log("Archive: checked " + rows.Count + " files.");
            return record;
        }

        void SaveRecord(EntryList record)
        {
            record.Pair = PairSignature();
            record.Save(Book(StateName));
        }

        static void Diff(EntryList current, EntryList record, out List<EntryRow> wanted, out List<string> removed)
        {
            wanted = new List<EntryRow>();
            removed = new List<string>();

            foreach (EntryRow row in current.Rows.Values)
            {
                EntryRow have;
                if (!record.Rows.TryGetValue(row.VPath, out have) || have.Hash != row.Hash || have.Size != row.Size)
                    wanted.Add(row);
            }
            foreach (string vpath in record.Rows.Keys)
            {
                if (!current.Rows.ContainsKey(vpath))
                    removed.Add(vpath);
            }
            wanted.Sort(delegate(EntryRow a, EntryRow b) { return string.CompareOrdinal(a.VPath, b.VPath); });
            removed.Sort(StringComparer.Ordinal);
        }

        // ---- 6. patching

        void Preflight(List<EntryRow> wanted, long bytes)
        {
            long dpk = new FileInfo(m_tools.DpkFile).Length;
            long dpi = new FileInfo(m_tools.DpiFile).Length;

            // generous: each entry may need a block of overhead, plus a margin
            if (dpk + bytes + wanted.Count * 1024L + (16L << 20) > MaxDpk)
                throw new InvalidDataException("The game archive would pass its 2 GB limit. A rebuilt archive is needed - tell the server admin.");

            string root = Path.GetPathRoot(Path.GetFullPath(m_tools.DataDir));
            long free = new DriveInfo(root).AvailableFreeSpace;
            long need = bytes * 2 + dpi + (64L << 20);
            if (free < need)
                throw new IOException("Not enough disk space to patch the game archive: " + UpdateEngine.FormatBytes(need) + " needed, " + UpdateEngine.FormatBytes(free) + " free.");
        }

        string StagePath(string vpath)
        {
            return Path.Combine(Book(StageDir), vpath.Replace('/', Path.DirectorySeparatorChar));
        }

        void Stage(List<EntryRow> wanted, long bytes)
        {
            long done = 0;
            for (int i = 0; i < wanted.Count; i++)
            {
                EntryRow row = wanted[i];
                string target = StagePath(row.VPath);
                m_engine.Status = "Downloading " + row.VPath;
                m_engine.Detail = (i + 1) + " / " + wanted.Count + "   " + UpdateEngine.FormatBytes(done) + " of " + UpdateEngine.FormatBytes(bytes);

                // kept from a run that stopped after downloading
                bool have = File.Exists(target) && new FileInfo(target).Length == row.Size && HashCache.HashFile(target, null) == row.Hash;
                if (!have)
                {
                    Directory.CreateDirectory(Path.GetDirectoryName(target));
                    long before = done;
                    m_engine.Download("files/archive/" + row.VPath, target + ".part", row.Hash, row.Size, row.VPath, delegate(long fileDone)
                    {
                        m_engine.FileFraction = UpdateEngine.Fraction(fileDone, row.Size);
                        m_engine.TotalFraction = UpdateEngine.Fraction(before + fileDone, bytes);
                    });
                    TryDelete(target);
                    File.Move(target + ".part", target);
                }
                done += row.Size;
            }
        }

        void Write(List<EntryRow> wanted, EntryList record)
        {
            for (int start = 0; start < wanted.Count; start += WriteBatch)
            {
                List<EntryRow> batch = wanted.GetRange(start, Math.Min(WriteBatch, wanted.Count - start));
                m_engine.Status = "Patching the game archive...";
                m_engine.Detail = Math.Min(wanted.Count, start + batch.Count) + " / " + wanted.Count;
                m_engine.TotalFraction = UpdateEngine.Fraction(start, wanted.Count);

                List<string> vpaths = new List<string>();
                List<KeyValuePair<string, string>> pairs = new List<KeyValuePair<string, string>>();
                foreach (EntryRow row in batch)
                {
                    vpaths.Add(row.VPath);
                    pairs.Add(new KeyValuePair<string, string>(StagePath(row.VPath), row.VPath));
                }

                BeginWrite("adding", vpaths);

                List<string> failures = m_tools.Add(pairs);
                if (failures.Count > 0)
                {
                    UndoWrite(vpaths);
                    throw new IOException("Could not write " + failures.Count + " files into the game archive (first: " + failures[0] + "). The archive was put back; the next run tries again.");
                }

                // read every one back: the archive must now hold exactly what the list says
                Dictionary<string, EntryRow> got = m_tools.Hash(vpaths, null, null, null);
                foreach (EntryRow row in batch)
                {
                    EntryRow check;
                    if (!got.TryGetValue(row.VPath, out check) || check.Hash != row.Hash || check.Size != row.Size)
                    {
                        UndoWrite(vpaths);
                        throw new InvalidDataException("A patched file did not read back correctly (" + row.VPath + "). The archive was put back; the next run tries again.");
                    }
                }

                foreach (EntryRow row in batch)
                {
                    record.Rows[row.VPath] = new EntryRow { Hash = row.Hash, Size = row.Size, VPath = row.VPath };
                    TryDelete(StagePath(row.VPath));
                }
                SaveRecord(record);
                EndWrite();
                ClearSuspects(vpaths);
                m_engine.Log("Archive: wrote " + batch.Count + " files" + (batch.Count == 1 ? " (" + batch[0].VPath + ")" : "") + ".");
            }
        }

        void Remove(List<string> removed, EntryList record)
        {
            if (removed.Count == 0)
                return;

            m_engine.Status = "Removing old files from the game archive...";
            BeginWrite("removing", removed);

            // a removal only touches the index: putting the index back undoes it whole
            if (!m_tools.Delete(removed))
            {
                UndoWrite(null);
                throw new IOException("Could not remove files from the game archive. Nothing was changed.");
            }

            Dictionary<string, EntryRow> still = m_tools.Hash(removed, null, null, null);
            if (still.Count > 0)
            {
                UndoWrite(null);
                throw new InvalidDataException("Files that were removed from the game archive are still in it. Nothing was changed.");
            }

            foreach (string vpath in removed)
            {
                record.Rows.Remove(vpath);
                m_engine.Log("Archive: removed " + vpath);
            }
            SaveRecord(record);
            EndWrite();
        }

        // Before every write: the index as it was, and a journal naming the write.
        // The payload is never copied (1.8 GB): a replaced entry's blocks are reused
        // only by that same write, so the old index plus a re-read of the archive
        // (the record is dropped) is enough to recover.
        void BeginWrite(string what, List<string> vpaths)
        {
            if (m_tools.IsGameRunning())
                throw new IOException("The game is running. Close it and run the updater again.");

            File.Copy(m_tools.DpiFile, Book(IndexBackupName), true);
            List<string> lines = new List<string> { what };
            lines.AddRange(vpaths);
            File.WriteAllLines(Book(JournalName), lines.ToArray());
        }

        void EndWrite()
        {
            TryDelete(Book(JournalName));
            TryDelete(Book(IndexBackupName));
        }

        // written: the entries that were being written (they may be damaged now), or
        // null for a removal
        void UndoWrite(List<string> written)
        {
            string backup = Book(IndexBackupName);
            if (IsIndex(backup))
                File.Copy(backup, m_tools.DpiFile, true);
            if (written != null)
                AddSuspects(written);
            TryDelete(Book(StateName));     // read the archive again next time
            EndWrite();
            m_engine.Log("Archive: the write failed; the index was put back.");
        }

        // ---- small things

        static void TryDelete(string path)
        {
            try
            {
                if (File.Exists(path))
                {
                    File.SetAttributes(path, FileAttributes.Normal);
                    File.Delete(path);
                }
            }
            catch (IOException) { }
            catch (UnauthorizedAccessException) { }
        }

        static void TryDeleteDir(string path)
        {
            try
            {
                if (Directory.Exists(path))
                    Directory.Delete(path, true);
            }
            catch (IOException) { }
            catch (UnauthorizedAccessException) { }
        }
    }
}
