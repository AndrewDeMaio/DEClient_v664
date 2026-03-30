/*-----------------------------------------------------------------------------

	UI.h

	User Interface Master Header file.h

   19981101. KJTINC
   19990706.
	20000207.

-----------------------------------------------------------------------------*/

#ifndef __UI__
#define __UI__

#include "FL_import.h"
#include "UI_PreDefine.h"
#include "window.h"
#include "singlemenu.h"
#include "listbox.h"
#include "file_service.h"
#include "outputbox.h"
#include "tree_control.h"
#include "icon_control.h"
#include "pulldownmenu.h"
#include "editbox.h"
#include "i_signal.h"
#include "scrollbar2.h"
#include "combobox.h"
#include "lib_wrapper.h"
#include "BasicS.h"
#include "sora_monitor.h"
#include "HotkeySystem.h"
#include "ui_strings.h" // for App
#include "UI_macro.h"

#define DATA_PATH							"\\data\\"

//
// _ABS_W(c, w)
//
// `Window가 왼쪽 화면 밖으로 나갔을 때 0으로 고정되는 Window client 좌표를 
//  절대좌표로 얻는 매크로 함수. 절대좌표를 얻음으로써 client rect에 그려진 것들의
//  clipping이 가능하다.
//
// c - client (x, y)
// w - window (x, y)
//
#define _ABS_W(c, w)						((c < 0) ? (c+w) : w)

/*-----------------------------------------------------------------------------
  System pulldown menu에 추가되는 item의 exec id는 이 매크로를 사용해서 정해야
  한다.
-----------------------------------------------------------------------------*/
#define ADD_EXEC_ID(x)					(0xFF+(x))

/*-----------------------------------------------------------------------------
  E_M_CONDITION
-----------------------------------------------------------------------------*/
typedef enum
{
   OK_WHAT, // what ok...????
   OK_X,
   OK_Y,
   OK_ALL,

} E_M_CONDITION;

/*-----------------------------------------------------------------------------
  DEFAULT_INT

  `어떤 integer값이 default임을 나타냄.
-----------------------------------------------------------------------------*/
#define DEFAULT_INT                 -1

/*-----------------------------------------------------------------------------
  UI Class

  `각 Method에 대한 설명은 함수 정의 부분에 있음(일부 제외). 
-----------------------------------------------------------------------------*/
class C_UI 
{
public:
	// UI font - FL 사용.
	static FONT_GID				m_ui_font1;
	static FONT_GID				m_ui_font2;

private:
	C_HOTKEY_SYSTEM *				m_pC_hotkey_system;

	bool	m_bl_toggle_windowshow;
	int	m_current_sequence; // 우선순위 버퍼 위치
	int	m_count_sequence; // 우선순위 버퍼 개수
	HANDLEID	* m_p_hid_sequence; // 우선순위 변경을 위한 버퍼

	void	CheckControlKey();
	void	(*m_fp_change_resolution)(int res_x, int res_y, int bpp);

	bool	m_bl_ctrl_state;
	HANDLEID	* m_p_handle_id_buffer;
	int	m_handle_id_buffer_count;
	bool	m_bl_handle_id_buffer_background; // background mode인가?

	bool	m_bl_in_file_menu;

	void	ToggleWindowShow();
	void	MakeHelpMenu(S_ADD_SYSPULLDOWNMENU_ITEM *pS_add_item, int count);
	void	MakeFileMenu(S_ADD_SYSPULLDOWNMENU_ITEM *pS_add_item, int count);
	void	MakeOptionMenu(S_ADD_SYSPULLDOWNMENU_ITEM *pS_add_item, int count);
	bool	DetermineFocusByMouseMove(UINT message, int x, int y);
	void	MakeSaveFileWindow();
	void	MakeOpenFileWindow();
	bool	DetermineChildWindowFocus(UINT message, int mx, int my);
	void	UpdateJobData();
	void	ShowMousePointer();
	void	Kill();
	void	TL_ChangeButtonState();
	void	TL_ChangeCursorState();
	void	ExecuteTimerList();
//	void	InitializeResource();
	void	Show();
	void	Kill_UI();

