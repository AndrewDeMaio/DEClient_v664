//----------------------------------------------------------------------
//
// Filename    : RCStatusHPHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "RCStatusHP.h"
#include "MParty.h"
#include "RequestUserManager.h"
#include "ClientDef.h"

#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
	extern CMessageArray*		g_pGameMessage;
#endif

//----------------------------------------------------------------------
// 
// RCStatusHPHander::execute()
// 
//----------------------------------------------------------------------
void RCStatusHPHandler::execute ( RCStatusHP * pPacket )
{
	__BEGIN_TRY

	//g_pClientCommunicationManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &glIncomingConnectionOK );
	
	if ((g_Mode==MODE_GAME
			|| g_Mode==MODE_WAIT_UPDATEINFO			// �ε� ���� �ƴϰų�..
			|| g_Mode==MODE_WAIT_SETPOSITION		// ��ǥ ��ٸ��� ���
			)
		&& g_pParty!=NULL
		&& g_pGameMessage!=NULL
		&& g_pRequestUserManager!=NULL)
	{
		// ����� ���� �ٽ� ����
		RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo( pPacket->getName().c_str() );

		if (pUserInfo!=NULL)
		{
			pUserInfo->IP = pPacket->getHost().c_str();
			pUserInfo->UDPPort = pPacket->getPort();
		}


		PARTY_INFO*	pInfo = NULL;
		
		// �̸��� ���� ��쿣 IP�� ã�ƺ���.
		if (pPacket->getName().size()==0)
		{
			pInfo = g_pParty->GetMemberInfoByIP( pPacket->getHost().c_str() );
		}
		else
		{
			pInfo = g_pParty->GetMemberInfo( pPacket->getName().c_str() );
		}
			
		// ��ǥ�� �������ش�.
		if (pInfo!=NULL
			&& !pInfo->bInSight)
		{
			pInfo->HP = pPacket->getCurrentHP();
			pInfo->MaxHP = pPacket->getMaxHP();
			
			#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
				if (g_pGameMessage!=NULL)
				{
					g_pGameMessage->AddFormat("[RCStatusHP] %d/%d", pInfo->HP, pInfo->MaxHP);
				}
			#endif
		}
		else
		{
			#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
				if (g_pGameMessage!=NULL)
				{
					g_pGameMessage->AddFormat("[RCStatusHP] in sight");
				}
			#endif
		}
	}
		
	__END_CATCH
}

