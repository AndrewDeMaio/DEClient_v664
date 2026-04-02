//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSystemMessageHandler.cc
// Written By  : elca
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSystemMessage.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCSystemMessageHandler::execute ( GCSystemMessage * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	if(g_pZone->GetID() == 1005 && pPacket->getType() != SYSTEM_MESSAGE_EVENT && pPacket->getType() != SYSTEM_MESSAGE_OPERATOR && pPacket->getType() != SYSTEM_MESSAGE_INFO)
		return;
	switch(pPacket->getType())
	{ 
		case SYSTEM_MESSAGE_HOLY_LAND :		// �ƴ��� ���� ����
			if(g_pUserOption->DoNotShowHolyLandMsg)
				return;
			break;

		case SYSTEM_MESSAGE_NORMAL:
			break;

//		case SYSTEM_MESSAGE_OPERATOR:	// ��� ����
//			break;
	
		case SYSTEM_MESSAGE_MASTER_LAIR:	// ������ ���� ����
			if(g_pUserOption->DoNotShowLairMsg)
				return;
			break;

		case SYSTEM_MESSAGE_COMBAT:		// ���� ����
			if(g_pUserOption->DoNotShowWarMsg)
				return;
			break;
	
		case SYSTEM_MESSAGE_INFO: 		// Ư���� ���� ����
			break;
			
		case SYSTEM_MESSAGE_RANGER_CHAT:
			{
				char* message = (char*)pPacket->getMessage().c_str();
				if(NULL != message)
				{
					UI_SetRangerChatString(message);
				}
			}
			return;
		case SYSTEM_MESSAGE_TIMER:
			{
				const char *tok = "[]";

				char szBuf[256];
				strcpy(szBuf, pPacket->getMessage().c_str());
				
				char szDesc[256];
				strcpy(szDesc, strtok(szBuf, tok));

				char *szTime = strtok(NULL, tok);
				DWORD dwSec = atoi(szTime) / 10;

				// Time�� 0�̸� ������� �Ҹ���.
				if(dwSec > 0)
				{
					UI_RunTimeCount(dwSec, szDesc);
				}
				else
				{
					UI_CloseTimeCount();
				}
			}
			return;
		//2008.07.17 zzi
		case SYSTEM_MESSAGE_OPERATOR:	//test��..��� ������.. EventMessage�� ����� ����.
			{
				char* message = (char*)pPacket->getMessage().c_str();
				if(NULL != message)
					g_pGMMessage->Add( message );
			}
			return;

		case SYSTEM_MESSAGE_EVENT:
			{
				static char cleaner[512] = { NULL, };
				//�ϴ� ������.. �о����.
				char* message = (char*)pPacket->getMessage().c_str();
				if(NULL != message)
				{
					if (!strcmp(message, cleaner))
					{
						g_pEventMessage->Clear();
						cleaner[0] = '\0';
					}
					else
					{
						g_pEventMessage->Add( message );
						strcpy (cleaner, message);
					}
				}
			}
			return;
		//-
	}

	static char previous[128] = { NULL, };

	const char* message = pPacket->getMessage().c_str();
	
	//--------------------------------------------------------------------
	// system message�� ���
	//--------------------------------------------------------------------
	if (strcmp(previous, message)==0)
	{
		BOOL bExist = FALSE;

		//--------------------------------------------------------------------
		// �̹� �ִ� �޼������� �˻��Ѵ�.
		//--------------------------------------------------------------------
		for (int i=0; i<g_pSystemMessage->GetSize(); i++)
		{
			if (strcmp((*g_pSystemMessage)[i], message)==0)
			{
				bExist = TRUE;
			}
		}

		//--------------------------------------------------------------------
		// ���°Ÿ� �߰��Ѵ�.		
		//--------------------------------------------------------------------
		if (!bExist)
		{
			g_pSystemMessage->Add( message );
		}
	}
	//--------------------------------------------------------------------
	// ���ο� �޼����̸� �߰��Ѵ�.
	//--------------------------------------------------------------------
	else
	{
		g_pSystemMessage->Add( message );

		strcpy( previous, pPacket->getMessage().c_str() );
	}

#endif

	__END_CATCH
}