	E_M_CONDITION HoldMousePointerIfInFrame(UINT message, int x, int y);

	HANDLEID m_auto_focused_hid;
	bool		m_background_focus;
	int		m_mouse_x, m_mouse_y; // for image show
	bool		m_bl_syspulldownmenu;

	//
	// Save file Window에서 입력된 문자열을 받는 method fp.
	//
	void		(*m_fp_save_file_string_receiver)(char *, char *);
	void		(*m_fp_save_file_string_receiver2)(char *, char *); // File 메뉴에서 save할 경우.

	//
	// System pulldown menu에 App의 menu를 추가할 경우 exec id를 받는 method
	// 이것은 App에서 item을 추가하면 설정할 수 있다.
	// `File, Option, Help ...
	//
	void		(*m_fp_syspulldownmenu_user_file)(EXEC_ID exec_id);
	void		(*m_fp_syspulldownmenu_user_option)(EXEC_ID exec_id);
	void		(*m_fp_syspulldownmenu_user_help)(EXEC_ID exec_id);

public:
/*-----------------------------------------------------------------------------
  UI graphic library - start
-----------------------------------------------------------------------------*/
	void  Clear(WINDOW_ID wid, int c);
	void  Vertline(WINDOW_ID wid, int x, int y, int h, int c);
	void  Horzline(WINDOW_ID wid, int x, int y, int w, int c);
	void	Line(WINDOW_ID wid, int x1, int y1, int x2, int y2, int c);
	void	FillRect(WINDOW_ID wid, int x, int y, int w, int h, int c);
	void	Rectangle(WINDOW_ID wid, int x, int y, int w, int h, int c);
	int	GetPixel(WINDOW_ID wid, int x, int y);
	void	PutPixel(WINDOW_ID wid, int x, int y, int c);
	void	Bltz(WINDOW_ID wid, int x, int y, S_SURFACEINFO &src_surface, S_RECT &src_rect);
	void  CkBltz(WINDOW_ID wid, int x, int y, S_SURFACEINFO &src_surface, S_RECT &src_rect, int colorkey);
/*-----------------------------------------------------------------------------
  UI graphic library - end
-----------------------------------------------------------------------------*/
	void	InitializeResource();

/*-----------------------------------------------------------------------------
  UI font library - start
-----------------------------------------------------------------------------*/
	enum UI_FONT
	{
		// hangul
		IYAGI,
		GOOLRIM,

		// english
		DEFAULT,
		OLIVE,
		NAPLES,
	};

	void	SelectEngFont(UI_FONT fontname);
	void	SelectHanFont(UI_FONT fontname);
	void	Text(WINDOW_ID wid, int x, int y, const char * str, int c);
/*-----------------------------------------------------------------------------
  UI font library - end
-----------------------------------------------------------------------------*/

	void	SetIconControlLastCutLine(S_DIALOG_POINTER *dp, int count);
	bool	AddHotKey(C_HOTKEY_SYSTEM::TYPE type, hk_class_t hk_class, 
								  C_HOTKEY_SYSTEM::EXT_KEY ext_key ,UINT scan_code, void (*fp_exec)(void));
	bool  SetStaticText(S_DIALOG_POINTER *dp, const char *str);
	void	CloseOpenFileWindow();
	bool	GetOpenFileWindowShowState();
	bool	GetSaveFileWindowShowState();
	void	ActivateToggleWindowShow();
	bool	SetChangeResolutionResultReceiver(void	(*fp_change_resolution)(int res_x, int res_y, int bpp));
	bool	GetHandleIDBufferState();
	bool	ClearAllSequenceWindow();
	bool	ShowAllSequenceWindow();
	inline void ForceBackgroundFocus() { m_background_focus = true; }
	inline void ForceNoBackgroundFocus() { m_background_focus = false; }
	inline bool GetBackgroundFocusState() const { return m_background_focus; }
	inline HANDLEID GetAutoFocusedWindowHid() const { return m_auto_focused_hid; }

