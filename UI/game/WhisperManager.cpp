//----------------------------------------------------------------------
// WhisperManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "WhisperManager.h"
#include "RequestClientPlayerManager.h"
#include "RequestUserManager.h"
#include "MGameStringTable.h"

#include "Cpackets\CGRequestIP.h"
#include "Cpackets\CGWhisper.h"
#include "ClientPlayer.h"
#include "DebugInfo.h"
#include "ServerInfo.h"
#include "UserInformation.h"
#include "UIFunction.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
WhisperManager*		g_pWhisperManager = NULL;

//----------------------------------------------------------------------
// extern
//----------------------------------------------------------------------
	extern ClientPlayer*		g_pSocket;


//----------------------------------------------------------------------
//
//						WhisperInfo
//
//----------------------------------------------------------------------
// Send to GameServer
//----------------------------------------------------------------------
void
WhisperInfo::SendToGameServer() const
{
	std::list<WHISPER_MESSAGE>::const_iterator iMessage = Messages.begin();


	CGWhisper _CGWhisper;
	_CGWhisper.setName( Name.c_str() );

	// ��� message ������
	while (iMessage != Messages.end())
	{		
		_CGWhisper.setMessage( (*iMessage).msg.c_str() );
		_CGWhisper.setColor( (*iMessage).color );

		g_pSocket->sendPacket( &_CGWhisper );

		iMessage ++;
	}
}

//----------------------------------------------------------------------
//
//						WhisperManager
// 
//----------------------------------------------------------------------
WhisperManager::WhisperManager()
{
	InitializeCriticalSection(&m_Lock);
}

