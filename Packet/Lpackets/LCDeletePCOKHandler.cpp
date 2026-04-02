//--------------------------------------------------------------------------------
//
// Filename    : LCDeletePCOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "client_PCH.h"
#include "LCDeletePCOK.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"
#endif

#include "ClientDef.h"
#include "UIFunction.h"

//--------------------------------------------------------------------------------
//
// PC �� ���������� �����ߴٴ� ���̴�.
//
//--------------------------------------------------------------------------------
void LCDeletePCOKHandler::execute ( LCDeletePCOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	#if __LINUX__

		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		cout << "                            " << endl;
		cout << "+--------------------------+" << endl;
		cout << "| PC deleted successfully! |" << endl;
		cout << "+--------------------------+" << endl;
		cout << "                            " << endl;

		// �ٽ� PC LIST �� �޾ƿ;� �Ѵ�.
		CLGetPCList clGetPCList;
		pClientPlayer->sendPacket( &clGetPCList );	

		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

	#elif __WINDOWS__

		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		// delete����
		UI_DeleteCharacterOK();

		// �ٽ� PC LIST�� �޾ƾ� �Ѵ�.
		CLGetPCList clGetPCList;
		pClientPlayer->sendPacket( &clGetPCList );	

		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

		// PC List�� ��ٸ��� mode
		g_ModeNext = MODE_WAIT_PCLIST;

	#endif
	
#endif

	__END_CATCH
}
