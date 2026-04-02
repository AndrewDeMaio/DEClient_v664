//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestRepairInfoHandler.cpp
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGRequestRepairInfo.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "ItemUtil.h"
//	#include "ItemInfo.h"
//	#include "ItemInfoManager.h"
	#include "PriceManager.h"
	#include "ZoneUtil.h"
	#include "Zone.h"

	#include "item/Key.h"

	#include "Gpackets/GCRepairInfo.h"

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairInfoHandler::execute (CGRequestRepairInfo* pPacket , Player* pPlayer)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t ITEMOID = pPacket->getObjectID();

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature *>(pGamePlayer->getCreature());
	
	// ��ȯ������ üũ �ʿ�
	// ���λ��� ������ üũ  �ʿ�

	float fRepairDiscountRate = 0.0f;
	
	if ( pPC->GetTalkingCallNPC() == NULL ) 
	{
		fRepairDiscountRate = 0.0f;
	}
	else
	{
		// GlobalNPC�� ��ȭ���� ���
		
		fRepairDiscountRate = 0.5f;
		
		// ���� NPC ī�� ����
		//pPC->SetParameter<float>("RepairDiscountRate", 0.2f);
		//pPC->SetParameter<float>("RepairDiscountRate", 0.5f);
		string strParamName = "RepairDiscountRate";
		pPC->GetParameter<float>(strParamName, fRepairDiscountRate, 0.0f);		
	}

	
	if (ITEMOID == 0)
	{
		// ObjectID�� 0�̶�� ��� �������� �����ϰ��� �ϴ� ���̴�.
		executeAll(pPacket, pPlayer, fRepairDiscountRate);
	}
	else
	{
		
		Item* pItem = NULL;
		
		pItem = pPC->findItemOID(ITEMOID);

		// �÷��̾ �������� ������ �ִٸ�
		if (pItem != NULL)
		{
			// �� �������� ���� ����Ŭ Ű���...
			if (pItem->getItemClass() == Item::ITEM_CLASS_KEY && pItem->getItemType() == 2)
			{
				executeMotorcycle(pPacket, pPlayer, fRepairDiscountRate);
				
				return;
			}
			else 
			{
				executeNormal(pPacket, pPlayer, fRepairDiscountRate);
			}
		}
	}
	
#endif

__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Ϲ� �������� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairInfoHandler::executeNormal (CGRequestRepairInfo* pPacket , Player* pPlayer, float fRepairDiscountRate)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	ObjectID_t ItemOID = pPacket->getObjectID();
	GamePlayer *pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);	
	PlayerCreature* pPC = dynamic_cast<PlayerCreature *>(pGamePlayer->getCreature());

	Item* pItem = NULL;

	int storage = 0;
	int X = 0;
	int Y = 0;
	
	pItem = pPC->findItemOID(ItemOID, storage, X, Y);
	
	if ( pItem == NULL )
	{
		return;
	}

	if (isRepairableItem(pItem) == false)
	{
		return;
	}

	Price_t repairPrice = 0;
	Price_t repairDiscountPrice = 0;
	
	repairPrice = g_pPriceManager->getRepairPrice(pItem, pPC);
	repairDiscountPrice = repairPrice - (Price_t)(repairPrice * fRepairDiscountRate);

	GCRepairInfo gcRepairInfo;
	gcRepairInfo.SetItemOID(ItemOID);
	gcRepairInfo.SetRepairPrice(repairPrice);
	gcRepairInfo.SetRepairDiscountPrice(repairDiscountPrice);
	
	pPlayer->sendPacket(&gcRepairInfo);

#endif

