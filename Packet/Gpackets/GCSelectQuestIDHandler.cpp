
//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSelectQuestIDHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSelectQuestID.h"
#include "ClientDef.h"
#include "TempInformation.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCSelectQuestIDHandler::execute ( GCSelectQuestID * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	
	DEBUG_ADD("[GCSelectQuestIDHandler] Execute");
	// UI_RunQuestList empties the packet, so check first
	bool bNoQuest = pPacket->empty();
	UI_RunQuestList( pPacket );

	if( !bNoQuest )
		g_pTempInformation->SetMode( TempInformation::MODE_SELECT_QUEST );
	
#endif

	__END_CATCH
}
