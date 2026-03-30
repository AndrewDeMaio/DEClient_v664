/*-----------------------------------------------------------------------------

	hangul.h

	한/영 입출력기.

	`공개된 fnt file을 읽는다.
	`한글 = 16x16
	 영문 =  8x16

   `입력은 내부에서 처리한다. 특히 한글일 경우에 이것은 중요한 사항이다. 영문은
	 외부에서 그냥 입력된 buffer를 출력하면 되지만, 한글은 외부에서 입력을 
	 처리해줄 겨우 오토마타의 모든 사항을 정의해야 한다. 하지만 이것은 이미 내부에
	 구현된 사항이다. 따라서 기본적으로 입력을 받는 내부의 라인입력버퍼를 외부에서
	 참조하므로써 그 효과를 대신한다.

	1999.12.27. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __HANGUL_H__
#define __HANGUL_H__

#include <string>
#include <windows.h>
#include "2D.h"
#include "DLL.h"

//----------------------------------------------------------------------------
// EXT_FLAG
// 
// keyboard input시의 extra 인자의 flag로, 이 값이 1이면 오른쪽 ctrl, alt key
// 등이 눌릴 때이다.
//----------------------------------------------------------------------------
#define EXT_FLAG							0x1000000

#define TAB_SIZE							3
#define SYLLABLE							17672

#define HAN_X_SIZE						16
#define HAN_Y_SIZE						16
#define ENG_X_SIZE						8
#define ENG_Y_SIZE						16

#define MSB									0x80

#define XCOL								8

#define FIR_COUNT							(8*20*32) // 초성
#define MID_COUNT							(4*22*32) // 중성
#define END_COUNT							(4*28*32) // 종성
#define ENG_COUNT							(256*16)

typedef std::string STRING;

/*-----------------------------------------------------------------------------
  Class Hangul Mix
-----------------------------------------------------------------------------*/
class C_MIX
{
private:
	void	EndCreate();
	void	ShiftKey(bool vowel);
	void	VoMidCreate();
	void	FirstCreate(bool vowel);
	int	CodeValue(bool vowel);

public:
 	void	MemoryInit(int count);
	void	OrImage(TCHAR *src, int size, int position);

public:
 	BYTE **			m_HanBitmap;    // 한글 비트맵 배열

private:
	//
	//	뷰로 부터 받은 데이다를  임시 보관하여 처리하는 데이타
	//
	// 1999.12.16 KJTINC
	// `m_string은 입력된 모든 한글만 저장한다. 
	//
	static STRING				m_string;
	static TCHAR				m_str;
	static short				m_shift;

	bool				m_no_public_eng;

public:
	BYTE				m_Fir[8][20][32];
	BYTE				m_Mid[4][22][32];
	BYTE				m_End[4][28][32];
	BYTE				m_Eng[256][16];

public:
	C_MIX();
	~C_MIX();

	void		SetNoPublicEngState(bool state);
	short		GetShiftState() const;
	void		SetShiftState(short state);
	STRING	CodeConvert(STRING string, TCHAR str);//, int *index);
	bool		ReadFont(const char *sz_hanfont_name, const char *sz_engfont_name);
	bool		ReadEnglishFont(const char *sz_filename);
	bool		ReadHangulFont(const char *sz_filename);

	static int			m_TabSize;
	static bool			m_PreEng; // 앞에 출력된 글이 한글인지 영문인지를 구분 
};

/*-----------------------------------------------------------------------------
  선형 문자열 입력 라인.
-----------------------------------------------------------------------------*/
class C_STRING_LINE
{
public:
	STRING				str;

	//
	// 입력된 문자의 한/영 여부를 저장한다. 0 = 영, 1 = 한
	// 이것은 문자열을 지울 때 요긴하게 쓰인다.
	// 편의상 string을 쓴다.
	//
	STRING				code;

	void	Init() 
	{ 
		str.erase(); 
		code.erase(); 
	}
};

//
// 현재까지 밝혀진 바(?)로는 '뭙' 등 5가지 입력 경우가 최대이다.
//
#define MAX_CASE_INPUT					5

/*-----------------------------------------------------------------------------
  Class Hangul View
  `Keyboard 입력과 출력을 담당한다.
-----------------------------------------------------------------------------*/
class C_HAN_VIEW 
{
public:
	static bool				m_bl_han_edit_exception; // 한글 보정을 위한 flag.
	static bool				m_bl_han_edit_exception2; // 한글 보정을 위한 flag.
	static bool				m_bl_han_edit_exception3; // 한글 보정의 위한 flag.
	static int				m_cursor_position; // line buffer에서의 cursor 위치
	static bool				m_bl_insert;
	static C_STRING_LINE	m_Row;	//	입력된 string을 임시 저장
	static int				m_han_x;

private:
	static bool				gbl_ext_flag;
	static int				m_cursor_color;
	static int				m_plot_start_code_index;
	static int				m_plot_end_code_index;

