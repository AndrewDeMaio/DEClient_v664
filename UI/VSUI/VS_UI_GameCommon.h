/*-----------------------------------------------------------------------------

	VS_UI_GameCommon.h

	Game common interface.

	Common:
				Chatting interface
				NPC
				Exchange

	2000.8.11. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_GAME_COMMON_H__
#define __VS_UI_GAME_COMMON_H__

#include "VS_UI_Base.h"
#include "VS_UI_Util.h"
#include "VS_UI_description.h"
#include "VS_UI_ExtraDialog.h"

//#include "VS_UI_GameSlayer.h"
class C_VS_UI_SLAYER_QUICKITEM;
class C_VS_UI_OUSTERS_QUICKITEM;

extern bool gbl_mine_progress;

#include "SkillDef.h"
#include "MItem.h"
#include "MMoneyManager.h"
#include "MSkillManager.h"
#include "ClientFunction.h"
#include "MZone.h"

#include <vector>	//by larosel

#include "TickTimer.h"
#include "VS_UI_GPS.H"

#include "ContentsFilter.h"

#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)
#include "MPremiumGiveItemInfo.h"
#include "VS_UI_PremiumGiveItem.h"
#endif //__PREMIUM_GIVE_ITEM_UI

#if __CONTENTS(__TITLE_UI_RENWEAL)
#include "VS_UI_NewTitle.h"
#else	//__TITLE_UI_RENWEAL
#include "VS_UI_Title.h"
#endif //__TITLE_UI_RENWEAL

#define SLAYER_FONT_COLOR				RGB(186, 189, 191)//RGB(20, 70, 0)	// by larosel
#define VAMPIRE_FONT_COLOR				RGB(186, 189, 191)//RGB(255, 255, 255)

#define ITEM_DISABLE_COLOR_SET			40

// For Window Manager
struct WindowStatus
{
	WindowStatus()
		: autoHide(Window::ATTRIBUTES_HIDE_NOT)
		, alpha(false) {
	}

	Rect windowRect;
	Window::ATTRIBUTES_HIDE autoHide;
	bool alpha;
};

//-----------------------------------------------------------------------------
// class C_VS_UI_LEVELUP
//
// vampire/slayer level up?? ??�???? button.
//-----------------------------------------------------------------------------
class C_VS_UI_LEVELUP : public Window
{
private:
	enum IMAGE_SPK_INDEX
	{
		LVU_GUARD_SLAYER,
		LVU_GUARD_VAMPIRE,
		LVU_GUARD_OUSTERS,
		PARTY_REQUEST,
		PARTY_INVITE,
		RESURRECT_SLAYER,
		RESURRECT_VAMPIRE,
		RESURRECT_OUSTERS,
		LVU_BUTTON,
		LVU_BUTTON_OUSTERS,
	};

	C_SPRITE_PACK				m_image_spk;

	bool							m_bl_pushed;
	bool							m_bl_focused;

public:
	C_VS_UI_LEVELUP();
	~C_VS_UI_LEVELUP();

	void	Show();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
	void	CancelPushState() { m_bl_pushed = false; }
	void	UnacquireMouseFocus() { m_bl_focused = false; }
};

#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)
//-----------------------------------------------------------------------------
// class C_VS_UI_REQUEST_PREMIUM_GIVE_ITEM
//
// ??????? ???? ??????? ???????? ?????? ??? ??�???? button.
//-----------------------------------------------------------------------------
class C_VS_UI_REQUEST_PREMIUM_GIVE_ITEM : public Window
{
private:
	C_VS_UI_PREMIUM_GIVE_ITEM* m_pC_Premium_Give_Item;

	enum IMAGE_SPK_INDEX
	{
		REQUEST_GUARD_SLAYER,		// - 00 ??????? ????
		REQUEST_GUARD_VAMPIRE,		// - 01 ??????? ????
		REQUEST_GUARD_OUSTERS,		// - 02 ??????? ????
		PARTY_REQUEST,				// - 03	????????�
		PARTY_INVITE,				// - 04	??????
		RESURRECT_SLAYER,			// - 05	??????? ???		- ???????.
		RESURRECT_VAMPIRE,			// - 06	??????? ???		- ???????.
		RESURRECT_OUSTERS,			// - 07	??????? ???		- ???????.
		LVU_BUTTON,					// - 08	??????? ??????
		LVU_BUTTON_OUSTERS,			// - 09	??????? ??????
		RESURRECT_SCROLL,			// - 10	????????			- ???????.
		ELIXIR_SCROLL,				// - 11	??????				- ???????.
		ETERNITY,					// - 12	??????			- ???????. (????????????)
		SKILL_FROM_OTHER_SLAYER,	// - 13 ??????? ???? ???
		SKILL_FROM_OTHER_OUSTERS,	// - 14 ??????? ???? ???
		SKILL_FROM_OTHER_VAMPIRE,	// - 15 ??????? ???? ???
		GIVE_ITEM01,				// - 16 ??????? ????????? ?????? 01 (???? UI?? ?? ?????)
		GIVE_ITEM02,				// - 17 ??????? ????????? ?????? 02 (???? UI?? ?? ?????)
		GIVE_ITEM_CASE01,			// - 18 ??????? ????????? ?????? ?????? 01
		GIVE_ITEM_CASE02,			// - 19 ??????? ????????? ?????? ?????? 02
	};

	C_SPRITE_PACK				m_image_spk;

	bool						m_bl_pushed;
	bool						m_bl_focused;

public:
	C_VS_UI_REQUEST_PREMIUM_GIVE_ITEM();
	~C_VS_UI_REQUEST_PREMIUM_GIVE_ITEM();

	void	Show();
	void	Process();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
	void	RunPremiumGiveItemDialog();
	bool	ClosePremiumGiveItemDialog();
	void	Set_DynamicDesc_Process(int id) { if (m_pC_Premium_Give_Item != NULL) m_pC_Premium_Give_Item->Set_DynamicDesc_Process(id); }
	void	Update_Item_List();

	void	CancelPushState() { m_bl_pushed = false; }
	void	UnacquireMouseFocus() { m_bl_focused = false; }
};
#endif //__PREMIUM_GIVE_ITEM_UI

//-----------------------------------------------------------------------------
// class C_VS_UI_REQUEST_PARTY
//
//-----------------------------------------------------------------------------
class C_VS_UI_REQUEST_PARTY : public Window
{
private:
	enum IMAGE_SPK_INDEX
	{
		REQUEST_GUARD_SLAYER,
		REQUEST_GUARD_VAMPIRE,
		REQUEST_GUARD_OUSTERS,
		PARTY_REQUEST,
		PARTY_INVITE,
		RESURRECT_SLAYER,
		RESURRECT_VAMPIRE,
		RESURRECT_OUSTERS,
		LVU_BUTTON,
		LVU_BUTTON_OUSTERS,
		RESURRECT_SCROLL,
		ELIXIR_SCROLL,
	};

	C_SPRITE_PACK				m_image_spk;

	bool							m_bl_pushed;
	bool							m_bl_focused;
	std::string					m_name;

	// TIMER
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_timer_tickcount;

	bool	Timer(bool reset = false);

public:
	enum REQUEST_PARTY
	{
		REQUEST,
		INVITE,
	};

private:
	REQUEST_PARTY				m_type;

public:
	C_VS_UI_REQUEST_PARTY(const char* name, DWORD timer);
	~C_VS_UI_REQUEST_PARTY();

	void	Show();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
	void	CancelPushState() { m_bl_pushed = false; }
	void	UnacquireMouseFocus() { m_bl_focused = false; }
};

//-----------------------------------------------------------------------------
// class C_VS_UI_REQUEST_DIE
//
//-----------------------------------------------------------------------------
class C_VS_UI_REQUEST_DIE : public Window
{
private:
	enum IMAGE_SPK_INDEX
	{
		RESURRECT_GUARD_SLAYER,
		RESURRECT_GUARD_VAMPIRE,
		RESURRECT_GUARD_OUSTERS,
		PARTY_REQUEST,
		PARTY_INVITE,
		RESURRECT_SLAYER,
		RESURRECT_VAMPIRE,
		RESURRECT_OUSTERS,
		LVU_BUTTON,
		LVU_BUTTON_OUSTERS,
		RESURRECT_SCROLL,
		ELIXIR_SCROLL,
	};

	C_SPRITE_PACK				m_image_spk;

	bool						m_bl_pushed;
	bool						m_bl_focused;

	bool						m_bl_enforce_resurrect;

	// TIMER
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_timer_tickcount;

	// levelwar timer
	DWORD						m_levelwar_prev_tickcount;
	DWORD						m_levelwar_timer_tickcount;


public:
	C_VS_UI_REQUEST_DIE(DWORD timer, bool enforceResurrect = false, DWORD level_timer = 0);
	~C_VS_UI_REQUEST_DIE();

	bool	Timer(bool reset = false);
	bool	levelWarTimer(bool reset = false);

	void	Show();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
	void	CancelPushState() { m_bl_pushed = false; }
	void	UnacquireMouseFocus() { m_bl_focused = false; }
};

//-----------------------------------------------------------------------------
// class C_VS_UI_PARTY_MANAGER
//
//-----------------------------------------------------------------------------
class C_VS_UI_PARTY_MANAGER : public Window, public Exec, public ButtonVisual
{
private:
	enum
	{
		window_default_height = 18,
		window_gap = 41,
		window_bottom_gap = 7,
#if __CONTENTS(__080405_FIREST_UI_UPDATE)
		away_x = 82,
		away_y = 4,
#else
		away_x = 95,
		away_y = 8,
#endif //__080405_FIREST_UI_UPDATE
	};

	enum IMAGE_SPK_INDEX
	{
		PARTY_WINDOW,
		PARTY_WINDOW_ALPHA,
		PARTY_WINDOW_BOTTOM,
		DENY_BUTTON,
		DENY_BUTTON_PUSHED,
		DENY_BUTTON_HILIGHTED,
		DENY_BUTTON_HILIGHTED_PUSHED,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		HELP_BUTTON_HILIGHTED,
		HELP_BUTTON_PUSHED_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_PUSHED,
		CLOSE_BUTTON_HILIGHTED,
		CLOSE_BUTTON_PUSHED_HILIGHTED,
		AWAY_BUTTON,
		AWAY_BUTTON_HILIGHTED,
		AWAY_BUTTON_HILIGHTED_PUSHED,
		FACE_GRID,
		NAME_GRID,
		HPBAR,
	};

	enum EXEC_ID
	{
		ALPHA_ID,
		DENY_ID,
		HELP_ID,
		CLOSE_ID,

		AWAY_I,
		AWAY_0,
		AWAY_1,
		AWAY_2,
		AWAY_3,
		AWAY_4,
	};

	C_SPRITE_PACK* m_p_face_spk;
	C_SPRITE_PACK* m_p_large_face_spk;
	C_SPRITE_PACK* m_p_image_spk;
	ButtonGroup* m_pC_bottom_button_group;

#if __CONTENTS(!__080405_FIREST_UI_UPDATE)
	ButtonGroup* m_pC_button_group;
#endif //__080405_FIREST_UI_UPDATE

	std::vector<C_SPRITE_PACK*>		m_vp_face;
	std::vector<std::string>					m_v_face_name;

	bool	m_away_button_focused;
	bool	m_away_pushed;
	int		m_old_away_focused;
	int		m_away_focused;
	bool	m_bl_show_face_large;
	DWORD	m_dw_show_face_large_time;

public:
	C_VS_UI_PARTY_MANAGER();
	~C_VS_UI_PARTY_MANAGER();

	void	RefreshFaceImage();

	int		GetPartyManagerFocused() { return m_away_focused; }
#if __CONTENTS(__080405_FIREST_UI_UPDATE)
	void	UnacquireMouseFocus() { m_pC_bottom_button_group->UnacquireMouseFocus(); m_old_away_focused = -1; m_away_focused = -1; }
	void	CancelPushState() { m_pC_bottom_button_group->CancelPushState(); }
#else
	void	UnacquireMouseFocus() { m_pC_bottom_button_group->UnacquireMouseFocus(); m_pC_button_group->UnacquireMouseFocus(); m_old_away_focused = -1; m_away_focused = -1; }
	void	CancelPushState() { m_pC_button_group->CancelPushState(); m_pC_bottom_button_group->CancelPushState(); }
#endif //__080405_FIREST_UI_UPDATE
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	void	Process();

	bool	Timer(bool reset = false);

	void	Show();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
};

//-----------------------------------------------------------------------------
// HotKey (abstract base class)
//
// 
//-----------------------------------------------------------------------------
class HotKey
{
public:

	virtual void HotKey_PetInfo() = 0;		// ctrl+CapsLock
	virtual void HotKey_MailBox() = 0;		// ctrl+b
	virtual void HotKey_Party() = 0;		// ctrl+p
	virtual void HotKey_Mark() = 0;			// '????'?
	//	virtual void HotKey_WindowToggle()=0;	// ctrl + space
	virtual void HotKey_Inventory(bool IsCheckSubInventory = false) = 0;		// tab
	virtual void HotKey_Gear() = 0;			// ctrl + tab
#if __CONTENTS(__GEAR_SWAP_CHANGE)		//	C_VS_UI_GAME	????� ??�??? ??? ?? ???? ??? ????
	virtual void HotKey_GearChange() = 0;		// Alt + A
	virtual void HotKey_GearChangeShow() = 0;	// Alt + S
#endif	// __GEAR_SWAP_CHANGE
	virtual void HotKey_QuickItemSlot() {}	// ctrl + ~
	virtual void HotKey_Skill() = 0;			// ctrl + s
	virtual void HotKey_CharInfo() = 0;		// ctrl + i
	virtual void HotKey_SkillInfo() = 0;		// ctrl + k
	virtual void HotKey_Grade3Info() = 0;		// ctrl + a
	virtual void HotKey_Grade2Info() = 0;		// ctrl + r
	virtual void HotKey_Grade1Info() = 0;		// ctrl + c
	virtual void HotKey_Help() = 0;			// ctrl + h
	virtual void HotKey_WorldMap() = 0;		// ctrl + m
	virtual void HotKey_Minimap() = 0;		// ????
	virtual void HotKey_Chat_Up() = 0;		// ctrl + PgUp
	virtual void HotKey_Chat_Dn() = 0;		// ctrl + PgDn
	virtual void HotKey_Tribe_Prior() = 0;	// alt	+ PgUp
	virtual void HotKey_Tribe_Next() = 0;		// alt	+ PgDn
	virtual void HotKey_Guild_Info() = 0;		// ctrl	+ v
	virtual void HotKey_Guild_Member_List() = 0;// ctrl	+ l
	virtual void HotKey_Coer_Attack() = 0;	// ctrl	+ o
	virtual void HotKey_ZoneChat() = 0;		// ctrl + z
	virtual void HotKey_GuildChat() = 0;		// ctrl + g
	virtual void HotKey_UnionChat() = 0;		// ctrl + d
	virtual void HotKey_Whisper() = 0;		// ctrl + w
	virtual void HotKey_ExtendChat() = 0;		// ctrl + e
	virtual void HotKey_Sysrq() = 0;			// printscreen sysrq
	virtual void HotKey_Slash() = 0;			// ctrl + /
	virtual void HotKey_Background_Music() = 0;	// �?�???? /?????
	virtual void HotKey_Effect_Music() = 0;		// �?�???? /?????
	virtual void HotKey_Chat_Help() = 0;			// �?�???? /�?�???
	virtual void HotKey_Where() = 0;				// �?�???? /???

	virtual void HotKey_ESC() {}			// esc

	virtual void HotKey_F1() {}				// f1
	virtual void HotKey_F2() {}				// f2
	virtual void HotKey_F3() {}				// f3
	virtual void HotKey_F4() {}				// f4
	virtual void HotKey_F5() {}				// f5
	virtual void HotKey_F6() {}				// f6
	virtual void HotKey_F7() {}				// f7
	virtual void HotKey_F8() {}				// f8
	virtual void HotKey_F9() {}				// f9
	virtual void HotKey_F10() {}				// f10
	virtual void HotKey_F11() {}				// f11
	virtual void HotKey_F12() {}				// f12
	virtual void Hotkey_Function(int FKey) {} // HotKey �?? ??? 

	//	virtual void HotKey_F9()=0;				// f9
	//	virtual void HotKey_F10()=0;			// f10
	//	virtual void HotKey_F11()=0;			// f11
	//	virtual void HotKey_F12()=0;			// f12
	virtual void HotKey_NormalChat() = 0;
	virtual void HotKey_PartyChat() = 0;	// ctrl + a
	virtual void HotKey_Quest() = 0;		// ctrl + q

	// 2004, 5, 17 sobeit add start
	virtual void HotKey_SummonPet() = 0;	// ctrl + space
	// 2004, 5, 17 sobeit add end
#if __CONTENTS(__ITEM_SHOW)
	virtual void CloseInventory() = 0;
#endif //__ITEM_SHOW
};

enum CHAT_LINE_CONDITION
{
	CLD_NORMAL,				//0
	CLD_ZONECHAT,			//1
	CLD_WHISPER,			//2
	CLD_PARTY,				//3
	CLD_GUILD,				//4
	CLD_UNION,				//5
	CLD_INFO,				//6 ???? ?????.
	CLD_GRADEDISPLAY,		//7 ????? ??? ?????
	CLD_MASTER,				//8 ???? ?????

	CLD_TOTAL = CLD_MASTER,	//8
};

//-----------------------------------------------------------------------------
// class StringCell
//
// Single string class.
//-----------------------------------------------------------------------------
class StringCell
{
private:
	char* m_sz_string;

public:
	void	Release()
	{
		DeleteNewArray(m_sz_string);
	}

	StringCell()
	{
		m_sz_string = NULL;
	}

	virtual ~StringCell()
	{
		Release();
	}

	void	SetString(const char* sz_str)
	{
		if (sz_str == NULL)
			return;

		Release();
		// strcpy_s wants the destination size INCLUDING the null terminator.
		// Passing strlen() alone makes it reject every non-empty string with
		// ERANGE, which fast-fails the process through the CRT invalid
		// parameter handler -- so any chat line with a non-empty id died here.
		const size_t len = strlen(sz_str);
		m_sz_string = new char[len + 1];
		strcpy_s(m_sz_string, len + 1, sz_str);
	}

	const char* GetString() const { return m_sz_string; }
};

extern COLORREF g_color[4][4];

//-----------------------------------------------------------------------------
// class C_VS_UI_CHAT_LINE
//
//
//-----------------------------------------------------------------------------
class C_VS_UI_CHAT_LINE
{
private:
	StringCell					m_id_cell;
	StringCell					m_msg_cell;
	CHAT_LINE_CONDITION			m_condition;
	DWORD						m_Color;

public:
	C_VS_UI_CHAT_LINE()
	{
		m_condition = CLD_NORMAL;
		m_Color = g_color[0][0];
	}

	virtual ~C_VS_UI_CHAT_LINE() {}

	void	Set(const char* sz_id, const char* sz_msg, CHAT_LINE_CONDITION condition, DWORD color)
	{
		m_id_cell.SetString(sz_id);
		m_msg_cell.SetString(sz_msg);
		m_condition = condition;
		m_Color = color;
	}

	const char* GetIdString() const { return m_id_cell.GetString(); }
	const char* GetMsgString() const { return m_msg_cell.GetString(); }
	CHAT_LINE_CONDITION	GetCondition() const { return m_condition; }
	DWORD	GetColor() const { return m_Color; }
};

//-----------------------------------------------------------------------------
// class C_VS_CHAT_LIST
//
//
//-----------------------------------------------------------------------------
class C_VS_CHAT_LIST
{
private:
	SimpleDataList<C_VS_UI_CHAT_LINE*>		m_list;

public:
	C_VS_CHAT_LIST() {}
	~C_VS_CHAT_LIST()
	{
		C_VS_UI_CHAT_LINE* data;
		for (int i = 0; i < m_list.Size(); i++)
			if (m_list.Data(i, data))
				delete data;
	}

	void	Add(const char* sz_id, const char* sz_msg, CHAT_LINE_CONDITION condition, DWORD color)
	{
		C_VS_UI_CHAT_LINE* p_line = new C_VS_UI_CHAT_LINE;
		p_line->Set(sz_id, sz_msg, condition, color);

		m_list.Add(p_line);
	}

	int	Size() const { return m_list.Size(); }

	C_VS_UI_CHAT_LINE* PopBack()
	{
		// !data?? delete?????? ??�?.

		C_VS_UI_CHAT_LINE* data;

		if (m_list.Data(0, data))
		{
			m_list.Delete(data);
			return data;
		}

		return NULL;
	}

	C_VS_UI_CHAT_LINE* GetLine(int n) const
	{
		// n?? 0?? ???????? ???? ??�? line???.

		if (n < 0)
			return NULL;

		int index = m_list.Size() - n - 1;

		C_VS_UI_CHAT_LINE* data;

		if (m_list.Data(index, data))
			return data;

		return NULL;
	}
};

class PAPERING_HISTORY
{
public:
	std::string			m_string;
	std::vector<DWORD>	m_timer;
};

//-----------------------------------------------------------------------------
// C_VS_UI_CHATTING
//
// ??????? chatting?? ????(slayer = PCS)?? ???????.
//-----------------------------------------------------------------------------
class C_VS_UI_CHATTING : public Window, public Exec, public ButtonVisual
{
public:
	enum EXEC_ID
	{
		ALPHA_ID,
		PUSHPIN_ID,
		MARK_ID,
		COLOR_ID,
		LANGUAGE_ID,
		SPREAD_ID,

		// CHAT
		CHAT_NORMAL_ID,
		CHAT_ZONE_ID,
		CHAT_WHISPER_ID,
		CHAT_PARTY_ID,
		CHAT_GUILD_ID,
		CHAT_UNION_ID,

		// FILTER
		FILTER_NORMAL_ID,
		FILTER_ZONE_ID,
		FILTER_WHISPER_ID,
		FILTER_PARTY_ID,
		FILTER_GUILD_ID,
		FILTER_UNION_ID,
		// renewal column and menu row (ids 18-23)
		MENU_ID,
		SCROLL_UP_ID,
		SCROLL_DOWN_ID,
		SCROLL_END_ID,
		HIDE_ID,
		SETTING_ID,

	};


private:
	// chattingrenewal.spk - one pack for every race. Buttons are normal/hover
	// pairs (the colour button adds pressed), tabs are normal/lit pairs.
	enum RENEWAL_SPK_INDEX
	{
		RENEWAL_INPUT_LEFT      = 18,
		RENEWAL_INPUT_MIDDLE    = 19,
		RENEWAL_INPUT_RIGHT     = 20,
		RENEWAL_DIALOG          = 21,
		RENEWAL_ARROW_UP        = 24,
		RENEWAL_ARROW_DOWN      = 26,
		RENEWAL_ARROW_END       = 28,
		RENEWAL_MENU            = 30,   // megaphone: hide/show the chat menu
		RENEWAL_HIDE            = 32,
		RENEWAL_SETTING         = 34,   // gear: which channels the history shows
		RENEWAL_FILTER_OFF      = 36,
		RENEWAL_FILTER_ON       = 37,
		RENEWAL_GEM             = 38,   // whisper-list button
		RENEWAL_TAB_NORMAL      = 40,   // then zone, whisper, party, guild, union
		RENEWAL_BUTTON_COLOR    = 57,
		// the column icons and gear again, shrunk for 1280x720 and appended to the
		// loose pack in the same order (each still followed by its hover frame)
		RENEWAL_SMALL_ARROW_UP  = 66,
		RENEWAL_SMALL_SETTING   = 76,
	};

	// renewal layout, window-relative
	enum RENEWAL_LAYOUT
	{
		CHAT_COLUMN_W           = 28,   // button column on the left
		CHAT_MENU_H             = 24,   // gear + channel tab row along the top
		CHAT_INPUT_BAR_H        = 28,   // input band: the middle 28 of the art's 38 rows
		CHAT_INPUT_ART_TOP      = 5,    // first art row drawn into that band
		CHAT_INPUT_FIELD_X      = 98,   // where the text field starts
		CHAT_INPUT_TEXT_X       = 104,  // where input text starts
		CHAT_MODE_TAB_X         = 60,   // lit tab of the current channel, in the input bar
		CHAT_MIN_W              = 360,
		CHAT_MIN_H              = 140,
		CHAT_DEFAULT_W          = 460,
		CHAT_DEFAULT_H          = 140,
		CHAT_DEFAULT_LIFT       = 176,  // default bottom edge: just above the quickslot bar
		CHAT_CORNER_R           = 5,    // rounded right-hand corners: rows with an inset
		CHAT_DIALOG_W           = 160,  // colour picker and channel settings
		CHAT_DIALOG_H           = 100,
		SETTING_CELL_X          = 30,   // channel settings: 2 columns x 3 rows
		SETTING_CELL_Y          = 27,
		SETTING_CELL_W          = 60,
		SETTING_CELL_H          = 17,
	};

	enum MAIN_SPK_INDEX
	{
		MAIN,
		MAIN_ALPHA,
		MAIN_RIGHT,
		MAIN_BOTTOM,
		INPUT,
		INPUT_ALPHA,
		INPUT_RIGHT,
		BUTTON_SPREAD,
		BUTTON_SPREAD_HILIGHTED,
		BUTTON_SPREAD_HILIGHTED_PUSHED,
		BUTTON_FILTER,
		BUTTON_FILTER_HILIGHTED,
		BUTTON_FILTER_SELECTED,
		BUTTON_MARK,
		BUTTON_MARK_HILIGHTED,
		BUTTON_MARK_HILIGHTED_PUSHED,
		BUTTON_COLOR,
		BUTTON_COLOR_HILIGHTED,
		BUTTON_COLOR_HILIGHTED_PUSHED,
		BUTTON_HAN,
		BUTTON_HAN_HILIGHTED,
		BUTTON_HAN_HILIGHTED_PUSHED,
		BUTTON_ENG,
		BUTTON_ENG_HILIGHTED,
		BUTTON_ENG_HILIGHTED_PUSHED,
		BUTTON_NORMAL,
		BUTTON_NORMAL_HILIGHTED,
		BUTTON_NORMAL_HILIGHTED_PUSHED,
		BUTTON_NORMAL_SELECTED,
		BUTTON_NORMAL_SELECTED_PUSHED,
		BUTTON_WHISPER,
		BUTTON_WHISPER_HILIGHTED,
		BUTTON_WHISPER_HILIGHTED_PUSHED,
		BUTTON_WHISPER_SELECTED,
		BUTTON_WHISPER_SELECTED_PUSHED,
		BUTTON_ZONE,
		BUTTON_ZONE_HILIGHTED,
		BUTTON_ZONE_HILIGHTED_PUSHED,
		BUTTON_ZONE_SELECTED,
		BUTTON_ZONE_SELECTED_PUSHED,
		BUTTON_PARTY,
		BUTTON_PARTY_HILIGHTED,
		BUTTON_PARTY_HILIGHTED_PUSHED,
		BUTTON_PARTY_SELECTED,
		BUTTON_PARTY_SELECTED_PUSHED,
		BUTTON_GUILD,
		BUTTON_GUILD_HILIGHTED,
		BUTTON_GUILD_HILIGHTED_PUSHED,
		BUTTON_GUILD_SELECTED,
		BUTTON_GUILD_SELECTED_PUSHED,
		BUTTON_UNION,
		BUTTON_UNION_HILIGHTED,
		BUTTON_UNION_HILIGHTED_PUSHED,
		BUTTON_UNION_SELECTED,
		BUTTON_UNION_SELECTED_PUSHED,
		BUTTON_CHANNEL,
	};

	enum
	{
		CHAT_INPUT_LIMIT = 100,
	};

	enum HISTORY
	{
		HISTORY_SIZE = 200,
		HISTORY_SIZE_TEMP = 250,
	};

	enum
	{
		MARK_X = 12,
		MARK_Y = 17,
		COLOR_X = 20,
		COLOR_Y = 17,
	};

	enum RESIZE_STATE
	{
		RESIZE_NOT,
		RESIZE_LEFT,
		RESIZE_TOP,
		RESIZE_RIGHT,
		RESIZE_BOTTOM,
		RESIZE_LEFTTOP,
		RESIZE_RIGHTTOP,
		RESIZE_LEFTBOTTOM,
		RESIZE_RIGHTBOTTOM,
	};

private:
	int						CHAT_LINE_START_X, CHAT_LINE_START_Y;
	int						CHAT_HISTORY_START_Y;
	int						CHAT_WINDOW_WIDTH, CHAT_INPUT_WIDTH;
	int						CHAT_INPUT_START_X;	// where input text begins, inside the input field
	bool					m_bl_menu_open;		// megaphone: gear + channel tab row shown
	int						m_column_top;		// height of the column's button stack, from the bottom edge

	bool					m_bl_input_mode;
	bool					m_chat_filter[CLD_TOTAL];
	CHAT_LINE_CONDITION		m_chat_mode;
	CHAT_LINE_CONDITION		m_befor_chat_mode;

	Rect					m_backup_rect;

	int						m_sub_window;
	Rect					m_sub_rect;
	POINT					m_sub_selected;

	RESIZE_STATE			m_resize;
	POINT					m_backup_window_point;

	C_VS_UI_SCROLL_BAR* m_pC_scroll_bar, * m_pC_sub_scroll_bar;
	C_SPRITE_PACK* m_pC_chatting_spk;

	ButtonGroup* m_pC_button_group;
	ButtonGroup* m_pC_input_button_group;
	ButtonGroup* m_pC_menu_button_group;

	int							m_history_line;
	std::vector<PAPERING_HISTORY>	m_history;

	//	int							m_string_output_x; // ???�?? by larosel

	void	ScrollHistory();

	std::vector<std::string>	m_v_help_string;
	std::vector<bool>			m_v_help_check;

	//
	// Chat history buffer.
	//
	C_VS_CHAT_LIST				m_pC_history_list;
	C_VS_CHAT_LIST				m_pC_history_temp_list;

	int scroll_up_x, scroll_up_y, scroll_down_x, scroll_down_y, scrolltag_x, scrolltag_y, scrolltrack_x, scrolltrack_y;	// by larosel

	bool							m_chat_stacked[CLD_TOTAL];

	LineEditorVisual				m_lev_chatting;

	COLORREF						m_color_tab[CLD_TOTAL + 1];

	bool							m_bl_spreadID;

	std::vector<std::string>		m_sz_whisper_id;	// by larosel
	std::string						m_sz_whisper_backup;	// by larosel
	bool							m_bl_whisper_mode;	// by larosel
	bool							m_bl_focus_whisper;	// by larosel
	int								m_whisper_index;	// by larosel

	//
	// Vampire/Slayer ?? ?? ??�?? ?? ??? Window?? ???? 2??(Inventory, Gear)???.
	// ??? ?? ???? ??�???? ??? click focus?? ??? ?????? ????? ????????? ???.
	//

//	int								m_slayer_chat_mode;	// ???�?? by larosel
//	void	AddChatToHistoryTemp(char * str, char * sz_id, CHAT_LINE_CONDITION condition);	// ???�?? by laorsel

	enum
	{
		TIMER_NONE,
		TIMER_ZONECHAT,
		TIMER_REP,
		TIMER_PAPERING,
		TIMER_HIDE,
	};

	// TIMER
	std::vector<DWORD>			m_dw_rep_tickcount;
	std::vector<DWORD>			m_dw_papering_tickcount;
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_zonechat_timer;
	DWORD						m_dw_rep_timer;
	DWORD						m_dw_papering_timer;
	DWORD						m_dw_help_timer;
	DWORD						m_dw_help_prev_tickcount;
	DWORD						m_dw_hide_timer;
	DWORD						m_dw_hide_prev_tickcount;
	int							m_timer;

	bool	Timer(bool reset = false);
	bool	TimerHelp();
	bool	TimerHide(bool reset = false);

public:
	void	Extend();

	void	SetSubWindow(int type) { m_sub_window = type; }
	//-------------------------
	// WHISPER	// by larosel
	//-------------------------
	std::string	GetWhisperID(int num = -1);										// by larosel
	int		GetWhisperSize() { return m_sz_whisper_id.size(); }	// by larosel
	bool	AddWhisperID(const char* sz_ID);	// by larosel
	void	ChangeWhisperFocus();												// by larosel
	bool	GetWhisperFocus() { return m_bl_focus_whisper; }		// by larosel
	bool	SlayerWhisperMode(bool mode);										// by larosel
	void	TribeChanged();
	bool	IsSpreadID() { return m_bl_spreadID; }
	bool	IsPixel(int _x, int _y);
	void	SetWhisperID(char* id);
	bool	IsInputMode() { return m_bl_input_mode; }
	int		GetChatMode() { return m_chat_mode; }				// 2007 01 16 by diesirace
	int		SetChatMode(int chat_mode);											// 2007 01 17 by diesirace
	LineEditorVisual	GetChatLev() { return m_lev_chatting; }			// 2007 01 23 by diesirace
	//---------------------------
	// GUILDCHAT // by larosel
	//---------------------------
	void	SetGuildChat(bool guild);

	void	ResetScroll();	// by larosel

	C_VS_UI_CHATTING();
	~C_VS_UI_CHATTING();

	void	Acquire() { m_lev_chatting.Acquire(); }
	bool	IsEmpty() { return (m_lev_chatting.Size() <= 0); }
	void	Start();
	void	Finish();

	void	RestoreHistoryTemp();
	void	Show();
	bool	MouseControl(UINT message, int _x, int _y);
	//	bool	MouseControlExtra(UINT message, int x, int y);	// by sigi
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	AddChatToHistory(const char* str, const char* sz_id, CHAT_LINE_CONDITION condition, DWORD color);
	void	AddToChatHistory(const char* sz_str, const char* sz_id, CHAT_LINE_CONDITION condition, DWORD color);
	void	SetInputString(const char* pString);	// by sigi
	void	AddInputString(const char* pString);	// by sigi
	void	SetInputStringColor(COLORREF rgb) { m_lev_chatting.SetInputStringColor(rgb); } // by sigi
	const char* GetInputString() const { return (const char*)m_lev_chatting.GetString(); }
#if __CONTENTS(__ITEM_SHOW)
	const char* GetNewInputString() { char* p_temp = NULL; g_Convert_DBCS_Ascii2SingleByte(m_lev_chatting.GetString(), m_lev_chatting.Size(), p_temp); return p_temp; }
#endif //__ITEM_SHOW
	void	InsertMark(char_t ch) { m_lev_chatting.InsertMark(ch); }

	bool	IsNormalChatStacked() { return m_chat_stacked[CLD_NORMAL]; }
	bool	IsWhisperStacked() { return m_chat_stacked[CLD_WHISPER]; }
	bool	IsZoneChatStacked() { return m_chat_stacked[CLD_ZONECHAT]; }
	bool	IsGuildChatStacked() { return m_chat_stacked[CLD_GUILD]; }
	bool	IsPartyChatStacked() { return m_chat_stacked[CLD_PARTY]; }
	bool	IsInfoStacked() { return m_chat_stacked[CLD_INFO]; }

	// common
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
		m_pC_input_button_group->UnacquireMouseFocus();
		m_pC_menu_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
		m_pC_input_button_group->CancelPushState();
		m_pC_menu_button_group->CancelPushState();
	}
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	bool	GetOccludeRect(int* px0, int* py0, int* px1, int* py1) const;
	bool	IsPanelOpen() const;	// the chat line is open: panel, input bar and menu show
	void	AcquireDisappear() {}
	void	Run(id_t id);

	void	Process();

	bool	IsCannotSendChatInput();		// Chat Message ?????? ??????? ????????
};

//-----------------------------------------------------------------------------
// class C_VS_UI_INVENTORY
//
// slayer/vampire inventory base class.
//
// - slayer/vampire inventory ?????? interface?? ???????. 
// - slayer???? vampire?? ????? ??? ?? ????? ??, ??�?? ????????
//   inventory?? ??????????, inventory?? item?? ???? ???????. interface??????
//   inventory?? item?? ??????? ???? ???. ????? ?? class?? base?? ??? ?????.
//-----------------------------------------------------------------------------
class C_VS_UI_INVENTORY : public Window, public Exec, public ButtonVisual
{
	//-----------
	// Data
	//-----------
public:
	enum
	{
		GRID_X = 10,
		GRID_Y = 6,
		GRID_UNIT_PIXEL_X = 30,
		GRID_UNIT_PIXEL_Y = 30,
	};

private:

protected:
	enum INVENTORY_SPK_INDEX
	{
		INVENTORY_WINDOW,
		INVENTORY_WINDOW_ALPHA,
		INVENTORY_ITEMBACK,
		INVENTORY_ITEMBACK_ALPHA,
		INVENTORY_WINDOW_BOTTOM,
		//*
		INVENTORY_CONTRACT_OF_BLOOD_SLOT_1,
		INVENTORY_CONTRACT_OF_BLOOD_SLOT_2,
		INVENTORY_CONTRACT_OF_BLOOD_SLOT_3,
		INVENTORY_CONTRACT_OF_BLOOD_SLOT_4,
		/**/
	};

	enum EXEC_ID
	{
		MONEY_ID,
		DESC_ID,
		//		BIKE_ID,
		//		EXCHANGE_ID,

		HELP_ID,
		CLOSE_ID,
		ALPHA_ID,
	};

	ButtonGroup* m_pC_button_group;

	bool						m_bl_shift, m_bl_set_load;;

	C_SPRITE_PACK* m_pC_inventory_spk;
	Rect						m_grid_rect; // ??� Grid rect.

	int							m_focus_grid_x, m_focus_grid_y;

	// ????? class???? ???? set????? ???.
	int							m_grid_start_offset_x, m_grid_start_offset_y;
	int							m_money_button_offset_x, m_money_button_offset_y;

