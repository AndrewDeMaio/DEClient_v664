//----------------------------------------------------------------------
//
// Filename    : GCFriendAddHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"
//#include "MZoneTable.h"

#include "GPacket_PCH.h"
#include "GCFriendAdd.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendAddHandler::execute ( GCFriendAdd* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

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

		// ģ�� ������ ��Ͽ� �߰�
		FriendSimpleInfo pInfo = pPacket->GetFriendSimpleInfo();
		int item_index = pFriend->GetListView()->GetItemSize();
		// ģ�� �̸�
		pFriend->GetListView()->InsertColumnItem(pInfo.GetFriendName().c_str(),item_index,0);
		// �� ���� ����
		std::string zone_id = "";
		if (g_pZoneTable->Get(pInfo.GetZoneID()) != NULL)
		{
			zone_id = g_pZoneTable->Get(pInfo.GetZoneID())->Name.GetString();
			if (!zone_id.empty())
				pFriend->GetListView()->InsertColumnItem(g_pZoneTable->Get(pInfo.GetZoneID())->Name,item_index,1);
			else
				pFriend->GetListView()->InsertColumnItem("�˼� ����",item_index,1);
		}
		else
			pFriend->GetListView()->InsertColumnItem("�˼� ����",item_index,1);
		// ���� ����
		if (pInfo.GetConnect())
			pFriend->GetListView()->InsertColumnItem("ON",item_index,2);
		else
			pFriend->GetListView()->InsertColumnItem("OFF",item_index,2);

		// ���� ������ �������� �ִ´�.
		pFriend->GetListView()->InsertColumnItem(pInfo.GetServerName().c_str(),item_index,3);

		// ģ���� �߰� �Ǿ��ٰ� Ȯ�� �޽����� ������.
		C_VS_UI_FRINEND_MESSAGE_BOX* pFriendPacket = (C_VS_UI_FRINEND_MESSAGE_BOX*)gpC_window_manager->GetWindowbyName("FriendAddOkPopupMessage");
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
		pFriendPacket = new C_VS_UI_FRINEND_MESSAGE_BOX("ģ�� ��Ͽ� ���������� �߰� �Ǿ����ϴ�.");
		pFriendPacket->SetWindowName("FriendAddOkPopupMessage");
		pFriendPacket->Start();
	}
	
	__END_CATCH
}
#endif //__FRIEND_ADDITION