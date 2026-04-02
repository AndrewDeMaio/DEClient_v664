//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopListMysteriousHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopListMysterious.h"
#include "ClientDef.h"
#include "MNPC.h"
#include "MShopShelf.h"
#include "MPriceManager.h"
#include "UIFunction.h"

void GCShopListMysteriousHandler::execute ( GCShopListMysterious * pPacket , Player * pPlayer )
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

			//------------------------------------------------------
			// �����۵� �߰�
			//------------------------------------------------------
			for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
			{
				const SHOPLISTITEM_MYSTERIOUS& item = pPacket->getShopItem( i );

				if (item.bExist)
				{
					// item ����
					MItem* pItem = MItem::NewItem( (ITEM_CLASS)item.itemClass );

					//pItem->SetID( item.objectID );
					//pItem->SetItemType( item.itemType );
					//pItem->SetItemOption( item.optionType );
					//pItem->SetCurrentDurability( item.durability );

					pItem->UnSetIdentified();

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
				pNPC->CreateFixedShelf(true);	// mystrious
			}

			//------------------------------------------------------
			// default�� normal ������ �����ϰ� �Ѵ�.
			//------------------------------------------------------
			pShop->SetCurrent( 0 );

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


#endif

	__END_CATCH
}
