#include "client_PCH.h"

// VS_UI_Dialog.cpp
#pragma warning(disable:4786)

#include "VS_UI_Dialog.h"
#include "VS_UI_GlobalResource.h"
#include "VS_UI_description.h"
#include "ClientFunction.h"
#include "UserOption.h"

#include "VS_UI_filepath.h"

#include "mgamestringtable.h"
#include "UserInformation.h"

#if __CONTENTS(__BLITZ_COUPON_EVENT)
#include "VS_UI_item.h"
#include "EffectSpriteTypeDef.h"
#endif //__BLITZ_COUPON_EVENT

extern C_VS_UI_DIALOG* gpC_dialog_confirm_item_bay_messagebox;
//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::WindowEventReceiver(id_t event)
{
	const static char* m_chatting_button_string[23] =
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_ON].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SPECIAL_CHARACTER].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SET_LETTER_COLOR].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CHANGE_INPUT_LANGUAGE].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_WHISPER_ID].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NORMAL_CHATING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TEAM_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_NORMAL_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_TEAM_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_NO_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_OFF].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_NORMAL_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_TEAM_CHATTING].GetString(),
	};

	const static char* m_vampire_chatting_button_string[23] =
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_ON].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SPECIAL_CHARACTER].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SET_LETTER_COLOR].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CHANGE_INPUT_LANGUAGE].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_WHISPER_ID].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NORMAL_CHATING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CLAN_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_NORMAL_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_CLAN_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_NO_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_OFF].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_NORMAL_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_ZONE_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_WHISPER_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_PARTY_CHATTING].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_SHOW_CLAN_CHATTING].GetString(),
	};
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_DIALOG::IsPixel(int _x, int _y)
{
	return IsInRect(_x, _y);
}

//-----------------------------------------------------------------------------
// UnacquireMouseFocus
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

//-----------------------------------------------------------------------------
// C_VS_UI_DIALOG
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_DIALOG::C_VS_UI_DIALOG(int _x, int _y, int width, int height, void (*exec_fp)(C_VS_UI_DIALOG*, id_t), WORD dd_button)
{
	m_dwDlg_Width = 0;
	m_dwDlg_Hight = 0;

	if (width < 10)width = (width + 2) * 81;		//���� �ڵ�� ȣȯ
	if (height < 10 && height != -1)height = (height + 2) * 81;	//���� �ڵ�� ȣȯ

	m_dwDlg_Width = width;
	m_dwDlg_Hight = height;

	m_bOkOnly = false;
	m_TempValue1 = 0;

#if __CONTENTS(__TUNING_ITEM)
	m_button_yPos = 0;
#endif //__TUNING_ITEM

#if __CONTENTS(__DYNAMIC_UI)
	m_bActiveDlg = false;
	m_Fit_Item_FrameID = -1;
	m_Effect_Id = 0;

	m_tx = (float)x - 10000.0f; // C_VS_UI_DIALOG���� �ʿ������, �ڽ� Ŭ����C_VS_UI_NPC_DIALOG�� Ÿ���� ȿ��������..
#endif //__DYNAMIC_UI

	g_RegisterWindow(this);

	AttrTopmost(true);
	//	AttrKeyboardControl(true);

	//	assert(center_x > -1);
	//	assert(exec_fp != NULL);

	//	m_center_x = center_x;
	//	m_center_y = center_y;
	m_exec_fp = exec_fp;
	m_ddb = dd_button;

	m_pC_msg_scroll_bar = NULL;
	m_pC_menu_scroll_bar = NULL;
	m_p_menu = NULL;
	m_menu_count = 0;
	//	m_pp_msg = NULL;
	m_line_count = 0;
	m_print_line_count = 0;
	m_nofit_mode_msg_y = 0;
	//	m_remained_track = 0;
	//	m_tag_up_limit = 0;
	//	m_tag_down_limit = 0;
	m_flag_menu = FALSE;
	m_button_y_list = NULL;
	m_menu_y_size = 0;

	w = width;
	h = height;
	// set Window pixel size
//	w = gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_LEFT) + 
//		 gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_CENTER)*m_center_x + 
//		 gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_RIGHT);
//	if(m_center_y != -1)
//	{
//		h = gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_UP) + 
//			gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_CENTER)*m_center_y + 
//			gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_DOWN);
//	}

	DIALOG_BUTTON_WIDTH = gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK);
	DIALOG_BUTTON_HEIGHT = gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK);
	DIALOG_BUTTON_TITLE_WIDTH = gpC_global_resource->m_pC_common_button_spk->GetWidth(C_GLOBAL_RESOURCE::BUTTON_OK_TITLE);
	DIALOG_BUTTON_TITLE_HEIGHT = gpC_global_resource->m_pC_common_button_spk->GetHeight(C_GLOBAL_RESOURCE::BUTTON_OK_TITLE);

	// -1 = center
	if (_x == -1)
		//x = RESOLUTION_X/2-w/2;
		x = g_pUserInformation->iResolution_x / 2 - w / 2;
	else
		x = _x;
	if (_y == -1 && h != -1)
		//y = RESOLUTION_Y/2-h/2;
		y = g_pUserInformation->iResolution_y / 2 - h / 2;
	else
		y = _y;

	// x��ǥ ����
	// ȭ������� �Ѿ�� ����...
	//if (Right() >= RESOLUTION_X)
	//	x = RESOLUTION_X - w;

	if (Right() >= g_pUserInformation->iResolution_x)
		x = g_pUserInformation->iResolution_x - w;


	if (x < 0)
		x = 0;
	//if (Down() >= RESOLUTION_Y && h != -1)
	//	y = RESOLUTION_Y - h;

	if (Down() >= g_pUserInformation->iResolution_y && h != -1)
		y = g_pUserInformation->iResolution_y - h;

	if (y < 0 && h != -1)
		y = 0;

	// set Button count
	m_button_count = 0;
	if (m_ddb != DIALOG_NO_BUTTON)
	{
		if (m_ddb & DIALOG_OK)
			m_button_count++;
		if (m_ddb & DIALOG_CANCEL)
			m_button_count++;
	}

	// set Client rect
	// Window�� Move���� ���� ������ �����Ѵ�.
	const int _EXTRA = 30;//2;
	m_client_rect.x = x + DECORATE_GAP + _EXTRA;
	m_client_rect.w = w - DECORATE_GAP * 2 - _EXTRA * 2;
	if (h != -1)
	{
		m_client_rect.y = y + DECORATE_GAP + _EXTRA / 2;
		m_client_rect.h = h - DECORATE_GAP * 2 - _EXTRA;
	}

	// set button
	m_pC_button_group = new ButtonGroup(this);

	if (m_ddb & DIALOG_OK && h != -1)
	{
		m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_POS(BS_OK), DIALOG_BUTTON_Y
#if __CONTENTS(__TUNING_ITEM)
			+ m_button_yPos
#endif //__TUNING_ITEM
			, DIALOG_BUTTON_WIDTH, DIALOG_BUTTON_HEIGHT, DIALOG_EXECID_OK, this, C_GLOBAL_RESOURCE::AB_BUTTON_OK));

		// �� ��ư �� �ִ� ���
		if (m_ddb & DIALOG_CANCEL)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_POS(BS_CANCEL), DIALOG_BUTTON_Y
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_WIDTH, DIALOG_BUTTON_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::AB_BUTTON_CANCEL));
		}
	}


#if __CONTENTS(__TITLE_UI_RENWEAL)
	else if (m_ddb & DIALOG_TITLE_OK && h != -1)// Ÿ��Ʋ ok ��ư 
	{
		m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_OK) - 80, DIALOG_BUTTON_TITLE_Y + 25
#if __CONTENTS(__TUNING_ITEM)
			+ m_button_yPos
#endif //__TUNING_ITEM
			, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_OK, this, C_GLOBAL_RESOURCE::BUTTON_OK_TITLE_RENEWAL));

		// �� ��ư �� �ִ� ���
		if (m_ddb & DIALOG_TITLE_CANCEL)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_CANCEL) - 77, DIALOG_BUTTON_TITLE_Y + 25
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::BUTTON_CANCEL_TITLE_RENEWAL));
		}
	}
	else if (m_ddb & DIALOG_TITLE_CANCEL)// Ÿ��Ʋ cancel
	{
		if (m_ddb & DIALOG_TITLE_CANCEL && h != -1)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_OK) - 70, DIALOG_BUTTON_TITLE_Y + 20
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::BUTTON_CANCEL_TITLE));
		}
	}



#else //__TITLE_UI_RENWEAL



	else if (m_ddb & DIALOG_TITLE_OK && h != -1)
	{
		m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_OK) - 80, DIALOG_BUTTON_TITLE_Y + 25
#if __CONTENTS(__TUNING_ITEM)
			+ m_button_yPos
#endif //__TUNING_ITEM
			, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_OK, this, C_GLOBAL_RESOURCE::BUTTON_OK_TITLE));

		// �� ��ư �� �ִ� ���
		if (m_ddb & DIALOG_TITLE_CANCEL)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_CANCEL) - 77, DIALOG_BUTTON_TITLE_Y + 25
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::BUTTON_CANCEL_TITLE));
		}
	}
	else if (m_ddb & DIALOG_TITLE_CANCEL)// Ÿ��Ʋ cancel
	{
		if (m_ddb & DIALOG_TITLE_CANCEL && h != -1)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_TITLE_POS(BS_OK) - 70, DIALOG_BUTTON_TITLE_Y + 20
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_TITLE_WIDTH, DIALOG_BUTTON_TITLE_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::BUTTON_CANCEL_TITLE));
		}
	}
