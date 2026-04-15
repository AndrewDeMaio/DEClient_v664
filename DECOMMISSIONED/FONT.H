/*-----------------------------------------------------------------------------

	font.h

	비공식 영문 폰트 header file.

	19990309. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __FONT__
#define __FONT__

#include "2d.h"
#include "DLL.h"

typedef enum
{
	//SYSTEM = 1,
	NAPLES,
   OLIVE,
	// ...
} E_FONTNAME;

//
// `0은 더 이상 작아질 수 없는 최소크기를 의미한다. 이것은 현재 저장되어 있는
//  size를 가리킨다.
//
#define DEFAULT_FONTSIZE		0

//
// `Font info.
//
typedef struct
{
	E_FONTNAME	e_fontname;
	int			i_font_size;

} S_FONT;

/*-----------------------------------------------------------------------------
  EXTERNS
-----------------------------------------------------------------------------*/
extern S_FONT gS_font;

/*-----------------------------------------------------------------------------
  PUBLIC FUNCTIONS
-----------------------------------------------------------------------------*/
DllExport void	SetFont(E_FONTNAME font);
void	SetFontSize(int new_size);
DllExport void	PrintString(const S_SURFACEINFO *info, int x, int y, const char *str, int color);
DllExport int	GetSelectedFontHeight();
int	GetStringWidth(const char *str);

DllExport E_FONTNAME GetPrevSetFontName();

#endif