private:
	BOOL						m_bLimited_Item_Change;
	int							m_focus_grid_x_Prev, m_focus_grid_y_Prev;

	//2008.09.24 shootkj
	//????? ???? ???? ???????? ?�??? ??????? ??� ??? ???????? cannotadd?? ?? ?? ??�? ??????? 
	//??�?? ???? ????? ??? ????? ???? ??? ???.

	//------------
	// Method
	//------------
private:
	void	SetDebugStart();
	void	SetDebugEnd();
	void	WriteLogLine(int line);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	UnacquireMouseFocus();
	void	AcquireDisappear();
	void	AcquireMouseFocus();
	//	void	CancelPushState();
	bool	AllMatchWindowPixel(int _x, int _y) const;
	bool	AnyMatchWindowPixel(int _x, int _y) const;

protected:
	bool	Click(int grid_start_x, int grid_start_y);
	void	Use();


public:
	// TIMER
	static bool		Timer(bool reset = false);
	static DWORD						m_dw_millisec;

	static C_SPRITE_PACK* m_pC_mine_progress_spk;
	enum MINE_PROGRESS_SPK_INDEX
	{
		INVENTORY_BAR_BACK,
		INVENTORY_BAR,
		SKILL_BAR_BACK,
		SKILL_BAR,
	};

	static int					m_mine_grid_x, m_mine_grid_y;

	C_VS_UI_INVENTORY();
	virtual ~C_VS_UI_INVENTORY();

	//??????
	bool	StartInstallMineProgress(int focus_grid_x, int focus_grid_y);
	bool	IsInstallMineProgress() { return gbl_mine_progress; }
	void	EndInstallMineProgress() { gbl_mine_progress = false; }
	//????????
	bool	StartCreateMineProgress(int focus_grid_x, int focus_grid_y);
	bool	IsCreateMineProgress() { return gbl_mine_progress; }
	void	EndCreateMineProgress() { gbl_mine_progress = false; }
	//??? ?????
	bool	StartCreateBombProgress(int focus_grid_x, int focus_grid_y);
	bool	IsCreateBombProgress() { return gbl_mine_progress; }
	void	EndCreateBombProgress() { gbl_mine_progress = false; }

	void	Start(bool bl_set_load = true);
	void	Finish();
	void	Show();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	Run(id_t id);

	void	ResetRect();
	bool	TestGridRect(int _x, int _y) const;
	int	GetFocusedItemGridX(const MItem* p_item);
	int	GetFocusedItemGridY(const MItem* p_item);
	int	GetFocusedItemGridH(const MItem* p_item);
	Rect	GetGridRect() const { return m_grid_rect; }

	int		GetFocusGridX() { return  m_focus_grid_x; }
	int		GetFocusGridY() { return  m_focus_grid_y; }

	static void	AutoMove(int grid_x, int grid_y);


	void	Prev_Item_Position_Remove();
	//2008.09.24 shootkj
	//????? ???? ???? ???????? ?�??? ??????? ??� ??? ???????? cannotadd?? ?? ?? ??�? ??????? 
	//??�?? ???? ????? ??? ????? ???? ??? ???.

	DWORD	m_dwWidth;
	DWORD	m_dwHight;

	int		m_nGearItemQuickViewScroll;
};

