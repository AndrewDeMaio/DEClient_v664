//--------------------------------------------------------------------------------
//
// Filename    : GCCreateItemHandler.cpp
// Written By  : elca
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCCreateItem.h"
#include "ClientDef.h"
#include "MInventory.h"
#include "UIFunction.h"
#include "VS_UI_GameCommon.h"
#include "VS_UI.h"
extern int g_C2G;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCCreateItemHandler::execute ( GCCreateItem * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
#if __CONTENTS(__PCITEMINFO)
	PCItemInfo* pPCItemInfo = pPacket->GetPCItemInfo();
#else //__PCITEMINFO
	GCCreateItem* pPCItemInfo =  pPacket;
#endif //__PCITEMINFO

	MItem* pItem;
	MSubInventory* pSubInventory = NULL;
	bool bSubInventoryUse = false;

	
	//---------------------------------------------------------------------
	// inventory���� item��� ��� ���..
	//---------------------------------------------------------------------
	if (g_pPlayer->IsItemCheckBufferPickupSomeFromInventory())
	{
		MItem* pItem = g_pPlayer->GetItemCheckBuffer();
		g_pPlayer->ClearItemCheckBuffer();		

		if (pItem!=NULL)
		{
			// ���� �ϴ� item�� ������
			// ( ���� ���� - �ٴڿ� ���� ���� ) �̴�.
			int numPickup = pItem->GetNumber() - pPCItemInfo->getItemNum();
			
			// inventory���� �����Ѵ�.
			//pSubInventory = (MSubInventory*)gC_vs_ui.GetSubInventoryItem();

			MItem* pRemovedItem;
			if(pPacket->getInventoryItemObjectID())
			{
				pSubInventory = dynamic_cast<MSubInventory*>(pItem->GetParentInventory());
				pRemovedItem = pSubInventory->RemoveItem( pItem->GetGridX(), pItem->GetGridY() );
				bSubInventoryUse = true;
			}
			else
			{
				pRemovedItem = g_pInventory->RemoveItem( pItem->GetGridX(), pItem->GetGridY() );
				bSubInventoryUse = false;
			}
//			MItem* pRemovedItem = g_pInventory->RemoveItem( pItem->GetGridX(), pItem->GetGridY() );

			if (pRemovedItem==pItem)
			{
				// ������ �ٽ� �������ش�.
				pItem->SetNumber( numPickup );

				// mouse�� ���.
				UI_PickUpItem( pItem );
			}
			else
			{
				DEBUG_ADD("[Error] PickupPart item Wrong");
			}
		}
		else
		{
			DEBUG_ADD("[Error] PickupPart item NULL");
		}
	}

	//---------------------------------------------------------------------
	// Item�� �����Ѵ�.
	//---------------------------------------------------------------------
	pItem = MItem::NewItem( (enum ITEM_CLASS)pPCItemInfo->getItemClass() );
	pItem->SetItemType( pPCItemInfo->getItemType() );
	pItem->SetItemOptionList( pPCItemInfo->getOptionType() );
#if __CONTENTS(__PET_MIXINGFORGE)
	pItem->SetPetMixingOptionList(pPCItemInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE

	pItem->SetID( pPCItemInfo->getObjectID() );		

	pItem->SetCurrentDurability( pPCItemInfo->getDurability() );

	//pItem->SetNumber( pPacket->getItemNum() );

	pItem->SetGrade( pPCItemInfo->getGrade() );
	pItem->SetEnchantLevel( pPCItemInfo->getEnchantLevel() );
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	pItem->SetCashItem(pPCItemInfo->getCashItem());
#endif //__INTERNATIONAL_PREMIUM_SYSTEM
//20071009 by diesirace ��������ۿɼ� �߰� (���� �ɼ� �޸� �������� ����������� ���� ���ܴ�...)
#if __CONTENTS(__PCITEMINFO)
	pItem->SetItemThirdOptionList(pPCItemInfo->getThirdOptionType() );
	pItem->SetItemThirdOptionType(pPCItemInfo->getThirdEnchantType());
#endif //__PCITEMINFO
	//------------------------------------------
	// ����
	//------------------------------------------
	// ���� ���
	//------------------------------------------
	if (pItem->IsGunItem())
	{
		MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

		// �ǹ� ���� - -;
		pMagazine->SetID( 0 );

		// �̰Ŵ� �ѿ� ���缭 ����ߵȴ�.
		for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
		{
			pMagazine->SetItemType(	j );

			if (pMagazine->IsInsertToItem( pItem ))
			{
				break;
			}
		}

		// �ǹ� ����
		pMagazine->ClearItemOption();
	
		// źâ ����
		pMagazine->SetNumber( pPCItemInfo->getItemNum() );

		//------------------------------------
		// źâ ����
		//------------------------------------
		MGunItem* pGunItem = (MGunItem*)pItem;
		pGunItem->SetMagazine( pMagazine );
	}		
	//------------------------------------------
	// ���� �ƴ� ���
	//------------------------------------------
	//20080220 ���� �������� �������� ��þƮ ������ �޴´�.
	else if(pItem->IsChargeItem())
		pItem->SetNumber( pPCItemInfo->getEnchantLevel() );
	else
	{
		pItem->SetNumber( pPCItemInfo->getItemNum() );
		//pItem->SetSilver( item.silver );
	}
	//20081219 Ʈ������ ����� ���� �Ҽ� �ְ� �Ѵ�. 
	int TreeSizeX = 3,TreeSizeY = 4;
#if __CONTENTS(__CHRISTMAS_SOCKS_EVENT)	
	if(pItem->GetItemClass() == ITEM_CLASS_EVENT_GIFT_BOX
		&& pItem->GetNumber() == 1	&& (pItem->GetItemType() == 39))
	{
		TreeSizeY = 3;
	}
#endif //__CHRISTMAS_SOCKS_EVENT


	// ũ�������� Ʈ�� ��ü
	if(pItem->GetItemClass() == ITEM_CLASS_EVENT_TREE 
#if __CONTENTS(__EVENTTREE_PILE)
		&& pItem->GetNumber() == 1
#endif //__EVENTTREE_PILE
		&&
	   (pItem->GetItemType() == 12 ||
		pItem->GetItemType() == 25 ||
		pItem->GetItemType() == 41 ||
		pItem->GetItemType() == 54		// ������ ����� 2006.11.30 by chyaya
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		|| pItem->GetItemType() == 67	// ������ ���� 2008.8.29 by ij-ch
#endif //__BLITZ_COUPON_EVENT
#if __CONTENTS(__2008_AUTUMN_LEAVES_EVENT)
		|| pItem->GetItemType() == 80	// ���� ���� 2008.8.29 by ij-ch
#endif //__2008_AUTUMN_LEAVES_EVENT
		)
#if __CONTENTS(__CHRISTMAS_SOCKS_EVENT)
		|| pItem->GetItemClass() == ITEM_CLASS_EVENT_GIFT_BOX
		&& pItem->GetNumber() == 1	&&
		(
		pItem->GetItemType() == 39
		)
#endif //__CHRISTMAS_SOCKS_EVENT
		)
	{
		if(g_pPlayer->GetItemCheckBufferStatus() == MPlayer::ITEM_CHECK_BUFFER_TREE_MERGE)
		{
			for(int y = 0; y < TreeSizeY; y++)
			{
				for(int x = 0; x < TreeSizeX; x++)
				{
					MItem *pPartOfTree = g_pInventory->GetItem(x+pPacket->getInvenX(), y+pPacket->getInvenY());
					if(pPartOfTree != NULL && 
						pPartOfTree->GetItemClass() == ITEM_CLASS_EVENT_TREE 
#if __CONTENTS(__EVENTTREE_PILE)
						&& pPartOfTree->GetNumber() == 1
#endif //__EVENTTREE_PILE
						&&
						(pPartOfTree->GetItemType() == y*TreeSizeX+x		||
						 pPartOfTree->GetItemType() == y*TreeSizeX+x + 13	||
						 pPartOfTree->GetItemType() == y*TreeSizeX+x + 29	||
						 pPartOfTree->GetItemType() == y*TreeSizeX+x + 42
#if __CONTENTS(__BLITZ_COUPON_EVENT)
						|| pPartOfTree->GetItemType() == y*TreeSizeX+x + 55
#endif //__BLITZ_COUPON_EVENT
#if __CONTENTS(__2008_AUTUMN_LEAVES_EVENT)
						|| pPartOfTree->GetItemType() == y*TreeSizeX+x + 68
#endif //__2008_AUTUMN_LEAVES_EVENT
#if __CONTENTS(__CHRISTMAS_SOCKS_EVENT)
						|| pPartOfTree->GetItemType() == y*TreeSizeX+x + 81
#endif //__CHRISTMAS_SOCKS_EVENT
						))
					{
						g_pInventory->RemoveItem(x+pPacket->getInvenX(), y+pPacket->getInvenY());
						delete pPartOfTree;
					}
				}
			}
			g_pPlayer->ClearItemCheckBuffer();
		}
		else
		{
			DEBUG_ADD("[GCCreateItemHandler] ItemCheckBuffer != ITEM_CHECK_BUFFER_TREE_MERGE");
		}
	}

	//---------------------------------------------------------------------
	// inventory�� �߰��Ѵ�.
	//---------------------------------------------------------------------

	if(bSubInventoryUse)
	{
		pSubInventory->AddItem( pItem, pPacket->getInvenX(), pPacket->getInvenY());
	}
	else
	{
		
		if (g_pInventory->AddItem( pItem, pPacket->getInvenX(), pPacket->getInvenY() ))
		{
			if( g_C2G > 0 )
			{
				C_VS_UI_INVENTORY::AutoMove( pPacket->getInvenX(), pPacket->getInvenY() );
				gpC_base->DispatchMessage();
				gpC_base->DispatchMessage();
				gpC_base->DispatchMessage();
				gpC_base->DispatchMessage();
				gpC_base->DispatchMessage();
				gpC_base->DispatchMessage();
				g_C2G--;
			}
			// ����� �߰��� ���..
		}
		
		else
		{
			DEBUG_ADD_FORMAT("[Error] Cannot Create Item to inventory: id=%d, tp=%d, xy=(%d,%d)", (int)pItem->GetID(), (int)pItem->GetItemType(), (int)pPacket->getInvenX(), (int)pPacket->getInvenY());
			
			delete pItem;
		}
	}


#endif

	__END_CATCH
}
