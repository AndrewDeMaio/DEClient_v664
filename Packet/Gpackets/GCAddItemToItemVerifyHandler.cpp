//--------------------------------------------------------------------------------
//
// Filename    : GCAddItemToItemVerifyHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------
#include "GPacket_PCH.h"
// include files
#include "GCAddItemToItemVerify.h"
#include "ClientDef.h"
#include "TempInformation.h"
#include "MInventory.h"
#include "UIDialog.h"
#include "MGameStringTable.h"
#include "ClientFunction.h"
#include "SkillDef.h"
#include "MinTR.H"
#include "UIFunction.h"

#ifdef __GAME_CLIENT__
#include "ClientPlayer.h"
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddItemToItemVerifyHandler::execute(GCAddItemToItemVerify* pPacket, Player* pPlayer)
{
	__BEGIN_TRY
		__BEGIN_DEBUG

#ifdef __GAME_CLIENT__
	MItem* pInventoryItem = NULL;

	MItem* pItem[2] = { NULL, NULL };

	if (g_pTempInformation->GetMode() == TempInformation::MODE_ITEM_TO_ITEM)
	{
		pInventoryItem = g_pInventory->GetItem(g_pTempInformation->Value1, g_pTempInformation->Value2);
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
	}
	else if (g_pTempInformation->GetMode() == TempInformation::MODE_ITEM_MIXING)
	{
		pItem[0] = g_pInventory->GetItem(g_pTempInformation->Value1, g_pTempInformation->Value2);
		pItem[1] = g_pInventory->GetItem(g_pTempInformation->Value3, g_pTempInformation->Value4);

		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
	}
	else
		DEBUG_ADD("[ERROR] TempInformationMode");


	switch (pPacket->getCode())
	{
	case ADD_ITEM_TO_ITEM_VERIFY_ERROR:
		// ui error dialog
		UI_PopupMessage(STRING_ERROR_ETC_ERROR);
		UI_UnlockItem();
		g_pPlayer->ClearItemCheckBuffer();
		break;

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE:
		// ui error dialog
		UI_PopupMessage(STRING_MESSAGE_ITEM_TO_ITEM_IMPOSIBLE);
		UI_UnlockItem();
		g_pPlayer->ClearItemCheckBuffer();
		break;

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH:
		//----------------------------------------------------
		// ��� ��� �õ� ����
		//----------------------------------------------------
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_REMOVE_ITEM,
			0
		);
		// ����??
		PlaySound(SOUND_XMAS_STAR);
		UI_DropItem();
		break;

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE:
	{
		DWORD OptionType = pPacket->getParameter();

		//----------------------------------------------------
		// ��� ��� �õ� ����
		//----------------------------------------------------
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_NULL,
			0, OptionType
		);

		// ����??
		PlaySound(SOUND_XMAS_STAR);
		UI_DropItem();
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK:
	{
		DWORD OptionType = pPacket->getParameter();
		//----------------------------------------------------
		// ��� ��� �õ� ����
		//----------------------------------------------------

		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_PLUS,
			0, OptionType
		);

		//				pInventoryItem->SetItemOption(OptionType);
		UI_DropItem();

	}
	break;
#if __CONTENTS(__2008_FIRST_CHARGE_ITEM)
	case ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK:				//ũ����Ż ������
	{
		DWORD OptionType = pPacket->getParameter();

		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_PLUS,
			0, OptionType
		);
		UI_DropItem();
		break;
	}
#endif//	__2008_FIRST_CHARGE_ITEM

#if __CONTENTS(__TUNING_ITEM)
	case ADD_ITEM_TO_ITEM_VERIFY_TUNING_OK:
	{
		DWORD tType = pPacket->getParameter();

		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_PLUS,
			0, tType
		);
		UI_DropItem();
		break;
	}