__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���� ����Ŭ�� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairInfoHandler::executeMotorcycle (CGRequestRepairInfo* pPacket , Player* pPlayer, float fRepairDiscountRate)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// ��Ŷ ������ �̾Ƴ���.
	ObjectID_t      ItemOID     = pPacket->getObjectID();
	GamePlayer *pGamePlayer		= dynamic_cast<GamePlayer*>(pPlayer);	
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature *>(pGamePlayer->getCreature());
	
	Zone*           pZone       = pPC->getZone();
	ZoneCoord_t     CenterX     = pPC->getX();
	ZoneCoord_t     CenterY     = pPC->getY();
	Item*           pItem       = NULL;
	
	pItem = pPC->findItemOID(ItemOID);

	// ���� ���� ������ �˻��ؼ�, ���� ����Ŭ�� �ִ��� Ȯ���Ѵ�.
	for (ZoneCoord_t zx = CenterX-5; zx <= CenterX+5; ++zx)
	{
		for (ZoneCoord_t zy = CenterY-5; zy <= CenterY+5; ++zy)
		{
			if (!isValidZoneCoord(pZone, zx, zy)) continue;

			Tile & tile = pZone->getTile(zx, zy);

			if (tile.hasItem())
			{
				Item* pItemOnTile = tile.getItem();
				Assert(pItemOnTile != NULL);

				// ���� �������� Ÿ�� ���� ���� ���, ���� ����Ŭ���� Ȯ���Ѵ�.
				if (pItemOnTile->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE)
				{
					DWORD    targetID     = dynamic_cast<Key*>(pItem)->getTarget();
					ItemID_t motorcycleID = pItemOnTile->getItemID();

					if (targetID == motorcycleID)
					{
						Price_t repairPrice = 0;
						Price_t repairDiscountPrice = 0;
						
						repairPrice = g_pPriceManager->getRepairPrice(pItemOnTile, pPC);
						repairDiscountPrice = repairPrice - (Price_t)(repairPrice * fRepairDiscountRate);

						GCRepairInfo gcRepairInfo;
						gcRepairInfo.SetItemOID(ItemOID);
						gcRepairInfo.SetRepairPrice(repairPrice);
						gcRepairInfo.SetRepairDiscountPrice(repairDiscountPrice);
						
						pPlayer->sendPacket(&gcRepairInfo);

						return;
					} 
				}
			}
		}
	}
	
#endif
 __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��� ������ �����ϱ�
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairInfoHandler::executeAll(CGRequestRepairInfo* pPacket , Player* pPlayer, float fRepairDiscountRate)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer *pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);	
	PlayerCreature* pPC = dynamic_cast<PlayerCreature *>(pGamePlayer->getCreature());
	
	Price_t repairTotalPrice = 0;
	Price_t repairTotalDiscountPrice = 0;

	// ��� �������� ���� ������ ����Ѵ�.
	for (int i=0; i< pPC->getMaxWearSlotNum(); i++)
	{
		Item* pItem = pPC->getWearItem(i);
		if (pItem != NULL)
		{
			if (i == pPC->getWearPartOfRightHand() && isTwohandWeapon(pItem))
			{
				// �������̰�, ���� ��� �ִ� ���Ⱑ ��� ������...
				// ���� ���ݿ� ���Խ�ų �ʿ䰡 ����.
			}
			else if ( isRepairableItem( pItem ) )
			{
				Price_t repairPrice = 0;
				Price_t repairDiscountPrice = 0;
				
				repairPrice = g_pPriceManager->getRepairPrice(pItem, pPC);
				repairDiscountPrice = repairPrice - (Price_t)(repairPrice * fRepairDiscountRate);
				
				repairTotalPrice += repairPrice;
				repairTotalDiscountPrice += repairDiscountPrice;
			}
		}
	}

	GCRepairInfo gcRepairInfo;
	gcRepairInfo.SetItemOID(0);
	gcRepairInfo.SetRepairPrice(repairTotalPrice);
	gcRepairInfo.SetRepairDiscountPrice(repairTotalDiscountPrice);
	
	pPlayer->sendPacket(&gcRepairInfo);


#endif

__END_CATCH
}
