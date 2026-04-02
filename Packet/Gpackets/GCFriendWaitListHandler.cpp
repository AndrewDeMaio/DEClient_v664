//----------------------------------------------------------------------
//
// Filename    : GCFriendWaitListHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"

#include "GPacket_PCH.h"
#include "GCFriendWaitList.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendWaitListHandler::execute ( GCFriendWaitList* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__


#endif

	// ����� ��� ����
	if (pPacket)
	{
		// ģ�� ����� â�� ������ �´�. ���� ��� ����
		C_VS_UI_FRIEND_WAIT* pFriend = (C_VS_UI_FRIEND_WAIT*)gpC_window_manager->GetWindowbyName("FriendWaitList");
		if (!pFriend)
		{
			pFriend = new C_VS_UI_FRIEND_WAIT;
			pFriend->SetWindowName("FriendWaitList");
		}

		// ��� ���� ģ���� ��Ͽ� �����Ѵ�.
		for(int i = 0; i < pPacket->GetFriendWaitListCount(); ++i)
		{
			FriendWaitInfo* pInfo = pPacket->GetFriendWaitInfo(i);
			if (pInfo)
			{
				int item_index = pFriend->GetListView()->GetItemSize();
				// ģ�� �̸�
				pFriend->GetListView()->InsertColumnItem(pInfo->GetFriendName().c_str(),item_index,0);
			}
		}
	}
		
	__END_CATCH
}
#endif //__FRIEND_ADDITION