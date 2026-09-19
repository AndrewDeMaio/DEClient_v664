//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopBuyFailHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopBuyFail.h"
#include "ClientDef.h"
#include "UIDialog.h"
#include "TempInformation.h"
#include "MGameStringTable.h"
#include "UIFunction.h"

void GCShopBuyFailHandler::execute ( GCShopBuyFail * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	// mode�� ���ش�.
	g_pTempInformation->SetMode(TempInformation::MODE_NULL);

	// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
	UI_UnlockItemTrade();

	switch (pPacket->getCode())		//���� ������ �ҽ� �ּ��� Ǯ������.	//2008.08.26 shootkj
	{
/*		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY:	//���� ���ڶ���.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_NO_MONEY].GetString() );
			break;

		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE:	// �ڸ��� ���ڶ���.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_NO_SPACE].GetString() );
			break;

		case GC_SHOP_BUY_FAIL_NPC_NOT_EXIST:	// NPC�� �������� �ʴ´�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NPC_NOT_EXIST].GetString() );
			break;

		case GC_SHOP_BUY_FAIL_NOT_NPC:	// NPC��� ������ ���� NPC�� �ƴϴ�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NOT_NPC].GetString() );
			break;

		case GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST:	// ������ ��ġ�� �������� �������� �ʴ´�.
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_ITEM_NOT_EXIST].GetString() );
			break;
*/
			//pPacket->getAmount()	// ������ ����
		// The block above went dark when three of its string IDs were dropped,
		// which left every failure saying "You do not have that item." These
		// two still exist.
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY:
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_NO_MONEY].GetString() );
			break;

		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE:
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_NO_SPACE].GetString() );
			break;
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLACK_STAR :
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_RED_STAR :
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLUE_STAR :
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_GREEN_STAR :
		case GC_SHOP_BUY_FAIL_NOT_ENOUGH_CYAN_STAR :
		default :
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_BUY_NO_ITEM].GetString() );
	}

#endif

	__END_CATCH
}
