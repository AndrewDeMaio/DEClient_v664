using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Text;
using System.Threading;

namespace DarkEden.Updater
{
    enum Phase
    {
        Working,
        Ready,          // verified, or nothing to verify against: the game may start
        Failed,         // could not finish; the game may still start if it is there
        Restarting,     // a new Updater.exe was put in place and launched
    }

    // Brings the folder the updater sits in into line with the server's manifest.
    // Runs on its own thread; the window reads the public fields on a timer.
    sealed class UpdateEngine
    {
        public const string StateFileName = "Updater.state";
        const string PartSuffix = ".part";
        const string NewSuffix = ".new";
        public const string OldSuffix = ".old";

        readonly string m_gameDir;
        readonly Config m_config;
        readonly bool m_repair;
        readonly string m_args;         // handed on to the updater that replaces this one
        readonly object m_lock = new object();
        readonly List<string> m_log = new List<string>();
        readonly List<string> m_secrets = new List<string>();
        StreamWriter m_logFile;

        public volatile Phase Phase = Phase.Working;
        public volatile string Status = "";
        public volatile string Detail = "";
        public volatile string Version = "";
        public volatile string News = "";
        public volatile string Server = "";
        public volatile string Launch = "DarkEden.exe";
        public double FileFraction;      // doubles are read torn-free enough for a progress bar
        public double TotalFraction;

        public UpdateEngine(string gameDir, Config config, bool repair, string args)
        {
            m_gameDir = gameDir;
            m_config = config;
            m_repair = repair;
            m_args = args;
            Server = config.LoginServer;
            AddSecret(config.BaseUrl);
            AddSecret(config.LoginServer);
        }

        public string GameDir { get { return m_gameDir; } }

        public string[] GetLog()
        {
            lock (m_lock)
                return m_log.ToArray();
        }

        public void Start()
        {
            Thread thread = new Thread(Run);
            thread.IsBackground = true;
            thread.Name = "UpdateEngine";
            thread.Start();
        }

        // Neither the window nor Log\Updater.log (which testers paste into chats
        // and bug reports) ever names a server: a framework error message can
        // carry the address it failed on, so every line is scrubbed on the way in.
        string Scrub(string line)
        {
            foreach (string secret in m_secrets)
            {
                int at;
                while (secret.Length > 0 && (at = line.IndexOf(secret, StringComparison.OrdinalIgnoreCase)) >= 0)
                    line = line.Substring(0, at) + "[server]" + line.Substring(at + secret.Length);
            }
            return line;
        }

        void AddSecret(string urlOrServer)
        {
            if (string.IsNullOrEmpty(urlOrServer))
                return;

            m_secrets.Add(urlOrServer.TrimEnd('/'));

            // and the bare host, however the message spells the rest
            string host = urlOrServer;
            int scheme = host.IndexOf("://", StringComparison.Ordinal);
            if (scheme >= 0) host = host.Substring(scheme + 3);
            int end = host.IndexOfAny(new[] { '/', ':' });
            if (end >= 0) host = host.Substring(0, end);
            if (host.Length > 3)
                m_secrets.Add(host);
        }

        internal void Log(string line)
        {
            line = Scrub(line);

            lock (m_lock)
            {
                m_log.Add(line);

                try
                {
                    if (m_logFile == null)
                    {
                        string dir = Path.Combine(m_gameDir, "Log");
                        Directory.CreateDirectory(dir);
                        m_logFile = new StreamWriter(Path.Combine(dir, "Updater.log"), false, Encoding.UTF8);
                        m_logFile.AutoFlush = true;
                    }
                    m_logFile.WriteLine(DateTime.Now.ToString("HH:mm:ss") + "  " + line);
                }
                catch (IOException) { }
                catch (UnauthorizedAccessException) { }
            }
        }

        void Run()
        {
            try
            {
                Update();
            }
            catch (Exception e)
            {
                Log("FAILED: " + e.Message);
                Status = Scrub(Describe(e));
                Detail = "";
                Phase = Phase.Failed;
            }
        }

        static string Describe(Exception e)
        {
            WebException web = e as WebException;
            if (web != null)
            {
                HttpWebResponse response = web.Response as HttpWebResponse;
                if (response != null)
                    return "Update server answered " + (int)response.StatusCode + " " + response.StatusDescription + ".";
                return "Could not reach the update server. The game may be out of date.";
            }

            if (e is UnauthorizedAccessException)
                return "No permission to write here. Move the game out of Program Files or run as administrator.";

            return e.Message;
        }

