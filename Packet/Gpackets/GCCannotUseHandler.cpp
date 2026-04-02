//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCannotUseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCCannotUse.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"
#include "MGameStringTable.h"
#include "MItemFinder.h"
#include "UIDialog.h"
#include "TempInformation.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCannotUseHandler::execute ( GCCannotUse * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	
	if(g_pPlayer->GetWaitVerify() == MPlayer::WAIT_VERIFY_LOVE_CHAIN)
	{
		TYPE_OBJECTID packetObjectID = pPacket->getObjectID();
		ITEM_CLASS		ItemClass;

		switch(g_pPlayer->GetRace() )
		{
		case RACE_SLAYER :
			ItemClass = ITEM_CLASS_COUPLE_RING;
			break;
		case RACE_VAMPIRE :
			ItemClass = ITEM_CLASS_VAMPIRE_COUPLE_RING;
			break;
		case RACE_OUSTERS :
			ItemClass = ITEM_CLASS_OUSTERS_HARMONIC_PENDENT; // ;
			break;
		default :
			ItemClass = ITEM_CLASS_COUPLE_RING;
			break;
		}

		MPlayerGear* pGear = g_pPlayer->GetGear();
		MItemClassFinder itemFinder( ItemClass );

//		const MItem *pItem = pGear->GetItem(packetObjectID);
		MItem *pItem = pGear->FindItem( itemFinder );
		if(pItem != NULL && pItem->GetID() == packetObjectID)
		{
			g_pPlayer->ClearItemCheckBuffer();			
			g_pPlayer->SetWaitVerifyNULL();
			g_pPlayer->RemoveEffectStatus( EFFECTSTATUS_LOVE_CHAIN );

//			g_pSystemMessage->AddFormat((*g_pGameStringTable)[UI_STRING_MESSAGE_CANNOT_TRACE].GetString(), (*g_pGameStringTable)[STRING_MESSAGE_COUPLE].GetString());
			if(g_pPlayer->GetRace() == RACE_OUSTERS)
				g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_CAN_NOT_FIND].GetString());
			else
				g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_CAN_NOT_FIND].GetString());
		}
		return;
	}
	//----------------------------------------------------
	// ������������ Item�� �о�´�.
	//----------------------------------------------------
	MItem* pItem = g_pPlayer->GetItemCheckBuffer();

	if (pItem!=NULL)
	{
		MPlayer::ITEM_CHECK_BUFFER status =	g_pPlayer->GetItemCheckBufferStatus();

		//----------------------------------------------------
		// Item ����ϴ°� �����޴� ��찡 �´ٸ�..
		//----------------------------------------------------
		if( status == MPlayer::ITEM_CHECK_BUFFER_ITEM_TO_ITEM )
		{			
			g_pPlayer->ClearItemCheckBuffer();
			g_pTempInformation->SetMode( TempInformation::MODE_NULL );
			
			if( pItem->GetItemClass() != ITEM_CLASS_CODE_SHEET )
				UI_PopupMessage( STRING_MESSAGE_FAILED_REMOVE_OPTION );
		} else
		if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY)
		{
			MItem *pItem = g_pPlayer->GetItemCheckBuffer();
			if(pItem != NULL && pItem->GetItemClass() == ITEM_CLASS_EVENT_TREE &&
				pItem->GetItemType() >= 26 && pItem->GetItemType() <= 28)
				UI_PopupMessage( STRING_MESSAGE_USE_GUILD_MEMBER_ONLY );

			if(pItem->GetItemClass() == ITEM_CLASS_MIXING_ITEM)
			{
				UI_CloseMixingForge();
				UI_PopupMessage(UI_STRING_MESSAGE_FAIL_MERGE_ITEM);				
			}

			if(pItem->GetItemClass() == ITEM_CLASS_DYE_POTION && pItem->GetItemType() == 48)
			{
				// 1:�� �԰��ִ�, 2:Ŀ���̶� �ȵȴ�. , 3:�̻��ѿ���
				switch( pPacket->getObjectID() )
				{
				case 1 :
					UI_PopupMessage(STRING_MESSAGE_CANNOT_CHANGE_SEX_BY_WEAR);
					break;
				case 2 :
					UI_PopupMessage(STRING_MESSAGE_CANNOT_CHANGE_SEX_BY_COUPLE);
					break;
				default :
					UI_PopupMessage(STRING_ERROR_ETC_ERROR);
					break;
				}
			}
			else if(pItem->GetItemClass() == ITEM_CLASS_DYE_POTION && pItem->GetItemType() >= 58 && pItem->GetItemType() <= 63)
			{
				UI_PopupMessage(UI_STRING_MESSAGE_ADD_COLOR);
			}
			
			else if(pItem->GetItemClass() == ITEM_CLASS_DYE_POTION && pItem->GetItemType() >= 65 && pItem->GetItemType() <= 67)
			{
				UI_PopupMessage(UI_STRING_MESSAGE_CANNOT_USE);
			}

			// Item Check Buffer�� �����.
			g_pPlayer->ClearItemCheckBuffer();			
		}
		else if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT)
		{
			// Item Check Buffer�� �����.
			g_pPlayer->ClearItemCheckBuffer();

			//----------------------------------------------------
			// ��Ʈ �� ���ֵ��� �Ѱ�.. ���
			//----------------------------------------------------
			UI_UnlockGear();
		}
		//----------------------------------------------------
		// �ٸ� ����??
		//----------------------------------------------------
		else if(status == MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GEAR)
		{
			g_pPlayer->ClearItemCheckBuffer();			

			// UNDONE : OK���� WAIT�ϴ� ��쿡�� ������� �ȵ�� �´�.
			// OK���� �̹� CHECK_BUFFER�� ������ ������� ������ ���� pItem != NULL�� �ɸ��� �ʴ´�
			// �̺κ��� WAIT_VERIFY_LOVE_CHAIN�� üũ�ؼ� ObjectID�� ���ѵ� �Ʒ��� ������ �����Ѵ�
			if( pItem->GetItemClass() == ITEM_CLASS_COUPLE_RING ||
				pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COUPLE_RING ||
				pItem->GetItemClass() == ITEM_CLASS_OUSTERS_HARMONIC_PENDENT	
				)
			{
				if(g_pPlayer->GetRace() == RACE_OUSTERS)
					g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_CAN_NOT_FIND].GetString());
				else
					g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_CAN_NOT_FIND].GetString());


