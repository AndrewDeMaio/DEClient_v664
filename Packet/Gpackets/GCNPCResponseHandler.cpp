//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCResponseHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files

#include "GPacket_PCH.h"
#include "GCNPCResponse.h"
#include "ClientDef.h"
#include "MStorage.h"
#include "MInventory.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"
#include "MMoneyManager.h"
#include "MGameStringTable.h"
#include "TempInformation.h"
#include "MSkillManager.h"
#include "UIDialog.h"
#include "SoundDef.h"
#include "MItemFinder.h"
#include "UserInformation.h"
#include "MSkillManager.h"
#include "MEventManager.h"
#include "UIFunction.h"
#include "Cpackets/CGDonationMoney.h"
#include "MPriceManager.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CGConnect.h"
	#include "Cpackets/CGStashList.h"
	#include "VS_UI.h"
	#include "VS_UI_filepath.h"

#endif


void GCNPCResponseHandler::execute ( GCNPCResponse * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	char sz_temp[1024];
	//------------------------------------------------------
	// ����
	//------------------------------------------------------
	if ( g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK )
	{
		g_pPlayer->SetWaitVerifyNULL();

		DEBUG_ADD("[Verified] NPC Ask Answer OK");
	}

	int value = pPacket->getParameter();
	int iSecondParameter ; 

	
	switch (pPacket->getCode())
	{		
		//------------------------------------------------------
		//
		//				Quit Dialog
		//
		//------------------------------------------------------
		case NPC_RESPONSE_QUIT_DIALOGUE :
			//if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK)
			{
				g_pUIDialog->UnSetLockInputPCTalk();

				g_pPlayer->SetWaitVerifyNULL();

				// ��ȭ���� �ƴ϶�� �ǹ��̴�.
				g_pUIDialog->ClosePCTalkDlg();
			}
		break;

		//------------------------------------------------------
		//
		//					���� ����
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_INTERFACE_REPAIR :
			UI_OpenInventoryToRepair();
		break;
#if __CONTENTS(__REPAIRSYSTEM_RENEWAL)
		case NPC_RESPONSE_REPAIR_FAIL_NOT_NEED :
			UI_PopupMessage(STRING_MESSAGE_CANNOT_REPAIR);
			break;
#endif //__REPAIRSYSTEM_RENEWAL

		//------------------------------------------------------
		//
		//					���� ����
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_INTERFACE_HELICOPTER :
			UI_RunSelectWayPoint( 0 );
		break;		

		//------------------------------------------------------			
		//
		//					������ ����
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_INTERFACE_STASHOPEN :
			//----------------------------------------------------------------------
			// ������ ������ ���� ��쿣 std::list�� ��û�Ѵ�.
			//----------------------------------------------------------------------
			if (g_pStorage==NULL)
			{	
				ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

				CGStashList	_CGStashList;

				_CGStashList.setObjectID( g_pPlayer->GetID() );
				
				pClientPlayer->sendPacket( &_CGStashList );
			}
			//----------------------------------------------------------------------
			// �̹� ������ ������ �ٷ� ����.
			//----------------------------------------------------------------------
			else
			{
				UI_RunStorage();
				UI_SetStorage(g_pStorage);
			}
		break;
	
		
		//--------------------------------------------------------------
		//
		//  Repair OK
		//
		//--------------------------------------------------------------
		case NPC_RESPONSE_REPAIR_OK :
			//--------------------------------------------------------------
			// Item �Ĵ� packet�� �����ϴ°� �³�?
			//--------------------------------------------------------------
			if (g_pTempInformation->GetMode() == TempInformation::MODE_SHOP_REPAIR)
			{
				//MItem* pCheckItem = (MItem*)g_pTempInformation->pValue;		
				
				MItem* pModifyItem = (MItem*)g_pTempInformation->pValue;		//NULL;

				BOOL	bInInventory	= g_pTempInformation->Value1;
				BOOL	bInGear			= g_pTempInformation->Value2;
				
				//--------------------------------------------------------------
				// inventory�� item����
				//--------------------------------------------------------------		
				/*
				if (bInInventory)
				{
					pModifyItem = g_pInventory->GetItemToModify( itemID );
				}
				//--------------------------------------------------------------
				// gear�� item����
				//--------------------------------------------------------------		
				else if (bInGear)
				{
					//--------------------------------------------------------------
					// gear�� item ����
					//--------------------------------------------------------------
					if (pModifyItem==NULL)
					{
						if (g_pPlayer->IsSlayer())
						{
							pModifyItem = g_pSlayerGear->GetItemToModify( itemID );
						}
						else
						{
							pModifyItem = g_pVampireGear->GetItemToModify( itemID );
						}
					}
				}
				*/

				//--------------------------------------------------------------
				// ��~ �����ϴ� ���
				//--------------------------------------------------------------
				if (pModifyItem==NULL && !bInInventory && bInGear)
				{
					MPlayerGear* pGear = g_pPlayer->GetGear();

					// �� �����ϱ�
					pGear->SetBegin();

					MItem* pLastItem = NULL;

					while (pGear->IsNotEnd())
					{
						MItem* pItem = pGear->Get();

						if (pItem!=NULL)
						{
							pItem->SetCurrentDurability( pItem->GetMaxDurability() );

							pLastItem = pItem;
						}

						pGear->Next();
					}

					// ���� üũ
#if __CONTENTS(__GEAR_SWAP_CHANGE)	//	GCNPCResponseHandler::execute		pGear->CheckAffectStatusAllGear();
					pGear->CheckAffectStatusAllGear();
#else
					pGear->CheckAffectStatusAll();
#endif //__GEAR_SWAP_CHANGE

					//--------------------------------------------------------------
					// �����ߴٰ� �Ҹ� ���
					//--------------------------------------------------------------
					if (pLastItem!=NULL)
					{	
						PlaySound( pLastItem->GetInventorySoundID() );				
					}


					//--------------------------------------------------------------
					// ���� �ٲ��ش�.
					//--------------------------------------------------------------
					if (!g_pMoneyManager->SetMoney( value ))
					{
						DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), value);
					}
#if __CONTENTS(__REPAIRSYSTEM_RENEWAL)
					g_pPriceManager->RepairPriceListeraseAll();
#endif //__REPAIRSYSTEM_RENEWAL


					DEBUG_ADD("RepairAll OK");
				}
				//--------------------------------------------------------------
				// �ϳ��� �����ϴ� ���
				//--------------------------------------------------------------
				else if (//pCheckItem!=NULL && 
						pModifyItem!=NULL)
				{
					// ID ������ �Ѵ�.
					if (1)//pCheckItem->GetID()==itemID && pModifyItem->GetID()==itemID)
					{
						//--------------------------------------------------------------
						// durability�� max��..
						//--------------------------------------------------------------
						if (pModifyItem->IsChargeItem())
						{
							pModifyItem->SetNumber( pModifyItem->GetMaxNumber() );

							if (g_pSkillAvailable!=NULL)
							{
								g_pSkillAvailable->SetAvailableSkills();		
							}	
						}
						else
						{
							pModifyItem->SetCurrentDurability( pModifyItem->GetMaxDurability() );
						}

						//--------------------------------------------------------------
						// Gear�� �ִ� ���� 
						//--------------------------------------------------------------
						if (bInGear)
						{
							MPlayerGear *pGear = g_pPlayer->GetGear();
							
#if __CONTENTS(__GEAR_SWAP_CHANGE)//	GCNPCResponseHandler::execute		pGear->CheckAffectStatusAllGear();
						pGear->CheckAffectStatusAllGear();
#else
						pGear->CheckAffectStatusAll();
#endif //__GEAR_SWAP_CHANGE				
						}

						//--------------------------------------------------------------
						// �����ߴٰ� �Ҹ� ���
						//--------------------------------------------------------------
						PlaySound( pModifyItem->GetInventorySoundID() );				

						//--------------------------------------------------------------
						// ���� �ٲ��ش�.
						//--------------------------------------------------------------
						if (!g_pMoneyManager->SetMoney( value ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), value);
						}
#if __CONTENTS(__REPAIRSYSTEM_RENEWAL)
						g_pPriceManager->RepairPriceListerase(pModifyItem->GetID());
#endif //__REPAIRSYSTEM_RENEWAL
					}
					//else
					//{
					//	DEBUG_ADD_FORMAT("[Error] Different ID. Packet(%d)!=ClientTemp(%d)", itemID, pModifyItem->GetID());
					//}
				}
				else
				{
					DEBUG_ADD_FORMAT("[Error] Item is NULL");
				}

				// mode�� ���ش�.
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
				UI_UnlockItemTrade();
			}
			else
			{
				DEBUG_ADD("[Error] Repair? -_-; No Temp Information!");
			}
		break;

		//------------------------------------------------------			
		//
		//					���� �Ұ�
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST :
		case NPC_RESPONSE_REPAIR_FAIL_ITEM_TYPE :
		case NPC_RESPONSE_REPAIR_FAIL_MONEY :
			// mode�� ���ش�.
			g_pTempInformation->SetMode(TempInformation::MODE_NULL);

			// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
			UI_UnlockItemTrade();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_REPAIR].GetString() );

		break;

		//------------------------------------------------------			
		//
		//					������ ���
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_STASH_SELL_OK :
			if (g_pTempInformation->GetMode() == TempInformation::MODE_STORAGE_BUY_WAIT)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// �ٽ� ������?������ �� �ְ� �Ѵ�.
				g_pUIDialog->ShowPCTalkDlg();

				// �̹� �������� �ִٸ� ���Ž�Ų��.
				// �׷���.. ������ ������ �����Ҷ�.. �ϳ� �߰��ż� �����ȴ�.
				if (g_pStorage!=NULL)
				{
					delete g_pStorage;
					g_pStorage = NULL;
				}

				// ������ ���� ����� ���ش�.
				g_pMoneyManager->UseMoney( g_pTempInformation->Value1 );

				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_STORAGE_BUY].GetString());
			}
		break;

		//------------------------------------------------------			
		//
		//					������ ��� ����
		//
		//------------------------------------------------------			
		case NPC_RESPONSE_STASH_SELL_FAIL_MAX :
		case NPC_RESPONSE_STASH_SELL_FAIL_MONEY :
			if (g_pTempInformation->GetMode() == TempInformation::MODE_STORAGE_BUY_WAIT)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// �ٽ� ������?������ �� �ְ� �Ѵ�.
				g_pUIDialog->ShowPCTalkDlg();

				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_MORE].GetString());
			}
		break;

		//------------------------------------------------------
		//
		//					Silver ���� ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_SILVER_COATING_OK :
			//--------------------------------------------------------------
			// silvering�� �³�?
			//--------------------------------------------------------------
			if (g_pTempInformation->GetMode() == TempInformation::MODE_SHOP_SILVERING)
			{
				//MItem* pCheckItem = (MItem*)g_pTempInformation->pValue;		
				
				MItem* pModifyItem = (MItem*)g_pTempInformation->pValue;		//NULL;

				BOOL	bInInventory	= g_pTempInformation->Value1;
				BOOL	bInGear			= g_pTempInformation->Value2;	

				if (//pCheckItem!=NULL && 
					pModifyItem!=NULL)
				{
					// ID ������ �Ѵ�.
					if (1)//pCheckItem->GetID()==itemID && pModifyItem->GetID()==itemID)
					{
						//--------------------------------------------------------------
						// durability�� max��..
						//--------------------------------------------------------------
						pModifyItem->SetSilver( pModifyItem->GetSilverMax() );
						const MItem* pWeapon = g_pSlayerGear->GetItem( MSlayerGear::GEAR_SLAYER_RIGHTHAND );
						if(pModifyItem->IsAffectStatus() && pModifyItem == pWeapon)
						{
							UI_SetCharInfoSilverDamage(pWeapon->GetMinDamage() / 10, pWeapon->GetMaxDamage() / 10);
						}

						//--------------------------------------------------------------
						// �����ߴٰ� �Ҹ� ���
						//--------------------------------------------------------------
						PlaySound( pModifyItem->GetInventorySoundID() );				

						//--------------------------------------------------------------
						// ���� �ٲ��ش�.
						//--------------------------------------------------------------
						if (!g_pMoneyManager->SetMoney( value ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), value);
						}
					}
					//else
					//{
					//	DEBUG_ADD_FORMAT("[Error] Different ID. Packet(%d)!=ClientTemp(%d)", itemID, pModifyItem->GetID());
					//}
				}
				else
				{
					DEBUG_ADD_FORMAT("[Error] Item is NULL");
				}

				// mode�� ���ش�.
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
				UI_UnlockItemTrade();
			}
			else
			{
				DEBUG_ADD("[Error] Silvering? -_-; No Temp Information!");
			}
		break;

		//------------------------------------------------------
		//
		//					Silver ���� ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_NOT_EXIST :
		case NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_TYPE :
		case NPC_RESPONSE_SILVER_COATING_FAIL_MONEY :
			// mode�� ���ش�.
			g_pTempInformation->SetMode(TempInformation::MODE_NULL);

			// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
			UI_UnlockItemTrade();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_SILVERING].GetString() );
		break;

		
		//------------------------------------------------------
		//
		//				Silver ���� UI ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_SILVER_COATING :
			UI_OpenInventoryToSilvering();
		break;

		//------------------------------------------------------
		//
		//				��� ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_CREATE_GUILD :
		break;

		//------------------------------------------------------
		//
		//				��� ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_DESTROY_GUILD :
		break;
	
		//------------------------------------------------------
		//
		//				Newbie Item
		//
		//-----------------------------------------------------
		case NPC_RESPONSE_INTERFACE_NEWBIE_ITEM :
			UI_RunTutorialExit();
		break;

		//------------------------------------------------------
		//
		//				Tutorial Computer
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_TUTORIAL_COMPUTER :
			UI_RunComputer();
		break;

		//------------------------------------------------------
		//
		//				Tutorial Briefing
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_TUTORIAL_BRIEFING :
			UI_RunBriefing();
		break;

		//------------------------------------------------------
		//
		//				Tutorial Bookcase
		//
		//------------------------------------------------------
		case NPC_RESPONSE_INTERFACE_TUTORIAL_BOOKCASE :
			UI_RunBookcase();
		break;

		//------------------------------------------------------
		//
		//				ġ�� ���� ��
		//
		//------------------------------------------------------
		case NPC_RESPONSE_HEAL :
			if( g_pPlayer->IsSlayer() )
				PlaySound( SOUND_ITEM_USE_HPOTION );
			else if (g_pPlayer->IsOusters() )
				PlaySound( SOUND_OUSTERS_PUPA );
		break;

		//------------------------------------------------------
		//
		//				��� ���� ��
		//
		//------------------------------------------------------
		case NPC_RESPONSE_DONATION_OK :
			//--------------------------------------------------------------
			// ���� �ٲ��ش�.
			//--------------------------------------------------------------
			if (!g_pMoneyManager->SetMoney( value ))
			{
				DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), value);
			}

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_DONATION_OK].GetString() );
		break;

		//------------------------------------------------------
		//
		//				��� ����
		//
		//------------------------------------------------------
		case NPC_RESPONSE_DONATION_FAIL_MONEY :
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_DONATION_FAIL].GetString() );
		break;

		/////////////////////////////////////////////////////////
		// �౸������ ���ǻ��
		/////////////////////////////////////////////////////////
		case NPC_RESPONSE_DECREASE_BALL:
		// ������ ������ŭ�� inventory���� �����ش�.
		{
			int remainNum = pPacket->getParameter();
				
			// ��� �ִ��� ã�ƺ���.
			MItemClassTypeFinder ballFinder(ITEM_CLASS_EVENT_STAR, 6);	// ball�� 6�� :)
				
			// ������ŭ inventory���� �����Ѵ�.
			while (remainNum > 0)
			{
				MItem* pBallItem = g_pInventory->FindItemGridOrder( ballFinder );
				
				// ���� ���� ��� - -;
				if (pBallItem==NULL)
				{
					DEBUG_ADD("[Error] Not Enough Ball -_-");
					break;
				}
				
				int itemNum = pBallItem->GetNumber();
				
				if (itemNum > remainNum)
				{
					pBallItem->SetNumber( itemNum - remainNum );
					remainNum = 0;
				}
				else
				{
					// ���ų� ���� ���
					remainNum -= itemNum;
					
					MItem* pRemovedItem = g_pInventory->RemoveItem( 
						pBallItem->GetGridX(), 
						pBallItem->GetGridY() );
					
					if (pRemovedItem!=NULL)
					{
						delete pRemovedItem;
					}
					else
					{
						DEBUG_ADD_FORMAT("[Error] Can't remove ball(%d, %d)", pBallItem->GetGridX(), pBallItem->GetGridY());
					}
				}
			}
		}
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_ALREADY_JOIN:			// ��� �ѹ� ����? �ڳ״� �̹� <team_name> �� �Ҽ��̶�� ���� �ֱ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_ALREADY_JOIN].GetString(), g_pUserInformation->GuildName.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_QUIT_TIMEOUT:			// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_QUIT_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_CANCEL_TIMEOUT:		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_CANCEL_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_LEVEL:				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_LEVEL].GetString() );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_MONEY:				// ���� ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_MONEY].GetString() );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_FAME:					// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_NAME:					// �� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_NAME].GetString() );
		break;

		case NPC_RESPONSE_TEAM_REGIST_FAIL_DENY:				// <team name>������ �ڳ׸� �ź����� �ʾҴ°�. �ٸ� ���� ã�ƺ���
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_REGIST_FAIL_DENY].GetString() );
		break;


		case NPC_RESPONSE_TEAM_STARTING_FAIL_ALREADY_JOIN:		// ����� �̹� �ٸ� ���� ���ԵǾ� �ֽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_ALREADY_JOIN].GetString() );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_QUIT_TIMEOUT:		// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_QUIT_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_CANCEL_TIMEOUT:		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_CANCEL_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_LEVEL:				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_LEVEL].GetString() );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_MONEY:				// <player_name>, �� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_MONEY].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_FAME:				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_TEAM_STARTING_FAIL_DENY:				// <team name>������ �ڳ׸� �ź����� �ʾҴ°�. �ٸ� ���� ã�ƺ���
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TEAM_STARTING_FAIL_DENY].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_ALREADY_JOIN:			// ��� �ѹ� ����? �ڳ״� �̹� <clan_name> Ŭ���� ������ ���� ���¶�� ���� �ֱ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_ALREADY_JOIN].GetString(), g_pUserInformation->GuildName.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_QUIT_TIMEOUT:			// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. �ʹ� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_QUIT_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_CANCEL_TIMEOUT:		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_CANCEL_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_LEVEL:				// �Ǹ������� ��θӸ��ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_LEVEL].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_MONEY:				// Ŭ���� ����Ϸ��� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ����̴±�...
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_MONEY].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_FAME:					// <player_name>�̶�.. ���� � �����̾��ΰ�����. �� ���� �Ǹ� ���ð� �ٽ� ã�ƿ��Գ�.
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_NAME:					// Ŭ�� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_NAME].GetString() );
		break;

		case NPC_RESPONSE_CLAN_REGIST_FAIL_DENY:				// <team name>Ŭ������ �ڳ׸� �ź����� �ʾҴ°�. �ٸ� Ŭ���� ã�ƺ���
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_REGIST_FAIL_DENY].GetString() );
		break;


		case NPC_RESPONSE_CLAN_STARTING_FAIL_ALREADY_JOIN:		// ����� �̹� �ٸ� Ŭ���� ���ԵǾ� �ֽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_ALREADY_JOIN].GetString() );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_QUIT_TIMEOUT:		// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. �ʹ� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_QUIT_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_CANCEL_TIMEOUT:		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_CANCEL_TIMEOUT].GetString() );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_LEVEL:				// �Ǹ��� �����ڰ� �Ǳ⿡�� ������ �� ������ �� ����. ���� ���� ������ �ϰ� ���Գ�
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_LEVEL].GetString() );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_MONEY:				// ����� �����ص� Ŭ���� ������ �� �ִ� ���� �����ϸ� �� Ŭ���� �������� ��������
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_MONEY].GetString() );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_FAME:				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
		break;

		case NPC_RESPONSE_CLAN_STARTING_FAIL_DENY:				// <team name>Ŭ������ �ڳ׸� �ź����� �ʾҴ°�. �ٸ� Ŭ���� ã�ƺ���
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLAN_STARTING_FAIL_DENY].GetString() );
		break;


		case NPC_RESPONSE_GUILD_SHOW_REGIST:             // ��� ��� â ����
			UI_ShowGuildRegist(pPacket->getParameter());
		break;
	
		case NPC_RESPONSE_GUILD_SHOW_STARTING_JOIN:      // ��� ��Ÿ�� ��� ���� â ����
