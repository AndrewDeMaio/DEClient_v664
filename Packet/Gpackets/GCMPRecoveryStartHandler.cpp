//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMPRecoveryToOhtersHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCMPRecoveryStart.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryStartHandler::execute ( GCMPRecoveryStart * pPacket , Player * pPlayer )
{
	__BEGIN_TRY


	// item ��� ����
	//UseItemOK();

	if (g_pPlayer!=NULL)
	{
		DWORD delay = ConvertDurationToMillisecond( pPacket->getDelay() );
	
		g_pPlayer->SetRecoveryMP( pPacket->getQuantity(),
									pPacket->getPeriod(),
									delay );
	}	


	__END_CATCH
}
