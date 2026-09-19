#!/usr/bin/env python3
"""Turn a game folder into what the update server hosts: manifest.txt and files\\.

    python make_manifest.py <game folder> <out folder> --version 1.0.3
    python make_manifest.py <game folder> <out folder> --version 1.0.3 --server 203.0.113.7:9909

<game folder> is a finished install (make_game_folder.py builds one) with
Updater.exe in it. Upload <out folder> as it is; BaseUrl in the players'
Updater.ini points at it:

    <out>/manifest.txt       version, login server, and one line per file:
                             file <sha256> <size> <path>
    <out>/files/<path>       the files themselves
    <out>/news.txt           optional, yours to write; shown in the launcher

The updater downloads whatever is missing or hashes differently, and deletes
what an earlier manifest listed and this one no longer does. So a patch is: put
the changed or new loose file in the game folder, run this again with a new
version, upload. darkeden.dpk is one line here - touch it and everybody
downloads all of it again.

Unchanged files are not copied again (same size and time), and are hard linked
rather than copied when <out> is on the same drive.
"""
import argparse
import hashlib
import os
import shutil
import sys

# what the game and the updater write for themselves; never shipped, and since
# it is never listed the updater never deletes it either
SKIP_DIRS = {"log", "screenshot", "userset", "temp"}
SKIP_FILES = {"updater.ini", "updater.cache", "updater.state", "start.bat"}
SKIP_SUFFIXES = (".part", ".old", ".new", ".dpl", ".pdb", ".lib", ".exp", ".ilk", ".iobj", ".ipdb")


def wanted(rel):
    parts = rel.lower().split("/")
    if parts[0] in SKIP_DIRS and len(parts) > 1:
        return False
    return parts[-1] not in SKIP_FILES and not parts[-1].endswith(SKIP_SUFFIXES)


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def place(src, dst):
    """Hard link when it can, copy when it cannot; skip what is already there."""
    if os.path.exists(dst):
        s, d = os.stat(src), os.stat(dst)
        if s.st_size == d.st_size and abs(s.st_mtime - d.st_mtime) < 2:
            return "kept"
        os.remove(dst)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    try:
        os.link(src, dst)
        return "linked"
    except OSError:
        shutil.copy2(src, dst)
        return "copied"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("game")
    ap.add_argument("out")
    ap.add_argument("--version", required=True, help="digits and dots, e.g. 1.0.3 (the launcher draws it)")
    ap.add_argument("--server", default="", help="login server ip:port for players whose Updater.ini names none")
    ap.add_argument("--launch", default="DarkEden.exe")
    args = ap.parse_args()

    game, out = os.path.abspath(args.game), os.path.abspath(args.out)
    if not os.path.isfile(os.path.join(game, args.launch)):
        sys.exit("%s is not in %s" % (args.launch, game))
    if out == game or out.startswith(game + os.sep):
        sys.exit("the out folder must not be inside the game folder")

    rels = []
    for root, dirs, files in os.walk(game):
        for name in files:
            rel = os.path.relpath(os.path.join(root, name), game).replace(os.sep, "/")
            if wanted(rel):
                rels.append(rel)
    rels.sort(key=str.lower)

    lines = ["# DarkEden update manifest", "version " + args.version]
    if args.server:
        lines.append("server " + args.server)
    lines.append("launch " + args.launch)

    total = 0
    for rel in rels:
        src = os.path.join(game, rel)
        size = os.path.getsize(src)
        how = place(src, os.path.join(out, "files", rel))
        lines.append("file %s %d %s" % (sha256(src), size, rel))
        total += size
        print("  %-7s %12d  %s" % (how, size, rel))

    # files/ holds exactly what the manifest lists
    listed = {rel.lower() for rel in rels}
    for root, dirs, files in os.walk(os.path.join(out, "files")):
        for name in files:
            full = os.path.join(root, name)
            rel = os.path.relpath(full, os.path.join(out, "files")).replace(os.sep, "/")
            if rel.lower() not in listed:
                os.remove(full)
                print("  dropped               %s" % rel)

    with open(os.path.join(out, "manifest.txt"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")

    if not any(r.lower() == "updater.exe" for r in rels):
        print("note: no Updater.exe in the game folder, so players' updaters will not update themselves")
    print("%d files, %.1f MB, version %s -> %s" % (len(rels), total / 1048576.0, args.version, out))


if __name__ == "__main__":
    main()