        void Update()
        {
            // the client writes into these and does not create them
            foreach (string dir in new[] { "Log", "ScreenShot", "UserSet", "temp" })
                Directory.CreateDirectory(Path.Combine(m_gameDir, dir));

            if (m_config.BaseUrl.Length == 0)
            {
                Log("No BaseUrl in " + Config.FileName + ": nothing to update from.");
                Status = "No update server is set. Ready to start.";
                TotalFraction = FileFraction = 1;
                Phase = Phase.Ready;
                return;
            }

            ServicePointManager.SecurityProtocol |= SecurityProtocolType.Tls12;
            ServicePointManager.DefaultConnectionLimit = 4;

            Status = "Connecting to the update server...";

            Manifest manifest = Manifest.Parse(DownloadText("manifest.txt"));
            Version = manifest.Version;
            Launch = manifest.Launch;
            if (m_config.LoginServer.Length == 0)
                Server = manifest.Server;
            AddSecret(manifest.Server);
            Log("Manifest " + manifest.Version + ": " + manifest.Files.Count + " files" + (manifest.HasArchive ? " + the game archive, patched file by file." : "."));

            try { News = DownloadText("news.txt"); }
            catch (WebException) { }    // optional

            HashCache cache = new HashCache(m_gameDir, m_repair);

            if (UpdateSelf(manifest, cache))
                return;

            // ---- what differs
            Status = "Checking files...";
            string selfName = Path.GetFileName(Process.GetCurrentProcess().MainModule.FileName);
            List<ManifestEntry> wanted = new List<ManifestEntry>();
            long totalBytes = 0, doneBytes = 0;

            foreach (ManifestEntry entry in manifest.Files)
                totalBytes += entry.Size;

            for (int i = 0; i < manifest.Files.Count; i++)
            {
                ManifestEntry entry = manifest.Files[i];
                Detail = (i + 1) + " / " + manifest.Files.Count;

                if (!string.Equals(entry.Path, selfName, StringComparison.OrdinalIgnoreCase) && !IsCurrent(entry, cache, doneBytes, totalBytes))
                    wanted.Add(entry);

                doneBytes += entry.Size;
                TotalFraction = Fraction(doneBytes, totalBytes);
            }
            cache.Save();

            // ---- fetch it
            long wantedBytes = 0, fetchedBytes = 0;
            foreach (ManifestEntry entry in wanted)
                wantedBytes += entry.Size;

            if (wanted.Count > 0)
                Log(wanted.Count + " files to download, " + FormatBytes(wantedBytes) + ".");

            for (int i = 0; i < wanted.Count; i++)
            {
                ManifestEntry entry = wanted[i];
                Status = "Downloading " + entry.Path;
                Detail = (i + 1) + " / " + wanted.Count + "   " + FormatBytes(fetchedBytes) + " of " + FormatBytes(wantedBytes);

                long before = fetchedBytes;
                Download(entry, delegate(long fileDone)
                {
                    FileFraction = Fraction(fileDone, entry.Size);
                    TotalFraction = Fraction(before + fileDone, wantedBytes);
                });
                Install(entry, cache);

                fetchedBytes += entry.Size;
                Log("Updated " + entry.Path);
            }

            // the files inside darkeden.dpk, one by one (only when the server
            // describes the archive that way; otherwise it was a plain file above)
            if (manifest.HasArchive)
            {
                cache.Save();
                new ArchivePatcher(this, manifest, cache, m_repair).Run();
            }

            RemoveObsolete(manifest, cache);
            SaveState(manifest);
            cache.Save();

            FileFraction = TotalFraction = 1;
            Detail = "";
            Status = wanted.Count > 0 ? "Update complete. Ready to start." : "Up to date. Ready to start.";
            Log(Status);
            Phase = Phase.Ready;
        }

        internal static double Fraction(long done, long total)
        {
            return total <= 0 ? 1 : Math.Min(1.0, (double)done / total);
        }

        bool IsCurrent(ManifestEntry entry, HashCache cache, long doneBytes, long totalBytes)
        {
            FileInfo file = new FileInfo(LocalPath(entry.Path));

            // the player's own settings by now, whatever they hash to
            if (entry.Seed && file.Exists)
                return true;

            if (!file.Exists || file.Length != entry.Size)
                return false;

            string hash = cache.GetHash(entry.Path, file, delegate(long hashed)
            {
                FileFraction = Fraction(hashed, entry.Size);
                TotalFraction = Fraction(doneBytes + hashed, totalBytes);
            });
            return hash == entry.Hash;
        }

        string LocalPath(string relativePath)
        {
            string full = Path.GetFullPath(Path.Combine(m_gameDir, relativePath.Replace('/', Path.DirectorySeparatorChar)));

            // Manifest.CheckPath already refuses these; this is the second lock
            string root = m_gameDir.TrimEnd(Path.DirectorySeparatorChar) + Path.DirectorySeparatorChar;
            if (!full.StartsWith(root, StringComparison.OrdinalIgnoreCase))
                throw new InvalidDataException("Path leaves the game folder: " + relativePath);

            return full;
        }

