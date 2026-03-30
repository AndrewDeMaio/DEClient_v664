/*-----------------------------------------------------------------------------

	FontManager.h

	Load된 여러개의 font를 효과적으로 관리하기 위한 것이다.
	이것은 font의 복수 등록, 등록시킨 font를 선택해서 문자 출력하기 등을 지원한다.

	2000.1.7. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include "hangul.h"
#include "font.h"
#include "directory.h"
#include "timer2.h"
#include "DLL.h"

#define FILE_DEBUG

#ifdef FILE_DEBUG
#include <fstream>
#endif

//#define _WINAPP_TEST // Window mode test를 위해.

//#define RELEASE_FONT

#define FONT_PATH						"\\data\\font\\"

/*-----------------------------------------------------------------------------
  Font Full Path
-----------------------------------------------------------------------------*/
/*
//#ifndef RELEASE_FONT
#if !defined(RELEASE_FONT)

#define PATH_CODE						"d:\\designed\\project\\fl\\font\\code.dat"

#define PATH_MYUNGJO					"d:\\designed\\project\\fl\\font\\han02.fnt"
#define PATH_IYAGI					"d:\\designed\\project\\fl\\font\\han01.fnt"
#define PATH_GOOLRIM					"d:\\designed\\project\\fl\\font\\han10.fnt"
#define PATH_PILGI					"d:\\designed\\project\\fl\\font\\han03.fnt"
#define PATH_MOLRA7					"d:\\designed\\project\\fl\\font\\han21.fnt"
#define PATH_SALBERL					"d:\\designed\\project\\fl\\font\\han55.fnt"
#define PATH_CUTE						"d:\\designed\\project\\fl\\font\\han54.fnt"
#define PATH_HSMALL					"d:\\designed\\project\\fl\\font\\hsmall(12x12).fnt"

#define PATH_ENG1						"d:\\designed\\project\\fl\\font\\eng01.fnt"
#define PATH_ENG2						"d:\\designed\\project\\fl\\font\\eng02.fnt"
#define PATH_ENG3						"d:\\designed\\project\\fl\\font\\eng03.fnt"
#define PATH_ENG7						"d:\\designed\\project\\fl\\font\\eng07.fnt"
#define PATH_JORRO					"d:\\designed\\project\\fl\\font\\eng-zorro.fnt"
#define PATH_MERT						"d:\\designed\\project\\fl\\font\\eng20.fnt"
#define PATH_ESMALL					"d:\\designed\\project\\fl\\font\\eng24.fnt"

#else*/

#define PATH_CODE						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"code.dat")

#define PATH_MYUNGJO					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han10.fnt")
#define PATH_IYAGI					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han01.fnt")
#define PATH_GOOLRIM					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han10.fnt")
#define PATH_PILGI					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han03.fnt")
#define PATH_MOLRA7					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han21.fnt")
#define PATH_SALBERL					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han55.fnt")
#define PATH_CUTE						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"han54.fnt")
#define PATH_HSMALL					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"hsmall(12x12).fnt")

#define PATH_ENG1						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng01.fnt")
#define PATH_ENG2						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng02.fnt")
#define PATH_ENG3						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng03.fnt")
#define PATH_ENG7						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng07.fnt")
#define PATH_JORRO					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng-zorro.fnt")
#define PATH_MERT						gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng20.fnt")
#define PATH_ESMALL					gC_directory.GetMixedPathWidthProgramDir(FONT_PATH"eng24.fnt")

//#endif

/*-----------------------------------------------------------------------------
  Font Group Id
  `(한글, 영어)가 하나의 group이 되어 객체로 존재하게된다. 글꼴의 등록도 
   group 단위로 하게 된다. 등록을 하면 id를 받아 이것으로 font group을 선택할
	수 있다.
-----------------------------------------------------------------------------*/
typedef short FONT_GID;


/*-----------------------------------------------------------------------------
  Class Font Manager
-----------------------------------------------------------------------------*/
class DllClass C_FONT_MANAGER
{
public:
	enum 
	{ 
		NO_GID = -1,
		TOTAL_FONT_GROUP_COUNT = 5, // 한 번에 등록할 수 있는 font group. 여기서 제한 해줌.
	};

private:
	FONT_GID				m_selected_gid;

