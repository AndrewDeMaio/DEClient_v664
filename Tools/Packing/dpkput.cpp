// dpkput - write files into a DarkEden .dpk virtual file system.
//
// Replacement for the missing NewDpkpaker source (the CVS module this repo came
// from contains DpkUnpacker but never Dpkpacker).
//
// The shipped NewDpkpaker.exe is destructive: it renames your archive to
// *_BACK.dpk, creates a fresh empty one in its place, and replaces the .dpi
// index. If the pack then adds nothing you are left with a 0-byte .dpk, an
// 8-byte empty index, a stale .dpl lock, and 1.8GB of orphaned payload with no
// index to address it.
//
// This tool never renames, never replaces, always releases the lock, and
// refuses to open an existing archive for write.
//
// Run with no arguments for the interactive prompt, or scripted:
//
//   dpkput <vfsbase> list  [pattern]                list archive contents
//   dpkput <vfsbase> add   <diskfile> <vpath> ...   add/replace files
//   dpkput <vfsbase> build <rootdir>                pack a tree into a NEW archive
//
// <vfsbase> omits the extension; the VFS appends .dpk / .dpi itself.
#include "VirtualFileSystem.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <stdarg.h>
#include <vector>

static const char BS  = 0x5C;   // backslash
static const char FS_ = 0x2F;   // forward slash

// Everything is mirrored to dpkput.log so a console that closes on exit does
// not take the diagnosis with it.
static FILE* g_log = NULL;
static std::vector<std::string> g_failures;

static void Log(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    if (g_log)
    {
        va_start(ap, fmt);
        vfprintf(g_log, fmt, ap);
        va_end(ap);
        fflush(g_log);
    }
}

// CAUTION: never pass FS_READ to VirtualFileSystem::Start(). nfs.h defines
// FS_READ as 1 and fcntl.h defines O_WRONLY as 1, so Start()'s
//     bWriteMode = flags & O_WRONLY || flags & O_RDWR
// treats FS_READ as a WRITE open, skipping its "does the .dpk exist" guard and
// silently CREATING an empty archive. Read with O_RDONLY (0) only.
static bool ArchiveExists(const char* base)
{
    std::string dpk(base); dpk += ".dpk";
    return _access(dpk.c_str(), 0) == 0;
}

// An archive is a PAIR, and opening it for write with either half missing is
// destructive: nfs_start takes its "create" branch and nfs_data_create opens
// the .dpk with "w+b", truncating a 1.8GB payload to nothing. So list/add/del
// refuse to start unless both halves exist and the .dpi really is an index
// (ABCD magic, and not an empty index beside a full payload).
static bool CheckPair(const char* base)
{
    std::string dpk(base); dpk += ".dpk";
    std::string dpi(base); dpi += ".dpi";

    if (_access(dpk.c_str(), 0) != 0) { printf("ERROR: %s does not exist.\n", dpk.c_str()); return false; }
    if (_access(dpi.c_str(), 0) != 0)
    {
        printf("ERROR: %s does not exist. Refusing to open %s without its index:\n"
               "       the archive code would recreate the pair and empty the .dpk.\n", dpi.c_str(), dpk.c_str());
        return false;
    }

    FILE* fk = fopen(dpk.c_str(), "rb");
    FILE* fi = fopen(dpi.c_str(), "rb");
    if (!fk || !fi)
    {
        printf("ERROR: could not read the archive pair (in use by the game?).\n");
        if (fk) fclose(fk);
        if (fi) fclose(fi);
        return false;
    }
    fseek(fk, 0, SEEK_END); long kSize = ftell(fk);
    fseek(fi, 0, SEEK_END); long iSize = ftell(fi);

    char magic[4] = {0};
    fseek(fi, 0, SEEK_SET);
    size_t rd = fread(magic, 1, 4, fi);
    fclose(fk); fclose(fi);

    if (rd != 4 || memcmp(magic, "ABCD", 4) != 0)
    {
        printf("ERROR: %s is not a dpk index (missing ABCD magic).\n", dpi.c_str());
        return false;
    }
    if (iSize <= 8 && kSize > 8)
    {
        printf("ERROR: %s is EMPTY (%ld bytes) but %s holds %ld bytes - they do not belong together.\n",
               dpi.c_str(), iSize, dpk.c_str(), kSize);
        return false;
    }
    return true;
}

static std::string Prompt(const char* label, const char* def)
{
    char buf[1024];
    printf("%s", label);
    if (def && *def) printf(" [%s]", def);
    printf(": ");
    fflush(stdout);
    if (!fgets(buf, sizeof(buf), stdin)) return "";
    std::string s(buf);
    while (!s.empty() && (s[s.size()-1] == '\n' || s[s.size()-1] == '\r' ||
                          s[s.size()-1] == ' '  || s[s.size()-1] == '\t'))
        s.erase(s.size() - 1);
    while (!s.empty() && (s[0] == ' ' || s[0] == '\t')) s.erase(0, 1);
    if (s.empty() && def) s = def;
    return s;
}

