//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddNicknameHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddNickname.h"
//#include "VS_UI.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddNicknameHandler::execute ( GCAddNickname * pGCAddNickname , Player * pPlayer )
{
	__BEGIN_TRY
#ifdef __GAME_CLIENT__

		gC_vs_ui.AddNickNameList((void*)&pGCAddNickname->getNicknameInfo());
		//cout << pGCAddNickname->toString() << endl;


#endif
	__END_CATCH
}
