//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMoveErrorHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCMoveError.h"
#include "ClientDef.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMoveErrorHandler::execute ( GCMoveError * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
/*
	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	pClientPlayer->setX( pPacket->getX() );
	pClientPlayer->setY( pPacket->getY() );

	cout << "Move Back To (" << (int)pPacket->getX() << "," << (int)pPacket->getY() << ")" << endl;
	
#elif __WINDOWS__
*/

	// ���� ��ǥ ����
	// 2001.10.8 ����
	g_pPlayer->SetServerPosition( pPacket->getX(), pPacket->getY() );

	// MoveOK message�� �ϳ� �� ���ƿ´ٴ°� �� �� �ִ�.
	g_pPlayer->PacketMoveNO();
	

#endif

	__END_CATCH
}
