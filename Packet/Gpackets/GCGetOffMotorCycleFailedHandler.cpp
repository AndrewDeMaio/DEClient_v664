//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGetOffMotorCycleFailedHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGetOffMotorCycleFailed.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGetOffMotorCycleFailedHandler::execute ( GCGetOffMotorCycleFailed * pPacket, Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__


	//------------------------------------------
	// ��¶�� ����.. ������ �Ǿ��ٰ� ����.
	//------------------------------------------
	g_pPlayer->SetWaitVerifyNULL();

#endif

	__END_CATCH
}
