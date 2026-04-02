//--------------------------------------------------------------------------------
//
// Filename    : GLIncomingConnectionOKHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GLIncomingConnectionOK.h"

#ifdef __LOGIN_SERVER__

	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "Assert.h"

	#include "Lpackets/LCReconnect.h"

#endif

//--------------------------------------------------------------------------------
// 
// GLIncomingConnectionOKHander::execute()
// 
// ���� �����κ��� GLIncomingConnectionOK ��Ŷ�� ���ƿ���, �α��� ������ �� �㰡�� 
// ��� �÷��̾ ���� �㰡���� ã�Ƴ��� �Ѵ�. �� ��, �� �÷��̾�� LCReconnect
// ��Ŷ�� ������� �Ѵ�.
// 
//--------------------------------------------------------------------------------
void GLIncomingConnectionOKHandler::execute ( GLIncomingConnectionOK * pPacket )
{
	__BEGIN_TRY

#ifdef __LOGIN_SERVER__

	try {	

		// �÷��̾� ���̵� ����ؼ� �÷��̾� ��ü�� �����Ѵ�.
		LoginPlayer * pLoginPlayer = g_pLoginPlayerManager->getPlayer( pPacket->getPlayerID() );

		//cout << "PlayerStatus : " << (int)pLoginPlayer->getPlayerStatus() << endl;

		Assert( pLoginPlayer->getPlayerStatus() == LPS_AFTER_SENDING_LG_INCOMING_CONNECTION );

		cout << "+--------------------------------+" << endl
			 << "| Please Reconnect to GameServer |" << endl
			 << "+--------------------------------+" << endl;

        // Ŭ���̾�Ʈ���� ���� ������ �������϶�� �˷��ش�.
        LCReconnect lcReconnect;
        lcReconnect.setGameServerIP( pPacket->getHost() );
        lcReconnect.setGameServerPort( pPacket->getTCPPort() );
        lcReconnect.setKey( pPacket->getKey() );

		// LCReconnect ��Ŷ�� �����Ѵ�.
        pLoginPlayer->sendPacket( &lcReconnect );

		// ������ �����Ѵ�.
		pLoginPlayer->disconnect( UNDISCONNECTED );

		// LPM���� �����Ѵ�.
		g_pLoginPlayerManager->deletePlayer( pLoginPlayer->getSocket()->getSOCKET() );

		// LoginPlayer ��ü�� �����Ѵ�.
		delete pLoginPlayer;

	} catch ( NoSuchElementException & nsee ) {
		cout << "Player not exist or already disconnected" << endl;
	}

#endif
		
	__END_CATCH
}
