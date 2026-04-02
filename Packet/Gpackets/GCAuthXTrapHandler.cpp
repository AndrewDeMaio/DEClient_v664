
//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAuthKeyHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAuthXTrap.h"
#include "../Cpackets/CGAuthXTrap.h"
#include "ServerInfo.h"
#include "XTrap4Client.h"

#ifdef __GAME_CLIENT__
#include "ClientPlayer.h"

extern ClientPlayer*		g_pSocket;
#endif
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCAuthXTrapHandler::execute ( GCAuthXTrap * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

#if !defined(_DEBUG)

	//MessageBox(NULL, "GCAuthKeyHandler����1", "Warning", MB_OK);

	CGAuthXTrap SendPack;
	
	if(pPacket->m_shCmdFlag == XTRAP_CMD_STEP_ONE)
	{
		BYTE szTemp[128] = {0};
		int ret = XTrap_CS_Step2(pPacket->getAuthData(), (void*)szTemp, XTRAP_PROTECT_PE| XTRAP_PROTECT_TEXT |XTRAP_PROTECT_EXCEPT_VIRUS);
		SendPack.setKey(szTemp);
		SendPack.m_shCmdFlag = XTRAP_CMD_STEP_TWO;
		g_pSocket->sendPacket( &SendPack );
		
		if(ret == XTRAP_API_RETURN_OK )
		{			
		}
		else
		{
			//MessageBox(NULL, "GCAuthKeyHandler����2", "Warning", MB_OK);
		}
	}

#endif	
#endif

	__END_CATCH
}
