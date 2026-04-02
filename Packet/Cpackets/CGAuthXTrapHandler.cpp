
//////////////////////////////////////////////////////////////////////
//
// Filename    : CGAuthXTrapHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGAuthXTrap.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "EventKick.h"
#include "XTrap4Server.h"
#include "Gpackets/GCSystemMessage.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void CGAuthXTrapHandler::execute ( CGAuthXTrap * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

/*	Assert( pPacket != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	DWORD key = pPacket->getKey();
	if ( !pGamePlayer->getCSAuth().CheckAuthDword(key) )
	{
		filelog("CSAuth.log", "[%s] ���� ���� �߸��Ǿ����ϴ�.", pGamePlayer->getID().c_str());

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage("nProtect GameGuard ������ �����߽��ϴ�. ���� ������ �����ǰų� GameGuard ������ �ջ�Ǿ����ϴ�.");
		pGamePlayer->sendPacket( &gcSystemMessage );

		EventKick* pKick = new EventKick( pGamePlayer );
		pKick->setDeadline(100);
//		pKick->setMessage("GameGuard ���� �ڵ尡 �߸��Ǿ����ϴ�. 10�� �ڿ� ������ ����˴ϴ�.");
		pKick->sendMessage();

		pGamePlayer->addEvent(pKick);
	}
	
	*/
	
	Assert(pPacket != NULL);
	GamePlayer * pGamePlayer = dynamic_cast<GamePlayer *> (pPlayer);
	Assert ( pGamePlayer != NULL);
	

	int ret = -1;

	switch( pPacket->m_shCmdFlag )
	{
		case XTRAP_CMD_STEP_TWO:
			{
				ret = XTrap_CS_Step3( pGamePlayer->getXTSessionData(), pPacket->getAuthData() );
				
				cout << "C-S XTrap_CS_Step3 Authencation Check!!ret=" <<ret << endl;
				if(XTRAP_API_RETURN_OK != ret)
				{					
					///< ���� �����Ű���...
					///< �ֽ� �޴��󿡼� ���� ���� �����..XTrap_CS_Step1���� ����
					//filelog("CSAuth.log", "[%s] ���� ���� �߸��Ǿ����ϴ�.", pGamePlayer->getID().c_str());
					//GCSystemMessage gcSystemMessage;
					//gcSystemMessage.setMessage("XTrap GameGuard ������ �����߽��ϴ�. ���� ������ �����ǰų� GameGuard ������ �ջ�Ǿ����ϴ�.");
					//pGamePlayer->sendPacket( &gcSystemMessage );
					//EventKick* pKick = new EventKick( pGamePlayer );
					//pKick->setDeadline(100);
					//pKick->sendMessage();
					//pGamePlayer->addEvent(pKick);

				}
			}
			break;
		case XTRAP_MAP_FILE_CHANGE:
			{
			//	MapFileChange();
				cout << "XTRAP_MAP_FILE_CHANGE " << endl;
			}
			break;
	}

#endif
	
	__END_CATCH
}
