#ifndef __PULLDOWNMENU__
#define __PULLDOWNMENU__

#include "dialog_base.h"
#include "singlemenu.h"

#define NOT_ARRANGE						0
#define FIRST_MENU						-1
#define LAST_MENU							0xFFFF

/*-----------------------------------------------------------------------------
  Menu item 추가 index.
-----------------------------------------------------------------------------*/
typedef enum 
{
	FILE_MENU,
	OPTION_MENU,
	HELP_MENU,

} E_ADD_INDEX;

/*-----------------------------------------------------------------------------
  S_ADD_SYSPULLDOWNMENU_ITEM
-----------------------------------------------------------------------------*/
typedef struct
{
	E_ADD_INDEX			e_add_index;
	char *				sz_title;
	EXEC_ID				exec_id;
	bool					bl_front; // 앞에 추가?
	E_TOGGLE_OPTION	toggle;

} S_ADD_SYSPULLDOWNMENU_ITEM;

class C_WINDOW;

/*-----------------------------------------------------------------------------
  C_PULLDOWNMENU

  `실제적인 메뉴는 single-menu의 것을 이용한다.
-----------------------------------------------------------------------------*/
class C_PULLDOWNMENU : public C_DIALOG
{
private:
	enum // menu item select gap
	{
		SELECT_GAP_LEFT = 8,
		SELECT_GAP_RIGHT = 8,
		SELECT_GAP_UP = 3,
		SELECT_GAP_DOWN = 2,
	};

	bool	m_bl_open_push;

	int	m_i_not_arrange_count;
	int	m_i_menu_count;
	int	m_i_selected_menu;
	int	m_i_focused_menu;

	struct S_PULLDOWN_MENUITEM
	{
		int				str_start_x;
		char *			m_pp_title;
		C_WINDOW *		pC_window;	// singlemenu Window
		int				i_priority; // 출력 우선순위. 같으면 먼저 들어온 것을 먼저 출력한다.
	} *m_pS_menu;

public:
	void ClearSelectedMenu();
	void ClearFocusedInfo();
	void SetSize();
	void AddMenuTitle(char *sz_title, C_WINDOW *pC_window, int priority);
	void MouseControl(UINT message, int x, int y);
	void KeyboardControl(UINT message, UINT key);
	void Show();

	C_PULLDOWNMENU();
	~C_PULLDOWNMENU();
};

#endif