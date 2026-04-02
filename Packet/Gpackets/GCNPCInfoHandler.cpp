//----------------------------------------------------------------------
//
// Filename    : GCNPCInfoHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCNPCInfo.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "Cpackets/CGReady.h"
	#include "ClientDef.h"
	#include "UIFunction.h"

#endif

//----------------------------------------------------------------------
// Ŭ���̾�Ʈ�� ���� �����κ��� GCNPCInfo ��Ŷ�� �ް� �Ǹ�,
// ��Ŷ ���� �����͵��� Ŭ���̾�Ʈ�� ������ ��, ������ �ε���
// ���� ���� ���� ������ CGReady ��Ŷ�� ������ �ȴ�.
//----------------------------------------------------------------------
void GCNPCInfoHandler::execute ( GCNPCInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__
	
	// NPC ������ ����´�-_-;
	
	UI_ClearNPC();
	
	while(1)
	{
		NPCInfo* pInfo = pPacket->popNPCInfo();

		if(pInfo == NULL)
			break;

		const char* pName = pInfo->getName().c_str();
		int npcID = pInfo->getNPCID();
		int x = pInfo->getX();
		int y = pInfo->getY();

		UI_SetNPCInfo( pName, npcID, x, y );

		delete pInfo;
	}

#endif

	__END_CATCH
}
