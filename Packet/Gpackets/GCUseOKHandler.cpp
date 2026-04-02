
//////////////////////////////////////////////////////////////////////
//
// Filename    : GCUseOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCUseOK.h"
#include "ClientDef.h"
#include "MInventory.h"
#include "MQuickSlot.h"
#include "MSlayerGear.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCUseOKHandler::execute ( GCUseOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	// message

	// ��.. cut & paste�� ����.. - -;;

	UseItemOK();

	//------------------------------------------------------------------
	//
	//						���°��� �ٲ۴�.
	//
	//------------------------------------------------------------------
	AffectModifyInfo( g_pPlayer, pPacket );


	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );

#endif

	__END_CATCH
}
