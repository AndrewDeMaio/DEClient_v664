using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace DarkEden.Updater
{
    // Hashing the 1.8GB archive takes several seconds, so a file's hash is kept
    // with the size and write time it was taken at and only taken again when one
    // of those moves. "Updater.exe /repair" ignores it.
    sealed class HashCache
    {
        public const string FileName = "Updater.cache";

        sealed class Row
        {
            public long Size;
            public long Ticks;
            public string Hash;
        }

        readonly Dictionary<string, Row> m_rows = new Dictionary<string, Row>(StringComparer.OrdinalIgnoreCase);
        readonly string m_path;

        public HashCache(string gameDir, bool ignoreSaved)
        {
            m_path = BookFiles.PathOf(gameDir, FileName);

            if (ignoreSaved || !File.Exists(m_path))
                return;

            try
            {
                foreach (string line in File.ReadAllLines(m_path))
                {
                    string[] parts = line.Split('|');
                    Row row = new Row();
                    if (parts.Length == 4 && long.TryParse(parts[1], out row.Size) && long.TryParse(parts[2], out row.Ticks))
                    {
                        row.Hash = parts[3];
                        m_rows[parts[0]] = row;
                    }
                }
            }
            catch (IOException) { }
        }

        public void Save()
        {
            StringBuilder text = new StringBuilder();
            foreach (KeyValuePair<string, Row> pair in m_rows)
                text.Append(pair.Key).Append('|').Append(pair.Value.Size).Append('|').Append(pair.Value.Ticks).Append('|').Append(pair.Value.Hash).Append("\r\n");

            try { File.WriteAllText(m_path, text.ToString()); }
            catch (IOException) { }
        }

        // progress: bytes hashed so far of this file
        public string GetHash(string relativePath, FileInfo file, Action<long> progress)
        {
            Row row;
            if (m_rows.TryGetValue(relativePath, out row) && row.Size == file.Length && row.Ticks == file.LastWriteTimeUtc.Ticks)
                return row.Hash;

            string hash = HashFile(file.FullName, progress);

            file.Refresh();
            m_rows[relativePath] = new Row { Size = file.Length, Ticks = file.LastWriteTimeUtc.Ticks, Hash = hash };
            return hash;
        }

        public void Forget(string relativePath)
        {
            m_rows.Remove(relativePath);
        }

        public static string HashFile(string path, Action<long> progress)
        {
            using (SHA256 sha = SHA256.Create())
            using (FileStream stream = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read, 1 << 20, FileOptions.SequentialScan))
            {
                byte[] buffer = new byte[1 << 20];
                long done = 0;
                int read;

                while ((read = stream.Read(buffer, 0, buffer.Length)) > 0)
                {
                    sha.TransformBlock(buffer, 0, read, null, 0);
                    done += read;
                    if (progress != null)
                        progress(done);
                }

                sha.TransformFinalBlock(buffer, 0, 0);
                return ToHex(sha.Hash);
            }
        }

        public static string ToHex(byte[] bytes)
        {
            StringBuilder hex = new StringBuilder(bytes.Length * 2);
            foreach (byte b in bytes)
                hex.Append(b.ToString("x2"));
            return hex.ToString();
        }
    }
}
