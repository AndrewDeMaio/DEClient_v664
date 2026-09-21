// dpkget - extract files from a DarkEden .dpk virtual file system.
//
// Replacement for NewDpkUnpaker.exe, which has three problems:
//
//  1. It ships as a DEBUG build, so its "argc < 3" guard is compiled out while
//     argv[2] is still dereferenced -- running it bare trips a blocking
//     assertion dialog.
//  2. It calls CreateRealFile(fileName, fileName), writing each entry to its
//     archive-internal path relative to the CURRENT DIRECTORY. Run it from
//     Release\ and "data/info/string.inf" lands on top of your real
//     Release\Data\info\String.inf, destroying translated files.
//  3. It exits after a single lookup, hit or miss.
//
// This tool always writes beneath an explicit output directory, never touches
// the archive, and keeps prompting until you choose to leave.
//
// Run with no arguments for the interactive prompt, or scripted:
//
//   dpkget <vfsbase> <outdir> <vpath> [vpath ...]   extract named entries
//   dpkget <vfsbase> <outdir> --glob <pattern>      extract everything matching
//   dpkget <vfsbase> --list [pattern]               list without extracting
//   dpkget <vfsbase> --hash [vpath ...]             sha256 of entries (all if none named)
//
// <vfsbase> omits the extension; the VFS appends .dpk / .dpi itself.
//
// --hash reads each entry through the VFS in memory and prints
//     <sha256> <size> <vpath>
// or  MISSING <vpath>
// one line each; exit 3 if any named entry is missing or unreadable. It is how
// the updater and the packing scripts check what an archive really holds
// without writing anything to disk.
#include "VirtualFileSystem.h"
#include "VirtualFileIO.h"
#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <io.h>

#pragma comment(lib, "bcrypt.lib")

static const char SEP = 0x2F;   // '/'

