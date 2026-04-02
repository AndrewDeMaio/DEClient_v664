//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopMarketConditionHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopMarketCondition.h"
#include "ClientDef.h"
#include "MNPC.h"
#include "MShopShelf.h"
#include "MShop.h"
#include "MPriceManager.h"
#include "UIFunction.h"

void GCShopMarketConditionHandler::execute ( GCShopMarketCondition * pPacket , Player * pPlayer )
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
		int objectID = pPacket->getObjectID();
		MCreature* pCreature = g_pZone->GetCreature(objectID);

		//20081023 �׷ι� NPC�� ���� �κ� npc�� ��ã�� �۷ι� ������ ������츸 ������ ���� ũ��ó�� ���� ����.
		if(pCreature == NULL && objectID == 0)
		{
			(MNPC*) pCreature;
			pCreature = new MNPC;
		}

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
			// ������ �д´�.
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
				//pNPC->CreateFixedShelf();
			}

			//------------------------------------------------------
			// ������ ���� ���� 
			//------------------------------------------------------
			g_pPriceManager->SetMarketCondBuy( pPacket->getMarketCondBuy() );
			g_pPriceManager->SetMarketCondSell( pPacket->getMarketCondSell() );
			
			//------------------------------------------------------
			// �ȱ� ���ؼ� inventory�� ����.
			//------------------------------------------------------
			UI_OpenInventoryToSell();

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