	bool SetMouseControlReceiver(WINDOW_ID wid, void (*fp_receiver)(UINT, int, int));
	bool SetScrollbar2LastPosition(S_DIALOG_POINTER *dp, int last_position);
	bool SetScrollbar2MovePixel(S_DIALOG_POINTER *dp, int newpixel);
	S_DIALOG_POINTER MakeScrollbar2(WINDOW_ID window_id, E_BAR_TYPE bar_type, 
												  void (*fp_result_receiver)(const S_RESULT_SCROLL &), int last_position);
	bool SetClientUpdateProc(WINDOW_ID wid, void (*fp)(void));
	bool GetClientSurfaceInfo(WINDOW_ID wid, S_SURFACEINFO *p_surfaceinfo, int *p_gap_x, int *p_gap_y);
	bool ReleaseClientSurfaceInfo(WINDOW_ID wid);
	bool GetTreeNode(S_DIALOG_POINTER *dp, LIST_LEVEL level, NODE_NUM node, S_NODE **pp_node);
	bool GetRootTreeList(S_DIALOG_POINTER *dp, TREE_LIST **list);
	bool GetViewLockSurfaceInfo(S_DIALOG_POINTER *dp, S_SURFACEINFO *pS_surfaceinfo);
	bool RefreshImage(S_DIALOG_POINTER *S_dp);
	bool SetComboStateReceiver(S_DIALOG_POINTER *dp, void (*fp)(int));
	bool SetListBoxComboInfo(S_DIALOG_POINTER *dp, char **list, int count, int index);
	bool GetWindowH(WINDOW_ID wid, int &h);
	bool GetWindowW(WINDOW_ID wid, int &w);
	bool GetWindowY(WINDOW_ID wid, int &y);
	bool GetWindowX(WINDOW_ID wid, int &x);
	bool SetMoveSyncWindow(WINDOW_ID dest_wid, WINDOW_ID src_wid);
	bool SetIconControlRightButtonUpJob(S_DIALOG_POINTER *dp, void (*fp)());
	bool SetIconControlSelectorShape(S_DIALOG_POINTER *dp, E_SELECTOR_SHAPE shape);
	bool ResetSpecifiedWindowSize(WINDOW_ID windowid, int w, int h);
	bool GetTreeLevelNodeCount(S_DIALOG_POINTER *dp, const LIST_LEVEL level, NODE_NUM &node);
	bool GetTreeLevelCount(S_DIALOG_POINTER *dp, LIST_LEVEL &level);
	bool SendFirstFocus(WINDOW_ID window_id);
	bool SetTreeNoClickState(S_DIALOG_POINTER *dp, bool state);
	bool GetWindowShowState(WINDOW_ID wid);
	S_NODE * GetClickNode(S_DIALOG_POINTER *dp);
	bool SaveTree(S_DIALOG_POINTER *dp, char *sz_full_filename);
	bool ClearTree(S_DIALOG_POINTER *dp);
	bool LoadTree(S_DIALOG_POINTER *dp, char *sz_full_filename);
	bool CallOpenFileInterface();
	void SetIconControlPushState(S_DIALOG_POINTER *dp, EXEC_ID exec_id);
	void ClearIconControlPushState(S_DIALOG_POINTER *dp, EXEC_ID exec_id);
	void ClearAllIconControlPushState(S_DIALOG_POINTER *dp);
	char * GetEditboxCurrentInputedString(S_DIALOG_POINTER *dp);
	bool PreSetEditboxCurrentInputedString(S_DIALOG_POINTER *dp, const char *str);
	bool SetSystemPulldownMenuAddFp_Help(void (*fp_syspulldownmenu_user_help)(EXEC_ID exec_id));
	bool SetSystemPulldownMenuAddFp_Option(void (*fp_syspulldownmenu_user_option)(EXEC_ID exec_id));
	bool SetSystemPulldownMenuAddFp_File(void (*fp_syspulldownmenu_user_file)(EXEC_ID exec_id));
	bool SetKeyboardControlReceiver(WINDOW_ID wid, void (*fp_receiver)(UINT,UINT));
	bool CallSaveFileInterface();
	void CancelSaveFileStringReceiver();
	void CancelSaveFileStringReceiver2();
	bool SetSaveFileStringReceiver(void (*fp_receiver)(char *, char *));
	bool SetSaveFileStringReceiver2(void (*fp_receiver)(char *, char *));
	void TL_UpdatePathScrollState();
	S_DIALOG_POINTER MakeEditbox(WINDOW_ID window_id, int x, int y, int width,
											  int char_count, void (*fp_receiver)(char *));
	void ClearPullDownMenu();
	bool SetIconControlExecFp(S_DIALOG_POINTER *dp, void (*fp_exec)(EXEC_ID));
	bool AddIconControl(S_DIALOG_POINTER *dp, char *sz_filename, EXEC_ID exec_id, E_ICONCONTROL_STYLE style);
	S_DIALOG_POINTER MakeIconControl(WINDOW_ID wid, int xsize, int ysize, int icon_x, int icon_y);
	bool	SetLastExecMethod(WINDOW_ID wid, void (*fp_last_exec_method)(void));
	