	//
	// m_plot_width
	//
	// input line을 제한된 구획(plot)으로 출력할 때 그 구획의 넓이다.
	// 이 plot이 이동하면서 scroll하는 효과를 얻는다.
	//
	static int				m_plot_width;

	static bool				m_bl_cursor; // to blink
	static bool				m_bl_password; // '*'로 해주기 위한..
	static bool				m_bl_nopublic_font_mode; // 비공식영문폰트를 사용할 것인가?
	static WORD				m_input_limit;
	static bool				m_bl_end_of_block;

	//
	// left shift + space bar OR 한/영 key를 눌렀을 때, 한 영 전환을 toggle한다.
	//
	static bool				m_bl_hangle_input;

	C_MIX						m_Mix;
	
	static C_STRING_LINE	m_RowBackup;
	static C_STRING_LINE m_Row_show; // scroll에 의해서 m_Row 대신 이것으로 출력한다.

	//
	// 한글 삭제시 필요한 정보
	//
	// `입력된 code를 저장해서 다시 convert시켜주는 것보다 convert된 한글 code를
	//  저장하는 게 효율적이다.
	// `다음 문자로 넘어가면 m_count_input은 0으로 된다.
	//
	static int				m_count_input; // 몇 번 입력되었는가?
	static char				m_code_save[MAX_CASE_INPUT][2];

	//
	// `'니다'의 경우 '닏'에서 'ㅏ'가 붙어 '닏'은 '니'로 되고 '다'가 만들어진다.
	//  m_last_scan_code는 항상 마지막 scan code를 저장하고 있어 이 경우에 사용한다.
	//
	// `이 처리는 '닏'에서 '니'로 바뀐 경우와 같이 이전 문자가 다음 문자로 인해
	//  변경될 때에만 유효하다.
	//
	static char				m_last_scan_code;
	static short			m_last_shift_state;

	void	ClearCodeSaveBuffer();

public:
	C_HAN_VIEW::C_HAN_VIEW(const char * sz_han_file, const char * sz_eng_file);
	~C_HAN_VIEW();

	inline C_STRING_LINE * GetStringBuffer() const { return &m_RowBackup; }
	inline C_STRING_LINE * GetCurrentInputBuffer() const { return &m_Row; }

	void	ForceShowCursor();
	void	Update(int x, int y, int color);
	void	Update(const S_SURFACEINFO *surface_info, int x, int y, int color);
	void  KeyInput(UINT message, UINT key, long extra);

	void	PrintString(const char *str, int x, int y, int color);
	void  PrintString(const S_SURFACEINFO *surface_info, const char *str, int x, int y, int color);
	static int	BytePosition(int where);

private:
	bool	ConvertScanCodeToAscii(BYTE scan_code, char &ascii);
	bool  ConvertScanCodeToAscii2(BYTE scan_code, char &ascii);
	void	SetPlotEndIndex();
	void	HangulInput(UINT key, BYTE scan_code);
	void	AsciiInput(UINT key);
	void	PrintCharE(const char _char, int x, int y, int color);
	void	PrintCharH(const char *p_char, int x, int y, int color);
	void  _PrintCharH(const char *p_char, int x, int y, int color);
	void	BackSpace();
	void  Delete();
	void	SetShowLineByPlot();
	void	PreviewFrontString();

public:
	void	SetCursorColor(int color) { m_cursor_color = color; }
	void	SetInputLine(const char * sz_str);
	void	CursorPosition(int val);
	void	SetInputWidth(int w) { m_plot_width = w; }
	int	GetWidthFromTo(int from, int to) const;
	void	ClearInputLine();
	void	BlinkCursor() { m_bl_cursor = !m_bl_cursor; }
	bool  GetBlinkCursorState() const { return m_bl_cursor; }
	void  SetInputLimit(WORD char_count);
	bool	GetHangulInputState() const;
	void	SetHangulInputState(bool state);
	void	ToggleHangulInputState();
	static void	WansungToJohap(const char *Wansung, char *Johap);
	static int	JohabToWansung(char * dest, const char *src);

#ifdef _DEBUG
	void	DebugPrint();
#endif

	//
	// font loading interface
	//
	bool	LoadHangulFont(const char *sz_filename);
	bool	LoadEnglishFont(const char *sz_filename);

	inline void	UseNoPublicEngFont() { m_bl_nopublic_font_mode = true; }
	inline void	NotUseNoPublicEngFont() { m_bl_nopublic_font_mode = false; }

	int	GetStringWidth(const char * sz_str) const;
	int	GetHangulCountInString(const char *str) const;
	int	GetEngCountInString(const char *str) const;
	int	GetHangulCountInInputBuffer() const;
	int	GetEngCountInInputBuffer() const;
	void	PasswordMode() { m_bl_password = true; }
	void	NoPasswordMode() { m_bl_password = false; }

	bool	PossibleStringCut(const char * str, int position);
};

#endif