// Mirror of make_unique_path() in VFS_Macro.h: lowercase, backslash -> slash,
// and collapse runs of repeated separators.
//
// This MUST be applied to every path handed to AddFileRename(). That function
// stores destname verbatim, while IsFileExist() -- and every lookup the client
// itself performs -- normalises first. Store "data/info/ClientConfig.inf" with
// its capitals and the game can never find it: it will only ever ask for
// "data/info/clientconfig.inf". Every entry in the original darkeden.dpk is
// lowercase for exactly this reason.
static void ToVPath(std::string& s)
{
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c == BS) c = FS_;
        if (c >= 'A' && c <= 'Z') c = char(c - 'A' + 'a');
        if (c == FS_ && !out.empty() && out[out.size() - 1] == FS_)
            continue;                       // collapse repeated separators
        out += c;
    }
    s.swap(out);
}

static int AddOne(VirtualFileSystem& vfs, const char* disk, const char* vpath, bool quiet)
{
    HANDLE h = CreateFileA(disk, GENERIC_READ, FILE_SHARE_READ, NULL,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE)
    {
        DWORD e = GetLastError();
        Log("  MISSING  %s (win32 error %lu)\n", disk, (unsigned long)e);
        g_failures.push_back(std::string(disk) + "  [open failed, win32 " +
                             std::to_string((long long)e) + "]");
        return 1;
    }
    DWORD sz = GetFileSize(h, NULL);
    CloseHandle(h);

    // Normalise before storing, so what we write is what the client will ask
    // for. Without this, mixed-case sources land in the archive unreachable.
    std::string v(vpath);
    ToVPath(v);

    bool existed = vfs.IsFileExist(v.c_str());
    if (existed) vfs.DeleteFile(v.c_str());

    vfs.AddFileRename(disk, v.c_str(), true /* compress */);

    bool ok = vfs.IsFileExist(v.c_str());
    if (!quiet || !ok)
        Log("  %-8s %-44s <- %s (%lu bytes)\n",
            ok ? (existed ? "REPLACE" : "ADD") : "FAILED",
            v.c_str(), disk, (unsigned long)sz);
    if (!ok)
        g_failures.push_back(v + "  <- " + disk + "  (" +
                             std::to_string((long long)sz) + " bytes)");
    return ok ? 0 : 1;
}

static void Walk(VirtualFileSystem& vfs, const std::string& root,
                 const std::string& rel, int& added, int& failed)
{
    std::string base = root;
    if (!rel.empty()) { base += BS; base += rel; }

    std::string pat = base; pat += BS; pat += "*";

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pat.c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return;

    do
    {
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, "..")) continue;

        std::string sub = rel;
        if (!sub.empty()) sub += BS;
        sub += fd.cFileName;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            Walk(vfs, root, sub, added, failed);
        }
        else
        {
            std::string disk = root; disk += BS; disk += sub;
            std::string v = sub; ToVPath(v);
            if (AddOne(vfs, disk.c_str(), v.c_str(), true)) ++failed; else ++added;
            if (((added + failed) % 500) == 0)
                printf("  ... %d packed\n", added + failed);
        }
    } while (FindNextFileA(h, &fd));

    FindClose(h);
}

static int DoBuild(const char* base, const char* rootdir)
{
    std::string root = rootdir;
    while (!root.empty() && (root[root.size()-1] == BS || root[root.size()-1] == FS_))
        root.erase(root.size() - 1);

    if (_access(root.c_str(), 0) != 0)
    {
        printf("ERROR: source folder \"%s\" does not exist.\n", root.c_str());
        return 2;
    }

    if (!g_log) g_log = fopen("dpkput.log", "w");

    VirtualFileSystem vfs;
    if (!vfs.Start(base, FS_RW))
    {
        Log("ERROR: could not create %s.dpk / %s.dpi\n", base, base);
        return 2;
    }

    Log("packing \"%s\" into %s.dpk ...\n", root.c_str(), base);
    int added = 0, failed = 0;
    Walk(vfs, root, "", added, failed);
    vfs.End();

    Log("\n%d written, %d failed\n", added, failed);

    if (!g_failures.empty())
    {
        Log("\n---- %d FAILURES ----\n", (int)g_failures.size());
        for (size_t i = 0; i < g_failures.size(); ++i)
            Log("  %s\n", g_failures[i].c_str());
    }
    if (added == 0)
        Log("WARNING: nothing was packed. Check the folder actually contains files.\n");

    Log("\nfull log written to dpkput.log\n");
    if (g_log) { fclose(g_log); g_log = NULL; }
    return failed ? 3 : 0;
}

static int Interactive()
{
    printf("**********************\n");
    printf("  Dpk Put 1.0\n");
    printf("  (safe packer)\n");
    printf("**********************\n");

    std::string dir = Prompt("dir to pack", "out");
    if (dir.empty()) return 0;

    std::string base;
    for (;;)
    {
        base = Prompt("new archive name (no extension)", "rebuilt");
        if (base.empty()) return 0;
        if (!ArchiveExists(base.c_str())) break;
        printf("  %s.dpk already exists -- building would destroy it.\n", base.c_str());
        printf("  Pick another name, or move that file aside first.\n");
    }

    int rc = DoBuild(base.c_str(), dir.c_str());

    printf("\npress Enter to close...");
    fflush(stdout);
    getchar();
    return rc;
}

