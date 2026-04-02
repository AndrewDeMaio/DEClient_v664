//////////////////////////////////////////////////////////////////////
//
// Filename    : GCDeleteandPickUpOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "MQuickSlot.h"
#include "MItem.h"
#include "MInventory.h"
#include "MMoneyManager.h"
#include "MSkillManager.h"
#include "SkillDef.h"
#include "ClientDef.h"

#include "GPacket_PCH.h"
#include "GCDeleteandPickUpOK.h"

#include "TempInformation.h"
#include "UIFunction.h"

#include "ClientPlayer.h"
#include "Cpackets\CGAddMouseToQuickSlot.h"

// Defined in MItem.cpp
bool	IsBombMaterial(const MItem* pItem);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCDeleteandPickUpOKHandler::execute ( GCDeleteandPickUpOK * pPacket, Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	//---------------------------------------------
	// ItemCheckBuffer�� item���
	//---------------------------------------------
	MItem* pItem = g_pPlayer->GetItemCheckBuffer();

	//---------------------------------------------
	// buffer�� ����
	//---------------------------------------------
	MPlayer::ITEM_CHECK_BUFFER	status = g_pPlayer->GetItemCheckBufferStatus();

	//---------------------------------------------
	// item check buffer�� �����ش�.
	//---------------------------------------------
	g_pPlayer->ClearItemCheckBuffer();

	//---------------------------------------------
	// �ֿ� item�� ����? ����..
	//---------------------------------------------
	if (pItem==NULL)
	{
		DEBUG_ADD_FORMAT("[Error] Pickup Item : no item! [ID=%d]", pPacket->getObjectID());
		
		return;
	}

	ITEM_CLASS itemClass = pItem->GetItemClass();

	BOOL bRemoveZoneItem = FALSE;

	//------------------------------------------------------------------------
	// id�� ���� ���..
	//------------------------------------------------------------------------
	if (pItem->GetID() == pPacket->getObjectID())
	{		
		BOOL bSkillCheck = FALSE;

		// �츮�� �����ΰ�� �ٷ� ����
//		if (pItem->GetItemClass()==ITEM_CLASS_RELIC// && 
//				(
//					(pItem->GetItemType() == 0 || pItem->GetItemType() == 1 ) && g_pPlayer->IsSlayer() ||
//					(pItem->GetItemType() == 2 || pItem->GetItemType() == 3 ) && g_pPlayer->IsVampire()
//				)
//			)
//		{
//			// sound
//			PlaySound( pItem->GetTileSoundID() );
//
//			// zone���� ����
//			bRemoveZoneItem = TRUE;
//			//g_pZone->RemoveItem( pItem->GetID() );
//			
//		}

		//------------------------------------------------------------------------
		// �̺�Ʈ�� �������� ���... �����Ѵ�.
		//------------------------------------------------------------------------
//		else 
		if (pItem->GetItemClass()==ITEM_CLASS_SKULL
			&& pItem->GetItemType()>=12 && pItem->GetItemType()<=16)
		{
			// sound
			PlaySound( pItem->GetInventorySoundID() );

			// zone���� ����
			bRemoveZoneItem = TRUE;
			//g_pZone->RemoveItem( pItem->GetID() );
		}
		//------------------------------------------------------------------------
		// ���� �ݴ� ���
		//------------------------------------------------------------------------
		else if (status == MPlayer::ITEM_CHECK_BUFFER_PICKUP_MONEY)
		{
			int lowWord = pItem->GetCurrentDurability();
			int highWord = pItem->GetSilver();
			int money = (highWord << 16) | lowWord;

			// ������ limit���� �ʰ�
			money = min(money, g_pMoneyManager->GetMaxAddMoney());
			
			// �� ����
			g_pMoneyManager->AddMoney( money );

			// sound
			PlaySound( pItem->GetTileSoundID() );

			// zone���� ����
			bRemoveZoneItem = TRUE;
			//g_pZone->RemoveItem( pItem->GetID() );
		}		
		//------------------------------------------------------------------------
		// Item�� Inventory�� �ִ� ���
		//------------------------------------------------------------------------
		else if (status == MPlayer::ITEM_CHECK_BUFFER_PICKUP_TO_INVENTORY)
		{
			const MItem* pOldItem = g_pInventory->GetItem( pItem->GetGridX(), pItem->GetGridY() );

			//------------------------------------------------------------------------
			// �� ������ �߰��Ǵ� ���
			//------------------------------------------------------------------------
			if (pOldItem==NULL)
			{
				//---------------------------------------------
				// item�� inventory�� �ִ´�.
				//---------------------------------------------
				if (g_pInventory->AddItem( pItem, pItem->GetGridX(), pItem->GetGridY() ))
				{		
					bSkillCheck = TRUE;

					// inventory�� �߰����� ��츸 zone���� �����ش�.
					if (g_pZone==NULL)
					{					
						DEBUG_ADD("[Error] Zone is not Init!");
					}
					else
					{
						// �ݴ� �Ҹ��� ����.
						//PlaySound( pItem->GetTileSoundID(),
						//			false,
						//			g_pPlayer->GetX(), g_pPlayer->GetY());

						g_pZone->PickupItem( pItem->GetID() );
					}
				}
				//---------------------------------------------
				// �ƴϸ� ����?? item
				//---------------------------------------------
				else
				{
					// �� �ڸ��� �־��µ� ������ ���..
					DEBUG_ADD_FORMAT("[Error] Pickup Item ID no fit position! ID=%d, xy=(%d, %d)", pItem->GetID(), pItem->GetGridX(), pItem->GetGridY());
				}
			}
			//------------------------------------------------------------------------
			// ������ �ִ� Item�� ���̴� ���
			//------------------------------------------------------------------------
			else
			{
				//--------------------------------------------------------
				// ���� �� �ִ� item���� �ѹ� �� ������ �ش�.
				//--------------------------------------------------------
				if (pOldItem->IsPileItem() && pItem->IsPileItem()
					&& pOldItem->GetItemClass()==itemClass
					&& pOldItem->GetItemType()==pItem->GetItemType())
				{
					bSkillCheck = TRUE;

					//----------------------------------------------------
					// pItem�� pOldItem�� �״´�.
					//----------------------------------------------------
					int total = pOldItem->GetNumber() + pItem->GetNumber();
					if ( total > pOldItem->GetMaxNumber() )
					{
						DEBUG_ADD_FORMAT("[Error] Exceed Item Pile Limit : %d/%d", total, pOldItem->GetMaxNumber());
						
						// max������ �߰��Ѵٰ� �����Ѵ�.
						total = pItem->GetMaxNumber();
					}
					
					//---------------------------------------------
					// OldItem�� ������ �ٲ㼭 �ٽ� �߰��Ѵ�.
					//---------------------------------------------
					MItem* pNewItem = g_pInventory->RemoveItem( pOldItem->GetID() );
					pNewItem->SetNumber( total );
					g_pInventory->AddItem( pNewItem, pItem->GetGridX(), pItem->GetGridY() );

					// item�� ������ �����Ѵ�.
					bRemoveZoneItem = TRUE;
					//g_pZone->RemoveItem( pItem->GetID() );
				}
				//--------------------------------------------------------
				// ���� �� ���� item�� ���
				//--------------------------------------------------------
				else
				{
					DEBUG_ADD_FORMAT("[Error] Cannot Pile Items : inv_item_id=%d, zone_item_id=%d", pItem->GetID(), pOldItem->GetID());
				}
			}
		}
		//---------------------------------------------
		// Item�� Mouse�� ���̴� ���
		//---------------------------------------------
		else if (status == MPlayer::ITEM_CHECK_BUFFER_PICKUP_TO_MOUSE)
		{
			bSkillCheck = TRUE;

			UI_PickUpItem( pItem );

			if (g_pZone==NULL)
			{
				DEBUG_ADD("[Error] Zone is not Init!");
			}
			else
			{				
				// �ݴ� �Ҹ��� ����.
				//PlaySound( pItem->GetTileSoundID(),
				//			false,
				//			g_pPlayer->GetX(), g_pPlayer->GetY());


				g_pZone->PickupItem( pItem->GetID() );
			}
		}
		//------------------------------------------------------------------------
		// Item�� Quickslot�� �ִ� ���
		//------------------------------------------------------------------------
		else if (status == MPlayer::ITEM_CHECK_BUFFER_PICKUP_TO_QUICKSLOT)
		{
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_PICKUP_TO_QUICKSLOT)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);
				int slot = g_pTempInformation->Value1;

				int itemID = pItem->GetID();

				// ��..
				bSkillCheck = TRUE;	
				
				if (g_pZone==NULL)		// �� ���̴� - -;
				{
					DEBUG_ADD("[Error] Zone is not Init!");	// �ᰡ��~
				}
				else 
				{	
					UI_PickUpItem( pItem );

					// zone���� �ݴ´�.
					g_pZone->PickupItem( pItem->GetID() );

					//------------------------------------------
					// �ٽ� Quickslot�� �ִ´�.
					//------------------------------------------
					if (g_pQuickSlot!=NULL&&g_pPlayer->IsSlayer() || g_pPlayer->IsOusters() &&(
						g_pArmsBand1 != NULL || g_pArmsBand2 != NULL ))
					{
						MItem* pQuickItem = NULL ;//= g_pQuickSlot->GetItem( slot );
						MOustersArmsBand* pQuickSlot = NULL;
						
						if( slot >= 3 )
							pQuickSlot = g_pArmsBand2;
						else
							pQuickSlot = g_pArmsBand1;
						
						if( g_pPlayer->IsSlayer() )
							pQuickItem = g_pQuickSlot->GetItem( slot );
						else
							pQuickItem = pQuickSlot->GetItem( slot % 3 );


						bool bSendPacket = false;

						//--------------------------------------------------------
						// �ƹ��͵� ���ٸ� �׳� ������ �ȴ�.
						//--------------------------------------------------------
						if (pQuickItem==NULL)
						{
							// mouse --> quickslot
							UI_DropItem();
							
							if( pQuickSlot!= NULL)
							{
								if( !pQuickSlot->AddItem( pItem, slot %3) )
								{
									DEBUG_ADD_FORMAT("[Error] can't add to quickslot. ousters id=%d, slot=%d", pItem->GetID(), slot);
								}
							}else
							if (!g_pQuickSlot->AddItem( pItem, slot ))
							{
								DEBUG_ADD_FORMAT("[Error] can't add to quickslot. id=%d, slot=%d", pItem->GetID(), slot);
							}

							bSendPacket = true;
						}
						//--------------------------------------------------------
						// ���� �ִ� ���� ���� �� �ִ� ����� ���̴�.
						// �ٽ� �ѹ� �������ش�.
						//--------------------------------------------------------
						else
						{
							if (pQuickItem->GetItemClass()==pItem->GetItemClass()
								&& pQuickItem->GetItemType()==pItem->GetItemType())
							{
								//----------------------------------------------------
								// ���� ������ max�� ���� �ʾƾ� �Ѵ�.
								//----------------------------------------------------
								int addTotal = pQuickItem->GetNumber() + pItem->GetNumber();
								if ( addTotal <= pQuickItem->GetMaxNumber() )
								{
									UI_DropItem();

									delete pItem;	// �������Ƿ� �����Ѵ�.

									pItem = pQuickItem;	// �Ʒ����� pItem�� �����ϱ� ������..
									
									pQuickItem->SetNumber( addTotal );

									bSendPacket = true;
								}
							}
						}

						if (bSendPacket)
						{
							//------------------------------------------
							// �̰Ŵ� �������� �ʾƵ� �ȴ�.
							//------------------------------------------
							CGAddMouseToQuickSlot _CGAddMouseToQuickSlot;
							_CGAddMouseToQuickSlot.setObjectID( itemID );
							_CGAddMouseToQuickSlot.setSlotID( slot );
							
							ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

							pClientPlayer->sendPacket( &_CGAddMouseToQuickSlot );
						}
					}
				}
			}		 
		}
		//---------------------------------------------
		// �ٸ� ���?
		//---------------------------------------------		
		else
		{
			// ����??
			DEBUG_ADD_FORMAT("[Error] ItemCheckBuffer is not Pickup Status [ID=%d]", pItem->GetID());
		}

		//------------------------------------------------------------------
		// ����� ������ ����� ó��..
		//------------------------------------------------------------------
		if (bSkillCheck)
		{
			g_pPlayer->CheckAffectStatus(pItem);

			//------------------------------------------------------------------------
			//
			//							Slayer�� ���
			//
			//------------------------------------------------------------------------
			if (g_pPlayer->IsSlayer())
			{
				switch (itemClass)
				{
					//----------------------------------------------------------
					// ����
					//----------------------------------------------------------
					case ITEM_CLASS_HOLYWATER :
						g_pSkillAvailable->AddSkill( MAGIC_THROW_HOLY_WATER );
					break;

					//----------------------------------------------------------
					// �����̾� ��Ż
					//----------------------------------------------------------
					case ITEM_CLASS_SLAYER_PORTAL_ITEM :
						g_pSkillAvailable->AddSkill( SUMMON_HELICOPTER );
					break;

					//----------------------------------------------------------
					// ��ź/���� ���
					//----------------------------------------------------------
					case ITEM_CLASS_BOMB_MATERIAL :
					{
						// 0~4�� bomb
						// 5~9�� mine -_-;
						/*
						int itemType = pItem->GetItemType();
						if (IsBombMaterial(pItem))
							g_pSkillAvailable->AddSkill( SKILL_MAKE_BOMB );
						else 
							g_pSkillAvailable->AddSkill( SKILL_MAKE_MINE );
						*/
						// SKILL_INSTALL_MINE�� ���� üũ�� �ؾ��Ѵ�. -_-;
						// g_pSkillAvailable�� �� ����� ���� üũ�� �־�δ°� ���ڴ�.
						g_pSkillAvailable->SetAvailableSkills();
					}
					break;

					//----------------------------------------------------------
					// ��ź / ����
					//----------------------------------------------------------
					case ITEM_CLASS_BOMB :
						g_pSkillAvailable->SetAvailableSkills();
						g_pSkillAvailable->AddSkill( (ACTIONINFO)pItem->GetUseActionInfo(), 
													g_pSkillAvailable->IsEnableSkill(SKILL_THROW_BOMB));
					break;

					case ITEM_CLASS_MINE :
						g_pSkillAvailable->SetAvailableSkills();
						g_pSkillAvailable->AddSkill( (ACTIONINFO)pItem->GetUseActionInfo(),
													g_pSkillAvailable->IsEnableSkill(SKILL_INSTALL_MINE));
					break;
				}
			}
			//----------------------------------------------------------
			//
			//					Vampire�� ���
			//
			//----------------------------------------------------------
			else if (g_pPlayer->IsVampire())
			{
				switch (itemClass)
				{
					//----------------------------------------------------------
					// Vampire Portal Item
					//----------------------------------------------------------
					case ITEM_CLASS_VAMPIRE_PORTAL_ITEM :
						if (((MVampirePortalItem*)pItem)->IsMarked())
						{
							if (g_pSkillAvailable->find( MAGIC_BLOODY_TUNNEL ) != g_pSkillAvailable->end())
							{
								g_pSkillAvailable->AddSkill( MAGIC_BLOODY_TUNNEL );
							}
						}
						else
						{
							if (g_pSkillAvailable->find( MAGIC_BLOODY_MARK ) != g_pSkillAvailable->end())
							{
								g_pSkillAvailable->AddSkill( MAGIC_BLOODY_MARK );
							}
						}
					break;

					//----------------------------------------------------------
					// Vampire ETC (���� ������)
					//----------------------------------------------------------
					case ITEM_CLASS_VAMPIRE_ETC :
						if (pItem->GetItemType()==0)
						{
							if (g_pSkillAvailable->find( MAGIC_TRANSFORM_TO_WOLF ) != g_pSkillAvailable->end())
							{
								g_pSkillAvailable->AddSkill( MAGIC_TRANSFORM_TO_WOLF );
							}
						} 
						else if (pItem->GetItemType()==1)
						{
							if (g_pSkillAvailable->find( MAGIC_TRANSFORM_TO_BAT ) != g_pSkillAvailable->end())
							{
								g_pSkillAvailable->AddSkill( MAGIC_TRANSFORM_TO_BAT );
							}
						}
					break;
				}
			}
		}

		//---------------------------------------------
		// Zone���� Item�� �����ؾ��ϴ� ���
		//---------------------------------------------
		if (bRemoveZoneItem)
		{
			g_pZone->RemoveItem( pItem->GetID() );
		}
	}
	//---------------------------------------------
	// id�� �ٸ� ���.. ����?? - -;;
	//---------------------------------------------
	else
	{
		DEBUG_ADD_FORMAT("[Error] Pickup Item ID conflict (%d != %d)", pItem->GetID(), pPacket->getObjectID());
	}

//	__BEGIN_HELP_EVENT
		if(itemClass == ITEM_CLASS_BELT)
			ExecuteHelpEvent( HELP_EVENT_GET_BELT );
		else
			ExecuteHelpEvent( HELP_EVENT_GET_ITEM );
//	__END_HELP_EVENT

//	__BEGIN_HELP_EVENT
//		if (status == MPlayer::ITEM_CHECK_BUFFER_PICKUP_MONEY)
//		{
//			// [����] ������ �ֿ� ��
//			ExecuteHelpEvent( HE_ITEM_PICKUP_MONEY );	
//		}
//		else
//		{
//			// [����] ������ �ֿ� ��
//			ExecuteHelpEvent( HE_ITEM_PICKUP );	
//		}
//	__END_HELP_EVENT


#endif

	__END_CATCH
}
