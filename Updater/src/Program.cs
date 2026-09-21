using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows.Forms;

namespace DarkEden.Updater
{
    static class Program
    {
        static string QuoteArgs(string[] args)
        {
            System.Text.StringBuilder line = new System.Text.StringBuilder();
            foreach (string arg in args)
            {
                if (line.Length > 0) line.Append(' ');
                line.Append(arg.IndexOf(' ') >= 0 ? "\"" + arg + "\"" : arg);
            }
            return line.ToString();
        }

        // Updater.exe [/repair] [/start] [/shot <png>]
        //   /repair   hash every file again instead of trusting Updater.cache, and
        //             read every file inside the game archive again (Archive.state)
        //   /start    start the game as soon as the update is through, without the click
        //   /shot     draw the window once into a png and exit (layout checks)
        //
        // Whatever else is on the command line is ignored: the game starts the
        // updater with its own arguments when it is run without NEWSTART.
        [STAThread]
        static void Main(string[] args)
        {
            bool repair = false;
            bool start = false;
            string shot = null;

            for (int i = 0; i < args.Length; i++)
            {
                // "-repair" as well: some shells rewrite a leading slash into a path
                string arg = args[i].Length > 0 && args[i][0] == '-' ? "/" + args[i].Substring(1) : args[i];

                if (string.Equals(arg, "/repair", StringComparison.OrdinalIgnoreCase))
                    repair = true;
                else if (string.Equals(arg, "/start", StringComparison.OrdinalIgnoreCase))
                    start = true;
                else if (string.Equals(arg, "/shot", StringComparison.OrdinalIgnoreCase) && i + 1 < args.Length)
                    shot = args[++i];
            }

            string selfPath = Process.GetCurrentProcess().MainModule.FileName;
            string gameDir = Path.GetDirectoryName(selfPath);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            bool first;
            using (Mutex mutex = new Mutex(true, "DarkEdenUpdater_" + gameDir.ToLowerInvariant().GetHashCode().ToString("x8"), out first))
            {
                // the updater that just replaced itself may still be closing
                for (int wait = 0; !first && wait < 20; wait++)
                {
                    Thread.Sleep(250);
                    try { first = mutex.WaitOne(0); }
                    catch (AbandonedMutexException) { first = true; }
                }

                if (!first)
                {
                    MessageBox.Show("The updater is already running.", "DarkEden", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }

                try { File.Delete(selfPath + UpdateEngine.OldSuffix); }
                catch (IOException) { }
                catch (UnauthorizedAccessException) { }

                Config config;
                try
                {
                    config = Config.Load(gameDir);
                }
                catch (Exception e)
                {
                    MessageBox.Show("Cannot use " + gameDir + ":\n" + e.Message, "DarkEden", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                using (LauncherForm form = new LauncherForm(new UpdateEngine(gameDir, config, repair, QuoteArgs(args)), config, start))
                {
                    if (shot != null)
                    {
                        try { form.SaveShot(shot); }
                        catch (Exception e) { File.WriteAllText(shot + ".err", e.ToString()); }
                    }
                    else
                        Application.Run(form);
                }

                mutex.ReleaseMutex();
            }
        }
    }
}