// CAUTION: never pass FS_READ to VirtualFileSystem::Start(). nfs.h defines
// FS_READ as 1 and fcntl.h defines O_WRONLY as 1, so Start()'s
//     bWriteMode = flags & O_WRONLY || flags & O_RDWR
// treats FS_READ as a WRITE open. That skips its "does the .dpk exist" guard
// and silently CREATES an empty archive when the file is missing. The original
// DpkUnpaker passes O_RDONLY (0), the only value that reads safely.
// An archive is a PAIR: .dpk holds the payload, .dpi the index. Checking only
// the .dpk is not enough -- a large .dpk beside an empty/truncated .dpi sends
// nFS walking the payload with an index that describes nothing, and it runs off
// the end and dies without printing anything. Validate both before opening.
static bool CheckPair(const char* base)
{
    std::string dpk(base); dpk += ".dpk";
    std::string dpi(base); dpi += ".dpi";

    if (_access(dpk.c_str(), 0) != 0) { printf("ERROR: %s does not exist.\n", dpk.c_str()); return false; }
    if (_access(dpi.c_str(), 0) != 0) { printf("ERROR: %s does not exist (the index is required).\n", dpi.c_str()); return false; }

    FILE* fk = fopen(dpk.c_str(), "rb");
    FILE* fi = fopen(dpi.c_str(), "rb");
    if (!fk || !fi)
    {
        printf("ERROR: could not read the archive pair (file in use?).\n");
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
    // 8 bytes == magic + a zero entry count: a freshly created, empty index.
    if (iSize <= 8 && kSize > 8)
    {
        printf("ERROR: %s is EMPTY (%ld bytes) but %s holds %ld bytes.\n",
               dpi.c_str(), iSize, dpk.c_str(), kSize);
        printf("       The index and payload do not belong together, so the\n"
               "       archive cannot be read. Restore the matching .dpi, or\n"
               "       delete both files and repack.\n");
        return false;
    }
    return true;
}

static bool OpenForRead(VirtualFileSystem& vfs, const char* base)
{
    if (!CheckPair(base)) return false;
    if (!vfs.Start(base, O_RDONLY))
    {
        printf("ERROR: could not open %s.dpk / %s.dpi\n", base, base);
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

static std::string Join(const char* dir, const char* rel)
{
    std::string s(dir);
    if (!s.empty() && s[s.size() - 1] != SEP && s[s.size() - 1] != 0x5C)
        s += SEP;
    s += rel;
    return s;
}

static int Extract(VirtualFileSystem& vfs, const char* outdir, const char* vpath, bool quiet)
{
    if (!vfs.IsFileExist(vpath))
    {
        printf("  NOT FOUND  %s\n", vpath);
        return 1;
    }
    std::string dest = Join(outdir, vpath);
    int size = vfs.GetFileSize(vpath);
    bool ok = vfs.CreateRealFile(vpath, dest.c_str());
    if (!quiet || !ok)
        printf("  %-9s %-46s -> %s (%d stored)\n", ok ? "OK" : "FAILED", vpath, dest.c_str(), size);
    return ok ? 0 : 1;
}

// Same normalisation the VFS applies to lookups: lowercase, backslash -> slash.
static std::string ToVPath(const char* in)
{
    std::string out;
    for (const char* p = in; *p; ++p)
    {
        char c = *p;
        if (c == 0x5C) c = SEP;
        if (c >= 'A' && c <= 'Z') c = char(c - 'A' + 'a');
        if (c == SEP && !out.empty() && out[out.size() - 1] == SEP)
            continue;
        out += c;
    }
    return out;
}

// sha256 of one entry, read through the VFS exactly as the client would read it.
// Returns 0 and prints "<hash> <size> <vpath>", or 1 and prints MISSING/FAILED.
static int HashEntry(VirtualFileSystem& vfs, BCRYPT_ALG_HANDLE alg, const char* rawpath)
{
    std::string vpath = ToVPath(rawpath);
    if (!vfs.IsFileExist(vpath.c_str()))
    {
        printf("MISSING %s\n", vpath.c_str());
        return 1;
    }

    VirtualFileIO file(&vfs);
    file.open(vpath.c_str(), std::ios_base::in | std::ios_base::binary);
    if (!file.is_open())
    {
        printf("FAILED %s\n", vpath.c_str());
        return 1;
    }

    BCRYPT_HASH_HANDLE h = NULL;
    if (BCryptCreateHash(alg, &h, NULL, 0, NULL, 0, 0) < 0)
    {
        file.close();
        printf("FAILED %s\n", vpath.c_str());
        return 1;
    }

    static char buffer[VirtualFileSystem::FILE_COPY_BUFFER_SIZE];
    long long total = 0;
    for (;;)
    {
        file.read(buffer, sizeof(buffer));
        int got = (int)file.gcount();
        if (got <= 0) break;
        BCryptHashData(h, (PUCHAR)buffer, (ULONG)got, 0);
        total += got;
    }
    file.close();

    UCHAR digest[32];
    bool ok = BCryptFinishHash(h, digest, sizeof(digest), 0) >= 0;
    BCryptDestroyHash(h);
    if (!ok)
    {
        printf("FAILED %s\n", vpath.c_str());
        return 1;
    }

    char hex[65];
    for (int i = 0; i < 32; ++i)
        sprintf(hex + i * 2, "%02x", digest[i]);
    printf("%s %lld %s\n", hex, total, vpath.c_str());
    return 0;
}

// An entry whose blocks were half overwritten (a write killed part way) can make
// the decompressor read wild memory. Catch that per entry, so one damaged entry is
// reported as FAILED and every other entry still gets its answer. (No C++ objects
// live in this frame, which __try requires.)
static int SafeHashEntry(VirtualFileSystem* vfs, BCRYPT_ALG_HANDLE alg, const char* vpath)
{
    __try
    {
        return HashEntry(*vfs, alg, vpath);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        printf("FAILED %s\n", vpath);
        return 1;
    }
}

static int RunHash(VirtualFileSystem& vfs, int count, char** vpaths)
{
    // every line reaches the caller even if the process dies on a later entry
    setvbuf(stdout, NULL, _IONBF, 0);

    BCRYPT_ALG_HANDLE alg = NULL;
    if (BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, NULL, 0) < 0)
    {
        printf("ERROR: SHA-256 is not available\n");
        return 2;
    }

    int failed = 0;
    if (count > 0)
    {
        for (int i = 0; i < count; ++i)
            failed += SafeHashEntry(&vfs, alg, vpaths[i]);
    }
    else
    {
        nfs_glob_t g;
        g.gl_offs = 0;
        vfs.GetNFS()->glob("*", GLOB_DOOFS, NULL, &g);
        for (int i = g.gl_offs; i < g.gl_pathc + g.gl_offs; ++i)
            failed += SafeHashEntry(&vfs, alg, g.gl_pathv[i]);
        vfs.GetNFS()->glob_free(&g);
    }

    BCryptCloseAlgorithmProvider(alg, 0);
    fflush(stdout);
    return failed ? 3 : 0;
}

// Returns entries matched. Pass extract=false to only list.
static int RunGlob(VirtualFileSystem& vfs, const char* outdir,
                   const char* pattern, bool extract)
{
    nfs_glob_t g;
    g.gl_offs = 0;
    vfs.GetNFS()->glob(pattern, GLOB_DOOFS, NULL, &g);
    int total = g.gl_pathc;
    printf("%d entries matching \"%s\"\n", total, pattern);

    int done = 0, failed = 0;
    for (int i = g.gl_offs; i < total + g.gl_offs; ++i)
    {
        if (!extract) { printf("  %s\n", g.gl_pathv[i]); continue; }
        if (Extract(vfs, outdir, g.gl_pathv[i], true)) ++failed; else ++done;
        if (((done + failed) % 500) == 0)
            printf("  ... %d/%d\n", done + failed, total);
    }
    vfs.GetNFS()->glob_free(&g);

    if (extract) printf("%d extracted, %d failed\n", done, failed);
    return total;
}

static int Interactive()
{
    printf("**********************\n");
    printf("  Dpk Get 1.0\n");
    printf("  (safe unpacker)\n");
    printf("**********************\n");

    VirtualFileSystem vfs;
    std::string base;
    for (;;)
    {
        base = Prompt("archive", "darkeden");
        if (base.empty()) return 0;
        std::string dpk = base + ".dpk";
        if (_access(dpk.c_str(), 0) == 0) break;
        printf("  %s not found in this folder. Try again, or blank to quit.\n", dpk.c_str());
    }
    if (!vfs.Start(base.c_str(), O_RDONLY))
    {
        printf("ERROR: could not open %s.dpk / %s.dpi\n", base.c_str(), base.c_str());
        return 2;
    }

    std::string outdir = Prompt("output folder", "out");
    if (outdir.empty()) outdir = "out";

    printf("\nEnter a file path to extract, a pattern such as data/ui/spk/*,\n");
    printf("'all' for everything, 'list <pattern>' to look without extracting,\n");
    printf("or 'exit' to quit.\n\n");

    for (;;)
    {
        std::string in = Prompt("(all,)", "");
        if (in.empty() || in == "exit" || in == "quit") break;

        if (in == "all")
        {
            RunGlob(vfs, outdir.c_str(), "*", true);
        }
        else if (in.compare(0, 5, "list ") == 0)
        {
            RunGlob(vfs, outdir.c_str(), in.substr(5).c_str(), false);
        }
        else if (in == "list")
        {
            RunGlob(vfs, outdir.c_str(), "*", false);
        }
        else if (in.find('*') != std::string::npos || in.find('?') != std::string::npos)
        {
            if (RunGlob(vfs, outdir.c_str(), in.c_str(), true) == 0)
                printf("  nothing matched that pattern -- try again.\n");
        }
        else
        {
            // single file; a miss re-prompts instead of exiting
            Extract(vfs, outdir.c_str(), in.c_str(), false);
        }
        printf("\n");
    }

    vfs.End();
    printf("done.\n");
    return 0;
}

int main(int argc, char** argv)
{
    // run by the updater with its output captured: a failed assert on a damaged
    // entry must end the process with an error code, not open a crash dialog
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

    if (argc == 1)
        return Interactive();

    if (argc < 3)
    {
        printf("dpkget - extract from a DarkEden .dpk\n\n"
               "  dpkget                                        interactive\n"
               "  dpkget <vfsbase> <outdir> <vpath> [vpath ...]\n"
               "  dpkget <vfsbase> <outdir> --glob <pattern>\n"
               "  dpkget <vfsbase> --list [pattern]\n"
               "  dpkget <vfsbase> --hash [vpath ...]\n\n"
               "vfsbase omits the extension. Never writes to the archive.\n");
        return 1;
    }

    VirtualFileSystem vfs;
    if (!OpenForRead(vfs, argv[1]))
        return 2;

    int rc = 0;

    if (!strcmp(argv[2], "--hash"))
    {
        rc = RunHash(vfs, argc - 3, argv + 3);
    }
    else if (!strcmp(argv[2], "--list"))
    {
        RunGlob(vfs, "", (argc > 3) ? argv[3] : "*", false);
    }
    else if (argc > 4 && !strcmp(argv[3], "--glob"))
    {
        RunGlob(vfs, argv[2], argv[4], true);
    }
    else
    {
        int done = 0, failed = 0;
        for (int i = 3; i < argc; ++i)
            if (Extract(vfs, argv[2], argv[i], false)) ++failed; else ++done;
        printf("\n%d extracted, %d failed\n", done, failed);
        rc = failed ? 3 : 0;
    }

    vfs.End();
    return rc;
}
