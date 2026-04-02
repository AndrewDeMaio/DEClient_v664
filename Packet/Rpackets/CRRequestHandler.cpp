//////////////////////////////////////////////////////////////////////
//
// Filename    : CRRequestHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CRRequest.h"
#include "RequestServerPlayer.h"
#include "UserInformation.h"
#include "ProfileManager.h"
#include "RequestFileManager.h"
#include "RequestUserManager.h"
#include "Rpackets\RCRequestVerify.h"
#include "DebugInfo.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CRRequestHandler::execute ( CRRequest * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	DEBUG_ADD("CRRequestHandler");

	RequestServerPlayer* pRequestServerPlayer = dynamic_cast<RequestServerPlayer*>( pPlayer );

	// �̸��� ���ٸ� .. IP�� �����Ѵ�.
	if (pRequestServerPlayer->getName().c_str()==NULL
		|| pRequestServerPlayer->getName().size()==0)
	{
		DEBUG_ADD("setName");
		pRequestServerPlayer->setName( pPlayer->getSocket()->getHost().c_str() );		
		DEBUG_ADD("setName OK");
	}
	
	const std::string& otherName =	pRequestServerPlayer->getName();


	if (pRequestServerPlayer!=NULL
		&& g_pUserInformation!=NULL
		&& g_pProfileManager!=NULL
		&& g_pRequestFileManager!=NULL
		&& g_pRequestUserManager!=NULL)
	{			
		DEBUG_ADD("Not NULL");

		// ����� ���� �ٽ� ����
		//RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo( otherName.c_str() );

		//if (pUserInfo!=NULL)
		{
		//	Socket* pSocket = pPlayer->getSocket();
		//	pUserInfo->IP = pSocket->getHost().c_str();
		//	pUserInfo->TCPPort = pSocket->getPort();
		}

		switch (pPacket->getCode())
		{
			//------------------------------------------------------------------
			//
			//			Profile�� ��û���� ��,
			//
			//------------------------------------------------------------------
			case CR_REQUEST_FILE_PROFILE :
			{
				DEBUG_ADD("Request Profile");

				const char* pMyName = g_pUserInformation->CharacterID.GetString();

				if (pPacket->getRequestName()==pMyName)
				{
					const char* pFilename = g_pProfileManager->GetFilename( pMyName );

					//-------------------------------------------------------------
					// profile�� �ִ� ���
					//-------------------------------------------------------------
					if (pFilename != NULL)
					{
						DEBUG_ADD("profile not NULL");

						// �̹� ��û�� ������ ���� ��쿡.. 
						if (!g_pRequestFileManager->HasOtherRequest(otherName))
						{
							DEBUG_ADD("no Request");

							std::string filenameIndex = pFilename;
							filenameIndex += "i";

							RequestSendInfo* pInfo = new RequestSendInfo(otherName.c_str());							
							
							pInfo->AddSendFileInfo( new SendFileInfo(filenameIndex.c_str(), REQUEST_FILE_PROFILE_INDEX) );
							pInfo->AddSendFileInfo( new SendFileInfo(pFilename, REQUEST_FILE_PROFILE) );							

							DEBUG_ADD("add OtherReq");

							if (g_pRequestFileManager->AddOtherRequest(pInfo))
							{
								DEBUG_ADD("add otherReq OK");

								pRequestServerPlayer->setRequestMode(REQUEST_CLIENT_MODE_PROFILE);

								pRequestServerPlayer->setPlayerStatus(CPS_REQUEST_SERVER_NORMAL);
							}
							else
							{
								DEBUG_ADD("not add otherReq");

								//pRequestServerPlayer->disconnect( UNDISCONNECTED );

								DEBUG_ADD("disconnectExp");
								throw DisconnectException("Already Requested");
							}
						}					
					}
					//-------------------------------------------------------------
					// profile�� �ƿ� ���� ���
					//-------------------------------------------------------------
					else
					{
						DEBUG_ADD("send RCRequestVerify");

						RCRequestVerify rcRequestVerify;
						rcRequestVerify.setCode( REQUEST_VERIFY_PROFILE_NOT_EXIST );

						pRequestServerPlayer->sendPacket( &rcRequestVerify );

						pRequestServerPlayer->setPlayerStatus( CPS_END_SESSION );
						//pRequestServerPlayer->disconnect( UNDISCONNECTED );

						DEBUG_ADD("disconnectExp");
						throw DisconnectException("No Profile");
					}
				}
				//-------------------------------------------------------------
				// �ٸ� ����� profile�� ��û�ϴ� ���
				//-------------------------------------------------------------
				else
				{
					RCRequestVerify rcRequestVerify;
					rcRequestVerify.setCode( REQUEST_VERIFY_PROFILE_WRONG_USER );

					pRequestServerPlayer->sendPacket( &rcRequestVerify );

					pRequestServerPlayer->setPlayerStatus( CPS_END_SESSION );
					//pRequestServerPlayer->disconnect( UNDISCONNECTED );

					DEBUG_ADD("disconnectExp");
					throw DisconnectException("Wrong Profile requested");
				}
			}
			break;
		
			//------------------------------------------------------------------
			//
			//			��� ��ũ�� ��û���� ��,
			//
			//------------------------------------------------------------------
			case CR_REQUEST_FILE_GUILD_MARK :

				DEBUG_ADD("Request GuildMark");

				pRequestServerPlayer->setRequestMode(REQUEST_CLIENT_MODE_GUILDMARK);
				pRequestServerPlayer->setPlayerStatus(CPS_REQUEST_SERVER_NORMAL);
			break;
		}
	}

	DEBUG_ADD("CRRequestHandler End");

#endif

	__END_CATCH
}
