using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Threading;

namespace DarkEden.Updater
{
    // The archive is written and read by dpkput.exe / dpkget.exe (Tools\Packing),
    // built from the client's own VirtualFileSystem code, so what they write is
    // exactly what the game reads. They travel inside Updater.exe as resources and
    // are unpacked into Data\Updater\tools\ - an updater and its tools always match.
    // They run as separate processes: if one ever dies on a damaged archive, the
    // updater does not die with it.
    sealed class DpkTools
    {
        const string Base = "darkeden";     // Data\darkeden.dpk / .dpi, as the client opens it
        const int BatchSize = 120;          // names per command line, well under the 32K limit
                                            // (dpkget --list prints names with leading spaces; a
                                            // name itself never starts with one)

        readonly string m_dataDir;
        readonly string m_put;
        readonly string m_get;

        public DpkTools(string gameDir)
        {
            m_dataDir = Path.Combine(gameDir, "Data");
            string dir = Path.Combine(m_dataDir, "Updater", "tools");
            Directory.CreateDirectory(dir);
            m_put = Unpack("Tools.dpkput.exe", Path.Combine(dir, "dpkput.exe"));
            m_get = Unpack("Tools.dpkget.exe", Path.Combine(dir, "dpkget.exe"));
        }

        public string DataDir { get { return m_dataDir; } }
        public string DpkFile { get { return Path.Combine(m_dataDir, Base + ".dpk"); } }
        public string DpiFile { get { return Path.Combine(m_dataDir, Base + ".dpi"); } }

        static string Unpack(string resource, string target)
        {
            byte[] bytes;
            using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(resource))
            {
                if (stream == null)
                    throw new InvalidOperationException("This Updater.exe was built without " + resource + ".");
                bytes = new byte[stream.Length];
                int read = 0;
                while (read < bytes.Length)
                    read += stream.Read(bytes, read, bytes.Length - read);
            }

            bool same = false;
            if (File.Exists(target) && new FileInfo(target).Length == bytes.Length)
            {
                byte[] have = File.ReadAllBytes(target);
                same = true;
                for (int i = 0; i < have.Length && same; i++)
                    same = have[i] == bytes[i];
            }
            if (!same)
            {
                if (File.Exists(target))
                    File.SetAttributes(target, FileAttributes.Normal);
                File.WriteAllBytes(target, bytes);
            }
            return target;
        }

        // ---- checks that come before anything is written