//-----------------------------------------------------------------------------
// class C_VS_UI_GEAR
//
// vampire/slayer gear base class.
//-----------------------------------------------------------------------------
class C_VS_UI_GEAR : public Window, public Exec, public ButtonVisual
{
	//-----------
	// Data
	//-----------
protected:
	// MyInformation.spk: the renewal equipment and character information window
	enum GEAR_SPK_INDEX
	{
		GEAR_WINDOW = 0,
		GEAR_BACKDROP_SLAYER = 1,		// behind the paperdoll
		GEAR_BACKDROP_VAMPIRE = 2,
		GEAR_BACKDROP_OUSTERS = 3,
		GEAR_LINE_V = 4,				// 1x569
		GEAR_LINE_H = 5,				// 584x1
		GEAR_CHANGE_ID1_UNCHECK = 6,	// the I and II gear set tabs
		GEAR_CHANGE_ID1_CHECK = 7,
		GEAR_CHANGE_ID2_UNCHECK = 9,
		GEAR_CHANGE_ID2_CHECK = 10,
		GEAR_CLOSE = 12,				// +1 focused, +2 pushed
		GEAR_NICK_DROP = 15,			// +1 focused, +2 pushed
		GEAR_LABEL_BOX = 24,
		GEAR_VALUE_BOX = 25,
		GEAR_EXP_BACK = 27,
		GEAR_EXP_BAR = 28,
		GEAR_SECTION = 29,
		GEAR_LEVEL_MARK = 31,
		GEAR_PLUS = 38,
		GEAR_SLOT_SQUARE = 39,			// 66x66
		GEAR_SLOT_SMALL = 40,			// 36x36
		GEAR_SLOT_TALL = 41,			// 66x96
		GEAR_BLOOD_BIBLE_BLOCK = 56,
		GEAR_WINDOW_ALPHA = GEAR_WINDOW,	// there is no see-through version
	};

	enum EXEC_ID
	{
		HELP_ID,
		CLOSE_ID,

		// ???????? ??????? ????
		FIRST_ID,
		SECOND_ID,

		ALPHA_ID,

		// ????� ??� ???
		GEAR_ID1,
		GEAR_ID2,
		NICK_ID,					// the nickname drop-down
		STR_PLUS_ID,				// spend a bonus point
		DEX_PLUS_ID,
		INT_PLUS_ID,
	};

	ButtonGroup* m_pC_button_group;

	C_SPRITE_PACK* m_pC_gear_spk; // gear Window image
	C_SPRITE_PACK* m_pC_gear_slot_spk; // gear slot image
	//by csm 2004.12.30  
	C_SPRITE_PACK* m_pC_advance_gear_spk; // Advencegear Window image


	int							m_focus_slot;
	bool						m_bl_set_load;

	// ????? class???? ???? set????? ???.
	int								m_slot_size;
	Rect* m_p_slot_rect;
	int* m_p_slot_image;
	BOOL 							m_bl_Abvencement;

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// C_VS_UI_GEAR ???? � ??? ?? ID?? ???? ???? ????
	DWORD							m_dwSendGearID;							//?????? ???? GearID
	DWORD							m_dwAccepGearID;						//???????? ???? GearID
	DWORD							m_dwGearChange_ID1_Button_Pos_X;		//????�?? ??�?? ????? ???
	DWORD							m_dwGearChange_ID1_Button_Pos_Y;
	DWORD							m_dwGearChange_ID1_Button_Width;		//????�?? ??�?? ????? ???
	DWORD							m_dwGearChange_ID1_Button_Height;
	DWORD							m_dwGearChange_ID2_Button_Pos_X;		//????�?? ??�?? ????? ???
	DWORD							m_dwGearChange_ID2_Button_Pos_Y;
	DWORD							m_dwGearChange_ID2_Button_Width;		//????�?? ??�?? ????? ???
	DWORD							m_dwGearChange_ID2_Button_Height;
#endif	// __GEAR_SWAP_CHANGE
	// 

	//	bool							m_bl_close_button_pushed;
	//	bool							m_bl_help_button_pushed;
	//	bool							m_bl_close_button_focused;
	//	bool							m_bl_help_button_focused;
	//	int							m_close_button_offset_x, m_close_button_offset_y;
	//	int							m_help_button_offset_x, m_help_button_offset_y;


	void	Use();
	void	ShowInformationFrame();		// the renewal window around the items
	void	ShowInformationText();
	//------------
	// Method
	//------------
private:
	//	void	CancelPushState();
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear();
	void	AcquireMouseFocus();
	void	UnacquireMouseFocus();
	bool	AnyMatchWindowPixel(int _x, int _y) const;
	bool	AllMatchWindowPixel(int _x, int _y) const;
	bool	TestSlotRect(int _x, int _y) const;
	bool	IsPixel(int _x, int _y);

public:
	C_VS_UI_GEAR();
	virtual ~C_VS_UI_GEAR();

	void	Start(bool bl_set_load = true);
	void	Finish();

	bool	Click(int window_x, int window_y, Rect* slot_rect);
	bool	MouseControl(UINT message, int _x, int _y);
	void	Show();
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	Run(id_t id);
	void	SetFocusSlot(BYTE Slot) { m_focus_slot = Slot; }

#if __CONTENTS(__GEAR_SWAP_CHANGE)			// C_VS_UI_GEAR ????� ??� ??? ?? ??? ????? ??? ????
	void	GearChange();
	void	GearChange(DWORD	dwGearID);
	void	GearChangeButtonShow();
#endif //__GEAR_SWAP_CHANGE

};

//-----------------------------------------------------------------------------
// class C_VS_UI_SKILL
//
// vampire/slayer skill base class.
//-----------------------------------------------------------------------------
class C_VS_UI_SKILL : public Window
{
	friend class C_VS_UI_HOTKEY_BAR;	// draws skill icons the way this box does
public:
	static CSpritePack				m_C_spk; // Skill icon Sprite list
	static CSpritePack				m_C_spk_mini; // Skill icon Sprite list
	static CSpritePack				m_C_spk_comboCnt;

	enum HOTKEY
	{
		HOTKEY1,
		HOTKEY2,
		HOTKEY3,
		HOTKEY4,

		//????? ???
		HOTKEY5,
		HOTKEY6,
		HOTKEY7,
		HOTKEY8,
		//
		HOTKEY9,
		HOTKEY10,
		HOTKEY11,
		HOTKEY12,

		HOTKEY_MAX,
	};

	enum HOTKEY_GRADE
	{
		GRADE1,
		GRADE2,
		GRADE3,
		GRADE4,

		GRADE_MAX,
	};

protected:
	int							m_skill_hotkey_buf[HOTKEY_MAX][GRADE_MAX];
	int							m_current_skill_set, m_current_skill_grade;
	enum
	{
		// ?? ?????? ??? ?? ??? skill ???? 100?? ??????...
		SPREAD_X_MAX = 10, // ???????? ???? ?????? ??? ????(� line?? Spread button?? ???????).
		SPREAD_Y_MAX = 10,
	};

	C_SPRITE_PACK				m_etc_spk;

	// ????? ??�???? set???? ??.
	int							m_skill_guard_x, m_skill_guard_y;
	int							m_skill_start_x, m_skill_start_y;
	int							m_skill_guard_extra_offset;
	int							m_extra_icon_offset_x, m_extra_icon_offset_y;

	enum ETC_SPK_INDEX
	{
		SKILL_GUARD, // skill icon ????
		SKILL_EMPTY_BUTTON,
		SKILL_PUSHED_BUTTON,
	};

	int							m_comboCnt;
	int							m_selected_skillid; // NOT_SELECTED??? ???�??? ???? ?????. ACTIONINFO?? ??????.
	bool						m_selected_comboAttackskill;
	int							m_focused_slot; // Spread button?? 0???? ??? ?�??? ??? ???????.
	bool						m_bl_pushed;
	bool						m_bl_open;

	// Progress Bar ????
	bool						m_bl_show_progress;
	int							m_progress_skill_id;
	CPoint						m_progress_inventory_grid;
	MItem* m_pC_progress_item;
	CTickTimer					m_progress_timer;

	void	ResetSize();
	int		GetFocusSlot(int _x, int _y) const;

	bool	AbleToUse(int id) const;
	bool	IsEnableSkill(int id) const;
	int		GetDelay(int id) const;

	bool	NoPassive(int n);
	bool	findSkillAvailable(ACTIONINFO id);

	// TIMER
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_millisec;

	bool	Timer(bool reset = false);

	void	ProcessSkillCastingProgress();

	void	DrawSkillIcon(CPoint ptPos, int nSkillID);

public:
	C_VS_UI_SKILL();
	virtual ~C_VS_UI_SKILL();

	void	SetStartPoint(int x, int y) { m_skill_start_x = x; m_skill_start_y = y; ResetSize(); }
	int		GetSelectedSkillID();
	void	SelectSkill(int id);
	int		GetHotkey(HOTKEY hotkey, HOTKEY_GRADE grade) const { return m_skill_hotkey_buf[hotkey][grade]; }
	void	ChangeSkillWheel(bool direct);
	void	ChangeSkillByHotkey(HOTKEY hotkey);
	int		GetSkillID(int n);
	int		GetFocusedSlot() const { return m_focused_slot; }
	void	SetHotkey(HOTKEY hotkey, ACTIONINFO id);
	void	ToggleWindow();
	Point	GetIconPoint(int n) const;
	void	CloseInterface();
	void	UnselectSkill();

	void	AcquireDisappear() {}
	void	CancelPushState();
	void	UnacquireMouseFocus();
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y) { return false; }
	bool	IsPixel2(int _x, int _y);

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show() { return; }
	void	Show2();
	void	Start();
	void	Process();
	void	ResetSkillSet();
	void	SetComboCnt(int ComboCnt);
	void	SetSelectedAttackComboSkill(bool	bAttackSkill);
	void	ResetHotkey();
	void	InitHotKey(HOTKEY hotkey);

	void	StartSkillCastingProgress(int skillID, DWORD time, CPoint inventoryGrid = CPoint(-1, -1));
	void	EndSkillCastingProgress();
	bool	IsSkillCastingProgress() { return m_bl_show_progress; }
};

//-----------------------------------------------------------------------------
// class C_VS_UI_HPBAR
//
// vampire/slayer HPBar class
//-----------------------------------------------------------------------------
class C_VS_UI_HPBAR : public Window, public Exec, public ButtonVisual
{
private:
	bool					m_width_mode, m_small_mode;
	C_SPRITE_PACK* m_pC_hpbar_spk;

	ButtonGroup* m_pC_width_button_group;
	ButtonGroup* m_pC_height_button_group;
	ButtonGroup* m_pC_small_width_button_group;
	ButtonGroup* m_pC_small_height_button_group;

	enum HPBAR_SPK_INDEX
	{
		MAIN_WIDTH,
		MAIN_HEIGHT,
		HPBAR_WIDTH,
		HPBAR_HEIGHT,

		// slayer
		MPBAR_WIDTH,
		MPBAR_HEIGHT,
		HPBAR_BLOOD_WIDTH,
		HPBAR_BLOOD_HEIGHT,
		CHANGE_BUTTON_WIDTH,
		CHANGE_BUTTON_WIDTH_HILIGHTED,
		CHANGE_BUTTON_HEIGHT,
		CHANGE_BUTTON_HEIGHT_HILIGHTED,

		SLAYER_MAX,

		// vampire
		EXPBAR_WIDTH = MPBAR_WIDTH,
		EXPBAR_HEIGHT,
		HPBAR_SILVER_WIDTH,
		HPBAR_SILVER_HEIGHT,
		CHANGE_BUTTON,
		CHANGE_BUTTON_PUSHED,
		CHANGE_BUTTON_HILIGHTED,
		CHANGE_BUTTON_HILIGHTED_PUSHED,
		SMALL_BUTTON,
		SMALL_BUTTON_PUSHED,
		SMALL_BUTTON_HILIGHTED,
		SMALL_BUTTON_HILIGHTED_PUSHED,

		VAMPIRE_MAX,

		// ousters				
		OUSTERS_EXPBAR_WIDTH = HPBAR_BLOOD_WIDTH,
		OUSTERS_EXPBAR_HEIGHT,
		OUSTERS_HPBAR_BLOOD_WIDTH,
		OUSTERS_HPBAR_BLOOD_HEIGHT,
		OUSTERS_HPBAR_SILVER_WIDTH,
		OUSTERS_HPBAR_SILVER_HEIGHT,
		OUSTERS_CHANGE_BUTTON_WIDTH,
		OUSTERS_CHANGE_BUTTON_WIDTH_PUSHED,
		OUSTERS_CHANGE_BUTTON_HEIGHT,
		OUSTERS_CHANGE_BUTTON_HEIGHT_PUSHED,
		OUSTERS_SMALL_BUTTON_WIDTH,
		OUSTERS_SMALL_BUTTON_WIDTH_PUSHED,
		OUSTERS_SMALL_BUTTON_HEIGHT,
		OUSTERS_SMALL_BUTTON_HEIGHT_PUSHED,

		OUSTERS_MAX,

		OUSTERS_2ND_MPBAR_WIDTH = 40,
		OUSTERS_2ND_MPBAR_HEIGHT,
		OUSTERS_3ND_MPBAR_WIDTH,
		OUSTERS_3ND_MPBAR_HEIGHT,

		OUSTERS_2ND_SMALL_MPBAR_WIDTH,
		OUSTERS_2ND_SMALL_MPBAR_HEIGHT,
		OUSTERS_3ND_SMALL_MPBAR_WIDTH,
		OUSTERS_3ND_SMALL_MPBAR_HEIGHT,
	};

	enum EXEC_ID
	{
		CHANGE_ID,
		RESIZE_ID,
	};

	int	m_small_offset;

	// Opaque bounds of each main sprite, window-relative, indexed
	// (vertical ? 1 : 0) + (small ? 2 : 0). See GetOccludeRect().
	RECT	m_rcOpaque[4];

	int				MainSpriteIndex() const;
	ButtonGroup*	CurrentButtonGroup() const;
	void			ComputeOpaqueBounds();

public:
	C_VS_UI_HPBAR();
	~C_VS_UI_HPBAR();

	// Draws the HP / level / MP readouts over the horizontal bar. The vertical
	// bar has 11px-wide channels, so there is no room for them there.
	void	ShowBarText(int hp_cx, int mid_cx, int right_cx, int bar_y,
						const char* szHP, const char* szMid, const char* szRight);

	void	UnacquireMouseFocus()
	{
		m_pC_width_button_group->UnacquireMouseFocus();
		m_pC_height_button_group->UnacquireMouseFocus();
		m_pC_small_width_button_group->UnacquireMouseFocus();
		m_pC_small_height_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_width_button_group->CancelPushState();
		m_pC_height_button_group->CancelPushState();
		m_pC_small_width_button_group->CancelPushState();
		m_pC_small_height_button_group->CancelPushState();
	}
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	bool	GetOccludeRect(int* px0, int* py0, int* px1, int* py1) const;
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
};



//-----------------------------------------------------------------------------
// class C_VS_UI_BLOOD_BURST
//
// vampire/slayer BloodBurst class
//-----------------------------------------------------------------------------
class C_VS_UI_BLOOD_BURST : public Window, public Exec, public ButtonVisual
{
private:

	enum EXEC_ID
	{
		BLOODBURST_CHANGE_ID,	// unused since the circles: they have no vertical layout
		ATTACK_ID,
		DEFENSE_ID,
		PARTY_ID,
	};

	// BloodBurstRenewal.spk (renewal art): 33x33 cells, one pack for
	// every race
	enum RENEWAL_SPK_INDEX
	{
		RENEWAL_FRAME,
		RENEWAL_ATTACK,		// red circle
		RENEWAL_DEFENSE,	// blue circle
		RENEWAL_PARTY,		// green circle
		RENEWAL_LETTER_A,	// letters show once a gauge is full - click one to burst
		RENEWAL_LETTER_D,
		RENEWAL_LETTER_P,
		// appended to the loose pack by Tools/Sprites: the same seven shrunk (sharper
		// at the 1.5x present), then the pieces of the full-gauge glow
		RENEWAL_SMALL_FRAME = 7,		// then attack, defense, party, A, D, P
		RENEWAL_LIT_ATTACK = 14,		// brightened circles, blended in while full
		RENEWAL_HALO_OUTER_ATTACK = 17,	// circle + 2 * GLOW_MARGIN discs in each gauge's glow colour
		RENEWAL_HALO_MID_ATTACK = 20,	// circle + GLOW_MARGIN, drawn 2px in
		RENEWAL_GLOW_FRAME_COUNT = 23,
	};

	enum	BLOOD_BURST_MAX
	{
		ATTACK_MAX_POINT = 3000,
		DEFENSE_MAX_POINT = 2000,
		PARTY_MAX_POINT = 20000,
	};

	enum { GAUGE_COUNT = 3, GLOW_MARGIN = 4 };	// attack, defense, party; glow room around each circle

	bool						m_bGageAttackFull;
	bool						m_bGageDefenseFull;
	bool						m_bGagePartyFull;

	int							m_iAttackGage;
	int							m_iDefenseGage;
	int							m_iPartyGage;

	C_SPRITE_PACK* m_pC_BloodBurst_spk;
	ButtonGroup* m_pC_button_group;
	bool						m_glow;			// the shrunk set and its glow frames are in the pack
	int							m_image_base;	// RENEWAL_SMALL_FRAME, or RENEWAL_FRAME without them
	int							m_margin;		// GLOW_MARGIN, or 0 without them

	int		GaugeCount() const;			// attack and defense, plus party while in a party
	bool	IsGaugeFull(int gauge) const;

public:
	C_VS_UI_BLOOD_BURST();
	~C_VS_UI_BLOOD_BURST();

	void	UnacquireMouseFocus() { m_pC_button_group->UnacquireMouseFocus(); }
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	bool	GetOccludeRect(int* px0, int* py0, int* px1, int* py1) const;
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();

	void	SetGage();
	void	SetAttackGage();
	void	SetDefenseGage();
	void	SetPartyGage();

	bool	GetAttackGageFull() { return	m_bGageAttackFull; }
	bool	GetDefenseGageFull() { return	m_bGageDefenseFull; }
	bool	GetPartyGageFull() { return	m_bGagePartyFull; }
};




//-----------------------------------------------------------------------------
// class C_VS_UI_BLOOD_BURST
//
// vampire/slayer BloodBurst class
//-----------------------------------------------------------------------------
/*class C_VS_UI_MARKET_ACCOUNT  : public Window, public Exec, public ButtonVisual
{
private:


	enum EXEC_ID
	{
		MARKETM_ID,
		MARKETB_ID,
		MARKETH_ID,
	};


	enum MARKET_ACCOUNT_SPK_INDEX
	{
		MARKETM_BUTTON ,
		MARKETM_BUTTON_HILIGHTED ,
		MARKETM_BUTTON_PUSHED ,

		MARKETB_BUTTON ,
		MARKETB_BUTTON_HILIGHTED ,
		MARKETB_BUTTON_PUSHED ,

		MARKETH_BUTTON ,
		MARKETH_BUTTON_HILIGHTED ,
		MARKETH_BUTTON_PUSHED ,
	};


	C_SPRITE_PACK	*			m_pC_Market_spk;

	ButtonGroup *				m_pC_Market_button_group;


public:
	C_VS_UI_MARKET_ACCOUNT();
	~C_VS_UI_MARKET_ACCOUNT();

	void	UnacquireMouseFocus()
	{
		m_pC_Market_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_Market_button_group->CancelPushState();
	}

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
}	;
*/


//-----------------------------------------------------------------------------
// class C_VS_UI_EFFECT_STATUS
//
// vampire/slayer EFFECT_STATUS class
//-----------------------------------------------------------------------------
class C_VS_UI_EFFECT_STATUS : public Window
{
private:
	// Renewal layout: no frame, only the icons, half transparent, flush in
	// the top-left corner and wrapping every ICONS_PER_ROW.
	enum
	{
		ICON_SIZE = 36,			// a full skill icon (C_VS_UI_SKILL::m_C_spk)
		ICONS_PER_ROW = 16,
		MAX_ICONS = 30,
	};

	int		IconCount() const;
	int		HitIcon(int _x, int _y) const;
	void	ShowIcon(int index, int sprite_id);

public:
	C_VS_UI_EFFECT_STATUS();
	~C_VS_UI_EFFECT_STATUS();

	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
};


struct MINIMAP_NPC
{
	int x;
	int y;
	int id;
	MString name;
};

struct MINIMAP_SHRINE
{
	int x;
	int y;
	int id;
	MString name;
	BYTE type;
};

struct MINIMAP_PORTAL
{
	CRect	position;
	int		zoneID;
};

//-----------------------------------------------------------------------------
// class C_VS_UI_MINIMAP
//
// vampire/slayer MINIMAP class
//-----------------------------------------------------------------------------
class C_VS_UI_MINIMAP : public Window, public Exec, public ButtonVisual
{
private:
	C_SPRITE_PACK* m_pC_minimap_spk;

	CSpriteSurface* m_p_minimap_surface;
	ButtonGroup* m_pC_button_group;

	bool								m_bl_refresh;
	POINT								m_map_start_point;
	std::vector<RECT>					m_portal;
	std::vector<int>					m_portal_zone_id;
	std::vector<MINIMAP_NPC>			m_npc;
	std::vector<MINIMAP_SHRINE>			m_shrine;
	std::vector<POINT>					m_Block;
	std::vector<MINIMAP_NPC>			m_Flag;

