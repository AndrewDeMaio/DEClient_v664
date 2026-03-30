#ifndef __EDITBOX__
#define __EDITBOX__

#include "dialog_base.h"

#define INFINITE_INPUT					-1 // 입력 제한 없음.

/*-----------------------------------------------------------------------------
  Class Edit box
-----------------------------------------------------------------------------*/
class C_EDITBOX : public C_DIALOG
{
private:
	bool				m_bl_focus;
	char *			m_sz_input_string;
	int				m_i_char_count; // 입력되는 문자 수 (8 bit)
	int				m_i_output_index; // 문자열 출력 index
	int				m_i_input_index;  // 문자 입력 index
	static bool		m_bl_cursor;
	int				m_i_cursor_move;
	int				m_i_cursor_gap;

	//
	// 입력을 종료하면(Enter를 누르면) 입력된 문자열을 이 method로 보낸다.
	//
	void				(*m_fp_string_receiver)(char *sz_string);

public:
	bool	PreSetInputedString(const char *str);
	void	SetFocusState(bool state);
	void	SetUnifyFlag();
	char * GetCurrentInputedString();
	void	ToggleCursorState();
	void	SetInputLimit(int char_count);
	void	SetEditLineWidth(int width);
	void	SetSize();
	void	Set_Y(int y);
	void	Set_X(int x);
	void	SetStringReceiver(void (*fp_receiver)(char *));
	void	MouseControl(UINT message, int x, int y);
	void	KeyboardControl(UINT message, UINT key);
	void	Show();
	
	C_EDITBOX();
	~C_EDITBOX();
};

#endif