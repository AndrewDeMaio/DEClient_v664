//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRequestedIPHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCRequestedIP.h"
//#include "MParty.h"
//#include "RequestFunction.h"

#include "RequestClientPlayerManager.h"
#include "RequestUserManager.h"
#include "WhisperManager.h"
#include "ClientDef.h"
#include "UserInformation.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRequestedIPHandler::execute ( GCRequestedIP * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
	if( g_pUserInformation->bKorean == false || 1 )
		return;
		
#ifdef __GAME_CLIENT__

	if (g_Mode==MODE_GAME
		&& g_pRequestUserManager!=NULL
		&& g_pRequestClientPlayerManager!=NULL)
	{
		const char* pName = pPacket->getName().c_str();

		struct in_addr sa;
		sa.S_un.S_addr = pPacket->getIP();

		const char* pIP = inet_ntoa( sa );

		// ���� �߰�
		g_pRequestUserManager->AddRequestUser( pName, pIP, pPacket->getPort() );	


		switch (g_pRequestUserManager->GetRequestingFor(pName))
		{
			//--------------------------------------------------------
			// REQUESTING_FOR_WHISPER
			//--------------------------------------------------------
			// �ӼӸ��� ������ ���� IP�� ��û�� ���
			//--------------------------------------------------------
			case RequestUserManager::REQUESTING_FOR_WHISPER :
				if (g_pWhisperManager->HasWhisperMessage( pName ))
				{
					g_pRequestClientPlayerManager->Connect( pIP, 
															pName, 
															REQUEST_CLIENT_MODE_WHISPER );
				}
			break;

			//--------------------------------------------------------
			// REQUESTING_FOR_PROFILE
			//--------------------------------------------------------
			// Profile�� �ޱ� ���� IP�� ��û�� ���
			//--------------------------------------------------------
			case RequestUserManager::REQUESTING_FOR_PROFILE :
				g_pRequestClientPlayerManager->Connect( pIP, 
														pName, 
														REQUEST_CLIENT_MODE_PROFILE );
			break;
		}


		// ��û���ΰ� ����
		g_pRequestUserManager->RemoveRequestingUser( pName );	
	}

	//---------------------------------------------------------------
	// �ϴ���.. ��Ƽ�� ���� IP�̹Ƿ�.. ��Ƽ���� üũ�� �غ���.	
	//---------------------------------------------------------------
	/*
	int num = g_pParty->GetSize();

	for (int i=0; i<num; i++)
	{
		PARTY_INFO*	pInfo = g_pParty->GetMemberInfo(i);

		if (pInfo!=NULL)
		{
			// ���� �̸��̶��..
			if (pInfo->Name==pPacket->getName().c_str())				
			{
				// �ϴ� IP ����
				pInfo->IP = pPacket->getIP().c_str();

				// ������ ���ٸ� ���ӽõ��� �Ѵ�.
				if (!g_pRequestClientPlayerManager->HasConnection( pInfo->Name.GetString() ))
				{
					RequestConnect( pInfo->IP.c_str(), pInfo->Name.GetString() );
				}

				break;
			}
		}
	}	
	*/

#endif

	__END_CATCH
}
