//----------------------------------------------------------------------
//
// Filename    : GCFriendUpdateConnectHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"

#include "GPacket_PCH.h"
#include "GCFriendUpdateConnect.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendUpdateConnectHandler::execute ( GCFriendUpdateConnect* pPacket, Player* pPlayer )
{	__BEGIN_TRY

#ifdef __GAME_SERVER__


#endif

	if (pPacket)
	{
		// ģ�� �ý��� â�� ������ �´�. ���� ��� ����
		C_VS_UI_FRIEND_SYSTEM* pFriend = (C_VS_UI_FRIEND_SYSTEM*)gpC_window_manager->GetWindowbyName("FriendSystem");
		if (!pFriend)
		{
			pFriend = new C_VS_UI_FRIEND_SYSTEM;
			pFriend->SetWindowName("FriendSystem");
		}

		// ���� ���� ������Ʈ
		int index = pFriend->GetListView()->GetItemIndexByName(pPacket->GetPCName().c_str());
		if (index != -1)
		{
			if (pPacket->GetConnect())
				pFriend->GetListView()->InsertColumnItem("ON",index,2);
			else
				pFriend->GetListView()->InsertColumnItem("OFF",index,2);

			// ���� ������ �������� �ִ´�.
			pFriend->GetListView()->InsertColumnItem(pPacket->GetServerName().c_str(),index,3);
		}
	}
		
	__END_CATCH
}
#endif //__FRIEND_ADDITION