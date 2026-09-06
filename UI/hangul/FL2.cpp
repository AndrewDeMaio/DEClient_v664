// FL2.cpp

#include "client_PCH.h"
#include "FL2.h"
#include "VS_UI_Base.h"
#include "CD3D9Present.h"
#include "CDirectDraw.h"

//-----------------------------------------------------------------------------
// Utilities for IO.
//-----------------------------------------------------------------------------

//
// FL2������ DC�� ����ϹǷ� surface�� �ʿ��ϴ�. �̰��� �Ϲ������� ����� 
// surface�̰�����, offscreen surface�ε� �� �� �ְڴ�.
//
// Unicorn edit line widget���� FL2�� ����ϹǷ� �װ����� �� surface�� ������
// ���̴�.
//
LPDIRECTDRAWSURFACE7	gpC_fl2_surface = NULL;
HDC gh_FL2_DC = NULL;

// ---------------------------------------------------------------------------
// Fallback GDI DC for 16-bit DirectDraw surfaces
//
// IDirectDrawSurface7::GetDC fails on 16-bit surfaces on modern Windows.
// As a workaround we keep a 32-bit GDI DIBSection the same size as
// gpC_fl2_surface.  Text is drawn there; on ReleaseDC the non-colorkey pixels
// are colour-converted and written into the 16-bit DirectDraw surface.
// ---------------------------------------------------------------------------
static HDC     s_fl2_fb_dc      = NULL;  // memory DC backed by the DIBSection
static HBITMAP s_fl2_fb_bmp     = NULL;  // 32-bit DIBSection HBITMAP
static HBITMAP s_fl2_fb_bmp_old = NULL;  // saved HBITMAP (for SelectObject cleanup)
static DWORD*  s_fl2_fb_bits    = NULL;  // raw pixel data pointer
static int     s_fl2_fb_w       = 0;
static int     s_fl2_fb_h       = 0;
static bool    s_fl2_fb_is565   = true;  // pixel format of gpC_fl2_surface
static bool    s_fl2_fb_active  = false; // true while the fallback DC is in use
static bool    s_fl2_fb_dirty   = false; // true once text has actually been drawn
static HDC     s_fl2_bare_dc    = NULL;  // last-resort measure-only DC
static bool    s_fl2_bare_active = false;// true when bare DC is in use

// ---------------------------------------------------------------------------
// Dirty-rectangle tracking
//
// The DIBSection used to be wiped in full on every acquire and scanned in
// full on every release - 921,600 pixels each way at 1280x720, no matter how
// few characters were involved. Since almost nothing in the UI brackets its
// text calls, most windows paid that twice per string, and the measurement
// helpers (g_GetStringWidth and friends, which draw nothing at all) paid the
// clear as well. That is what made every text-drawing window get slower as
// more text appeared on screen.
//
// Now: nothing is cleared on acquire. The first actual draw clears whatever
// the previous acquire left behind, and release copies back only the regions
// touched. A measure-only cycle does no pixel work whatsoever.
//
// Several small rects rather than one bounding box: UI text sits in opposite
// corners of the screen, so a single union would cover nearly everything and
// give most of the saving straight back.
// ---------------------------------------------------------------------------
#define FL2_MAX_DIRTY 12

struct FL2_DIRTYRECT { int x0, y0, x1, y1; };

static FL2_DIRTYRECT s_fl2_cur[FL2_MAX_DIRTY];	// drawn since this acquire
static int           s_fl2_curN  = 0;
static FL2_DIRTYRECT s_fl2_prev[FL2_MAX_DIRTY];	// still holding glyphs, needs clearing
static int           s_fl2_prevN = 0;

// false = persistent DIBSection DC (fast). true = per-acquire DirectDraw DC.
bool g_bFL2UseSurfaceDC = false;

// Colorkey: pixels equal to this value in the DIBSection are skipped (transparent)
// during copy-back.  Deliberately unusual to avoid colliding with real colours.
static const DWORD FL2_FB_COLORKEY = 0x00010101u;

// ---------------------------------------------------------------------------
// DBCS companion font
//
// The UI face (Georgia) carries no Hangul glyphs, and the GDI font mapper
// refuses a HANGUL_CHARSET request for such a face - it silently substitutes
// a different font entirely. So UI fonts are created with ANSI_CHARSET, and
// any string containing DBCS bytes is drawn with a same-size Malgun Gothic
// companion font instead, created on demand and cached by height/weight.
// (Assumes high-byte strings are CP949 Korean, which is what the game data
// contains; extended-Latin bytes would be misread either way.)
// ---------------------------------------------------------------------------
#define FL2_MAX_COMPANION 16

struct FL2_COMPANION { LONG height; LONG weight; HFONT hfont; };
static FL2_COMPANION s_fl2_companion[FL2_MAX_COMPANION];
static int           s_fl2_companionN = 0;

static bool s_FL2_HasDbcs(const char* s, int len)
{
	for (int i = 0; i < len; i++)
		if ((unsigned char)s[i] >= 0x80)
			return true;
	return false;
}

static HFONT s_FL2_PickFont(HFONT hRequested, const char* s, int len)
{
	if (hRequested == NULL || s == NULL || len <= 0 || !s_FL2_HasDbcs(s, len))
		return hRequested;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	if (GetObject(hRequested, sizeof(lf), &lf) == 0)
		return hRequested;

	for (int i = 0; i < s_fl2_companionN; i++)
		if (s_fl2_companion[i].height == lf.lfHeight && s_fl2_companion[i].weight == lf.lfWeight)
			return s_fl2_companion[i].hfont;

	lf.lfCharSet = HANGUL_CHARSET;
	lf.lfQuality = NONANTIALIASED_QUALITY;
	strcpy_s(lf.lfFaceName, "Malgun Gothic");

	HFONT hNew = CreateFontIndirect(&lf);
	if (hNew == NULL)
		return hRequested;

	if (s_fl2_companionN < FL2_MAX_COMPANION)
	{
		s_fl2_companion[s_fl2_companionN].height = lf.lfHeight;
		s_fl2_companion[s_fl2_companionN].weight = lf.lfWeight;
		s_fl2_companion[s_fl2_companionN].hfont  = hNew;
		s_fl2_companionN++;
	}
	else
	{
		// Cache full (should not happen with the game's handful of sizes):
		// don't leak a font per call, just draw with the requested face.
		DeleteObject(hNew);
		hNew = hRequested;
	}

	return hNew;
}

// Add a rect to a set, merging into an existing one when they touch. When the
// set is full everything collapses into slot 0 - correctness over precision.
static void s_FL2_AddRect(FL2_DIRTYRECT* pSet, int& n, int l, int t, int r, int bm)
{
	if (r <= l || bm <= t)
		return;

	for (int i = 0; i < n; i++)
	{
		FL2_DIRTYRECT& e = pSet[i];

		// Overlapping or adjacent - absorb rather than add another entry.
		if (l <= e.x1 && e.x0 <= r && t <= e.y1 && e.y0 <= bm)
		{
			if (l  < e.x0) e.x0 = l;
			if (t  < e.y0) e.y0 = t;
			if (r  > e.x1) e.x1 = r;
			if (bm > e.y1) e.y1 = bm;
			return;
		}
	}

	if (n < FL2_MAX_DIRTY)
	{
		pSet[n].x0 = l;  pSet[n].y0 = t;
		pSet[n].x1 = r;  pSet[n].y1 = bm;
		n++;
		return;
	}

	// Full: fold everything into one rect so nothing is ever missed.
	for (int i = 1; i < n; i++)
	{
		if (pSet[i].x0 < pSet[0].x0) pSet[0].x0 = pSet[i].x0;
		if (pSet[i].y0 < pSet[0].y0) pSet[0].y0 = pSet[i].y0;
		if (pSet[i].x1 > pSet[0].x1) pSet[0].x1 = pSet[i].x1;
		if (pSet[i].y1 > pSet[0].y1) pSet[0].y1 = pSet[i].y1;
	}

	if (l  < pSet[0].x0) pSet[0].x0 = l;
	if (t  < pSet[0].y0) pSet[0].y0 = t;
	if (r  > pSet[0].x1) pSet[0].x1 = r;
	if (bm > pSet[0].y1) pSet[0].y1 = bm;
	n = 1;
}

// Record a drawn region, padded and clamped.
static void s_FL2_Dirty(int l, int t, int r, int bm)
{
	// Glyphs can overhang their reported extent (italics, antialiasing).
	l -= 2; t -= 2; r += 3; bm += 3;

	if (l < 0) l = 0;
	if (t < 0) t = 0;
	if (r  > s_fl2_fb_w) r  = s_fl2_fb_w;
	if (bm > s_fl2_fb_h) bm = s_fl2_fb_h;

	s_FL2_AddRect(s_fl2_cur, s_fl2_curN, l, t, r, bm);
}

// For callers that draw straight into the DC and cannot tell us where.
static void s_FL2_DirtyAll()
{
	s_fl2_curN = 0;
	s_FL2_AddRect(s_fl2_cur, s_fl2_curN, 0, 0, s_fl2_fb_w, s_fl2_fb_h);
}

// Bounds of a TextOut on the given DC, honouring its current alignment.
// Shared by the lo-res dirty tracker and the native-res overlay mirror.
static bool s_FL2_TextOutBounds(HDC hdc, int x, int y, const char* psz, int len,
                                int* pl, int* pt, int* pr, int* pb)
{
	SIZE sz = { 0, 0 };

	if (psz == NULL || len <= 0 || !GetTextExtentPoint32(hdc, psz, len, &sz))
		return false;

	const UINT align = GetTextAlign(hdc);
	const UINT h     = align & (TA_LEFT | TA_RIGHT | TA_CENTER);
	const UINT v     = align & (TA_TOP | TA_BOTTOM | TA_BASELINE);

	int l;
	if      (h == TA_CENTER) l = x - sz.cx / 2;
	else if (h == TA_RIGHT)  l = x - sz.cx;
	else                     l = x;

	if (v == TA_BASELINE)
	{
		// y is the baseline: ascent above, descent below.
		*pl = l; *pt = y - sz.cy; *pr = l + sz.cx; *pb = y + sz.cy / 2;
		return true;
	}

	const int t = (v == TA_BOTTOM) ? (y - sz.cy) : y;

	*pl = l; *pt = t; *pr = l + sz.cx; *pb = t + sz.cy;
	return true;
}

// Bounds of a TextOut, honouring the DC's current alignment.
static void s_FL2_DirtyTextOut(HDC hdc, int x, int y, const char* psz, int len)
{
	int l, t, r, b;

	if (!s_FL2_TextOutBounds(hdc, x, y, psz, len, &l, &t, &r, &b))
	{
		s_FL2_DirtyAll();	// cannot bound it - stay correct
		return;
	}

	s_FL2_Dirty(l, t, r, b);
}

