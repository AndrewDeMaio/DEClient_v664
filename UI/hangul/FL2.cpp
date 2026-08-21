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

// Colorkey: pixels equal to this value in the DIBSection are skipped (transparent)
// during copy-back.  Deliberately unusual to avoid colliding with real colours.
static const DWORD FL2_FB_COLORKEY = 0x00FE01FEu;

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
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);

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
			SelectObject(hdc, p_print_info->hfont);
		}

		TextOut(hdc, x, y, sz_str, str_length);
		if (s_fl2_fb_active) s_fl2_fb_dirty = true;

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
		if (s_fl2_fb_active) s_fl2_fb_dirty = true;

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
	if (s_fl2_fb_dc != NULL)
		return true;   // already initialised

	if (gpC_fl2_surface == NULL)
		return false;

	// Query the surface dimensions and pixel format
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	if (FAILED(gpC_fl2_surface->GetSurfaceDesc(&ddsd)))
		return false;

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

	for (int y = 0; y < s_fl2_fb_h; y++)
	{
		WORD*        dst = dst_base + y * dst_stride;
		const DWORD* src = src_base + y * s_fl2_fb_w;

		for (int x = 0; x < s_fl2_fb_w; x++)
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

	gpC_fl2_surface->Unlock(NULL);
}

bool	g_FL2_GetDC()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (gh_FL2_DC == NULL)
	{
		// Try DirectDraw GetDC first (works on 32-bit surfaces).
		HRESULT hr = gpC_fl2_surface->GetDC(&gh_FL2_DC);
		if (SUCCEEDED(hr))
			return true;

		// GetDC failed – this surface is likely 16-bit (modern Windows limitation).
		// Use the GDI DIBSection fallback instead.
		gh_FL2_DC = NULL;
		if (s_FL2_EnsureFallbackDC())
		{
			// Clear the DIBSection so stale pixels from a previous call don't bleed through.
			int nPx = s_fl2_fb_w * s_fl2_fb_h;
			for (int i = 0; i < nPx; i++)
				s_fl2_fb_bits[i] = FL2_FB_COLORKEY;

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
		s_fl2_fb_dirty = true;
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















