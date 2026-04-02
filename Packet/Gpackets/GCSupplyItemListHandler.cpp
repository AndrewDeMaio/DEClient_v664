////////////////////////////////////////////////////////////////////////////////
// Filename    : GCSupplyItemListHandler.cpp
// Written By  : rappi76
// Description :
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSupplyItemList.h"

void GCSupplyItemListHandler::execute ( GCSupplyItemList * pPacket , Player * pPlayer )
{
	__BEGIN_TRY //__BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG
//	__END_DEBUG_EX
	__END_CATCH
}
