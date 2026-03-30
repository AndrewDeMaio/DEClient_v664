#ifndef __WINDOW__
#define __WINDOW__

#include "core.h"
#include "GL_import.h"
#include "dialog_base.h"

#define NOT_FOCUS_INDEX					-1

/*-----------------------------------------------------------------------------
  E_WHEREFRAME
  `Coordinates system을 위한 부가 정보
-----------------------------------------------------------------------------*/
typedef enum
{
   WF_NO,
   WF_LEFT,
   WF_RIGHT,
   WF_UP,
   WF_DOWN,
   WF_LEFTUP,
   WF_LEFTDOWN,
   WF_RIGHTUP,
   WF_RIGHTDOWN,

} E_WHEREFRAME;

/*-----------------------------------------------------------------------------
  Window 자체의 정교한 처리를 위한 좌표입력반응시스템 구조체
  `이것은 C_WINDOW와 분리한다(global). 따라서 이것은 어떤 C_WINDOW와 반응하고 
   있는지 파악하기 위해 windowhandle을 포함하여야 한다.
  `windowhandle은 2가지이다. 버튼이 push된 상태에서 마우스 포인터를 이동하여
   다른 Window의 버튼을 가리킬 수 있다. any_windowhandle_pushed은 눌린 버튼을
   포함하는 windowhandle이고, any_windowhandle_indicated는 마우스 포인터가 
   위치한 windowhandle이다.
-----------------------------------------------------------------------------*/
typedef struct
{
   WINDOWHANDLE   any_windowhandle_pushed;
   WINDOWHANDLE   any_windowhandle_indicated;
   bool           is_in_mbutton;  // minimize button에 있다.
   bool           is_in_cbutton;  // close button에 있다. 
	bool				is_in_maximize;
   bool           is_in_frame_left;    // window frame에 있다. -window size 변경시-
   bool           is_in_frame_right;
   bool           is_in_frame_up;
   bool           is_in_frame_down;
   bool           is_in_frame_leftup_edge; // 왼쪽 위 모서리
   bool           is_in_frame_leftdown_edge; // 왼쪽 아래 모서리
   bool           is_in_frame_rightup_edge; // 오른쪽 위 모서리
   bool           is_in_frame_rightdown_edge; // 오른쪽 아래 모서리
   bool           is_in_frame_edge_vertical; // edge 부가 정보
   bool           is_in_frame_edge_horizon; // edge 부가 정보
   bool           bl_mb_flag; // for minimize button
   bool           bl_cb_flag; // for close button
	bool				bl_maximize_flag; // for maximize button
   bool           bl_push; // for Window movement
   bool           bl_cb_push; // for close button
   bool           bl_mb_push; // for minimize button
	bool				bl_maximize_push; // for maximize button
   bool           bl_push_for_resize; // for Window resizing
   E_WHEREFRAME   e_whereframe;

} S_COORDISYSTEM;

/*-----------------------------------------------------------------------------
  Window 생성 정보 구조체
-----------------------------------------------------------------------------*/
typedef struct
{
   int   x, y;             // (x, y)
   int   w, h;             // width, height
   char *title_str;        // title bar string
   bool  titlebar;         // titlebar 유무 결정
   bool  button;           // system button 유무 결정 
   bool  movable;          // 이동 가능 유무 결정 
   bool  sequence_apply;   // 우선순위 적용 결정
   bool  resize;           // Window resize 가능 여부

} S_WINDOW_MAKEINFO;

/*-----------------------------------------------------------------------------
- BF_WINDOW_OPTION
- Window option
-----------------------------------------------------------------------------*/
typedef struct
{
	DWORD	movable		:		1;	// Movable window option
	DWORD	sequence	   :		1;	// 우선순위 적용 option
   DWORD resize      :     1; // resize option

} BF_WINDOW_OPTION;

/*-----------------------------------------------------------------------------
- BF_OPTION_BUTTON
- window button option
-----------------------------------------------------------------------------*/
typedef struct 
{
	DWORD	close		   :		1;
	DWORD	minimize	   :		1;
	DWORD	iconize		:		1;

} BF_OPTION_BUTTON;

