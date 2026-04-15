#ifndef __SINGLEMENU__
#define __SINGLEMENU__

#include "dialog_base.h"
#include "ui_setup.h"

//
// `실행 id 없음.
//
#define NO_EXEC_ID						0

/*-----------------------------------------------------------------------------
  메뉴 선택 가능/불가능 옵션
-----------------------------------------------------------------------------*/
typedef enum
{
	SELECT_DISABLE,
	SELECT_ABLE,
	SELECT_NO_CHANGE,

} E_SELECT_OPTION;

/*-----------------------------------------------------------------------------
  Menu Toggle option
-----------------------------------------------------------------------------*/
typedef enum
{
	TOGGLE_NOTSET,	// no toggle - default
	TOGGLE_ON,		// check
	TOGGLE_OFF,		// no check

} E_TOGGLE_OPTION;

/*-----------------------------------------------------------------------------
  메뉴 항목 구조체
-----------------------------------------------------------------------------*/
class C_SINGLEMENU;

typedef struct
{
	E_SELECT_OPTION	option;
	EXEC_ID				exec_id;				// execution id
	char *		      p_str;
	bool					bl_is_submenu;
	C_SINGLEMENU *		pC_singlemenu;
	bool					bl_toggle_mode;	// toggle이 가능한가?
	bool					bl_toggle;			// toggle state

} S_SINGLEMENU_ITEM;

/*-----------------------------------------------------------------------------
  Single-Menu Class

  `각 Method에 대한 설명은 함수 정의 부분에 있음(일부 제외). 
-----------------------------------------------------------------------------*/
class C_SINGLEMENU : public C_DIALOG
{
private:
	bool GetSubMenuShowState(UINT n);
	void ExecMenuItem() const;
	void GetSelectionBarRect(S_RECT *S_rect, UINT item_num) const;

	bool					m_bl_is_toggle; // toggle mode가 하나라도 있으면 set - 속도를 위해 저장하고 있음.

	S_SINGLEMENU_ITEM	*m_pS_item;
	UINT				   m_u_item_count;			// count of total item
	UINT				   m_u_item_input_count;		// current count of a item input
   UINT              m_u_item_pointer; // 선택된 항목의 item

   //
   // m_fp_exec_item_id
   // `function pointer for user item exection
   // `Global로 놓지 않는 이유는, 모든 메뉴가 한 Mehtod에서 처리되게 하면
	//  문제가 발생하기 때문이다. 만약 UI시스템에서 하나의 시스템 메뉴를 항상 
	//  존재하게 한다면, 사용자가 이 라이브러리를 사용하여 메뉴객체를 만들 때
	//  그 Method에 추가해야 하기 때문이다. 또는 새로 정의한다면 시스템은 
	//  망가지게 된다.
	//
   void     (*m_fp_exec_item_id)(EXEC_ID); 

public:
	void		ResetSubMenuCoordinates() const;
	bool		GetSubMenuState(UINT n) const { return m_pS_item[n].bl_is_submenu; }
	bool		GetToggleModeState(UINT n) const { return m_pS_item[n].bl_toggle_mode; }
	bool		AttachSubMenu(UINT n, C_SINGLEMENU *pC_singlemenu);
	EXEC_ID	GetExecID(UINT n) const { return m_pS_item[n].exec_id; }
	bool		ChangeSingleMenuItemOption(EXEC_ID exec_id, E_SELECT_OPTION option, int new_toggle);
	bool		SetItemIDExecFpointer(void (*fp_item_exec)(EXEC_ID));
	void		ClearItemPointer() { m_u_item_pointer = 0; }
	void		SetHeight(int newh) { m_h = newh; }
	void		SetWidth(int neww) { m_w = neww; }
	int		GetStringStartY() const { return DIALOG_STRING_DEFAULT_GAP; }
	int		GetStringStartX() const { return DIALOG_STRING_DEFAULT_GAP; }
	int		Get_MostItemStrW() const;
	UINT		GetItemCount() const { return m_u_item_input_count; }
	int		GetY_of_Dialog() const { return m_y; }
	int		GetX_of_Dialog() const { return m_x; }
	void		MouseControl(UINT message, int mx, int my);
	void		KeyboardControl(UINT message, UINT key);
	void		Show();
	void		AddItem(char *p_str, E_SELECT_OPTION option, EXEC_ID exec_id, E_TOGGLE_OPTION toggle);

	C_SINGLEMENU(int count);
	~C_SINGLEMENU();
};

#endif