	std::string m_zone_name;
	int									m_surface_w, m_surface_h;
	int									m_map_cut;	// map window columns left out for a narrow map
	int									m_map_x, m_map_y, m_map_w, m_map_h, m_zone_id;

	//timer
	DWORD						m_dw_minimap_prev_tickcount;
	DWORD						m_dw_minimap_millisec;

	bool						m_bMiniMapDisableZone;	// ?????? ??????? ??? ?????.

#if __CONTENTS(__GPS_ADD)
	int							m_GPSBoard_X;
	int							m_GPSBoard_Y;
	int							m_GPSButton_X;
	int							m_GPSButton_Y;
	bool						m_bGPSViewOpen;

	S_GPS_NPC_INFO				m_Gps_User_Info;
#endif // __GPS_ADD

	bool	TimerMinimap();

	enum MINIMAP_SPK_INDEX	// MinimapRenewal.spk, the renewal minimap, for every race
	{
		MINIMAP_PANEL = 0,
		MINIMAP_WORLDMAP_BUTTON = 1,	// +1 highlighted, +2 pushed
		MINIMAP_PIN = 9,				// a plain circle, as on the simple information panel
		MINIMAP_PIN_LIT = 10,
		MINIMAP_ICON_SELF = 11,
		MINIMAP_ICON_PARTY = 12,
		MINIMAP_ICON_PARTY_DEAD = 18,
	};

	// Positions relative to the panel.
	enum MINIMAP_LAYOUT
	{
		MINIMAP_MARGIN = 2,				// from the right and bottom of the screen
		MINIMAP_MAP_X = 7,				// the window the map shows through
		MINIMAP_MAP_Y = 28,
		MINIMAP_MAP_RIGHT = 200,
		MINIMAP_MAP_BOTTOM = 128,
		MINIMAP_TITLE_Y = 5,
		MINIMAP_PIN_X = 226,
		MINIMAP_PIN_Y = 6,
		MINIMAP_WORLDMAP_X = 209,
		MINIMAP_WORLDMAP_Y = 105,
		MINIMAP_COORD_X = 214,			// X and Y print centred across this column
		MINIMAP_COORD_W = 21,
		MINIMAP_COORD_X_Y = 53,
		MINIMAP_COORD_Y_Y = 89,
		MINIMAP_SEAM_X = 72,			// where a narrow map's panel is cut, see Show
	};

	enum EXEC_ID
	{
		ALPHA_ID,
		PUSHPIN_ID,

#if __CONTENTS(__GPS_ADD)
		GPSVIEW_ID,
#endif //__GPS_ADD
		WORLDMAP_ID,
	};

	bool	m_bWindowEvent;

public:
	void SetBlock(int x, int y);
	C_VS_UI_MINIMAP();
	~C_VS_UI_MINIMAP();

	// 	static	int GetZoneNumber(int zone_id);
	// 	static	char * GetZoneName(int zone_id);

	int		GetZoneID() { return m_zone_id; }
	void	SetZone(int zone_id);
	void	SetSize(SIZE size) { m_map_w = size.cx; m_map_h = size.cy; }
	void	SetPortal(RECT rect, int id);
	void	SetNPC(MINIMAP_NPC npc);
	void	ClearNPC() { m_npc.clear(); }
	void	SetSafetyZone(RECT rect, bool my_zone);
	void	SetFlagArea(POINT pt);
	void	SetXY(int x, int y) { m_map_x = x; m_map_y = y; }
	int		GetX() { return m_map_x; }
	int		GetY() { return m_map_y; }

	// Where the minimap rests: the bottom-right corner, MINIMAP_MARGIN in.
	// Auto-hide slides it away from here, and a drag moves it.
	void	GetRestingRect(RECT* rect) const;
	void	ResetWidth();					// fits the panel to a narrow map

	void	TogglePushPin() { Run(PUSHPIN_ID); }

	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	MouseControlExtra(UINT message, int _x, int _y);
#if __CONTENTS(__MOVE_ZONE)
	bool	SetMoveZone(int iPox_X, int iPox_Y);
#endif //__MOVE_ZONE
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();

	void	ResetBoardPosition();

private:
#if __CONTENTS(__GPS_ADD)
	void	GPSRun();
#endif //__GPS_ADD
};




#if __CONTENTS(__JAPAN_UI)
#define MARK_MAX 3
#else
#define MARK_MAX 6
#endif //__JAPAN_UI
extern const char g_mark[MARK_MAX][9][7];

#define BLANK_TIMER 500
//-----------------------------------------------------------------------------
// class C_VS_UI_QUEST_STATUS
//
//
//-----------------------------------------------------------------------------
class C_VS_UI_QUEST_STATUS : public Window, public Exec, public ButtonVisual
{
public:

	struct QUEST_STATUS
	{
		char* Title;
		DWORD			QuestID;
		DWORD			current_point;
		DWORD			quest_time;
	};

	QUEST_STATUS		m_quest_status;					// ???? ???????? ????? ????
	bool				m_bl_active;
	bool				m_bl_timeover;
	bool				m_bl_focus;

	DWORD				m_timer;
	DWORD				m_timer2;
	CSpriteSurface* m_p_back_surface;
	std::vector<std::string>					m_hard_cording;		// ?? ??????!!!


private:

	ButtonGroup* m_pC_button_group;

	enum EXEC_ID
	{
		PUSHPIN_ID,
		ALPHA_ID,
		CLOSE_ID,
		HELP_ID,

		DETAIL_ID,
	};

public:
	void IncreaseQuestPoint();

	C_VS_UI_QUEST_STATUS();
	~C_VS_UI_QUEST_STATUS();


	DWORD	GetQuestStatusID() { return m_quest_status.QuestID; }
	void	SetQuestStatusInit();
	void	SetQuestStatus(QUEST_STATUS& status);
	void	ToggleWindow();
	void	ShowQuestDescription(int _x, int _y);

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	std::string		GetDetailInfo();

	bool	IsPixel(int _x, int _y);
	int		Timer(int time = -1);
	int		Timer2(int time = -1);

	void	ShowDesc(int strX, int strY, const char* str);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}
};



//-----------------------------------------------------------------------------
// class C_VS_UI_HOTKEY_BAR
//
// The renewal shortcut bar: a movable strip of twelve slots showing what F1-F12
// are bound to, a skill at its selected grade or a quick item. Binding still
// happens the old way, by pressing the key over the skill box or a quick slot.
//-----------------------------------------------------------------------------
class C_VS_UI_TRIBE;
class MItem;

class C_VS_UI_HOTKEY_BAR : public Window, public Exec, public ButtonVisual
{
private:
	enum SHORTCUT_SPK_INDEX	// ShortcutSlot.spk, the renewal shortcut slots
	{
		SHORTCUT_SLOT = 12,			// the dark slot behind each key
		SHORTCUT_LABEL = 13,		// the small bar under it that the key name prints on
		SHORTCUT_PIN = 14,
		SHORTCUT_PIN_FOCUSED = 15,
		SHORTCUT_SELECTED = 16,		// frames the slot of the skill in use
		SHORTCUT_SELECTED_LABEL = 17,	// and its label
	};

	// Offsets are from a slot's top-left.
	enum BAR_LAYOUT
	{
		BAR_SLOT_COUNT = 12,
		BAR_SLOT_PITCH = 43,
		BAR_ICON_X = 2,
		BAR_ICON_Y = 3,
		BAR_SELECTED_X = -6,
		BAR_SELECTED_Y = -6,
		BAR_SELECTED_LABEL_X = 4,
		BAR_SELECTED_LABEL_Y = 34,
		BAR_LABEL_X = 6,
		BAR_LABEL_Y = 35,
		BAR_LABEL_W = 30,
		BAR_LABEL_TEXT_Y = 37,
		BAR_COUNT_RIGHT = 39,			// a stack's item count, right-aligned
		BAR_COUNT_Y = 23,
		BAR_STACK_PITCH = 37,			// hovering a skill key stacks its other grades
		BAR_STACK_GAP = 5,
		BAR_STACK_LABEL_H = 14,
	};

	enum EXEC_ID
	{
		BAR_PIN_ID,
	};

	C_VS_UI_TRIBE* m_p_tribe;
	C_SPRITE_PACK* m_pC_spk;
	ButtonGroup* m_pC_button_group;
	bool m_bl_folded;					// down to just the pin

	int		SlotX(int slot) const { return x + slot * BAR_SLOT_PITCH; }
	int		GetHotkeySkill(int fkey, int* grade);
	const MItem* GetHotkeyItem(int fkey);
	int		HoveredSlot();
	void	ShowSkillIcon(int _x, int _y, int skill_id);
	void	ResetSize();

public:
	C_VS_UI_HOTKEY_BAR(C_VS_UI_TRIBE* p_tribe);
	~C_VS_UI_HOTKEY_BAR();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event) {}
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra) {}

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
};



//-----------------------------------------------------------------------------
// class C_VS_UI_SKILL_BOOK
//
// The renewal "Skills & Runes" window with a Rank tab of our own: the race's
// skills under sub tabs, its rank skills, and the rare and advanced skills in
// the lists on the right. Runes is a stub.
//-----------------------------------------------------------------------------
class C_VS_UI_SKILL_BOOK : public Window, public Exec, public ButtonVisual
{
public:
	enum TAB
	{
		TAB_SKILLS,
		TAB_RANK,
		TAB_RUNES,
		TAB_COUNT
	};

private:
	enum SKILL_BOOK_SPK_INDEX	// SkillWindow.spk, the renewal skill window
	{
		BOOK_WINDOW = 0,
		BOOK_TAB = 4,				// 92x22: normal, focused, selected
		BOOK_SUB_TAB = 7,			// 82x22: normal, focused, selected
		BOOK_DOMAIN_ICON = 10,		// 18x18: blade, sword, gun, heal, enchant
		BOOK_CLOSE = 23,			// +1 focused, +2 pushed
		BOOK_SCROLL_UP = 26,		// +1 focused, +2 pushed
		BOOK_SCROLL_DOWN = 29,
		BOOK_SLOT = 32,				// 40x42 behind a skill
		BOOK_LEVEL_BAR = 33,		// 30x15 under it
		BOOK_TREE_COMBAT = 34,		// the lines of the ousters trees
		BOOK_TREE_ELEMENTAL = 35,
	};

	enum RUNE_TAB_SPK_INDEX		// RuneTab.spk, the renewal rune tab
	{
		RUNE_BAR_BACK = 3,
		RUNE_BAR = 4,
	};

	enum
	{
		MAX_SUB_TABS = 6,
		GRID_COLUMNS = 6,
		LIST_COUNT = 2,				// rare skills, advanced skills
		LIST_ROWS = 4,
		RANK_TIERS = 10,			// a rank name each
		RANK_TABS_PER_ROW = 5,
		RANK_ROWS = 7,				// rank skills shown at once
	};

	enum EXEC_ID
	{
		CLOSE_ID,
		SCROLL_UP_ID,
		SCROLL_DOWN_ID,
		TAB_ID,						// + TAB
		SUB_TAB_ID = TAB_ID + TAB_COUNT,	// + sub tab
		RANK_TAB_ID = SUB_TAB_ID + MAX_SUB_TABS,	// + rank tier
	};

	// an icon on the grid, the tree or a list, where it was last drawn
	struct ENTRY
	{
		int id;					// skill id, or rank bonus index on the Rank tab
		int sprite;
		int state;
		int label;				// the level under a grid icon, or -1
		int domain;				// SKILLDOMAIN, for the tooltip
		bool passive;
		bool enabled;
		int x, y;				// the icon, in the window
	};

	C_SPRITE_PACK* m_pC_spk;
	C_SPRITE_PACK* m_pC_rune_spk;
	ButtonGroup* m_pC_button_group;
	C_VS_UI_DIALOG* m_pC_confirm;

	int m_tab;
	int m_sub_tab;
	int m_sub_tab_count;
	int m_sub_tab_key[MAX_SUB_TABS];	// slayer domain, vampire skill group, ousters tree
	int m_scroll;					// grid rows, or tree pixels
	int m_scroll_max;
	int m_list_scroll[LIST_COUNT];
	int m_rank_tier;				// the rank on show: five grades each
	int m_rank_tab_tier[RANK_TIERS];	// the ranks that have rank skills, one per tab
	int m_rank_tab_count;
	int m_rank_learnable;			// a bit per rank with a skill to learn
	int m_desc_domain;				// what the skill tooltip looks the skill up in
	bool m_bOustersDownSkill;		// opened by the NPC who lowers skills: a learnt skill's card offers that
	std::vector<ENTRY> m_entries;
	std::vector<ENTRY> m_list[LIST_COUNT];

	bool	IsTree() const;			// the ousters trees rather than a grid
	int		GetDomain() const;
	int		GetLineY() const;		// the level line, under one or two rows of sub tabs
	void	LayoutTabs();			// hides the sub tabs of the other tabs
	void	Rebuild();
	void	BuildGrid();
	void	BuildTree();
	void	BuildRank();
	void	BuildLists();
	void	LayoutGrid(std::vector<ENTRY>& entries);
	int		HitEntry(int _x, int _y) const;
	int		HitList(int _x, int _y, int& list) const;
	void	Scroll(int step);
	void	LearnRankSkill(const ENTRY& entry);
	void	LearnAdvancedSkill(const ENTRY& entry);
	int		GetLineExp(bool& max_level) const;
	void	ShowLevelBar();
	void	ShowRankText();
	void	ShowText();

public:
	C_VS_UI_SKILL_BOOK();
	~C_VS_UI_SKILL_BOOK();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event) {}
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra) {}

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	void	StartOustersDownSkill();
	// R: open (or raise) the window on the Rank tab
	void	StartRank();
	bool	OnRankTab() const	{ return m_tab == TAB_RANK; }
};



class C_VS_UI_TRIBE : public Window, public HotKey, public Exec, public ButtonVisual
{
	friend class C_VS_UI_HOTKEY_BAR;	// reads the F-key bindings
public:
	enum	HOTKEYTYPE
	{
		QUICKITEM_TYPE,
		SKILL_TYPE,
		NOT_SELECT_TYPE,
	};

protected:

	// simpleinformation.spk, the renewal status panel
	enum SIMPLE_SPK_INDEX
	{
		SIMPLE_EXP_TRACK = 0,
		SIMPLE_EXP_FILL = 1,
		SIMPLE_CIRCLE_LIT = 4,
		SIMPLE_CIRCLE = 5,			// the pin
		SIMPLE_DAY_FRAME = 6,
		SIMPLE_DAY_BAR = 7,
		SIMPLE_NIGHT_BAR = 8,
		SIMPLE_SUN = 9,
		SIMPLE_MOON = 10,
		SIMPLE_DOMAIN = 13,			// + SKILLDOMAIN_BLADE .. SKILLDOMAIN_ENCHANT
		SIMPLE_DOMAIN_LIT = 18,		// the same five, for a domain with levels
		SIMPLE_DOMAIN_FRAME = 23,
		SIMPLE_EARTH = 24,
		SIMPLE_WATER = 25,
		SIMPLE_FIRE = 26,
		SIMPLE_PANEL = 30,
	};

	// Where things go on the panel. Relative to
	// the window, which is SIMPLE_PANEL's top-left; the art is transparent
	// above SIMPLE_PANEL_TOP.
	enum SIMPLE_LAYOUT
	{
		SIMPLE_PANEL_TOP = 56,
		SIMPLE_PIN_X = 8,
		SIMPLE_PIN_Y = 63,
		SIMPLE_TIME_Y = 62,
		SIMPLE_SUN_Y = 73,
		SIMPLE_DAY_Y = 78,

		SIMPLE_STAT_W = 54,			// a stat's label and value share a column this wide
		SIMPLE_EXP_LABEL_X = 20,
		SIMPLE_EXP_TRACK_X = 44,

		SIMPLE_SLAYER_STAT_Y = 99,
		SIMPLE_DOMAIN_X = 35,
		SIMPLE_DOMAIN_GAP = 38,
		SIMPLE_DOMAIN_LEVEL_Y = 110,
		SIMPLE_DOMAIN_Y = 118,
		SIMPLE_SLAYER_EXP_LABEL_Y = 138,
		SIMPLE_SLAYER_EXP_Y = 140,

		SIMPLE_VAMPIRE_STAT_Y = 110,
		SIMPLE_OUSTERS_STAT_Y = 100,
		SIMPLE_OUSTERS_ELEMENT_Y = 115,
		SIMPLE_EXP_LABEL_Y = 131,		// vampires and ousters
		SIMPLE_EXP_Y = 134,
	};

	enum EXEC_INDEX	// by larosel
	{
		// COMMON
		PUSHPIN_ID,
		SYSTEM_ID,

		MENU_INFO_ID,
		MENU_GUILD_ID,
		MENU_COMMUNITY_ID,
		MENU_SHOP_ID,
		MENU_HELP_ID,

		//////////////////////////////////////////////////////////////////////////
		// MENU TAB
		INVENTORY_ID,
		GEAR_ID,
		INFO_ID,
		PARTY_ID,
		QUEST_ID,
		MAIL_ID,
#if __CONTENTS(__SMS_SERVICES)
		SMS_ID,
#endif
		NAMING_ID,

		// TEAM TAB
		TEAM_INFO_ID, // ??� ?????
		TEAM_MEMBER_LIST_ID, // ??� ??? ???
		//		TEAM_COMMAND_ID, // ??? ????
		TEAM_LIST_ID, // ??? ?????
		TEAM_WAIT_LIST_ID, // ??? ??? ?????
		TEAM_UNION_ID,		// ???? ????

		// UTIL TAB
		UTIL_STORE_ID, // ??� ??? ????
		//#if __CONTENTS(__POWER_JJANG_ID)
		//		UTIL_POWER_JJANG_ID,
		//#endif
#if __CONTENTS(__DARKEDEN_MARKET)
		UTIL_MARKETM_ID,
#endif //__DARKEDEN_MARKET
		UTIL_MARKETB_ID,

#if __CONTENTS(__FRIEND_ADDITION)
		UTIL_FRIEND_SYSTEM,
		UTIL_FRIEND_WAIT,
#endif //__FRIEND_ADDITION	


		// HELP TAB
		HELP_ID,
		CHAT_HELP_ID,
		BATTLE_HELP_ID,
		SKILL_HELP_ID,
		GUILD_HELP_ID,
		WORLD_MAP_HELP_ID,

		//
		//////////////////////////////////////////////////////////////////////////


#if __CONTENTS(__USER_GRADE)
		USER_GRADE,
#endif
		EXEC_MAX
	};




	C_VS_UI_SKILL* m_pC_skill;

	C_VS_UI_LEVELUP* m_pC_level_up;
	Point						m_backup_inventory_xy, m_backup_gear_xy;
	ButtonGroup* m_pC_common_button_group;


	// 	ButtonGroup *				m_pC_menu_button_group;
	// 	ButtonGroup *				m_pC_guild_button_group;
	// 	ButtonGroup *				m_pC_msg_button_group;
	// 	ButtonGroup *				m_pC_util_button_group;
	// 	ButtonGroup *				m_pC_help_button_group;

	C_VS_UI_HPBAR* m_pC_hpbar;
	C_VS_UI_BLOOD_BURST* m_pC_BloodBurst;
	//C_VS_UI_MARKET_ACCOUNT*		m_pC_Market;

	C_VS_UI_EFFECT_STATUS* m_pC_effect_status;
	C_VS_UI_MINIMAP* m_pC_minimap;
	C_VS_UI_HOTKEY_BAR* m_pC_hotkey_bar;
	C_VS_UI_SKILL_BOOK* m_pC_skill_book;
	C_VS_UI_CHATTING* m_pC_chatting;
	C_VS_UI_SLAYER_QUICKITEM* m_pC_quickitem;

	C_VS_UI_OUSTERS_QUICKITEM* m_pC_armsband;
	C_VS_UI_QUEST_STATUS* m_pC_quest_status;

	C_VS_UI_INVENTORY* m_pC_inventory;
	//C_VS_UI_QUEST_STATUS *		m_pC_quest;

	C_SPRITE_PACK* m_pC_simple_spk;


	std::string m_time;
	std::string m_date;

	int							m_selected_menu;

	//	bool						m_bl_help, m_bl_party;

		//timer
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_millisec;


	id_t						m_OpenedHelpIdx;
	int							m_HotKey_Type[12];

	bool	Timer();

public:
	void	MouseControlExtra(UINT message, int _x, int _y)
	{
		if (m_pC_minimap != NULL)
		{
			m_pC_minimap->IsInRect(_x, _y);
			m_pC_minimap->MouseControlExtra(message, _x, _y);
		}
	}
	void	ResetOpenedHelpIdx() { m_OpenedHelpIdx = EXEC_MAX; }

