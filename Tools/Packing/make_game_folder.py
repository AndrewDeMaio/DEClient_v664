#!/usr/bin/env python3
"""Assemble a standalone game folder from Release\\ - everything the client needs
to launch outside the repo, and nothing else.

    python make_game_folder.py "C:\\Users\\you\\Desktop\\Release Folder"
    python make_game_folder.py <dest> --check     report only, copy nothing

What goes in, and why it cannot simply live in darkeden.dpk:

  * DarkEden.exe, DEUtil.dll, GL.dll   the only non-static binaries
  * Data\\darkeden.dpk + .dpi          every asset we have packed
  * Data\\Music\\*                      Vorbis\\FileStream.cpp opens these with
                                       fopen_s, a real disk read that never goes
                                       through the VFS - the original archive has
                                       no data/music/* entries for the same reason
  * Data\\Info\\version.inf             a 2-byte file, and a 2-byte entry comes back
                                       out of the archive with its second byte
                                       zeroed (see the dpk notes)
  * start.bat                          DarkEden.exe NEWSTART0 Futec(127.0.0.1:9909)
  * Log, ScreenShot, UserSet, temp     the client writes into these; it does not
                                       create them

Everything else under Release\\ is build output (.lib/.pdb/.exp), the packing
tools, or the loose copies that are already inside the archive.
"""
import filecmp
import os
import shutil
import sys

SRC = r"D:\GitHub\DEClient_v664\Release"

FILES = ["DarkEden.exe", "DEUtil.dll", "GL.dll", "start.bat"]
DATA_FILES = [os.path.join("Data", "darkeden.dpk"),
              os.path.join("Data", "darkeden.dpi"),
              os.path.join("Data", "Info", "version.inf")]
TREES = [os.path.join("Data", "Music")]
DIRS = ["Log", "ScreenShot", "UserSet", "temp"]
# left behind by a crashed run; the VFS recreates it
STALE = [os.path.join("Data", "darkeden.dpl")]


def find_source(rel):
    """Release\\ has Data\\info on disk but the client writes Data\\Info - match
    either, since Windows does not care and our copies differ in case."""
    p = os.path.join(SRC, rel)
    if os.path.exists(p):
        return p
    parts = rel.split(os.sep)
    cur = SRC
    for part in parts:
        try:
            match = next(e for e in os.listdir(cur) if e.lower() == part.lower())
        except (StopIteration, FileNotFoundError):
            return None
        cur = os.path.join(cur, match)
    return cur if os.path.exists(cur) else None


def copy_file(rel, dest, check):
    src = find_source(rel)
    if src is None:
        print("  MISSING SOURCE  %s" % rel)
        return 1
    dst = os.path.join(dest, rel)
    if os.path.exists(dst) and os.path.getsize(dst) == os.path.getsize(src) \
            and abs(os.path.getmtime(dst) - os.path.getmtime(src)) < 2:
        print("  ok        %-34s %10d" % (rel, os.path.getsize(src)))
        return 0
    why = "stale" if os.path.exists(dst) else "absent"
    print("  %-9s %-34s %10d %s" % ("CHECK" if check else "COPY", rel,
                                    os.path.getsize(src), why))
    if not check:
        os.makedirs(os.path.dirname(dst) or dest, exist_ok=True)
        shutil.copy2(src, dst)
    return 0 if check else 0


def copy_tree(rel, dest, check):
    src = find_source(rel)
    if src is None:
        print("  MISSING SOURCE  %s" % rel)
        return 1
    n_copy = n_ok = 0
    for dirpath, dirnames, files in os.walk(src):
        for f in files:
            s = os.path.join(dirpath, f)
            r = os.path.join(rel, os.path.relpath(s, src))
            d = os.path.join(dest, r)
            if os.path.exists(d) and filecmp.cmp(s, d, shallow=True):
                n_ok += 1
                continue
            n_copy += 1
            if not check:
                os.makedirs(os.path.dirname(d), exist_ok=True)
                shutil.copy2(s, d)
    print("  %-9s %-34s %d files (%d already there)"
          % ("CHECK" if check else "COPY", rel, n_copy, n_ok))
    return 0


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    dest = sys.argv[1]
    check = "--check" in sys.argv

    print("source: %s\ntarget: %s%s\n" % (SRC, dest, "   (check only)" if check else ""))
    if not check:
        os.makedirs(dest, exist_ok=True)

    bad = 0
    for rel in FILES + DATA_FILES:
        bad += copy_file(rel, dest, check)
    for rel in TREES:
        bad += copy_tree(rel, dest, check)

    for d in DIRS:
        p = os.path.join(dest, d)
        if not os.path.isdir(p):
            print("  %-9s %s\\" % ("CHECK" if check else "MKDIR", d))
            if not check:
                os.makedirs(p, exist_ok=True)

    for rel in STALE:
        p = os.path.join(dest, rel)
        if os.path.exists(p):
            print("  %-9s %s (stale lock from a crashed run)" % ("CHECK" if check else "DELETE", rel))
            if not check:
                os.remove(p)

    print("\n%s" % ("problems: %d" % bad if bad else
                    "done - run start.bat from the target folder"))
    return 1 if bad else 0


sys.exit(main())