/*-----------------------------------------------------------------------------
- BF_DIALOGINFO
- dialogs information 
-----------------------------------------------------------------------------*/
typedef struct  
{
	DWORD	textbutton	:		1; // 1
	DWORD	iconcontrol	:		1; // 2
	DWORD radiobutton	:		1; // 3
	DWORD	checkbox	   :		1; // 4
	DWORD	listbox		:		1; // 5
	DWORD	outputbox	:		1; // 6
	DWORD	editbox		:		1; // 7
	DWORD	spinbox		:		1; // 8
	DWORD	scrollbar	:		1; // 9
	DWORD	scrollbar2	:		1; // 9+
	DWORD	singlemenu	:		1; // 10
	DWORD	pulldownmenu:		1; // 11
	DWORD treecontrol :		1; // 12
	DWORD combobox		:		1; // 13
	DWORD statictext	:		1; // 14

} BF_DIALOGINFO;

/*-----------------------------------------------------------------------------
- S_DIALOG_HANDLE_ID
- 각각의 구조체 맴버 포인터는 해당하는 handle id들의 의 선두를 가리킨다. 이것은
  m_S_dialog_count를 참조하여 해당 대화상자를 참조한다.
-----------------------------------------------------------------------------*/
typedef struct 
{
	HANDLEID	*p_textbutton;
	HANDLEID	*p_iconcontrol;
	HANDLEID	*p_radiobutton;
	HANDLEID	*p_checkbox;
	HANDLEID	*p_listbox;
	HANDLEID	*p_outputbox;
	HANDLEID	*p_editbox;
	HANDLEID	*p_spinbox;
	HANDLEID	*p_scrollbar;
	HANDLEID	*p_scrollbar2;
	HANDLEID	*p_singlemenu;
	HANDLEID	*p_pulldownmenu;
	HANDLEID *p_treecontrol;
	HANDLEID *p_combobox;
	HANDLEID *p_statictext;

} S_DIALOG_HANDLE_ID;

/*-----------------------------------------------------------------------------
- S_DIALOG_COUNT
- 대화상자들의 개수를 나타낸다. 
-----------------------------------------------------------------------------*/
typedef struct 
{
	int	textbutton;
	int	iconcontrol;
	int	radiobutton;
	int	checkbox;
	int	listbox;
	int	outputbox;
	int	editbox;
	int	spinbox;
	int	scrollbar;
	int	scrollbar2;
	int	singlemenu;
	int	pulldownmenu;
	int	treecontrol;
	int	combobox;
	int	statictext;

} S_DIALOG_COUNT;

/*-----------------------------------------------------------------------------
  Parent Window인가 Child Window인가?
-----------------------------------------------------------------------------*/
typedef enum
{
	ME_SOLO,
	ME_PARENT, // me? Jin-Tae...^^
	ME_CHILD,
} E_WHO_AM_I;

class C_SINGLEMENU;
class C_OUTPUTBOX;
class C_LISTBOX;
class C_TREE_CONTROL;
class C_ICON_CONTROL;

/*-----------------------------------------------------------------------------
  Window Class

  `각 Method에 대한 설명은 함수 정의 부분에 있음(일부 제외). 
  `Dialog에 관련된 Method는 dialog또는 Dialog라는 문자열을 포함한다.
-----------------------------------------------------------------------------*/
class C_WINDOW
{
private:
	void ResizeDown(int my);
	void ResizeUp(int my);
	void ResizeRight(int mx);
	void ResizeLeft(int mx);
	bool Test_FrameRightUpEdge_Coordinates(int mx, int my) const;
   bool Test_FrameRightDownEdge_Coordinates(int mx, int my) const;
	bool Test_FrameLeftDownEdge_Coordinates(int mx, int my) const;
	bool Test_FrameLeftUpEdge_Coordinates(int mx, int my) const;
	bool Test_FrameLeft_Coordinates(int mx, int my) const;
	bool Test_FrameRight_Coordinates(int mx, int my) const;
	bool Test_FrameDown_Coordinates(int mx, int my) const;
	bool Test_FrameUp_Coordinates(int mx, int my) const;
	bool TestClosePosition(int mx, int my) const;
   bool TestMinimizePosition(int mx, int my) const;
	bool TestMaximizePosition(int mx, int my) const;
   bool Test_Titlebar_Coordinates(int mx, int my) const;

