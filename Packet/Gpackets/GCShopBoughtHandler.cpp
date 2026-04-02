//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopBoughtHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopBought.h"
#include "ClientDef.h"
#include "MNPC.h"
#include "MShop.h"
#include "MShopShelf.h"

void GCShopBoughtHandler::execute ( GCShopBought * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	// shop�� ������ ����
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

			MShop* pShop = pNPC->GetShop();

			if (pShop==NULL)
			{
				//------------------------------------------------------
				// shop�� ���ٸ�..
				// item�� �߰� ��ų �ʿ䰡 ����.
				//------------------------------------------------------
			}
			else
			{
				//------------------------------------------------------
				// ���ο� �������� �����ؼ� �߰��ؾ� �Ѵ�.
				//------------------------------------------------------
				MShopShelf* pShopShelf = pShop->GetShelf( pPacket->getShopType() );

				if (pShopShelf==NULL)
				{
					DEBUG_ADD_FORMAT("[Error] There is no Shelf type=%d", (int)pPacket->getShopType());
				}
				else
				{
					// version ����
					pShopShelf->SetVersion( pPacket->getShopVersion() );

					// ���ο� item ����
					MItem* pItem = MItem::NewItem( (ITEM_CLASS)pPacket->getItemClass() );

					pItem->SetID( pPacket->getItemObjectID() );
					pItem->SetItemType( pPacket->getItemType() );
					pItem->SetItemOptionList( pPacket->getOptionType() );
					pItem->SetCurrentDurability( pPacket->getDurability() );
					pItem->SetSilver( pPacket->getSilver() );
					pItem->SetGrade( pPacket->getGrade() );
					pItem->SetEnchantLevel( pPacket->getEnchantLevel() );

					// ������ item�� shop�� �߰�
					if (!pShopShelf->SetItem( pPacket->getShopIndex(), pItem ))
					{
						DEBUG_ADD("[Error] Cannot Add Item to ShopShelf");
						
						delete pItem;
					}
				}
			}

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
