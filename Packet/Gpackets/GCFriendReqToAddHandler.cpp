//----------------------------------------------------------------------
//
// Filename    : GCFriendReqToAddHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"

#include "GPacket_PCH.h"
#include "GCFriendReqToAdd.h"
#include "Types/FriendType.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendReqToAddHandler::execute ( GCFriendReqToAdd* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__


#endif

	if (pPacket)
	{
		C_VS_UI_FRINEND_MESSAGE_BOX* pFriendPacket = (C_VS_UI_FRINEND_MESSAGE_BOX*)gpC_window_manager->GetWindowbyName("FriendRequestAddMessage");
		if (pFriendPacket)
		{
			if (pFriendPacket->Running())
			{
				pFriendPacket->Finish();
				DeleteNew(pFriendPacket);
			}
			else
			{
				DeleteNew(pFriendPacket);
			}
		}

		switch (pPacket->GetResultCode())//by viva translation
		{
		case FRIEND_REQ_TO_ADD_RESULT_CODE_SUCCESS:								// �߰� ��û ����
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("Friend requests have been processed successfully.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_CAN_NOT_ADD_SELF:					// �ڱ� �ڽ��� �߰��� �� ����
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("You can't add yourself as friend.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_EXCEED_MAX_LIST_COUNT_BY_SELF:		// �ڽ��� ģ�� �ִ� ��� ���� �ʰ� 
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_EXCEED_MAX_LIST_COUNT_BY_OTHER:		// ������ ģ�� �ִ� ��� ���� �ʰ�
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("This person can't add anymore friends.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_EXCEED_MAX_WAITLIST_COUNT_BY_OTHER:	// ������ ģ�� �ִ� ��� ��� ���� �ʰ�
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("The other side of the wait list is full.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_ALREADY_EXIST_FRIEND_IN_WAIT_LIST:	// �̹� ����Ͽ� ������ 
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("Add a friend is already applied for a target.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_ALREADY_EXIST_FRIEND:				// �̹� �߰��� ģ��
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("The person is already in your friends list.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_NOT_EXIST_NAME:						// �������� �ʴ� �̸���
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("The name does not exist.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_DIFFERENT_RACE:						// ���� �ٸ� ������
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("Different race cannot be added as a friend.");
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		case FRIEND_REQ_TO_ADD_RESULT_CODE_DENY_ADD_REQUEST:					// ģ�� �߰� ��û�� �ź���
			pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("The friend request have been denied."); 
			pFriendPacket->SetWindowName("FriendRequestAddMessage");
			pFriendPacket->Start();
			break;
		}
	
		// ģ�� ����� â�� ������ �´�. ���� ��� ����
		C_VS_UI_FRIEND_WAIT* pFriend = (C_VS_UI_FRIEND_WAIT*)gpC_window_manager->GetWindowbyName("FriendWaitList");
		if (!pFriend)
		{
			pFriend = new C_VS_UI_FRIEND_WAIT;
			pFriend->SetWindowName("FriendWaitList");
		}

		// ��� ���� ģ�� ��Ͽ��� �ش� ģ���� �����Ѵ�.
		int index = pFriend->GetListView()->GetItemIndexByName(pPacket->GetPCName().c_str());
		if (index != -1)
		{
			pFriend->GetListView()->DeleteColumnItem(pPacket->GetPCName().c_str());
		}
	}
	
	__END_CATCH
}
#endif //__FRIEND_ADDITION