        // null when the pair looks like an archive, otherwise why not. Never let the
        // tools open a pair that fails this: with the .dpi missing, opening for write
        // recreates the archive and empties the .dpk (dpkput refuses as well).
        public string CheckPair()
        {
            FileInfo dpk = new FileInfo(DpkFile), dpi = new FileInfo(DpiFile);
            if (!dpk.Exists && !dpi.Exists) return "the archive is not there";
            if (!dpk.Exists) return "darkeden.dpk is missing";
            if (!dpi.Exists) return "darkeden.dpi (the index) is missing";
            if (dpi.Length < 8) return "darkeden.dpi is too short to be an index";

            byte[] magic = new byte[4];
            using (FileStream f = new FileStream(DpiFile, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                if (f.Read(magic, 0, 4) != 4)
                    return "darkeden.dpi cannot be read";
            }
            if (magic[0] != 'A' || magic[1] != 'B' || magic[2] != 'C' || magic[3] != 'D')
                return "darkeden.dpi is not an index (no ABCD mark)";
            if (dpi.Length <= 8 && dpk.Length > 8)
                return "darkeden.dpi is empty but darkeden.dpk is not";
            return null;
        }

        // The game keeps both halves open for as long as it runs, so opening them
        // exclusively fails exactly while it runs. A virus scanner can hold a file
        // for a moment, so a few tries before giving up.
        public bool IsGameRunning()
        {
            try
            {
                Mutex mutex;
                if (Mutex.TryOpenExisting("<<<DarkEden>>>", out mutex))
                {
                    mutex.Dispose();
                    return true;
                }
            }
            catch (UnauthorizedAccessException) { return true; }

            // (no permission to write is not "in use": that surfaces as its own error)
            for (int attempt = 0; attempt < 5; attempt++)
            {
                try
                {
                    foreach (string file in new[] { DpkFile, DpiFile })
                    {
                        if (File.Exists(file))
                            using (new FileStream(file, FileMode.Open, FileAccess.ReadWrite, FileShare.None)) { }
                    }
                    return false;
                }
                catch (IOException) { Thread.Sleep(600); }
            }
            return true;
        }

        // ---- the tools

        sealed class Result
        {
            public int ExitCode;
            public readonly List<string> Lines = new List<string>();
        }

        static string Quote(string arg)
        {
            if (arg.IndexOf('"') >= 0)
                throw new ArgumentException("Unusable name: " + arg);
            return "\"" + arg + "\"";
        }

        Result Run(string exe, IEnumerable<string> args, int timeoutMs)
        {
            StringBuilder line = new StringBuilder();
            foreach (string arg in args)
            {
                if (line.Length > 0) line.Append(' ');
                line.Append(Quote(arg));
            }

            ProcessStartInfo info = new ProcessStartInfo(exe, line.ToString())
            {
                WorkingDirectory = m_dataDir,
                UseShellExecute = false,
                CreateNoWindow = true,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                StandardOutputEncoding = Encoding.GetEncoding(949),
                StandardErrorEncoding = Encoding.GetEncoding(949),
            };

            Result result = new Result();
            using (Process process = new Process { StartInfo = info })
            {
                object gate = new object();
                DataReceivedEventHandler take = delegate(object sender, DataReceivedEventArgs e)
                {
                    if (e.Data != null)
                        lock (gate) result.Lines.Add(e.Data);
                };
                process.OutputDataReceived += take;
                process.ErrorDataReceived += take;
                process.Start();
                process.BeginOutputReadLine();
                process.BeginErrorReadLine();

                if (!process.WaitForExit(timeoutMs))
                {
                    try { process.Kill(); } catch (InvalidOperationException) { }
                    throw new IOException(Path.GetFileName(exe) + " did not finish in " + (timeoutMs / 1000) + " seconds.");
                }
                process.WaitForExit();      // drains the output events
                result.ExitCode = process.ExitCode;
            }
            return result;
        }

        // sha256 and size of entries as the archive holds them. vpaths null = every
        // entry. Entries that are not there go to missing; entries the archive cannot
        // read (a write killed part way leaves one like that) go to damaged - they are
        // for the caller to rewrite. Only an archive that cannot be opened at all throws.
        //
        // A damaged entry can take dpkget down with it (it reports FAILED, but the
        // damage may already have wrecked the process). Output is unbuffered, so what
        // was answered is known: the entry it died on is marked damaged and the rest
        // is asked again in a fresh process.
        public Dictionary<string, EntryRow> Hash(ICollection<string> vpaths, List<string> missing, List<string> damaged, Action<int> progress)
        {
            Dictionary<string, EntryRow> found = new Dictionary<string, EntryRow>(StringComparer.Ordinal);
            if (missing == null) missing = new List<string>();
            if (damaged == null) damaged = new List<string>();

            List<string> pending;
            if (vpaths == null)
            {
                // everything in one process: the common case, ~20 s for the whole archive
                Result all = Run(m_get, new List<string> { Base, "--hash" }, 30 * 60 * 1000);
                Collect(all, found, missing, damaged, progress);
                if (all.ExitCode == 0 || all.ExitCode == 3)
                    return found;
                ThrowIfUnopened(all);

                // it died part way: the archive's own order tells which entry it died on
                pending = List();
                MarkCulpritAndDropAnswered(pending, found, missing, damaged, !EndsOnFailed(all));
            }
            else
                pending = new List<string>(vpaths);

            int deadRuns = 0;
            while (pending.Count > 0)
            {
                List<string> batch = pending.GetRange(0, Math.Min(BatchSize, pending.Count));
                List<string> args = new List<string> { Base, "--hash" };
                args.AddRange(batch);
                int before = found.Count + missing.Count + damaged.Count;

                Result r = Run(m_get, args, 10 * 60 * 1000);
                Collect(r, found, missing, damaged, progress);
                bool crashed = r.ExitCode != 0 && r.ExitCode != 3;
                if (crashed)
                    ThrowIfUnopened(r);

                // a process that dies before answering anything, again and again, is
                // not one bad entry: the archive as a whole cannot be read
                if (crashed && found.Count + missing.Count + damaged.Count == before)
                {
                    if (++deadRuns >= 3)
                        throw new InvalidDataException("The archive cannot be read (dpkget exit " + r.ExitCode + ").");
                }
                else
                    deadRuns = 0;

                MarkCulpritAndDropAnswered(pending, found, missing, damaged, crashed && !EndsOnFailed(r));
            }
            return found;
        }

        // A process that reported an entry FAILED and then died was most likely
        // wrecked by that entry: the next one is not to blame. (If it were, the next
        // run dies on it straight away, with nothing before it, and it is caught then.)
        static bool EndsOnFailed(Result r)
        {
            for (int i = r.Lines.Count - 1; i >= 0; i--)
            {
                if (r.Lines[i].Trim().Length > 0)
                    return r.Lines[i].StartsWith("FAILED ", StringComparison.Ordinal);
            }
            return false;
        }

        static void Collect(Result r, Dictionary<string, EntryRow> found, List<string> missing, List<string> damaged, Action<int> progress)
        {
            foreach (string line in r.Lines)
            {
                if (line.StartsWith("MISSING ", StringComparison.Ordinal))
                {
                    missing.Add(line.Substring(8));
                    continue;
                }
                if (line.StartsWith("FAILED ", StringComparison.Ordinal))
                {
                    damaged.Add(line.Substring(7));
                    continue;
                }

                string[] parts = line.Split(new[] { ' ' }, 3);
                long size;
                if (parts.Length == 3 && parts[0].Length == 64 && long.TryParse(parts[1], out size))
                {
                    found[parts[2]] = new EntryRow { Hash = parts[0], Size = size, VPath = parts[2] };
                    if (progress != null) progress(found.Count);
                }
            }
        }

        // exit 1/2 = it never got to the entries (no archive, bad index, bad arguments)
        static void ThrowIfUnopened(Result r)
        {
            if (r.ExitCode == 1 || r.ExitCode == 2)
                throw new InvalidDataException("The archive could not be opened (" + string.Join(" ", r.Lines.ToArray()).Trim() + ").");
        }

        // Drops every answered entry from pending. After a crash, the first entry
        // still pending is the one the process died on: it is damaged, and goes too.
        static void MarkCulpritAndDropAnswered(List<string> pending, Dictionary<string, EntryRow> found,
                                               List<string> missing, List<string> damaged, bool crashed)
        {
            HashSet<string> answered = new HashSet<string>(found.Keys, StringComparer.Ordinal);
            answered.UnionWith(missing);
            answered.UnionWith(damaged);

            int firstOpen = pending.FindIndex(delegate(string v) { return !answered.Contains(v); });
            if (crashed && firstOpen >= 0)
            {
                damaged.Add(pending[firstOpen]);
                answered.Add(pending[firstOpen]);
            }
            pending.RemoveAll(delegate(string v) { return answered.Contains(v); });
        }

        // every entry name, in the archive's own order (the order --hash walks)
        public List<string> List()
        {
            Result r = Run(m_get, new List<string> { Base, "--list", "*" }, 10 * 60 * 1000);
            if (r.ExitCode != 0)
            {
                ThrowIfUnopened(r);
                throw new InvalidDataException("The archive's file list could not be read (dpkget exit " + r.ExitCode + ").");
            }
            List<string> names = new List<string>();
            foreach (string line in r.Lines)
            {
                if (line.StartsWith("  ", StringComparison.Ordinal))
                    names.Add(line.Trim());
            }
            return names;
        }

        // Writes files into the archive under their vpaths, replacing what is there.
        // Returns the vpaths that failed; empty means all went in.
        public List<string> Add(IList<KeyValuePair<string, string>> diskToVPath)
        {
            List<string> failures = new List<string>();
            for (int start = 0; start < diskToVPath.Count; start += BatchSize)
            {
                List<string> args = new List<string> { Base, "add" };
                HashSet<string> sent = new HashSet<string>(StringComparer.Ordinal);
                for (int i = start; i < Math.Min(diskToVPath.Count, start + BatchSize); i++)
                {
                    args.Add(diskToVPath[i].Key);
                    args.Add(diskToVPath[i].Value);
                    sent.Add(diskToVPath[i].Value);
                }

                Result r = Run(m_put, args, 10 * 60 * 1000);
                HashSet<string> done = new HashSet<string>(StringComparer.Ordinal);
                foreach (string line in r.Lines)
                {
                    // "  REPLACE  data/info/x.inf   <- C:\...\x.inf (123 bytes)"
                    string t = line.Trim();
                    if (t.StartsWith("REPLACE ", StringComparison.Ordinal) || t.StartsWith("ADD ", StringComparison.Ordinal))
                    {
                        string rest = t.Substring(t.IndexOf(' ')).Trim();
                        int arrow = rest.IndexOf(" <- ", StringComparison.Ordinal);
                        if (arrow > 0)
                            done.Add(rest.Substring(0, arrow).Trim());
                    }
                }

                foreach (string vpath in sent)
                {
                    if (r.ExitCode != 0 || !done.Contains(vpath))
                        failures.Add(vpath);
                }
            }
            return failures;
        }

        // Drops entries from the archive. An entry that is already gone counts as done.
        public bool Delete(ICollection<string> vpaths)
        {
            List<string> all = new List<string>(vpaths);
            for (int start = 0; start < all.Count; start += BatchSize)
            {
                List<string> args = new List<string> { Base, "del" };
                args.AddRange(all.GetRange(start, Math.Min(BatchSize, all.Count - start)));
                if (Run(m_put, args, 10 * 60 * 1000).ExitCode != 0)
                    return false;
            }
            return true;
        }
    }
}