//				g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_CAN_NOT_FIND].GetString());
//				g_pPlayer->SetWaitVerifyNULL();
//				g_pPlayer->RemoveEffectStatus( EFFECTSTATUS_LOVE_CHAIN );
			}
		}
		// 2004, 9, 13, sobeit add start - ����Ʈ �κ� ������ ��� ����
		else if(status == MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GQUEST_INVENTORY)
		{
			g_pPlayer->ClearItemCheckBuffer();
		}
		// 2004, 9, 13, sobeit add end - ����Ʈ �κ� ������ ��� ����
		// 2004, 12, 13, sobeit add start - ������ ���Ƕ� ���� ������..�κ��� �� �� �־����� ���� ��Ǯ�Ⱦ���...-_-
		else if(status == MPlayer::ITEM_CHECK_BUFFER_DROP_TO_CREATURE)
		{
			g_pPlayer->ClearItemCheckBuffer();
		}
		// 2004, 12, 13, sobeit add end
		else
		{
			DEBUG_ADD_FORMAT("[Error] ItemCheck Buffer is not Use Status: status=%d", (int)status);
		}

	}
	//----------------------------------------------------
	// item�� ���� ���.. - -;;
	//----------------------------------------------------
	else
	{
		DEBUG_ADD("[Error] No Item in CheckBuffer");
	}
	
#endif

	__END_CATCH
}
