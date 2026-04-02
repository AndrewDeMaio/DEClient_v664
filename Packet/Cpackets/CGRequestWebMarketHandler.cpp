//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestWebMarketHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGRequestWebMarket.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "DB.h"
	#include "Properties.h"

	#include "Gpackets/GCShowWebMarket.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestWebMarketHandler::execute (CGRequestWebMarket* pPacket , Player* pPlayer)
{
	//__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_TRY
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	switch ( pPacket->getCode() )
	{
		case CGRequestWebMarket::REQUEST_WEB_MARKET:
			{
				// Ű ����
				DWORD key = rand() << ( time(0) % 10 ) + rand() >> ( time(0) % 10 );

				cout << "Key: " << key << endl;

				// Ű ����
				Statement* pStmt = NULL;
				Result* pResult = NULL;
				
				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
					pResult = pStmt->executeQuery( "UPDATE WebMarketKey SET Key = %u WHERE PlayerID = '%s'", key, pGamePlayer->getID().c_str() );

					if ( pStmt->getAffectedRowCount() == 0 )
					{
						pStmt->executeQuery( "INSERT INTO WebMarketKey VALUES( '%s', %u )", pGamePlayer->getID().c_str(), key );
					}
				}
				END_DB( pStmt )

				// ����ID �ҷ�����
				static int WorldID = g_pConfig->getPropertyInt("Dimension") * 3 + g_pConfig->getPropertyInt("WorldID");

				// ��Ŷ ����
				GCShowWebMarket gcShowWebMarket;
				gcShowWebMarket.setPlayerID( pGamePlayer->getID() );
				gcShowWebMarket.setName( pPC->getName() );
				gcShowWebMarket.setWorldID( WorldID );
				gcShowWebMarket.setKey( key );

				// ��Ŷ ������
				pGamePlayer->sendPacket( &gcShowWebMarket );
			}
			break;

		case CGRequestWebMarket::REQUEST_BUY_COMPLETE:
			{
				// GoodsObject �� ���� �ε��Ѵ�
				pPC->loadGoods();
			}
			break;

		default:
			break;
	}

#endif	// __GAME_SERVER__
	__END_CATCH	
	//__END_DEBUG_EX __END_CATCH
}