#endif // __TITLE_UI_RENWEAL
	else
	{
		// cancel�� �ִ� ���
		if (m_ddb & DIALOG_CANCEL && h != -1)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(DIALOG_BUTTON_POS(BS_OK), DIALOG_BUTTON_Y
#if __CONTENTS(__TUNING_ITEM)
				+ m_button_yPos
#endif //__TUNING_ITEM
				, DIALOG_BUTTON_WIDTH, DIALOG_BUTTON_HEIGHT, DIALOG_EXECID_CANCEL, this, C_GLOBAL_RESOURCE::AB_BUTTON_CANCEL));
		}
	}

	m_blSelect_Return_Button = TRUE;
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_DIALOG
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_DIALOG::~C_VS_UI_DIALOG()
{
	g_UnregisterWindow(this);


	if (m_pC_menu_scroll_bar)
	{
		DeleteNew(m_pC_menu_scroll_bar);
	}
	if (m_pC_msg_scroll_bar)
	{
		DeleteNew(m_pC_msg_scroll_bar);
	}
	//	for (int i=0; i < m_menu_count; i++)
	//	{
	//		DeleteNewArray(m_p_menu[i].sz_menu_str);
	//	}

	DeleteNewArray(m_p_menu);
	DeleteNewArray(m_button_y_list);

	DeleteNew(m_pC_button_group);
}




DWORD	C_VS_UI_DIALOG::GetWidth()
{
	return m_dwDlg_Width;
}



DWORD	C_VS_UI_DIALOG::GetHight()
{
	return m_dwDlg_Hight;
}



//-----------------------------------------------------------------------------
// C_VS_UI_DIALOG::CancelPushState
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_DIALOG::CancelPushState()
{
	//	m_tag_pushed = false;
	m_pC_button_group->CancelPushState();
}

