//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGetOffMotorCycleOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGetOffMotorCycleOK.h"
#include "ClientDef.h"
#include "SoundDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGetOffMotorCycleOKHandler::execute ( GCGetOffMotorCycleOK * pPacket, Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	
	//------------------------------------------
	// ������� �׸��� �����ش�.
	//------------------------------------------
	g_pPlayer->RemoveAddon( ADDON_MOTOR );

	//------------------------------------------
	// �����̴� ��� �ٲ�
	//------------------------------------------
	g_pPlayer->SetMoveDevice( MCreature::MOVE_DEVICE_WALK );

	//------------------------------------------
	// ��¶�� ����.. ������ �Ǿ��ٰ� ����.
	//------------------------------------------
	g_pPlayer->SetWaitVerifyNULL();

	//------------------------------------------
	// ������ �Ҹ� ���
	//------------------------------------------
	PlaySound( SOUND_WORLD_BIKE_STOP );

#endif

	__END_CATCH
}