// Clear what the previous acquire drew. Called immediately before the first
// draw of an acquisition, so a measure-only cycle never reaches it.
static void s_FL2_EnsureCleared()
{
	if (s_fl2_prevN == 0 || s_fl2_fb_bits == NULL)
		return;

	for (int i = 0; i < s_fl2_prevN; i++)
	{
		const FL2_DIRTYRECT& e = s_fl2_prev[i];

		for (int y = e.y0; y < e.y1; y++)
		{
			DWORD* pRow = s_fl2_fb_bits + (size_t)y * s_fl2_fb_w;

			for (int x = e.x0; x < e.x1; x++)
				pRow[x] = FL2_FB_COLORKEY;
		}
	}

	s_fl2_prevN = 0;
}

// ---------------------------------------------------------------------------
// Native-resolution text overlay
//
// The game surface is upscaled 1.5x by the GPU presenter, which turns 1px
// font strokes into randomly-1-or-2px lumps. Every TextOut that lands in the
// lo-res DIB is therefore mirrored - at MulDiv-scaled coordinates, with a
// scaled twin of the current font - into a second, destination-sized DIB.
// g_FL2_OverlayFlush() (called from CDirectDraw::Flip via callback) verifies
// each mirrored region is still on the surface (a mismatching checksum means
// later UI painted over the text - overlay falls back to the lo-res pixels
// there), then hands the dirty regions to CD3D9Present::UpdateOverlay, which
// composites them 1:1 AFTER the upscale. The lo-res path is untouched; the
// overlay is purely additive and expires every frame.
// ---------------------------------------------------------------------------
#define FL2_OV_MAX_REGION 256
#define FL2_OV_MAX_UPLOAD 64
#define FL2_OV_MAX_SCALED_FONT 32
#define FL2_OV_MAX_TEXTLEN 512

#define FL2_OV_MAX_SUB 8

// Per-region occlusion baselines are kept per COLUMN slice (~24 lo px),
// so text only loses its crisp copy where something actually painted
// over it - a tooltip overlapped at one edge keeps the rest readable,
// clipped like the lo-res original would have been.
// kind 0 = text (redrawable from the pooled string + stored attributes),
// kind 1 = caret fill. failMask marks columns suppressed at flush.
struct FL2_OVREGION
{
	FL2_DIRTYRECT lo, hi;
	DWORD    sub[FL2_OV_MAX_SUB];
	int      nSub;
	BYTE     failMask;
	BYTE     kind;
	int      textOfs;      // -1 = not redrawable
	int      textLen;
	HFONT    fontLo;
	COLORREF textColor;
	COLORREF bkColor;
	int      bkMode;
	UINT     align;
	int      hx, hy;       // draw anchor (overlay coords)
	int      cw, ch;       // caret fill size
	DWORD    fill;         // caret fill pixel
};

#define FL2_OV_POOL 32768
#define FL2_OV_MAX_CLEARED 128
struct FL2_SCALEDFONT { HFONT base; HFONT scaled; };

static bool    s_fl2_ov_userEnabled = true;    // Resolution.inf "TextOverlay"
static bool    s_fl2_ov_on          = false;   // usable this frame
static bool    s_fl2_ov_began       = false;   // per-frame init ran
static bool    s_fl2_ov_geomFailed  = false;   // DIB creation failed for this geometry
static HDC     s_fl2_ov_dc          = NULL;
static HBITMAP s_fl2_ov_bmp         = NULL;
static HBITMAP s_fl2_ov_bmp_old     = NULL;
static DWORD*  s_fl2_ov_bits        = NULL;
static int     s_fl2_ov_w           = 0;       // destination (screen) size
static int     s_fl2_ov_h           = 0;
static int     s_fl2_ov_srcW        = 0;       // logical size it scales from
static int     s_fl2_ov_srcH        = 0;
static LPDIRECTDRAWSURFACE7 s_fl2_ov_boundSurface = NULL;

static FL2_OVREGION  s_fl2_ov_frame[FL2_OV_MAX_REGION];   // this frame's text regions
static int           s_fl2_ov_frameN   = 0;
static int           s_fl2_ov_checkedN = 0;               // [0,checkedN) have valid sums
static FL2_DIRTYRECT s_fl2_ov_prevHi[FL2_OV_MAX_REGION];  // last frame's glyphs, to erase
static int           s_fl2_ov_prevHiN  = 0;
static bool          s_fl2_ov_overflow = false;           // whole frame falls back lo-res

static FL2_SCALEDFONT s_fl2_ov_font[FL2_OV_MAX_SCALED_FONT];
static int            s_fl2_ov_fontN = 0;

// Outline/shadow passes re-draw the same string offset by 1-2 lo px.
// Scaled naively those offsets become 2-3 screen px and smear the AA
// glyphs; when the pattern is detected the offsets stay 1:1 instead.
struct FL2_OVLASTDRAW { DWORD hash; int len; HFONT font; int x, y, hx, hy; bool valid; };
static FL2_OVLASTDRAW s_fl2_ov_last = { 0, 0, NULL, 0, 0, 0, 0, false };

// Per-frame string pool backing the redraw parameters.
static char s_fl2_ov_poolBuf[FL2_OV_POOL];
static int  s_fl2_ov_poolN = 0;

// Frames during which the overlay stands down entirely (splash/CI fade
// paints over every text region each tick; lo-res text blends under it
// like the original client).
static int  s_fl2_ov_skipFrames = 0;

// Splash-fade sync: instead of standing down (which swapped to lo-res text
// and read as a font change), the crisp overlay fades WITH the splash.
// While active, occlusion verify is skipped - the splash legitimately
// paints over every region and the alpha does the hiding.
static int  s_fl2_ov_fadeAlpha  = 255;
static int  s_fl2_ov_fadeFrames = 0;

// ---------------------------------------------------------------------------
// TEMPORARY overlay diagnostics: aggregated counters, one line every ~2s
// appended to fl2_ov.log. Remove once the in-game text path is understood.
// ---------------------------------------------------------------------------
#define FL2_OV_DIAG 1
#if FL2_OV_DIAG
struct FL2_OVDIAG
{
	// mirror outcomes
	int mirOK, mirBeginFail, mirOverflow, mirSurfSwap, mirUpdateCP, mirFontFail, mirBoundsFail;
	// begin fail reasons (last one wins per frame)
	int begUser, begNoFb, begNoSurf, begSkip, begGeomInactive, begGeomMismatch, begNoUpscale, begDibFail;
	int begOK;
	// checksum bookkeeping
	int pendLockFail, blitLockFail;
	// flush outcomes
	int flushInactive, flushOverflow, flushFrames;
	int supNoBaseline, supChecksum, regionsTotal;
	int lastFrameN, lastCheckedN;
	int fbW, fbH, ovW, ovH;
};
static FL2_OVDIAG s_diag = {};
static DWORD s_diagLastDump = 0;

static void s_FL2_DiagDump()
{
	const DWORD now = GetTickCount();
	if (s_diagLastDump != 0 && now - s_diagLastDump < 2000)
		return;
	s_diagLastDump = now;

	FILE* f = fopen("fl2_ov.log", "a");
	if (f == NULL)
		return;
	fprintf(f,
		"mir ok=%d beg=%d ovf=%d swap=%d cp=%d font=%d bnd=%d | "
		"begin ok=%d user=%d nofb=%d nosurf=%d skip=%d inact=%d geom=%d noup=%d dib=%d | "
		"lockfail pend=%d blit=%d | "
		"flush inact=%d ovf=%d n=%d | sup nobase=%d sum=%d of=%d | "
		"last frameN=%d checkedN=%d | fb=%dx%d ov=%dx%d\n",
		s_diag.mirOK, s_diag.mirBeginFail, s_diag.mirOverflow, s_diag.mirSurfSwap,
		s_diag.mirUpdateCP, s_diag.mirFontFail, s_diag.mirBoundsFail,
		s_diag.begOK, s_diag.begUser, s_diag.begNoFb, s_diag.begNoSurf, s_diag.begSkip,
		s_diag.begGeomInactive, s_diag.begGeomMismatch, s_diag.begNoUpscale, s_diag.begDibFail,
		s_diag.pendLockFail, s_diag.blitLockFail,
		s_diag.flushInactive, s_diag.flushOverflow, s_diag.flushFrames,
		s_diag.supNoBaseline, s_diag.supChecksum, s_diag.regionsTotal,
		s_diag.lastFrameN, s_diag.lastCheckedN,
		s_diag.fbW, s_diag.fbH, s_diag.ovW, s_diag.ovH);
	fclose(f);

	FL2_OVDIAG zero = {};
	s_diag = zero;
	s_diagLastDump = now;
}
#define FL2_OV_DIAG_INC(field) (s_diag.field++)
#else
#define FL2_OV_DIAG_INC(field) ((void)0)
#endif

// Fill one overlay-DIB rect back to the colorkey (transparent).
static void s_FL2_OvClearRect(const FL2_DIRTYRECT& e)
{
	if (s_fl2_ov_bits == NULL)
		return;

	for (int y = e.y0; y < e.y1; y++)
	{
		DWORD* pRow = s_fl2_ov_bits + (size_t)y * s_fl2_ov_w;
		for (int x = e.x0; x < e.x1; x++)
			pRow[x] = FL2_FB_COLORKEY;
	}
}

// Order-dependent checksum of the 16-bit surface pixels under a lo-res rect.
static DWORD s_FL2_SumRegion(const WORD* pBase, int nStride, const FL2_DIRTYRECT& e)
{
	DWORD h = 2166136261u;

	for (int y = e.y0; y < e.y1; y++)
	{
		const WORD* pRow = pBase + (size_t)y * nStride;
		for (int x = e.x0; x < e.x1; x++)
			h = h * 131u + pRow[x];
	}

	return h;
}

static void s_FL2_SumRegionCols(const WORD* pBase, int nStride, FL2_OVREGION& e)
{
	const int w = e.lo.x1 - e.lo.x0;
	int n = w / 24;
	if (n < 1) n = 1;
	if (n > FL2_OV_MAX_SUB) n = FL2_OV_MAX_SUB;
	e.nSub = n;

	for (int i = 0; i < n; i++)
	{
		FL2_DIRTYRECT c = e.lo;
		c.x0 = e.lo.x0 + w * i / n;
		c.x1 = e.lo.x0 + w * (i + 1) / n;
		e.sub[i] = s_FL2_SumRegion(pBase, nStride, c);
	}
}

static void s_FL2_OvColHiRect(const FL2_OVREGION& e, int j, FL2_DIRTYRECT* p)
{
	const int hiW = e.hi.x1 - e.hi.x0;
	*p = e.hi;
	p->x0 = e.hi.x0 + hiW * j / e.nSub;
	p->x1 = e.hi.x0 + hiW * (j + 1) / e.nSub;
}

static void s_FL2_OverlayRelease()
{
	for (int i = 0; i < s_fl2_ov_fontN; i++)
		if (s_fl2_ov_font[i].scaled != NULL)
			DeleteObject(s_fl2_ov_font[i].scaled);
	s_fl2_ov_fontN = 0;

	if (s_fl2_ov_dc != NULL)
	{
		SelectObject(s_fl2_ov_dc, s_fl2_ov_bmp_old);
		DeleteDC(s_fl2_ov_dc);
		s_fl2_ov_dc = NULL;
	}
	if (s_fl2_ov_bmp != NULL)
	{
		DeleteObject(s_fl2_ov_bmp);
		s_fl2_ov_bmp = NULL;
	}
	s_fl2_ov_bmp_old = NULL;
	s_fl2_ov_bits    = NULL;
	s_fl2_ov_w = s_fl2_ov_h = 0;
	s_fl2_ov_srcW = s_fl2_ov_srcH = 0;
	s_fl2_ov_frameN = s_fl2_ov_checkedN = s_fl2_ov_prevHiN = 0;
	s_fl2_ov_poolN = 0;
	s_fl2_ov_overflow = false;
	s_fl2_ov_on = false;
	s_fl2_ov_began = false;
	s_fl2_ov_geomFailed = false;
	s_fl2_ov_boundSurface = NULL;
}