#endif	//__TUNING_ITEM

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM:
		if (g_pPlayer->IsSlayer())
			UI_PopupMessage(STRING_MESSAGE_ITEM_TO_ITEM_FAIL_NO_PREMIUM_SLAYER);
		else
			UI_PopupMessage(STRING_MESSAGE_ITEM_TO_ITEM_FAIL_NO_PREMIUM_VAMPIRE);
		UI_UnlockItem();
		g_pPlayer->ClearItemCheckBuffer();
		break;
	case ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK:				// ����ȯ ����
	{
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_TRANS_ITEM_OK,
			0, 0);
		UI_DropItem();
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE:		// ����ȯ ����
	{
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK:
	{
		if (pItem[0] == NULL || pItem[1] == NULL)
			return;

		UI_OkMixingForge(pPacket->getParameter(), pItem[0], pItem[1]);

		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		g_pTempInformation->Value1 = 0;
		g_pTempInformation->Value2 = 0;
		g_pTempInformation->Value3 = 0;
		g_pTempInformation->Value4 = 0;
		g_pTempInformation->pValue = NULL;
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		if (pInventoryItem == NULL)
			return;

		UI_OkRemoveOption(pPacket->getParameter(), pInventoryItem);
		UI_DropItem();
		g_pPlayer->ClearItemCheckBuffer();
		break;
	case ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAILED_SAME_OPTION_GROUP:
		UI_PopupMessage(STRING_MESSAGE_MIXING_FORGE_FAILED_SAME_OPTION_GROUP);
		break;

	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
	{
		MItem* pItem = UI_GetMouseItem();
		if (NULL != pItem)
		{
			if (pItem->GetItemClass() == ITEM_CLASS_EVENT_STAR &&
				(pItem->GetItemType() == 22 || pItem->GetItemType() == 48
					|| pItem->GetItemType() == 57 || (pItem->GetItemType() >= 63 && pItem->GetItemType() <= 69)
					)) // ���ο� ��� & ���� ��þƮ ������
			{
				g_pPlayer->ClearItemCheckBuffer();
				UI_PopupMessage(STRING_MESSAGE_ENCHANT_FAIL);

				//						AddNewInventoryEffect( pInventoryItem->GetID() ,
				//							MAGIC_ENCHANT_OPTION_NULL,
				//							0, pInventoryItem->GetGrade() );

			}
			else
			{
				AddNewInventoryEffect(pInventoryItem->GetID(),
					MAGIC_ENCHANT_OPTION_NULL,
					0, 0);
			}
			UI_DropItem();
		}
		//				AddNewInventoryEffect( pInventoryItem->GetID() ,
		//					MAGIC_ENCHANT_OPTION_NULL,
		//					0, 0 );
		//				UI_DropItem();
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
	{
		if (pInventoryItem == NULL)
			return;

		DWORD OptionType = pPacket->getParameter();
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_PLUS,
			0, OptionType
		);

		//			pInventoryItem->SetCurrentDurability(pPacket->getParameter());
		UI_DropItem();
		//			g_pPlayer->ClearItemCheckBuffer();
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_CLEAR_OPTION_OK:
	{
		DWORD OptionType = pPacket->getParameter();
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_NULL,
			0, OptionType
		);
		PlaySound(SOUND_XMAS_STAR);
		//				pInventoryItem->RemoveItemOption(g_pTempInformation->Value3);

		UI_DropItem();
		UI_PopupMessage(STRING_MESSAGE_SUCCESS_CHANGE);
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
	{

		DWORD ItemGrade = pPacket->getParameter();

		pInventoryItem->SetGrade(ItemGrade);
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_PLUS,
			0, ItemGrade
		);

		UI_DropItem();
		UI_PopupMessage(STRING_MESSAGE_SUCCESS_CHANGE);
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_PET_MAGIC_ENCHANT_OK:
	{
		DWORD MagicRemainSec = pPacket->getParameter();

		UI_RemoveEffectStatus(EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER);
		UI_AddEffectStatus(EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER, MagicRemainSec << 4);

		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_NULL,
			0, 0
		);

		UI_DropItem();

		UI_PopupMessage(STRING_MESSAGE_SUCCESS_CHANGE);
	}
	break;
#if __CONTENTS(__EXPERT_PET_CHANGER)
	case ADD_ITEM_TO_ITEM_VERIFY_PET_EXPERT_ENCHANT_OK:
	{
		DWORD ExpertRemainSec = pPacket->getParameter();


		UI_RemoveEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER);
		UI_AddEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER, ExpertRemainSec << 4);

		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_OPTION_NULL,
			0, 0
		);

		UI_DropItem();

		UI_PopupMessage(STRING_MESSAGE_SUCCESS_CHANGE);
	}
	break;
