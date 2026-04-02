////////////////////////////////////////////////////////////////////////////////
// Filename    : GCGoodsListHandler.cpp
// Written By  : �輺��
// Description :
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGoodsList.h"
#include "ClientDef.h"
#include "UIFunction.h"

void GCGoodsListHandler::execute ( GCGoodsList * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

	UI_RunItemShop( pPacket );			

	__END_CATCH
}