// Per-frame lazy init: decide whether the overlay runs this frame, (re)build
// the destination-sized DIB on geometry changes, and clear last frame's
// glyphs out of it (the rect list itself survives until flush, which needs
// it to erase the same regions from the GPU texture).
static bool s_FL2_OverlayBegin()
{
	if (s_fl2_ov_began)
		return s_fl2_ov_on;

	s_fl2_ov_began = true;
	s_fl2_ov_on    = false;

	if (!s_fl2_ov_userEnabled) { FL2_OV_DIAG_INC(begUser); return false; }
	if (s_fl2_fb_bits == NULL) { FL2_OV_DIAG_INC(begNoFb); return false; }
	if (gpC_fl2_surface == NULL) { FL2_OV_DIAG_INC(begNoSurf); return false; }
	if (s_fl2_ov_skipFrames > 0) { FL2_OV_DIAG_INC(begSkip); return false; }

	D3D9PresentGeometry g;
	if (!CD3D9Present::GetPresentGeometry(&g) || !g.bActive)
	{
		FL2_OV_DIAG_INC(begGeomInactive);
		return false;
	}
	if (g.srcW != s_fl2_fb_w || g.srcH != s_fl2_fb_h)
	{
		FL2_OV_DIAG_INC(begGeomMismatch);
#if FL2_OV_DIAG
		s_diag.fbW = s_fl2_fb_w; s_diag.fbH = s_fl2_fb_h;
		s_diag.ovW = g.srcW;     s_diag.ovH = g.srcH;   // presenter src, for the log
#endif
		return false;   // presenter geometry doesn't match the text surface
	}
	if (g.dstW <= g.srcW || g.dstH <= g.srcH)
	{
		FL2_OV_DIAG_INC(begNoUpscale);
		return false;   // 1:1 (window mode) or downscale: lo-res text is already right
	}

	if (s_fl2_ov_dc == NULL || g.dstW != s_fl2_ov_w || g.dstH != s_fl2_ov_h ||
	    g.srcW != s_fl2_ov_srcW || g.srcH != s_fl2_ov_srcH)
	{
		if (s_fl2_ov_geomFailed)
			return false;

		s_FL2_OverlayRelease();
		s_fl2_ov_began = true;   // Release cleared it; we are still inside Begin

		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth       =  g.dstW;
		bmi.bmiHeader.biHeight      = -g.dstH;   // top-down
		bmi.bmiHeader.biPlanes      = 1;
		bmi.bmiHeader.biBitCount    = 32;
		bmi.bmiHeader.biCompression = BI_RGB;

		HDC screen_dc = GetDC(NULL);
		s_fl2_ov_bmp  = CreateDIBSection(screen_dc, &bmi, DIB_RGB_COLORS,
		                                 (void**)&s_fl2_ov_bits, NULL, 0);
		s_fl2_ov_dc   = CreateCompatibleDC(screen_dc);
		ReleaseDC(NULL, screen_dc);

		if (!s_fl2_ov_bmp || !s_fl2_ov_dc || !s_fl2_ov_bits)
		{
			if (s_fl2_ov_dc)  { DeleteDC(s_fl2_ov_dc);      s_fl2_ov_dc  = NULL; }
			if (s_fl2_ov_bmp) { DeleteObject(s_fl2_ov_bmp); s_fl2_ov_bmp = NULL; }
			s_fl2_ov_bits = NULL;
			s_fl2_ov_geomFailed = true;   // don't retry every frame
			FL2_OV_DIAG_INC(begDibFail);
			return false;
		}

		s_fl2_ov_bmp_old = (HBITMAP)SelectObject(s_fl2_ov_dc, s_fl2_ov_bmp);
		s_fl2_ov_w    = g.dstW;
		s_fl2_ov_h    = g.dstH;
		s_fl2_ov_srcW = g.srcW;
		s_fl2_ov_srcH = g.srcH;

		FL2_DIRTYRECT all = { 0, 0, s_fl2_ov_w, s_fl2_ov_h };
		s_FL2_OvClearRect(all);
	}
	else
	{
		// Clear last frame's glyphs; the rect list stays for flush.
		for (int i = 0; i < s_fl2_ov_prevHiN; i++)
			s_FL2_OvClearRect(s_fl2_ov_prevHi[i]);
	}

	s_fl2_ov_last.valid = false;
	s_fl2_ov_boundSurface = gpC_fl2_surface;
	s_fl2_ov_on = true;
#if FL2_OV_DIAG
	s_diag.begOK++;
	s_diag.fbW = s_fl2_fb_w; s_diag.fbH = s_fl2_fb_h;
	s_diag.ovW = s_fl2_ov_w; s_diag.ovH = s_fl2_ov_h;
#endif
	return true;
}

// Scaled twin of a lo-res font, cached by the exact HFONT handle (companion
// fonts are cached HFONTs themselves, so the DBCS path is covered for free).
static HFONT s_FL2_OverlayFont(HFONT hBase)
{
	if (hBase == NULL)
		return NULL;

	for (int i = 0; i < s_fl2_ov_fontN; i++)
		if (s_fl2_ov_font[i].base == hBase)
			return s_fl2_ov_font[i].scaled;

	if (s_fl2_ov_fontN >= FL2_OV_MAX_SCALED_FONT)
		return NULL;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	if (GetObject(hBase, sizeof(lf), &lf) == 0)
		return NULL;

	// Scale the height, then take it down a notch: at native resolution
	// slightly finer text reads better and can never overflow the lo-res
	// layout boxes.
	int nScaledH = MulDiv(lf.lfHeight, s_fl2_ov_h, s_fl2_ov_srcH);
	if (nScaledH > 14)
		nScaledH -= 2;
	else if (nScaledH > 8)
		nScaledH -= 1;
	lf.lfHeight = nScaledH;
	lf.lfWidth  = 0;   // natural aspect of the overlay face

	// The lo-res face is a pixel font - scaled up it stays blocky. The
	// overlay renders at true screen resolution, so use smooth outline
	// faces with grayscale AA (edges blend toward the near-black colorkey
	// and read as a soft outline; never ClearType, which would fringe).
	if (lf.lfCharSet == HANGUL_CHARSET)
		strcpy_s(lf.lfFaceName, "Malgun Gothic");
	else
		strcpy_s(lf.lfFaceName, "Segoe UI");
	lf.lfQuality = ANTIALIASED_QUALITY;

	HFONT hNew = CreateFontIndirect(&lf);
	if (hNew == NULL)
		return NULL;

	s_fl2_ov_font[s_fl2_ov_fontN].base   = hBase;
	s_fl2_ov_font[s_fl2_ov_fontN].scaled = hNew;
	s_fl2_ov_fontN++;
	return hNew;
}

// Mirror one TextOut into the overlay. Returns true when the crisp copy
// was drawn AND tracked - the caller then skips the lo-res twin entirely
// (drawing both leaves the upscaled lo-res glyphs peeking out around the
// crisp ones as a double image). Any decline returns false and the
// caller renders lo-res exactly as before.
static bool s_FL2_OverlayMirrorTextOut(HDC hdcLo, int x, int y, const char* psz, int len)
{
	// Nothing to draw: decline WITHOUT tripping the whole-frame overflow.
	// (Empty strings do get printed every frame - the chat whisper line for
	// one - and the bounds helper rejects len<=0, so before this guard a
	// single empty print discarded the entire frame's crisp text.)
	if (psz == NULL || len <= 0)
		return false;

	if (!s_FL2_OverlayBegin() || s_fl2_ov_overflow)
	{
		if (s_fl2_ov_overflow) { FL2_OV_DIAG_INC(mirOverflow); }
		else                   { FL2_OV_DIAG_INC(mirBeginFail); }
		return false;
	}
	if (gpC_fl2_surface != s_fl2_ov_boundSurface)
	{
		FL2_OV_DIAG_INC(mirSurfSwap);
		return false;   // mid-frame surface swap (debug paths): leave those draws lo-res
	}

	if (s_fl2_ov_frameN >= FL2_OV_MAX_REGION)
	{
		s_fl2_ov_overflow = true;
		FL2_OV_DIAG_INC(mirOverflow);
		return false;
	}

	const UINT align = GetTextAlign(hdcLo);
	if (align & TA_UPDATECP)
	{
		FL2_OV_DIAG_INC(mirUpdateCP);
		return false;   // current-position mode would desync the two DCs
	}

	HFONT hLo = (HFONT)GetCurrentObject(hdcLo, OBJ_FONT);
	HFONT hHi = s_FL2_OverlayFont(hLo);
	if (hHi == NULL)
	{
		FL2_OV_DIAG_INC(mirFontFail);
		return false;
	}

	SelectObject(s_fl2_ov_dc, hHi);
	SetTextAlign(s_fl2_ov_dc, align);
	SetBkMode(s_fl2_ov_dc, GetBkMode(hdcLo));
	SetBkColor(s_fl2_ov_dc, GetBkColor(hdcLo));
	SetTextColor(s_fl2_ov_dc, GetTextColor(hdcLo));

	// Natural rendering: glyphs use the overlay font's own advances. Layout
	// agreement comes from the measurement side instead - g_GetStringWidth
	// returns overlay-derived widths - so no per-character grid fitting
	// (letter-spacing) or total-width justification (word gaps) is needed.
	DWORD dwHash = 5381;
	for (int i = 0; i < len; i++)
		dwHash = dwHash * 33u + (unsigned char)psz[i];

	int hx, hy;
	if (s_fl2_ov_last.valid && s_fl2_ov_last.hash == dwHash &&
	    s_fl2_ov_last.len == len && s_fl2_ov_last.font == hLo &&
	    x - s_fl2_ov_last.x >= -2 && x - s_fl2_ov_last.x <= 2 &&
	    y - s_fl2_ov_last.y >= -2 && y - s_fl2_ov_last.y <= 2)
	{
		// Outline/shadow pass: keep the tiny offset 1:1.
		hx = s_fl2_ov_last.hx + (x - s_fl2_ov_last.x);
		hy = s_fl2_ov_last.hy + (y - s_fl2_ov_last.y);
	}
	else
	{
		hx = MulDiv(x, s_fl2_ov_w, s_fl2_ov_srcW);
		hy = MulDiv(y, s_fl2_ov_h, s_fl2_ov_srcH);
		s_fl2_ov_last.hash = dwHash;
		s_fl2_ov_last.len  = len;
		s_fl2_ov_last.font = hLo;
		s_fl2_ov_last.x = x;   s_fl2_ov_last.y = y;
		s_fl2_ov_last.hx = hx; s_fl2_ov_last.hy = hy;
		s_fl2_ov_last.valid = true;
	}

	TextOut(s_fl2_ov_dc, hx, hy, psz, len);

	int hl, ht, hr, hb;
	if (!s_FL2_TextOutBounds(s_fl2_ov_dc, hx, hy, psz, len, &hl, &ht, &hr, &hb))
	{
		// Hi-res pixels are down but can't be tracked: degrade the frame.
		s_fl2_ov_overflow = true;
		FL2_OV_DIAG_INC(mirBoundsFail);
#if FL2_OV_DIAG
		{
			// A len>0 draw the bounds helper cannot measure is unexpected -
			// name it, rate-limited, so the log shows what poisoned the frame.
			static DWORD s_lastBndDump = 0;
			const DWORD now = GetTickCount();
			if (s_lastBndDump == 0 || now - s_lastBndDump > 2000)
			{
				s_lastBndDump = now;
				FILE* f = fopen("fl2_ov.log", "a");
				if (f != NULL)
				{
					fprintf(f, "BOUNDS-FAIL len=%d text=\"%.*s\"\n",
						len, len > 64 ? 64 : len, psz);
					fclose(f);
				}
			}
		}
#endif
		return false;
	}

	// Checksum region: the crisp text's footprint mapped down to lo coords.
	const int ll = MulDiv(hl, s_fl2_ov_srcW, s_fl2_ov_w) - 1;
	const int lt = MulDiv(ht, s_fl2_ov_srcH, s_fl2_ov_h) - 1;
	const int lr = MulDiv(hr, s_fl2_ov_srcW, s_fl2_ov_w) + 2;
	const int lb = MulDiv(hb, s_fl2_ov_srcH, s_fl2_ov_h) + 2;

	FL2_OVREGION& e = s_fl2_ov_frame[s_fl2_ov_frameN++];

	// Same overhang padding as s_FL2_Dirty on the lo side; a little more on
	// the hi side (scaled glyphs overhang further).
	e.lo.x0 = ll - 2;  e.lo.y0 = lt - 2;  e.lo.x1 = lr + 3;  e.lo.y1 = lb + 3;
	if (e.lo.x0 < 0) e.lo.x0 = 0;
	if (e.lo.y0 < 0) e.lo.y0 = 0;
	if (e.lo.x1 > s_fl2_fb_w) e.lo.x1 = s_fl2_fb_w;
	if (e.lo.y1 > s_fl2_fb_h) e.lo.y1 = s_fl2_fb_h;

	e.hi.x0 = hl - 3;  e.hi.y0 = ht - 3;  e.hi.x1 = hr + 4;  e.hi.y1 = hb + 4;
	if (e.hi.x0 < 0) e.hi.x0 = 0;
	if (e.hi.y0 < 0) e.hi.y0 = 0;
	if (e.hi.x1 > s_fl2_ov_w) e.hi.x1 = s_fl2_ov_w;
	if (e.hi.y1 > s_fl2_ov_h) e.hi.y1 = s_fl2_ov_h;

	e.nSub     = 0;   // baselines captured at the next surface lock
	e.failMask = 0;
	e.kind     = 0;
	e.textLen  = len;
	e.fontLo   = hLo;
	e.textColor = GetTextColor(s_fl2_ov_dc);
	e.bkColor   = GetBkColor(s_fl2_ov_dc);
	e.bkMode    = GetBkMode(s_fl2_ov_dc);
	e.align     = align;
	e.hx = hx;  e.hy = hy;
	if (s_fl2_ov_poolN + len <= FL2_OV_POOL)
	{
		memcpy(s_fl2_ov_poolBuf + s_fl2_ov_poolN, psz, len);
		e.textOfs = s_fl2_ov_poolN;
		s_fl2_ov_poolN += len;
	}
	else
		e.textOfs = -1;
	FL2_OV_DIAG_INC(mirOK);
	return true;
}

