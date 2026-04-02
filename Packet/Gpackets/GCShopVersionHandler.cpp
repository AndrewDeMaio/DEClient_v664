//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopVersionHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopVersion.h"
#include "ClientDef.h"
#include "MNPC.h"
#include "MShopShelf.h"
#include "ServerInfo.h"
#include "UIFunction.h"
#include "MPriceManager.h"
void GCShopVersionHandler::execute ( GCShopVersion * pPacket , Player * pPlayer )
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
#if __CONTENTS(__GLOBAL_NPC)
		//20081023 �׷ι� NPC�� ���� �κ� npc�� ��ã�� �۷ι� ������ ������츸 ������ ���� ũ��ó�� ���� ����.
		if(pCreature == NULL)// && pPacket->isGlobal())
		{
			(MNPC*) pCreature;
			pCreature = new MNPC;
			pCreature->SetID(pPacket->getNPCID());
			((MNPC*) pCreature)->SetNPCID(pPacket->getNPCID());
		}
#endif //__GLOBAL_NPC
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
			// NPC�� ������ ��´�.
			//------------------------------------------------------
			MShop* pShop = pNPC->GetShop();

			if (pShop==NULL)
			{
				// ������ ���� ��� --> ����.
				pShop = new MShop;
				pShop->Init( MShopShelf::MAX_SHELF );
				
				// NPC�� ���� ����..
				pNPC->SetShop( pShop );				
			}

			//------------------------------------------------------
			// default�� normal ������ �����ϰ� �Ѵ�.
			//------------------------------------------------------
			pShop->SetCurrent( 0 );

			//------------------------------------------------------
			// normal item ������ �����Ѵ�.
			//------------------------------------------------------
			pNPC->CreateFixedShelf();
			pNPC->CreateFixedShelf(true);	// mysterious -_-;


			//------------------------------------------------------
			// �� shelf�� version ��..
			//------------------------------------------------------
			BOOL bSameAll = TRUE;
			for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
			{
				//------------------------------------------------------
				// normal item�� ���� üũ�� �ʿ����. 
				// --> client�� �̹� ������ �����Ƿ�
				//------------------------------------------------------
				if (i!=SHOP_RACK_SPECIAL)
				{
					continue;
				}

				MShopShelf* pShopShelf = pShop->GetShelf( i );

				//------------------------------------------------------
				// ������ ���� ��� --> ����
				//------------------------------------------------------
				if (pShopShelf==NULL)
				{
					pShopShelf = MShopShelf::NewShelf( (MShopShelf::SHELF_TYPE)i );

//20081105 Global_NPC �ϰ��� ������ ������ Ư�������� UI�̰� ������ �ʵ��� �Ѵ�.
//�� �ڵ�ܿ��� GCShopListHandler.cpp�� �۷ι��� ��� ������ �����Ƿ� �ڵ����� �ʴ´�.
//Ȥ ��������� ���� ObjectID�� NULL�� ����ð�� creature �����Ͱ� NULL�Ǿ� �ڵ����� ����ó���ȴ�.
#if __CONTENTS(__GLOBAL_NPC)
					if (pPacket->getObjectID() == NULL)
					{
						pShopShelf->SetDisable();
					}
#endif //__GLOBAL_NPC
					pShop->SetShelf( (MShopShelf::SHELF_TYPE)i, pShopShelf );
					
				}

				unsigned int serverVersion = pPacket->getVersion( i );
				unsigned int clientVersion = pShopShelf->GetVersion();

				//------------------------------------------------------
				// version�� �ٸ��� item std::list�� ��û�Ѵ�.
				//------------------------------------------------------
				if (serverVersion!=clientVersion
#if __CONTENTS(__GLOBAL_NPC)
					&& pPacket->getObjectID() != NULL
#endif //__GLOBAL_NPC					
					)
				{
					// version�� �ٸ� ���� �ִٰ� üũ
					bSameAll = FALSE;

						// item std::list ��û packet
						CGShopRequestList	_CGShopRequestList;
						_CGShopRequestList.setObjectID( pNPC->GetID() );
						_CGShopRequestList.setRackType( i );

						g_pSocket->sendPacket( &_CGShopRequestList );						
				}
			}

			// 2004, 10, 25, sobeit add start - ���� ����
			g_pPriceManager->SetMarketCondSell( pPacket->getMarketCondSell() );
			// 2004, 10, 25, sobeit add end
			
			//------------------------------------------------------
			// ��� shelf�� version�� ������..
			// �ٷ� ������ ����.
			//------------------------------------------------------
			if (bSameAll)
			{
				//------------------------------------------------------
				// ���������� �� ���
				// --> ������ �����Ѵ�.
				//------------------------------------------------------
				UI_RunShop();
				UI_SetShop( pShop );		// shop ����				
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