//			UI_ShowGuildStartJoin(pPacket->getParameter());
		break;

		case NPC_RESPONSE_GUILD_SHOW_JOIN:               // ��� ���� â ����
//			UI_ShowGuildJoin(pPacket->getParameter());
		break;

		case NPC_RESPONSE_GUILD_SHOW_QUIT:               // ��� Ż�� â ����
//			UI_ShowGuildQuit();
		break;

		case NPC_RESPONSE_GUILD_ERROR:                   // ��� ����
		break;

		case NPC_RESPONSE_TRADE_GIFT_BOX_OK:             // ���� ���� ��ȯ ����
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_GIFT_BOX_OK].GetString() );
		break;

		case NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM:        // ���� ���� ����
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_GIFT_BOX_NO_ITEM].GetString() );
		break;

		case NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE:  // ���� ���ڸ� �̹� �ѹ� ��ȯ�ߴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_GIFT_BOX_ALREADY_TRADE].GetString() );
		break;

		case NPC_RESPONSE_TRADE_GIFT_BOX_ERROR:          // ���� ���� ��ȯ�� ���� ��Ÿ ����
		break;

		case NPC_RESPONSE_REWARD_OK:					// ������ �޾ҽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_REWARD_OK].GetString() );
		break;

		case NPC_RESPONSE_REWARD_FAIL:					// ������ ���� �� �����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_REWARD_FAIL].GetString() );
		break;

		case NPC_RESPONSE_NO_EMPTY_SLOT:				// �� �ڸ��� �����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NO_EMPTY_SLOT].GetString() );
		break;

		case NPC_RESPONSE_SHOW_TAX_BALANCE :			// ���� �׿��ִ� ������ �ܾ��� �����ش�.
			UI_OpenBringFee(pPacket->getParameter());
			break;

		case NPC_RESPONSE_WITHDRAW_TAX_OK :				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
			UI_SetTotalFee(pPacket->getParameter());
			if(g_pTempInformation->GetMode() == TempInformation::MODE_WAIT_BRING_FEE)
			{
				// �������� �����شٴ�.. ��ȿ-_-
				//g_pMoneyManager->AddMoney(g_pTempInformation->Value1);
				// ���� �Ϸ�
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);
			}
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_SUCCESS_BRING_FEE].GetString());
			break;

		case NPC_RESPONSE_WITHDRAW_TAX_FAIL :			// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_FAIL_BRING_FEE].GetString());
			
			// ����-_- �Ϸ� 
			if(g_pTempInformation->GetMode() == TempInformation::MODE_WAIT_BRING_FEE)
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

			break;			
		
		case NPC_RESPONSE_NO_GUILD :					// ��(Ŭ��)�� �ҼӵǾ� ���� �ʽ��ϴ�.
			if(g_pPlayer->IsSlayer())			
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NO_TEAM].GetString());
			else
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NO_CLAN].GetString());
			break;
		
		case NPC_RESPONSE_NOT_GUILD_MASTER:				// ��(Ŭ��) �����Ͱ� �ƴմϴ�.
			if(g_pPlayer->IsSlayer())			
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NOT_TEAM_MASTER].GetString());
			else
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NOT_CLAN_MASTER].GetString());
			break;
		
		case NPC_RESPONSE_HAS_NO_CASTLE:			    // ��(Ŭ��)�� ���� ���� �����ϴ�.
			if(g_pPlayer->IsSlayer())			
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_TEAM_HAS_NO_CASTLE].GetString());
			else
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_CLAN_HAS_NO_CASTLE].GetString());
			break;
		
		case NPC_RESPONSE_NOT_YOUR_CASTLE:		        // ��(Ŭ��)�� ������ ���� �ƴմϴ�.
			if(g_pPlayer->IsSlayer())			
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_TEAM_NOT_YOUR_CASTLE].GetString());
			else
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_CLAN_NOT_YOUR_CASTLE].GetString());
			break;
		
		case NPC_RESPONSE_NOT_ENOUGH_MONEY :			// ���� �����մϴ�.(�����û�� ���������� ���������� ������ -_-;)
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_WAR_NOT_ENOUGH_MONEY].GetString());
			break;
		
		case NPC_RESPONSE_WAR_SCHEDULE_FULL :			// ���� �������� �� á���ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_WAR_SCHEDULE_FULL].GetString());
			break;
		
		case NPC_RESPONSE_WAR_ALREADY_REGISTERED :        // �̹� ������ ��û�߾����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_WAR_ALREADY_REGISTERED].GetString());
			break;
		
		case NPC_RESPONSE_WAR_REGISTRATION_OK :			// ���� �����쿡 ��� �Ǿ����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_WAR_REGISTRATION_OK].GetString());
			break;
		
		case NPC_RESPONSE_ALREADY_HAS_CASTLE :            // �̹� ���� ������ �ֽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_ALREADY_HAS_CASTLE].GetString());			
			break;
		
		case NPC_RESPONSE_WAR_UNAVAILABLE :               // ������ ���� ��û�� ���� �ʽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_WAR_UNAVAILABLE].GetString());
			break;

		case NPC_RESPONSE_RACE_WAR_JOIN_FAILED :               // <�����> �� �������� ���� ���� ��û�ο��� �� á���ϴ�.
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_RACE_WAR_JOIN_FAILED].GetString(), g_pUserInformation->CharacterID.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;

		case NPC_RESPONSE_RACE_WAR_JOIN_OK :               // ���� ���� ���� ��û�� �߽��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_RACE_WAR_JOIN_OK].GetString());
			break;

		case NPC_RESPONSE_RACE_WAR_GO_FIRST_SERVER :               // ���� ������ �� ������ ù��° ���������� ��û �� ������ �����մϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_RACE_WAR_GO_FIRST_SERVER].GetString());
			break;

		case NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW:      // ������ �̺�Ʈ �������� ���� �� �����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_GIVE_EVENT_ITEM_FAIL_NOW].GetString());
		break;
    		
		case NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL:          // �̺�Ʈ �������� ���� �� �����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_GIVE_EVENT_ITEM_FAIL].GetString());
		break;

		case NPC_RESPONSE_GIVE_EVENT_ITEM_OK:            // �̺�Ʈ�� ���� �������� �޾ҽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_GIVE_EVENT_ITEM_OK].GetString());
		break;

		case NPC_RESPONSE_GIVE_PREMIUM_USER_ONLY:        // �����̾����� ����ڸ� ���� �� �ֽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_GIVE_PREMIUM_USER_ONLY].GetString());
		break;

		// Ŀ�ý�û ����
		case NPC_RESPONSE_WAIT_FOR_MEET_COUPLE:			// Ŀ�� ��û �� ����� �̸��� �Է��ϼ���
			UI_RunInputNameWindow(0);
		break;

		case NPC_RESPONSE_COUPLE_MEET_SUCCESS:			// Ŀ���� ����Ǿ����ϴ�.
			UI_CloseInputNameWindow();
			if(g_pPlayer->IsOusters())
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_MEET_SUCCESS].GetString());
			else
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_MEET_SUCCESS].GetString());
			
		break;

		case NPC_RESPONSE_COUPLE_CANNOT_MEET:			// Ŀ���� ����� �� �����ϴ�.CoupleMessage Enum ���
			UI_CloseInputNameWindow();
			
			if(g_pPlayer->IsOusters())
			{
				if(pPacket->getParameter() != 0 && pPacket->getParameter() < COUPLE_MESSAGE_MAX)
					// enum�� 1���� �����ϹǷ� -1���ش�. MGameStringTabe�� ������ �����!!!
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_NOT_EVENT_TERM+pPacket->getParameter()-1].GetString());
				else
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_CANNOT_MEET].GetString());
			}
			else
			{
				if(pPacket->getParameter() != 0 && pPacket->getParameter() < COUPLE_MESSAGE_MAX)
					// enum�� 1���� �����ϹǷ� -1���ش�. MGameStringTabe�� ������ �����!!!
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_NOT_EVENT_TERM+pPacket->getParameter()-1].GetString());
				else
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_CANNOT_MEET].GetString());
			}
			
		break;

		case NPC_RESPONSE_MEET_WAIT_TIME_EXPIRED:		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.
			UI_CloseInputNameWindow();
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_MEET_WAIT_TIME_EXPIRED].GetString());			
		break;

		case NPC_RESPONSE_WAIT_FOR_APART_COUPLE:		// ����� ����� �̸��� �Է��ϼ���
			UI_RunInputNameWindow(1);
		break;

		case NPC_RESPONSE_COUPLE_APART_SUCCESS:			// ��������ϴ�.
			UI_CloseInputNameWindow();
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_APART_SUCCESS].GetString());
			g_pSkillAvailable->SetAvailableSkills();			
		break;

		case NPC_RESPONSE_NOT_COUPLE:					// Ŀ���� �ƴ϶� ����� �� �����ϴ�.CoupleMessage Enum ���
			UI_CloseInputNameWindow();


			if(g_pPlayer->IsOusters())
			{
				if(pPacket->getParameter() != 0 && pPacket->getParameter() < COUPLE_MESSAGE_MAX)
					// enum�� 1���� �����ϹǷ� -1���ش�. MGameStringTabe�� ������ �����!!!
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_OUSTERS_COUPLE_NOT_EVENT_TERM+pPacket->getParameter()-1].GetString());
				else
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NOT_COUPLE].GetString());
			}
			else
			{
					if(pPacket->getParameter() != 0 && pPacket->getParameter() < COUPLE_MESSAGE_MAX)
						// enum�� 1���� �����ϹǷ� -1���ش�. MGameStringTabe�� ������ �����!!!
						g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_COUPLE_NOT_EVENT_TERM+pPacket->getParameter()-1].GetString());
					else
						g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_NOT_COUPLE].GetString());
			}
			break;

		case NPC_RESPONSE_APART_WAIT_TIME_EXPIRED:		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.
			UI_CloseInputNameWindow();
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_MEET_WAIT_TIME_EXPIRED].GetString());
		break;

		case NPC_RESPONSE_APART_COUPLE_FORCE :            // �Ϲ������� ����� ����� �̸��� �Է��ϼ���.
			UI_RunInputNameWindow(2);
			break;
		case NPC_RESPONSE_QUEST :
			switch( (QuestMessage) pPacket->getParameter() )
			{
			case START_SUCCESS :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_START_MONSTER_KILL_QUEST].GetString() );
				break;
			case START_FAIL_QUEST_NUM_EXCEEDED :				
			case START_FAIL_DUPLICATED_QUEST_ID :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_FAIL_ALREADY_START_MONSTER_KILL_QUEST].GetString() );
				break;
			case START_FAIL_PC :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_FAIL_MONSTER_KILL_QUEST_BY_STATUS].GetString() );
				break;
			case COMPLETE_SUCCESS :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_SUCCESS_MONSTER_KILL_QUEST].GetString() );
				//g_pEventManager->RemoveEvent( EVENTID_MONSTER_KILL_QUEST );
				UI_InitQuestStatus();				
				break;
			case COMPLETE_FAIL_NOT_COMPLETE :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_YET_COMPLETE_MONSTER_KILL_QUEST].GetString() );
				break;
			case COMPLETE_FAIL_NO_INVENTORY_SPACE :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_INVENTORY_FULL_MONSTER_KILL_QUEST].GetString() );
				break;
			case COMPLETE_FAIL_NOT_IN_QUEST :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_IN_QUEST].GetString() );
				break;
			case COMPLETE_FAIL_TIME_EXPIRED :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_FAIL_QUEST_EXPIRED_TIME].GetString() );
				break;
			case START_FAIL_CANNOT_APPLY_QUEST :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_CANNOT_APPLY_QUEST].GetString() );
				break;
			case CANCEL_SUCCESS :
				//				g_pEventManager->RemoveEvent( EVENTID_MONSTER_KILL_QUEST );				
				UI_InitQuestStatus();
				// NPC Script �� ������ �ϹǷ�, �ٽ� ���� �ɾ��ش�.
				g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_NPC_ASK );
				break;
			case CANCEL_NOT_IN_QUEST :
				g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_NPC_ASK );
				break;
			case COMPLETE_FAIL_INVALID_NPC :
				// �ش� NPC ���� ������ ���� �� �����ϴ�.
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_FAIL_INVALID_NPC].GetString() );
				break;
			case FAIL_BUG :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_FAIL_BUG].GetString() );
				break;
			}			
			break;
		case NPC_RESPONSE_LOTTERY :
			{
				int step = -1;
				if( pPacket->getParameter() >= 0 && pPacket->getParameter() <= 4 )
					step = pPacket->getParameter() + 1;
				
				if(step != -1 )
				{
					UI_RunLottery( step );
				}
			}
			break;
		case NPC_RESPONSE_CANNOT_BUY :			
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TAKE_OUT_ITEM_FROM_SHOP].GetString() );
			break;
		case NPC_RESPONSE_CLEAR_RANK_BONUS_OK :           // �����Ͻ� ����� ��ų�� ���� �Ǿ����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CLEAR_RANK_BONUS_OK].GetString() );
			break;
		case NPC_RESPONSE_NO_RANK_BONUS :                 // �ش� �ڰ��� �����ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NO_RANK_BONUS].GetString() );
			break;
		case NPC_RESPONSE_ALREADY_CLEAR_RANK_BONUS :      // �����Ͻ� ��� ��ų�� ������ ���� �ֽ��ϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_ALREADY_CLEAR_RANK_BONUS].GetString() );
			break;
		case NPC_RESPONSE_GNOME_CONTRACT_OK :
			g_pUIDialog->ClosePCTalkDlg();
			UI_PopupMessage( STRING_MESSAGE_CONTRACT_GNOMES_HORN_OK );
			break;
		case NPC_RESPONSE_DOWN_SKILL :
			UI_DownSkill();
			break;
			
		case NPC_RESPONSE_GUILD_REGIST_FAIL_ALREADY_JOIN :		// ��� �ѹ� ����? �ڳ״� �̹� <guild_name> ��� �Ҽ��̶�� ���� �ֱ�
			wsprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_GUILD_REGIST_FAIL_ALREADY_JOIN].GetString(), g_pUserInformation->GuildName.GetString());
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_QUIT_TIMEOUT :		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_QUIT_TIMEOUT );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_CANCEL_TIMEOUT :		// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_CANCEL_TIMEOUT );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_LEVEL :				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_LEVEL );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_MONEY :				// ��带 ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_MONEY );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_FAME :				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
			wsprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_GUILD_REGIST_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString() );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_NAME :				// ��� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_NAME );
			break;
		case NPC_RESPONSE_GUILD_REGIST_FAIL_DENY :				// �źεǾ����ϴ�.
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_DENY );
			break;			
		case NPC_RESPONSE_GUILD_STARTING_FAIL_ALREADY_JOIN :		// ����� �̹� �ٸ� ��忡 ���ԵǾ� �ֽ��ϴ�.
			UI_PopupMessage( STRING_MESSAGE_GUILD_STARTING_FAIL_ALREADY_JOIN );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_QUIT_TIMEOUT :		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
			UI_PopupMessage( STRING_MESSAGE_GUILD_STARTING_FAIL_QUIT_TIMEOUT );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_CANCEL_TIMEOUT :	// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
			UI_PopupMessage( STRING_MESSAGE_GUILD_STARTING_FAIL_CANCEL_TIMEOUT );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_LEVEL :				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.
			UI_PopupMessage( STRING_MESSAGE_GUILD_STARTING_FAIL_LEVEL );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_MONEY :				// <player_name>, ��� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�
			wsprintf( sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_GUILD_STARTING_FAIL_MONEY].GetString(), g_pUserInformation->CharacterID.GetString() );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_FAME :				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
			wsprintf( sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_GUILD_STARTING_FAIL_FAME].GetString(), g_pUserInformation->CharacterID.GetString() );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
		case NPC_RESPONSE_GUILD_STARTING_FAIL_DENY :			// �źεǾ����ϴ�.
			UI_PopupMessage( STRING_MESSAGE_GUILD_REGIST_FAIL_DENY );
			break;
		case NPC_RESPONSE_TOO_MANY_GUILD_REGISTERED:             // ���� ��û�� ��尡 �ʹ� ���Ƽ� ��û�� �� �����ϴ�.   // 120
			UI_PopupMessage( STRING_MESSAGE_TOO_MANY_GUILD_REGISTERED );
			break;
		case NPC_RESPONSE_REINFORCE_DENYED:                      // ������ ���� ��û�� �̹� �źδ��ؼ� ���û �� �� �����ϴ�.    // 121
			UI_PopupMessage( STRING_MESSAGE_REINFORCE_DENYED );
			break;
		case NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED:            // ������ ���� ��û�� �㰡�� ��尡 �̹� �־ ��û�� �� �����ϴ�. // 122
			UI_PopupMessage( STRING_MESSAGE_ALREADY_REINFORCE_ACCEPTED );
			break;
		case NPC_RESPONSE_NO_WAR_REGISTERED:                     // ���� ��û�� ��尡 ��� ������ ���� ��û�� �� �� �����ϴ�. 
			UI_PopupMessage( STRING_MESSAGE_NO_WAR_REGISTERED );
			break;
		case NPC_RESPONSE_CANNOT_ACCEPT:
			UI_PopupMessage( STRING_MESSAGE_CANNOT_ACCEPT );//] = "������ ���� ��û�� ������ �� �����ϴ�";
			break;
		case NPC_RESPONSE_ACCEPT_OK:
			UI_PopupMessage( STRING_MESSAGE_ACCEPT_OK );//] = "���� ��û�� �����Ͽ����ϴ�.";
			break;
		case NPC_RESPONSE_CANNOT_DENY:
			UI_PopupMessage( STRING_MESSAGE_CANNOT_DENY );//] = "������ ���� ��û�� �ź��� �� �����ϴ�.
			break;
		case NPC_RESPONSE_DENY_OK:
			UI_PopupMessage( STRING_MESSAGE_DENY_OK );//] = "���� ��û�� �ź��Ͽ����ϴ�.;
			break;
			
		case NPC_RESPONSE_SHOW_TAX_RATIO:						// ������ �춧�� ���� ����â �߰� �Ѵ�.
			UI_RunModifyTax(value);
			break;
		case NPC_RESPONSE_MODIFY_TAX_RATIO_OK:					// ���� ���� ������~
			gC_vs_ui.CloseTexRate() ;
			UI_PopupMessage( UI_STRING_MESSAGE_MODIFY_TAX_OK );
			break;
		case NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL:				// ���� ���� ����
			gC_vs_ui.CloseTexRate() ;
			UI_PopupMessage( UI_STRING_MESSAGE_MODIFY_TAX_FAIL );
			break;
		case NPC_RESPONSE_SWAP_ADVANCEMENT_ITEM:
			UI_Show_Swap_Advancement_Item();
			break;
		case NPC_RESPONSE_NOT_ADVANCED:
			UI_PopupMessage( UI_STRING_MESSAGE_SWAP_ERROR );
			break;
		case NPC_RESPONSE_SHOW_DONATION_DAILOG:                  // ���â�� ����.
		//	value
			iSecondParameter = pPacket->getParameter(); //  : ��α�  : ���Ǳ� 
			switch(iSecondParameter)
			{
			case DONATION_TYPE_200501_PERSONAL	:
			case DONATION_TYPE_200501_GUILD	:
				UI_Run_Campaign_Help_Unfortunate_Neighbors(value);
				break;	
			case DONATION_TYPE_200505_WEDDING : 
				UI_Run_Wedding_Contribution_Unfortunate_Neighbors(value);
				break;
			}
			break ;  

		case NPC_RESPONSE_SHOW_DONATION_COMPLETE_DAILOG:         // ��� ���� â�� ����.
			UI_PopupMessage( UI_STRING_MESSAGE_CAMPAIGN_HELP_THANKS );
			break;
			
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:    // �̺�Ʈ ������ �ޱ� Ȯ�� ���̾�α׸� ����.
			UI_Run_Confirm_GetEventItem(value);
			break;

		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:           // ���� �޽��� ���̾�α׸� ����.
			switch(value)
			{
			case YOU_CAN_GET_EVENT_200412_COMBACK_ITEM:
				gC_vs_ui.RunPopupMessage(TXT_TUTORIAL_COMEBACKEVENT_NOTICE, C_VS_UI_POPUP_MESSAGE::POPUP_WELCOME );
				//UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_COMEBACK_1 );
				break;
			case YOU_CAN_GET_EVENT_200412_COMBACK_PREMIUM_ITEM:
				gC_vs_ui.RunPopupMessage(TXT_TUTORIAL_COMEBACKEVENT_PAY, C_VS_UI_POPUP_MESSAGE::POPUP_WELCOME );
				//UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_COMEBACK_2 );
				break;
			case YOU_CAN_GET_EVENT_200412_COMBACK_RECOMMEND_ITEM:
				gC_vs_ui.RunPopupMessage(TXT_TUTORIAL_COMEBACKEVENT_RECOMMEND, C_VS_UI_POPUP_MESSAGE::POPUP_WELCOME );
				//UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_COMEBACK_3 );
				break;
			case YOU_GET_EVENT_ITEM:
				UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_RECEIVE_OK );
				break;
			case NOT_ENOUGH_INVENTORY_SPACE:
				UI_PopupMessage( UI_STRING_MESSAGE_INVENTORY_FULL_MONSTER_KILL_QUEST );
				break;
			case ALEADY_GET_EVENT_ITEM:
				UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_RECEIVE_ALREADY );
				break;
			case FAIL_GET_EVENT_ITEM:
				UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_RECEIVE_FAIL );
				break;
			case YOU_ARE_NOT_EVENT_USER:
				UI_PopupMessage( UI_STRING_MESSAGE_GET_EVENT_ITEM_NOT_EVENT_USER );
				break;
			case YOU_CAN_GET_EVENT_200507_COMEBACK_ITEM:
				UI_PopupSummerComBack(0);
				break;
			case YOU_CAN_GET_EVENT_200507_COMEBACK_PREMIUM_ITEM:
				UI_PopupSummerComBack(1);
				break;
			case YOU_CAN_GET_EVENT_200507_COMEBACK_RECOMMEND_ITEM:
				UI_PopupSummerComBack(2);
				break;
			case YOU_CAN_GET_EVENT_COMEBACK_200604_ITEM:
				UI_PopupSummerComBack(3);
				break;
			case YOU_CAN_GET_EVENT_COMEBACK_200604_PREMIUM_ITEM:
				UI_PopupSummerComBack(4);
				break;
			}
			break;
		case NPC_RESPONSE_SHOW_DONATION_WEDDING_COMPLETE_DIALOG:	// ���Ǳ� ����â�� ����.
			 UI_PopupMessage( UI_STRING_MESSAGE_WEDDING_CONTRIBUTION_THANKS);
			 break ;	
		case NPC_RESPONSE_SHOW_ALEADY_DONATED_DIALOG:	// ���Ǳ� �� �̹� ���̽��ϴ�. 
			 UI_PopupMessage( UI_STRING_MESSAGE_WEDDING_CONTRIBUTION_FAIL);
			 break ; 
		
		case NPC_RESPONSE_NOT_CAHNGE_COLOR:	// ������ �ߺ��Ǿ� �ٲܼ� ����.
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_FLAME_COLOR);
			 g_pPlayer->SetPrevDyeColorSet(ITEMTYPE_NULL) ;
			 break ; 

		case NPC_RESPONSE_NOT_ENOUGH_MONEY_CAHNGE_COLOR:	// ���� ������� �ʾ� ������ �ٲܼ� ����.
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_MONEY_FKANE_COLOR);
			 g_pPlayer->SetPrevDyeColorSet(ITEMTYPE_NULL) ;
			 break ; 

		case NPC_RESPONSE_CHANGE_COLOR_OK:	// ������ �Ϸ� �Ǿ����ϴ�.
			{	
				UI_PopupMessage( UI_STRING_MESSAGE_FKANE_COLOR_OK);
				TYPE_ITEMTYPE	ItemType = g_pPlayer->GetPrevDyeColorSet() ; 
				int		DyeColorSet[48] = {400,359,312,267,222,174,130,86,381,342,297,252,207,159,115,70,369,327,283,237,193,145,101,57,
											 165,381,407,420,435,451,466,480,170,364,412,426,440,455,471,487,179,371,419,434,449,464,479,494};
			
				if(ItemType >= 0 && ItemType <= 23 )
				{
					if(g_pPlayer->IsSlayer())
					{
						int color_set = DyeColorSet[ItemType];
						if(g_pPlayer->IsAdvancementClass())
							g_pPlayer->SetAddonColorSet1( ADDON_COAT, (WORD) color_set );
						else
							g_pPlayer->SetAddonHair( g_pPlayer->GetHairFrameID(), (WORD) color_set );
						g_pUserInformation->HairColor = color_set;
					}
					else if (g_pPlayer->IsOusters() )
					{
						int color_set = DyeColorSet[ItemType];
						g_pPlayer->SetBodyColor1( color_set );
						g_pUserInformation->HairColor = color_set;
					}
				} else
				if( ItemType >=24 && ItemType <= 47 )
				{
					int color_set = DyeColorSet[ItemType];
					if(g_pPlayer->IsSlayer())
					{
						g_pPlayer->SetAddonColorSet1(ADDON_COAT, color_set);
					}						
					else
						g_pPlayer->SetBodyColor1( color_set );
					g_pUserInformation->SkinColor = color_set;
				}
			}
			g_pPlayer->SetPrevDyeColorSet(ITEMTYPE_NULL) ;
			break ;
			
		case NPC_NOT_ENOUGH_EXCHANGE_OF_MONEY:	// ���� ������� �ʾ� ��ǥ�� �ٲܼ� ����
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_ENOUGH_EXCHANGE_OF_MONEY);
			 break ; 
		
		case NPC_ENOUGH_PLAYER_MONEY:	// �÷��̾��� �������� �ִ� �����ݾ��� �Ѿ���
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_ENOUGH_PLAYER_MONEY);
			 break ; 

		case NPC_NOT_ENOUGH_CHECK_MONEY:	// ��ǥ�� ����!
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_ENOUGH_CHECK_MONEY);
			 break ; 

		case NPC_EXCHANGE_OF_MONEY_OK:	// ���������� �ŷ��� �Ϸ� �Ǿ����ϴ�
			 UI_PopupMessage( UI_STRING_MESSAGE_EXCHANGE_OF_MONEY_OK);
			 break ; 
		case NPC_NOT_ENOUGH_SOCCER_BALL:
			 UI_PopupMessage( UI_STRING_MESSAGE_NOT_ENOUGH_SOCCER_BALL);
			 break ; 
		case NPC_NOT_ENOUGH_EXCHANGE_SEALING_STONE:
			 UI_PopupMessage( UI_STRING_MESSAGE_NPC_NOT_ENOUGH_EXCHANGE_SEALING_STONE);
			 break ; 

		// ������ ��û ���� ���� �޽��� 
		case NPC_RESPONSE_NOT_ENOUGH_LEVEL:         // ������ ��� ���� �ʴ� 
			UI_PopupMessage(UI_STRING_MESSAGE_SIEGE_WAR_CHALLENGE_ERROR_1);
			break;
		case NPC_RESPONSE_NOT_ENOUGH_GUILD_MEMBER:  // ������ �����ϴ� 
			UI_PopupMessage(UI_STRING_MESSAGE_SIEGE_WAR_CHALLENGE_ERROR_2);
			break;
		case NPC_RESPONSE_NOT_ENOUGH_GUILD_LEVEL:   // ������ ��� ������ �����ϴ� 
			UI_PopupMessage(UI_STRING_MESSAGE_SIEGE_WAR_CHALLENGE_ERROR_3);
			break;

		case NPC_RESPONSE_NOT_ENTER_SURVIVAL_ZONE:	// �����̹� ���� ���� �Ұ����ϴ�. (���� �Ұ��� �ð�, ���� �ο�)
			UI_PopupMessage(UI_STRING_MESSAGE_NOT_ENTER_SURVIVAL_ZONE);
			break;
			
		case NPC_RESPONSE_GIVE_GAMBLE_ITEM_OK:		// �׺��ؼ� ������ �޾�����
			sprintf(sz_temp, (*g_pGameStringTable)[UI_STRING_MESSAGE_GIVE_GAMBLE_ITEM].GetString(), pPacket->getParameter() );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
		case NPC_RESPONSE_GAMBLE_INIT_OK:			// �׺� �������� �ʱ�ȭ �� ��
			UI_PopupMessage(UI_STRING_MESSAGE_GAMBLE_ACCUMULATION_INIT);
			break;

		case NPC_NOT_ENOUGH_EVENT_ITEM:				// ��ȯ�� �ʿ��� �̺�Ʈ �������� ������ ��
			UI_PopupMessage(UI_STRING_MESSAGE_NOT_ENOUGH_EVENT_ITEM);
			break;
			
		case NPC_NOT_ENOUGH_ITEM:					// ��ȯ�� �ʿ��� �������� ������ ��
			UI_PopupMessage(UI_STRING_MESSAGE_NOT_ENOUGH_ITEM);
			break;

		// 2007 �⼮ üũ �̺�Ʈ
		case NPC_RESPONSE_DENY_ATTEND:					// �ű� ���� ȸ���� �̺�Ʈ�� ���� ���� �մϴ�.
			UI_PopupMessage(UI_STRING_MESSAGE_DENY_ATTEND);
			break;

		case NPC_RESPONSE_TODAY_NOT_ATTEND:				// �̹� �⼮ �ϼ̽��ϴ�. ���� �ٽ� ������ �ּ���.
			UI_PopupMessage(UI_STRING_MESSAGE_TODAY_NOT_ATTEND);
			break;

		case NPC_RESPONSE_CHECK_COUNT_ATTEND:			// [ĳ����]���� [�⼮ üũ ȸ��]�� �⼮�ϼ̽��ϴ�.
			sprintf(sz_temp, (*g_pGameStringTable)[UI_STRING_MESSAGE_CHECK_COUNT_ATTEND].GetString(),
				g_pPlayer->GetName(), value );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;
			
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		case NPC_RESPONSE_BLITZ_COUPON:					// �� ���� ���� ����: %d\n���� �ܿ� ���� ����: %d
			sprintf(sz_temp, (*g_pGameStringTable)[UI_STRING_BLITZ_COUPON].GetString(),
				HIWORD(value), LOWORD(value) );
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
			break;

		case NPC_RESPONSE_REWORD_ITEM_OK:
			int _lo_class = LOWORD(value);
			int _hi_type = HIWORD(value);
			int _InventoryFrameID = -1;

			string str_item_name = "<NULL>";
			
			if( _lo_class<(*g_pItemTable).GetSize() && _hi_type<(*g_pItemTable)[_lo_class].GetSize() )
			{
				str_item_name = "";
				str_item_name += (*g_pItemTable)[_lo_class][_hi_type].HName.GetString();
				str_item_name += "(";
				str_item_name += (*g_pItemTable)[_lo_class][_hi_type].EName.GetString();
				str_item_name += ")";

				_InventoryFrameID = (*g_pItemTable)[_lo_class][_hi_type].InventoryFrameID;
			}
			
			sprintf(sz_temp, (*g_pGameStringTable)[STRING_MESSAGE_REWORD_ITEM_OK].GetString(), str_item_name);

#if __CONTENTS(__DYNAMIC_UI)
			g_pUIDialog->PopupFreeMessageAndItemDlg( sz_temp, _InventoryFrameID );
#else
			g_pUIDialog->PopupFreeMessageDlg( sz_temp );
#endif //__DYNAMIC_UI

			break;
#endif //__BLITZ_COUPON_EVENT
	}
#endif

	__END_CATCH

}