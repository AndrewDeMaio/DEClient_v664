//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopSellFailHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopSellFail.h"
#include "ClientDef.h"
#include "UIDialog.h"
#include "TempInformation.h"
#include "MGameStringTable.h"
#include "UIFunction.h"

void GCShopSellFailHandler::execute ( GCShopSellFail * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	// mode�� ���ش�.
	g_pTempInformation->SetMode(TempInformation::MODE_NULL);

	// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
	UI_UnlockItemTrade();

	// 2005, 1, 3, sobeit add start - �̱� ����. TempInformation�� ��� �߰� �ؾ� ������.. 
	if(UI_IsRunningSwapAdvancementItem())
		g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[UI_STRING_MESSAGE_SWAP_ADVANCEMENT_ITEM_ERROR].GetString() );
	else
	// 2005, 1, 3, sobeit add end
		g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_SELL].GetString() );

#endif

	__END_CATCH
}
