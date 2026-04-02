//--------------------------------------------------------------------------------
//
// Filename    : GCChangeDarkLightHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCChangeGearSlot.h"
#include "Client.h"
#include "Assert.h"

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// GCChangeGearSlotHandler.cpp
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
extern BloodBibleSignInfo*	g_pBloodBibleSignInfo;	// ���� ������ �ְ� �̰� ��� ������ �ִ°� �̰� �ƴѰ� ������..
															// ���� ���� �ʹ� �ٺ� ���̽Ŵ�~! ��.��
															// BloodBibleSignInfo ���� ��Ŷ���� �޾ƾ� �Ҳ� ������..

void GCChangeGearSlotHandler::execute ( GCChangeGearSlot * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__	
	SetGearInfo( pPacket->getGearInfo(), g_pBloodBibleSignInfo, pPacket->getGearSlotID());

	// ����� �ٽ����ش�.
	g_pPlayer->CalculateStatus();
#endif

	__END_CATCH
}
#endif //__GEAR_SWAP_CHANGE