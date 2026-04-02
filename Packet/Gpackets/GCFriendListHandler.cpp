//----------------------------------------------------------------------
//
// Filename    : GCFriendListHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"
//#include "MZoneTable.h"

#include "GPacket_PCH.h"
#include "GCFriendList.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendListHandler::execute ( GCFriendList* pPacket, Player* pPlayer )
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

		// ����Ʈ�� �ֱ��� ���� ����Ʈ�� ��� �����.
		pFriend->GetListView()->DeleteAllItem(); 

		// ģ�� ������ ��Ͽ� �߰�
		for(int i = 0; i < pPacket->GetFriendListCount(); ++i)
		{
			FriendSimpleInfo* pInfo = pPacket->GetFriendInfo(i);
			if (pInfo)
			{
				int item_index = pFriend->GetListView()->GetItemSize();
				// ģ�� �̸�
				pFriend->GetListView()->InsertColumnItem(pInfo->GetFriendName().c_str(),item_index,0);
				// �� ���� ����
				std::string zone_id = "";
				if (g_pZoneTable->Get(pInfo->GetZoneID()) != NULL)
				{
					zone_id = g_pZoneTable->Get(pInfo->GetZoneID())->Name;
					if (!zone_id.empty())
						pFriend->GetListView()->InsertColumnItem(zone_id.c_str(),item_index,1);
					else
						pFriend->GetListView()->InsertColumnItem("Unknown",item_index,1); //by viva
				}
				else
					pFriend->GetListView()->InsertColumnItem("Unknown",item_index,1); //by viva
				// ���� ����
				if (pInfo->GetConnect())
					pFriend->GetListView()->InsertColumnItem("ON",item_index,2);
				else
					pFriend->GetListView()->InsertColumnItem("OFF",item_index,2);

				// ���� ������ �������� �ִ´�.
				pFriend->GetListView()->InsertColumnItem(pInfo->GetServerName().c_str(),item_index,3);
			}
		}

		// �ɼ� ���� ����
		pFriend->SetCheckConfirm(pPacket->GetFriendGlobalOptionInfo().GetOptionToDenyAddRequest()^1);
	}
		
	__END_CATCH
}
#endif //__FRIEND_ADDITION