        // ---- the updater itself
        //
        // A running exe cannot be overwritten but it can be renamed, so the new
        // one takes its name and is started in its place. Program.Main deletes
        // the .old one on the next run.
        bool UpdateSelf(Manifest manifest, HashCache cache)
        {
            string selfPath = Process.GetCurrentProcess().MainModule.FileName;
            string selfName = Path.GetFileName(selfPath);

            if (!string.Equals(Path.GetDirectoryName(selfPath).TrimEnd('\\'), m_gameDir.TrimEnd('\\'), StringComparison.OrdinalIgnoreCase))
                return false;

            ManifestEntry entry = manifest.Files.Find(delegate(ManifestEntry e) { return string.Equals(e.Path, selfName, StringComparison.OrdinalIgnoreCase); });
            if (entry == null)
                return false;

            if (HashCache.HashFile(selfPath, null) == entry.Hash)
                return false;

            Status = "Updating the updater...";
            Log("A new " + selfName + " is available.");

            Download(entry, delegate(long done) { FileFraction = TotalFraction = Fraction(done, entry.Size); });

            string part = LocalPath(entry.Path) + PartSuffix;
            string old = selfPath + OldSuffix;
            File.Delete(old);
            File.Move(selfPath, old);
            File.Move(part, selfPath);
            cache.Forget(entry.Path);

            Log("Restarting into the new updater.");
            Process.Start(new ProcessStartInfo(selfPath, m_args) { WorkingDirectory = m_gameDir, UseShellExecute = false });
            Phase = Phase.Restarting;
            return true;
        }

        // ---- downloads
        string Url(string relativePath)
        {
            StringBuilder url = new StringBuilder(m_config.BaseUrl);
            string[] parts = relativePath.Split('/');
            for (int i = 0; i < parts.Length; i++)
            {
                if (i > 0) url.Append('/');
                url.Append(Uri.EscapeDataString(parts[i]));
            }
            return url.ToString();
        }

        HttpWebRequest Request(string url)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            // make_manifest.py looks for "ArchivePatch/1" in Updater.exe before it
            // publishes an archive as base/entries lines: an updater without it
            // would not know those lines and would lose the archive
            request.UserAgent = "DarkEdenUpdater/2 ArchivePatch/1";
            request.Timeout = 20000;
            request.ReadWriteTimeout = 30000;
            request.AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate;
            request.CachePolicy = new System.Net.Cache.RequestCachePolicy(System.Net.Cache.RequestCacheLevel.NoCacheNoStore);
            return request;
        }

        string DownloadText(string name)
        {
            using (WebResponse response = Request(Url(name)).GetResponse())
            using (StreamReader reader = new StreamReader(response.GetResponseStream(), Encoding.UTF8))
                return reader.ReadToEnd();
        }

        // Into <file>.part, picking up where a broken download stopped, and only
        // accepted once the whole file hashes to what the manifest says.
        internal void Download(ManifestEntry entry, Action<long> progress)
        {
            Download("files/" + entry.Path, LocalPath(entry.Path) + PartSuffix, entry.Hash, entry.Size, entry.Path, progress);
        }

        // serverPath: under BaseUrl; part: where it is written; label: for the log
        internal void Download(string serverPath, string part, string hash, long size, string label, Action<long> progress)
        {
            if (progress == null)
                progress = delegate(long done) { };
            Directory.CreateDirectory(Path.GetDirectoryName(part));

            for (int attempt = 1; ; attempt++)
            {
                try
                {
                    DownloadOnce(serverPath, part, size, label, progress);

                    if (HashCache.HashFile(part, null) == hash)
                        return;

                    File.Delete(part);
                    throw new InvalidDataException("Downloaded " + label + " does not match the manifest.");
                }
                catch (Exception e)
                {
                    if (attempt >= 3 || !(e is WebException || e is IOException || e is InvalidDataException))
                        throw;

                    Log("Retrying " + label + ": " + e.Message);
                    Thread.Sleep(1500 * attempt);
                }
            }
        }

