//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKickMessageHandler.cc
// Written By  : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCKickMessage.h"

#ifdef __GAME_CLIENT__
	#include "MGameStringTable.h"
	#include "MEventManager.h"
	#include "ClientDef.h"

#endif 

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCKickMessageHandler::execute ( GCKickMessage * pPacket , Player * pPlayer )
{
	__BEGIN_TRY 
	
	switch( pPacket->getType() )
	{
	case KICK_MESSAGE_PAY_TIMEOUT :
		{
			MEvent event;
			event.eventID = EVENTID_FORCE_LOGOUT_BY_PREMIUM;
			event.eventDelay = int( pPacket->getSeconds() * 1000 );
			event.eventFlag = EVENTFLAG_SHOW_DELAY_STRING;
			event.eventType = EVENTTYPE_ZONE;
			event.m_StringsID.push_back(STRING_MESSAGE_LOGOUT_BY_PAYTIME);
			event.m_StringsID.push_back(STRING_MESSAGE_LOGOUT_AFTER_SECOND);
						
			g_pEventManager->AddEvent(event);
		}
		break;
	case KICK_MESSAGE_EXPIRE_FREEPLAY :
		{
			MEvent event;
			event.eventID = EVENTID_FORCE_LOGOUT_BY_PREMIUM;
			event.eventDelay = int( pPacket->getSeconds() * 1000 );
			event.eventFlag = EVENTFLAG_SHOW_DELAY_STRING;
			event.eventType = EVENTTYPE_ZONE;
			if(g_pPlayer->IsSlayer())
				event.m_StringsID.push_back(STRING_MESSAGE_LOGOUT_BY_FREEPLAY_LEVEL);
			else
				event.m_StringsID.push_back(STRING_MESSAGE_LOGOUT_BY_LEVEL);
			event.m_StringsID.push_back(STRING_MESSAGE_LOGOUT_AFTER_SECOND);

			g_pEventManager->AddEvent(event);
		}
		break;
	}		

	__END_CATCH
}
