// dpkraw - dump RAW virtual-file bytes (VFHeader + CVFHeader + stored payload)
// for one or more entries, bypassing the compression/XOR layer entirely.
// Diagnostic only: never writes to the archive.
//
//   dpkraw <vfsbase> <outdir> <vpath> [vpath ...]
#include "VirtualFileSystem.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <fcntl.h>

static std::string BaseName(const char* p)
{
    std::string s(p);
    size_t a = s.find_last_of("/\\");
    return (a == std::string::npos) ? s : s.substr(a + 1);
}

int main(int argc, char** argv)
{
    if (argc < 4) { printf("usage: dpkraw <vfsbase> <outdir> <vpath> [vpath ...]\n"); return 2; }

    VirtualFileSystem vfs;
    if (!vfs.Start(argv[1], O_RDONLY)) { printf("ERROR: cannot open %s\n", argv[1]); return 1; }

    CNFS* nfs = vfs.GetNFS();
    int ok = 0, fail = 0;

    for (int a = 3; a < argc; ++a)
    {
        NFS_FILEDES des = nfs->file_open(argv[a], O_RDONLY);
        if (des < 0) { printf("  MISS  %s\n", argv[a]); ++fail; continue; }

        int size = nfs->file_size(des);
        char* buf = new char[size];
        int got = nfs->file_read(des, buf, size);
        nfs->file_close(des);

        std::string dest = std::string(argv[2]) + "/" + BaseName(argv[a]) + ".raw";
        FILE* f = fopen(dest.c_str(), "wb");
        if (f) { fwrite(buf, 1, got, f); fclose(f); ++ok; }
        else   { printf("  WRITEFAIL  %s\n", dest.c_str()); ++fail; }
        delete[] buf;
    }
    printf("dumped %d, failed %d\n", ok, fail);
    return 0;
}
