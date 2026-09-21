using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace DarkEden.Updater
{
    // Data\Info\Resolution.inf, the game's "Key: value" display settings. The
    // launcher owns three of its keys and leaves the others (D3DPresent,
    // SmoothScale, Scaler, Sharpen, TextOverlay) as it finds them.
    static class ResolutionFile
    {
        const string RelativePath = @"Data\Info\Resolution.inf";

        public static void Write(string gameDir, int width, int height, bool fullScreen)
        {
            string path = Path.Combine(gameDir, RelativePath);
            Directory.CreateDirectory(Path.GetDirectoryName(path));

            Dictionary<string, string> ours = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
            ours["ResolutionX"] = width.ToString();
            ours["ResolutionY"] = height.ToString();
            ours["FullScreen"] = fullScreen ? "1" : "0";

            List<string> lines = new List<string>();
            foreach (KeyValuePair<string, string> pair in ours)
                lines.Add(pair.Key + ": " + pair.Value);

            if (File.Exists(path))
            {
                foreach (string line in File.ReadAllLines(path))
                {
                    string[] parts = line.Split(new[] { ':' }, 2);
                    if (line.Trim().Length > 0 && !(parts.Length == 2 && ours.ContainsKey(parts[0].Trim())))
                        lines.Add(line);
                }
            }

            File.WriteAllLines(path, lines.ToArray());
        }

        // 16:9 sizes, the shape the game draws in, up to what this screen can show
        public static List<Size> Choices()
        {
            Size[] all = { new Size(1280, 720), new Size(1600, 900), new Size(1920, 1080), new Size(2560, 1440), new Size(3840, 2160) };
            Rectangle screen = Screen.PrimaryScreen.Bounds;

            List<Size> fit = new List<Size>();
            foreach (Size size in all)
            {
                if (fit.Count == 0 || (size.Width <= screen.Width && size.Height <= screen.Height))
                    fit.Add(size);
            }
            return fit;
        }
    }
}
