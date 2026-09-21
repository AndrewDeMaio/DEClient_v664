using System;
using System.Collections.Generic;
using System.IO;

namespace DarkEden.Updater
{
    // manifest.txt, written by Tools\Packing\make_manifest.py:
    //
    //   # comment
    //   version 1.0.3
    //   server 203.0.113.7:9909          optional; Updater.ini's LoginServer wins
    //   launch DarkEden.exe
    //   file <sha256 hex> <size> <path/with/forward/slashes and spaces>
    //   seed <sha256 hex> <size> <path>     a settings file the game rewrites: fetched
    //                                       when missing, then never touched again
    //
    // Every file of the install is listed; the 1.8GB archive is one line of it.
    sealed class ManifestEntry
    {
        public string Path;     // relative, forward slashes
        public long Size;
        public string Hash;     // lowercase sha256
        public bool Seed;       // only ever created, never brought back in line
    }

    sealed class Manifest
    {
        public string Version = "";
        public string Server = "";
        public string Launch = "DarkEden.exe";
        public readonly List<ManifestEntry> Files = new List<ManifestEntry>();

        public static Manifest Parse(string text)
        {
            Manifest manifest = new Manifest();
            HashSet<string> seen = new HashSet<string>(StringComparer.OrdinalIgnoreCase);

            foreach (string raw in text.Split('\n'))
            {
                string line = raw.Trim();
                if (line.Length == 0 || line[0] == '#')
                    continue;

                int space = line.IndexOf(' ');
                if (space < 0)
                    throw new InvalidDataException("Manifest line has no value: " + line);

                string key = line.Substring(0, space);
                string value = line.Substring(space + 1).Trim();

                switch (key)
                {
                    case "version": manifest.Version = value; break;
                    case "server": manifest.Server = value; break;

                    case "launch":
                        CheckPath(value);
                        manifest.Launch = value;
                        break;

                    case "file":
                    case "seed":
                    {
                        string[] parts = value.Split(new[] { ' ' }, 3);
                        ManifestEntry entry = new ManifestEntry();
                        if (parts.Length != 3 || parts[0].Length != 64 || !long.TryParse(parts[1], out entry.Size) || entry.Size < 0)
                            throw new InvalidDataException("Bad manifest file line: " + line);

                        entry.Seed = key == "seed";
                        entry.Hash = parts[0].ToLowerInvariant();
                        entry.Path = parts[2].Replace('\\', '/');
                        CheckPath(entry.Path);

                        if (!seen.Add(entry.Path))
                            throw new InvalidDataException("Manifest lists a file twice: " + entry.Path);

                        manifest.Files.Add(entry);
                        break;
                    }

                    // a newer generator may say more than this updater knows
                    default: break;
                }
            }

            if (manifest.Files.Count == 0)
                throw new InvalidDataException("The manifest lists no files.");

            return manifest;
        }

        // A manifest is downloaded text: it must never be able to name a file
        // outside the game folder.
        static void CheckPath(string path)
        {
            bool bad = path.Length == 0 || path.Length > 240
                || path[0] == '/' || path.IndexOf(':') >= 0 || path.IndexOfAny(System.IO.Path.GetInvalidPathChars()) >= 0;

            if (!bad)
            {
                foreach (string part in path.Split('/'))
                {
                    if (part.Length == 0 || part == "." || part == ".." || part.EndsWith(" ") || part.EndsWith("."))
                        bad = true;
                }
            }

            if (bad)
                throw new InvalidDataException("Manifest names an unsafe path: " + path);
        }
    }
}
