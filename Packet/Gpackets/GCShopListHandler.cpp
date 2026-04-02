//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopListHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopList.h"
#include "ClientDef.h"
#include "MShopShelf.h"
#include "MNPC.h"
#include "MPriceManager.h"
#include "UIFunction.h"

void GCShopListHandler::execute ( GCShopList * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
	}
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		//------------------------------------------------------
		// �׷� creature�� ���� ���
		//------------------------------------------------------
		if (pCreature==NULL)
		{
			DEBUG_ADD_FORMAT("[Error] There is no such Creature id=%d", pPacket->getObjectID());
		}
		//------------------------------------------------------
		// NPC�� ���
		//------------------------------------------------------
		else if (pCreature->GetClassType()==MCreature::CLASS_NPC)
		{
			MNPC* pNPC = (MNPC*)pCreature;

			//------------------------------------------------------
			// ���ο� Shelf�� �����Ѵ�.
			//------------------------------------------------------
			MShopShelf* pShelf = MShopShelf::NewShelf( (MShopShelf::SHELF_TYPE)pPacket->getShopType() );
			
			pShelf->SetVersion( pPacket->getShopVersion() );
			pShelf->SetEnable();
			//------------------------------------------------------
			// �����۵� �߰�
			//------------------------------------------------------
			for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
			{
				const SHOPLISTITEM& item = pPacket->getShopItem( i );

				if (item.bExist)
				{
					// item ����
					MItem* pItem = MItem::NewItem( (ITEM_CLASS)item.itemClass );

					pItem->SetID( item.objectID );
					pItem->SetItemType( item.itemType );
					pItem->SetItemOptionList( item.optionType );
					pItem->SetCurrentDurability( item.durability );
					pItem->SetSilver( item.silver );
					pItem->SetGrade( item.grade );
					pItem->SetEnchantLevel( item.enchantLevel );
					
					// Shelf�� item�߰�
					pShelf->SetItem( i, pItem );
				}
			}

			//------------------------------------------------------
			//
			// NPC�� ������ shelf�� �߰��Ѵ�.
			//
			//------------------------------------------------------
			MShop* pShop = pNPC->GetShop();

			if (pShop==NULL)
			{
				// ������ �������� �����Ѵ�.
				pShop = new MShop;
				pShop->Init( MShopShelf::MAX_SHELF );

				// NPC�� ���� ����
				pNPC->SetShop( pShop );

				// normal item ������ �����Ѵ�.
				pNPC->CreateFixedShelf();
				pNPC->CreateFixedShelf(true);	// mysterious -_-;
			}

			//------------------------------------------------------
			// ������ ���� ����
			//------------------------------------------------------
			pShop->SetShopType( (MShop::SHOP_TYPE)pPacket->getNPCShopType() );

			//------------------------------------------------------
			// default�� normal ������ �����ϰ� �Ѵ�.
			//------------------------------------------------------
			if (pShop->GetShopType()==MShop::SHOP_EVENT_STAR)
			{
				pShop->SetCurrent( 1 );
			}
			else
			{			
				pShop->SetCurrent( 0 );
			}

			//------------------------------------------------------
			// ������ ���� ���� 
			//------------------------------------------------------
			g_pPriceManager->SetMarketCondBuy( pPacket->getMarketCondBuy() );
			g_pPriceManager->SetMarketCondSell( pPacket->getMarketCondSell() );			
			
			//------------------------------------------------------
			// ������ ���� ����
			//------------------------------------------------------
			pShop->SetShelf( pShelf->GetShelfType(), pShelf );

			//------------------------------------------------------
			// ���������� �� ���
			// --> ������ �����Ѵ�.
			//------------------------------------------------------
			UI_SetShop( pShop );		// shop ����
			UI_RunShop();
			UI_SetShop( pShop );		// shop ����
		}
		//------------------------------------------------------
		// NPC�� �ƴ� ���
		//------------------------------------------------------
		else
		{
			DEBUG_ADD_FORMAT("[Error] The Creature is Not NPC. id=%d", pPacket->getObjectID());
		}
	}
//	__BEGIN_HELP_EVENT
		ExecuteHelpEvent( HELP_EVENT_USE_SHOP );
//	__END_HELP_EVENT
#endif

	__END_CATCH
}
