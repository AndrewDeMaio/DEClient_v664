//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodBibleStatusHandler.cc
// Written By  : elca
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCBloodBibleStatus.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatusHandler::execute ( GCBloodBibleStatus * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
	UI_SetBloodBibleStatus(pPacket);
#endif

	__END_CATCH
}
