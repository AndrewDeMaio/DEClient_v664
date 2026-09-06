/*-----------------------------------------------------------------------------

	FL2.h

	FL2 master header file.

	2000.10.4. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __FL2_H__
#define __FL2_H__

#include "CI.h"
#include <string>
#include <ddraw.h>

void g_SetFL2Surface(LPDIRECTDRAWSURFACE7 surface);

extern LPDIRECTDRAWSURFACE7	gpC_fl2_surface;
extern HDC gh_FL2_DC;

struct PrintInfo
{
	HFONT		hfont;
	COLORREF	text_color;
	COLORREF	back_color;
	int			bk_mode;
	UINT		text_align;
};

//----------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------
int		g_DBCSLen(const char_t* p_dbcs);
int		g_GetByteLenth(const char_t* p_dbcs, int dbcs_len);

int		g_Convert_DBCS_Ascii2SingleByte(const char_t* p_dbcs, int dbcs_len, char*& p_new_buf);
int		g_ConvertAscii2DBCS(const char* p_ascii, int ascii_len, char_t*& p_new_buf);

void	g_PrintLen(int x, int y, const char* sz_str, int str_length, PrintInfo* p_print_info);
void	g_DrawText(RECT* pRt, const char* sz_str, PrintInfo* p_print_info = nullptr);

int		g_GetStringWidth(const char* sz_str, HFONT hfont = nullptr);

//Index������ ���ڿ� ���� Ȯ��.
int		g_GetStringWidth2(const char* sz_str, int Index, HFONT hfont);
int		g_PrintColorStr2(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, int LimitWidth);
int		g_GetStringIndexByWidth(const char* sz_str, int Width, HFONT hfont);
//-

int		g_GetStringHeight(const char* sz_str, HFONT hfont = nullptr);
bool	g_PossibleStringCut(const char* sz_str, int position);

bool	g_FL2_GetDC();
bool	g_FL2_ReleaseDC();
void	g_FL2_MarkDirty();  // mark fallback DC dirty after direct GDI drawing

// Native-resolution text overlay (see FL2.cpp). Flush is registered as the
// CDirectDraw::Flip callback; TextOutMirrored replaces raw TextOut calls in
// widgets that draw straight into gh_FL2_DC.
void	g_FL2_OverlayFlush();
void	g_FL2_SetOverlayEnabled(bool bEnable);
void	g_FL2_OverlaySkipFrames(int nFrames);
void	g_FL2_OverlaySetFadeAlpha(int nAlpha255);
void	g_FL2_TextOutMirrored(HDC hdc, int x, int y, const char* psz, int len);
bool	g_FL2_CaretMirrored(HDC hdc, int xBase, int yBase, const char* psz, int len, COLORREF color);

void	ReduceString(char* str, int len);
void	ReduceString2(char* str, int len);
void	ReduceString3(char* str, int len);

int		g_PrintColorStrLen(int x, int y, const char* sz_str, int str_length, PrintInfo& pi, COLORREF str_rgb);
int		g_PrintColorStrOut(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, COLORREF out_rgb);
int		g_PrintColorStrShadow(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb, COLORREF shadow_rgb = 0xFFFFFFFF);

std::string g_GetNumberString(int number);
std::string g_GetStringByMoney(DWORD dwMoney);
std::string g_MakeLinefeedString(char* sz_src, int linewidth, HFONT hfont);

// g_PrintLen�� ���ڿ� ���̸� �ڵ����� ������ش�.
inline void g_Print(int x, int y, const char* sz_str, PrintInfo* p_print_info = nullptr)
{
	g_PrintLen(x, y, sz_str, strlen(sz_str), p_print_info);
}

// g_PrintColorStrLen�� ���ڿ� ���̸� �ڵ����� ������ش�.
inline int g_PrintColorStr(int x, int y, const char* sz_str, PrintInfo& pi, COLORREF str_rgb)
{
	return g_PrintColorStrLen(x, y, sz_str, strlen(sz_str), pi, str_rgb);
}

#endif