// Capture checksum baselines for regions recorded during an acquire that
// never blitted (mirrored draws leave the lo-res DIB untouched, so the
// blit early-outs). Runs from g_FL2_ReleaseDC.
static void s_FL2_OverlayChecksumPending()
{
	if (!s_fl2_ov_on || s_fl2_ov_overflow || s_fl2_ov_checkedN >= s_fl2_ov_frameN)
		return;
	if (gpC_fl2_surface == NULL || gpC_fl2_surface != s_fl2_ov_boundSurface)
		return;

	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	if (FAILED(gpC_fl2_surface->Lock(NULL, &ddsd,
	           DDLOCK_READONLY | DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL)))
	{
		FL2_OV_DIAG_INC(pendLockFail);
		return;
	}

	const WORD* base   = (const WORD*)ddsd.lpSurface;
	const int   stride = (int)(ddsd.lPitch / sizeof(WORD));

	for (int i = s_fl2_ov_checkedN; i < s_fl2_ov_frameN; i++)
		s_FL2_SumRegionCols(base, stride, s_fl2_ov_frame[i]);
	s_fl2_ov_checkedN = s_fl2_ov_frameN;

	gpC_fl2_surface->Unlock(NULL);
}

// Width of a string as the OVERLAY font will draw it, converted back to
// lo-res units (rounded up, so boxes never clip). This is what the layout
// measures with, which is why the crisp text can use natural spacing and
// still line up with every box and column the game computes.
static bool s_FL2_OverlayMeasureWidth(HDC hdcLo, const char* psz, int len, int* pnW)
{
	if (psz == NULL || len <= 0 || pnW == NULL)
		return false;
	if (!s_FL2_OverlayBegin())
		return false;

	HFONT hHi = s_FL2_OverlayFont((HFONT)GetCurrentObject(hdcLo, OBJ_FONT));
	if (hHi == NULL)
		return false;
	SelectObject(s_fl2_ov_dc, hHi);

	SIZE sz = { 0, 0 };
	if (!GetTextExtentPoint32(s_fl2_ov_dc, psz, len, &sz))
		return false;

	*pnW = (int)(((LONG)sz.cx * s_fl2_ov_srcW + s_fl2_ov_w - 1) / s_fl2_ov_w);
	return true;
}

//-----------------------------------------------------------------------------
// g_SetFL2Surface
//
// 
//-----------------------------------------------------------------------------
void g_SetFL2Surface(LPDIRECTDRAWSURFACE7 surface)
{
	gpC_fl2_surface = surface;
}

//-----------------------------------------------------------------------------
// g_PossibleStringCut
//
// sz_str�� position(byte)�� cut�� �� �ִ°� ���θ� ��ȯ�Ѵ�.
// sz_str�� �ѱ� 2byte, ���� 1byte�̴�.
//-----------------------------------------------------------------------------
bool g_PossibleStringCut(const char* sz_str, int position)
{
	if (sz_str != NULL)
	{
		if ((int)strlen(sz_str) <= position)
			return true;

		//
		// position���� ������ ����� data�� ���� �� �ִ�.
		//
		// (1) ASCII
		// (2) �ѱ� 1 byte
		// (3) �ѱ� 2 byte
		//
		// �׷��� (3)�� ��� �� ���� ASCII�� �ƴ϶�� ����� �� ����.
		// �׷��� ó������ position���� �˻縦 �ؾ� �Ѵ�.
		//
		enum _CODE
		{
			_ENG,
			_HAN,
		};

		_CODE code = _ENG;
		int i;
		for (i = 0; i <= position; i++)
		{
			if ((BYTE)sz_str[i] > 128) // no ASCII?
			{
				i++;
				code = _HAN;
			}
			else
				code = _ENG;
		}

		if (code == _HAN)
			if (i <= position + 1)
				return false;

		return true;
	}

	return false;
}

int g_GetStringWidth2(const char* sz_str, int Index, HFONT hfont)
{
	int iStrLen = strlen(sz_str);
	if (Index >= iStrLen)
		Index = iStrLen - 1;

	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;

	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;

	if (hfont != NULL)
		SelectObject(hdc, s_FL2_PickFont(hfont, sz_str, (int)strlen(sz_str)));

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, Index, &size);

	int nOvW;
	if (s_FL2_OverlayMeasureWidth(hdc, sz_str, Index, &nOvW))
		size.cx = nOvW;

	if (bGetDC)
		g_FL2_ReleaseDC();

	return size.cx;
}

// sz_str���ڿ���, Width���� ���Ե� �� �ִ� ���ڿ��� Index (base 0)�� �˷��ش�. 
int g_GetStringIndexByWidth(const char* sz_str, int Width, HFONT hfont)
{
	int iStrWidth = g_GetStringWidth(sz_str, hfont);
	int resIndex;
	int Len = strlen(sz_str);

	if (iStrWidth <= Width)	//��� ���Եȴ�.
		resIndex = Len - 1;
	else
	{
		int Index = Len - 1;
		while (--Index)
		{
			if (!g_PossibleStringCut(sz_str, Index))
				Index--;

			iStrWidth = g_GetStringWidth2(sz_str, Index + 1, hfont);
			if (iStrWidth <= Width)
				break;
		}
		//���� Index����.. Width���� ���� �ʴ� ���ڿ��� ������ ĳ������ ��ġ.
		resIndex = Index;
	}

	return resIndex;
}

int g_PrintColorStr2(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, int LimitWidth)
{
	int iStrWidth = g_GetStringWidth((const char*)sz_str, pi.hfont);
	if (iStrWidth <= LimitWidth)
		return g_PrintColorStr(x, y, sz_str, pi, str_rgb);
	else
	{
		// ����� ���ڿ��� �ȼ� ���̰�, ���� ���̺��� ���. ���� ���̸� ���� �ʵ���.. ���ڿ��� �ڸ���..
		int Len = strlen(sz_str);
		char* strTemp = new char[Len + 1];

		int Index = Len - 1;
		while (--Index)
		{
			if (!g_PossibleStringCut(sz_str, Index))
			{
				//�ڸ� �� ���� Index (�ѱ۵� 2����Ʈ ���ڱ��������� .. ����)�� ���.. �ѹ� �� --
				Index--;
			}
			//���ڿ� ���� ��..
			iStrWidth = g_GetStringWidth2((const char*)sz_str, Index - 1, pi.hfont);
			if (iStrWidth <= LimitWidth)
				break;
		}
		// ���ڿ��� ó������ �Դٸ�.. �׷����� ���� ��������.. üũ
		if (Index == 0)
			return g_PrintColorStr(x, y, sz_str, pi, str_rgb);
		// �ƴ϶��.. Index ��ŭ��.. �׸���. �ϴ�.. ���� �ڸ� ������.. '..'�� �ٿ�����.
		strncpy_s(strTemp, Len, sz_str, Index - 2);
		strTemp[Index - 2] = '.';
		strTemp[Index - 1] = '.';
		strTemp[Index] = '\0';
		int res = g_PrintColorStr(x, y, (const char*)strTemp, pi, str_rgb);
		delete strTemp;
		return res;
	}
}

