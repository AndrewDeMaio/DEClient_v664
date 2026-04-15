/*-----------------------------------------------------------------------------

	sora_monitor.h
	// monitor.h visual c include에 있음 !-.-

	App state monitor.

	`error or 성공 message의 출력 및 저장 특정 변수의 출력 등등 App 개발 및
	 상황판단에 필요한 정보를 제공한다. 또한 간단한 명령행을 제공한다.

   `이것은 UI library를 사용하는 App이면 사용할 수 있다.

	2000.2.28. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __SORA_MONITOR_H__
#define __SORA_MONITOR_H__

#include "UI.h"
#include "sora_monitor_def.h"

/*-----------------------------------------------------------------------------
  Class Monitor
  `Monitor View의 계속적인 update로 인해 모든 line의 data를 저장해야 한다.
-----------------------------------------------------------------------------*/
class C_MONITOR
{
private:
	enum { ROW = 25, COL = 80 }; // default...

	int			m_line_count; // 화면크기로 인해 가변일 수 있음.
	char **		m_p_line_buf;
	char *		m_p_command_line_buf;

	int			m_cursor_x; // command-line cursor 위치
	int			m_cursor_y; // cursor의 line 위치

	//
	// Command registration
	//
	struct S_COMMAND
	{
		char *sz_command;
		void	(*fp_exec)(void);
	};

	int			m_command_count; // 등록된 command 개수
	S_COMMAND *	m_pS_command_list;

	void	ParseCommand();
	void	InputChar(const char c);
	void	BackSpace();
	void	ExecCommand();
	void	ClearScreen();
	void	ClearCommandLine();

public:
	C_MONITOR();
	~C_MONITOR();

/*-----------------------------------------------------------------------------
  Internal(built-in) method
-----------------------------------------------------------------------------*/
	void	Print(const char * str);

/*-----------------------------------------------------------------------------
  Command & Exec method registration
-----------------------------------------------------------------------------*/
	void	RegisterCommand(const char * command, void (*fp_exec)(void));

/*-----------------------------------------------------------------------------
  friends
-----------------------------------------------------------------------------*/
	friend void UI_KeyboardControl_Monitor(UINT message, UINT key);
	friend void UI_ClientUpdate_Monitor();
	friend void UI_ScrollResultReceiverY_Monitoring(const S_RESULT_SCROLL &S_result_scroll);
	friend void MakeMonitor();

	// built-in command
	friend void Clear();
	friend void ShowCommandList();
};

/*-----------------------------------------------------------------------------
  Extern
-----------------------------------------------------------------------------*/
extern WINDOW_ID		g_wid_monitor;
extern C_MONITOR		gC_monitor;

#endif