	bool	SystemPulldownMenuState();

	// UI's friends
	friend void HOTKEY_SwitchWindow();
	friend void HOTKEY_CloseWindow();
	friend void HOTKEY_ToggleWindowShow();
	friend void HOTKEY_CallOpenFileDialog();
	friend void HOTKEY_CallSaveFileDialog();
	friend void HOTKEY_ToggleAppMonitor();
	friend void UI_ItemExecution_FileMenu(EXEC_ID exec_id);
	friend void UI_ItemExecution_OptionMenu(EXEC_ID exec_id);
	friend void UI_ItemExecution_OptionMenu_Res(EXEC_ID exec_id);
	friend void UI_LastExecMethod_FileOpen();
	friend void UI_LastExecMethod_FileSave();
	friend void UI_ItemExecution_HelpMenu(EXEC_ID exec_id);
	friend void UI_LastExecMethod_HelpAboutUI();
	friend void UI_TB_SaveFile_Cancel();
	friend void UI_TB_SaveFile_Ok();
	friend void UI_EB_StringReceiver_FileName(char *sz_filename);

	void ClearGeneralWindow(WINDOW_ID wid);
	S_DIALOG_POINTER MakePulldownMenu(WINDOW_ID wid);
	bool	AddMenuTitleToSystemPulldownMenu(char *sz_str, WINDOW_ID singlemenu_wid, int priority);
	void	MakeSystemPulldownMenu(S_ADD_SYSPULLDOWNMENU_ITEM *, int);
	bool	SetTreeControlMouseControlFp(S_DIALOG_POINTER *dp, void (*AppMouseControl)(UINT,int,int,C_TREE_CONTROL *));
	bool	SetTreeControlUniqueID_receiver(S_DIALOG_POINTER *dp, void (*fp_uniqueID_receiver)(UNIQUE_ID));
	bool	EraseTreeNode(S_DIALOG_POINTER *dp, LIST_LEVEL level, NODE_NUM node);
	bool	InsertTreeNode(S_DIALOG_POINTER *dp, LIST_LEVEL level, NODE_NUM node, char *sz_title, UNIQUE_ID unique_id);
	bool	GetClientRect(WINDOW_ID wid, S_RECT *rect);
	bool	SetTitlebarString(WINDOW_ID wid, char *sz_title);
	bool	KillThisDialog(WINDOW_ID wid, S_DIALOG_POINTER *dp);
	bool	GetViewSurfaceInfo(S_DIALOG_POINTER *dp, S_SURFACEINFO *pS_surfaceinfo);
	bool	SetViewMouseControlFp(S_DIALOG_POINTER *dp, void (*AppMouseControl)(UINT,int,int,C_OUTPUTBOX *));
	bool	SetFileServiceProcFp(void (*FileServiceProc)(const S_FILE_SERVICE_INFO *));
	void	ValidateWindowID(WINDOW_ID *p_wid);
	bool	SetListBoxRefreshFlag(S_DIALOG_POINTER *dp, bool newflag);
	int	GetListBackgroundColor(S_DIALOG_POINTER *dp);
	bool	SetListBackgroundColor(S_DIALOG_POINTER *dp, int color);
	bool	ClearAllListUnit(S_DIALOG_POINTER *S_dp);
	bool	AddListUnit(S_DIALOG_POINTER *S_dp, char *sz_str, DWORD unique_id, bool delete_flag);
	bool	AddSingleMenuItem(S_DIALOG_POINTER *S_dp, char *p_str, E_SELECT_OPTION option, EXEC_ID unique_id, 
									E_TOGGLE_OPTION toggle = TOGGLE_NOTSET);
	bool	SetListEventExecFpointer(S_DIALOG_POINTER *dp, 
											void (*fp_list_event_exec)(S_LIST_ITEM *, C_LISTBOX::EVENT_CATEGORY category));
	bool	SetListUpdateFpointer(S_DIALOG_POINTER *dp, void (*fp_list_update)());
	int	GetViewBackgroundColor(S_DIALOG_POINTER *dp);
	bool	SetViewUpdateFpointer(S_DIALOG_POINTER *dp, void (*fp_view_update)(void));
	bool	GiveChildWindowToParentWindow(WINDOW_ID parent_wid, WINDOW_ID child_wid);
	bool	IsChildWindow();
	bool	AttachSubMenuToSingleMenu(S_DIALOG_POINTER *S_dp, EXEC_ID unique_id, S_DIALOG_POINTER *S_attached_dp);
	bool	UnifyTextButtonClass(WINDOW_ID window_id);
	bool	SetScrollbarMovePixel(S_DIALOG_POINTER *dp, int newpixel);
	bool	SetViewBackgroundColor(S_DIALOG_POINTER *dp, int color);
	bool	ChangeSingleMenuItemOption(S_DIALOG_POINTER *dp, EXEC_ID unique_id, E_SELECT_OPTION option, int new_toggle = NOT_SELECTED);
	bool	ImageOut(S_DIALOG_POINTER *S_dp, int ix, int iy, char *filename, bool lock);
	bool	TextOut(S_DIALOG_POINTER *S_dp, int ix, int iy, char *str, int color);
	bool	SetItemIDExecFpointer(S_DIALOG_POINTER *dp, void (*fp_item_exec)(EXEC_ID));
	void	KillSpecifiedWindow(WINDOW_ID windowid);
	void	ClearSpecifiedWindow(WINDOW_ID windowid);
	void	SetSpecifiedWindowCoordinates(WINDOW_ID windowid, int x, int y);
	void	ShowSpecifiedWindow(WINDOW_ID windowid);
	void	Init();
	bool	MouseControl(UINT message, int x, int y);
	bool	KeyboardControl(UINT message, WPARAM wParam, LPARAM lParam);
	void	UI_Loop();

