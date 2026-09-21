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
    //   base <sha256 hex> <size> Data/darkeden.dpk   the archive pair as first published:
    //   base <sha256 hex> <size> Data/darkeden.dpi   fetched only when the local pair is
    //                                       missing or unusable, never compared as a whole
    //                                       afterwards (patching changes both files)
    //   entries <sha256 hex> <size> archive/entries.txt   what the archive should hold,
    //                                       file by file (see ArchivePatcher)
    //
    // Without base/entries lines the archive is two plain file lines, as before.
    sealed class ManifestEntry
    {
        public string Path;     // relative, forward slashes
        public long Size;
        public string Hash;     // lowercase sha256
        public bool Seed;       // only ever created, never brought back in line
    }

    sealed class Manifest
    {
        public const string DpkPath = "Data/darkeden.dpk";
        public const string DpiPath = "Data/darkeden.dpi";

        public string Version = "";
        public string Server = "";
        public string Launch = "DarkEden.exe";
        public readonly List<ManifestEntry> Files = new List<ManifestEntry>();

        // set together or not at all
        public ManifestEntry BaseDpk;
        public ManifestEntry BaseDpi;
        public ManifestEntry Entries;   // Path is where it lives under files/ on the server

        public bool HasArchive { get { return BaseDpk != null; } }

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
                    case "base":
                    case "entries":
                    {
                        string[] parts = value.Split(new[] { ' ' }, 3);
                        ManifestEntry entry = new ManifestEntry();
                        if (parts.Length != 3 || parts[0].Length != 64 || !long.TryParse(parts[1], out entry.Size) || entry.Size < 0)
                            throw new InvalidDataException("Bad manifest " + key + " line: " + line);

                        entry.Seed = key == "seed";
                        entry.Hash = parts[0].ToLowerInvariant();
                        entry.Path = parts[2].Replace('\\', '/');
                        CheckPath(entry.Path);

                        if (!seen.Add(entry.Path))
                            throw new InvalidDataException("Manifest lists a file twice: " + entry.Path);

                        if (key == "base")
                        {
                            if (string.Equals(entry.Path, DpkPath, StringComparison.OrdinalIgnoreCase))
                                manifest.BaseDpk = entry;
                            else if (string.Equals(entry.Path, DpiPath, StringComparison.OrdinalIgnoreCase))
                                manifest.BaseDpi = entry;
                            else
                                throw new InvalidDataException("A base line names something other than the archive: " + entry.Path);
                        }
                        else if (key == "entries")
                        {
                            if (manifest.Entries != null)
                                throw new InvalidDataException("The manifest has two entries lines.");
                            manifest.Entries = entry;
                        }
                        else
                            manifest.Files.Add(entry);
                        break;
                    }

                    // a newer generator may say more than this updater knows
                    default: break;
                }
            }

            if (manifest.Files.Count == 0)
                throw new InvalidDataException("The manifest lists no files.");

            // the archive is described completely or not at all
            bool anyArchive = manifest.BaseDpk != null || manifest.BaseDpi != null || manifest.Entries != null;
            if (anyArchive && (manifest.BaseDpk == null || manifest.BaseDpi == null || manifest.Entries == null))
                throw new InvalidDataException("The manifest describes the archive only in part (needs both base lines and an entries line).");

            // and never also as plain files
            foreach (ManifestEntry entry in manifest.Files)
            {
                if (anyArchive && (string.Equals(entry.Path, DpkPath, StringComparison.OrdinalIgnoreCase)
                                   || string.Equals(entry.Path, DpiPath, StringComparison.OrdinalIgnoreCase)))
                    throw new InvalidDataException("The manifest lists the archive both as base and as a file.");
            }

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
