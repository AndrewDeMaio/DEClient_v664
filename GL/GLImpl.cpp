/*-----------------------------------------------------------------------------

    GLImpl.cpp

    Implementation of the GL graphics library functions previously provided
    by an external DLL. These are software-rendering routines that operate
    on locked DirectDraw surfaces via S_SURFACEINFO.

-----------------------------------------------------------------------------*/

#include <ddraw.h>

#include "GL_PCH.h"
#include "2D.h"
#include "BasicData.h"
#include "picinfo.h"
#include "TGA.H"
#include "GL_import.h"

//-----------------------------------------------------------------------------
// Internal state set by InitializeGL
//-----------------------------------------------------------------------------
static int s_bpp           = 16;
static int s_r_bits        = 5;
static int s_g_bits        = 6;
static int s_b_bits        = 5;
static int s_r_shift       = 11;
static int s_g_shift       = 5;
static int s_b_shift       = 0;
static int s_bytes_per_px  = 2;

//-----------------------------------------------------------------------------
// Helper: clip a software-rect to surface bounds
//-----------------------------------------------------------------------------
static bool ClipRect(const S_SURFACEINFO* info, int& x, int& y, int& w, int& h)
{
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > info->width)  w = info->width  - x;
    if (y + h > info->height) h = info->height - y;
    return (w > 0 && h > 0);
}

//=============================================================================
// Exported function implementations
//=============================================================================

void InitializeGL(int bpp, int r_bit, int g_bit, int b_bit)
{
    s_bpp          = bpp;
    s_r_bits       = r_bit;
    s_g_bits       = g_bit;
    s_b_bits       = b_bit;
    s_b_shift      = 0;
    s_g_shift      = b_bit;
    s_r_shift      = b_bit + g_bit;
    s_bytes_per_px = bpp / 8;
}

DWORD GL_RGB(DWORD r, DWORD g, DWORD b)
{
    return ((r >> (8 - s_r_bits)) << s_r_shift) |
           ((g >> (8 - s_g_bits)) << s_g_shift) |
           ((b >> (8 - s_b_bits)) << s_b_shift);
}

int Convert24RGBto16(int R, int G, int B)
{
    return (int)GL_RGB((DWORD)R, (DWORD)G, (DWORD)B);
}

//-----------------------------------------------------------------------------
// SetSurfaceInfo
//-----------------------------------------------------------------------------
void SetSurfaceInfo(S_SURFACEINFO* info, const DDSURFACEDESC2* ddsd)
{
    info->p_surface = ddsd->lpSurface;
    info->width     = (int)ddsd->dwWidth;
    info->height    = (int)ddsd->dwHeight;
    info->pitch     = (int)ddsd->lPitch;
    info->bpp       = (int)ddsd->ddpfPixelFormat.dwRGBBitCount;
}

void SetSurfaceInfo(S_SURFACEINFO* info, const DDSURFACEDESC* ddsd)
{
    info->p_surface = ddsd->lpSurface;
    info->width     = (int)ddsd->dwWidth;
    info->height    = (int)ddsd->dwHeight;
    info->pitch     = (int)ddsd->lPitch;
    info->bpp       = (int)ddsd->ddpfPixelFormat.dwRGBBitCount;
}

void SetSurfaceInfo(S_SURFACEINFO& info, void* p_surface, int w, int h, int pitch)
{
    info.p_surface = p_surface;
    info.width     = w;
    info.height    = h;
    info.pitch     = (pitch != 0) ? pitch : w * s_bytes_per_px;
    info.bpp       = s_bpp;
}