//-----------------------------------------------------------------------------
// g_GetStringWidth
//
// p_str�� null terminated string�̴�.
// hfont�� �ùٸ��� setting�ؾ� ��Ȯ�� ���� ���´�.
//
// ! �ܺο��� lock�ɸ� �ȵȴ�.
//-----------------------------------------------------------------------------
int g_GetStringWidth(const char* sz_str, HFONT hfont)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;

	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;

	if (hfont != NULL)
		SelectObject(hdc, s_FL2_PickFont(hfont, sz_str, (int)strlen(sz_str)));

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);

	// Report the width of what will actually be on screen (the overlay's
	// crisp text), in lo-res units.
	int nOvW;
	if (s_FL2_OverlayMeasureWidth(hdc, sz_str, (int)strlen(sz_str), &nOvW))
		size.cx = nOvW;

	if (bGetDC)
		g_FL2_ReleaseDC();

	return size.cx;
}

//-----------------------------------------------------------------------------
// g_GetStringHeight
//
// p_str�� null terminated string�̴�.
// hfont�� �ùٸ��� setting�ؾ� ��Ȯ�� ���� ���´�.
//
// !�ܺο��� lock�ɸ� �ȵȴ�.
//-----------------------------------------------------------------------------
int g_GetStringHeight(const char* sz_str, HFONT hfont)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;

	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;


	if (hfont != NULL)
		SelectObject(hdc, s_FL2_PickFont(hfont, sz_str, (int)strlen(sz_str)));

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);

	if (bGetDC)
		g_FL2_ReleaseDC();

	return size.cy;
}

//-----------------------------------------------------------------------------
// g_PrintLen
//
// gpC_fl2_surface�� ����Ѵ�.
// p_str�� null terminated string�̴�.
//
// !�ܺο��� lock�ɸ� �ȵȴ�.
//-----------------------------------------------------------------------------
void g_PrintLen(int x, int y, const char* sz_str, int str_length, PrintInfo* p_print_info)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());

	// Empty prints happen every frame (chat whisper line among others). They
	// draw nothing, but the dirty tracker cannot bound them and falls back to
	// marking the whole surface - and the overlay mirror used to degrade the
	// entire frame over them. Skip them outright.
	if (str_length <= 0)
		return;

	if (sz_str != NULL)
	{
		//assert(sz_str != NULL);
		assert(gpC_fl2_surface != NULL);

		// no Release exception handling code for speed.

		HDC hdc;

		bool bGetDC = g_FL2_GetDC();

		hdc = gh_FL2_DC;

		if (p_print_info != NULL)
		{
			SetTextAlign(hdc, p_print_info->text_align);
			SetBkMode(hdc, p_print_info->bk_mode);
			SetBkColor(hdc, p_print_info->back_color);
			SetTextColor(hdc, p_print_info->text_color);
			SelectObject(hdc, s_FL2_PickFont(p_print_info->hfont, sz_str, str_length));
		}

		// Prefer the native-res overlay; when the mirror succeeds the lo-res
		// twin is not drawn at all. The surface keeps only the background,
		// and the occlusion checksum detects anything painted over it.
		bool bMirrored = false;
		if (s_fl2_fb_active)
			bMirrored = s_FL2_OverlayMirrorTextOut(hdc, x, y, sz_str, str_length);

		if (!bMirrored)
		{
			if (s_fl2_fb_active) s_FL2_EnsureCleared();

			TextOut(hdc, x, y, sz_str, str_length);

			if (s_fl2_fb_active)
			{
				s_fl2_fb_dirty = true;
				s_FL2_DirtyTextOut(hdc, x, y, sz_str, str_length);
			}
		}

		if (bGetDC)
			g_FL2_ReleaseDC();

	}
}

std::string g_MakeLinefeedString(char* sz_src, int linewidth, HFONT hfont)
{
	assert(sz_src != NULL);

	std::string resultString = sz_src;

	int strWidth = g_GetStringWidth(sz_src, hfont);
	int LinefeedCount = strWidth / linewidth;

	int srcIndex = 0;
	int destIndex = 0;
	int LinefeedIndex = 0;
	for (int i = 0; i < LinefeedCount; i++)
	{
		LinefeedIndex = g_GetStringIndexByWidth(&sz_src[srcIndex], linewidth, hfont);
		destIndex += LinefeedIndex;
		resultString.insert(destIndex, "\n");
		destIndex++;
		srcIndex += LinefeedIndex;
	}
	return resultString;
}

void g_DrawText(RECT* pRt, const char* sz_str, PrintInfo* p_print_info)
{
	if (!pRt || !sz_str) return;

	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (sz_str != NULL)
	{
		//assert(sz_str != NULL);
		assert(gpC_fl2_surface != NULL);

		//sz_str�� �����ȼ� ũ��� pRt�� ���� ���Ͽ�, ���ڿ��� �����ǵ�� �� �ֵ��� �� ó���Ѵ�.

		int str_length = strlen(sz_str);
		int destWidth = pRt->right - pRt->left;
		int strWidth = g_GetStringWidth(sz_str, p_print_info->hfont);
		int LinefeedCount = strWidth / destWidth;
		HFONT hfont = NULL;
		if (p_print_info)
			hfont = p_print_info->hfont;

		std::string srcStr = g_MakeLinefeedString((char*)sz_str, destWidth, hfont);//sz_str;


		/*		int srcIndex = 0;
				int destIndex = 0;
				int LinefeedIndex = 0;
				for (int i=0; i<LinefeedCount; i++)
				{
					LinefeedIndex = g_GetStringIndexByWidth (&sz_str[srcIndex], destWidth, hfont);
					destIndex += LinefeedIndex;
					srcStr.insert(destIndex, "\n");
					destIndex ++;
					srcIndex += LinefeedIndex;
				}*/

		int strHeight = g_GetStringHeight(sz_str, hfont);
		int destHeight = pRt->bottom - pRt->top;
		if (strWidth % destWidth) LinefeedCount++;
		pRt->bottom = pRt->top + strHeight * LinefeedCount;

		// no Release exception handling code for speed.

		HDC hdc;

		bool bGetDC = g_FL2_GetDC();

		hdc = gh_FL2_DC;

		if (s_fl2_fb_active) s_FL2_EnsureCleared();

		if (p_print_info != NULL)
		{
			SetTextAlign(hdc, p_print_info->text_align);
			SetBkMode(hdc, p_print_info->bk_mode);
			SetBkColor(hdc, p_print_info->back_color);
			SelectObject(hdc, s_FL2_PickFont(p_print_info->hfont, srcStr.c_str(), (int)srcStr.length()));
			//�׸��� ���
			SetTextColor(hdc, 0);
			RECT sRt = { pRt->left + 1, pRt->top + 1, pRt->right + 1, pRt->bottom + 1 };
			DrawText(hdc, srcStr.c_str(), srcStr.length(), &sRt, p_print_info->text_align);
			//���ڿ� ���
			SetTextColor(hdc, p_print_info->text_color);
			DrawText(hdc, srcStr.c_str(), srcStr.length(), pRt, p_print_info->text_align);

		}
		else
			DrawText(hdc, srcStr.c_str(), srcStr.length(), pRt, DT_LEFT);

		if (s_fl2_fb_active)
		{
			s_fl2_fb_dirty = true;

			// DrawText was handed its rectangle, so the bounds are known. The
			// shadow pass above is offset by one, hence the +1 on each edge.
			if (pRt != NULL)
				s_FL2_Dirty(pRt->left, pRt->top, pRt->right + 1, pRt->bottom + 1);
			else
				s_FL2_DirtyAll();
		}

		if (bGetDC)
			g_FL2_ReleaseDC();

	}
}



//-----------------------------------------------------------------------------
// g_DBCSLen
//
// p_dbcs�� length�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int g_DBCSLen(const char_t* p_dbcs)
{
	if (p_dbcs == NULL)
		return 0;

	int len = 0;
	while (*p_dbcs++ != 0)
		len++;

	return len;
}
int	g_GetByteLenth(const char_t* p_dbcs, int dbcs_len)
{
	int c = 0;
	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;

	// convert
	for (int i = 0, c = 0; i < dbcs_len; i++)
	{
		// check high byte
		if ((p_dbcs[i] & 0xFF00) != 0)
		{
			c += 2;
		}
		else
		{
			c++;
		}
	}
	return c;

}
//-----------------------------------------------------------------------------
// g_Convert_DBCS_Ascii2SingleByte
//
// DBCS Ascii code�� single byte�� �ٲ۴�. �ٸ� ���ڵ��� �״�� ������Ų��.
// p_new_buf�� new�� �Ҵ��Ѵ�. ���� �ܺο��� p_new_buf�� delete����� �Ѵ�.
//
// ����� buffer�� ����(by byte)�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int g_Convert_DBCS_Ascii2SingleByte(const char_t* p_dbcs, int dbcs_len, char*& p_new_buf)
{
	//
	// (1) ignore 'p_new_buf'.
	//

	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;

	int max_size = dbcs_len * 2 + 1;

	char* p_temp = new char[max_size];
	CheckMemAlloc(p_temp);
	memset(p_temp, 0, max_size);

	// convert
	for (int i = 0, c = 0; i < dbcs_len; i++)
	{
		// check high byte
		if ((p_dbcs[i] & 0xFF00) != 0)
		{
			*(char_t*)(p_temp + i + c) = p_dbcs[i];
			c++;
		}
		else
		{
			p_temp[i + c] = (char)(p_dbcs[i]);
		}
	}

	int len = strlen(p_temp);
	p_new_buf = new char[len + 1];
	CheckMemAlloc(p_new_buf);

	strcpy_s(p_new_buf, len + 1, p_temp);

	DeleteNewArray(p_temp);

	return len;
}

//-----------------------------------------------------------------------------
// g_ConvertAscii2DBCS
//
// ascii code(single byte���� ����)�� DBCS�� ��ȯ�Ͽ� p_new_buf�� �Ҵ��Ѵ�.
// p_new_buf�� �ܺο��� delete�ؾ� �Ѵ�.
//
//-----------------------------------------------------------------------------
// p_ascii:		single byte string
// ascii_len:	p_ascii length
// p_new_buf:	converted DBCS buf
//
// return:		p_new_buf length
//					zero is failed.
//-----------------------------------------------------------------------------
int g_ConvertAscii2DBCS(const char* p_ascii, int ascii_len, char_t*& p_new_buf)
{
	if (p_ascii == NULL || ascii_len <= 0)
		return 0;

	int size = ascii_len + 1;
	char_t* p_temp = new char_t[size];

	int dbcs = 0;
	for (int i = 0; i < ascii_len; i++, dbcs++)
		if (isascii(p_ascii[i]) != 0) // ascii? or not hangul code?
		{
			// ascii

			p_temp[dbcs] = (char_t)p_ascii[i];
		}
		else
		{
			// hangul

			p_temp[dbcs] = *((char_t*)(p_ascii + i));
			i++;
		}

	// ��Ȯ�� size�� buffer�� p_new_buf�� ����Ű���� �Ѵ�.
	// �ѱ��� ���ԵǸ� dbcs�� ascii_len�� �ٸ���.
	p_new_buf = new char_t[dbcs + 1];

	for (int m = 0; m < dbcs; m++)
		p_new_buf[m] = p_temp[m];

	DeleteNewArray(p_temp);
	p_new_buf[dbcs] = 0;

	return dbcs;
}

