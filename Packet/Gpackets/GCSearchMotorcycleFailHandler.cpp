//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSearchMotorcycleFailHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSearchMotorcycleFail.h"
#include "ClientDef.h"
#include "MGameStringTable.h"
#include "UIDialog.h"

void GCSearchMotorcycleFailHandler::execute ( GCSearchMotorcycleFail * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__


	if (rand()%2)
	{
		g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_FIND_MOTOR_NO_WHERE].GetString());
	}
	else
	{
		g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_FIND_MOTOR_NO_KEY].GetString());
	}
	
#endif

	__END_CATCH
}
