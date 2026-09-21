using System;
using System.Collections.Generic;
using System.IO;

namespace DarkEden.Updater
{
    // Updater.ini beside the exe: "Key=Value" lines, '#' or ';' comments.
    //
    //   BaseUrl      where manifest.txt and files/ live; empty = no update server yet
    //   LoginServer  ip:port handed to the game as Futec(ip:port). Overrides the
    //                manifest's own "server" line, so a LAN tester and an outside
    //                tester can share one host.
    //   HomepageUrl / MarketUrl   what the two left buttons open; empty = inert
    //   FullScreen / Resolution   the launcher's own two controls. The game writes
    //                Data\Info\Resolution.inf back as 1280x720 whenever it exits, so
    //                the choice lives here and the file is written before each start.
    sealed class Config
    {
        public const string FileName = "Updater.ini";

        public string BaseUrl = "";
        public string LoginServer = "";
        public string HomepageUrl = "";
        public string MarketUrl = "";
        public bool FullScreen;             // windowed 1280x720 until the player says otherwise
        public int Width = 1280, Height = 720;

        string m_path;

        public static Config Load(string gameDir)
        {
            Config config = new Config();
            string path = Path.Combine(gameDir, FileName);
            config.m_path = path;

            if (!File.Exists(path))
            {
                File.WriteAllLines(path, new[]
                {
                    "# DarkEden updater settings",
                    "# BaseUrl: the folder on the update server holding manifest.txt and files/",
                    "BaseUrl=",
                    "# LoginServer: ip:port of the login server; empty = use the one the update server names",
                    "LoginServer=127.0.0.1:9909",
                    "HomepageUrl=",
                    "MarketUrl=",
                });
            }

            foreach (KeyValuePair<string, string> pair in ReadPairs(path))
            {
                switch (pair.Key.ToLowerInvariant())
                {
                    case "baseurl": config.BaseUrl = pair.Value; break;
                    case "loginserver": config.LoginServer = pair.Value; break;
                    case "homepageurl": config.HomepageUrl = pair.Value; break;
                    case "marketurl": config.MarketUrl = pair.Value; break;

                    case "fullscreen": config.FullScreen = pair.Value == "1"; break;

                    case "resolution":
                    {
                        string[] size = pair.Value.ToLowerInvariant().Split('x');
                        int w, h;
                        if (size.Length == 2 && int.TryParse(size[0], out w) && int.TryParse(size[1], out h) && w >= 640 && h >= 360)
                        {
                            config.Width = w;
                            config.Height = h;
                        }
                        break;
                    }
                }
            }

            if (config.BaseUrl.Length > 0 && !config.BaseUrl.EndsWith("/"))
                config.BaseUrl += "/";

            return config;
        }

        // One key of the file, the rest of it (comments included) left as it is.
        public void Save(string key, string value)
        {
            try
            {
                List<string> lines = new List<string>(File.Exists(m_path) ? File.ReadAllLines(m_path) : new string[0]);
                int at = lines.FindIndex(delegate(string line) { return line.TrimStart().StartsWith(key + "=", StringComparison.OrdinalIgnoreCase); });

                if (at >= 0) lines[at] = key + "=" + value;
                else lines.Add(key + "=" + value);

                File.WriteAllLines(m_path, lines.ToArray());
            }
            catch (IOException) { }
            catch (UnauthorizedAccessException) { }
        }

        static IEnumerable<KeyValuePair<string, string>> ReadPairs(string path)
        {
            foreach (string raw in File.ReadAllLines(path))
            {
                string line = raw.Trim();
                if (line.Length == 0 || line[0] == '#' || line[0] == ';')
                    continue;

                int eq = line.IndexOf('=');
                if (eq <= 0)
                    continue;

                yield return new KeyValuePair<string, string>(line.Substring(0, eq).Trim(), line.Substring(eq + 1).Trim());
            }
        }

        // "ip:port", nothing else: it goes onto the game's command line, whose
        // parser looks for '(' ':' ')' across the whole string
        public static bool IsValidServer(string server)
        {
            if (string.IsNullOrEmpty(server))
                return false;

            int colon = server.LastIndexOf(':');
            if (colon <= 0 || colon == server.Length - 1)
                return false;

            int port;
            if (!int.TryParse(server.Substring(colon + 1), out port) || port <= 0 || port > 65535)
                return false;

            foreach (char c in server.Substring(0, colon))
            {
                if (!(char.IsLetterOrDigit(c) || c == '.' || c == '-'))
                    return false;
            }
            return true;
        }
    }
}