	//
	// `이동시 함께 이동되어야할 Window의 핸들.
	// `이것은 어떤 Window와 붙어있길 원하는 다른 Window를 연결하는 것이다.
	//
	C_WINDOW *				pC_move_sync_window;

	bool                 m_bl_kill;
   int					   m_x, m_y, m_w, m_h;
	int						m_backup_x, m_backup_y;
	int						m_prev_x, m_prev_y, m_prev_w, m_prev_h;
	std::string				   m_p_titlebar_str;
	bool						m_bl_now_moving;
	bool				      m_bl_show;
	bool				      m_bl_is_option_button;
	bool				      m_bl_is_titlebar;
	BF_OPTION_BUTTON	   m_BF_option_button;
	BF_WINDOW_OPTION	   m_BF_window_option;
	HANDLEID			      m_self_hid;

	E_DIALOG_ID			   m_e_focus;		// focus된 dialog id
	int						m_i_focus_n;	// focus된 dialog의 index

	//
	// `for Child Window 
	//
	E_WHO_AM_I				m_e_who_am_i;
	bool						m_bl_have_child;
	int						m_i_child_count;
	WINDOW_ID *				m_p_window_id; // Child window id 저장 버퍼 ptr
	C_WINDOW *				m_pC_parent_window; // Parent Window handle - only one

   //
   // Methods for Dialog
   //
	S_DIALOG_HANDLE_ID	m_S_dialog_handle_id;
	S_DIALOG_COUNT		   m_S_dialog_count;
   BF_DIALOGINFO		   m_BF_dialoginfo;
	void SetDialogInfo(E_DIALOG_ID id);

	//
	// window id pointer 
	// `window id는 hid의 index이다. 어떤 Window가 제거되어서 그 window id가 반드시 
	//  무효화되어야 한다고 할 때, 이 포인터를 사용한다. 이것은 그 window id의 pointer이다.
	//
	WINDOW_ID *				m_p_wid_pointer;

	//
	// Last execution method
	// `Window종료시 ~C_WINDOW()가 호출될 때 마지막으로 실행하는 method.
	// `이것의 용도는 마지막으로 그 Window와 관련된 어떤 일을 할 수 있는 기회를 
	//  App에 주는 것이다.
	//
	void (*m_fp_last_exec_method)(void);

	//
	// Keyboard control receiver
	// `이것은 특정 Dialog 전용이 아니라 Window 차원에서 지원한다. 이것이 더 활용범위가 넓다.
	//  물론, 특정 Dialog에서는 keyboard control을 받지만, 충돌을 피하는 것은 App의 몫이다.
	//  심각한 사항은 UI 내부에서 처리해준다.
	//
	void (*m_fp_keyboard_control_receiver)(UINT message, UINT key);

	//
	// Mouse control receiver
	// `Window client rect에 마우스 입력이 들어오면 보낸다. Window client rect내의 Mouse
	//  access를 필요로 할 때 사용한다.
	//
	void (*m_fp_mouse_control_receiver)(UINT message, int mx, int my);