	//??????
	void	StartInstallMineProgress(int focus_grid_x, int focus_grid_y)
	{
		if (m_pC_inventory)m_pC_inventory->StartInstallMineProgress(focus_grid_x, focus_grid_y);
	}
	bool	IsInstallMineProgress() { return gbl_mine_progress; }
	void	EndInstallMineProgress() { gbl_mine_progress = false; }
	//????????
	void	StartCreateMineProgress(int focus_grid_x, int focus_grid_y)
	{
		if (m_pC_inventory)m_pC_inventory->StartCreateMineProgress(focus_grid_x, focus_grid_y);
	}
	bool	IsCreateMineProgress() { return gbl_mine_progress; }
	void	EndCreateMineProgress() { gbl_mine_progress = false; }
	//??? ?????
	void	StartCreateBombProgress(int focus_grid_x, int focus_grid_y)
	{
		if (m_pC_inventory)m_pC_inventory->StartCreateBombProgress(focus_grid_x, focus_grid_y);
	}
	bool	IsCreateBombProgress() { return gbl_mine_progress; }
	void	EndCreateBombProgress() { gbl_mine_progress = false; }

	//???? Progress Bar
	void	StartSkillCastingProgress(int skillID, DWORD time, CPoint inventoryGrid = CPoint(-1, -1))
	{
		if (m_pC_skill) m_pC_skill->StartSkillCastingProgress(skillID, time, inventoryGrid);
	}
	bool	IsSkillCastingProgress()
	{
		return m_pC_skill && m_pC_skill->IsSkillCastingProgress();
	}
	void	EndSkillCastingProgress()
	{
		if (m_pC_skill) m_pC_skill->EndSkillCastingProgress();
	}


	int		GetSelectedMenu() { return m_selected_menu; }
	void	SetSelectMenu(int menu);

	void	SetHotkey(C_VS_UI_SKILL::HOTKEY hotkey, ACTIONINFO id)
	{
		GetSkillWindow()->SetHotkey(hotkey, id);
	}

	void	ResetSkillSet()
	{
		if (m_pC_skill != NULL)
			m_pC_skill->ResetSkillSet();
	}

	int		GetSelectedSkillID()
	{
		if (m_pC_skill != NULL)
			return m_pC_skill->GetSelectedSkillID();
		else return -1;
	}

	void	SetComboCnt(int ComboCnt)
	{
		if (m_pC_skill != NULL)
			m_pC_skill->SetComboCnt(ComboCnt);
	}

	void	SetSelectedAttackComboSkill(bool	bAttackSkill)
	{
		if (m_pC_skill != NULL)
			m_pC_skill->SetSelectedAttackComboSkill(bAttackSkill);
	}

	//void	SetGage()
	//{
	//	if(m_pC_BloodBurst!=NULL)
	//		m_pC_BloodBurst->SetGage()	;
	//}

	void	SetBloodBurstAttackGage()
	{
		if (m_pC_BloodBurst != NULL)
			m_pC_BloodBurst->SetAttackGage();
	}

	void	SetBloodBurstDefenseGage()
	{
		if (m_pC_BloodBurst != NULL)
			m_pC_BloodBurst->SetDefenseGage();
	}

	void	SetBloodBurstPartyGage()
	{
		if (m_pC_BloodBurst != NULL)
			m_pC_BloodBurst->SetPartyGage();
	}


	bool	GetBloodBurstAttackGageFull()
	{
		if (m_pC_BloodBurst != NULL)
			return	m_pC_BloodBurst->GetAttackGageFull();
		return false;
	}

	bool	GetBloodBurstDefenseGageFull()
	{
		if (m_pC_BloodBurst != NULL)
			return	m_pC_BloodBurst->GetDefenseGageFull();
		return false;
	}

	bool	GetBloodBurstPartyGageFull()
	{
		if (m_pC_BloodBurst != NULL)
			return	m_pC_BloodBurst->GetPartyGageFull();
		return false;
	}



	int	GetHotkey(C_VS_UI_SKILL::HOTKEY hotkey, C_VS_UI_SKILL::HOTKEY_GRADE grade) const
	{
		return GetSkillWindow()->GetHotkey(hotkey, grade);
	}

	void	SetTime(const char* str) { m_time = str; }
	void	SetDate(const char* str) { m_date = str; }
	void	ToggleMinimap() { m_pC_minimap->TogglePushPin(); }

	virtual void	RunQuickItemSlot() = 0;
	virtual void	CloseQuickItemSlot() = 0;
	virtual bool	IsRunningQuickItemSlot() = 0;
	void	RunMinimap() {}
	void	CloseMinimap() {}
	bool	IsRunningMinimap() { return false; }
	void	RunMark() {}
	void	CloseMark() {}
	bool	IsRunningMark() { return false; }
	void	SetWhisperID(char* id) { if (m_pC_chatting)m_pC_chatting->SetWhisperID(id); }

	bool	IsRunningQuestStatusWindow() { if (m_pC_quest_status) return m_pC_quest_status->Running(); return false; }
	void	OpenQuestStatusWindow() { if (!m_pC_quest_status->Running()) m_pC_quest_status->Start(); }
	void	CloseQuestStatusWindow() { if (m_pC_quest_status->Running()) m_pC_quest_status->Finish(); }
	void	SetQuestStatusWindow(C_VS_UI_QUEST_STATUS::QUEST_STATUS& status) { if (m_pC_quest_status) m_pC_quest_status->SetQuestStatus(status); }
	DWORD	GetQuestStatusID() {
		if (m_pC_quest_status) return m_pC_quest_status->GetQuestStatusID();
		else return 0xffffffff;
	}
	void	UnSetQuestStatusWindow() { if (m_pC_quest_status) m_pC_quest_status->SetQuestStatusInit(); }

	void	LevelUp()
	{
		// ??? ?? ?????? ?????? ?????.
		// ??? ???? closing interface??...

		if (!m_pC_level_up)
		{
			m_pC_level_up = new C_VS_UI_LEVELUP;
			m_pC_level_up->Start();
		}
	}

	bool	IsRunningLevelUp()
	{
		return (m_pC_level_up != NULL);
	}

	void	FinishLevelUp()
	{
		DeleteNew(m_pC_level_up);
	}

	void	AcquireChatting()
	{
		m_pC_chatting->Acquire();
	}

	bool	IsEmptyChatting()
	{
		return m_pC_chatting->IsEmpty();
	}

	virtual void	DoCommonActionBeforeEventOccured(); // ?????? ??
	virtual void	DoCommonActionAfterEventOccured()  // ????? ??
	{
		CloseInventory();
		CloseGear();

		//		InitWindowToggleFlag();
		GetInventoryWindow()->AttrWindowMove(true);
		GetGearWindow()->AttrWindowMove(true);

		// restore xy
		InventoryXY(m_backup_inventory_xy.x, m_backup_inventory_xy.y);
		GearXY(m_backup_gear_xy.x, m_backup_gear_xy.y);

		gpC_base->FinishEvent();
	}

	void	OpenInventoryToSell();
	void	FinishItemSelling();

	void	OpenInventoryToRepair();
	void	FinishItemRepairing();

	void	OpenInventoryToSilvering();
	void	FinishItemSilvering();

	void	InventoryXY(int _x, int _y)
	{
		GetInventoryWindow()->XY(_x, _y);
		GetInventoryWindow()->ResetRect();
	}

	void	GearXY(int _x, int _y)
	{
		GetGearWindow()->XY(_x, _y);
	}

	void	ShopRunningAnnounced(); // Shop?? ???? ????? Window?? ????.

	void	StorageRunningAnnounced();

	void	GetItemBoxRunningAnnounced();

	void	ExchangeRunningAnnounced();

	void	SetChattingInterface(C_VS_UI_CHATTING* p_chatting);

	virtual void	ResetSlayerQuickItemSize() {}
	virtual void	ResetOustersQuickItemSize() {}
	virtual void	OpenGear(bool bl_set_load = true) = 0;
#if __CONTENTS(__GEAR_SWAP_CHANGE)			//?????? ??� ???? ???? ??? ????
	virtual	void	RunGearChange() = 0;
#endif //__GEAR_SWAP_CHANGE
	virtual void	CloseGear() = 0;
	virtual C_VS_UI_GEAR* GetGearWindow() const = 0;

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);

	C_VS_UI_TRIBE();
	virtual ~C_VS_UI_TRIBE();

	void	SetupMenuItems();


	void	Start();

	void	Show();
	virtual void ShowExp() = 0;
	bool	GetOccludeRect(int* px0, int* py0, int* px1, int* py1) const;

protected:
	bool	IsSimplePanelShown() const { return GetAttributes()->autohide == ATTRIBUTES_HIDE_NOT; }
	void	ShowDayBar();
	void	ShowSimpleStats(int row_y, int* value_x = NULL);
	void	ShowSimpleExp(int track_y, int label_y);
public:
	static void	GetSimpleExp(__int64& goal_exp, __int64& exp_remain);	// the equipment window's EXP bar too
protected:
	void	ShowSimpleDescription(int _x, int _y);
	void	PlaceSkillBox(bool bl_force);

public:

	void Finish()
	{
		PI_Processor::Finish();

		gpC_window_manager->DisappearWindow(this);
	}

	void	Process();

	void	AcquireDisappear() {}

	virtual void CancelPushState()
	{
		m_pC_common_button_group->CancelPushState();
	}

	virtual void UnacquireMouseFocus()
	{
		m_pC_common_button_group->UnacquireMouseFocus();
	}

	void AcquireFirstSequence()
	{

	}

	Point GetInventoryPosition() const
	{
		Point point(GetInventoryWindow()->x, GetInventoryWindow()->y);

		return point;
	}

	Point	GetInventoryGridPosition(int grid_x, int grid_y) const
	{
		Point point(GetInventoryWindow()->x + GetInventoryWindow()->GetGridRect().x + C_VS_UI_INVENTORY::GRID_UNIT_PIXEL_X * grid_x,
			GetInventoryWindow()->y + GetInventoryWindow()->GetGridRect().y + C_VS_UI_INVENTORY::GRID_UNIT_PIXEL_Y * grid_y);

		return point;
	}

	Point	GetInventoryGetWidthAndHeight()
	{
		Point pt;
		pt.x = GetInventoryWindow()->m_dwWidth;
		pt.y = GetInventoryWindow()->m_dwHight;
		return pt;
	}

	void	Run(id_t id);
	bool	IsPixel(int _x, int _y);
	C_VS_UI_SKILL* GetSkillWindow() const { return m_pC_skill; }
	C_VS_UI_INVENTORY* GetInventoryWindow() const { return m_pC_inventory; }
	void	CloseInventory() { m_pC_inventory->Finish(); }
	void	OpenInventory(bool bl_set_load = true) { if (m_pC_inventory != NULL) m_pC_inventory->Start(bl_set_load); }

	void	WindowEventReceiver(id_t event);
	bool	MouseControl(UINT message, int _x, int _y);

	void	SetZone(int zone_id) { m_pC_minimap->SetZone(zone_id); }
	int		GetZoneID() { return m_pC_minimap->GetZoneID(); }
	void	SetBlock(int x, int y) { m_pC_minimap->SetBlock(x, y); }
	void	SetSize(SIZE size) { m_pC_minimap->SetSize(size); }
	void	SetXY(int x, int y) { m_pC_minimap->SetXY(x, y); }
	int		GetX() { return m_pC_minimap->GetX(); }
	int		GetY() { return m_pC_minimap->GetY(); }
	void	SetSafetyZone(RECT rect, bool my_zone) { m_pC_minimap->SetSafetyZone(rect, my_zone); }
	void	SetNPC(MINIMAP_NPC npc) { m_pC_minimap->SetNPC(npc); }
	void	ClearNPC() { m_pC_minimap->ClearNPC(); }
	void	SetPortal(RECT rect, int id) { m_pC_minimap->SetPortal(rect, id); }


	bool	CloseInventoryGearWindow();
	bool	CloseSkillBook();
	void	SetOustersDownSkill()	{ if (m_pC_skill_book != NULL) m_pC_skill_book->StartOustersDownSkill(); }
	bool	GetGearOpenState() const;
	bool	GetInventoryOpenState() const;

	void	UnselectSkill() { GetSkillWindow()->UnselectSkill(); }
	void	ChangeSkillWheel(bool direct) { GetSkillWindow()->ChangeSkillWheel(direct); }
	void	SelectSkill(int id) { GetSkillWindow()->SelectSkill(id); }

	void	OnClick_HelpTap(id_t execidx);

	void	HotKey_Party();
	void	HotKey_Mark();
	void	HotKey_Help();
	void	HotKey_SkillInfo();
	void	HotKey_Grade3Info();
	void	HotKey_Grade2Info();
	void	HotKey_Grade1Info();
	void	HotKey_Minimap();
	void	HotKey_WorldMap();
	void	HotKey_CharInfo();
	//void	HotKey_WindowToggle();
	void	HotKey_Inventory(bool IsCheckSubInventory = false);
	void	HotKey_Gear();
#if	__CONTENTS(__GEAR_SWAP_CHANGE)	//C_VS_UI_TRIBE		//HotKey_GearChange();
	void	HotKey_GearChange();
	void	HotKey_GearChangeShow();
#endif	//__GEAR_SWAP_CHANGE
	void	HotKey_Skill();
	void	HotKey_ExtendChat();		// ctrl + e
	void	HotKey_Chat_Up();			// ctrl + PgUp
	void	HotKey_Chat_Dn();			// ctrl + PgDn
	void	HotKey_Tribe_Prior();		// alt	+ PgUp
	void	HotKey_Tribe_Next();		// alt	+ PgDn
	void	HotKey_Guild_Info();		// ctrl	+ v
	void	HotKey_Guild_Member_List();	// ctrl	+ l
	void	HotKey_Coer_Attack();		// ctrl	+ o
	void	HotKey_Sysrq();				// printscreen sysrq
	void	HotKey_Slash();				// ctrl + /
	void	HotKey_Background_Music();	// �?�???? /?????
	void	HotKey_Effect_Music();		// �?�???? /?????
	void	HotKey_Chat_Help();			// �?�???? /�?�???
	void	HotKey_ZoneChat();			// �?�???? /z
	void	HotKey_GuildChat();			// �?�???? /g
	void	HotKey_UnionChat();			// �?�???? /u
	void	HotKey_Whisper();			// �?�???? /w
	void	HotKey_Where();				// �?�???? /???
	//	void	HotKey_F9();	
	//	void	HotKey_F10();
	//	void	HotKey_F11();
	//	void	HotKey_F12();
	void	HotKey_PartyChat();			// �?�???? /p
	void	HotKey_NormalChat();		// �?�???? /c
	void	HotKey_Quest();				// ctrl + q
	void	HotKey_MailBox();			// ctrl + b
	void	HotKey_PetInfo();			// ctrl + CapsLock
	void    HotKey_SummonPet();			// ctrl + space
	void	HotKey_SMSWindow();
	void	HotKey_NamingWindow();

	// 2005, 1, 3, sobeit add start
	void	OpenInventoryToSwapAdvanceItem();
	void	FinishSwapAdvancementItem();
	// 2005, 1, 3, sobeit add end

	void	Inventory_Item_Position_Remove();
	//2008.09.24 shootkj
	//?�??? ??????? ????? ??� ??? ???? ???????? cannotadd?? ?????? ???????.
	//??? ???? ??� ?? ?? ????. ??? ??????? ??� ?�??? ???.
	//??�?? ???? ????? ????? ??? ???? ??? ??? ??? ???.
};

//-----------------------------------------------------------------------------
// C_VS_UI_INFO
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_INFO : public Window, public Exec, public ButtonVisual
{
public:

	enum INFO_MODE
	{
		CHARACTER_INFO_MODE = 0,
		SKILL_INFO_MODE,
		GRADE1_INFO_MODE,
		GRADE2_INFO_MODE,
		GRADE3_INFO_MODE,
		RARE_SKILL_INFO_MODE,
		INFO_MODE_MAX,
	};

	static int				m_selected_grade_skill;
	static int				m_selected_skill_domain;
	static int				m_ousters_Magic;
	static int				m_vampire_ACType;

	static int				m_selected_ACSkillID;

private:
	struct PETINFO* m_pPetInfo;
	C_SPRITE_PACK			m_petButtonSpk;

	C_VS_UI_DIALOG* m_pC_learn_grade_skill_confirm;
	Rect					m_rt_tab;

	int						m_focused_skill_id;
	//bool					m_skill_info_mode;
	INFO_MODE				m_info_mode;
	int						m_iDomain;
	int						m_iGrade;
	int						m_draw_grade_skill_mark;

	int						m_modify_wide;

	std::vector<int>		m_grade_skill_id;

	SKILLDOMAIN				m_skill_domain;

	MSkillDomain::SKILL_STEP_LIST	m_advance_skill_id_vec;		// ??? ??�?? ???? ??? ????? ???????.
	MSkillDomain::SKILL_STEP_LIST	m_rare_skill_id_vec;		// ??? ??�?? ???? ??? ????? ???????.

	int						m_rare_skill_max;					// ?????? ??? ?? ??? ??????? ???


	ButtonGroup* m_pC_common_button_group;
	ButtonGroup* m_pC_char_button_group;
	ButtonGroup* m_pC_skill_button_group;
	ButtonGroup* m_pC_grade1_button_group;
	ButtonGroup* m_pC_grade2_button_group;
	ButtonGroup* m_pC_grade3_button_group;
	C_VS_UI_SCROLL_BAR* m_pC_char_scroll_bar;
	C_VS_UI_SCROLL_BAR* m_pC_skill_scroll_bar;
	C_VS_UI_SCROLL_BAR* m_pC_skill_scroll_bar_width;
	C_VS_UI_SCROLL_BAR* m_pC_grade1_scroll_bar;
	C_VS_UI_SCROLL_BAR* m_pC_grade3_scroll_bar;
	C_VS_UI_SCROLL_BAR* m_pC_rare_skill_scroll_bar;
	CSprite* m_p_guild_mark;

	RECT					m_rcSkillDesciption;

	POINT					m_CenterPos;
	bool					m_bOustersDownSkill;

	enum EXEC_ID
	{
		ALPHA_ID,
		CLOSE_ID,
		HELP_ID,

		// SLAYER SKILL INFO
		BLADE_ID,
		SWORD_ID,
		GUN_ID,
		HEAL_ID,
		ENCHANT_ID,
		TOTAL_ID,

		// VAMPIRE SKILL INFO
		POISON_ID,
		ACID_ID,
		CURSE_ID,
		SUMMON_ID,
		BLOOD_ID,
		INNATE_ID,

		// OUSTERS SKILL INFO
		COMBAT_ID,
		ELEMENTAL_ID,

		// VAMPIRE CHARACTER INFO
		STR_PLUS_ID,
		DEX_PLUS_ID,
		INT_PLUS_ID,

		PIVATE_ID,
		SERENT_ID,
		FEACEL_ID,
		LITENA_ID,
		KAINEL_ID,
		GENEAL_ID,
		FORE_GENEAL_ID,
		MAJORIS_GENEAL_ID,
		CLOEL_GENEAL_ID,
		MARSHAL_ID,

		RITTER_ID,
		REICHSRITTER_ID,
		BARONET_ID,
		PREYHER_ID,
		GRAF_ID,
		MARKGRAF_ID,
		PFALZGRAF_ID,
		FURST_ID,
		HERZOG_ID,
		LANDESHER_ID,

		MALCHUT_ID,					// ???????
		YESOD_ID,						// ?????
		HOD_ID,						// ???
		NETRETH_ID,					// ?????
		TIPHRETH_ID,					// ?????
		GEBURAH_ID,
		CHESED_ID,
		BINSH_ID,
		CHOKMA_ID,
		KEATHER_ID,
		ADVENCEMENT_ID,
		// GRADE1 BUTTON
		GRADE1_BUTTON1_ID,
		GRADE1_BUTTON2_ID,
		GRADE1_BUTTON3_ID,
		GRADE1_BUTTON4_ID,
		GRADE1_BUTTON5_ID,
		GRADE1_BUTTON6_ID,
		GRADE1_BUTTON7_ID,
		GRADE1_BUTTON8_ID,
		GRADE2_BUTTON1_ID,
		GRADE2_BUTTON2_ID,
		GRADE2_BUTTON3_ID,
		GRADE2_BUTTON4_ID,
		GRADE2_BUTTON5_ID,
		GRADE2_BUTTON6_ID,
		GRADE2_BUTTON7_ID,
		GRADE2_BUTTON8_ID,
		GRADE3_BUTTON1_ID,
		GRADE3_BUTTON2_ID,
		GRADE3_BUTTON3_ID,
		GRADE3_BUTTON4_ID,
		GRADE3_BUTTON5_ID,
		GRADE3_BUTTON6_ID,
		//		GRADE3_BUTTON_TAB_ID1,
		//		GRADE3_BUTTON_TAB_ID2,
		//		GRADE3_BUTTON_TAB_ID3,
		//		GRADE3_BUTTON_TAB_ID4,
		//		GRADE3_BUTTON_TAB_ID5,
		//		GRADE3_BUTTON_TAB_ID6,
		//		GRADE3_BUTTON_TAB_ID7,
		//		GRADE3_BUTTON_TAB_ID8,
		//		GRADE3_BUTTON_TAB_ID9,
		//		GRADE3_BUTTON_TAB_ID10,
		CHANGE_IMAGE_ID,		// ????? ???? ???
		PET_INFO_ID,

		// grade 2





	};

	enum GRADESKILL_STATUS
	{
		DISABLE,
		CAN_LEARN,
		LEARNED,
	};


	Rect m_rt_char_box;
	CSpritePack* m_p_face;

public:



	C_VS_UI_INFO();
	~C_VS_UI_INFO();

	void	RefreshImage();

	void	UnacquireMouseFocus()
	{
		//		m_pC_button_group->UnacquireMouseFocus();
		m_pC_common_button_group->UnacquireMouseFocus();
		m_pC_char_button_group->UnacquireMouseFocus();
		m_pC_skill_button_group->UnacquireMouseFocus();
		m_pC_grade1_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		//		m_pC_button_group->CancelPushState();
		m_pC_common_button_group->CancelPushState();
		m_pC_char_button_group->CancelPushState();
		m_pC_skill_button_group->CancelPushState();
		m_pC_grade1_button_group->CancelPushState();
	}

	void	SetPetInfo(struct PETINFO* pPetInfo);
	struct PETINFO* GetPetInfo();
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	AcquireDisappear() {}
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	bool	CharacterInfoMouseControl(UINT message, int _x, int _y);
	bool	SkillInfoMouseControl(UINT message, int _x, int _y);
	bool	RareSkillInfoMouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	CheckGradeSkillIDList();

	void	Show();
	void	_Show1();	// Skill Info
	void	_Show2();	// Character Info
	void	_Show3();	// Grade1
	void	_Show4();	// Grade2
	//by csm 2004.12.30 ???? ???? ????????? ??? 

	void	_Show5();	// Grade2
	void	_Show5_ACSkillList();		// ???? ??? ????? ???

	void	_Show6();	// Rare Skill	by chyaya
	void	_Show6_RareSkillList();		// ???? ??? ????? ???

	void	Process();
	//	void	Start(bool skill_mode);
	void	Start(INFO_MODE	Info_Mode);
	void	Finish();

	bool	IsCharacterMode() { return m_info_mode == CHARACTER_INFO_MODE; }
	bool	IsSkillMode() { return m_info_mode == SKILL_INFO_MODE; }
	bool	IsGrade1Mode() { return m_info_mode == GRADE1_INFO_MODE; }
	bool	IsGrade2Mode() { return m_info_mode == GRADE2_INFO_MODE; }
	bool	IsGrade3Mode() { return m_info_mode == GRADE3_INFO_MODE; }
	bool	IsRareSkillMode() { return m_info_mode == RARE_SKILL_INFO_MODE; }

	void	SetOustersDownSkill() { m_bOustersDownSkill = true; }
	void	SetCorrectGrade();
	const char* GetChinhoLevel(const int level);

	// ?????? ???? �??
	void	Process5_ACSkillList();
	void	Process5_ACSkillList_Slayer();
	void	Process5_ACSkillList_Vampire();
	void	Process5_ACSkillList_Ousters();

	// ??????? ???? �??
	void	Process6_RareSkillList();
};



