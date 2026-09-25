#!/usr/bin/env python3
"""Stage single-file patches for the files inside darkeden.dpk.

    python make_patch.py info\\npcscript.en.inf [ui\\txt\\item.rpk ...]    stage changed files
    python make_patch.py info\\*.inf ui\\spk\\*.spk                         wildcards (** = any depth)
    python make_patch.py --all                                            everything that differs
    python make_patch.py --all --full                                     ... hashing every file
    python make_patch.py --remove data/ui/spk/old.spk                     drop an entry
    python make_patch.py --unstage info\\npcscript.en.inf                  take one back out
    python make_patch.py                                                  show what is staged

--all compares the archive files in Release\\Data with the base (size first, then
sha256) and makes the staged set the difference: changed and new files are staged,
staged files that are back to the base are unstaged. Base files missing from
Release\\Data are only reported; drop them with --remove.

--all remembers when it last ran (Release\\Package\\last_scan.txt, with the base it
compared against). The next run only hashes files modified since then, plus every
file that is already staged, so a day's work compares in seconds instead of
hashing all 1.8 GB. A file whose modification time is older than the last scan
is taken as unchanged - true for anything edited, saved, or checked out with git,
not for a copy made with its old timestamp kept (robocopy /COPY:DAT, an archive
extracted with timestamps). For those, or to get the exact difference after an
--unstage, add --full: it hashes everything and rewrites the stamp. A new base
(make_dpk.py) or a missing stamp also means a full compare.

Paths are relative to Release\\Data (the loose working copy). The package's
Data\\darkeden.entries (written by make_dpk.py) is the base: the list of what the
published darkeden.dpk holds. A staged file lands in Release\\Package\\Archive\\files\\
under its archive name; removals go into Archive\\removed.txt.

Upload Release\\Package\\Archive\\ to the game folder on the server as Archive/
(replacing what is there), then run ./publish.sh patch. The server lists every
file of the archive with its sha256, marks the staged ones as hosted singly, and
players' updaters download only those and write them into their own archive.

A file identical to the base is not staged (there is nothing to send). What
make_dpk.py would never put into the archive - Music, 2-byte files such as
version.inf, player.inf, editing leftovers - is refused here too: those ship loose.
"""
import argparse
import glob
import os
import shutil
import sys
import time

from make_dpk import DEFAULT_OUT, DEFAULT_SRC, classify, read_entries, sha256


SCAN_TXT = "last_scan.txt"      # beside PACKAGE.txt, not inside Archive\\ (nothing to upload)
SCAN_MARGIN = 2                 # seconds; a save right at the scan start is checked again next time


def read_scan(path):
    """-> (base dpk sha256, epoch seconds when --all last walked the tree) or None"""
    if not os.path.isfile(path):
        return None
    base_hash = when = None
    with open(path, encoding="utf-8") as f:
        for line in f:
            p = line.split()
            if len(p) >= 2 and p[0] == "base":
                base_hash = p[1]
            elif len(p) >= 2 and p[0] == "time":
                try:
                    when = float(p[1])
                except ValueError:
                    return None
    if base_hash is None or when is None:
        return None
    return base_hash, when


def write_scan(path, base_hash, when):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# make_patch.py --all last compared Release\\Data with this base at this time.\n"
                "# Files not modified since are taken as unchanged; --all --full hashes everything.\n")
        f.write("base %s\n" % base_hash)
        f.write("time %d %s\n" % (when, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(when))))


