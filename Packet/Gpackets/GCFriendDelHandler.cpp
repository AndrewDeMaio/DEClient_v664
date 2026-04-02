//----------------------------------------------------------------------
//
// Filename    : GCFriendDelHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"

#include "GPacket_PCH.h"
#include "GCFriendDel.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendDelHandler::execute ( GCFriendDel* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__


#endif
		
	// ģ�� �ý��� â�� ������ �´�. ���� ��� ����
	C_VS_UI_FRIEND_SYSTEM* pFriend = (C_VS_UI_FRIEND_SYSTEM*)gpC_window_manager->GetWindowbyName("FriendSystem");
	if (!pFriend)
	{
		pFriend = new C_VS_UI_FRIEND_SYSTEM;
		pFriend->SetWindowName("FriendSystem");
	}
	
	// ģ�� �����
	if (!pPacket->GetPCName().empty())
	{
		pFriend->GetListView()->DeleteColumnItem(pPacket->GetPCName().c_str());
	}

	__END_CATCH
}
#endif //__FRIEND_ADDITION