class C_VS_UI_WINDOW_MANAGER
{
public:
	enum WINDOW_ID
	{
		HPBAR,
		MINIMAP,
		MAINMENU,
		CHATTING,
		CHATTING_OLD,
		INVENTORY,
		GEAR,
		INFO,
		QUICKITEMSLOT,
		PARTY,
		EFFECT_STATUS,
		OTHER_INFO,
		TRACE_WINDOW,
		BLOOD_BIBLE_WINDOW,
		QUEST_STATUS_WINDOW,

		CTF_STATUS,
		PET_INFO,

		NAMING_WINDOW,

		QUEST_MANAGER_LIST, // ???? �
		QUEST_MANAGER_DETAIL, // ???????
		QUEST_MANAGER_MISSION, // ???
		QUEST_MANAGER_ITEM, // ?????
		INVENTORY_SUB,
		BLOOD_BURST_WINDOW,
		WINDOW_TOTAL,
	};

	typedef std::map<std::string, WindowStatus> WINDOWSTATUS_MAP;

	C_VS_UI_WINDOW_MANAGER();
	~C_VS_UI_WINDOW_MANAGER();

	void SetFilter(CHAT_LINE_CONDITION filter, bool set);
	bool GetFilter(CHAT_LINE_CONDITION filter) { return m_filter[filter]; }

	void SetAlpha(WINDOW_ID id, bool bl_alpha);
	bool IsAlpha(WINDOW_ID id) { return m_alpha[id]; }

	void SetAutoHide(WINDOW_ID id, Window::ATTRIBUTES_HIDE hide);
	Window::ATTRIBUTES_HIDE GetAutoHide(WINDOW_ID id) { return m_autohide[id]; }

	void SetRect(WINDOW_ID id, Rect rect);
	Rect& GetRect(WINDOW_ID id) { return m_rect[id]; }

	// The hotkey bar's position; the file keeps it after everything else.
	void SetHotkeyBarRect(const Rect& rect) { m_hotkey_bar_rect = rect; }
	const Rect& GetHotkeyBarRect() const { return m_hotkey_bar_rect; }

	void SetHPBarSmall(bool bl_small) { m_bl_hpbar_small = bl_small; }
	bool IsHPBarSmall() { return m_bl_hpbar_small; }

	void SetHPBarHeight(bool bl_height) { m_bl_hpbar_height = bl_height; }
	bool IsHPBarHeight() { return m_bl_hpbar_height; }

	void SetBloodBurstHeight(bool bl_height) { m_bl_bloodburst_height = bl_height; }
	bool IsBloodBurstHeight() { return m_bl_bloodburst_height; }

	void SetQuickItemSlotHeight(bool bl_height) { m_bl_quickitemslot_height = bl_height; }
	bool IsQuickItemSlotHeight() { return m_bl_quickitemslot_height; }

	void SetEffectStatusHeight(bool bl_height) { m_bl_effectstatus_height = bl_height; }
	bool IsEffectStatusHeight() { return m_bl_effectstatus_height; }

	void SetMainMenu(int index) { m_i_main_menu = index; }
	int	 GetMainMenu() { return m_i_main_menu; }

	void SaveToFile(std::ofstream& file);
	void LoadFromFile(ivfstream& file);

	void SetDefault();
	void SetHotKey(int** hotkey = NULL);
	void SetQuickSlotHotkey(int* hotkey = NULL);
	void SetHotkeyType(int* hotkey = NULL);

	int** GetHotKey() { return (int**)m_skill_hotkey_buf; }
	int* GetHotKeyQuickSlot() { return	(int*)m_QuickSlot_hotkey_buf; }
	int* GetHotKeyType() { return	(int*)m_HotKey_Type; }

	void  SetSMSMynum(char* str);
	char* GetSMSMyNum() { return &m_SMS_MyNum[0]; }

	void  InitDefaultQuickSlot();

	void SetWindowStatus(const char* key, const WindowStatus* winStatus);
	const WindowStatus* GetWindowStatus(const char* key);
	void RemoveWindowStatus(const char* key);
	void ClearWindowStatus();

private:
	Rect m_rect[WINDOW_TOTAL];
	Rect m_hotkey_bar_rect;
	Window::ATTRIBUTES_HIDE m_autohide[WINDOW_TOTAL];
	bool m_alpha[WINDOW_TOTAL];

	WINDOWSTATUS_MAP m_WindowStatusMap;

	bool m_filter[CLD_TOTAL];
	int	 m_skill_hotkey_buf[C_VS_UI_SKILL::HOTKEY_MAX][C_VS_UI_SKILL::GRADE_MAX];

	int	 m_QuickSlot_hotkey_buf[C_VS_UI_SKILL::HOTKEY_MAX];
	int	 m_HotKey_Type[C_VS_UI_SKILL::HOTKEY_MAX];

	bool m_bl_hpbar_small, m_bl_hpbar_height, m_bl_quickitemslot_height, m_bl_effectstatus_height, m_bl_bloodburst_height;

	int m_i_main_menu;

	char m_SMS_MyNum[12];
};


class C_VS_UI_TEAM_LIST : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_spk;
	enum GUILD_SPK
	{
		LIST_WINDOW = 0,
		INFO_WINDOW,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		X_BUTTON,
		X_BUTTON_PUSHED,
		SCROLL_BAR,
		SCROLL_UP_BUTTON,
		SCROLL_UP_BUTTON_PUSHED,
		SCROLL_DOWN_BUTTON,
		SCROLL_DOWN_BUTTON_PUSHED,
		SCROLL_TAG,
		BAR_DARKEN,
		BAR_HILIGHTED,
		BAR_SEARCH,
		TITLE_TEAM_REGISTRATION,
		TITLE_MEMBER_REGISTRATION,
		TITLE_TEAM_INFO,
		TITLE_MEMBER_INFO,
		TITLE_TEAM_LIST,
		TITLE_TEAM_LIST_HILIGHTED,

		SEARCH_NAME,
		SEARCH_NAME_HILIGHTED,
		SEARCH_NAME_HILIGHTED_PUSHED,
		SEARCH_LEADER,
		SEARCH_LEADER_HILIGHTED,
		SEARCH_LEADER_HILIGHTED_PUSHED,
		SEARCH_ALL2,
		SEARCH_ALL_HILIGHTED,
		SEARCH_ALL_HILIGHTED_PUSHED,
		SEARCH_SEARCH,
		SEARCH_SEARCH_HILIGHTED,
		SEARCH_SEARCH_HILIGHTED_PUSHED,

		REGISTER_BUTTON,
		REGISTER_BUTTON_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		JOIN_BUTTON,
		JOIN_BUTTON_HILIGHTED,
		EXPEL_BUTTON,
		EXPEL_BUTTON_HILIGHTED,
		ACCEPT_BUTTON,
		ACCEPT_BUTTON_HILIGHTED,
		DENY_BUTTON,
		DENY_BUTTON_HILIGHTED,
		MODIFY_BUTTON,
		MODIFY_BUTTON_HILIGHTED,

		INDEX_TEAM,
		INDEX_TEAM_HILIGHTED,
		INDEX_LEADER,
		INDEX_LEADER_HILIGHTED,
		INDEX_EXPIREDATE,
		INDEX_EXPIREDATE_HILIGHTED,
		INDEX_MEMBERS,
		INDEX_MEMBERS_HILIGHTED,
		INDEX_RANKING,
		INDEX_RANKING_HILIGHTED,

		TITLE_WAR_LIST,
		TITLE_WAR_LIST_HILIGHTED,
		INDEX_WAR_CHALLENGER,
		INDEX_WAR_CHALLENGER_HILIGHTED,
		INDEX_WAR_DATE,
		INDEX_WAR_DATE_HILIGHTED,

		INDEX_UNITED_JOIN,				// ???????
		INDEX_UNITED_JOIN_HILIGHTED,
		INDEX_UNITED_WITHDRAWAL,		// ???????
		INDEX_UNITED_WITHDRAWAL_HILIGHTED,
		INDEX_UNITED_EXPEL,				// ???????
		INDEX_UNITED_EXPEL_HILIGHTED,
		INDEX_GUILD_APPOINT,			// ???
		INDEX_GUILD_APPOINT_HILIGHTED,


	};

	enum EXEC_ID
	{
		HELP_ID,
		X_ID,
		CLOSE_ID,
		REGISTER_ID,

		SCROLL_UP_ID,
		SCROLL_DOWN_ID,

		TEAM_LIST_ID,

		INDEX_TEAM_ID,
		INDEX_LEADER_ID,
		INDEX_EXPIREDATE_ID,
		INDEX_MEMBERS_ID,
		INDEX_RANKING_ID,

		SEARCH_TYPE_ID,
		SEARCH_ID,


		EXEC_MAX,
	};
public:
	struct TEAM_LIST_BASE
	{
		std::string TEAM_NAME, LEADER_NAME;
		int	guild_id;
		int MEMBERS;
	};

	struct REGIST_TEAM_LIST :public TEAM_LIST_BASE
	{
		int RANKING;
	};

	struct READY_TEAM_LIST :public TEAM_LIST_BASE
	{
		std::string EXPIRE_DATE;
		int MEMBERS_MAX;
	};

private:
	POINT	m_vampire_point;
	bool	m_bl_ready;
	int		m_scroll;
	bool	m_bl_scrolling;

	int		m_search_type;
	int		m_print_x[4], m_print_y, m_print_gap;

	int		m_iFocus;

	LineEditorVisual			m_lev_search;

	std::vector<READY_TEAM_LIST>	m_v_ready_team_search_list;
	std::vector<READY_TEAM_LIST>	m_v_ready_team_list;
	std::vector<REGIST_TEAM_LIST>	m_v_regist_team_search_list;
	std::vector<REGIST_TEAM_LIST>	m_v_regist_team_list;

	int		m_last_sort_type;

	bool	m_bIsUnion;
public:
	C_VS_UI_TEAM_LIST(bool ready, bool IsUnion = false);
	~C_VS_UI_TEAM_LIST();

	void	AddReadyTeamList(const READY_TEAM_LIST& team_info);
	void	AddRegistTeamList(const REGIST_TEAM_LIST& team_info);

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	AllMatchWindowPixel(int _x, int _y) const;
	bool	IsUnionInfo() { return m_bIsUnion; }

	void	Start();
	void	Finish();

	void	Show();

};

class C_VS_UI_TEAM_MEMBER_LIST : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_member_list_spk;
	C_VS_UI_SCROLL_BAR* m_pC_scroll_bar;

	bool						m_SortFlag_Id;
	bool						m_SortFlag_Server;
	bool						m_SortFlag_Grade;
	BYTE						m_ButtonFlag[3];
	enum TEAM_MEMBER_SPK
	{
		BUTTON_CLOSE,
		BUTTON_CLOSE_HILIGHTED,
		BUTTON_CLOSE_HILIGHTED_PUSHED,
		IMAGE_NULL,
	};

	enum EXEC_ID
	{
		CLOSE_ID,
		SORT_ID,
		SORT_SERVER,
		SORT_GRADE,
		EXEC_MAX,
	};
public:
	struct TEAM_MEMBER_LIST
	{
		std::string MEMBER_NAME;
		std::string SERVER_NAME;
		int member_grade;
		//		int server_type;
		bool bLogOn;
	};

private:
	int		m_print_x[2], m_print_y, m_print_gap;
	int		m_focus;
	std::vector<TEAM_MEMBER_LIST>	m_v_member_list;
	BYTE	m_bAvailableRecall; // �??? ???? ??? ?????? 
	char	m_SelectedID[16];
	char	m_AskingMessage[128];
public:
	C_VS_UI_TEAM_MEMBER_LIST();
	~C_VS_UI_TEAM_MEMBER_LIST();

	void	AddMemberList(const TEAM_MEMBER_LIST& member_list, BYTE bType);

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Start();
	void	Finish();

	void	Show();
	void	_Sort(int nSort);
	BYTE	GetAvailableRecall() { return m_bAvailableRecall; }
	void	SetAvailableRecall(BYTE bFlag) { m_bAvailableRecall = bFlag; }
	char* GetSelectedID() { return m_SelectedID; }
};

class C_VS_UI_NPC_DIALOG;
class C_VS_UI_TEAM_INFO : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_spk;
	enum GUILD_SPK
	{
		LIST_WINDOW = 0,
		INFO_WINDOW,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		X_BUTTON,
		X_BUTTON_PUSHED,
		SCROLL_BAR,
		SCROLL_UP_BUTTON,
		SCROLL_UP_BUTTON_PUSHED,
		SCROLL_DOWN_BUTTON,
		SCROLL_DOWN_BUTTON_PUSHED,
		SCROLL_TAG,
		BAR_DARKEN,
		BAR_HILIGHTED,
		BAR_SEARCH,
		TITLE_TEAM_REGISTRATION,
		TITLE_MEMBER_REGISTRATION,
		TITLE_TEAM_INFO,
		TITLE_MEMBER_INFO,
		TITLE_TEAM_LIST,
		TITLE_TEAM_LIST_HILIGHTED,

		SEARCH_NAME,
		SEARCH_NAME_HILIGHTED,
		SEARCH_NAME_HILIGHTED_PUSHED,
		SEARCH_LEADER,
		SEARCH_LEADER_HILIGHTED,
		SEARCH_LEADER_HILIGHTED_PUSHED,
		SEARCH_ALL2,
		SEARCH_ALL_HILIGHTED,
		SEARCH_ALL_HILIGHTED_PUSHED,
		SEARCH_SEARCH,
		SEARCH_SEARCH_HILIGHTED,
		SEARCH_SEARCH_HILIGHTED_PUSHED,

		REGISTER_BUTTON,
		REGISTER_BUTTON_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		JOIN_BUTTON,
		JOIN_BUTTON_HILIGHTED,
		EXPEL_BUTTON,
		EXPEL_BUTTON_HILIGHTED,
		ACCEPT_BUTTON,
		ACCEPT_BUTTON_HILIGHTED,
		DENY_BUTTON,
		DENY_BUTTON_HILIGHTED,
		MODIFY_BUTTON,
		MODIFY_BUTTON_HILIGHTED,

		INDEX_TEAM,
		INDEX_TEAM_HILIGHTED,
		INDEX_LEADER,
		INDEX_LEADER_HILIGHTED,
		INDEX_EXPIREDATE,
		INDEX_EXPIREDATE_HILIGHTED,
		INDEX_MEMBERS,
		INDEX_MEMBERS_HILIGHTED,
		INDEX_RANKING,
		INDEX_RANKING_HILIGHTED,

		TITLE_WAR_LIST,
		TITLE_WAR_LIST_HILIGHTED,
		INDEX_WAR_CHALLENGER,
		INDEX_WAR_CHALLENGER_HILIGHTED,
		INDEX_WAR_DATE,
		INDEX_WAR_DATE_HILIGHTED,

		INDEX_UNITED_JOIN,				// ???????
		INDEX_UNITED_JOIN_HILIGHTED,
		INDEX_UNITED_WITHDRAWAL,		// ???????
		INDEX_UNITED_WITHDRAWAL_HILIGHTED,
		INDEX_UNITED_EXPEL,				// ???????
		INDEX_UNITED_EXPEL_HILIGHTED,
		INDEX_GUILD_APPOINT,			// ???
		INDEX_GUILD_APPOINT_HILIGHTED,


	};
	enum EXEC_ID
	{
		HELP_ID,
		X_ID,
		CLOSE_ID,
		JOIN_ID,

		SCROLL_UP_ID,
		SCROLL_DOWN_ID,

		MODIFY_ID,
		UNITED_JOIN_ID,
		UNITED_WITHDRAWAL_ID,
		UNUTED_EXPEL_ID,

		EXEC_MAX,
	};
public:
	struct TEAM_INFO_BASE
	{
		std::string TEAM_NAME, LEADER_NAME, INTRODUCTION;
		int guild_id, MEMBERS, REG_FEE;
	};

	struct REGIST_TEAM_INFO :public TEAM_INFO_BASE
	{
		std::string REGISTERED_DATE;
		int RANKING;
	};

	struct READY_TEAM_INFO :public TEAM_INFO_BASE
	{
		std::string EXPIRE_DATE;
		std::vector<std::string> MEMBERS_NAME;
		int MEMBERS_MAX;
	};

private:
	bool	m_master;
	bool	m_bl_ready;
	int		m_scroll;
	int		m_scroll_max;
	bool	m_bl_scrolling;

	static REGIST_TEAM_INFO			m_regist_info;
	READY_TEAM_INFO				m_ready_info;
	C_VS_UI_NPC_DIALOG* m_pC_dialog;
	LineEditorVisual			m_lev_intro;

	bool	m_IsUnion;

public:
	C_VS_UI_TEAM_INFO(bool ready, void* info, bool IsUnion = false);
	~C_VS_UI_TEAM_INFO();

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	static int		GetGuildId() { return m_regist_info.guild_id; }
	void	CloseTeamInfoDialogBox();

	void	Start();
	void	Finish();
	void	Show();

};

