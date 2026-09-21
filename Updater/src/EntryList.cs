using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace DarkEden.Updater
{
    // One file inside darkeden.dpk. VPath is how the archive names it: lowercase,
    // forward slashes, "data/" first (data/info/npcscript.en.inf).
    sealed class EntryRow
    {
        public string Hash;     // sha256 of the file's content, lowercase hex
        public long Size;       // bytes, uncompressed
        public string VPath;
        public bool Hosted;     // the server has this file on its own (files/archive/<vpath>)
    }

    // A list of archive entries, in the one text format all three uses share:
    //
    //   # darkeden entries                     comment lines start with #
    //   # pair <dpk size> <dpk ticks> <dpi size> <dpi ticks>   (the updater's record only)
    //   <sha256> <size> <vpath>                an entry
    //   P <sha256> <size> <vpath>              an entry the server hosts on its own
    //   B <sha256> <size> <vpath>              an entry only the base archive carries
    //
    // The server's list (archive/entries.txt) marks every row P or B. The updater's
    // record of its own archive (Data\Updater\Archive.state) has no marks and a pair
    // line: the size and write time of darkeden.dpk/.dpi when the record was made,
    // so a pair changed behind its back makes the record worthless.
    sealed class EntryList
    {
        public readonly Dictionary<string, EntryRow> Rows = new Dictionary<string, EntryRow>(StringComparer.Ordinal);
        public string Pair = "";

        public static EntryList Parse(string text)
        {
            EntryList list = new EntryList();
            int lineNo = 0;

            foreach (string raw in text.Split('\n'))
            {
                lineNo++;
                string line = raw.TrimEnd('\r');
                if (line.Trim().Length == 0)
                    continue;

                if (line[0] == '#')
                {
                    string comment = line.Substring(1).Trim();
                    if (comment.StartsWith("pair ", StringComparison.Ordinal))
                        list.Pair = comment.Substring(5).Trim();
                    continue;
                }

                EntryRow row = new EntryRow();
                string rest = line;

                if (rest.Length > 2 && rest[1] == ' ' && (rest[0] == 'P' || rest[0] == 'B'))
                {
                    row.Hosted = rest[0] == 'P';
                    rest = rest.Substring(2);
                }

                string[] parts = rest.Split(new[] { ' ' }, 3);
                if (parts.Length != 3 || parts[0].Length != 64 || !IsHex(parts[0])
                    || !long.TryParse(parts[1], out row.Size) || row.Size < 0 || !IsValidVPath(parts[2]))
                    throw new InvalidDataException("Bad entry list line " + lineNo + ": " + line);

                row.Hash = parts[0].ToLowerInvariant();
                row.VPath = parts[2];

                if (list.Rows.ContainsKey(row.VPath))
                    throw new InvalidDataException("The entry list names " + row.VPath + " twice.");
                list.Rows.Add(row.VPath, row);
            }

            return list;
        }

        public static EntryList Load(string path)
        {
            return Parse(File.ReadAllText(path, Encoding.UTF8));
        }

        // written to a temp name and moved into place, so a crash never leaves half a record
        public void Save(string path)
        {
            StringBuilder text = new StringBuilder();
            text.Append("# darkeden entries\n");
            if (Pair.Length > 0)
                text.Append("# pair ").Append(Pair).Append('\n');

            List<string> keys = new List<string>(Rows.Keys);
            keys.Sort(StringComparer.Ordinal);
            foreach (string key in keys)
            {
                EntryRow row = Rows[key];
                text.Append(row.Hash).Append(' ').Append(row.Size).Append(' ').Append(row.VPath).Append('\n');
            }

            string temp = path + ".new";
            File.WriteAllText(temp, text.ToString(), new UTF8Encoding(false));
            if (File.Exists(path))
                File.Delete(path);
            File.Move(temp, path);
        }

        // what the archive code itself accepts as a name, and nothing that could
        // step outside a folder when it is used as a path on disk
        public static bool IsValidVPath(string vpath)
        {
            if (vpath.Length < 6 || vpath.Length > 200 || !vpath.StartsWith("data/", StringComparison.Ordinal))
                return false;

            foreach (char c in vpath)
            {
                bool ok = (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '/' || c == '.' || c == '_'
                          || c == '-' || c == ' ' || c == '(' || c == ')' || c == '+' || c == '&' || c == '\'';
                if (!ok)
                    return false;
            }

            foreach (string part in vpath.Split('/'))
            {
                if (part.Length == 0 || part == "." || part == ".." || part.EndsWith(" ") || part.EndsWith("."))
                    return false;
            }
            return true;
        }

        static bool IsHex(string s)
        {
            foreach (char c in s)
            {
                if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                    return false;
            }
            return true;
        }
    }
}