def vpath_of(arg):
    rel = arg.replace("\\", "/").strip("/").lower()
    if rel.startswith("data/"):
        rel = rel[5:]
    return rel, "data/" + rel


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("paths", nargs="*", help="files under Release\\Data (wildcards allowed)")
    ap.add_argument("--all", action="store_true", help="stage what differs from the base")
    ap.add_argument("--full", action="store_true",
                    help="with --all: hash every file instead of only those modified since the last scan")
    ap.add_argument("--remove", nargs="+", metavar="VPATH", help="archive entries to drop")
    ap.add_argument("--unstage", nargs="+", metavar="PATH", help="staged files to take back out")
    ap.add_argument("--src", default=DEFAULT_SRC)
    ap.add_argument("--package", default=DEFAULT_OUT)
    a = ap.parse_args()

    entries = os.path.join(a.package, "Data", "darkeden.entries")
    if not os.path.isfile(entries):
        sys.exit("no base list at %s\n  build the base with make_dpk.py, or list the published pair with\n"
                 "  make_dpk.py --entries-only <its Data folder> --entries-out %s" % (entries, entries))
    header, base = read_entries(entries)
    archive = os.path.join(a.package, "Archive")
    files = os.path.join(archive, "files")
    removed_txt = os.path.join(archive, "removed.txt")
    os.makedirs(files, exist_ok=True)

    # the delta belongs to this base; the server refuses a delta made for another
    base_txt = os.path.join(archive, "base.txt")
    with open(base_txt, "w", encoding="utf-8", newline="\n") as f:
        f.write(header["dpk"][0] + "\n")

    removed = []
    if os.path.isfile(removed_txt):
        removed = [l.strip() for l in open(removed_txt, encoding="utf-8") if l.strip()]

    # wildcards, expanded against Release\Data (cmd and PowerShell leave them to us)
    paths = []
    for arg in a.paths:
        if "*" in arg or "?" in arg:
            hits = [h for h in glob.glob(os.path.join(a.src, arg), recursive=True) if os.path.isfile(h)]
            if not hits:
                sys.exit("nothing in %s matches %s" % (a.src, arg))
            paths += [os.path.relpath(h, a.src) for h in sorted(hits)]
        else:
            paths.append(arg)

    if a.all:
        # files modified before the last scan (of this same base) are taken as unchanged
        scan_txt = os.path.join(a.package, SCAN_TXT)
        since = None
        if a.full:
            print("comparing every archive file in %s with the base (--full) ..." % a.src)
        else:
            prev = read_scan(scan_txt)
            if prev is None:
                print("no scan recorded yet - comparing every archive file in %s with the base ..." % a.src)
            elif prev[0] != header["dpk"][0]:
                print("the base changed since the last scan - comparing every archive file in %s ..." % a.src)
            else:
                since = prev[1] - SCAN_MARGIN
                print("comparing files in %s modified since %s with the base (--full checks all) ..."
                      % (a.src, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(prev[1]))))
        scan_start = time.time()
        hashed = untouched = 0
        in_src = set()
        for root, dirs, names in os.walk(a.src):
            for name in names:
                disk = os.path.join(root, name)
                rel = os.path.relpath(disk, a.src).replace("\\", "/").lower()
                st = os.stat(disk)
                size = st.st_size
                if classify(rel, size) != "pack":
                    continue
                vpath = "data/" + rel
                in_src.add(vpath)
                row = base.get(vpath)
                staged = os.path.join(files, *vpath.split("/"))
                if row is not None and row[1] == size:
                    # same size as the base: only a hash tells. Skip it when it was not touched
                    # since the last scan - unless it is staged, which must always be re-checked
                    if since is not None and st.st_mtime < since and not os.path.exists(staged):
                        untouched += 1
                        continue
                    hashed += 1
                    if row[0] == sha256(disk):
                        if os.path.exists(staged):
                            os.remove(staged)
                            print("  back to the base, unstaged: %s" % vpath)
                        continue
                if os.path.exists(staged) and os.path.getsize(staged) == size and sha256(staged) == sha256(disk):
                    continue        # already staged as it is now
                paths.append(rel)
        if since is not None:
            print("  %d files hashed, %d untouched since the last scan" % (hashed, untouched))
        missing = sorted(v for v in base if v not in in_src and v not in removed)
        if missing:
            print("  %d base files are no longer in Release\\Data (not removed - use --remove if meant):" % len(missing))
            for v in missing[:20]:
                print("    " + v)

    for arg in paths:
        rel, vpath = vpath_of(arg)
        disk = os.path.join(a.src, *rel.split("/"))
        if not os.path.isfile(disk):
            sys.exit("no such file: %s" % disk)
        kind = classify(rel, os.path.getsize(disk))
        if kind != "pack":
            sys.exit("%s does not go into the archive (%s)" % (rel, kind))

        staged = os.path.join(files, *vpath.split("/"))
        h, size = sha256(disk), os.path.getsize(disk)
        if base.get(vpath) == (h, size):
            if os.path.exists(staged):
                os.remove(staged)
            print("  same as the base archive, nothing to send: %s" % vpath)
            continue
        os.makedirs(os.path.dirname(staged), exist_ok=True)
        shutil.copy2(disk, staged)
        if vpath in removed:
            removed.remove(vpath)
        print("  %-8s %s (%d bytes)" % ("changed" if vpath in base else "new", vpath, size))

    if a.all:
        write_scan(scan_txt, header["dpk"][0], scan_start)

    for arg in a.unstage or []:
        rel, vpath = vpath_of(arg)
        staged = os.path.join(files, *vpath.split("/"))
        if os.path.exists(staged):
            os.remove(staged)
            print("  unstaged %s" % vpath)

    for v in a.remove or []:
        rel, vpath = vpath_of(v)
        if vpath not in base:
            sys.exit("%s is not in the base archive" % vpath)
        if vpath not in removed:
            removed.append(vpath)
        staged = os.path.join(files, *vpath.split("/"))
        if os.path.exists(staged):
            os.remove(staged)
        print("  remove   %s" % vpath)

    with open(removed_txt, "w", encoding="utf-8", newline="\n") as f:
        f.write("".join(v + "\n" for v in sorted(set(removed))))

    # prune empty folders, then show the whole delta
    for root, dirs, fs in os.walk(files, topdown=False):
        if root != files and not os.listdir(root):
            os.rmdir(root)
    staged = []
    for root, dirs, fs in os.walk(files):
        for n in fs:
            p = os.path.join(root, n)
            staged.append((os.path.relpath(p, files).replace(os.sep, "/"), os.path.getsize(p)))
    staged.sort()

    print("\nStaged against base %s (%d files):" % (header["dpk"][0][:16], len(base)))
    for v, s in staged:
        print("  %s  %s (%d bytes)" % ("changed" if v in base else "new    ", v, s))
    for v in sorted(set(removed)):
        print("  remove   %s" % v)
    if not staged and not removed:
        print("  nothing - players would download nothing")
    else:
        print("\nplayers download %.1f KB. Upload %s to the server's game folder as Archive/\n"
              "(replace its contents), then run ./publish.sh patch there."
              % (sum(s for _, s in staged) / 1024.0, archive))
    return 0


if __name__ == "__main__":
    sys.exit(main())
