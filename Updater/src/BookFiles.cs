using System;
using System.IO;

namespace DarkEden.Updater
{
    // Where the updater keeps its own bookkeeping (Updater.cache, Updater.state):
    // Data\Updater\, out of the way of the game's root folder. Updater.ini is not
    // one of them - it is the player's to edit and ships beside the exe.
    static class BookFiles
    {
        const string RelativeDir = @"Data\Updater";

        public static string PathOf(string gameDir, string name)
        {
            string dir = Path.Combine(gameDir, RelativeDir);
            string path = Path.Combine(dir, name);

            try
            {
                Directory.CreateDirectory(dir);

                // they used to sit in the root. Losing the cache costs a rehash of the
                // whole archive, losing the state leaves dropped files behind: move them.
                string old = Path.Combine(gameDir, name);
                if (File.Exists(old))
                {
                    if (File.Exists(path))
                        File.Delete(old);
                    else
                        File.Move(old, path);
                }
            }
            catch (IOException) { }
            catch (UnauthorizedAccessException) { }

            return path;
        }
    }
}
