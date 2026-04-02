//////////////////////////////////////////////////////////////////////
//
// Filename    : RCConnectVerifyHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "RCConnectVerify.h"
#include "RequestClientPlayer.h"
//#include "CRRequest.h"
//#include "MZone.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void RCConnectVerifyHandler::execute ( RCConnectVerify * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	RequestClientPlayer* pRequestClientPlayer = dynamic_cast<RequestClientPlayer*>( pPlayer );

	if (pRequestClientPlayer!=NULL)
	{
		switch (pPacket->getCode())
		{
			//---------------------------------------------------------------
			// ������ ���� ���
			//---------------------------------------------------------------
			case RC_CONNECT_OK :
				pRequestClientPlayer->setPlayerStatus( CPS_REQUEST_CLIENT_NORMAL );

				// ���� player�� �þ߿� �ִ��� �������� üũ�ؼ� 
				// ���ٸ� ��ǥ ��û�� �Ѵ�.
				/*
				if (OBJECTID_NULL != g_pZone->GetCreatureID( pRequestClientPlayer->getRequestServerName().c_str() ))
				{
					// �ִ� ���					
				}
				else
				{
					// ���� ���
					// �������� ��ǥ ��û�� �Ѵ�.
					CRRequest _CRRequest;
					_CRRequest.setCode( CR_REQUEST_POSITION_REPEATLY );

					pRequestClientPlayer->sendPacket( &_CRRequest );
				}
				*/

			break;

			//---------------------------------------------------------------
			// ������ �ȵǰų� �źε� ���
			//---------------------------------------------------------------
			case RC_CONNECT_REJECT :
			case RC_CONNECT_WRONG :
				pRequestClientPlayer->setPlayerStatus( CPS_END_SESSION );
				//pRequestClientPlayer->disconnect(UNDISCONNECTED);
				throw DisconnectException("Reject or Wrong");
			break;
		}
	}

#endif

	__END_CATCH
}
