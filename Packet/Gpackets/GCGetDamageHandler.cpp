//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGetDamageHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGetDamage.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"
#include "MTopView.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGetDamageHandler::execute ( GCGetDamage * pGCGetDamage , Player * pPlayer )
{
	__BEGIN_TRY

	// The game server sends this to the player who swung, one per monster hit
	// (the final damage) or missed (0xFFFF), for the floating number over it.
	// It used to play a hit reaction here, but the server never sent the
	// packet until the floating numbers, so that path never ran.
	if (g_pTopView != NULL)
	{
		g_pTopView->AddFloatingDamage(pGCGetDamage->getObjectID(), pGCGetDamage->getDamage());
	}

	__END_CATCH
}