   WINDOW_ID			MakeWindow(S_WINDOW_MAKEINFO *makeinfo);
	S_DIALOG_POINTER	MakeTreeControl(WINDOW_ID wid);
	S_DIALOG_POINTER	MakeList(WINDOW_ID window_id, bool bl_primary_cl, bool bl_secondary_cl);
	S_DIALOG_POINTER	MakeTextButton(WINDOW_ID window_id, char *str, int x, int y, 
												  void (*fp_tb_exec)(void));
	S_DIALOG_POINTER	MakeView(WINDOW_ID window_id, int resolution_x, int resolution_y);
	S_DIALOG_POINTER	MakeScrollbar(WINDOW_ID window_id, E_BAR_TYPE bar_type);
	S_DIALOG_POINTER	MakeSingleMenu(WINDOW_ID window_id, int unit_count);
	S_DIALOG_POINTER	MakeComboBox(WINDOW_ID window_id, int x, int y, const C_COMBOBOX::S_ITEM *p_item, 
												int total, void (*fp_exec)(EXEC_ID id), int **selection = NULL);
	S_DIALOG_POINTER  MakeStaticText(WINDOW_ID window_id, int x, int y, const char *str);

	C_UI();
	~C_UI();
};

/*-----------------------------------------------------------------------------
  EXTERNS
-----------------------------------------------------------------------------*/
extern C_UI gC_ui;
extern S_DIALOG_POINTER	g_dp_filemenu;
extern S_DIALOG_POINTER  g_dp_optionmenu;
extern S_DIALOG_POINTER  g_dp_helpmenu;

#endif