#endif //__EXPERT_PET_CHANGER
	case ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_LEVEL_FAIL:
	{
		g_pPlayer->ClearItemCheckBuffer();

		UI_PopupMessage(UI_STRING_MESSAGE_PET_ENCHANT_LEVEL_FAIL);
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_DUPLICATE_FAIL:
	{
		g_pPlayer->ClearItemCheckBuffer();

		UI_PopupMessage(UI_STRING_MESSAGE_ENCHANT_DUPLICATE_FAIL);
	}
	break;

	case ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_OK_MESSAGE:
	{
		UI_DropItem();
		g_pPlayer->ClearItemCheckBuffer();

		UI_PopupMessage(UI_STRING_MESSAGE_PET_ENCHANT_OK);
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL:
	{
		BYTE itemGrade = pPacket->getGrade();
		if (itemGrade && itemGrade != 99)
		{
			AddNewInventoryEffect(pInventoryItem->GetID(),
				MAGIC_ENCHANT_OPTION_PLUS,
				0, itemGrade);
			UI_PopupMessage(UI_STRING_MESSAGE_THIRD_ENCHANT_DOWN_GRADE);
		}
		else if (itemGrade == 99)
		{
			UI_PopupMessage(UI_STRING_MESSAGE_THIRD_ENCHANT_2_OVERLEVEL);
			g_pPlayer->ClearItemCheckBuffer();
			break;
		}
		else
		{
			list<OptionType_t>* thirdOptionType = &pPacket->getThirdOptionType();
			AddNewInventoryEffect(pInventoryItem->GetID(),
				MAGIC_ENCHANT_THIRD_OPTION_NULL,
				0, reinterpret_cast<DWORD> (thirdOptionType));
			UI_PopupMessage(UI_STRING_MESSAGE_THIRD_ENCHANT_FAIL);
			g_pPlayer->ClearItemCheckBuffer();
		}
		UI_DropItem();
	}
	break;


	case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK:
	{
		tag_ThirdOptionData ThirdOptionData;

		ThirdOptionData.thirdOptionList = &pPacket->getThirdOptionType();
		ThirdOptionData.thirdOptionType = pPacket->getThirdEnchantType();

		//----------------------------------------------------
		// ��� ��� �õ� ����
		//----------------------------------------------------
		AddNewInventoryEffect(pInventoryItem->GetID(),
			MAGIC_ENCHANT_THIRD_OPTION_PLUS,
			0, reinterpret_cast<DWORD> (&ThirdOptionData)
		);
		g_pPlayer->ClearItemCheckBuffer();
		UI_PopupMessage(UI_STRING_MESSAGE_THIRD_ENCHANT_OK);

		UI_DropItem();
	}
	break;
#if __CONTENTS(__ENCHANT_REQUIRE_LEVE)
	case ADD_ITEM_TO_ITEM_VERIFY_NEED_LEVEL_FAIL:
	{
		UI_PopupMessage(STRING_MESSAGE_ITEM_TO_ITEM_IMPOSIBLE);
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
#endif
	case ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_OK:
	{
		if (pItem[0] == NULL || pItem[1] == NULL)
			return;
		UI_OKPetMixingForge(pItem[1]);

		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		g_pTempInformation->Value1 = 0;
		g_pTempInformation->Value2 = 0;
		g_pTempInformation->Value3 = 0;
		g_pTempInformation->Value4 = 0;
		g_pTempInformation->pValue = NULL;
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_FAIL:
	{
		UI_ClosePetMixingForge();
		UI_PopupMessage(UI_STRING_MESSAGE_DESC_PETMIXING_FAIL);
	}
	break;
#if __CONTENTS(__TREASURE_BOX)
	case 	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_OK:// ���� ���� ����
	{
		g_pPlayer->ClearItemCheckBuffer();
		UI_DropItem();
	}
	break;
	case 	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_NOT_ENOUGH_SPACE:// �κ��丮 ������ ������ 
	{
		UI_PopupMessage(UI_STRING_MESSAGE_OPEN_CASE_FAIL_NOT_ENOUGH_SPACE);
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
	case 	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_NO_ITEM:// ���ڿ� �������� ���� 
	{
		UI_PopupMessage(UI_STRING_MESSAGE_OPEN_CASE_FAIL_NO_ITEM);
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
	case 	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_INCORRECT_KEY:// ���ڿ� ���� �ʴ� ����
	{
		UI_PopupMessage(UI_STRING_MESSAGE_OPEN_CASE_FAIL_INCORRECT_KEY);
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;

#endif //__TREASURE_BOX
#if __CONTENTS(__IMI_LOW_LEVEL_ITEM)
	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DOWN_GRADE:
	{
		DWORD ItemGrade = pPacket->getParameter();
		pInventoryItem->SetGrade(ItemGrade);
		UI_PopupMessage(UI_STRING_MESSAGE_THIRD_ENCHANT_DOWN_GRADE);
		UI_DropItem();
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
#endif //__IMI_LOW_LEVEL_ITEM
#if __CONTENTS(__IMI_NEW_ENCHANT_ITEM)
	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DELETE_DEFENSE:
	{
		// �������� ������� ���� ��� �Ǿ����ϴ�.
		UI_PopupMessage(UI_STRING_MESSAGE_ENCHANT_DELETE_DEFENSE);
		UI_DropItem();
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
	case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_THIRDOPTION_PENALTY_DEFENSE:
	{
		// �������� �޼��� �ɼ��� ��� �Ǵ� ���� ��� �Ǿ����ϴ�.
		UI_PopupMessage(UI_STRING_MESSAGE_ENCHANT_THIRDOPTION_PENALTY_DEFENSE);
		UI_DropItem();
		g_pPlayer->ClearItemCheckBuffer();
	}
	break;
#endif //__IMI_NEW_ENCHANT_ITEM
#if __CONTENTS(__IMI_MIXNGFORGE)
	case ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAIL:
	{
		// �������� �޼��� �ɼ��� ��� �Ǵ� ���� ��� �Ǿ����ϴ�.
		UI_PopupMessage(UI_STRING_MESSAGE_MIXING_FORGE_FAIL);
		UI_CloseMixingForge();
	}
	break;
#endif //__IMI_MIXNGFORGE
	}


#endif

	__END_DEBUG
		__END_CATCH
}