//-----------------------------------------------------------------------------
// GetButtonGap
//
// button�� �ֳľ��ĸ� �����Ͽ� button height gap�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
int C_VS_UI_DIALOG::GetButtonGap() const
{
	if (m_button_count > 0)
		return DIALOG_BUTTON_HEIGHT + DIALOG_BUTTON_EXTRA_HGAP;
	else
		return DIALOG_BUTTON_EXTRA_HGAP;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::Run(id_t id)
{
	if (m_exec_fp == NULL)return;

	if (id != DIALOG_EXECID_SCROLL_UP && id != DIALOG_EXECID_SCROLL_DOWN)
		m_exec_fp(this, id);

	switch (id)
	{
		//		case DIALOG_EXECID_SCROLL_UP:
		//			m_scrollbar.DecreaseAmountToScroll();
		//			break;

		//		case DIALOG_EXECID_SCROLL_DOWN:
		//			m_scrollbar.IncreaseAmountToScroll();
		//			break;

	case DIALOG_EXECID_OK:
#ifdef _LIB
		if (true == g_pUserInformation->IsAutoLogIn) // �� �ڵ� �α� �� ��� 
			gpC_base->SendMessage(UI_TERMINATION, 0, 0); // ��尡 ���� �޴� �� ��
#endif
		Finish();
		break;

	case DIALOG_EXECID_CANCEL:
	case DIALOG_EXECID_EXIT:
		Finish();
		break;
	}

	// scroll up/down common control
//	if (m_available_tag == true)
//	{
//		// change scroll tag position
//		double proportion = Proportion(m_scrollbar.GetPercentToScroll(), PERCENTAGE, m_remained_track);
//
//		// �Ҽ� ù°�ڸ� �ݿø�.
//		proportion += 0.5;
//		m_tag_rect.y = m_tag_up_limit+(int)floor(proportion);
//	}
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::KeyboardControl(UINT message, UINT key, long extra)
{
	Window::KeyboardControl(message, key, extra);

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN: // ok�� ����. !cancel�� �ݵ�� ok�� �Բ� �ִ�.
			if (m_blSelect_Return_Button == FALSE)
			{
				Run(DIALOG_EXECID_EXIT);
			}
			else
			{
				if ((m_ddb & DIALOG_OK) || (m_ddb & DIALOG_TITLE_OK))
					Run(DIALOG_EXECID_OK);
			}
			break;

			/* Ȯ�θ� �㶧�� Ȯ�� ���������� ó���Ϸ��� �õ� ������ ���� ������ �����ڸ� ������ ��𼭵�
			SetOkOnly()�� ���ؼ� m_bOkOnly�� ������ ���� �ʴ´�. */
		case VK_ESCAPE: // �ƹ��͵� ����.
			if (true == m_bOkOnly)
				Run(DIALOG_EXECID_OK);
			else
			{
				Run(DIALOG_EXECID_EXIT);

				/*20070514 by diesirace Ȯ�� ��ư�� �㶩 �����ϱ� �ڵ�
				if(m_ddb == DIALOG_OK)
				{
				}
				else
				{
					Run(DIALOG_EXECID_EXIT);
				}*/
			}
			break;
		case VK_LEFT:
			m_blSelect_Return_Button = TRUE;
			break;
		case VK_RIGHT:
			m_blSelect_Return_Button = FALSE;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_DIALOG::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);

	if (m_pC_menu_scroll_bar)
	{
		BOOL result = m_pC_menu_scroll_bar->MouseControl(message, _x - m_menu_rect.x, _y - m_menu_rect.y);
		if (result == false) ProcessMenuScrollBar();
		if (GetScrollPos() > 0)
		{
			int skip;
			skip = m_button_y_list[GetScrollPos()] - m_button_y_list[0];
			m_pC_button_group->MouseControl(message, _x, _y + skip + m_menu_y_size
#if __CONTENTS(__TUNING_ITEM)
				- m_button_yPos
#endif //__TUNING_ITEM
			);
		}
		else
			m_pC_button_group->MouseControl(message, _x, _y + m_menu_y_size
#if __CONTENTS(__TUNING_ITEM)
				- m_button_yPos
#endif //__TUNING_ITEM
			);
	}
	else m_pC_button_group->MouseControl(message, _x, _y + m_menu_y_size
#if __CONTENTS(__TUNING_ITEM)
		- m_button_yPos
#endif //__TUNING_ITEM
	);

	// control scroll bar tag
//	if (m_available_tag == true)
	if (m_pC_msg_scroll_bar)
	{
		m_pC_msg_scroll_bar->MouseControl(message, _x - m_msg_rect.x, _y - m_msg_rect.y);
	}
	{
		switch (message)
		{
		case M_MOVING:
			if (_y >= m_msg_rect.y && _y < m_msg_rect.y + m_msg_rect.h)
			{
				//					if (m_tag_pushed == true)
				//					{
				//						m_tag_rect.y += _y-m_prev_tag_y;
				//						m_prev_tag_y = _y;
				//
				//						// check limit
				//						if (m_tag_rect.y < m_tag_up_limit)
				//							m_tag_rect.y = m_tag_up_limit;
				//						if (m_tag_rect.y > m_tag_down_limit)
				//							m_tag_rect.y = m_tag_down_limit;
				//
				//						m_scrollbar.SetAmountToScrollByPercent(Percentage(m_tag_rect.y-m_tag_up_limit, m_remained_track));
				//					}
			}
			break;

		case M_LEFTBUTTON_DOWN:
		case M_LB_DOUBLECLICK:
			//				if (m_tag_rect.IsInRect(_x, _y) == true)
			//				{
			//					m_tag_pushed = true;
			//					m_prev_tag_y = _y;
			//				}
			break;

		case M_LEFTBUTTON_UP:
			CancelPushState();
			break;

		case M_WHEEL_UP:
			if (_x > m_msg_rect.x && _x<m_msg_rect.x + m_msg_rect.w && _y>m_msg_rect.y && _y < m_msg_rect.y + m_msg_rect.h)
			{
				if (m_pC_msg_scroll_bar)
					m_pC_msg_scroll_bar->ScrollUp();
			}
			else
				if (_x > m_menu_rect.x && _x<m_menu_rect.x + m_menu_rect.w && _y>m_menu_rect.y && _y < m_menu_rect.y + m_menu_rect.h)
				{
					if (m_pC_menu_scroll_bar)
						m_pC_menu_scroll_bar->ScrollUp();
				}
#if __CONTENTS(__BLITZ_COUPON_EVENT)
			ProcessMenuScrollBar(120);
#else
			ProcessMenuScrollBar();
#endif //__BLITZ_COUPON_EVENT
			//				Run(DIALOG_EXECID_SCROLL_UP);
			break;

		case M_WHEEL_DOWN:
			if (_x > m_msg_rect.x && _x<m_msg_rect.x + m_msg_rect.w && _y>m_msg_rect.y && _y < m_msg_rect.y + m_msg_rect.h)
			{
				if (m_pC_msg_scroll_bar)
					m_pC_msg_scroll_bar->ScrollDown();
			}
			else
				if (_x > m_menu_rect.x && _x<m_menu_rect.x + m_menu_rect.w && _y>m_menu_rect.y && _y < m_menu_rect.y + m_menu_rect.h)
				{
					if (m_pC_menu_scroll_bar)
						m_pC_menu_scroll_bar->ScrollDown();
				}
#if __CONTENTS(__BLITZ_COUPON_EVENT)
			ProcessMenuScrollBar(-120);
#else
			ProcessMenuScrollBar();
#endif //__BLITZ_COUPON_EVENT
			//				Run(DIALOG_EXECID_SCROLL_DOWN);
			break;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// ShowButtonDescription
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::ShowButtonDescription(C_VS_UI_EVENT_BUTTON* p_button)
{
}


//-----------------------------------------------------------------------------
// ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::ShowButtonWidget(C_VS_UI_EVENT_BUTTON* p_button)
{
	int i;

#if __CONTENTS(__DYNAMIC_UI)
	if (m_tx >= (float)(g_pUserOption->Resolution1024 ? 1024 : 800))
	{
		p_button->x = -100;
	}
#endif //__DYNAMIC_UI

	// Menu button�� �׳� Button�� �ٸ��� ó��. 
	if (p_button->GetID() == DIALOG_EXECID_OK ||
		p_button->GetID() == DIALOG_EXECID_CANCEL)
	{
		if (p_button->GetFocusState())
		{

			if (p_button->GetID() == DIALOG_EXECID_OK)
			{
				m_blSelect_Return_Button = TRUE;
			}
			else
			{
				m_blSelect_Return_Button = FALSE;
			}

			if (p_button->GetPressState())
			{
				if ((m_ddb & DIALOG_TITLE_OK) || (m_ddb & DIALOG_TITLE_CANCEL) || (m_ddb & (DIALOG_TITLE_CANCEL | DIALOG_TITLE_OK)))
				{
					gpC_global_resource->m_pC_common_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
						+ m_button_yPos
#endif //__TUNING_ITEM
						, p_button->m_image_index + 2);
				}
				else
				{
					gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
						+ m_button_yPos
#endif //__TUNING_ITEM
						, p_button->m_image_index + C_GLOBAL_RESOURCE::AB_BUTTON_PUSHED_OFFSET);
				}
			}
			else
			{
				if ((m_ddb & DIALOG_TITLE_OK) || (m_ddb & DIALOG_TITLE_CANCEL) || (m_ddb & (DIALOG_TITLE_CANCEL | DIALOG_TITLE_OK)))
				{
					gpC_global_resource->m_pC_common_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
						+ m_button_yPos
#endif //__TUNING_ITEM
						, p_button->m_image_index + 4);
				}
				else
				{
					gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
						+ m_button_yPos
#endif //__TUNING_ITEM
						, p_button->m_image_index + C_GLOBAL_RESOURCE::AB_BUTTON_HILIGHTED_OFFSET);
				}
			}
		}
		else
		{
			if ((m_ddb & DIALOG_TITLE_OK) || (m_ddb & DIALOG_TITLE_CANCEL) || (m_ddb & (DIALOG_TITLE_CANCEL | DIALOG_TITLE_OK)))
			{
				gpC_global_resource->m_pC_common_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
					+ m_button_yPos
#endif //__TUNING_ITEM
					, p_button->m_image_index);
			}
			else
			{
				gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
					+ m_button_yPos
#endif //__TUNING_ITEM
					, p_button->m_image_index);
			}



			if (gpC_dialog_confirm_item_bay_messagebox == this)
			{
				if (m_blSelect_Return_Button)
				{
					if (p_button->GetID() == DIALOG_EXECID_OK)
					{
						gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
							+ m_button_yPos
#endif //__TUNING_ITEM
							, p_button->m_image_index + C_GLOBAL_RESOURCE::AB_BUTTON_HILIGHTED_OFFSET);
					}
				}
				else
				{
					if (p_button->GetID() == DIALOG_EXECID_CANCEL)
					{
						gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y
#if __CONTENTS(__TUNING_ITEM)
							+ m_button_yPos
#endif //__TUNING_ITEM
							, p_button->m_image_index + C_GLOBAL_RESOURCE::AB_BUTTON_HILIGHTED_OFFSET);
					}
				}
			}



		}
	}
	else if (p_button->GetID() == DIALOG_EXECID_SCROLL_UP ||
		p_button->GetID() == DIALOG_EXECID_SCROLL_DOWN)
	{
		//		gpC_global_resource->m_pC_assemble_box_etc_spk->Blt(p_button->x, p_button->y, p_button->m_image_index);

		//		if (p_button->GetFocusState() && p_button->GetPressState())
		//			gpC_global_resource->m_pC_assemble_box_etc_spk->Blt(p_button->x+1, p_button->y+1, p_button->m_image_index+2);
	}
	else
	{
		if (m_menu_rect.w != 0 && m_menu_rect.h != 0)
		{
			PrintInfo* p_pi;

			// �޴� �̵��� ���� ��ư ��ǥ ���� ��
			int y_skip_line = 0;
			if (m_pC_menu_scroll_bar != NULL)
			{
				if (p_button->m_image_index < GetScrollPos()) return;
				if (p_button->m_image_index > 0 && m_button_y_list != NULL && GetScrollPos() > 0)
					y_skip_line = m_button_y_list[GetScrollPos()] - m_temp_menu_rect_y;
			}
			y_skip_line += m_menu_y_size;			// m_menu_y_size �� �޴�Rect ũ�Ⱑ ����Ǿ����� ������ ���̴�.


			if (p_button->GetFocusState())
			{
#if __CONTENTS(__DYNAMIC_UI)
				gpC_base->m_info_pi.text_color = RGB(180, 180, 255);
				p_pi = &gpC_base->m_info_pi;
#else
				gpC_base->m_dialog_menu_pi.text_color = RGB(180, 180, 255);
				p_pi = &gpC_base->m_dialog_menu_pi;
#endif //__DYNAMIC_UI
				// arrow^^
//				gpC_global_resource->m_pC_assemble_box_etc_spk->Blt(p_button->x-15, p_button->y+1, C_GLOBAL_RESOURCE::AB_RIGHT_ARROW);
//				gpC_global_resource->m_pC_assemble_box_etc_spk->Blt(p_button->Right()+9, p_button->y+1, C_GLOBAL_RESOURCE::AB_LEFT_ARROW);
//				gpC_global_resource->m_pC_assemble_box_etc_spk->Blt(p_button->x-25, p_button->y+1, C_GLOBAL_RESOURCE::AB_LEFT_ARROW);

			}
			else
			{
#if __DYNAMIC_UI
				gpC_base->m_info_pi.text_color = RGB_WHITE;

				p_pi = &gpC_base->m_info_pi;
#else
				gpC_base->m_dialog_menu_pi.text_color = RGB_WHITE;

				p_pi = &gpC_base->m_dialog_menu_pi;
#endif //__DYNAMIC_UI
			}

#if __CONTENTS(__DYNAMIC_UI)
			p_button->x = x + 230;
#endif //__DYNAMIC_UI

			if (p_button->GetFocusState() && p_button->GetPressState())
			{
				if (p_button->y - y_skip_line < m_menu_rect.y + m_menu_rect.h)
					gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x - 20, p_button->y + 2 - y_skip_line, C_GLOBAL_RESOURCE::AB_DIALOG_TAG_SELECTED);

				if (!m_p_menu[p_button->m_image_index].sz_menu_str.empty())
				{
					g_FL2_GetDC();
					for (i = 0; i < m_p_menu[p_button->m_image_index].sz_menu_str.size(); i++)
					{
						if (p_button->y - i * TEXT_EXTRA_HGAP - y_skip_line + m_menu_str_height * i < m_menu_rect.y + m_menu_rect.h)
#if __CONTENTS(__DYNAMIC_UI)
							g_Print(p_button->x + 5, p_button->y + 6 + m_menu_str_height * i - TEXT_EXTRA_HGAP * i - y_skip_line, m_p_menu[p_button->m_image_index].sz_menu_str[i].c_str(), p_pi);
#else
							g_Print(p_button->x, p_button->y + 6 + m_menu_str_height * i - TEXT_EXTRA_HGAP * i - y_skip_line, m_p_menu[p_button->m_image_index].sz_menu_str[i].c_str(), p_pi);
#endif //__DYNAMIC_UI
					}
					g_FL2_ReleaseDC();
				}
			}
			else
			{
				if (p_button->GetFocusState())
				{
					if (p_button->y - y_skip_line < m_menu_rect.y + m_menu_rect.h)
						gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x - 20, p_button->y - y_skip_line, C_GLOBAL_RESOURCE::AB_DIALOG_TAG_SELECTED);
				}
				else
				{
					if (p_button->y - y_skip_line < m_menu_rect.y + m_menu_rect.h)
						gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x - 20, p_button->y - y_skip_line, C_GLOBAL_RESOURCE::AB_DIALOG_TAG);
				}
				if (!m_p_menu[p_button->m_image_index].sz_menu_str.empty())
				{
					g_FL2_GetDC();
					for (i = 0; i < m_p_menu[p_button->m_image_index].sz_menu_str.size(); i++)
					{
						// ������ �����ش�.
						if (p_button->y - i * TEXT_EXTRA_HGAP - y_skip_line + m_menu_str_height * i < m_menu_rect.y + m_menu_rect.h)
						{
							//m_p_menu[p_button->m_image_index].sz_menu_str[i].c_str()
							if (m_p_menu != NULL && p_button->m_image_index < m_menu_count && i <= m_p_menu[p_button->m_image_index].sz_menu_str.size() && m_p_menu[p_button->m_image_index].sz_menu_str[i].size() > 0)
#if __CONTENTS(__DYNAMIC_UI)
								g_Print(p_button->x + 5, p_button->y + 4 + m_menu_str_height * i - TEXT_EXTRA_HGAP * i - y_skip_line, m_p_menu[p_button->m_image_index].sz_menu_str[i].c_str(), p_pi);
#else
								g_Print(p_button->x, p_button->y + 4 + m_menu_str_height * i - TEXT_EXTRA_HGAP * i - y_skip_line, m_p_menu[p_button->m_image_index].sz_menu_str[i].c_str(), p_pi);
#endif //__DYNAMIC_UI
						}
					}
					g_FL2_ReleaseDC();
				}
			}
		}
	}

}




