//////////////////////////////////////////////////////////////////////
//
// Filename    : LCLoginErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "client_PCH.h"
#include "LCLoginError.h"
#include "UIDialog.h"
#include "MGameStringTable.h"
#include "ClientDef.h"

extern void		PopupErrorMessage(ErrorID errorID);

extern BOOL		g_bNeedUpdate;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LCLoginErrorHandler::execute ( LCLoginError * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__
	//20081224 ũ�������� �̺� �Դϴ�. �ݺ����� ��Ŷ ���� ��� �غ��ô�.
	Sleep(2000);

	//cout << "Access Denied... (" << pPacket->toString() << ")" << endl;
	//throw ProtocolException("Login Failed!");
	// Debug Message

	if (!g_bNeedUpdate)
	{
		// ���Է�
		//SetMode( MODE_MAINMENU );
		g_ModeNext = MODE_LOGIN_WRONG;

		// ETC_ERROR�� ���������� �����̶�� ����ؾ� �Ѵ�.
//		if ((ErrorID)pPacket->getErrorID()==ETC_ERROR)
//		{
//			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_LOGIN_DENY].GetString());
//		}
//		else if ((ErrorID)pPacket->getErrorID() == IP_DENYED )
//		{
//			g_pUIDialog->PopupFreeMessageDlg("You can't play this. Play your country version, Please.");
//		}
//		else
		{
			//g_UIDialog.PopupFreeMessageDlg( pPacket->getMessage().c_str() );
			PopupErrorMessage( (ErrorID)pPacket->getErrorID() );
		}
	}

#endif
		
	__END_CATCH
}
