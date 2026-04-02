//////////////////////////////////////////////////////////////////////
//
// Filename    : LCRegisterPlayerOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "LCRegisterPlayerOK.h"
#include "UserInformation.h"
#include "ClientDef.h"
#include "UIFunction.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"

#endif

extern BOOL g_bNeedUpdate;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LCRegisterPlayerOKHandler::execute ( LCRegisterPlayerOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	//cout << "�÷��̾� ��Ͽ� �����߽��ϴ�.. ��ī.. " << endl;

	//throw DisconnectException("�÷��̾� ��Ͽ� ���������ϱ�, ������ �����ϰ� �ٽ� �ض�..");
	// Debug Message

	if (!g_bNeedUpdate)
	{
		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		CLGetPCList clGetPCList;

		pClientPlayer->sendPacket( &clGetPCList );
		
		// �÷��̾��� ���¸� �ٲ۴�.
		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

		//------------------------------------------------------------
		// �ݴ´�.
		//------------------------------------------------------------
		UI_CloseUserRegistrationWindow();

		// ID�� �����ѵд�.
		if( g_pUserInformation->UserID != NULL && g_pUserInformation->UserID.GetLength() < 12 )
			UI_BackupLoginID( g_pUserInformation->UserID );
		else
			UI_BackupLoginID( "DarkEden" );


		//------------------------------------------------------------
		// ���� Server ������ �����صд�.
		//------------------------------------------------------------
		SetServerGroupName( pPacket->getGroupName().c_str() );
		//SetServerName( pPacket->getServerName().c_str() );

		//------------------------------------------------------------
		// Client�� PC List�� ��ٷ��� �Ѵ�.
		//------------------------------------------------------------	
		SetMode( MODE_WAIT_PCLIST );

		//------------------------------------------------------------
		// Gore Level�� �ٲ۴�.
		//------------------------------------------------------------
		bool bGoreLevel = pPacket->isAdult() && !g_pUserOption->UseTeenVersion;

		SetGoreLevel( bGoreLevel);	
		
	}

#endif

	__END_CATCH
}
