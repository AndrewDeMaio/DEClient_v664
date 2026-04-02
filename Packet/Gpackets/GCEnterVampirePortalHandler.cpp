//////////////////////////////////////////////////////////////////////////////
// Filename    : GCEnterVampirePortalHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCEnterVampirePortal.h"
#include "ClientDef.h"
#include "MTopView.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCEnterVampirePortalHandler::execute ( GCEnterVampirePortal * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__


	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
		
	}	
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		int creatureID = pPacket->getObjectID();

		MCreature* pCreature = g_pZone->GetCreature( creatureID );

		//--------------------------------------------------
		// portal�� ������� ���
		//--------------------------------------------------
		if (pCreature!=NULL)
		{
			int x = pPacket->getX();
			int y = pPacket->getY();

			pCreature->SetStop();

			pCreature->MovePosition( x, y );
			pCreature->SetServerPosition( x, y );

			g_pTopView->VampireMoveIntoPortal( pCreature );

			g_pZone->RemoveCreature( creatureID );
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] There is no such Creature. id=%d", creatureID);
		}
	}

#endif

	__END_CATCH
}
