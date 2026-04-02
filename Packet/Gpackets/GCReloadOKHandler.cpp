//////////////////////////////////////////////////////////////////////
//
// Filename    : GCReloadOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCReloadOK.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "MInventory.h"
#include "MQuickSlot.h"
#include "UIFunction.h"
#include "VS_UI.h"

#define SAFE_DELETE(x)		{ if(x!=NULL) delete x; x=NULL; }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCReloadOKHandler::execute ( GCReloadOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__
	// message

	//------------------------------------------------------------------
	// Slayer�� ��츸 ����Ǵ� packet�̴�.
	//------------------------------------------------------------------
	if (g_pPlayer->IsVampire())
	{
		DEBUG_ADD("[Error] Player is Vampire. No Effect!");

		return;
	}

	// ��.. cut & paste�� ����.. - -;;

	//------------------------------------------------------------------
	//
	//				Item Check Buffer Ȯ��
	//
	//------------------------------------------------------------------	
	MItem* pItem = g_pPlayer->GetItemCheckBuffer();

	//----------------------------------------------------
	// Check Buffer�� item�� �ִ� ���
	//----------------------------------------------------
	if (pItem!=NULL)
	{
		PlaySound( pItem->GetUseSoundID() );

		MPlayer::ITEM_CHECK_BUFFER status =	g_pPlayer->GetItemCheckBufferStatus();

		//----------------------------------------------------
		// Inventory���� ���
		//----------------------------------------------------
		if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY)			
		{
			// Item Check Buffer�� �����.
			g_pPlayer->ClearItemCheckBuffer();

			//----------------------------------------------------
			// MAGAZINE
			//----------------------------------------------------
			if (pItem->GetItemClass()==ITEM_CLASS_MAGAZINE)
			{
				MMagazine* pMagazineItem;

				//-------------------------------------------------
				// ���� üũ�� �ؾ��Ѵ�.
				//-------------------------------------------------
				if (pItem->GetNumber()>1)
				{
					// ���� ������ �� ���� �ִ� ���,
					// ������ �ϳ� �ٿ��ش�.
					pItem->SetNumber( pItem->GetNumber() - 1 );

					//-------------------------------------------------
					// ���ο� źâ�� �����ؼ� �ѿ� �߰��ؾ� �Ѵ�.
					//-------------------------------------------------
					pMagazineItem = (MMagazine*)MItem::NewItem( ITEM_CLASS_MAGAZINE );

					pMagazineItem->SetID( 0 );	// ������ ID.. ������� ���� ��.. 
					pMagazineItem->SetItemType( pItem->GetItemType() );
					pMagazineItem->SetItemOptionList( pItem->GetItemOptionList() );
				}
				//-------------------------------------------------
				// �� ����� ��� --> �����Ѵ�.
				//-------------------------------------------------
				else
				{
					// inventory���� ����
					g_pInventory->RemoveItem( pItem->GetID() );

					// memory���� �����ϸ� �ȵȴ� --> �ѿ� ���Ƿ�..
					//delete pItem;	
					
					pMagazineItem = (MMagazine*)pItem;
				}

				
				//----------------------------------------------------
				// �Ѿ� ������ �ٽ� �����Ѵ�.
				//----------------------------------------------------
				// Magazine.GetNumber()
				//
				// źâ���� ���� ���� źâ ���� ����
				// �ѿ� ��� ���� �� Number�� �Ѿ��� ����.
				//----------------------------------------------------
				pMagazineItem->SetNumber( pPacket->getBulletNum() );

				// Slayer�� ��츸 �����ϴ�.
				const MItem* pRightHandItem = g_pSlayerGear->GetItem( (MSlayerGear::GEAR_SLAYER)MSlayerGear::GEAR_SLAYER_RIGHTHAND );

				//----------------------------------------------------
				// �����տ� ���� ��� �ִ� ����̸�
				//----------------------------------------------------
				if (pRightHandItem!=NULL)
				{
					if (pRightHandItem->IsGunItem())
					{
						MGunItem* pGunItem = (MGunItem*)pRightHandItem;

						// źâ ����
						MMagazine* pOldMagazine = pGunItem->SetMagazine( pMagazineItem );

						// ������ źâ ����
						g_pCurrentMagazine = pMagazineItem;

						// ������ �ִ� źâ�� ������ �����Ѵ�.
						if (pOldMagazine!=NULL)
						{
							DEBUG_ADD("Delete Old Magazine");
							
							delete pOldMagazine;
						}
					}									
				}
				//----------------------------------------------------
				// ���� �ƴ� ��� --> Error��..
				//----------------------------------------------------
				else
				{
					DEBUG_ADD_FORMAT("[Error] Player not Use GUN. the ItemClass=%d", (int)pRightHandItem->GetItemClass());
					
					// inventory���� ����
					g_pInventory->RemoveItem( pItem->GetID() );

					// item���� ���� - �ǹ������� - -;
					UI_RemoveDescriptor( (void*)pItem );

					delete pItem;
				}
			}
			//----------------------------------------------------
			// źâ�� �ƴϸ� ������.
			//----------------------------------------------------
			else
			{
				DEBUG_ADD_FORMAT("[Error] Item is Not Magazine: the ItemClass=%d", (int)pItem->GetItemClass());
			}
		}
		//----------------------------------------------------
		// QuickSlot���� ���
		//----------------------------------------------------
		else if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT)
		{
			// Item Check Buffer�� �����.
			g_pPlayer->ClearItemCheckBuffer();

			//----------------------------------------------------
			// MAGAZINE
			//----------------------------------------------------
			if (pItem->GetItemClass()==ITEM_CLASS_MAGAZINE)
			{
				MMagazine* pMagazineItem;

				//-------------------------------------------------
				// ���� üũ�� �ؾ��Ѵ�.
				//-------------------------------------------------
				if (pItem->GetNumber()>1)
				{
					// ���� ������ �� ���� �ִ� ���,
					// ������ �ϳ� �ٿ��ش�.
					pItem->SetNumber( pItem->GetNumber() - 1 );

					//-------------------------------------------------
					// ���ο� źâ�� �����ؼ� �ѿ� �߰��ؾ� �Ѵ�.
					//-------------------------------------------------
					pMagazineItem = (MMagazine*)MItem::NewItem( ITEM_CLASS_MAGAZINE );

					pMagazineItem->SetID( 0 );	// ������ ID.. ������� ���� ��.. 
					pMagazineItem->SetItemType( pItem->GetItemType() );
					pMagazineItem->SetItemOptionList( pItem->GetItemOptionList() );					
				}
				//-------------------------------------------------
				// �� ����� ��� --> �����Ѵ�.
				//-------------------------------------------------
				else
				{
					// �������� �� ������� ��� ���� �������� �κ��丮�� �ִٸ� ���������� �ű��.
					MItem* pNextItem	= g_pInventory->FindItem(pItem->GetItemClass(), pItem->GetItemType());
					BYTE nItemSlot		= pItem->GetItemSlot();

					// QuickSlot���� ����
					g_pQuickSlot->RemoveItem( pItem->GetID() );

					if(pNextItem != NULL)
						gC_vs_ui.AutoMoveInventoryItemToQuickSlot(
							pNextItem->GetGridX(), pNextItem->GetGridY(), nItemSlot);	// ���������� ����

					// memory���� �����ϸ� �ȵȴ� --> �ѿ� ���Ƿ�..
					//delete pItem;	
					
					pMagazineItem = (MMagazine*)pItem;
				}

				//----------------------------------------------------
				// �Ѿ� ������ �ٽ� �����Ѵ�.
				//----------------------------------------------------
				pMagazineItem->SetNumber( pPacket->getBulletNum() );

				// Slayer�� ��츸 �����ϴ�.
				const MItem* pRightHandItem = g_pSlayerGear->GetItem( (MSlayerGear::GEAR_SLAYER)MSlayerGear::GEAR_SLAYER_RIGHTHAND );

				//----------------------------------------------------
				// �����տ� ���� ��� �ִ� ����̸�
				//----------------------------------------------------
				if (pRightHandItem!=NULL)
				{
					if (pRightHandItem->IsGunItem())
					{
						MGunItem* pGunItem = (MGunItem*)pRightHandItem;

						// źâ ����
						MMagazine* pOldMagazine = pGunItem->SetMagazine( pMagazineItem );

						// ������ źâ ����
						g_pCurrentMagazine = pMagazineItem;

						// ������ �ִ� źâ�� ������ �����Ѵ�.
						if (pOldMagazine!=NULL)
						{
							DEBUG_ADD("Delete Old Magazine");
							
							delete pOldMagazine;
						}
					}									
				}
				//----------------------------------------------------
				// ���� �ƴ� ��� --> Error��..
				//----------------------------------------------------
				else
				{
					DEBUG_ADD_FORMAT("[Error] Player not Use GUN. the ItemClass=%d", (int)pRightHandItem->GetItemClass());
					
					// QuickSlot���� ����
					g_pQuickSlot->RemoveItem( pItem->GetID() );

					SAFE_DELETE( pItem );					
				}
			}
			//----------------------------------------------------
			// źâ�� �ƴϸ� ������.
			//----------------------------------------------------
			else
			{
				DEBUG_ADD_FORMAT("[Error] Item is Not Magazine: the ItemClass=%d", (int)pItem->GetItemClass());
			}
		}
		//----------------------------------------------------
		// �ٸ� ����??
		//----------------------------------------------------
		else
		{
			DEBUG_ADD_FORMAT("[Error] ItemCheck Buffer is not Use Status: status=%d", (int)status);
			
			return;
		}

		// ���Ѿ� ������... ������ ���.. �ٽ� ���..
		g_pPlayer->CalculateStatus();

	}
	//----------------------------------------------------
	// item�� ���� ���.. - -;;
	//----------------------------------------------------
	else
	{
		DEBUG_ADD("[Error] No Item in CheckBuffer");
		
		return;
	}


#endif

	__END_CATCH
}