        void DownloadOnce(string serverPath, string part, long size, string label, Action<long> progress)
        {
            long have = File.Exists(part) ? new FileInfo(part).Length : 0;
            if (have > size)
            {
                File.Delete(part);
                have = 0;
            }
            if (have == size)
            {
                // an empty file (the install has a few) is nothing to ask the server for
                if (have == 0)
                    File.WriteAllBytes(part, new byte[0]);
                return;
            }

            HttpWebRequest request = Request(Url(serverPath));
            request.AutomaticDecompression = DecompressionMethods.None;    // a Range is in stored bytes
            if (have > 0)
                request.AddRange(have);

            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            {
                // a server that ignores Range sends the whole file again
                bool resumed = have > 0 && response.StatusCode == HttpStatusCode.PartialContent;
                if (!resumed)
                    have = 0;

                using (Stream input = response.GetResponseStream())
                using (FileStream output = new FileStream(part, resumed ? FileMode.Append : FileMode.Create, FileAccess.Write, FileShare.None, 1 << 16))
                {
                    byte[] buffer = new byte[1 << 16];
                    int read;
                    while ((read = input.Read(buffer, 0, buffer.Length)) > 0)
                    {
                        output.Write(buffer, 0, read);
                        have += read;
                        progress(have);
                    }
                }
            }

            if (have != size)
                throw new IOException(label + " stopped at " + have + " of " + size + " bytes.");
        }

        internal void Install(ManifestEntry entry, HashCache cache)
        {
            string target = LocalPath(entry.Path);
            string part = target + PartSuffix;

            try
            {
                if (File.Exists(target))
                {
                    File.SetAttributes(target, FileAttributes.Normal);
                    File.Delete(target);
                }
                File.Move(part, target);
            }
            catch (IOException)
            {
                throw new IOException(entry.Path + " is in use. Close the game and run the updater again.");
            }

            // hashed a moment ago as the .part; spare the next run doing it again
            cache.Forget(entry.Path);
            cache.GetHash(entry.Path, new FileInfo(target), null);
        }

        // ---- files a newer manifest dropped
        //
        // Only what an earlier manifest put here is ever deleted: saves, settings,
        // screenshots and logs were never listed, so they are never touched.
        void RemoveObsolete(Manifest manifest, HashCache cache)
        {
            string statePath = BookFiles.PathOf(m_gameDir, StateFileName);
            if (!File.Exists(statePath))
                return;

            HashSet<string> current = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
            foreach (ManifestEntry entry in manifest.Files)
                current.Add(entry.Path);
            if (manifest.HasArchive)
            {
                current.Add(manifest.BaseDpk.Path);
                current.Add(manifest.BaseDpi.Path);
            }

            // an older manifest may have listed, as plain files, what the game writes
            // for itself; those are the player's now
            foreach (string path in s_never_remove)
                current.Add(path);

            string selfName = Path.GetFileName(Process.GetCurrentProcess().MainModule.FileName);

            foreach (string line in File.ReadAllLines(statePath))
            {
                string path = line.Trim();
                if (path.Length == 0 || current.Contains(path) || string.Equals(path, selfName, StringComparison.OrdinalIgnoreCase))
                    continue;

                // never the archive: a manifest that stopped naming it is far more
                // likely a publishing mistake than a wish to delete 1.8 GB
                if (path.EndsWith(".dpk", StringComparison.OrdinalIgnoreCase) || path.EndsWith(".dpi", StringComparison.OrdinalIgnoreCase))
                    continue;

                try
                {
                    string full = LocalPath(path);
                    if (File.Exists(full))
                    {
                        File.SetAttributes(full, FileAttributes.Normal);
                        File.Delete(full);
                        Log("Removed " + path);
                    }
                    cache.Forget(path);
                }
                catch (IOException e) { Log("Could not remove " + path + ": " + e.Message); }
                catch (UnauthorizedAccessException e) { Log("Could not remove " + path + ": " + e.Message); }
                catch (InvalidDataException) { }
            }
        }

        static readonly string[] s_never_remove = { "Data/Info/Player.inf", "Data/Info/ClientConfig.inf", "Data/Info/Resolution.inf" };

        void SaveState(Manifest manifest)
        {
            List<string> lines = new List<string>();
            foreach (ManifestEntry entry in manifest.Files)
            {
                if (!entry.Seed)
                    lines.Add(entry.Path);
            }
            if (manifest.HasArchive)
            {
                lines.Add(manifest.BaseDpk.Path);
                lines.Add(manifest.BaseDpi.Path);
            }
            File.WriteAllLines(BookFiles.PathOf(m_gameDir, StateFileName), lines.ToArray());
        }

        public static string FormatBytes(long bytes)
        {
            if (bytes >= 1L << 30) return (bytes / (double)(1L << 30)).ToString("0.00") + " GB";
            if (bytes >= 1L << 20) return (bytes / (double)(1L << 20)).ToString("0.0") + " MB";
            if (bytes >= 1L << 10) return (bytes / (double)(1L << 10)).ToString("0") + " KB";
            return bytes + " B";
        }
    }
}
