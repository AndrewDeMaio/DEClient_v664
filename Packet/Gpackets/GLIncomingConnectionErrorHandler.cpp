//--------------------------------------------------------------------------------
//
// Filename    : GLIncomingConnectionErrorHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GLIncomingConnectionError.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "Assert.h"
#endif

//--------------------------------------------------------------------------------
// 
// GLIncomingConnectionErrorHander::execute()
// 
//--------------------------------------------------------------------------------
void GLIncomingConnectionErrorHandler::execute ( GLIncomingConnectionError * pPacket )
{
	__BEGIN_TRY

#ifdef __LOGIN_SERVER__

	// �α��� �÷��̾ �����Ѵ�.
	//
	// *CAUTION*
	//
	// �̷� ���� ����� ������ �ִ�. �α��� �÷��̾� �Ŵ����� �� �÷��̾ ó���ϰ� ����
	// ���, �Ʒ��� ���� ������ ������ ������.. - -; ����.. �̷��� �Ǹ� setPlayerStatus()
	// ���� ��ŷ �������� ������ �ϴ°�..  �ϴ��� �̷��� ����.. (���� �Է��� ���� ���̹Ƿ�
	// ó�������� �ʴ´�..)
	//
	// ������ ����, �Է����� �����̷����ϴ� ���� �Ұ����ϴٴ� ���̴�. �ֳ��ϸ�, �����̷���
	// �������� �Է� ���ۿ� ��Ŷ�� �� ���ܼ� ���Դٴ� ���� �� �� ���� �����̴�. 
	//
	try {
		LoginPlayer * pLoginPlayer = g_pLoginPlayerManager->getPlayer( pPacket->getPlayerID() );
	
		Assert( pLoginPlayer->getPlayerStatus() == LPS_AFTER_SENDING_LG_INCOMING_CONNECTION );

		// �� �÷��̾��� �α����� ���������Ƿ� ������ �����Ѵ�.
		cout << "Fail to join game server...(" << pPacket->getPlayerID() << ")" << endl;

		// ������ �����Ѵ�.
		pLoginPlayer->disconnect(UNDISCONNECTED);

		// LPM���� �����Ѵ�.
		g_pLoginPlayerManager->deletePlayer( pLoginPlayer->getSocket()->getSOCKET() );

		// LoginPlayer ��ü�� �����Ѵ�.
		delete pLoginPlayer;

	} catch ( NoSuchElementException & nsee ) {
		cout << "Player not exist or already disconnected." << endl;
	}

#endif
		
	__END_CATCH
}
