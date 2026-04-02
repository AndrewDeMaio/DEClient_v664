//----------------------------------------------------------------------
//
// Filename    : GCFriendReqToDelHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"

#include "GPacket_PCH.h"
#include "GCFriendReqToDel.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendReqToDelHandler::execute ( GCFriendReqToDel* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__


#endif
		
	if (pPacket)
	{
		// ģ�� ����� â�� ������ �´�. ���� ��� ����
		C_VS_UI_FRIEND_WAIT* pFriend = (C_VS_UI_FRIEND_WAIT*)gpC_window_manager->GetWindowbyName("FriendWaitList");
		if (!pFriend)
		{
			pFriend = new C_VS_UI_FRIEND_WAIT;
			pFriend->SetWindowName("FriendWaitList");
		}

		// ��� ���� ģ�� ��Ͽ��� �ش� ģ���� �����Ѵ�.
		int index = pFriend->GetListView()->GetItemIndexByName(pPacket->getPCName().c_str());
		if (index != -1)
		{
			pFriend->GetListView()->DeleteColumnItem(pPacket->getPCName().c_str());
		}
	}

	__END_CATCH
}
#endif //__FRIEND_ADDITION