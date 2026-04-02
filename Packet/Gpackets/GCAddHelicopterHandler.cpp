//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddHelicopterHandler.cpp
// Written By  : excel96
// Description :
// �����̾ �����⸦ �����, ��⸦ ȣ������ ��쿡 ���ư��� ��Ŷ
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCAddHelicopter.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCAddHelicopterHandler::execute ( GCAddHelicopter * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	if (g_pZone!=NULL)
	{
		TYPE_OBJECTID	creatureID = pPacket->getObjectID();
		BYTE			ExtendType = pPacket->getExtendType();

		if (pPacket->getCode()==0)
		{
			g_pZone->AddHelicopter( creatureID, 0, 0, ExtendType );
		}
		else
		{
			g_pZone->RemoveHelicopter( creatureID );
		}
	}

#endif

	__END_CATCH
}
