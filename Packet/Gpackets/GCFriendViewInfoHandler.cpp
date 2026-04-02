//----------------------------------------------------------------------
//
// Filename    : GCFriendViewInfoHandler.cpp
// Written By  : 
// Description :
//
//----------------------------------------------------------------------

// include files
//#include "VS_UI_Friend_System.h"
//#include "MZoneTable.h"

#include "GPacket_PCH.h"
#include "GCFriendViewInfo.h"
#include "Assert.h"

#ifdef __GAME_SERVER__

#endif

#if __CONTENTS(__FRIEND_ADDITION)
void GCFriendViewInfoHandler::execute ( GCFriendViewInfo* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__ 


#endif

	if (pPacket)
	{
		// ģ�� ����â�� ������ �´�. ���� ��� ����
		C_VS_UI_FRIEND_INFO* pFriend = (C_VS_UI_FRIEND_INFO*)gpC_window_manager->GetWindowbyName("FriendInfo");
		if (!pFriend)
		{
			pFriend = new C_VS_UI_FRIEND_INFO;
			pFriend->SetWindowName("FriendInfo");
		}

		// ģ�� ������ �����Ѵ�.
		pFriend->SetUserName(pPacket->GetFriendDetailInfo().GetFriendName().c_str());
		pFriend->SetUserGrade((unsigned char)pPacket->GetFriendDetailInfo().GetRank());
		pFriend->SetUserLevel((unsigned char)pPacket->GetFriendDetailInfo().GetLevel());
		pFriend->SetUserAdvLevel((unsigned char)pPacket->GetFriendDetailInfo().GetAdvLevel());
		pFriend->SetUserDomain((unsigned char)pPacket->GetFriendDetailInfo().GetSkillDomainType());
		pFriend->SetUserSociety(pPacket->GetFriendDetailInfo().GetGuildName().c_str());
		pFriend->SetUserSocietyID(pPacket->GetFriendDetailInfo().GetGuildID());
		pFriend->SetUserPropensity(pPacket->GetFriendDetailInfo().GetAlignment());
		pFriend->SetUserContribute(pPacket->GetFriendDetailInfo().GetContributePoint());

		// �޸�� ������ ������ ���� �ʴ´�.
		if (!pPacket->GetFriendIndividualOptionInfo().GetMemo().empty())
			pFriend->SetUserMemo(pPacket->GetFriendIndividualOptionInfo().GetMemo().c_str());

		// �� ���� ����
		std::string zone_id = "";
		if (g_pZoneTable->Get(pPacket->GetFriendDetailInfo().GetZoneID()) != NULL)
		{
			zone_id = g_pZoneTable->Get(pPacket->GetFriendDetailInfo().GetZoneID())->Name;
			if (!zone_id.empty())
				pFriend->SetUserLocation(zone_id.c_str());
			else
				pFriend->SetUserLocation("Unknown");//�˼� ���� by viva
		}
		else
			pFriend->SetUserLocation("Unknown");//�˼� ���� by viva

		// ä�� ������ ģ�� ����Ʈ���� ������ �´�.
		// �� ������ �״� ���� �����Ƿ� ���߿� ������ �ٲٵ��� �Ѵ�.
		C_VS_UI_FRIEND_SYSTEM* pFriendSystem = (C_VS_UI_FRIEND_SYSTEM*)gpC_window_manager->GetWindowbyName("FriendSystem");
		if (pFriendSystem)
		{
			int index = pFriendSystem->GetListView()->GetItemIndexByName(pPacket->GetFriendDetailInfo().GetFriendName().c_str());
			if (index != -1 && index < pFriendSystem->GetListView()->GetItemSize())
			{
				std::string server = pFriendSystem->GetListView()->GetItemNameByIndex(index,3);
				pFriend->SetUserServer(server.c_str());
			}
		}

		pFriend->Start();
	}

	__END_CATCH
}
#endif //__FRIEND_ADDITION