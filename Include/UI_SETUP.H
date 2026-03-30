#ifndef __UI_SETUP__
#define __UI_SETUP__

#include "ui_typedef.h"
#include "FL_import.h"

/*-----------------------------------------------------------------------------
  재정의할 수 없는 크기및 위치 정보 구조체
-----------------------------------------------------------------------------*/
#define TITLEBAR_H   				   18 // 외곽선 제외
#define CLOSE_BUTTON_X				   ((m_x+m_w-2) - 25)
#define CLOSE_BUTTON_Y				   (m_y + 4)
#define CLOSE_BUTTON_W				   22
#define CLOSE_BUTTON_H				   12
#define MINIMIZE_BUTTON_X				((m_x+m_w-2) - 25)
#define MINIMIZE_BUTTON_Y				(m_y + 4)
#define MINIMIZE_BUTTON_W1          8
#define MINIMIZE_BUTTON_W2          15
#define MINIMIZE_BUTTON_H1          7
#define MINIMIZE_BUTTON_H2          6
#define MAXIMIZE_BUTTON_X				((m_x+m_w-2) - 18)
#define MAXIMIZE_BUTTON_Y				(m_y + 4)
#define MAXIMIZE_BUTTON_W1          15
#define MAXIMIZE_BUTTON_W2          8
#define MAXIMIZE_BUTTON_H1          7
#define MAXIMIZE_BUTTON_H2          6
#define ITEM_STRING_H_GAP			   4
#define TSTR_BUFSIZE                80 // Title bar string buf size for exception
#define EDGE_GAP                    8 // for Window resizing
#define LEAST_WIDTH                 75 // 최소 크기
#define LEAST_HEIGHT                21
#define MOST_WIDTH                  GetResolutionX()
#define MOST_HEIGHT                 GetResolutionY()
#define DEFAULT_SB_WIDTH            15 // default scroll bar width - 수직버튼기준
#define DEFAULT_SB_HEIGHT           14 // 수직버튼기준
#define LEAST_TAG_LENGTH            14
#define TAG_RING_HALF               3 // tag 무늬 절반 길이
#define TEXTBUTTON_W_GAP				7 // text 다음의 여백
#define TEXTBUTTON_H_GAP				6
#define TB_W_GAP							(TEXTBUTTON_W_GAP*2 + 1) // '1' is a shadow
#define TB_H_GAP							(TEXTBUTTON_H_GAP*2 + 1) // '1' is a shadow
#define ARROW_XGAP						16
#define ARROW_RIGHT_GAP					13 // dialog rect 끝에서 arrow의 시작 x까지의 거리
#define ARROW_HEIGHT_HALF				5
#define SELECTIONBAR_GAPX				6
#define SELECTIONBAR_GAPY				2
#define COMMENT_LINE_H					20 // list box comment line height
#define DIALOG_STRING_DEFAULT_GAP	10
#define PULLDOWNMENU_SRT_START_X		12		// gap of 6 pixel
#define PULLDOWNMENU_SRT_START_Y		6		// gap of 6 pixel
#define PULLDOWNMENU_STR_GAP			28
#define PULLDOWNMENU_HEIGHT			25
#define ICONCONTROL_XSIZE				64//35
#define ICONCONTROL_YSIZE				32//35
#define EDITBOX_MESSAGE_YGAP			9
#define EDITLINE_GAP						3
#define MESSAGE_GAP_EDITLINE			6
#define TOGGLE_CHECK_GAP				14

#define UI_BACKGROUND_DEFAULT_COLOR	15220

/*-----------------------------------------------------------------------------
  UI color 구조체

  `선택된 윈도우와 선택되지 않은 윈도우의 구별은 제목글자의 색깔로 구별한다.

  `가변할 수 있기 때문에 변수로 한 이유도 있지만, 속도를 위해서도 값을 저장한다.
-----------------------------------------------------------------------------*/
typedef struct
{
   int frame_edge;         // 틀의 테두리 색 + 그림자 + titlebar button(t-button)
   int frame_inside;       // 틀의 안쪽 바탕 
   int titlebar;           // title bar + t-button
   int titlebar_edgeup;    // title bar 위와 왼쪽 테두리 + tag up line + t-button
   int titlebar_edgedown;  // title bar 아래와 오른쪽 테두리 + t-button
   int titlebar_leftmo;    // title bar 왼쪽 모서리 점 + t-button
   int titlebar_rightmo;   // title bar 오른쪽 모서리 점 + tag down line + tag up line + t-button
   int titlebar_rightupmo; // title bar 오른위쪽 모서리 점 + t-button
   int selectedwindow_titlestring;  // 선택된 윈도우의 제목 
   int nselectedwindow_titlestring; // 선택되지 않은 윈도우의 제목 

   // for single-menu
   int selected_item_string_color; // menu item color selected
   int item_string_color;  // menu item color
   int item_string_disable_color; // disable...
   int selected_item_string_disable_color; // menu item color selected
   int selectbar_inside_color; // 선택막대 inside color
   int selectbar_frame_color; // 선택막대 테두리 color
   int resize_frame_color; // when resizing
	int move_frame; // when moving

   // for scroll bar
   int sb_frame;
   int sb_inside_addline;
   int sb_inside_addline2;
   int sb_inside_when_active;
   int sb_inside_when_noactive;
   int sb_tag_inside;
   int sb_tag_left_edge;
   int sb_tag_right_edge;
   int sb_tag_mo;

	int view_background;

	// for text button
	// !text button color = Window color!

	int list_string;
	int list_background;
	int list_select_rect;
	int list_primary_cl_str;
	int list_secondary_cl_str;
	int list_primary_cl_inside;
	int list_secondary_cl_inside;

	int iconcontrol_boundary;

	int treecontrol_plusminus;
	int icon_selector;

	int combo_selected;
	
} S_UICOLOR;

#define BOUNDARY_COLOR					0x00FF // 경계를 알아보기 위한...

/*-----------------------------------------------------------------------------
  UI font 구조체
-----------------------------------------------------------------------------*/
typedef struct
{
	E_FONTNAME window_title;
	E_FONTNAME menu_string;
	E_FONTNAME listbox_string;
	E_FONTNAME listbox_primary;
	E_FONTNAME listbox_secondary;
	E_FONTNAME textbutton_string;
	E_FONTNAME pulldownmenu_string;
	E_FONTNAME edit_string;

} S_UI_FONT;

/*-----------------------------------------------------------------------------
  UI option 구조체
-----------------------------------------------------------------------------*/
typedef enum
{ // MT (MoveType)
	MT_TOTAL,
	MT_FRAME,
} E_MOVETYPE;

typedef struct
{
   bool			mousemove_focus; // click없이 마우스포인터의 위치로 focus set한다.
   bool			drag_shape; // Title bar에 끌기 모양을 넣는다.
	E_MOVETYPE	e_movetype;
} S_UIOPTION;

/*-----------------------------------------------------------------------------
  UI setup object.
-----------------------------------------------------------------------------*/
class C_UI_SETUP
{
private:

public:
	void ToggleMoveType();
   C_UI_SETUP();
   ~C_UI_SETUP();

	void SetDefault();
	void Setup();

   S_UICOLOR   S_uicolor;
   S_UIOPTION  S_uioption;
	S_UI_FONT	S_uifont;
};

#endif