WhisperManager::~WhisperManager()
{
	Release();

	DeleteCriticalSection(&m_Lock);
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void		
WhisperManager::Release()
{
	Lock();

	WHISPER_INFO_MAP::iterator iInfo = m_WhisperInfos.begin();

	while (iInfo != m_WhisperInfos.end())
	{
		WhisperInfo* pInfo = iInfo->second;

		delete pInfo;

		iInfo++;
	}

	m_WhisperInfos.clear();

	Unlock();
}

//----------------------------------------------------------------------
// Send / Remove Message
//----------------------------------------------------------------------
bool		
WhisperManager::HasWhisperMessage(const char* pName) const
{
	WHISPER_INFO_MAP::const_iterator iInfo = m_WhisperInfos.find( std::string(pName) );	

	if (iInfo != m_WhisperInfos.end())
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Send Message
//----------------------------------------------------------------------
//
// if (has toUser's IP in RequestUserManager)
// {			
//		RequestClientManager --(CRWhisper)--> RequestServer(toUser) [2]			
// }
// else
// {
//		CGWhisper --> GameServer [3]
// }
//
//----------------------------------------------------------------------
void		
WhisperManager::SendWhisperMessage(const char* pName, const char* pMessage, DWORD color)
{
	//CRWhisper *pPacket;
	//_CRWhisper.setName( pName );
	//_CRWhisper.setMessage( pMessage );
	//Packet* pPacket = NULL;

	if( 0 && g_pUserInformation->bKorean == true )	// �ѱ������̸� p2p
	{
		//-------------------------------------------------------
		// �������̰ų� ���� �õ� ���� ���..
		//-------------------------------------------------------
		if (g_pRequestClientPlayerManager->HasConnection(pName)
			|| g_pRequestClientPlayerManager->HasTryingConnection(pName))//!g_pRequestClientPlayerManager->SendPacket(pName, pPacket))
		{
			AddWhisperMessage( pName, pMessage, color );
		}
		//-------------------------------------------------------
		// �������� �ƴ� ���
		//-------------------------------------------------------
		else
		{
			RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo(pName);

			//-------------------------------------------------------
			// ����� ������ �ִٸ� ���� �õ��� �Ѵ�.
			//-------------------------------------------------------
			if (pUserInfo!=NULL)
			{
				//-------------------------------------------------------
				// ���� �Ұ� ������ ���
				//-------------------------------------------------------
				if (pUserInfo->IsStatusUnable())
				{
					// GameServer�� �׳� ������.
						CGWhisper _CGWhisper;
						_CGWhisper.setName( pName );

						_CGWhisper.setMessage( pMessage );
						_CGWhisper.setColor( color );

						g_pSocket->sendPacket( &_CGWhisper );
				}
				//-------------------------------------------------------
				// �������� ������ �Ǵ� ���..
				//-------------------------------------------------------
				else
				{
					AddWhisperMessage( pName, pMessage, color );
					g_pRequestClientPlayerManager->Connect(pUserInfo->IP.c_str(), pName, REQUEST_CLIENT_MODE_WHISPER);
				}
			}
			//-------------------------------------------------------
			// ����� ������ ���ٸ� ... ������ IP�� ��û�Ѵ�.
			//-------------------------------------------------------
			else
			{
				if (!g_pRequestUserManager->HasRequestingUser( pName ))
				{
					if( g_pUserInformation->bKorean == true )
					{
						// ������ IP�� ��û�Ѵ�.
						CGRequestIP _CGRequestIP;
						_CGRequestIP.setName( pName );

						g_pSocket->sendPacket( &_CGRequestIP );			
		
					g_pRequestUserManager->AddRequestingUser( pName, RequestUserManager::REQUESTING_FOR_WHISPER );
					}
				}

				// IP�� �ް� ���� message�� �����ֱ� ���ؼ� �����صд�.
				AddWhisperMessage( pName, pMessage, color );
			}
		}	
	}
	else	// �ѱ� ������ �ƴϸ�
	{
		// GameServer�� �׳� ������.
		CGWhisper _CGWhisper;
		_CGWhisper.setName( pName );
		
		_CGWhisper.setMessage( pMessage );
		_CGWhisper.setColor( color );
		
		g_pSocket->sendPacket( &_CGWhisper );
	}
}

//----------------------------------------------------------------------
// Add Message
//----------------------------------------------------------------------
void		
WhisperManager::AddWhisperMessage(const char* pName, const char* pMessage, DWORD color)
{
	Lock();

	WHISPER_INFO_MAP::iterator iInfo = m_WhisperInfos.find( std::string(pName) );

	//------------------------------------------------
	// ���ٸ� �����Ѵ�.
	//------------------------------------------------
	if (iInfo == m_WhisperInfos.end())
	{
		WhisperInfo* pInfo = new WhisperInfo;
		pInfo->Name		= std::string(pName);
		WHISPER_MESSAGE temp_message;
		temp_message.msg = std::string(pMessage);
		temp_message.color = color;
		pInfo->Messages.push_back( temp_message );

		m_WhisperInfos[pInfo->Name] = pInfo;
	}
	//------------------------------------------------
	// �̹� �ִٸ� �߰��صд�.
	//------------------------------------------------
	else
	{
		WhisperInfo* pInfo = iInfo->second;
		
		WHISPER_MESSAGE temp_message;
		temp_message.msg = std::string(pMessage);
		temp_message.color = color;
		pInfo->Messages.push_back( temp_message );
	}

	Unlock();
}

//----------------------------------------------------------------------
// Get Message
//----------------------------------------------------------------------
const std::list<WHISPER_MESSAGE>*
WhisperManager::GetWhisperMessages(const char* pName) const
{
	WHISPER_INFO_MAP::const_iterator iInfo = m_WhisperInfos.find( std::string(pName) );

	if (iInfo != m_WhisperInfos.end())
	{
		return &iInfo->second->Messages;
	}

	return NULL;
}

//----------------------------------------------------------------------
// Remove Message
//----------------------------------------------------------------------
void		
WhisperManager::TryToSendWhisperMessage(const char* pName)
{
	Lock();

	WHISPER_INFO_MAP::const_iterator iInfo = m_WhisperInfos.find( std::string(pName) );

	if (iInfo != m_WhisperInfos.end())
	{
		// �õ� ȸ�� ����
		iInfo->second->TryingCount++;		
	}
	else
	{
		// �ӼӸ��� �������� �õ��ϴ� ���� �ƴ϶�� ������ ���ش�.
//		g_pRequestUserManager->RemoveRequestUserLater( pName );
	}

	Unlock();
}

//----------------------------------------------------------------------
// Remove Message
//----------------------------------------------------------------------
bool
WhisperManager::RemoveWhisperMessage(const char* pName)
{
	Lock();

	WHISPER_INFO_MAP::iterator iInfo = m_WhisperInfos.find( std::string(pName) );

	if (iInfo != m_WhisperInfos.end())
	{
		delete iInfo->second;

		m_WhisperInfos.erase( iInfo );

		Unlock();
		return true;
	}

	Unlock();
	return false;
}


//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
// �׿� �ִ� message���� ó���Ѵ�.
//----------------------------------------------------------------------
void
WhisperManager::Update()
{
	if (m_WhisperInfos.empty())
	{
		return;
	}	

	Lock();
	
	WHISPER_INFO_MAP::iterator iInfo = m_WhisperInfos.begin();

	while (iInfo != m_WhisperInfos.end())
	{
		WhisperInfo* pInfo = iInfo->second;

		//-------------------------------------------------------
		// �õ��� ���� �� ����... ����~�ؾ� �Ѵ�.
		// �׷� Ȯ���� ���� ������..
		// �������� �߸��� IP�� �Ѿ���� ��찡 �ִ�.
		//-------------------------------------------------------
		if (pInfo->TryingCount > 2)		// 2 _-_;
		{
			WHISPER_INFO_MAP::iterator iTemp = iInfo ++;

			// �ӼӸ� �������� �ʾҴٰ� ������ְ�
			//UI_AddChatToHistory( (*g_pGameStringTable)[STRING_MESSAGE_WHISPER_FAILED].GetString(), NULL, 5 );

			// ������ ������.
			pInfo->SendToGameServer();

			// ����� ������ ���� �Ұ� ���·� �����Ѵ�.
			RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo(pInfo->Name.c_str());

			if (pUserInfo!=NULL)
			{
				pUserInfo->SetStatusUnable();
			}

			// ������ �����Ѵ�.
			delete pInfo;
			m_WhisperInfos.erase( iTemp );

			continue;
		}
		//-------------------------------------------------------
		// �ӼӸ� ������ ���� ���� ��û..
		//-------------------------------------------------------
		else
		{			
			const char* pName = pInfo->Name.c_str();

			//-------------------------------------------------------
			// �������̰ų� ���� �õ� ���� ���..
			//-------------------------------------------------------
			if (g_pRequestClientPlayerManager->HasTryingConnection(pName)
				|| g_pRequestClientPlayerManager->HasConnection(pName))			
			{			
			}
			//-------------------------------------------------------
			// �������� �ƴ� ���
			//-------------------------------------------------------
			else
			{
				RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo(pName);
				
				//-------------------------------------------------------
				// ����� ������ �ִٸ� ���� �õ��� �Ѵ�.
				//-------------------------------------------------------
				if (pUserInfo!=NULL)
				{
					if (pUserInfo->IsStatusUnable())
					{
						pInfo->SendToGameServer();
						
						// ������ �����Ѵ�.
						WHISPER_INFO_MAP::iterator iTemp = iInfo ++;
						delete pInfo;
						m_WhisperInfos.erase( iTemp );
						continue;
					}
					else
					{
						g_pRequestClientPlayerManager->Connect(pUserInfo->IP.c_str(), pName, REQUEST_CLIENT_MODE_WHISPER);
					}
				}
				
				//-------------------------------------------------------
				// ����� ������ ���ٸ� ... ������ IP�� ��û�Ѵ�.
				//-------------------------------------------------------
				else
				{
					if (!g_pRequestUserManager->HasRequestingUser( pName ))
					{
						if( 0 && g_pUserInformation->bKorean == true )
						{
							// ������ IP�� ��û�Ѵ�.
							CGRequestIP _CGRequestIP;
							_CGRequestIP.setName( pName );

							g_pSocket->sendPacket( &_CGRequestIP );

						g_pRequestUserManager->AddRequestingUser( pName, RequestUserManager::REQUESTING_FOR_WHISPER );
						}
					}
				}
			}	
		}
		

		iInfo++;
	}

	Unlock();
}
