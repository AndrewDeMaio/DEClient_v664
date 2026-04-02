//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGuildChatHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGuildChat.h"
#include "ClientDef.h"
#include "MChatManager.h"
#include "UserInformation.h"
#include "UIFunction.h"
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCGuildChatHandler::execute ( GCGuildChat * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
		char str[256];

		//---------------------------------------------------------------
		// �ϼ��� --> ������
		//---------------------------------------------------------------
		//UI_WansungToJohap( pPacket->getMessage().c_str(), str );
	
		
		strcpy( str, pPacket->getMessage().c_str() );
		
		if (str[0] != NULL)
		{
			//--------------------------------------------------
			// ������ ���̴� ���ΰ�?
			//--------------------------------------------------
			if (g_pChatManager->IsAcceptID( pPacket->getSender().c_str() ))
			{
				//--------------------------------------------------
				// �� ����
				//--------------------------------------------------
				g_pChatManager->RemoveCurse( str );
					
				// GUILDCHAT = 4
				// 2004, 11, 11, sobeit modify start
				if(0 == pPacket->getType()) // ���ê 
					UI_AddChatToHistory( str, (char *)pPacket->getSender().c_str(), 4, pPacket->getColor() );
				else // ���Ͽ� ê
				{
					char szName[128];
					sprintf(szName, "[%s]%s", pPacket->getSendGuildName().c_str(), pPacket->getSender().c_str());
					UI_AddChatToHistory( str, szName, 5, pPacket->getColor() );
				}
				//UI_AddChatToHistory( str, (char *)pPacket->getSender().c_str(), 4, pPacket->getColor() );
				// 2004, 11, 11, sobeit modify start
			}
		}
#endif

	__END_CATCH
}