// DC�� Get�Ѵ�.
// ---------------------------------------------------------------------------
// s_FL2_EnsureFallbackDC
// Lazily creates the DIBSection and memory DC on first use.
// ---------------------------------------------------------------------------
static bool s_FL2_EnsureFallbackDC()
{
	if (gpC_fl2_surface == NULL)
		return false;

	// Query the surface dimensions and pixel format
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	if (FAILED(gpC_fl2_surface->GetSurfaceDesc(&ddsd)))
		return false;

	if (s_fl2_fb_dc != NULL)
	{
		// Already built, and still the right size - reuse it.
		if ((int)ddsd.dwWidth == s_fl2_fb_w && (int)ddsd.dwHeight == s_fl2_fb_h)
			return true;

		// g_SetFL2Surface only swaps the pointer, and InitSurface can recreate
		// g_pLast at a different resolution, so the cached DIBSection can end up
		// the wrong size. Tear it down and rebuild rather than draw off the end.
		SelectObject(s_fl2_fb_dc, s_fl2_fb_bmp_old);
		DeleteDC(s_fl2_fb_dc);
		DeleteObject(s_fl2_fb_bmp);

		s_fl2_fb_dc      = NULL;
		s_fl2_fb_bmp     = NULL;
		s_fl2_fb_bmp_old = NULL;
		s_fl2_fb_bits    = NULL;
		s_fl2_curN       = 0;
		s_fl2_prevN      = 0;

		// The overlay scales from this DIB's geometry - rebuild it too.
		s_FL2_OverlayRelease();
	}

	s_fl2_fb_w = (int)ddsd.dwWidth;
	s_fl2_fb_h = (int)ddsd.dwHeight;
	if (ddsd.dwFlags & DDSD_PIXELFORMAT)
		s_fl2_fb_is565 = (ddsd.ddpfPixelFormat.dwGBitMask == 0x07E0u);
	else
		s_fl2_fb_is565 = true;   // assume 565 if we can't tell

	// Create a 32-bit top-down DIBSection of the same dimensions
	BITMAPINFO bmi   = {};
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       =  s_fl2_fb_w;
	bmi.bmiHeader.biHeight      = -s_fl2_fb_h;  // negative = top-down rows
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biBitCount    = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	HDC screen_dc    = GetDC(NULL);
	s_fl2_fb_bmp     = CreateDIBSection(screen_dc, &bmi, DIB_RGB_COLORS,
	                                     (void**)&s_fl2_fb_bits, NULL, 0);
	s_fl2_fb_dc      = CreateCompatibleDC(screen_dc);
	ReleaseDC(NULL, screen_dc);

	if (!s_fl2_fb_bmp || !s_fl2_fb_dc || !s_fl2_fb_bits)
	{
		if (s_fl2_fb_dc)  { DeleteDC(s_fl2_fb_dc);       s_fl2_fb_dc  = NULL; }
		if (s_fl2_fb_bmp) { DeleteObject(s_fl2_fb_bmp);  s_fl2_fb_bmp = NULL; }
		s_fl2_fb_bits = NULL;
		return false;
	}

	s_fl2_fb_bmp_old = (HBITMAP)SelectObject(s_fl2_fb_dc, s_fl2_fb_bmp);

	// CreateDIBSection zero-fills, and zero is not the colorkey, so the buffer
	// has to be primed once. From here on only drawn regions are ever cleared.
	{
		const int nPx = s_fl2_fb_w * s_fl2_fb_h;
		for (int i = 0; i < nPx; i++)
			s_fl2_fb_bits[i] = FL2_FB_COLORKEY;
	}

	s_fl2_curN  = 0;
	s_fl2_prevN = 0;

	return true;
}

// ---------------------------------------------------------------------------
// s_FL2_BlitFallbackToSurface
// Colour-converts and copies the DIBSection pixels onto gpC_fl2_surface.
// Pixels equal to FL2_FB_COLORKEY are skipped (transparent).
// Only runs when s_fl2_fb_dirty is set (i.e. something was actually drawn).
// ---------------------------------------------------------------------------
static void s_FL2_BlitFallbackToSurface()
{
	if (!s_fl2_fb_dirty || !s_fl2_fb_bits || !gpC_fl2_surface)
		return;

	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	if (FAILED(gpC_fl2_surface->Lock(NULL, &ddsd,
	           DDLOCK_WAIT | DDLOCK_WRITEONLY, NULL)))
	{
		FL2_OV_DIAG_INC(blitLockFail);
		return;
	}

	WORD*        dst_base   = (WORD*)ddsd.lpSurface;
	int          dst_stride = (int)(ddsd.lPitch / sizeof(WORD));
	const DWORD* src_base   = s_fl2_fb_bits;

	for (int r = 0; r < s_fl2_curN; r++)
	{
	const FL2_DIRTYRECT& _e = s_fl2_cur[r];

	for (int y = _e.y0; y < _e.y1; y++)
	{
		WORD*        dst = dst_base + y * dst_stride;
		const DWORD* src = src_base + y * s_fl2_fb_w;

		for (int x = _e.x0; x < _e.x1; x++)
		{
			DWORD p = src[x];
			if (p == FL2_FB_COLORKEY)
				continue;   // transparent – leave destination pixel untouched

			// GDI DIBSection (BI_RGB, 32-bit) stores pixels as 0x00RRGGBB
			BYTE r = (BYTE)(p >> 16);
			BYTE g = (BYTE)(p >>  8);
			BYTE b = (BYTE)(p);

			WORD w;
			if (s_fl2_fb_is565)
				w = (WORD)(((WORD)(r >> 3) << 11) | ((WORD)(g >> 2) << 5) | (WORD)(b >> 3));
			else   // RGB555
				w = (WORD)(((WORD)(r >> 3) << 10) | ((WORD)(g >> 3) << 5) | (WORD)(b >> 3));

			dst[x] = w;
		}
	}
	}

	// Native-res overlay bookkeeping: checksum the 565 pixels under each new
	// text region while the surface is already locked, and refresh sums whose
	// regions this release legitimately rewrote (text over text is not
	// occlusion). A mismatch later, at flush, means non-text UI painted over
	// the region and its crisp copy must yield to the lo-res pixels.
	if (s_fl2_ov_on && !s_fl2_ov_overflow && gpC_fl2_surface == s_fl2_ov_boundSurface)
	{
		for (int i = 0; i < s_fl2_ov_checkedN; i++)
		{
			for (int r2 = 0; r2 < s_fl2_curN; r2++)
			{
				const FL2_DIRTYRECT& c  = s_fl2_cur[r2];
				const FL2_DIRTYRECT& lo = s_fl2_ov_frame[i].lo;
				if (lo.x0 < c.x1 && c.x0 < lo.x1 && lo.y0 < c.y1 && c.y0 < lo.y1)
				{
					s_FL2_SumRegionCols(dst_base, dst_stride, s_fl2_ov_frame[i]);
					break;
				}
			}
		}

		for (int i = s_fl2_ov_checkedN; i < s_fl2_ov_frameN; i++)
			s_FL2_SumRegionCols(dst_base, dst_stride, s_fl2_ov_frame[i]);

		s_fl2_ov_checkedN = s_fl2_ov_frameN;
	}

	gpC_fl2_surface->Unlock(NULL);
}

bool	g_FL2_GetDC()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (gh_FL2_DC == NULL)
	{
		// Deliberately NOT using gpC_fl2_surface->GetDC() any more.
		//
		// It succeeds here, but it hands back a brand new HDC on every acquire -
		// around 500 a second. Selecting a font into a fresh DC makes GDI build a
		// new font realisation each time, and that cost shows up inside TextOut
		// and GetTextExtentPoint32 rather than in SelectObject. Measured effect:
		// ASCII text went from 0.72us/char at login to 66us/char after a session,
		// identically for Korean, while acquire time itself stayed flat.
		//
		// The DIBSection path below keeps ONE persistent CreateCompatibleDC for
		// the life of the surface, so the font is realised once instead of
		// continuously. Set g_bFL2UseSurfaceDC to restore the old behaviour.
		if (g_bFL2UseSurfaceDC)
		{
			HRESULT hr = gpC_fl2_surface->GetDC(&gh_FL2_DC);

			if (SUCCEEDED(hr))
			{
				return true;
			}
		}

		// GetDC failed – this surface is likely 16-bit (modern Windows limitation).
		// Use the GDI DIBSection fallback instead.
		gh_FL2_DC = NULL;
		if (s_FL2_EnsureFallbackDC())
		{
			// Nothing is cleared here. The first actual draw calls
			// s_FL2_EnsureCleared(), so an acquire that only measures text costs
			// nothing at all - which is the common case by a wide margin.
			s_fl2_curN = 0;

			gh_FL2_DC       = s_fl2_fb_dc;
			s_fl2_fb_active = true;
			s_fl2_fb_dirty  = false;
			return true;
		}

		// Last resort: bare screen-compatible DC (measurement only, no rendering).
		if (s_fl2_bare_dc == NULL)
			s_fl2_bare_dc = CreateCompatibleDC(NULL);
		if (s_fl2_bare_dc != NULL)
		{
			gh_FL2_DC        = s_fl2_bare_dc;
			s_fl2_bare_active = true;
			return true;
		}

		return false;   // completely out of options – caller gets NULL hdc
	}

	return false;
}

// Mark the fallback DIBSection as dirty so g_FL2_ReleaseDC() will blit it back.
// Call this after drawing directly into gh_FL2_DC without going through g_PrintLen / g_DrawText.
void g_FL2_MarkDirty()
{
	if (s_fl2_fb_active)
	{
		// The caller drew straight into the DC, so we have no bounds and cannot
		// know what it disturbed. Clear first, then mark the lot.
		s_FL2_EnsureCleared();
		s_fl2_fb_dirty = true;
		s_FL2_DirtyAll();
	}
}

// DC�� Release �Ѵ�.
bool	g_FL2_ReleaseDC()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (gh_FL2_DC != NULL)
	{
		if (s_fl2_fb_active)
		{
			// Copy rendered text from the DIBSection onto the DirectDraw surface.
			s_FL2_BlitFallbackToSurface();

			// Baselines for overlay regions from acquires that never blitted.
			s_FL2_OverlayChecksumPending();

			// What was just drawn is what the next draw has to clear.
			for (int i = 0; i < s_fl2_curN; i++)
				s_FL2_AddRect(s_fl2_prev, s_fl2_prevN,
					s_fl2_cur[i].x0, s_fl2_cur[i].y0,
					s_fl2_cur[i].x1, s_fl2_cur[i].y1);

			s_fl2_curN = 0;

			s_fl2_fb_active = false;
			s_fl2_fb_dirty  = false;
		}
		else if (s_fl2_bare_active)
		{
			// Bare measure-only DC – nothing to copy back.
			s_fl2_bare_active = false;
		}
		else
		{
			// Real DirectDraw DC – release normally.
			gpC_fl2_surface->ReleaseDC(gh_FL2_DC);
		}

		gh_FL2_DC = NULL;
		return true;
	}

	return false;
}


////////////////////////////////////////////////
// �̸� �ٿ��ִ� �ҽ� by sonee
//
// �� ���ڸ� 40�ڷ� ���̰� ������ ReduceString(str,40);
// str ��ü�� �����Ѵ�.
// �������� �ʰ� ���ϰ����� �Ұ�� ������ ����κ��� ���� �׳� �����ϸ��
////////////////////////////////////////////////