	// client를 갱신하는 procedure(method).
	void (*m_fp_client_update_proc)(void);

public:
	WINDOW_ID GetWindowID() const;
	void	SetFocusToThisEditBox(WINDOWHANDLE p_editbox);
	C_WINDOW * GetMoveSyncWindow() const { return pC_move_sync_window; }
	bool	SetMouseControlReceiver(void (*fp_receiver)(UINT, int, int));
	bool	SetClientUpdateProc(void (*fp)(void));
	void	ReleaseClientSurfaceInfo() const;
	bool	GetClientSurfaceInfo(S_SURFACEINFO &surfaceinfo, int &client_x, int &client_y) const;
	void	SetMoveSyncWindow(C_WINDOW *window);
	void	SendFirstFocus();
	bool	SetKeyboardControlReceiver(void (*fp_receiver)(UINT, UINT));
	bool	IsEditbox();
	bool	ResetWindowSizebyIconControl(C_ICON_CONTROL *pC_iconcontrol);
	bool	SetLastExecMethod(void (*fp_last_exec_method)(void));
	void	ToggleShowFlag();
	void	KeyboardControl(UINT message, UINT key);
	bool	KillThisDialog(E_DIALOG_ID did, HANDLEID hid);
	bool	InvalidateWindowID();
	bool	SetWindowIDPointer(WINDOW_ID *p_wid);
	bool	IsListbox() const;
	void	SetParentWindowHandle(C_WINDOW *pC_window) { m_pC_parent_window = pC_window; }
	void	ShowChildWindow();
	void	SetWhoAmI(E_WHO_AM_I e_new_state) { m_e_who_am_i = e_new_state; }
	void	KillChildWindow();
	bool	GetTitlebarState() const { return m_bl_is_titlebar; }
	int	GetChildWindowCount() const { return m_i_child_count; }
	bool	AddChildWindow(WINDOW_ID child_wid);
	bool	IsChildWindow() const { return m_bl_have_child; }
	bool	ClearChildWindow();
	bool	UnifyTextButtonClass() const;
	void	KillAllChildDialogs();
	bool	IsOutputbox() const;
	void	GetAvailableClientRect(S_RECT *rect) const;
   void	RefreshAllDialogSize() const;
	int	GetScrollbarCount() const { return m_S_dialog_count.scrollbar; }
	int	GetScrollbar2Count() const { return m_S_dialog_count.scrollbar2; }
	bool	GetPushForResizeState() const { return S_coordisystem.bl_push_for_resize; }
	void	SetResizeState(bool newflag) { m_BF_window_option.resize = newflag; }
	bool	ResetWindowSizebySingleMenu(C_SINGLEMENU *C_singlemenu);
	void	ShowClientAreaRect() const;
	void	GetClientRect(S_RECT *S_rect) const;
	void  GetClientRect2(S_RECT *S_rect) const;
	void	Set_CB_PushFlag(bool newflag) { S_coordisystem.bl_cb_push = newflag; }
	void	Set_MB_PushFlag(bool newflag) { S_coordisystem.bl_mb_push = newflag; }
	void	Set_Maximize_PushFlag(bool newflag) { S_coordisystem.bl_maximize_push = newflag; }
	void	SetKillFlag(bool newflag) { m_bl_kill = newflag; }
	bool	GetKillState() const { return m_bl_kill; }
	void	Set_Maximize_Flag(bool newflag) { S_coordisystem.bl_maximize_flag = newflag; }
	void	Set_MB_Flag(bool newflag) { S_coordisystem.bl_mb_flag = newflag; }
	bool	GetPushedFlag() const { return S_coordisystem.bl_push; }
	void	SetWindowHeight(int new_h) { m_h = new_h; }
	void	SetWindowWidth(int new_w) { m_w = new_w; }
	void	SetSelfHid(HANDLEID hid) { m_self_hid = hid; }
	bool	GetShowState() const { return m_bl_show; }
	bool	GetSequenceState() const;
	void	MouseControl(UINT message, int mx, int my);
	int	GetY_of_Window() const { return m_y; }
	int	GetX_of_Window() const { return m_x; }
	int	GetH_of_Window() const { return m_h; }
	int	GetW_of_Window() const { return (m_w - 1); } // 그림자는 뺀다.
	void	ApplySequence(bool result) { m_BF_window_option.sequence = result; }
	void	Movable(bool result) { m_BF_window_option.movable = result; }
   void	SystemButton(bool result) { m_bl_is_option_button = result; }
	bool	GetSystemButtonState() const { return m_bl_is_option_button; }
	void	Titlebar(bool result) { m_bl_is_titlebar = result; }
	void	SetWindowCoordinates(int new_x, int new_y);
	void	SetShowFlag(bool result);
	void	SetTitlebarString(std::string str);
	void	Show();
	void	GiveSelfHandleToDialogs();
   bool	PutDialogHandleID(E_DIALOG_ID id, HANDLEID hid);

	C_TREE_CONTROL *	GetTreeControlHandle() const;
	C_LISTBOX *			GetListHandle() const;
	C_OUTPUTBOX *		GetViewHandle() const;
	C_WINDOW *			GetChildWindowHandle(int n) const;
	C_WINDOW *			GetParentWindowHandle() const;
	E_WHO_AM_I			GetWhoAmI() const { return m_e_who_am_i; }

	static S_COORDISYSTEM       S_coordisystem; // this is public

	C_WINDOW();
	~C_WINDOW();
};

#endif