	int					m_total; // 현재까지 등록된 font group.
	C_HAN_VIEW *		m_pC_han_view[TOTAL_FONT_GROUP_COUNT];

public:
	static timer_id_t		m_tid_cursor_blink; // C_HAN_VIEW에서 참조하므로...

	enum HFONT_NAME
	{
		MYUNGJO,	// 명조체
		IYAGI,	// 이야기체
		GOOLRIM,	// 굴림체
		PILGI,	// 필기체
		MOLRA7,	// 몰라체 7
		SALBERL,	// 살벌체
		HSMALL,	// 12x12 둥근글꼴
		CUTE,		// 귀염체
	};

	enum EFONT_NAME
	{
		NAPLES,	// 비공식 영문 폰트
		OLIVE,	// 비공식 영문 폰트

		ENG1,		// 이름 모름...
		ENG2,
		ENG3,
		ENG7,
		JORRO,	// 조로체
		ESMALL,	// 8x16 아주작은 체
		MERT,		// 멋체^^
	};

public:
	C_FONT_MANAGER();
	~C_FONT_MANAGER();

	void	Initialize();

	FONT_GID RegisterFont(C_FONT_MANAGER::HFONT_NAME e_hfontname, 
								 C_FONT_MANAGER::EFONT_NAME e_efontname);
	bool	LoadEnglishFont(const char *sz_filename);
	bool	LoadHangulFont(const char *sz_filename);

	bool	SelectFont(FONT_GID gid);
	void	PrintString(const S_SURFACEINFO *surface_info, const char *str, int x, int y, int color);
	void	PrintStringNoConvert(const S_SURFACEINFO *surface_info, const char *str, int x, int y, int color);
	void	Update(const S_SURFACEINFO *surface_info, int x, int y, int color);
	void	Update(int x, int y, int color); // to test this library
	//void	PauseCursorBlink();
	void	ContinueCursorBlink();
	void	InitCursorTimer();
	void	ClearInputLine();
	void	ForceShowCursor();

#ifdef _DEBUG
	void	DebugPrint()
	{
		if (m_total > 0)
		{
			m_pC_han_view[0]->DebugPrint();
		}
	}
#endif

/*-----------------------------------------------------------------------------
  Input Control.
-----------------------------------------------------------------------------*/
	void  KeyInput(UINT message, UINT key, long extra);

/*-----------------------------------------------------------------------------
  Get.
-----------------------------------------------------------------------------*/
	int	GetStringWidth(const char * sz_str) const;
	FONT_GID	GetSelectedGID() const { return m_selected_gid; }
	bool	GetHangulInputState() const;
	int   GetEngCountInString(const char *str) const;
	int   GetHangulCountInString(const char *str) const;
	bool	PossibleStringCut(const char * str, int position);

	C_STRING_LINE * GetStringBuffer() const;
	C_STRING_LINE * GetStringBackupBuffer() const;

/*-----------------------------------------------------------------------------
  Set.
-----------------------------------------------------------------------------*/
	void	SetCursorColor(int color);
	void	SetInputLimit(WORD char_count);
	void	SetInputWidth(WORD width);
	void	UseNoPublicEng(E_FONTNAME fontname);
	void	NotUseNoPublicEng();
	void	ToggleHangulInputState();
	void	PasswordMode();
	void	NoPasswordMode();
	void	PutCursorToEnd();
	void	SetInputLine(const char * sz_str);
	void	UseSmallHangul() { C_HAN_VIEW::m_han_x = 12; }
	void	NotUseSmallHangul() { C_HAN_VIEW::m_han_x = HAN_X_SIZE; }

/*-----------------------------------------------------------------------------
  Friend.
-----------------------------------------------------------------------------*/
	friend void BlinkCursor();
};

/*-----------------------------------------------------------------------------
  EXTERN
-----------------------------------------------------------------------------*/
extern void BlinkCursor();

#endif