void ReduceString(char* str, int len)
{
	if (len < 15) return;
	char name[100] = "", * p_name;
	int lt = strlen(str), passlen, position, size;
	p_name = &name[0];
	//bool g_PossibleStringCut(const char * sz_str, int position)
	if (lt > len)
	{
		if (g_PossibleStringCut(str, 5))
			passlen = 5;
		else
			passlen = 6;
		memcpy(p_name, str, passlen);
		p_name += passlen;
		*(p_name++) = '.';
		*(p_name++) = '.';
		*(p_name++) = '.';
		passlen += 3;
		size = passlen;
		position = lt - (len - passlen);
		if (g_PossibleStringCut(str, position))
		{
			position = lt - len + passlen;
			passlen = len - passlen;
		}
		else
		{
			position = lt - len + passlen - 1;
			passlen = len - passlen + 1;
		}
		size += passlen;
		memcpy(p_name, str + position, passlen);
		memcpy(str, name, size);
		str[size] = '\0';
	}
}

// �޺κп� ... �� ����ش�.				 by sonee
void ReduceString2(char* str, int len)
{
	if (len < 15) return;
	char name[100] = "", * p_name;
	int lt = strlen(str), passlen, position, size;
	p_name = &name[0];
	//bool g_PossibleStringCut(const char * sz_str, int position)

	int skip_len = len - 14;
	if (lt > len)
	{
		if (g_PossibleStringCut(str, skip_len))
			passlen = skip_len;
		else
			passlen = skip_len + 1;
		memcpy(p_name, str, passlen);
		p_name += passlen;
		*(p_name++) = '.';
		*(p_name++) = '.';
		*(p_name++) = '.';
		passlen += 3;
		size = passlen;
		position = lt - (len - passlen);
		if (g_PossibleStringCut(str, position))
		{
			position = lt - len + passlen;
			passlen = len - passlen;
		}
		else
		{
			position = lt - len + passlen - 1;
			passlen = len - passlen + 1;
		}
		size += passlen;
		memcpy(p_name, str + position, passlen);
		memcpy(str, name, size);
		str[size] = '\0';
	}
}
// 2004, 10, 26, sobeit add start
void ReduceString3(char* str, int len)
{
	if (str == NULL) return;
	if (len < 15) return;
	int CurLen = strlen(str);
	if (CurLen <= len) return;

	if (!g_PossibleStringCut(str, len))
		str[len - 3] = '.';
	str[len - 2] = '.';
	str[len - 1] = '.';
	str[len] = '\0';
}
// 2004, 10, 26, sobeit add end

//-----------------------------------------------------------------------------
// g_PrintColorStrLen
//
// str�� ����� ���� x�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int g_PrintColorStrLen(int x, int y, const char* sz_str, int str_length, PrintInfo& pi, COLORREF str_rgb)
{
	PrintInfo use_pi = pi;

	use_pi.text_color = str_rgb;

	bool bGetDC = g_FL2_GetDC();

	g_PrintLen(x, y, sz_str, str_length, &use_pi);

	int re = (x + g_GetStringWidth(sz_str, use_pi.hfont));

	if (bGetDC)
		g_FL2_ReleaseDC();

	return re;
}


//-----------------------------------------------------------------------------
// g_PrintColorStrOut
//
// str�� ����� ���� x�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int g_PrintColorStrOut(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, COLORREF out_rgb)
{
	PrintInfo use_pi = pi;

	use_pi.text_color = out_rgb;
	bool bGetDC = g_FL2_GetDC();
	g_Print(x - 1, y, sz_str, &use_pi);
	g_Print(x + 1, y, sz_str, &use_pi);
	g_Print(x, y - 1, sz_str, &use_pi);
	g_Print(x, y + 1, sz_str, &use_pi);

	use_pi.text_color = str_rgb;
	g_Print(x, y, sz_str, &use_pi);

	int re = (x + g_GetStringWidth(sz_str, use_pi.hfont));

	if (bGetDC)
		g_FL2_ReleaseDC();

	return re;
}

//-----------------------------------------------------------------------------
// g_PrintColorStrShadow
//
// str�� ����� ���� x�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int g_PrintColorStrShadow(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, COLORREF shadow_rgb)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	PrintInfo use_pi = pi;

	if (shadow_rgb == 0xFFFFFFFF)
	{
		int r = (str_rgb & 0xFF0000) >> 16;
		int g = (str_rgb & 0xFF00) >> 8;
		int b = str_rgb & 0xFF;
		//		shadow_rgb = RGB(max(0, r-150), max(0, g-150), max(0, b-150));
		shadow_rgb = RGB(r >> 2, g >> 2, b >> 2);
	}

	bool bGetDC = g_FL2_GetDC();

	use_pi.text_color = shadow_rgb;
	g_Print(x + 1, y + 1, sz_str, &use_pi);

	use_pi.text_color = str_rgb;
	g_Print(x, y, sz_str, &use_pi);

	int re = (x + g_GetStringWidth(sz_str, use_pi.hfont));

	if (bGetDC)
		g_FL2_ReleaseDC();

	return re;
}

std::string g_GetNumberString(int number)
{
	char sz_temp[20];
	wsprintf(sz_temp, "%d", number);
	std::string sstr = sz_temp;
	for (int i = 3; i <= 13; i += 4)
		if ((int)sstr.size() > i)sstr.insert(sstr.size() - i, ",");

	return sstr;
}


std::string g_GetStringByMoney(DWORD dwMoney)
{
	char TempBuffer[32] = { 0, };
	std::string sstr;
	DWORD TempMoney = 0;
	if (dwMoney >= 100000000) // ��
	{
		TempMoney = dwMoney / 100000000;
		if (TempMoney)
		{
			wsprintf(TempBuffer, "%d��", TempMoney);
			sstr += TempBuffer;
		}
	}
	if (dwMoney >= 10000) // ��
	{
		TempMoney = (dwMoney % 100000000) / 10000;
		if (TempMoney)
		{
			wsprintf(TempBuffer, "%d��", TempMoney);
			sstr += TempBuffer;
		}
	}

	TempMoney = (dwMoney % 10000);
	if (TempMoney || 0 == dwMoney)
	{
		wsprintf(TempBuffer, "%d", TempMoney);
		sstr += TempBuffer;
	}

	return sstr;
}

















// ---------------------------------------------------------------------------
// Native-resolution overlay: public entry points
// ---------------------------------------------------------------------------

// Ask the overlay to stand down for the next nFrames frames (splash/CI
// fades paint over every text region each tick; text draws lo-res under
// them like the original client, then goes crisp again).
void g_FL2_OverlaySkipFrames(int nFrames)
{
	if (nFrames > s_fl2_ov_skipFrames)
		s_fl2_ov_skipFrames = nFrames;
}

// 0 = overlay invisible, 255 = fully crisp. Decays after 2 frames without
// a caller (the splash code calls this every fade tick).
void g_FL2_OverlaySetFadeAlpha(int nAlpha255)
{
	if (nAlpha255 < 0)   nAlpha255 = 0;
	if (nAlpha255 > 255) nAlpha255 = 255;
	s_fl2_ov_fadeAlpha  = nAlpha255;
	s_fl2_ov_fadeFrames = 2;
}

// Resolution.inf "TextOverlay: 0" kill switch.
void g_FL2_SetOverlayEnabled(bool bEnable)
{
	s_fl2_ov_userEnabled = bEnable;
	if (!bEnable)
		s_FL2_OverlayRelease();
}

// Raw-GDI widgets (edit boxes) draw their text through this so it reaches
// both the lo-res surface path and the overlay. Replaces the caller's own
// TextOut - do not call both.
void g_FL2_TextOutMirrored(HDC hdc, int x, int y, const char* psz, int len)
{
	if (hdc == NULL || psz == NULL || len <= 0)
		return;

	bool bMirrored = false;
	if (s_fl2_fb_active)
		bMirrored = s_FL2_OverlayMirrorTextOut(hdc, x, y, psz, len);

	if (!bMirrored)
	{
		TextOut(hdc, x, y, psz, len);

		if (s_fl2_fb_active)
		{
			s_fl2_fb_dirty = true;
			s_FL2_DirtyTextOut(hdc, x, y, psz, len);
		}
	}
}

// Mirrored caret for single-line edit widgets. The visible text is the
// overlay's, so the caret must sit at the OVERLAY font's measured width of
// the substring before the cursor - positioning it from lo-res metrics
// drifts further off with every typed character. Returns true when drawn
// (the caller then skips its lo-res caret).
bool g_FL2_CaretMirrored(HDC hdcLo, int xBase, int yBase, const char* psz, int len, COLORREF color)
{
	if (!s_fl2_fb_active)
		return false;
	if (!s_FL2_OverlayBegin() || s_fl2_ov_overflow)
		return false;
	if (gpC_fl2_surface != s_fl2_ov_boundSurface)
		return false;
	if (s_fl2_ov_frameN >= FL2_OV_MAX_REGION)
		return false;

	HFONT hHi = s_FL2_OverlayFont((HFONT)GetCurrentObject(hdcLo, OBJ_FONT));
	if (hHi == NULL)
		return false;
	SelectObject(s_fl2_ov_dc, hHi);

	SIZE szCur = { 0, 0 };
	if (psz != NULL && len > 0 &&
	    !GetTextExtentPoint32(s_fl2_ov_dc, psz, len, &szCur))
		return false;

	TEXTMETRIC tmHi;
	if (!GetTextMetrics(s_fl2_ov_dc, &tmHi))
		return false;

	const int hx = MulDiv(xBase, s_fl2_ov_w, s_fl2_ov_srcW) + szCur.cx + 2;
	const int hy = MulDiv(yBase, s_fl2_ov_h, s_fl2_ov_srcH);
	const int hh = tmHi.tmHeight;

	// COLORREF is 0x00BBGGRR, the DIB wants 0x00RRGGBB.
	DWORD dwPx = ((DWORD)GetRValue(color) << 16) |
	             ((DWORD)GetGValue(color) <<  8) |
	              (DWORD)GetBValue(color);
	if (dwPx == FL2_FB_COLORKEY)
		dwPx = FL2_FB_COLORKEY + 0x010101u;

	for (int y = hy; y < hy + hh; y++)
	{
		if (y < 0 || y >= s_fl2_ov_h)
			continue;
		DWORD* pRow = s_fl2_ov_bits + (size_t)y * s_fl2_ov_w;
		for (int x = hx; x < hx + 2; x++)
			if (x >= 0 && x < s_fl2_ov_w)
				pRow[x] = dwPx;
	}

	// Track it like a text region so it uploads now and erases next frame.
	SIZE szLo = { 0, 0 };
	if (psz != NULL && len > 0)
		GetTextExtentPoint32(hdcLo, psz, len, &szLo);

	TEXTMETRIC tmLo;
	tmLo.tmHeight = 16;
	GetTextMetrics(hdcLo, &tmLo);

	FL2_OVREGION& e = s_fl2_ov_frame[s_fl2_ov_frameN++];

	e.lo.x0 = xBase + szLo.cx - 2;   e.lo.y0 = yBase - 2;
	e.lo.x1 = xBase + szLo.cx + 5;   e.lo.y1 = yBase + tmLo.tmHeight + 3;
	if (e.lo.x0 < 0) e.lo.x0 = 0;
	if (e.lo.y0 < 0) e.lo.y0 = 0;
	if (e.lo.x1 > s_fl2_fb_w) e.lo.x1 = s_fl2_fb_w;
	if (e.lo.y1 > s_fl2_fb_h) e.lo.y1 = s_fl2_fb_h;

	e.hi.x0 = hx - 2;   e.hi.y0 = hy - 2;
	e.hi.x1 = hx + 4;   e.hi.y1 = hy + hh + 3;
	e.failMask = 0;
	e.kind     = 1;
	e.textOfs  = -1;
	e.textLen  = 0;
	e.hx = hx;  e.hy = hy;
	e.cw = 2;   e.ch = hh;
	e.fill = dwPx;
	if (e.hi.x0 < 0) e.hi.x0 = 0;
	if (e.hi.y0 < 0) e.hi.y0 = 0;
	if (e.hi.x1 > s_fl2_ov_w) e.hi.x1 = s_fl2_ov_w;
	if (e.hi.y1 > s_fl2_ov_h) e.hi.y1 = s_fl2_ov_h;

	e.nSub = 0;   // baselines captured at the next surface lock
	return true;
}