class C_VS_UI_TEAM_MEMBER_INFO : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_member_spk;
	enum GUILD_SPK
	{
		LIST_WINDOW = 0,
		INFO_WINDOW,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		X_BUTTON,
		X_BUTTON_PUSHED,
		SCROLL_BAR,
		SCROLL_UP_BUTTON,
		SCROLL_UP_BUTTON_PUSHED,
		SCROLL_DOWN_BUTTON,
		SCROLL_DOWN_BUTTON_PUSHED,
		SCROLL_TAG,
		BAR_DARKEN,
		BAR_HILIGHTED,
		BAR_SEARCH,
		TITLE_TEAM_REGISTRATION,
		TITLE_MEMBER_REGISTRATION,
		TITLE_TEAM_INFO,
		TITLE_MEMBER_INFO,
		TITLE_TEAM_LIST,
		TITLE_TEAM_LIST_HILIGHTED,

		SEARCH_NAME,
		SEARCH_NAME_HILIGHTED,
		SEARCH_NAME_HILIGHTED_PUSHED,
		SEARCH_LEADER,
		SEARCH_LEADER_HILIGHTED,
		SEARCH_LEADER_HILIGHTED_PUSHED,
		SEARCH_ALL2,
		SEARCH_ALL_HILIGHTED,
		SEARCH_ALL_HILIGHTED_PUSHED,
		SEARCH_SEARCH,
		SEARCH_SEARCH_HILIGHTED,
		SEARCH_SEARCH_HILIGHTED_PUSHED,

		REGISTER_BUTTON,
		REGISTER_BUTTON_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		JOIN_BUTTON,
		JOIN_BUTTON_HILIGHTED,
		EXPEL_BUTTON,
		EXPEL_BUTTON_HILIGHTED,
		ACCEPT_BUTTON,
		ACCEPT_BUTTON_HILIGHTED,
		DENY_BUTTON,
		DENY_BUTTON_HILIGHTED,
		MODIFY_BUTTON,
		MODIFY_BUTTON_HILIGHTED,

		INDEX_TEAM,
		INDEX_TEAM_HILIGHTED,
		INDEX_LEADER,
		INDEX_LEADER_HILIGHTED,
		INDEX_EXPIREDATE,
		INDEX_EXPIREDATE_HILIGHTED,
		INDEX_MEMBERS,
		INDEX_MEMBERS_HILIGHTED,
		INDEX_RANKING,
		INDEX_RANKING_HILIGHTED,

		TITLE_WAR_LIST,
		TITLE_WAR_LIST_HILIGHTED,
		INDEX_WAR_CHALLENGER,
		INDEX_WAR_CHALLENGER_HILIGHTED,
		INDEX_WAR_DATE,
		INDEX_WAR_DATE_HILIGHTED,

		INDEX_UNITED_JOIN,							// ???????
		INDEX_UNITED_JOIN_HILIGHTED,
		INDEX_UNITED_WITHDRAWAL,					// ???????
		INDEX_UNITED_WITHDRAWAL_HILIGHTED,
		INDEX_UNITED_EXPEL,							// ???????
		INDEX_UNITED_EXPEL_HILIGHTED,
		INDEX_GUILD_APPOINT,						// ???
		INDEX_GUILD_APPOINT_HILIGHTED,

		INDEX_GUILD_DELEGATION_OF_POWER,			// ???? ????
		INDEX_GUILD_DELEGATION_OF_POWER_HILIGHTED,

	};

	enum EXEC_ID
	{
		HELP_ID,
		X_ID,
		CLOSE_ID,

		EXPEL_ID,
		ACCEPT_ID,
		DENY_ID,

		SCROLL_UP_ID,
		SCROLL_DOWN_ID,

		MODIFY_ID,

		APPOINT_ID,

		DELEGATION_OF_POWER_ID,

		EXEC_MAX,
	};

public:
	struct MEMBER_INFO
	{
		std::string NAME, INTRODUCTION;
		int guild_id;
		BYTE GRADE;
	};

private:
	int		m_scroll;
	int		m_scroll_max;
	bool	m_bl_scrolling;
	bool	m_own_info;

	MEMBER_INFO m_member_info;

	LineEditorVisual			m_lev_intro;

public:
	C_VS_UI_TEAM_MEMBER_INFO(MEMBER_INFO* info);
	~C_VS_UI_TEAM_MEMBER_INFO();

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Start();
	void	Finish();

	void	Show();

};

class C_VS_UI_TEAM_REGIST : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_spk;
	enum GUILD_SPK
	{
		LIST_WINDOW = 0,
		INFO_WINDOW,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		X_BUTTON,
		X_BUTTON_PUSHED,
		SCROLL_BAR,
		SCROLL_UP_BUTTON,
		SCROLL_UP_BUTTON_PUSHED,
		SCROLL_DOWN_BUTTON,
		SCROLL_DOWN_BUTTON_PUSHED,
		SCROLL_TAG,
		BAR_DARKEN,
		BAR_HILIGHTED,
		BAR_SEARCH,
		TITLE_TEAM_REGISTRATION,
		TITLE_MEMBER_REGISTRATION,
		TITLE_TEAM_INFO,
		TITLE_MEMBER_INFO,
		TITLE_TEAM_LIST,
		TITLE_TEAM_LIST_HILIGHTED,

		SEARCH_NAME,
		SEARCH_NAME_HILIGHTED,
		SEARCH_NAME_HILIGHTED_PUSHED,
		SEARCH_LEADER,
		SEARCH_LEADER_HILIGHTED,
		SEARCH_LEADER_HILIGHTED_PUSHED,
		SEARCH_ALL2,
		SEARCH_ALL_HILIGHTED,
		SEARCH_ALL_HILIGHTED_PUSHED,
		SEARCH_SEARCH,
		SEARCH_SEARCH_HILIGHTED,
		SEARCH_SEARCH_HILIGHTED_PUSHED,

		REGISTER_BUTTON,
		REGISTER_BUTTON_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		JOIN_BUTTON,
		JOIN_BUTTON_HILIGHTED,
		EXPEL_BUTTON,
		EXPEL_BUTTON_HILIGHTED,
		ACCEPT_BUTTON,
		ACCEPT_BUTTON_HILIGHTED,
		DENY_BUTTON,
		DENY_BUTTON_HILIGHTED,
		MODIFY_BUTTON,
		MODIFY_BUTTON_HILIGHTED,

		INDEX_TEAM,
		INDEX_TEAM_HILIGHTED,
		INDEX_LEADER,
		INDEX_LEADER_HILIGHTED,
		INDEX_EXPIREDATE,
		INDEX_EXPIREDATE_HILIGHTED,
		INDEX_MEMBERS,
		INDEX_MEMBERS_HILIGHTED,
		INDEX_RANKING,
		INDEX_RANKING_HILIGHTED,

		TITLE_WAR_LIST,
		TITLE_WAR_LIST_HILIGHTED,
		INDEX_WAR_CHALLENGER,
		INDEX_WAR_CHALLENGER_HILIGHTED,
		INDEX_WAR_DATE,
		INDEX_WAR_DATE_HILIGHTED,

		INDEX_UNITED_JOIN,				// ???????
		INDEX_UNITED_JOIN_HILIGHTED,
		INDEX_UNITED_WITHDRAWAL,		// ???????
		INDEX_UNITED_WITHDRAWAL_HILIGHTED,
		INDEX_UNITED_EXPEL,				// ???????
		INDEX_UNITED_EXPEL_HILIGHTED,
		INDEX_GUILD_APPOINT,			// ???
		INDEX_GUILD_APPOINT_HILIGHTED,


	};

	enum EXEC_ID
	{
		HELP_ID,
		X_ID,
		CLOSE_ID,
		REGIST_ID,

		EXEC_MAX,
	};

private:
	POINT	m_vampire_point;
	bool	m_bl_member;
	int		m_scroll;
	bool	m_bl_scrolling;
	int		m_print_x, m_print_y, m_print_gap;
	int		m_mark_x, m_mark_y;

	LineEditorVisual			m_lev_intro, m_lev_team_name;

	int		m_guild_id;
	int		m_reg_fee, m_rank;
	std::string m_team_name, m_introduction, m_date;
	CDirectDrawSurface* m_guild_mark;

public:
	C_VS_UI_TEAM_REGIST(bool member, int reg_fee, int rank, const char* team_name = NULL, const char* date = NULL, int guild_id = -1); // team_name?? member?? ?????
	~C_VS_UI_TEAM_REGIST();

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	ReturnTeamRegistMember() { return m_bl_member; }

	void	Start();
	void	Finish();

	void	Show();

};

//-----------------------------------------------------------------------------
// C_VS_UI_INFO
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_OTHER_INFO : public Window, public Exec, public ButtonVisual
{
private:
	//	C_SPRITE_PACK			*m_pC_info_spk;
	ButtonGroup* m_pC_button_group;
	CSprite* m_p_guild_mark;
	//CSprite					*m_p_guild_mark;
	struct PETINFO* m_pPetInfo;
	C_SPRITE_PACK			m_petButtonSpk;

#if __CONTENTS(__080405_FIREST_UI_UPDATE)
	enum EXEC_ID
	{
		ALPHA_ID,
		HELP_ID,
		CLOSE_ID,
		PET_INFO_ID,
	};
#else
	enum EXEC_ID
	{
		ALPHA_ID,

		CLOSE_ID,
		HELP_ID,
		PET_INFO_ID,
	};
#endif //__080405_FIREST_UI_UPDATE

public:
	struct PLAYER_INFO
	{
		void Init();

		std::string PLAYER_NAME;
		int DOMAINLEVEL[5];
		int GRADE, LEVEL, FAME;
		int ALIGNMENT;
		int STR_CUR, DEX_CUR, INT_CUR;
		int STR_PURE, DEX_PURE, INT_PURE;
		int guild_id;
		int face_type;
		bool bl_female;

		int	 Origin_ServerIdx;
		std::string PLAYER_OLDNAME;
		DWORD contributePoint;
	};
private:

	CSpritePack* m_p_face;
	//	C_SPRITE_PACK				*m_p_face_spk;
	PLAYER_INFO					m_player_info;

	int TopDomain;

public:

	C_VS_UI_OTHER_INFO();
	~C_VS_UI_OTHER_INFO();

	void	SetPetInfo(struct PETINFO* pPetInfo);
	void	RefreshImage();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	SetOtherInfo(PLAYER_INFO& info);
	const char* GetCurrentOtherInfoName();

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
	//bool	IsRunningOtherInfo();
};

//-----------------------------------------------------------------------------
// C_VS_UI_TRACE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_TRACE : public Window, public Exec, public ButtonVisual
{
private:
	bool status;
	C_SPRITE_PACK* m_pC_trace_spk;
	ButtonGroup* m_pC_button_group;

	enum EXEC_ID
	{
		OK_ID,
		CLOSE_ID,
		HELP_ID,
	};

	enum TRACE_SPK
	{
		MAIN_WINDOW = 0,
		TRACE_START,
		TRACE_START_HILIGHTED,
		TRACE_START_PUSHED,
		TRACE_CANCEL,
		TRACE_CANCEL_HILIGHTED,
		TRACE_CANCEL_PUSHED,
	};

	LineEditorVisual		m_lev_name;
	std::string					m_status_msg;
	std::string					name;
public:

	C_VS_UI_TRACE();
	~C_VS_UI_TRACE();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
	bool	IsStartTrace();
	void	SetCannotTrace();
};

//-----------------------------------------------------------------------------
// C_VS_UI_TRACE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_XMAS_CARD : public Window, public Exec, public ButtonVisual
{
private:
	C_SPRITE_PACK* m_pC_card_spk;
	ButtonGroup* m_pC_button_group;
	bool					status;

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

	enum TRACE_SPK
	{
		MAIN_WINDOW = 0,
		BUTTON_OK,
		BUTTON_OK_HILIGHTED,
		BUTTON_OK_PUSHED,
		BUTTON_CANCEL,
		BUTTON_CANCEL_HILIGHTED,
		BUTTON_CANCEL_PUSHED,
	};

	//	LineEditorVisual		m_lev_from;	
	LineEditorVisual		m_lev_to;
	LineEditorVisual		m_lev_message;

	MItem* m_pItem;
	std::string				m_szTreeMessage;


public:

	C_VS_UI_XMAS_CARD(const MItem* pItem);
	~C_VS_UI_XMAS_CARD();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_BRING_FEE
//
// ???? ????????
//
//-----------------------------------------------------------------------------
class C_VS_UI_BRING_FEE : public Window, public Exec, public ButtonVisual
{
private:
	UINT	m_TotalFee;
	UINT	m_BringFee;
	int		m_money_x, m_money_y;

	ButtonGroup* m_pC_button_group;

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
		MONEY_ID,
	};

public:
	//	static	C_VS_UI_MONEY_DIALOG		*m_pC_bring_fee_dialog;
	C_VS_UI_BRING_FEE(UINT totalfee = 0, UINT bringfee = 0);
	~C_VS_UI_BRING_FEE();

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	void	SetTotalFee(UINT fee) { m_TotalFee = fee; }
	void	SetBringFee(UINT fee) { m_BringFee = fee; }
	UINT		GetTotalFee() { return m_TotalFee; }
	UINT		GetBringFee() { return m_BringFee; }

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}
};

class C_VS_UI_WAR_LIST : public Window, public Exec, public ButtonVisual
{
	ButtonGroup* m_pC_button_group;
	C_SPRITE_PACK				m_guild_spk;
	enum GUILD_SPK
	{
		LIST_WINDOW = 0,
		INFO_WINDOW,
		HELP_BUTTON,
		HELP_BUTTON_PUSHED,
		X_BUTTON,
		X_BUTTON_PUSHED,
		SCROLL_BAR,
		SCROLL_UP_BUTTON,
		SCROLL_UP_BUTTON_PUSHED,
		SCROLL_DOWN_BUTTON,
		SCROLL_DOWN_BUTTON_PUSHED,
		SCROLL_TAG,
		BAR_DARKEN,
		BAR_HILIGHTED,
		BAR_SEARCH,
		TITLE_TEAM_REGISTRATION,
		TITLE_MEMBER_REGISTRATION,
		TITLE_TEAM_INFO,
		TITLE_MEMBER_INFO,
		TITLE_TEAM_LIST,
		TITLE_TEAM_LIST_HILIGHTED,

		SEARCH_NAME,
		SEARCH_NAME_HILIGHTED,
		SEARCH_NAME_HILIGHTED_PUSHED,
		SEARCH_LEADER,
		SEARCH_LEADER_HILIGHTED,
		SEARCH_LEADER_HILIGHTED_PUSHED,
		SEARCH_ALL2,
		SEARCH_ALL_HILIGHTED,
		SEARCH_ALL_HILIGHTED_PUSHED,
		SEARCH_SEARCH,
		SEARCH_SEARCH_HILIGHTED,
		SEARCH_SEARCH_HILIGHTED_PUSHED,

		REGISTER_BUTTON,
		REGISTER_BUTTON_HILIGHTED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		JOIN_BUTTON,
		JOIN_BUTTON_HILIGHTED,
		EXPEL_BUTTON,
		EXPEL_BUTTON_HILIGHTED,
		ACCEPT_BUTTON,
		ACCEPT_BUTTON_HILIGHTED,
		DENY_BUTTON,
		DENY_BUTTON_HILIGHTED,
		MODIFY_BUTTON,
		MODIFY_BUTTON_HILIGHTED,

		INDEX_TEAM,
		INDEX_TEAM_HILIGHTED,
		INDEX_LEADER,
		INDEX_LEADER_HILIGHTED,
		INDEX_EXPIREDATE,
		INDEX_EXPIREDATE_HILIGHTED,
		INDEX_MEMBERS,
		INDEX_MEMBERS_HILIGHTED,
		INDEX_RANKING,
		INDEX_RANKING_HILIGHTED,

		TITLE_WAR_LIST,
		TITLE_WAR_LIST_HILIGHTED,
		INDEX_WAR_CHALLENGER,
		INDEX_WAR_CHALLENGER_HILIGHTED,
		INDEX_WAR_DATE,
		INDEX_WAR_DATE_HILIGHTED,

		INDEX_UNITED_JOIN,				// ???????
		INDEX_UNITED_JOIN_HILIGHTED,
		INDEX_UNITED_WITHDRAWAL,		// ???????
		INDEX_UNITED_WITHDRAWAL_HILIGHTED,
		INDEX_UNITED_EXPEL,				// ???????
		INDEX_UNITED_EXPEL_HILIGHTED,
		INDEX_GUILD_APPOINT,			// ???
		INDEX_GUILD_APPOINT_HILIGHTED,


	};
	enum EXEC_ID
	{
		HELP_ID,
		X_ID,
		CLOSE_ID,

		SCROLL_UP_ID,
		SCROLL_DOWN_ID,

		WAR_LIST_ID,
		INDEX_CHALLENGER_ID,
		INDEX_DATE_ID,

		EXEC_MAX,
	};
public:
	class WarInfo
	{
	public:
		WarInfo()
		{
			for (int i = 0; i < 5; i++)
				challengerGuildID[i] = 0;
			reinforceGuildID = 0;
		};

		BYTE warType;		// 0 : ?????? 1 : ??????
		WORD year;
		BYTE month;
		BYTE day;
		BYTE hour;
		WORD		challengerGuildID[5];
		std::string challengerGuildName[5];
		WORD		reinforceGuildID;
		std::string	reinforceGuildName;
	};

	struct _WarList
	{
		BYTE warType;		// 0 : ?????? 1 : ??????
		WORD year;
		BYTE month;
		BYTE day;
		BYTE hour;
		WORD		challengerGuildID;
		std::string challengerGuildName;
	};
private:
	std::vector<_WarList>			m_v_war_list;
	POINT							m_vampire_point;
	bool							m_bl_scrolling;
	int								m_scroll;

public:
	C_VS_UI_WAR_LIST();
	~C_VS_UI_WAR_LIST();


	void	AddWarList(const WarInfo& war_info);
	void	ClearWarList();

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	AllMatchWindowPixel(int _x, int _y) const;

	void	Start();
	void	Finish();

	void	Show();
};

//-----------------------------------------------------------------------------
// C_VS_UI_INFO
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_BLOOD_BIBLE_STATUS : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup* m_pC_button_group;

	enum EXEC_ID
	{
		PUSHPIN_ID,
		ALPHA_ID,
		CLOSE_ID,
		HELP_ID,
	};

public:

	enum BLOOD_BIBLE_STATUS_INFO
	{
		BLOOD_BIBLE_NONE,
		BLOOD_BIBLE_DROP,
		BLOOD_BIBLE_HAS_SLAYER,
		BLOOD_BIBLE_HAS_VAMPIRE,
		BLOOD_BIBLE_SHRINE_SLAYER,
		BLOOD_BIBLE_SHRINE_VAMPIRE,
		BLOOD_BIBLE_SHRINE_OUSTERS,
		BLOOD_BIBLE_HAS_OUSTERS,
	};
	struct BLOOD_BIBLE_STATUS
	{
		int zone_id;
		int x;
		int y;
		BYTE shrine_race;
		BLOOD_BIBLE_STATUS_INFO status;
		//BYTE bonus;										-_- ?????. 
		std::string name;
	};

	BLOOD_BIBLE_STATUS		m_BloodBibleStatus[12];

	DWORD					m_tickCount;
	DWORD					m_sec;

public:

	C_VS_UI_BLOOD_BIBLE_STATUS();
	~C_VS_UI_BLOOD_BIBLE_STATUS();

	void	SetTimer(DWORD sec) { m_sec = sec; m_tickCount = timeGetTime(); }

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	SetBloodBible(int blood_bible_id, BLOOD_BIBLE_STATUS& blood_bible_status);
	void	UnSetBloodBible(int blood_bible_id);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_BRING_FEE
//
// ??? ??????
// -_- ????? ???�?.
//-----------------------------------------------------------------------------
class C_VS_UI_INPUT_NAME : public Window, public Exec, public ButtonVisual
{
public:
	enum INPUT_NAME_MODE_LIST
	{
		INPUT_NAME_HOPE_COUPLE = 0,					// ??? ?????
		INPUT_NAME_BREAK_UP,					// ??? ????		
		INPUT_NAME_FORCE_BREAK_UP,

		INPUT_NAME_MAX,
	};

	enum	INPUT_STATUS_LIST
	{
		INPUT_STATUS_NORMAL,
		INPUT_STATUS_DISABLE,
		INPUT_STATUS_MAX,
		INPUT_STATUS_NULL,
	};
private:
	LineEditorVisual		m_lev_name;
	int		m_name_x, m_name_y;
	INPUT_NAME_MODE_LIST	m_Mode;
	INPUT_STATUS_LIST		m_Status;

	ButtonGroup* m_pC_button_group;

	std::string			m_name, m_status;

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

public:
	//	static	C_VS_UI_MONEY_DIALOG		*m_pC_bring_fee_dialog;
	C_VS_UI_INPUT_NAME(INPUT_NAME_MODE_LIST mode = INPUT_NAME_HOPE_COUPLE);
	~C_VS_UI_INPUT_NAME();

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	const char* GetCurrentName();
	void	SetName(const char* name);


	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	SetEnable() { m_Status = INPUT_STATUS_NORMAL; }
	void	SetDisable() { m_Status = INPUT_STATUS_DISABLE; }
};

