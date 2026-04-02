//////////////////////////////////////////////////////////////////////
//
// Filename    : GCReconnectHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCReconnect.h"
#include "Assert.h"

#ifdef __GAME_SERVER__
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCReconnectHandler::execute ( GCReconnect * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_SERVER__


#endif
		
	__END_CATCH
}

/*

	// �� �ڵ�� ���� �������� ����Ǿ�� �ϴ� �ڵ��̴�. �� Ư�� ����ڰ�
	// ���� ��Ż���� �ö��� ��, �� ��Ż�� �������� �ٸ� ������ ��� 
	// 
	try {

		// �ϴ� ũ��ó�� ����Ÿ���̽��� �����ϰ�, ������ �����ؾ� �Ѵ�.
		Creature * pCreature = pPlayer->getCreature();
		// g_pDatabaseManager->saveCreature(pCreature);
		Zone * pZone = pCreature->getZone();
		Tile & tile = pZone->getTile( pCreature->getX() , pCreature->getY() );
		tile.deleteCreature( pCreature->getMoveMode() );

		// �÷��̾� ��ü�� ���׷��� �÷��̾�Ŵ������� �����Ѵ�.
		ZoneGroup * pZoneGroup = pZone->getZoneGroup();
		ZonePlayerManager * pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		pZonePlayerManager->deletePlayer( pPlayer->getSocket()->getSOCKET() );

		// �÷��̾�� GCReconnect ��Ŷ�� ������.
		GCReconnect gcReconnect;
		gcReconnect.setServerIP( ... );
		gcReconnect.setKey( ... );
		pPlayer->sendPacket( &gcReconnect);

		// ��.. �÷��ð� �Ǵ°�.. �ּ��� ���۴� �÷����ϰ����� ������ ����� �Ѵ�.
		pPlayer->flush();

		// ������ �����ϰ�, �÷��̾� ��ü�� �����Ѵ�. 
		delete pPlayer;

	} catch ( NoSuchElementException & nsee ) {

		// �߸��� ��Ŷ�̶�� �Ҹ���. �� IncomingPlayer ���°� �ƴ϶�� ��.
		// �� ��ŷ�� ���ؼ� ���ƿ� ��Ŷ�̹Ƿ�, Ban Manager �� ����ϰ�, ������ �����Ѵ�.
		// �ϴ��� ������ �����Ѵ�.
		throw Error( nsee.toString() );

	}
*/	