#if __CONTENTS(__TITLE_UI_RENWEAL)
WORD	C_VS_UI_DIALOG::Get_RGB_16(BYTE btRGB_R, BYTE btRGB_G, BYTE btRGB_B)
{
	WORD	wRGB = 0;

	wRGB += (BYTE)(((float)((float)btRGB_R / 255)) * 31);

	wRGB = wRGB << 6;
	wRGB += (BYTE)(((float)((float)btRGB_G / 255)) * 63);

	wRGB = wRGB << 5;
	wRGB += (BYTE)(((float)((float)btRGB_B / 255)) * 31);

	return wRGB;
}


WORD	C_VS_UI_DIALOG::Get_RGBAlpha_16(BYTE btRGB_Alpha)
{
	WORD	wRGBAlpha = 0;

	if (btRGB_Alpha > 100)
		btRGB_Alpha = 10;

	wRGBAlpha = (BYTE)(((float)((float)btRGB_Alpha / 100)) * 31);

	return wRGBAlpha;
}


void	C_VS_UI_DIALOG::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255] = { NULL, };
	char arrstrFileName[255] = { NULL, };

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//���� ���� ���� ������ ��θ� ��´�.

	strcpy(arrstrAppName, "RGB_16");

	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_btBox_RGB_R = (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_R", 0, arrstrFileName);
	m_btBox_RGB_G = (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_G", 0, arrstrFileName);
	m_btBox_RGB_B = (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_B", 0, arrstrFileName);
	m_btBox_RGB_Alpha = (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_ALPHA", 0, arrstrFileName);

	m_btLine_RGB_R = (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_R", 0, arrstrFileName);
	m_btLine_RGB_G = (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_G", 0, arrstrFileName);
	m_btLine_RGB_B = (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_B", 0, arrstrFileName);
}


#endif //__TITLE_UI_RENWEAL







//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::Show()
{


	int i;
	//	int i, j;
	//	int _x = x+81;//gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_LEFTUP);
	//	int _y = y+h-81;//gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_LEFTDOWN);


	if ((m_ddb & DIALOG_TITLE_OK) || (m_ddb & DIALOG_TITLE_CANCEL) || (m_ddb & DIALOG_TITLE_NO_BUTTON))
	{
		RECT mssageBox;

		mssageBox.left = x;
		mssageBox.top = y;
		mssageBox.right = x + w;
		mssageBox.bottom = y + h;

#if __CONTENTS(__TITLE_UI_RENWEAL)
		Init_TitleUIInterface_InfInfo();

		WORD	wBox_RGB = Get_RGB_16(m_btBox_RGB_R, m_btBox_RGB_G, m_btBox_RGB_B);
		WORD	wLine_RGB = Get_RGB_16(m_btLine_RGB_R, m_btLine_RGB_G, m_btLine_RGB_B);
		WORD	wBoxRGB_Alpha = Get_RGBAlpha_16(m_btBox_RGB_Alpha);

		gpC_base->m_p_DDSurface_back->DrawRect(&mssageBox, wLine_RGB);
		gpC_base->m_p_DDSurface_back->BltColorAlpha(&mssageBox, wBox_RGB, wBoxRGB_Alpha);
#else	// __TITLE_UI_RENWEAL

		gpC_base->m_p_DDSurface_back->DrawRect(&mssageBox, 0x3BCA);

		gpC_base->m_p_DDSurface_back->BltColorAlpha(&mssageBox, 0x2245, 5);
#endif //__TITLE_UI_RENWEAL

	}
	else
	{
		gpC_global_resource->DrawDialog(x, y, w, h, GetAttributes()->alpha);
	}
	//	Rect rect;
	//	rect.Set(0, 0, w-2, h-2);
	//
	//	// alpha�� ���õǾ� ������ ������â���� ��� :)
	//	if(GetAttributes()->alpha)
	//	{
	//		RECT alpha_rect;
	//		if(gbl_vampire_interface)
	//			SetRect(&alpha_rect, x+10, y+9, x+rect.w-7, y+rect.h-8);
	//		else
	//			SetRect(&alpha_rect, x+5, y+12, x+rect.w-4, y+rect.h-10);
	//		DrawAlphaBox(&alpha_rect, 0, 0, 0, ALPHA_DEPTH);
	//		gpC_global_resource->m_pC_assemble_box_spk->BltClip(x, y, rect, C_GLOBAL_RESOURCE::AB_BACK_ALPHA);
	//	}
	//	else
	//		gpC_global_resource->m_pC_assemble_box_spk->BltClip(x, y, rect, C_GLOBAL_RESOURCE::AB_BACK);
	//
	//	rect.Set(0, 0, gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_RIGHT), h);
	//	gpC_global_resource->m_pC_assemble_box_spk->BltClip(x+w - gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_RIGHT), y, rect, C_GLOBAL_RESOURCE::AB_RIGHT);
	//	rect.Set(0, 0, w, gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_DOWN));
	//	gpC_global_resource->m_pC_assemble_box_spk->BltClip(x, y+h - gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_DOWN), rect, C_GLOBAL_RESOURCE::AB_DOWN);
	//	gpC_global_resource->m_pC_assemble_box_spk->Blt(x+w - gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_RIGHTDOWN), y+h - gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_RIGHTDOWN), C_GLOBAL_RESOURCE::AB_RIGHTDOWN);
	//	if (gpC_base->m_p_DDSurface_back->Lock())
	//	{
	//	gpC_global_resource->m_pC_assemble_box_spk->BltLocked(x, y, C_GLOBAL_RESOURCE::AB_LEFTUP);
	//	gpC_global_resource->m_pC_assemble_box_spk->BltLocked(x, _y, C_GLOBAL_RESOURCE::AB_LEFTDOWN);
	//
	//	for (i=0; i < m_center_x; i++)
	//	{
	//		gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, y, C_GLOBAL_RESOURCE::AB_UP);
	//		gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, _y, C_GLOBAL_RESOURCE::AB_DOWN);
	//		_x += gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_UP);
	//	}
	//	gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, y, C_GLOBAL_RESOURCE::AB_RIGHTUP);
	//	gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, _y, C_GLOBAL_RESOURCE::AB_RIGHTDOWN);
	//
	//	// center
	//	// !�� block�� ũ�Ⱑ �ٸ� �� �ִ�.
	//	_y = y+gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_LEFTUP);
	//	for (j=0; j < m_center_y; j++)
	//	{
	//		gpC_global_resource->m_pC_assemble_box_spk->BltLocked(x, 
	//				_y+gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_LEFT)*j,
	//				C_GLOBAL_RESOURCE::AB_LEFT);
	//
	//		_x = x+gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_LEFT);
	//
	//		for (i=0; i < m_center_x; i++)
	//		{
	//			gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, 
	//					_y+gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_LEFT)*j,
	//					C_GLOBAL_RESOURCE::AB_CENTER);
	//
	//			_x += gpC_global_resource->m_pC_assemble_box_spk->GetWidth(C_GLOBAL_RESOURCE::AB_UP);
	//		}
	//
	//		gpC_global_resource->m_pC_assemble_box_spk->BltLocked(_x, 
	//				_y+gpC_global_resource->m_pC_assemble_box_spk->GetHeight(C_GLOBAL_RESOURCE::AB_LEFT)*j,
	//				C_GLOBAL_RESOURCE::AB_RIGHT);
	//	}
	//	}

		// message
	gpC_base->m_p_DDSurface_back->Lock();
	if (m_msg_rect.h != 0 && !m_vs_msg.empty())
	{
#if __CONTENTS(__DYNAMIC_UI)
		m_msg_rect.x = m_client_rect.x;
#endif //__DYNAMIC_UI

		if (m_message_mode == SMO_FIT)
		{
			int line;
			if (m_line_count > m_print_line_count)
			{
				line = m_print_line_count;

				//				if (gpC_base->m_p_DDSurface_back->Lock()) // draw track
				//				{
				//				if(m_msg_rect.h > 0)
				//				{
				//					S_SURFACEINFO	surfaceinfo;
				//					SetSurfaceInfo(&surfaceinfo, gpC_base->m_p_DDSurface_back->GetDDSD());
				//
				//					int track_x = m_msg_rect.x+m_msg_rect.w+m_tag_rect.w/2;
				//					vertline(&surfaceinfo, track_x, m_msg_rect.y, track_x, m_msg_rect.Down(), BLACK);
				//					vertline(&surfaceinfo, track_x+1, m_msg_rect.y, track_x+1, m_msg_rect.Down(), DARKGRAY);
				//				}

				//				}

				//				if (m_available_tag == true)
				//					gpC_global_resource->m_pC_assemble_box_etc_spk->BltLocked(m_tag_rect.x, m_tag_rect.y, C_GLOBAL_RESOURCE::AB_SCROLL_TAG);
			}
			else
				line = m_line_count;

			//			int scrolled = m_scrollbar.GetAmountToScroll();
			int scrolled = 0;
			if (m_pC_msg_scroll_bar)
				scrolled = m_pC_msg_scroll_bar->GetScrollPos();


			gpC_base->m_p_DDSurface_back->Unlock();
			g_FL2_GetDC();
			m_msg_rect.x = m_client_rect.x;

#if __CONTENTS(__DYNAMIC_UI)
			bool ShowLineCopy = true;

			if ((int)m_tx - x > 20)
			{
				ShowLineCopy = false;
			}

			for (i = 0; i < m_line_count; i++)
			{
				if (ShowLineCopy && m_vs_msg[i].size() != 0 && m_vs_Show_msg[i].size() <= m_vs_msg[i].size())
				{
					ShowLineCopy = false;
					m_vs_Show_msg[i] += m_vs_msg[i][m_vs_Show_msg[i].size()];
				}
			}
#endif //__DYNAMIC_UI

			for (i = 0; i < line; i++)
			{
#if __CONTENTS(__DYNAMIC_UI)

				g_Print(m_msg_rect.x,
					m_msg_rect.y + 5 + (g_GetStringHeight(m_vs_Show_msg[i + scrolled].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP) * i,
					m_vs_Show_msg[i + scrolled].c_str(),
					&gpC_base->m_dialog_msg_pi);
#else
				g_Print(m_msg_rect.x,
					m_msg_rect.y + 5 + (g_GetStringHeight(m_vs_msg[i + scrolled].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP) * i,
					m_vs_msg[i + scrolled].c_str(),
					&gpC_base->m_dialog_msg_pi);
#endif //__DYNAMIC_UI
			}

			g_FL2_ReleaseDC();
		}
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		else if (m_message_mode == SMO_FIT_ITEM) // ���̾�α� �ڽ��� ������ �׷���.
		{
			int line;
			if (m_line_count > m_print_line_count)
			{
				line = m_print_line_count;
			}
			else
				line = m_line_count;

			int scrolled = 0;
			if (m_pC_msg_scroll_bar)
				scrolled = m_pC_msg_scroll_bar->GetScrollPos();

			// ItemObject Image //////////////////////////////////////////////////////////////////////////
			// �Ʒ��ڵ�� SMO_FIT_ITEM ��带 ����Ұ��, �������� ���̾�α� �ڽ��� �׷��ִµ�, 
			// EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3 ����Ʈ�� EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150 ����Ʈ��
			// �ѷ��ش�. �׸��� ���� SOUND_EVENT_FANFARE�� ������ش�.
			// ������ �� 3����ȿ���� ������ �ʴ´ٸ�, SMO_FIT_ITEM�� ����ϸ� �ȵȴ�. �̰��� �����Ѵٸ�
			// ���������� ����� ������������, ����μ��� __BLITZ_COUPON_EVENT�� Ưȭ�� �ڵ尡 ��� �����Ƿ� ����. 2008.9.3 - ij-ch

			POINT obj_pt = { x + 40,y + 40 };
			POINT eff_pt = { obj_pt.x - 20,obj_pt.y + 60 }; // ����� ����(����Ʈ ������ǥ)

			if (m_Effect_Id == (int)EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150) // 972
			{
				eff_pt.x -= 3;
				eff_pt.y -= 18;
			}

			eff_pt.x += (gpC_item->GetWidth(m_Fit_Item_FrameID) / 2);
			eff_pt.y += (gpC_item->GetHeight(m_Fit_Item_FrameID) / 2);

			bool bEffectDraw = DrawUIEffect(&eff_pt, (int)m_Effect_Id, 0, 4, false);

			if (m_Fit_Item_FrameID != -1 && (m_Effect_Id == (int)EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150 || !bEffectDraw))
			{
				if (m_Effect_Id == (int)EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3)
				{
					PlaySound(SOUND_EVENT_FANFARE);
				}

				m_Effect_Id = (int)EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150;

				if (!bEffectDraw)
				{
					Set_UIEffect_Frame_Zero();
				}

				gpC_item->BltLocked(obj_pt.x, obj_pt.y, m_Fit_Item_FrameID);
			}
			// End ItemObject Image //////////////////////////////////////////////////////////////////////////

			gpC_base->m_p_DDSurface_back->Unlock();
			g_FL2_GetDC();
			m_msg_rect.x = m_client_rect.x + gpC_item->GetWidth(1325);

#if __CONTENTS(__DYNAMIC_UI)
			bool ShowLineCopy = true;

			if (m_Effect_Id == (int)EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3)
			{
				ShowLineCopy = false;
			}

			for (i = 0; i < m_line_count; i++)
			{
				if (ShowLineCopy && m_vs_msg[i].size() != 0 && m_vs_Show_msg[i].size() <= m_vs_msg[i].size())
				{
					ShowLineCopy = false;
					m_vs_Show_msg[i] += m_vs_msg[i][m_vs_Show_msg[i].size()];
				}
			}
#endif //__DYNAMIC_UI

			for (i = 0; i < line; i++)
			{
#if __CONTENTS(__DYNAMIC_UI)
				g_Print(m_msg_rect.x,
					m_msg_rect.y + 5 + (g_GetStringHeight(m_vs_Show_msg[i + scrolled].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP) * i,
					m_vs_Show_msg[i + scrolled].c_str(),
					&gpC_base->m_dialog_msg_pi);
#else
				g_Print(m_msg_rect.x,
					m_msg_rect.y + 5 + (g_GetStringHeight(m_vs_msg[i + scrolled].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP) * i,
					m_vs_msg[i + scrolled].c_str(),
					&gpC_base->m_dialog_msg_pi);
#endif //__DYNAMIC_UI
			}
			g_FL2_ReleaseDC();
		}
#endif //__BLITZ_COUPON_EVENT
		else
		{

			gpC_base->m_p_DDSurface_back->Unlock();
			m_line_count = m_vs_msg.size();
			if (m_line_count <= m_print_line_count)
			{
				g_FL2_GetDC();
				for (i = 0; i < m_line_count; i++)
					g_Print(m_msg_rect.x + m_msg_rect.w / 2 - g_GetStringWidth(m_vs_msg[i].c_str(), gpC_base->m_dialog_msg_pi.hfont) / 2,
						m_nofit_mode_msg_y + (g_GetStringHeight(m_vs_msg[i].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP) * i,
						m_vs_msg[i].c_str(),
						&gpC_base->m_dialog_msg_pi);
				g_FL2_ReleaseDC();
			}
		}

		// draw boundary line
//		if (m_menu_count > 0)
//		{
//			if (gpC_base->m_p_DDSurface_back->Lock()) // draw track
//			{
//				S_SURFACEINFO	surfaceinfo;
//				SetSurfaceInfo(&surfaceinfo, gpC_base->m_p_DDSurface_back->GetDDSD());
//
//				int b_y = m_msg_rect.y+m_msg_rect.h+4;
//				horzline(&surfaceinfo, m_msg_rect.x, b_y, m_msg_rect.Right(), b_y, BLACK);
//				horzline(&surfaceinfo, m_msg_rect.x, b_y+1, m_msg_rect.Right(), b_y+1, DARKGRAY);
//
//				gpC_base->m_p_DDSurface_back->Unlock();
//			}
//		}
	}
	else
	{
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	m_pC_button_group->Show();
	if (m_pC_msg_scroll_bar)
		m_pC_msg_scroll_bar->Show(m_msg_rect.x, m_msg_rect.y);
	if (m_pC_menu_scroll_bar)
		m_pC_menu_scroll_bar->Show(m_menu_rect.x, m_menu_rect.y);
#ifndef _LIB
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		S_SURFACEINFO	surfaceinfo;
		SetSurfaceInfo(&surfaceinfo, gpC_base->m_p_DDSurface_back->GetDDSD());

		//rectangle(&surfaceinfo, this, WHITE);
		//FillRect(&surfaceinfo, &m_client_rect, WHITE);
		//FillRect(&surfaceinfo, &m_menu_rect, BLUE);
		//FillRect(&surfaceinfo, &m_msg_rect, BLUE);

		gpC_base->m_p_DDSurface_back->Unlock();
	}
#endif

	SHOW_WINDOW_ATTR;

}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::Start()
{

	AttrAlpha(g_pUserOption->DefaultAlpha != FALSE);

	PI_Processor::Start();

#if __CONTENTS(__DYNAMIC_UI)
	m_bActiveDlg = true;
#endif //__DYNAMIC_UI

	m_pC_button_group->Init();

	gpC_window_manager->AppearWindow(this);

	//	m_tag_pushed = false;
	//	m_prev_tag_y = 0;

	if (gpC_dialog_confirm_item_bay_messagebox == this)			//�������� ������ �޽��� �ڽ��� ��� ���̾� �α��� ��
	{
		m_blSelect_Return_Button = FALSE;
	}
	else
	{
		m_blSelect_Return_Button = TRUE;
	}

}

//-----------------------------------------------------------------------------
// StartByPinMode
//
// pin mode�� Start�Ѵ�.
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::StartByPinMode()
{
	AttrTopmost(false);
	AttrPin(true);

	Start();
}

//-----------------------------------------------------------------------------
// Finish
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::Finish()
{
	PI_Processor::Finish();

#if __CONTENTS(__DYNAMIC_UI)
	m_bActiveDlg = false;
#endif //__DYNAMIC_UI

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// SetMessage
//
// - Message rect = (Client rect - Menu rect - Button rect)
// - If the height cannot be calculated, it will not be displayed. (Not implemented yet)
//
// Parameter format:
//     std::string pp_msg[] = {"line1", "line2", ...} // global or local static
//     SetMessage(pp_msg, line_x);
//
// Behavior notes:
//     The existing SetMessage is kept as-is, but a flag (m_flag_menu) was added
//     so that scrolling is automatically handled only when a menu exists.
//     You MUST call SetMenu first, then SetMessage, for the menu scrolling to work correctly.
//
// Fixes:
//     If problems occur in a normal dialog, uncomment the ----[Fix]---- section
//     to resolve it. In this revision, only this part was modified.
//
// Notes:
//     SetMessage expects an array of C-style strings (char*), one per line.
//     The system displays multi-line messages and is sensitive to call order.
//     Messages may not appear if the height cannot be calculated.
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::SetMessage(std::string* sz_msg, UINT line_count, SETMESSAGE_MODE_OPTION mode, int nLineCheck, int iMsgWidth)
{
	assert(sz_msg != NULL);
	assert(line_count > 0);

	if (sz_msg == NULL || line_count == 0)
		return;

	m_message_mode = mode;

#if __CONTENTS(__DYNAMIC_UI)
	Set_UIEffect_Frame_Zero();
	m_Effect_Id = (int)EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3; // 905

	// Ÿ���� ȿ��
	m_vs_Show_msg.clear();
	m_vs_Show_msg.resize(0);
#endif //__DYNAMIC_UI

	for (int i = 0; i < line_count; i++)
	{
		char test[2] = " ";
		int font_w = g_GetStringWidth(test, gpC_base->m_dialog_msg_pi.hfont);
#if __CONTENTS(__DYNAMIC_UI)
		int row = m_client_rect.w / font_w + 0;
#else
		int row = m_client_rect.w / font_w + 3;
#endif //__DYNAMIC_UI
		char sz_temp[4048];
		char* cur = sz_temp;
		char char_temp;

		// Bounded copy: sz_msg[i] is caller-supplied text (quest and NPC strings
		// come straight from XML), and an unbounded strcpy into this 4048-byte
		// stack buffer would smash the frame. Truncating is the safe failure.
		{
			const std::string& src = sz_msg[i];
			size_t copy_len = src.size();
			if (copy_len >= sizeof(sz_temp))
				copy_len = sizeof(sz_temp) - 1;
			memcpy(sz_temp, src.c_str(), copy_len);
			sz_temp[copy_len] = '\0';
		}

		//wlzzi - 200710
		// - ���ڿ��� ���̸� üũ�Ͽ�, ���� �ٲٴ� ������ �����.. ��Ʈ�� ���� ����ġ ���� ����� �� �� �ִ�.
		// - "  " ���ڿ��� �ȼ� ũ��� .. ��Ʈ���� �ٸ��� �����̴�. �����.. �ѱ���Ʈ������ ����� ����������.. �ٸ� ��Ʈ������ .. 
		// - ����� �� ����. Ư�� ������Ʈ����. ��.,��;;

		// --> ���ڿ��� �ȼ����� üũ�Ͽ�, ���� �ٲٴ� ������ ������ ����. 
		// --> �Ʒ� /**/ �� ���� if ���� ���� ������ ����.
		// -- ��Ʈ�� �̻��ϰ� ���´�..�Ѥ�; ����� ��Ʈ�� ������ ��������..Ȥ�� ����~~ ������ �κ��� .. �۷ι� �������� ������ ����.
#if 0 //__CONTENTS (__INTERNATIONAL_UI || __CHINESE_UI || __JAPAN_UI)			
		if (nLineCheck == LINECHECK_USE_BOTH) {
			char* pStrSrc = strtok(cur, "\n");	//����, "\n"���� ���ڿ���.. �翬��..���õǰ� �־���.
			char* pChar = pStrSrc;

			int StrWidth = g_GetStringWidth(pChar, gpC_base->m_dialog_msg_pi.hfont);
			int CutIndex;
			int destWidth = m_client_rect.w;


			while (StrWidth > destWidth)
			{
				CutIndex = g_GetStringIndexByWidth(pChar, destWidth, gpC_base->m_dialog_msg_pi.hfont);

				//CutIndex ������ ���ڵ��� �߶�.. ����Ʈ�� �ִ´�.
				char* pPushStr = new char[CutIndex + 1];//[CutIndex+2];
				strncpy(pPushStr, pChar, CutIndex);//CutIndex+1);
				pPushStr[CutIndex] = '\0';//pPushStr [CutIndex+1] = '\0';
				m_vs_msg.push_back(pPushStr);
#if __CONTENTS(__DYNAMIC_UI)
				m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
				delete pPushStr;

				//����, CutIndex ������ ���ڿ���.. �ٽ� �˻�
//				pChar = &pStrSrc[CutIndex+1];
				pChar = &pChar[CutIndex];//+1];
				StrWidth = g_GetStringWidth(pChar, gpC_base->m_dialog_msg_pi.hfont);
			}

			if (StrWidth)
			{
				//pChar�� �״�� ..�ִ´�.
				m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
				m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
			}
		}
#else

		// Line Break�� Width Check �Ѵ� �Ѵ�.
		// ���� �ҽ��� ȣȯ�� �ǰ� �ϱ� ���� if������ �б�ó��
		if (nLineCheck == LINECHECK_USE_BOTH)
		{
			char* pChar = strtok(cur, "\n");

			while (pChar != NULL)
			{
				int iLength = strlen(pChar);

				if (row < iLength)
				{

					while (1)
					{
						int check;
						if (g_PossibleStringCut(pChar, row))check = 0; else check = 1;

						char_temp = pChar[row - check];

						pChar[row - check] = '\0';

						int len = strlen(pChar);

						if (len > 0)
						{
							m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
							m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
						}

						pChar += row - check;
						*pChar = char_temp;

						if (len < row - check) break;
						if (*pChar == ' ')pChar++;
					}
				}
				else
				{
					m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
					m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
				}

				pChar = strtok(NULL, "\n");
			}
		}
#endif
		else
		{
			while (1)
			{
				int check;
				if (g_PossibleStringCut(cur, row))check = 0; else check = 1;

				char_temp = cur[row - check];

				if (nLineCheck == LINECHECK_USE_LINE_BREAK)
				{
					char* pChar = strtok(cur, "\n");

					while (pChar != NULL)
					{
						int iLength = strlen(pChar);
						m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
						m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI

						pChar = strtok(NULL, "\n");
					}
					if (!pChar) break;
				}
				else
				{
					cur[row - check] = '\0';
					m_vs_msg.push_back(cur);
#if __CONTENTS(__DYNAMIC_UI)
					m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI					
					if (strlen(cur) < row - check) break;
					cur += row - check;
					*cur = char_temp;
					if (*cur == ' ')cur++;
				}
			}
		}
	}


	/*
	for(int i = 0; i < line_count; i++)
	{
		char test[2] = " ";
		int font_w = g_GetStringWidth(test, gpC_base->m_dialog_msg_pi.hfont);
		int row = m_client_rect.w / font_w+3;

		char sz_temp[4048];
		char *cur = sz_temp;
		char char_temp;

		strcpy(sz_temp, sz_msg[i]);

		while(1)
		{
			int check;
			if(g_PossibleStringCut(cur, row))check = 0; else check = 1;

			char_temp = cur[row - check];

			if(bLineCheck)
			{
				char *pChar = strtok(cur ,"\n") ;

				while( pChar != NULL )
			   {
				  int iLength = strlen(pChar) ;
				  m_vs_msg.push_back( pChar );
				  pChar = strtok( NULL, "\n" );

			   }
			   if(!pChar) break;
			}
			else
			{
				cur[row - check] = '\0';
				m_vs_msg.push_back( cur );

				if(strlen(cur) < row-check) break;
				cur += row-check;
				*cur = char_temp;
				if(*cur == ' ')cur++;
			}
		}
	}
	*/

	if (!m_vs_msg.empty())
		m_line_count = m_vs_msg.size();
	else
		m_line_count = 0;

	int m_message_str_height = g_GetStringHeight(m_vs_msg[0].c_str(), gpC_base->m_dialog_msg_pi.hfont) + MSG_EXTRA_HGAP;

	const int _EXTRA = 30;//2;
	if (h == -1)
	{
		h = m_line_count * m_message_str_height;		// Rect �� ���̴� �޽���â�� ���̷� ���Ѵ�. 
		if (m_menu_count > 0)
			h += 14 + m_menu_rect.h;

		m_client_rect.h = h - DECORATE_GAP * 2 - _EXTRA;

		if (y == -1)
			y = (RESOLUTION_Y - 102 * 2) / 2 - h / 2 + 90;

		m_client_rect.y = y + DECORATE_GAP + _EXTRA;
		m_menu_rect.y = (m_client_rect.y + m_client_rect.h - GetButtonGap()) - m_menu_rect.h;

		int plus = 0;
		int width, height;

		for (int i = 0; i < m_menu_count; i++, plus += (m_menu_str_height - TEXT_EXTRA_HGAP) * height + TEXT_EXTRA_HGAP)
		{
			if (!m_p_menu[i].sz_menu_str.empty())
			{
				height = m_p_menu[i].sz_menu_str.size();
				if (m_p_menu[i].sz_menu_str.size() > 1)width = m_menu_rect.w;
#if __CONTENTS(__DYNAMIC_UI)
				else width = g_GetStringWidth(m_p_menu[i].sz_menu_str[0].c_str(), gpC_base->m_info_pi.hfont);
#else
				else width = g_GetStringWidth(m_p_menu[i].sz_menu_str[0].c_str(), gpC_base->m_dialog_menu_pi.hfont);
#endif //__DYNAMIC_UI
			}
			else
			{
				width = 0;
				height = 0;
			}

			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_menu_rect.x,
				m_menu_rect.y + plus,
				width,
				(m_menu_str_height - TEXT_EXTRA_HGAP) * height,
				m_p_menu[i].exec_id,
				this,
				i)); // m_p_menu�� string�� �����ϱ� ���ؼ� index�� �ִ´�.
		}
	}

	m_msg_rect.x = m_client_rect.x;
	m_msg_rect.w = m_client_rect.w;
	m_msg_rect.y = m_client_rect.y;

	// 2002�� 7�� 23�� ���� �κ�.
	// �޴��� ������ ���� ���̾˷α��� ������ ���� ������ ��´�.
	// �׷��� �������� ������ �� �״�� ���.

	if (m_flag_menu)
	{
		m_msg_rect.h = m_client_rect.h / 2;
	}
	else
	{
		m_msg_rect.h = m_client_rect.h - m_menu_rect.h - GetButtonGap() + iMsgWidth; //; //  + 100;
		if (m_menu_count > 0)
			m_msg_rect.h -= 14;
	}

	// set print line count
	m_print_line_count = m_msg_rect.h / m_message_str_height + 1;

	if (m_pC_menu_scroll_bar == NULL && m_flag_menu)		// �Ʒ��� �޴��ǿ� ��ũ�ѹٰ� ������ �ʾ������
	{
		// ���̸� �÷��ش�.
		m_msg_rect.h = m_client_rect.h - m_menu_rect.h - 28;
		m_print_line_count = (m_msg_rect.h) / m_message_str_height;
	}
	if (mode == SMO_NOFIT)
	{
		m_nofit_mode_msg_y = m_msg_rect.y + m_msg_rect.h / 2 - (m_message_str_height * line_count) / 2; // sort in center
	}
	else if (m_line_count > m_print_line_count)				// ��¹����� �����Ƿ� ScrollBar �� �����Ѵ�.
	{
		// ��ũ�ѹٶ����� �ٽ� �۾��� �ڸ���.
		m_vs_msg.clear();

		/*
		for(int i = 0; i < line_count; i++)
		{
			char test[2] = " ";
			int font_w = g_GetStringWidth(test, gpC_base->m_dialog_msg_pi.hfont);
			int row = m_client_rect.w / font_w;

			char sz_temp[4048];
			char *cur = sz_temp;
			char char_temp;

			strcpy(sz_temp, sz_msg[i]);

			while(1)
			{
				int check;
				if(g_PossibleStringCut(cur, row))check = 0; else check = 1;

				char_temp = cur[row - check];
				cur[row - check] = '\0';
				m_vs_msg.push_back( cur );

				if(strlen(cur) < row-check) break;
				cur += row-check;
				*cur = char_temp;
				if(*cur == ' ')cur++;
			}
		}
		*/



		for (int i = 0; i < line_count; i++)
		{
			char test[2] = " ";
			int font_w = g_GetStringWidth(test, gpC_base->m_dialog_msg_pi.hfont);
			int row = m_client_rect.w / font_w;

			char sz_temp[4048];
			char* cur = sz_temp;
			char char_temp;

			// Bounded copy, same reasoning as the other SetMessage loop above.
			{
				const std::string& src = sz_msg[i];
				size_t copy_len = src.size();
				if (copy_len >= sizeof(sz_temp))
					copy_len = sizeof(sz_temp) - 1;
				memcpy(sz_temp, src.c_str(), copy_len);
				sz_temp[copy_len] = '\0';
			}

			// Line Break�� Width Check �Ѵ� �Ѵ�.
			// ���� �ҽ��� ȣȯ�� �ǰ� �ϱ� ���� if������ �б�ó��
			if (nLineCheck == LINECHECK_USE_BOTH)
			{
				char* pChar = strtok(cur, "\n");

				while (pChar != NULL)
				{
					int iLength = strlen(pChar);

					if (row < iLength)
					{

						while (1)
						{
							int check;
							if (g_PossibleStringCut(pChar, row))check = 0; else check = 1;

							char_temp = pChar[row - check];

							pChar[row - check] = '\0';

							int len = strlen(pChar);

							if (len > 0)
							{
								m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
								m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
							}

							pChar += row - check;
							*pChar = char_temp;

							if (len < row - check) break;
							if (*pChar == ' ')pChar++;
						}
					}
					else
					{
						m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
						m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI
					}

					pChar = strtok(NULL, "\n");
				}
			}
			else
			{
				while (1)
				{
					int check;
					if (g_PossibleStringCut(cur, row))check = 0; else check = 1;

					char_temp = cur[row - check];

					if (nLineCheck == LINECHECK_USE_LINE_BREAK)
					{
						char* pChar = strtok(cur, "\n");

						while (pChar != NULL)
						{
							int iLength = strlen(pChar);
							m_vs_msg.push_back(pChar);
#if __CONTENTS(__DYNAMIC_UI)
							m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI

							pChar = strtok(NULL, "\n");

						}
						if (!pChar) break;
					}
					else
					{
						cur[row - check] = '\0';
						m_vs_msg.push_back(cur);
#if __CONTENTS(__DYNAMIC_UI)
						m_vs_Show_msg.push_back(""); // Ÿ���� ȿ��
#endif //__DYNAMIC_UI

						if (strlen(cur) < row - check) break;
						cur += row - check;
						*cur = char_temp;
						if (*cur == ' ')cur++;
					}
				}
			}
		}






		m_line_count = m_vs_msg.size();

		if (m_pC_msg_scroll_bar)
		{
			delete m_pC_msg_scroll_bar;
			m_pC_msg_scroll_bar = NULL;
		}
		m_pC_msg_scroll_bar = new C_VS_UI_SCROLL_BAR(m_line_count - m_print_line_count + 1,
			Rect(m_msg_rect.w, m_msg_rect.y - m_client_rect.y + 10, -1, m_msg_rect.h - 30));
	}
	else
		if (m_flag_menu)				// �޴��� ���� ���
		{
			// ������ ���� ������ ��ũ�ѹٰ� ���� ��� �޴�rect �� ���� �����ش�.
			if (m_pC_menu_scroll_bar != NULL)
			{
				// linelen �� ������ �����ؼ� �޽����� h ũ���̴�.
				// m_client.h/2-linelen �� �󿵿��̸�, �޴��� ���� �ø� �� �ִ� �����̴�.
				int linelen = (m_line_count + 1) * m_message_str_height;

				m_msg_rect.y = m_client_rect.y;
				m_msg_rect.h = linelen;

				m_menu_y_size = m_client_rect.h / 2 - linelen;
				m_menu_rect.y -= m_menu_y_size;
				m_menu_rect.h += m_menu_y_size;

				delete m_pC_menu_scroll_bar;
				m_pC_menu_scroll_bar = NULL;

				int len_menu = m_button_y_list[m_menu_count] - m_temp_menu_rect_y;

				// ���̸� �ø�������, ��ư���� ��� ����� �� ����������, â�� �°� ���ġ�ϰ�,
				// ��ũ���� �������� �ʴ´�. 
				if (len_menu < m_menu_rect.h)
				{
					len_menu = m_menu_rect.h - len_menu;
					m_menu_y_size -= len_menu;
				}
				else
				{
					m_pC_menu_scroll_bar = new C_VS_UI_SCROLL_BAR(len_menu - m_menu_rect.h,
						Rect(m_menu_rect.w + 20, 14, -1, m_menu_rect.h - 20));
				}
			}
		}
}

//-----------------------------------------------------------------------------
// SetMenu
//
// - Client rect���� Menu rect������ Ȯ������ ���ϸ� ��µ��� ���� ���̴�.
// - �� �� �̻� ������ �� ����.
// - menu_only�� true�̸� dialog center�� ���߰� false�̸� message ������ ����
//   rect �ϴܿ� ��ġ��Ų��.
// 
// 2002�� 7�� 23�� ��������				-by sonee
// - Menu Rect ������ Ȯ������ ���Ͽ������ �ڵ� ��ũ�ѹٰ� ������, �޽��� rect
//  �� ���Ͽ� �ڵ����� ������ Ȯ���Ѵ�.
//-----------------------------------------------------------------------------
void C_VS_UI_DIALOG::SetMenu(const DIALOG_MENU* p_dialog_menu, UINT menu_count, bool menu_only)
{
	BOOL fMakeScrollBar = FALSE;
	assert(p_dialog_menu != NULL);
	assert(menu_count > 0);

	int i;

	if (p_dialog_menu == NULL || menu_count == 0)
		return;
	if (m_p_menu != NULL)
		return;

	m_flag_menu = TRUE;
	// set Menu list
	m_menu_count = menu_count;

	if (m_p_menu != NULL)
		delete[] m_p_menu;

	m_p_menu = new DIALOG_MENU_INNER[m_menu_count];

	// Menu ���� �Ѿ�°� �ڸ���.
	for (i = 0; i < m_menu_count; i++)
	{
		m_p_menu[i].exec_id = p_dialog_menu[i].exec_id;

		char test[2] = " ";
#if __CONTENTS(__DYNAMIC_UI)
		int font_w = g_GetStringWidth(test, gpC_base->m_info_pi.hfont);
#else
		int font_w = g_GetStringWidth(test, gpC_base->m_dialog_menu_pi.hfont);
#endif //__DYNAMIC_UI

		if (0 == font_w) continue;
		assert(font_w != 0);

#if __CONTENTS(__DYNAMIC_UI)
		int row = (m_client_rect.w / font_w) - 16;
#else
		int row = (m_client_rect.w / font_w) - 2;
#endif //__DYNAMIC_UI

		assert(row > 0);

		char sz_temp[2048];
		char* cur = sz_temp;
		char char_temp;

		strcpy(sz_temp, p_dialog_menu[i].sz_menu_str.c_str());

		while (*cur != '\0')
		{
			int check;

			if (g_PossibleStringCut(cur, row))
				check = 0;
			else
				check = 1;

			int cutLen = row - check;
			assert(cutLen > 0 && cutLen < 2048);

			char* pCut = cur + cutLen;

			char_temp = *pCut;
			*pCut = '\0';
			m_p_menu[i].sz_menu_str.push_back(cur);

			*pCut = char_temp;

			int size = strlen(cur) - 1;
			if (strlen(cur) <= cutLen) break;
			cur += cutLen;

			while (*cur == ' ') cur++;
		}
	}

	//
	// ! SetMessage()�� ���ؼ� Message�� ���� ������ �� ������, �װ��� �������� �ʴ´�.
	// �׷��ϱ� VS_UI_Dialog class�� �ùٸ� �����, SetMenu()�� ���� ���� �� SetMessage()��
	// ���ִ� ���̴�. Menu rect�� ������ Client rect�� �ϴܿ��� ��� Menu�� ��ġ�� �� �ִ�
	// rect�� �����ȴ�. �׷��� ���� Client rect�� Message �������� �Ǵ� ���̴�.
	//
	//	m_menu_str_height;

	if (!m_p_menu[0].sz_menu_str.empty())
#if __CONTENTS(__DYNAMIC_UI)
		m_menu_str_height = g_GetStringHeight(m_p_menu[0].sz_menu_str[0].c_str(), gpC_base->m_info_pi.hfont) + 2 + TEXT_EXTRA_HGAP;
#else
		m_menu_str_height = g_GetStringHeight(m_p_menu[0].sz_menu_str[0].c_str(), gpC_base->m_dialog_menu_pi.hfont) + 2 + TEXT_EXTRA_HGAP;
#endif //__DYNAMIC_UI

	m_menu_rect.x = m_client_rect.x + 20;
	m_menu_rect.w = m_client_rect.w - 20;
	m_menu_rect.h = 0;
	for (i = 0; i < m_menu_count; i++)
	{
		m_menu_rect.h += (m_menu_str_height - TEXT_EXTRA_HGAP) * m_p_menu[i].sz_menu_str.size() + TEXT_EXTRA_HGAP;
		//m_menu_str_height*m_p_menu[i].sz_menu_str.size();

	}

	if (menu_only)
		m_menu_rect.y = m_client_rect.y + (m_client_rect.h - GetButtonGap()) / 2 - m_menu_rect.h / 2;
	else
	{
		if (h != -1)
			m_menu_rect.y = (m_client_rect.y + m_client_rect.h) - m_menu_rect.h;
	}

	if (m_menu_rect.y < m_client_rect.y + m_client_rect.h / 2 && h != -1)
	{
		m_menu_rect.y = m_client_rect.y + m_client_rect.h / 2;
		m_menu_rect.h = m_client_rect.h / 2;

		if (m_pC_menu_scroll_bar)
			delete m_pC_menu_scroll_bar;
		m_pC_menu_scroll_bar = NULL;
		fMakeScrollBar = TRUE;
	}

	// Create Menu button
	if (h != -1)
	{
		int plus = 0;
		int width, height;

		if (m_button_y_list != NULL) delete[] m_button_y_list;
		m_button_y_list = new int[m_menu_count + 1];

		for (i = 0; i < m_menu_count; i++, plus += (m_menu_str_height - TEXT_EXTRA_HGAP) * height + TEXT_EXTRA_HGAP)
		{
			if (!m_p_menu[i].sz_menu_str.empty())
			{
				height = m_p_menu[i].sz_menu_str.size();
				if (m_p_menu[i].sz_menu_str.size() > 1)width = m_menu_rect.w;
#if __CONTENTS(__DYNAMIC_UI)
				else width = g_GetStringWidth(m_p_menu[i].sz_menu_str[0].c_str(), gpC_base->m_info_pi.hfont);
#else
				else width = g_GetStringWidth(m_p_menu[i].sz_menu_str[0].c_str(), gpC_base->m_dialog_menu_pi.hfont);
#endif //__DYNAMIC_UI
			}
			else
			{
				width = 0;
				height = 0;
			}
			m_temp_menu_rect_y = m_menu_rect.y;
			m_button_y_list[i] = m_menu_rect.y + plus;
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_menu_rect.x,
				m_menu_rect.y + plus,
				width,
				(m_menu_str_height - TEXT_EXTRA_HGAP) * height,
				m_p_menu[i].exec_id,
				this,
				i)); // m_p_menu�� string�� �����ϱ� ���ؼ� index�� �ִ´�. �̰��� imageindex �� ����ȴ�.			
		}
		m_button_y_list[i] = m_menu_rect.y + plus;

		if (fMakeScrollBar)
		{
			int linelen = m_button_y_list[m_menu_count] - m_temp_menu_rect_y - m_menu_rect.h;
			m_pC_menu_scroll_bar = new C_VS_UI_SCROLL_BAR(linelen, Rect(m_menu_rect.w, 14, -1, m_menu_rect.h - 20));
		}
	}
}


int C_VS_UI_DIALOG::GetScrollPos()
{
	int i, NowPos, now_len;

	if (m_pC_menu_scroll_bar)
		NowPos = m_pC_menu_scroll_bar->GetScrollPos();
	else
		return 0;

	for (i = 0; i < m_menu_count; i++)
	{
		now_len = m_button_y_list[i] - m_temp_menu_rect_y;
		// |-----+-----|
		//    +- �̰�� 
		if (NowPos >= now_len && NowPos < now_len + (m_button_y_list[i + 1] - m_button_y_list[i]) / 2)
		{
			m_pC_menu_scroll_bar->SetScrollPos(m_button_y_list[i] - m_temp_menu_rect_y);
			return i;
		}
		else
			if (NowPos >= now_len + (m_button_y_list[i + 1] - m_button_y_list[i]) / 2 && NowPos < m_button_y_list[i + 1] - m_temp_menu_rect_y)
			{
				m_pC_menu_scroll_bar->SetScrollPos(m_button_y_list[i + 1] - m_temp_menu_rect_y);
				return i + 1;
			}
	}

	return 0;
}

// --------------------------------------------------------------------------------------
//  C_VS_UI_DIALOG::ProcessMenuScrollBar();
//  
//  Pixel ���� ��ũ���� �ϱ� ������, ������ ��ũ�ѹٸ� ����ϸ鼭 ������ ����.

#if __CONTENTS(__BLITZ_COUPON_EVENT)
void C_VS_UI_DIALOG::ProcessMenuScrollBar(int _digit)
#else
void C_VS_UI_DIALOG::ProcessMenuScrollBar()
#endif //__BLITZ_COUPON_EVENT
{
	int NowPos, i, MaxPos = 0, half;
	if (m_menu_count > 0 && m_button_y_list != NULL)
	{
		MaxPos = m_button_y_list[m_menu_count] - m_temp_menu_rect_y - m_menu_rect.h;
	}

	//	BYTE Remain;

	if (m_pC_menu_scroll_bar == NULL) return;
	NowPos = m_pC_menu_scroll_bar->GetScrollPos();
	if (NowPos == 0) return;


	for (i = 0; i <= m_menu_count; i++)
	{
		if (i < m_menu_count)
		{
			half = (m_button_y_list[i + 1] - m_button_y_list[i]) >> 1;

			// ��ũ���� �Ʒ��� �ϴ°��
			if (NowPos > m_button_y_list[i] - m_temp_menu_rect_y && NowPos < m_button_y_list[i + 1] - m_temp_menu_rect_y - half)
			{
				NowPos = m_button_y_list[i + 1] - m_temp_menu_rect_y;

				// �� ȭ�鿡 ����� �Ǵ°�� PosMax �� �ٽ� �������ش�.
				if (!(m_button_y_list[m_menu_count] - m_temp_menu_rect_y < NowPos + m_menu_rect.h))
					m_pC_menu_scroll_bar->SetScrollPos(NowPos);
				else
					m_pC_menu_scroll_bar->SetPosMax(NowPos + 1);

#if __CONTENTS(__BLITZ_COUPON_EVENT)
				if (_digit == -120)
#endif //__BLITZ_COUPON_EVENT
					m_pC_menu_scroll_bar->SetScrollPos(NowPos);
				break;
			}
		}
		if (i > 0)
		{
			half = (m_button_y_list[i] - m_button_y_list[i - 1]) >> 1;
			// ��ũ���� ���� �ϴ� ���
			if (NowPos<m_button_y_list[i] - m_temp_menu_rect_y && NowPos>m_button_y_list[i - 1] - m_temp_menu_rect_y + half)
			{
				NowPos = m_button_y_list[i - 1] - m_temp_menu_rect_y;

				if (!(m_button_y_list[m_menu_count] - m_temp_menu_rect_y < NowPos + m_menu_rect.h))
				{
#if __CONTENTS(__BLITZ_COUPON_EVENT)
					if (_digit == 120)
#endif //__BLITZ_COUPON_EVENT
						m_pC_menu_scroll_bar->SetScrollPos(NowPos);
				}
				break;
			}
		}
	}
}