// Frame flush, invoked from CDirectDraw::Flip just before the present:
// verify no later UI painted over the mirrored text (checksum per region,
// fall back to lo-res where it did), upload the dirty regions, rotate the
// erase list for next frame.
void g_FL2_OverlayFlush()
{
	const bool bBegan = s_fl2_ov_began;
	s_fl2_ov_began = false;   // next frame re-evaluates geometry

	if (s_fl2_ov_skipFrames > 0)
		s_fl2_ov_skipFrames--;

	const bool bFade = (s_fl2_ov_fadeFrames > 0);
	if (s_fl2_ov_fadeFrames > 0)
		s_fl2_ov_fadeFrames--;
	CD3D9Present::SetOverlayAlpha(bFade ? s_fl2_ov_fadeAlpha : 255);

#if FL2_OV_DIAG
	s_diag.flushFrames++;
	s_diag.lastFrameN   = s_fl2_ov_frameN;
	s_diag.lastCheckedN = s_fl2_ov_checkedN;
	s_diag.regionsTotal += s_fl2_ov_frameN;
	s_FL2_DiagDump();
#endif

	if (!s_fl2_ov_on)
	{
		// Disabled / inactive this frame: nothing was mirrored, nothing is
		// uploaded, and the presenter's per-frame expiry keeps any stale
		// texture invisible.
		FL2_OV_DIAG_INC(flushInactive);
		s_fl2_ov_frameN = s_fl2_ov_checkedN = 0;
		s_fl2_ov_poolN = 0;
		s_fl2_ov_overflow = false;
		return;
	}
	s_fl2_ov_on = false;

	// Whole-frame fallback: something exceeded the tracking limits. Clear
	// everything and push one full transparent rect so no stale texel can
	// ever resurface.
	if (s_fl2_ov_overflow)
	{
		FL2_OV_DIAG_INC(flushOverflow);
		FL2_DIRTYRECT all = { 0, 0, s_fl2_ov_w, s_fl2_ov_h };
		s_FL2_OvClearRect(all);

		RECT rc = { 0, 0, s_fl2_ov_w, s_fl2_ov_h };
		CD3D9Present::UpdateOverlay((const unsigned long*)s_fl2_ov_bits,
		                            s_fl2_ov_w, s_fl2_ov_h, s_fl2_ov_w,
		                            &rc, 1, FL2_FB_COLORKEY);

		s_fl2_ov_prevHiN = 0;
		s_fl2_ov_frameN = s_fl2_ov_checkedN = 0;
		s_fl2_ov_poolN = 0;
		s_fl2_ov_overflow = false;
		return;
	}

	// Frame with no text at all: erase last frame's glyphs from the texture
	// (Begin never ran, so the DIB still holds them).
	if (s_fl2_ov_frameN == 0)
	{
		if (bBegan == false && s_fl2_ov_prevHiN > 0)
		{
			RECT upl[FL2_OV_MAX_UPLOAD];
			int  uplN = 0;

			for (int i = 0; i < s_fl2_ov_prevHiN && uplN < FL2_OV_MAX_UPLOAD; i++)
			{
				s_FL2_OvClearRect(s_fl2_ov_prevHi[i]);
				upl[uplN].left   = s_fl2_ov_prevHi[i].x0;
				upl[uplN].top    = s_fl2_ov_prevHi[i].y0;
				upl[uplN].right  = s_fl2_ov_prevHi[i].x1;
				upl[uplN].bottom = s_fl2_ov_prevHi[i].y1;
				uplN++;
			}

			CD3D9Present::UpdateOverlay((const unsigned long*)s_fl2_ov_bits,
			                            s_fl2_ov_w, s_fl2_ov_h, s_fl2_ov_w,
			                            upl, uplN, FL2_FB_COLORKEY);
			s_fl2_ov_prevHiN = 0;
		}
		// bBegan true with zero regions: Begin already cleared prevHi pixels;
		// fall through to the normal upload below with an empty frame list.
		if (bBegan == false)
		{
			s_fl2_ov_checkedN = 0;
			return;
		}
	}

	// ---- Occlusion verify (per column) ------------------------------------

	// The mouse cursor sprite is composited into the surface after UI text
	// every frame; without an exclusion it would knock out every region it
	// touches. A cursor-sized box around the pointer is excused (crisp text
	// simply draws over the cursor there).
	FL2_DIRTYRECT excl = { 0, 0, 0, 0 };
	bool bExcl = false;
	{
		extern HWND g_hWnd;
		POINT pt;
		if (g_hWnd != NULL && GetCursorPos(&pt) && ScreenToClient(g_hWnd, &pt))
		{
			CDirectDraw::WindowToViewport(pt);
			excl.x0 = pt.x - 12;  excl.y0 = pt.y - 12;
			excl.x1 = pt.x + 52;  excl.y1 = pt.y + 52;
			bExcl = true;
		}
	}

	static FL2_DIRTYRECT s_clr[FL2_OV_MAX_CLEARED];
	int  nClr = 0;
	bool bClrOver = false;

	if (!bFade)
	{
		bool bLocked = false;
		DDSURFACEDESC2 ddsd = {};
		ddsd.dwSize = sizeof(ddsd);

		if (s_fl2_ov_boundSurface != NULL &&
		    SUCCEEDED(s_fl2_ov_boundSurface->Lock(NULL, &ddsd,
		              DDLOCK_READONLY | DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL)))
			bLocked = true;

		for (int i = 0; i < s_fl2_ov_frameN; i++)
		{
			FL2_OVREGION& e = s_fl2_ov_frame[i];

			if (!bLocked || i >= s_fl2_ov_checkedN || e.nSub <= 0)
			{
				FL2_OV_DIAG_INC(supNoBaseline);
				e.failMask = 0xFF;   // no baseline: fully suppressed
				s_FL2_OvClearRect(e.hi);
				if (nClr < FL2_OV_MAX_CLEARED) s_clr[nClr++] = e.hi; else bClrOver = true;
				continue;
			}

			const WORD* base   = (const WORD*)ddsd.lpSurface;
			const int   stride = (int)(ddsd.lPitch / sizeof(WORD));
			const int   loW    = e.lo.x1 - e.lo.x0;

			e.failMask = 0;
			for (int j = 0; j < e.nSub; j++)
			{
				FL2_DIRTYRECT c = e.lo;
				c.x0 = e.lo.x0 + loW * j / e.nSub;
				c.x1 = e.lo.x0 + loW * (j + 1) / e.nSub;

				if (s_FL2_SumRegion(base, stride, c) == e.sub[j])
					continue;

				if (bExcl &&
				    c.x0 < excl.x1 && excl.x0 < c.x1 &&
				    c.y0 < excl.y1 && excl.y0 < c.y1)
					continue;   // the cursor, not a window

				e.failMask |= (BYTE)(1u << j);
				FL2_OV_DIAG_INC(supChecksum);

				FL2_DIRTYRECT h;
				s_FL2_OvColHiRect(e, j, &h);
				s_FL2_OvClearRect(h);
				if (nClr < FL2_OV_MAX_CLEARED) s_clr[nClr++] = h; else bClrOver = true;
			}
		}

		if (bLocked)
			s_fl2_ov_boundSurface->Unlock(NULL);
	}

	// ---- Upload: this frame's regions (cleared ones included, so the
	// texture shows the fallback) plus last frame's, which erase old glyphs.
	{
		RECT upl[FL2_OV_MAX_UPLOAD];
		int  uplN = 0;
		bool bFull = false;

		for (int i = 0; i < s_fl2_ov_frameN + s_fl2_ov_prevHiN && !bFull; i++)
		{
			const FL2_DIRTYRECT& e = (i < s_fl2_ov_frameN)
			                       ? s_fl2_ov_frame[i].hi
			                       : s_fl2_ov_prevHi[i - s_fl2_ov_frameN];

			// Merge into an overlapping/adjacent entry when possible.
			int k;
			for (k = 0; k < uplN; k++)
			{
				if (e.x0 <= upl[k].right && upl[k].left <= e.x1 &&
				    e.y0 <= upl[k].bottom && upl[k].top <= e.y1)
				{
					if (e.x0 < upl[k].left)   upl[k].left   = e.x0;
					if (e.y0 < upl[k].top)    upl[k].top    = e.y0;
					if (e.x1 > upl[k].right)  upl[k].right  = e.x1;
					if (e.y1 > upl[k].bottom) upl[k].bottom = e.y1;
					break;
				}
			}
			if (k == uplN)
			{
				if (uplN >= FL2_OV_MAX_UPLOAD)
				{
					bFull = true;
					break;
				}
				upl[uplN].left   = e.x0;
				upl[uplN].top    = e.y0;
				upl[uplN].right  = e.x1;
				upl[uplN].bottom = e.y1;
				uplN++;
			}
		}

		if (bFull)
		{
			upl[0].left = 0;  upl[0].top = 0;
			upl[0].right = s_fl2_ov_w;  upl[0].bottom = s_fl2_ov_h;
			uplN = 1;
		}

		CD3D9Present::UpdateOverlay((const unsigned long*)s_fl2_ov_bits,
		                            s_fl2_ov_w, s_fl2_ov_h, s_fl2_ov_w,
		                            upl, uplN, FL2_FB_COLORKEY);
	}

	// ---- Rotate: everything mirrored this frame is what next frame must
	// erase (cleared parts are already colorkey; re-clearing is a no-op).
	s_fl2_ov_prevHiN = 0;
	for (int i = 0; i < s_fl2_ov_frameN; i++)
		s_fl2_ov_prevHi[s_fl2_ov_prevHiN++] = s_fl2_ov_frame[i].hi;

	s_fl2_ov_frameN = s_fl2_ov_checkedN = 0;
	s_fl2_ov_poolN = 0;
}
