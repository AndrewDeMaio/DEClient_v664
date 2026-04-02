//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodBibleSignInfoHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCBloodBibleSignInfo.h"
#include "PacketFunction.h"
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// BloodBibleSignInfo*	g_pBloodBibleSignInfo	= NULL;
BloodBibleSignInfo*	g_pBloodBibleSignInfo	= NULL;	//����â�� �ٲ𶧿� �μ��� ���� �۷ι� ��
															//SetGearInfo 2��° �μ��� NULL�� ���ϱ� ���� ������ �Ⱥ��̴� ������ �߻�.
															//GCChangeGearSlot���� BloodBibleSignInfo ��Ŷ�� ���� ������ ���ڴ�. ��.��
#endif // __GEAR_SWAP_CHANGE



void GCBloodBibleSignInfoHandler::execute ( GCBloodBibleSignInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY 
	
#ifdef __GAME_CLIENT__
	SetBloodBibleSlot(pPacket->getSignInfo());

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// 	g_pBloodBibleSignInfo	= pPacket->getSignInfo();
	g_pBloodBibleSignInfo	= pPacket->getSignInfo();
#endif	// __GEAR_SWAP_CHANGE

	//cout << pPacket->toString() << endl;
#endif

	 __END_CATCH
}