int main(int argc, char** argv)
{
    // run by the updater with its output captured: a failed assert on a damaged
    // archive must end the process with an error code, not open a crash dialog
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

    if (argc == 1)
        return Interactive();

    if (argc < 3)
    {
        printf("dpkput - write files into a DarkEden .dpk\n\n"
               "  dpkput                                          interactive\n"
               "  dpkput <vfsbase> list  [pattern]\n"
               "  dpkput <vfsbase> add   <diskfile> <vpath> [...]\n"
               "  dpkput <vfsbase> del   <vpath> [...]\n"
               "  dpkput <vfsbase> build <rootdir>\n\n"
               "vfsbase omits the extension. Work on a COPY of the master archive.\n");
        return 1;
    }

    const char* base = argv[1];
    const char* mode = argv[2];
    bool listing  = !strcmp(mode, "list");
    bool building = !strcmp(mode, "build");
    bool exists   = ArchiveExists(base);

    // Guard rails. Without these a typo silently destroys an archive: opening
    // an existing .dpk for write reinitialises it to an empty filesystem.
    if ((listing || !strcmp(mode, "add") || !strcmp(mode, "del")) && !exists)
    {
        printf("ERROR: %s.dpk does not exist.\n"
               "       \"%s\" needs an existing archive. Use \"build\" to create one.\n",
               base, mode);
        return 2;
    }
    if (building && exists)
    {
        printf("ERROR: %s.dpk already exists.\n"
               "       \"build\" creates a NEW archive and would destroy this one --\n"
               "       opening an existing .dpk for write reinitialises it to empty.\n"
               "       Pick an unused name, or move the existing file aside first.\n",
               base);
        return 2;
    }

    if (building)
    {
        if (argc < 4) { printf("ERROR: build needs <rootdir>\n"); return 1; }
        return DoBuild(base, argv[3]);
    }

    if (!CheckPair(base))
        return 2;

    VirtualFileSystem vfs;
    if (!vfs.Start(base, listing ? O_RDONLY : FS_RW))
    {
        printf("ERROR: could not open %s.dpk / %s.dpi\n", base, base);
        return 2;
    }

    int rc = 0;

    if (listing)
    {
        const char* pattern = (argc > 3) ? argv[3] : "*";
        nfs_glob_t g;
        g.gl_offs = 0;
        vfs.GetNFS()->glob(pattern, GLOB_DOOFS, NULL, &g);
        printf("%d entries matching \"%s\"\n", g.gl_pathc, pattern);
        for (int i = g.gl_offs; i < g.gl_pathc + g.gl_offs; ++i)
            printf("  %s\n", g.gl_pathv[i]);
        vfs.GetNFS()->glob_free(&g);
    }
    else if (!strcmp(mode, "add"))
    {
        if (argc < 5 || ((argc - 3) % 2))
        {
            printf("ERROR: add needs <diskfile> <vpath> pairs\n");
            rc = 1;
        }
        else
        {
            int added = 0, failed = 0;
            for (int i = 3; i + 1 < argc; i += 2)
                if (AddOne(vfs, argv[i], argv[i + 1], false)) ++failed; else ++added;
            printf("\n%d written, %d failed\n", added, failed);
            rc = failed ? 3 : 0;
        }
    }
    else if (!strcmp(mode, "del"))
    {
        // Drops entries from the index. Their blocks go back to the free pool
        // and later adds reuse them (measured: replacing an entry with one the
        // same size or smaller leaves the .dpk the same size; a larger one grows
        // it only by the difference), but the .dpk never shrinks. Use "build"
        // to compact it.
        if (argc < 4)
        {
            printf("ERROR: del needs <vpath> [...]\n");
            rc = 1;
        }
        else
        {
            int gone = 0, missing = 0;
            for (int i = 3; i < argc; ++i)
            {
                std::string v(argv[i]);
                ToVPath(v);
                // already gone is what was asked for: not a failure, so a
                // repeated removal (an interrupted update run again) succeeds
                if (!vfs.IsFileExist(v.c_str()))
                {
                    printf("  ABSENT   %s\n", v.c_str());
                    continue;
                }
                vfs.DeleteFile(v.c_str());
                bool ok = !vfs.IsFileExist(v.c_str());
                printf("  %-8s %s\n", ok ? "DELETE" : "FAILED", v.c_str());
                if (ok) ++gone; else ++missing;
            }
            printf("\n%d deleted, %d not deleted\n", gone, missing);
            rc = missing ? 3 : 0;
        }
    }
    else
    {
        printf("ERROR: unknown mode \"%s\"\n", mode);
        rc = 1;
    }

    vfs.End();   // releases the .dpl lock the shipped packer leaves behind
    return rc;
}