void SetRect(S_RECT& rect, int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

//-----------------------------------------------------------------------------
// FillRect  (Rect version)
//-----------------------------------------------------------------------------
void FillRect(S_SURFACEINFO* info, Rect* rect, int color)
{
    if (!info || !info->p_surface || !rect) return;

    int x = rect->x, y = rect->y, w = rect->w, h = rect->h;
    if (!ClipRect(info, x, y, w, h)) return;

    const int bpp = info->bpp / 8;
    BYTE* dst = (BYTE*)info->p_surface + y * info->pitch + x * bpp;

    for (int row = 0; row < h; ++row, dst += info->pitch)
    {
        if (bpp == 2)
        {
            WORD* p = (WORD*)dst;
            for (int col = 0; col < w; ++col) p[col] = (WORD)color;
        }
        else
        {
            DWORD* p = (DWORD*)dst;
            for (int col = 0; col < w; ++col) p[col] = (DWORD)color;
        }
    }
}

//-----------------------------------------------------------------------------
// filledRect  (S_RECT version — used as function pointer)
//-----------------------------------------------------------------------------
static void _filledRect(S_SURFACEINFO* info, S_RECT* rect, int color)
{
    if (!info || !info->p_surface || !rect) return;

    int x = rect->x, y = rect->y, w = rect->w, h = rect->h;
    if (!ClipRect(info, x, y, w, h)) return;

    const int bpp = info->bpp / 8;
    BYTE* dst = (BYTE*)info->p_surface + y * info->pitch + x * bpp;

    for (int row = 0; row < h; ++row, dst += info->pitch)
    {
        if (bpp == 2)
        {
            WORD* p = (WORD*)dst;
            for (int col = 0; col < w; ++col) p[col] = (WORD)color;
        }
        else
        {
            DWORD* p = (DWORD*)dst;
            for (int col = 0; col < w; ++col) p[col] = (DWORD)color;
        }
    }
}

//-----------------------------------------------------------------------------
// cls
//-----------------------------------------------------------------------------
static void _cls(S_SURFACEINFO* info, int color)
{
    if (!info || !info->p_surface) return;
    S_RECT r = { 0, 0, info->width, info->height };
    _filledRect(info, &r, color);
}

//-----------------------------------------------------------------------------
// putPixel / getPixel
//-----------------------------------------------------------------------------
static void _putPixel(S_SURFACEINFO* info, int x, int y, int color)
{
    if (!info || !info->p_surface) return;
    if (x < 0 || x >= info->width || y < 0 || y >= info->height) return;
    const int bpp = info->bpp / 8;
    BYTE* p = (BYTE*)info->p_surface + y * info->pitch + x * bpp;
    if (bpp == 2) *(WORD*)p  = (WORD)color;
    else          *(DWORD*)p = (DWORD)color;
}

static int _getPixel(S_SURFACEINFO* info, int x, int y)
{
    if (!info || !info->p_surface) return 0;
    if (x < 0 || x >= info->width || y < 0 || y >= info->height) return 0;
    const int bpp = info->bpp / 8;
    const BYTE* p = (const BYTE*)info->p_surface + y * info->pitch + x * bpp;
    return (bpp == 2) ? (int)*(const WORD*)p : (int)*(const DWORD*)p;
}

int getPixel16(S_SURFACEINFO* info, int x, int y)
{
    return _getPixel(info, x, y);
}

//-----------------------------------------------------------------------------
// vertline / horzline
//-----------------------------------------------------------------------------
static void _vertline(S_SURFACEINFO* info, int x, int y1, int x2, int y2, int color)
{
    // parameters match original: vertline(info, x, y_top, x, y_bottom, color)
    if (!info || !info->p_surface) return;
    if (x < 0 || x >= info->width) return;
    int yStart = (y1 < y2) ? y1 : y2;
    int yEnd   = (y1 < y2) ? y2 : y1;
    yStart = max(yStart, 0);
    yEnd   = min(yEnd,   info->height - 1);
    const int bpp = info->bpp / 8;
    for (int y = yStart; y <= yEnd; ++y)
        _putPixel(info, x, y, color);
}

static void _horzline(S_SURFACEINFO* info, int x1, int y, int x2, int y2, int color)
{
    if (!info || !info->p_surface) return;
    if (y < 0 || y >= info->height) return;
    int xStart = (x1 < x2) ? x1 : x2;
    int xEnd   = (x1 < x2) ? x2 : x1;
    xStart = max(xStart, 0);
    xEnd   = min(xEnd,   info->width - 1);
    const int bpp = info->bpp / 8;
    BYTE* row = (BYTE*)info->p_surface + y * info->pitch + xStart * bpp;
    const int len = xEnd - xStart + 1;
    if (bpp == 2)
    {
        WORD* p = (WORD*)row;
        for (int i = 0; i < len; ++i) p[i] = (WORD)color;
    }
    else
    {
        DWORD* p = (DWORD*)row;
        for (int i = 0; i < len; ++i) p[i] = (DWORD)color;
    }
}

//-----------------------------------------------------------------------------
// rectangle  (outline only)
//-----------------------------------------------------------------------------
void rectangle(S_SURFACEINFO* info, int lx, int ly, int rx, int ry, int color)
{
    _horzline(info, lx, ly, rx, ly, color);
    _horzline(info, lx, ry, rx, ry, color);
    _vertline(info, lx, ly, lx, ry, color);
    _vertline(info, rx, ly, rx, ry, color);
}

void rectangle(S_SURFACEINFO* info, Rect* p_rect, int color)
{
    if (!p_rect) return;
    int lx = p_rect->x;
    int ly = p_rect->y;
    int rx = p_rect->x + p_rect->w - 1;
    int ry = p_rect->y + p_rect->h - 1;
    rectangle(info, lx, ly, rx, ry, color);
}

//-----------------------------------------------------------------------------
// line  (Bresenham)
//-----------------------------------------------------------------------------
void line(S_SURFACEINFO* info, int x1, int y1, int x2, int y2, int color)
{
    if (!info || !info->p_surface) return;
    int dx = abs(x2 - x1), sx = (x1 < x2) ? 1 : -1;
    int dy = abs(y2 - y1), sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (true)
    {
        _putPixel(info, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}

//-----------------------------------------------------------------------------
// Bltz  (raw surface copy, no colorkey)
//-----------------------------------------------------------------------------
static void _Bltz(const S_SURFACEINFO* dest, const S_SURFACEINFO* src,
                  const S_RECT* dest_rect, const S_RECT* src_rect)
{
    if (!dest || !src || !dest->p_surface || !src->p_surface) return;
    if (!dest_rect || !src_rect) return;

    int w = min(dest_rect->w, src_rect->w);
    int h = min(dest_rect->h, src_rect->h);
    w = min(w, dest->width  - dest_rect->x);
    h = min(h, dest->height - dest_rect->y);
    w = min(w, src->width   - src_rect->x);
    h = min(h, src->height  - src_rect->y);
    if (w <= 0 || h <= 0) return;

    const int bpp = dest->bpp / 8;
    const BYTE* s = (const BYTE*)src->p_surface  + src_rect->y  * src->pitch  + src_rect->x  * bpp;
    BYTE*       d = (BYTE*)dest->p_surface        + dest_rect->y * dest->pitch + dest_rect->x * bpp;
    const int rowBytes = w * bpp;

    for (int row = 0; row < h; ++row, s += src->pitch, d += dest->pitch)
        memcpy(d, s, rowBytes);
}

//-----------------------------------------------------------------------------
// CkBltz  (copy with colorkey transparency)
//-----------------------------------------------------------------------------
static void _CkBltz(const S_SURFACEINFO* dest, const S_SURFACEINFO* src,
                    const S_RECT* dest_rect, const S_RECT* src_rect, const int colorkey)
{
    if (!dest || !src || !dest->p_surface || !src->p_surface) return;
    if (!dest_rect || !src_rect) return;

    int w = min(dest_rect->w, src_rect->w);
    int h = min(dest_rect->h, src_rect->h);
    w = min(w, dest->width  - dest_rect->x);
    h = min(h, dest->height - dest_rect->y);
    w = min(w, src->width   - src_rect->x);
    h = min(h, src->height  - src_rect->y);
    if (w <= 0 || h <= 0) return;

    const int bpp = dest->bpp / 8;
    const BYTE* s = (const BYTE*)src->p_surface  + src_rect->y  * src->pitch  + src_rect->x  * bpp;
    BYTE*       d = (BYTE*)dest->p_surface        + dest_rect->y * dest->pitch + dest_rect->x * bpp;

    for (int row = 0; row < h; ++row, s += src->pitch, d += dest->pitch)
    {
        if (bpp == 2)
        {
            const WORD* sp = (const WORD*)s;
            WORD*       dp = (WORD*)d;
            for (int col = 0; col < w; ++col)
                if (sp[col] != (WORD)colorkey) dp[col] = sp[col];
        }
        else
        {
            const DWORD* sp = (const DWORD*)s;
            DWORD*       dp = (DWORD*)d;
            for (int col = 0; col < w; ++col)
                if (sp[col] != (DWORD)colorkey) dp[col] = sp[col];
        }
    }
}

//-----------------------------------------------------------------------------
// TransparentBlt16
//-----------------------------------------------------------------------------
void TransparentBlt16(S_SURFACEINFO* dest, S_SURFACEINFO* src,
                      S_RECT* dest_rect, S_RECT* src_rect)
{
    // Colorkey is assumed to be 0 (black) for 16bpp transparent blit
    _CkBltz(dest, src, dest_rect, src_rect, 0);
}

//-----------------------------------------------------------------------------
// Get_ColorkeyColor
//-----------------------------------------------------------------------------
int Get_ColorkeyColor(S_PICINFO* picinfo)
{
    if (picinfo->p_data.empty()) return 0;

    // Colorkey is typically the top-left pixel
    if (picinfo->bpp == 16)
    {
        if (picinfo->p_data.size() < 2)
            return 0;

        // Read first 2 bytes safely
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(picinfo->p_data.data());
        uint16_t color = static_cast<uint16_t>(ptr[0] | (ptr[1] << 8));
        return static_cast<int>(color);
    }

    return 0;
}

int Get_ColorkeyColor(S_SURFACEINFO* info)
{
    if (!info || !info->p_surface) return 0;
    // Colorkey is typically the top-left pixel
    if (info->bpp == 16)
        return (int)*(WORD*)info->p_surface;
    return 0;
}

//-----------------------------------------------------------------------------
// TGA helpers
// Note: TGA loading is handled by SpriteLib (Tga class). These are stubs
// to satisfy the GL_import.h interface; callers should use Tga directly.
//-----------------------------------------------------------------------------
bool TestTga(const char* filename)
{
    // Open file in binary mode
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        return false;

    // Read TGA header
    S_TGAHEAD head{};
    file.read(reinterpret_cast<char*>(&head), sizeof(head));
    if (!file)
        return false;

    // Optional: skip ID field if present
    if (head.idsize > 0)
        file.seekg(head.idsize, std::ios::cur);

    // Check that this is the “classic” 16-bit uncompressed TGA
    if (head.idsize != 0 ||
        head.colormaptype != 0 ||
        head.colormapbits != 0 ||
        head.xstart != 0 ||
        head.ystart != 0)
    {
        return false;
    }

    return true;
}

bool GetTgaPicInfo(const char* sz_filename, S_PICINFO& picinfo)
{
    std::ifstream file(sz_filename, std::ios::binary);
    if (!file)
        return false;

    S_TGAHEAD head{};
    file.read(reinterpret_cast<char*>(&head), sizeof(head));
    if (!file)
        return false;

    if (head.imagetype != 2) 
        return false;

    picinfo.width = head.width;
    picinfo.height = head.height;
    picinfo.bpp = head.bpp;
    picinfo.filename = sz_filename;

    size_t pixelCount = head.width * head.height;
    size_t bytesPerPixel = head.bpp / 8;
    picinfo.p_data.resize(pixelCount * bytesPerPixel);

    // Skip ID field if present
    if (head.idsize > 0)
        file.seekg(head.idsize, std::ios::cur);

    file.read(reinterpret_cast<char*>(picinfo.p_data.data()), picinfo.p_data.size());
    if (!file) return false;

    return true;
}

//=============================================================================
// Function pointer definitions (set to the static implementations above)
//=============================================================================
void (*filledRect)(S_SURFACEINFO*, S_RECT*, int)                                     = _filledRect;
void (*cls)(S_SURFACEINFO*, int)                                                     = _cls;
void (*putPixel)(S_SURFACEINFO*, int, int, int)                                      = _putPixel;
int  (*getPixel)(S_SURFACEINFO*, int, int)                                           = _getPixel;
void (*vertline)(S_SURFACEINFO*, int, int, int, int, int)                            = _vertline;
void (*horzline)(S_SURFACEINFO*, int, int, int, int, int)                            = _horzline;
void (*Bltz)(const S_SURFACEINFO*, const S_SURFACEINFO*, const S_RECT*, const S_RECT*)                          = _Bltz;
void (*CkBltz)(const S_SURFACEINFO*, const S_SURFACEINFO*, const S_RECT*, const S_RECT*, const int)             = _CkBltz;
