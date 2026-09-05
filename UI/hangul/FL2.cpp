// FL2.cpp

#include "client_PCH.h"
#include "FL2.h"
#include "VS_UI_Base.h"

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

// Temporary instrumentation - which part of this path actually costs?
static int      s_stAcquire  = 0;	// cold acquires (fallback path)
static int      s_stDdGetDC  = 0;	// acquires that got a real DirectDraw DC instead
static int      s_stDraws    = 0;	// TextOut / DrawText calls
static int      s_stDirtyAll = 0;	// times we gave up and marked the whole surface
static double   s_stClearPx  = 0.0;	// pixels cleared
static double   s_stBlitPx   = 0.0;	// pixels scanned for copy-back
static LONGLONG s_stNext     = 0;

// false = persistent DIBSection DC (fast). true = per-acquire DirectDraw DC.
bool g_bFL2UseSurfaceDC = false;

// Where inside the text path does the time actually go?
static double   s_msAcquire  = 0.0;	// IDirectDrawSurface7::GetDC + ReleaseDC
static double   s_msDraw     = 0.0;	// TextOut / DrawText themselves
static double   s_msMeasure  = 0.0;	// GetTextExtentPoint32
static double   s_msSelect   = 0.0;	// SelectObject (font realisation)
// Split by content: a string containing any byte >= 0x80 needs CJK glyphs.
// If those are missing from the selected face, GDI walks the font-link
// chain on every call - which would hit TextOut and GetTextExtentPoint32
// equally, persist once triggered, and cost far more per character.
static int      s_nAscii     = 0;
static double   s_chAscii    = 0.0;
static double   s_msAscii    = 0.0;
static int      s_nDbcs      = 0;
static double   s_chDbcs     = 0.0;
static double   s_msDbcs     = 0.0;

static LONGLONG s_tick()
{
	LARGE_INTEGER n; QueryPerformanceCounter(&n); return n.QuadPart;
}

static double s_ms(LONGLONG d)
{
	LARGE_INTEGER f; QueryPerformanceFrequency(&f);
	return (double)d * 1000.0 / (double)f.QuadPart;
}

static void s_FL2_Stats()
{
	LARGE_INTEGER f, n;
	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&n);

	if (s_stNext == 0) { s_stNext = n.QuadPart; return; }

	const double ms = (double)(n.QuadPart - s_stNext) * 1000.0 / (double)f.QuadPart;
	if (ms < 5000.0) return;

	FILE* fp = fopen("fl2_probe.log", "a");
	if (fp)
	{
		fprintf(fp, "ascii n=%6d ch=%8.0f ms=%8.1f (%6.2fus/ch) | dbcs n=%6d ch=%8.0f ms=%8.1f (%7.2fus/ch) | meas=%7.1f acq=%6.1f\n",
			s_nAscii, s_chAscii, s_msAscii,
			(s_chAscii > 0.0) ? (s_msAscii * 1000.0 / s_chAscii) : 0.0,
			s_nDbcs, s_chDbcs, s_msDbcs,
			(s_chDbcs > 0.0) ? (s_msDbcs * 1000.0 / s_chDbcs) : 0.0,
			s_msMeasure, s_msAcquire);
		fclose(fp);
	}

	s_stAcquire = s_stDdGetDC = s_stDraws = s_stDirtyAll = 0;
	s_stClearPx = s_stBlitPx = 0.0;
	s_msAcquire = s_msDraw = s_msMeasure = s_msSelect = 0.0;
	s_nAscii = s_nDbcs = 0;
	s_chAscii = s_chDbcs = s_msAscii = s_msDbcs = 0.0;
	s_stNext = n.QuadPart;
}
// Colorkey: pixels equal to this value in the DIBSection are skipped (transparent)
// during copy-back.  Deliberately unusual to avoid colliding with real colours.
static const DWORD FL2_FB_COLORKEY = 0x00FE01FEu;

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
	s_stDirtyAll++;
	s_fl2_curN = 0;
	s_FL2_AddRect(s_fl2_cur, s_fl2_curN, 0, 0, s_fl2_fb_w, s_fl2_fb_h);
}

// Bounds of a TextOut, honouring the DC's current alignment.
static void s_FL2_DirtyTextOut(HDC hdc, int x, int y, const char* psz, int len)
{
	SIZE sz = { 0, 0 };

	if (psz == NULL || len <= 0 || !GetTextExtentPoint32(hdc, psz, len, &sz))
	{
		s_FL2_DirtyAll();	// cannot bound it - stay correct
		return;
	}

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
		s_FL2_Dirty(l, y - sz.cy, l + sz.cx, y + sz.cy / 2);
		return;
	}

	const int t = (v == TA_BOTTOM) ? (y - sz.cy) : y;

	s_FL2_Dirty(l, t, l + sz.cx, t + sz.cy);
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

			s_stClearPx += (double)(e.x1 - e.x0);
		}
	}

	s_fl2_prevN = 0;
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
		SelectObject(hdc, hfont);

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, Index, &size);

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
		SelectObject(hdc, hfont);

	SIZE size;
	const LONGLONG _m0 = s_tick();
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);
	s_msMeasure += s_ms(s_tick() - _m0);

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
		SelectObject(hdc, hfont);

	SIZE size;
	const LONGLONG _m0 = s_tick();
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);
	s_msMeasure += s_ms(s_tick() - _m0);

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
			const LONGLONG _s0 = s_tick();
			SelectObject(hdc, p_print_info->hfont);
			s_msSelect += s_ms(s_tick() - _s0);
		}

		s_stDraws++;
		if (s_fl2_fb_active) s_FL2_EnsureCleared();

		// Any high byte means the string needs glyphs outside plain Latin.
		bool _bDbcs = false;
		for (int _i = 0; _i < str_length; _i++)
		{
			if ((unsigned char)sz_str[_i] >= 0x80) { _bDbcs = true; break; }
		}

		const LONGLONG _d0 = s_tick();
		TextOut(hdc, x, y, sz_str, str_length);
		const double _dms = s_ms(s_tick() - _d0);

		s_msDraw += _dms;

		if (_bDbcs) { s_nDbcs++;  s_chDbcs  += (double)str_length; s_msDbcs  += _dms; }
		else        { s_nAscii++; s_chAscii += (double)str_length; s_msAscii += _dms; }

		if (s_fl2_fb_active)
		{
			s_fl2_fb_dirty = true;
			s_FL2_DirtyTextOut(hdc, x, y, sz_str, str_length);
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
			SelectObject(hdc, p_print_info->hfont);
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
		return;

	WORD*        dst_base   = (WORD*)ddsd.lpSurface;
	int          dst_stride = (int)(ddsd.lPitch / sizeof(WORD));
	const DWORD* src_base   = s_fl2_fb_bits;

	for (int r = 0; r < s_fl2_curN; r++)
	{
	const FL2_DIRTYRECT& _e = s_fl2_cur[r];

	s_stBlitPx += (double)(_e.x1 - _e.x0) * (double)(_e.y1 - _e.y0);

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
			const LONGLONG _a0 = s_tick();
			HRESULT hr = gpC_fl2_surface->GetDC(&gh_FL2_DC);
			s_msAcquire += s_ms(s_tick() - _a0);

			if (SUCCEEDED(hr))
			{
				s_stDdGetDC++;
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
			s_stAcquire++;

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
			const LONGLONG _r0 = s_tick();
			gpC_fl2_surface->ReleaseDC(gh_FL2_DC);
			s_msAcquire += s_ms(s_tick() - _r0);
		}

		s_FL2_Stats();
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