//-----------------------------------------------------------------------------
// class C_VS_UI_BRING_FEE
//
// ??? ??????
// -_- ????? ???�?.
//-----------------------------------------------------------------------------
class C_VS_UI_POPUP_MESSAGE : public Window, public Exec, public ButtonVisual
{
public:
	enum POPUP_TYPE
	{
		POPUP_NORMAL,
		POPUP_LARGE,
		POPUP_WELCOME,
		POPUP_EVENT_QUEST,
		POPUP_MINI_WINDOW,
		POPUP_ASK_BEGINNER_ZONE,			// ????? ?????? ?????

		POPUP_MAX,
		POPUP_NULL,
	};

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

	enum
	{
		STYLE_OK_BUTTON = 1,
		STYLE_CANCEL_BUTTON = 2,
		STYLE_JOIN_BUTTON = 4,
		STYLE_ABSENCE_BUTTON = 8,
	};

	struct PopupWindowStyle
	{
		short			WindowX, WindowY;
		POPUP_TYPE		Type;
		DWORD			Style;
		DWORD			SendID;
		std::string		str;

		DWORD			Value1;
		DWORD			Value2;

		void* pValue;
	};

private:
	std::string				m_Str;
	POPUP_TYPE				m_Type;
	CSpritePack				m_p_NPCFace;
	DWORD					m_SendID;

	ButtonGroup* m_pC_button_group;

public:
	//	static	C_VS_UI_MONEY_DIALOG		*m_pC_bring_fee_dialog;
	C_VS_UI_POPUP_MESSAGE(const char* str, POPUP_TYPE type = POPUP_NORMAL);
	C_VS_UI_POPUP_MESSAGE(PopupWindowStyle& style);
	~C_VS_UI_POPUP_MESSAGE();

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}
};

//-----------------------------------------------------------------------------
// class C_VS_UI_LOTTERY_CARD
//
//
//-----------------------------------------------------------------------------
class C_VS_UI_LOTTERY_CARD : public Window, public Exec, public ButtonVisual
{
public:

	enum LOTTERY_STATUS
	{
		LOTTERY_TYPE_READY,
		LOTTERY_TYPE_WAIT_CLIENT,
		LOTTERY_TYPE_SCRATCH,
		LOTTERY_TYPE_CLEARING,
		LOTTERY_TYPE_CLOSE,
		LOTTERY_TYPE_MAX,
	};

	int						m_step;
	C_SPRITE_PACK* m_pC_lottery_spk;
	CSpriteSurface* m_p_cover_surface;
	LOTTERY_STATUS			m_Type;
	int						m_radio_select;
	int						m_line_select;
	bool					m_bl_scratch_enable;
	bool					m_bl_press;
	int						m_backimage[3];
	bool					m_bl_result;
	int						m_old_point_x;
	int						m_old_point_y;


private:

	struct GiftInfo
	{
		DWORD	id;
		BOOL	Active;
		std::string name;
		int		image;
	};

	std::vector<GiftInfo*>	m_GiftList;
	ButtonGroup* m_pC_button_group;
	ButtonGroup* m_pC_radio_group;

	enum EXEC_ID
	{
		BUTTON_ID,
		RADIO1,
		RADIO2,
		RADIO3,
		RADIO4,
		RADIO5,
	};

	enum LOTTERY_SPK
	{
		BACK = 0,
		BOTTOM,
		COVER,
		LOTTERY_READY,
		LOTTERY_READY_HILIGHTED,
		LOTTERY_READY_PUSHED,
		LOTTERY_CLOSE,
		LOTTERY_CLOSE_HILIGHTED,
		LOTTERY_CLOSE_PUSHED,
		RADIO_BACK,
		RADIO_CHECK,

		GIFT_TICKET_1,
		DARKEDEN_TSHIRTS,
		DARKEDEN_PENDANT,
		DARKEDEN_TICKET_1,
		INLINE_SKATE,
		//		VOICE_MAN,
		//		MP3_PLAYER,
		SPEAKER,
		GIFT_TICKET_2,
		WATCH,
		//		DVD_COMBO,
		CAMCORDER,
		CAMERA,
		GIFT_TICKET_3,
		HOME_THEATER,
		FLAT_TV,
		TFT_MONITOR,
		COMPUTER,
		DIGITAL_TV,
		DARKEDEN_TICKET_2,
		REFRIGERATOR,
		DVD_PLAYER,
		HEELYS,
		IRIVER_395,
	};

public:

	C_VS_UI_LOTTERY_CARD(int step = -1);
	~C_VS_UI_LOTTERY_CARD();

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	void	ClearGiftList();

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	SetResult(bool	bSuccess);
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	ScratchCover(int _x, int _y);
	void	ClearingCover();
	void	ClearAllCover();
	int		PeelRate();
	void	SetScratchEnable();
	void	LoadInfo(int& step);
	void	ShowDesc(int strX, int strY, const char* str);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_ITEM_LIST
//
// ??? ??????
// -_- ????? ???�?.
//-----------------------------------------------------------------------------
class C_VS_UI_ITEM_LIST : public Window, public Exec, public ButtonVisual
{
public:
	enum EXEC_ID
	{
		NEXT_ID,
		PREV_ID,
		BRING_ID,

		OK_ID,
		CANCEL_ID,
	};

	struct ItemList
	{
		MItem* pItem;
		DWORD	TimeLimit;
	};

	static MItem* m_pItem;

private:
	std::string					m_Str;
	std::vector<ItemList>		m_ItemList;
	int							m_CurrentItem;
	int							m_MouseFocus;

	ButtonGroup* m_pC_button_group;
	C_VS_UI_SCROLL_BAR* m_pC_scroll_bar;

public:
	C_VS_UI_ITEM_LIST();
	~C_VS_UI_ITEM_LIST();

	void	Show();
	void	ShowDesc(ItemList pItem);
	std::string		GetItemName(int Focus);

	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	bool	IsPixel(int _x, int _y);

	bool	AddItem(ItemList pItem);
	bool	DeleteItem(DWORD ID);
	void	ClearItem();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

};

//-----------------------------------------------------------------------------
// class C_VS_UI_IMAGE_NOTICE
//
// ??? ??????
// -_- ????? ???�?.
//-----------------------------------------------------------------------------
class C_VS_UI_IMAGE_NOTICE : public Window, public Exec, public ButtonVisual
{
public:
	struct SNotice
	{
		DWORD				m_Time;
		std::string			m_Name;
		std::string			m_GiftName;
		char				m_Alpha;
	};

private:
	int		m_CloseTime;

	C_SPRITE_PACK* m_pC_image_spk;

	std::vector<SNotice*>			m_NoticeList;

public:

	C_VS_UI_IMAGE_NOTICE();
	~C_VS_UI_IMAGE_NOTICE();

	void	Show();
	std::string	LoadInfo(DWORD ID);
	void	AddNotice(const char* name, DWORD id);
	void	ClearNotice();
	void	DeleteNotice(int n);

	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
	}
	void	CancelPushState()
	{
	}
};

//-----------------------------------------------------------------------------
// C_VS_UI_TRACE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_BULLETIN_BOARD : public Window, public Exec, public ButtonVisual
{
private:
	C_SPRITE_PACK* m_pC_back_spk;
	ButtonGroup* m_pC_button_group;
	bool					status;

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

	enum TRACE_SPK
	{
		MAIN_WINDOW = 0,
		BUTTON_OK,
		BUTTON_OK_HILIGHTED,
		BUTTON_OK_PUSHED,
		BUTTON_CANCEL,
		BUTTON_CANCEL_HILIGHTED,
		BUTTON_CANCEL_PUSHED,
	};

	LineEditorVisual		m_lev_from;
	LineEditorVisual		m_lev_message;

	MItem* m_pItem;
	std::string				m_szTreeMessage;

	int						m_pos_from_x;
	int						m_pos_from_y;
	int						m_pos_msg_x;
	int						m_pos_msg_y;

public:

	C_VS_UI_BULLETIN_BOARD(const MItem* pItem);
	~C_VS_UI_BULLETIN_BOARD();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_REQUEST_RESURRECT
//
//-----------------------------------------------------------------------------
class C_VS_UI_REQUEST_RESURRECT : public Window
{
public:
	enum IMAGE_SPK_INDEX
	{
		RESURRECT_GUARD_SLAYER,
		RESURRECT_GUARD_VAMPIRE,
		RESURRECT_GUARD_OUSTERS,
		PARTY_REQUEST,
		PARTY_INVITE,
		RESURRECT_SLAYER,
		RESURRECT_VAMPIRE,
		RESURRECT_OUSTERS,
		LVU_BUTTON,
		LVU_BUTTON_OUSTERS,
		RESURRECT_SCROLL,
		ELIXIR_SCROLL,
		ETERNITY,
		SKILL_FROM_OTHER_SLAYER,
		SKILL_FROM_OTHER_OUSTERS,
		SKILL_FROM_OTHER_VAMPIRE,
	};

	enum RESURRECT_MODE
	{
		RESURRECT_MODE_RESURRECT_SCROLL = 0,
		RESURRECT_MODE_ELIXIR,
		RESURRECT_MODE_ETERNITY,
		// 2004, 11, 16, sobeit add start
		RESURRECT_MODE_SIEGE_ATTACKER,
		// 2004, 11, 16, sobeit add end
		RESURRECT_MODE_SKILL_FROM_OTHER,	// ??? ????? ??????? ??????.
		RESURRECT_MODE_MAX
	};

	class CResurrect
	{
	public:
		CResurrect() : m_Delay(0), m_Time(0) { memset(&m_ButtonRect, 0, sizeof(RECT)); m_Enable = false; m_Image = -1; }
		void		SetRect(int x, int y, int w, int h) { m_ButtonRect.left = x; m_ButtonRect.right = x + w; m_ButtonRect.top = y; m_ButtonRect.bottom = y + h; }

		RECT		m_ButtonRect;
		bool		m_Enable;
		int			m_Image;
		int			m_Delay;
		DWORD		m_Time;
	};

	C_SPRITE_PACK				m_image_spk;

	CResurrect					m_ResurrectButton[RESURRECT_MODE_MAX];

	int							m_focus;
	int							m_pushed;

public:
	C_VS_UI_REQUEST_RESURRECT(bool resurrect, bool elixir, bool eternity, bool IsSiegeAttacker, bool IsSkillFromOther);
	~C_VS_UI_REQUEST_RESURRECT();

	void	Show();
	bool	IsPixel(int _x, int _y);
	void	Start();
	void	Finish();
	bool	MouseControl(UINT message, int _x, int _y);
	void	CancelPushState() { m_pushed = -1; }
	void	UnacquireMouseFocus() { m_pushed = -1; }
	void	SetDelay(RESURRECT_MODE mode, int delay);
	void	Process();
	void	RequestResurrectSetButton(int resurrectMode, bool enable);
};

//-----------------------------------------------------------------------------
// C_VS_UI_MIXING_FORGE
// 
//-----------------------------------------------------------------------------
class C_VS_UI_MIXING_FORGE : public Window, public Exec, public ButtonVisual
{
private:
	C_SPRITE_PACK* m_pC_back_spk;
	C_SPRITE_PACK* m_pC_inventory_spk;
	ButtonGroup* m_pC_button_group;

	Rect					m_my_grid_rect, m_your_grid_rect;
	int						m_focus_grid_x, m_focus_grid_y;

	MItem* m_p_select_item[2];

	std::vector<bool>		m_v_check;


	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

	enum MIXING_FORGE_SPK
	{
		MAIN_WINDOW = 0,
		BUTTON_OK,
		BUTTON_OK_HILIGHTED,
		BUTTON_OK_PUSHED,
		BUTTON_CANCEL,
		BUTTON_CANCEL_HILIGHTED,
		BUTTON_CANCEL_PUSHED,
	};

	enum INVENTORY_SPK_INDEX
	{
		INVENTORY_WINDOW,
		INVENTORY_WINDOW_ALPHA,
		INVENTORY_ITEMBACK,
		INVENTORY_ITEMBACK_ALPHA,
		INVENTORY_WINDOW_BOTTOM,
	};

public:

	enum FORGE_CLASS
	{
		CLASS_WEAPON,
		CLASS_ARMOR,
		CLASS_ACCESSORY,
	};

	enum FORGE_TYPE
	{
		TYPE_A,
		TYPE_B,
		TYPE_C,
		TYPE_D,
		TYPE_E,
	};

	FORGE_CLASS				m_forge_class;
	FORGE_TYPE				m_forge_type;

	C_VS_UI_MIXING_FORGE(FORGE_CLASS forge_class, FORGE_TYPE forge_type);
	~C_VS_UI_MIXING_FORGE();

	bool	IsCorrectClass(ITEM_CLASS item_class);
	bool	IsCorrectType(TYPE_ITEMTYPE item_type, ITEM_CLASS item_class);
	bool	IsCorrectOption(MItem* p_item1, MItem* p_item2);

	int		GetFocusedItemGridX(const MItem* p_item);
	int		GetFocusedItemGridY(const MItem* p_item);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	AcquireDisappear() {}
	void	UnacquireMouseFocus()
	{
		m_pC_button_group->UnacquireMouseFocus();
	}
	void	CancelPushState()
	{
		m_pC_button_group->CancelPushState();
	}

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	bool	IsPixel(int _x, int _y);
	bool	Check(int grid_start_x, int grid_start_y);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_REMOVE_OPTION
//
//-----------------------------------------------------------------------------
class C_VS_UI_REMOVE_OPTION : public Window, public Exec, public ButtonVisual
{
public:
	enum TYPE
	{
		TYPE_A,
		TYPE_B,
		TYPE_C,
	};

	enum STATUS
	{
		STATUS_SELECT_OPTION,
		STATUS_QUESTION,
	};

	int					m_select_option;
	STATUS				m_status;
	std::string			m_str_option[2];
	bool				m_b_press;
	const MItem* m_pMouseItem, * m_pCurItem;

private:

	ButtonGroup* m_pC_button_group;
	bool				m_IsBokjory;


	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};

public:
	C_VS_UI_REMOVE_OPTION(const MItem* pItem, const MItem* pCurItem);
	~C_VS_UI_REMOVE_OPTION();

	static	bool	IsCanRemoveOption_Puritas(const MItem* pItem, const MItem* pTItem);

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	IsPixel(int _x, int _y);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);
	void	CheckOption();

};

//-----------------------------------------------------------------------------
// class C_VS_UI_OUSTERS_SKILL_INFO
//
//-----------------------------------------------------------------------------
class C_VS_UI_OUSTERS_SKILL_INFO : public C_VS_UI_DESC, public Window, public Exec, public ButtonVisual
{
public:
private:

	ButtonGroup* m_pC_button_group;
	bool				m_bDownSkill;
	C_SPRITE_PACK		m_SPK;				// SkillWindow.spk, for its scroll arrows

	enum EXEC_ID
	{
		CLOSE_ID,
		ALPHA_ID,
		LEARN_ID,
		SCROLL_UP_ID,
		SCROLL_DOWN_ID,
	};
	int		m_skillID;
	bool	CanPressLearn();
	bool	CanScroll()				{ return GetDescSize() > GetDescCol(); }
	void	ShowButtonLabels();

public:
	C_VS_UI_OUSTERS_SKILL_INFO(int skillID, int window_x, int window_y, bool DownSkill = false);
	~C_VS_UI_OUSTERS_SKILL_INFO();

	void	SetSkillID(int skillID);
	bool	IsDownSkill() const		{ return m_bDownSkill; }
	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	IsPixel(int _x, int _y);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);

};


//-----------------------------------------------------------------------------
// class C_VS_UI_HORN
//
//-----------------------------------------------------------------------------
class C_VS_UI_HORN : public Window, public Exec, public ButtonVisual
{
public:
private:

	ButtonGroup* m_pC_button_group;

	C_SPRITE_PACK		m_SPK, m_MapSPK;

	enum EXEC_ID
	{
		CLOSE_ID,
		UP_ID,
		DOWN_ID,
	};

	enum SPRITE_ID
	{
		MAIN_WINDOW,
		UD_BUTTON,
		UD_BUTTON_HILIGHTED,
		UD_BUTTON_PUSHED,
		CLOSE_BUTTON,
		CLOSE_BUTTON_HILIGHTED,
		CLOSE_BUTTON_PUSHED,
	};

	int		m_CurrentZone;
	int		m_MapX, m_MapY;
	int		m_focus;
	int		m_Cost;

	//	UI_PORTAL_VECTOR		m_portal;

public:
	C_VS_UI_HORN(int currentZoneID);
	~C_VS_UI_HORN();

	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	IsPixel(int _x, int _y);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);

	int		GetNext(int map, bool bUp);
};

//-----------------------------------------------------------------------------
// class C_VS_UI_FINDING_MINE
//
//-----------------------------------------------------------------------------
class C_VS_UI_FINDING_MINE : public Window, public Exec, public ButtonVisual
{
public:
private:

	ButtonGroup* m_pC_button_group;

	enum EXEC_ID
	{
		CLOSE_ID,
		START_ID,
		LEVEL0_ID,
		LEVEL1_ID,
		LEVEL2_ID,
	};

	//	enum SPRITE_ID
	//	{
	//		MAIN_WINDOW,
	//			UD_BUTTON,
	//			UD_BUTTON_HILIGHTED,
	//			UD_BUTTON_PUSHED,
	//			CLOSE_BUTTON,
	//			CLOSE_BUTTON_HILIGHTED,
	//			CLOSE_BUTTON_PUSHED,
	//	};


	enum GAME_SIZES
	{
		BLOCK_WIDTH = 16,
		BLOCK_HEIGHT = 16,
		BLOCK_START_X = 12,
		BLOCK_START_Y = 96,
	};

	enum GAMELEVEL
	{
		GAMELEVEL_0,
		GAMELEVEL_1,
		GAMELEVEL_2,

		GAMELEVEL_MAX,
	};

	enum GAME_STATUS
	{
		GAMESTATUS_GAME,	// ??????
		GAMESTATUS_DIE,		// ???? ???? ??????-??-
		GAMESTATUS_CLEAR,	// ???? ???? ?? �???
		GAMESTATUS_READY,	// ?? ????
	};

	enum LEFTMINE
	{
		LEFTMINE_LEVEL0 = 10,
		LEFTMINE_LEVEL1 = 40,
		LEFTMINE_LEVEL2 = 99,
	};

	enum BOARDSIZE
	{
		BOARDSIZE_LEVEL0_WIDTH = 10,
		BOARDSIZE_LEVEL0_HEIGHT = 10,
		BOARDSIZE_LEVEL1_WIDTH = 16,
		BOARDSIZE_LEVEL1_HEIGHT = 16,
		BOARDSIZE_LEVEL2_WIDTH = 30,
		BOARDSIZE_LEVEL2_HEIGHT = 16,
	};

	enum BLOCK_STATUS
	{
		BLOCKSTATUS_CLOSE,
		BLOCKSTATUS_OPEN,
		BLOCKSTATUS_QUESTION,
		BLOCKSTATUS_FLAG,
	};

	struct BLOCK_STRUCT
	{
		BLOCK_STRUCT() { num = 0; status = (BLOCK_STATUS)0; bl_focused = false; }

		int num;
		BLOCK_STATUS status;
		bool		bl_focused;
	};

	DWORD	m_startTime;
	int		m_leftMineCount;
	SIZE	m_boardSize;
	GAME_STATUS	m_status;

	BLOCK_STRUCT* m_Blocks;

	Rect	m_BlockRect;

	GAMELEVEL m_level;
	bool bLButton, bRButton;

	void	DrawBlock(int x, int y, BLOCK_STRUCT& block);
	void	DrawRect(RECT& rect, int depth, WORD color, WORD color2, WORD color3);
	void	ClearBlockFocus(int x = -1, int y = -1, int w = -1, int h = -1);
	void	OpenBlock(int x, int y, bool bCenter = false);
	bool	CheckClear();
	void	DrawNumbers(int x, int y, int number);
	void	DrawNumber(int x, int y, BYTE flag);

public:
	C_VS_UI_FINDING_MINE();
	~C_VS_UI_FINDING_MINE();

	void	NewGame(GAMELEVEL level);
	void	Show();
	void	Start();
	void	Finish();
	void	Process();
	void	Run(id_t id);

	bool	IsPixel(int _x, int _y);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button);
	void	WindowEventReceiver(id_t event);

};

extern C_VS_UI_WINDOW_MANAGER* gpC_vs_ui_window_manager;

#define ITEM_REF_POINT_COUNT			4

extern S_SLOT	g_char_slot_ingame;
extern Point g_item_ref_point[];

extern int g_HISTORY_LINE;	// �??� ????

void g_SetItemRefPoint(int item_rect_w, int item_rect_h);

#endif
