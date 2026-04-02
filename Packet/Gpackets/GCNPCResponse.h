//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCResponse.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_RESPONSE_H__
#define __GC_NPC_RESPONSE_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	// Ŭ���̾�Ʈ�� �Ͽ��� ������ �������̽��� ������ �ϴ� �ڵ�
	NPC_RESPONSE_INTERFACE_REPAIR = 0,
	NPC_RESPONSE_INTERFACE_STASHOPEN,
	NPC_RESPONSE_INTERFACE_SILVER_COATING,
	NPC_RESPONSE_INTERFACE_CREATE_GUILD,
	NPC_RESPONSE_INTERFACE_DESTROY_GUILD,
	NPC_RESPONSE_INTERFACE_NEWBIE_ITEM,
	NPC_RESPONSE_INTERFACE_TUTORIAL_COMPUTER,
	NPC_RESPONSE_INTERFACE_TUTORIAL_BRIEFING,
	NPC_RESPONSE_INTERFACE_TUTORIAL_BOOKCASE,
	NPC_RESPONSE_INTERFACE_HELICOPTER,

	// ...
	NPC_RESPONSE_QUIT_DIALOGUE,
	NPC_RESPONSE_HEAL,

	// Ŭ���̾�Ʈ�� ��Ŷ�� ���� ���� �ڵ�
	NPC_RESPONSE_REPAIR_OK,
	NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST,
	NPC_RESPONSE_REPAIR_FAIL_ITEM_TYPE,
	NPC_RESPONSE_REPAIR_FAIL_MONEY,

	NPC_RESPONSE_STASH_SELL_OK,
	NPC_RESPONSE_STASH_SELL_FAIL_MAX,
	NPC_RESPONSE_STASH_SELL_FAIL_MONEY,

	NPC_RESPONSE_SILVER_COATING_OK,
	NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_NOT_EXIST, 
	NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_TYPE,
	NPC_RESPONSE_SILVER_COATING_FAIL_MONEY,

	NPC_RESPONSE_DONATION_OK,
	NPC_RESPONSE_DONATION_FAIL_MONEY,

	// �ӽÿ� ���̵�
	// ������ ��ġ���� �౸���� ���� ����� ���� ����� NPC Response�� ����ؼ� ���δ�.
	NPC_RESPONSE_DECREASE_BALL,

	// ��� ����
	NPC_RESPONSE_TEAM_REGIST_FAIL_ALREADY_JOIN,			// ��� �ѹ� ����? �ڳ״� �̹� <team_name> �� �Ҽ��̶�� ���� �ֱ�
	NPC_RESPONSE_TEAM_REGIST_FAIL_QUIT_TIMEOUT,			// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
	NPC_RESPONSE_TEAM_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_TEAM_REGIST_FAIL_LEVEL,				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�
	NPC_RESPONSE_TEAM_REGIST_FAIL_MONEY,				// ���� ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...
	NPC_RESPONSE_TEAM_REGIST_FAIL_FAME,					// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
	NPC_RESPONSE_TEAM_REGIST_FAIL_NAME,					// �� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����
	NPC_RESPONSE_TEAM_REGIST_FAIL_DENY,					// �źεǾ����ϴ�.

	NPC_RESPONSE_TEAM_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� ���� ���ԵǾ� �ֽ��ϴ�.
	NPC_RESPONSE_TEAM_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
	NPC_RESPONSE_TEAM_STARTING_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_TEAM_STARTING_FAIL_LEVEL,				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.
	NPC_RESPONSE_TEAM_STARTING_FAIL_MONEY,				// <player_name>, �� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�
	NPC_RESPONSE_TEAM_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
	NPC_RESPONSE_TEAM_STARTING_FAIL_DENY,				// �źεǾ����ϴ�.

	NPC_RESPONSE_CLAN_REGIST_FAIL_ALREADY_JOIN,			// ��� �ѹ� ����? �ڳ״� �̹� <clan_name> Ŭ���� ������ ���� ���¶�� ���� �ֱ�
	NPC_RESPONSE_CLAN_REGIST_FAIL_QUIT_TIMEOUT,			// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. ���� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�
	NPC_RESPONSE_CLAN_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_CLAN_REGIST_FAIL_LEVEL,				// �Ǹ������� ��θӸ��ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�.
	NPC_RESPONSE_CLAN_REGIST_FAIL_MONEY,				// Ŭ���� ����Ϸ��� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ����̴±�...
	NPC_RESPONSE_CLAN_REGIST_FAIL_FAME,					// <player_name>�̶�.. ���� � �����̾��ΰ�����. �� ���� �Ǹ� ���ð� �ٽ� ã�ƿ��Գ�.
	NPC_RESPONSE_CLAN_REGIST_FAIL_NAME,					// 
	NPC_RESPONSE_CLAN_REGIST_FAIL_DENY,					// �źεǾ����ϴ�.

	NPC_RESPONSE_CLAN_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� Ŭ���� ���ԵǾ� �ֽ��ϴ�.
	NPC_RESPONSE_CLAN_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. ���� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�
	NPC_RESPONSE_CLAN_STARTING_FAIL_CANCEL_TIMEOUT,		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_CLAN_STARTING_FAIL_LEVEL,				// �Ǹ��� �����ڰ� �Ǳ⿡�� ������ �� ������ �� ����. ���� ���� ������ �ϰ� ���Գ�
	NPC_RESPONSE_CLAN_STARTING_FAIL_MONEY,				// ����� �����ص� Ŭ���� ������ �� �ִ� ���� �����ϸ� �� Ŭ���� �������� ��������
	NPC_RESPONSE_CLAN_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
	NPC_RESPONSE_CLAN_STARTING_FAIL_DENY,				//  �źεǾ����ϴ�.

	NPC_RESPONSE_GUILD_SHOW_REGIST,				// ��� ��� â ����
	NPC_RESPONSE_GUILD_SHOW_STARTING_JOIN,		// ��� ��Ÿ�� ��� ���� â ����
	NPC_RESPONSE_GUILD_SHOW_JOIN,				// ��� ���� â ����
	NPC_RESPONSE_GUILD_SHOW_QUIT,				// ��� Ż�� â ����
	NPC_RESPONSE_GUILD_ERROR,					// ��� ����

	NPC_RESPONSE_TRADE_GIFT_BOX_OK,				// ���� ���� ��ȯ ����
	NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM,		// ���� ���� ����
	NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE,	// ���� ���ڸ� �̹� �ѹ� ��ȯ�ߴ�.
	NPC_RESPONSE_TRADE_GIFT_BOX_ERROR,			// ���� ���� ��ȯ�� ���� ��Ÿ ����

	NPC_RESPONSE_REWARD_OK,		            	// ������ �޾ҽ��ϴ�.
	NPC_RESPONSE_REWARD_FAIL,		            // ������ ���� �� �����ϴ�.
	NPC_RESPONSE_NO_EMPTY_SLOT,		            // �� �ڸ��� �����ϴ�.

	NPC_RESPONSE_SHOW_TAX_BALANCE,				// ���� �׿��ִ� ������ �ܾ��� �����ش�.
	NPC_RESPONSE_WITHDRAW_TAX_OK,				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
	NPC_RESPONSE_WITHDRAW_TAX_FAIL,				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.

	NPC_RESPONSE_NO_GUILD,						// ��(Ŭ��)�� �ҼӵǾ� ���� �ʽ��ϴ�.
	NPC_RESPONSE_NOT_GUILD_MASTER,				// ��(Ŭ��) �����Ͱ� �ƴմϴ�.
	NPC_RESPONSE_HAS_NO_CASTLE,					// ��(Ŭ��)�� ���� ���� �����ϴ�.
	NPC_RESPONSE_NOT_YOUR_CASTLE,				// ��(Ŭ��)�� ������ ���� �ƴմϴ�.

	// �������
	NPC_RESPONSE_NOT_ENOUGH_MONEY,				// ���� �����մϴ�.(�����û�� ���������� ���������� ������ -_-;)
	NPC_RESPONSE_WAR_SCHEDULE_FULL,				// ���� �������� �� á���ϴ�.
	NPC_RESPONSE_WAR_ALREADY_REGISTERED,		// �̹� ������ ��û�߾����ϴ�.
	NPC_RESPONSE_WAR_REGISTRATION_OK,			// ���� �����쿡 ��� �Ǿ����ϴ�.
	NPC_RESPONSE_ALREADY_HAS_CASTLE,			// �̹� ���� ������ �ֽ��ϴ�.
	NPC_RESPONSE_WAR_UNAVAILABLE,				// ������ ���� ��û�� ���� �ʽ��ϴ�.

	// ���� ���� ����
	NPC_RESPONSE_RACE_WAR_JOIN_FAILED,			// <�����> �� �������� ���� ���� ��û�ο��� �� á���ϴ�.
	NPC_RESPONSE_RACE_WAR_JOIN_OK,				// ���� ���� ���� ��û�� �߽��ϴ�.
	NPC_RESPONSE_RACE_WAR_GO_FIRST_SERVER, 		// ���� ������ �� ������ ù��° ���������� ��û �� ������ �����մϴ�.

	// �̺�Ʈ ����������
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW,		// ������ �̺�Ʈ �������� ���� �� �����ϴ�.
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL,			// �̺�Ʈ �������� ���� �� �����ϴ�.
	NPC_RESPONSE_GIVE_EVENT_ITEM_OK,			// �̺�Ʈ�� ���� �������� �޾ҽ��ϴ�.
	NPC_RESPONSE_GIVE_PREMIUM_USER_ONLY,		// �����̾����� ����ڸ� ���� �� �ֽ��ϴ�.

	// Ŀ�ý�û ����
	NPC_RESPONSE_WAIT_FOR_MEET_COUPLE,			// Ŀ�� ��û �� ����� �̸��� �Է��ϼ���
	NPC_RESPONSE_COUPLE_MEET_SUCCESS,			// Ŀ���� ����Ǿ����ϴ�.
	NPC_RESPONSE_COUPLE_CANNOT_MEET,			// Ŀ���� ����� �� �����ϴ�. CoupleMessage Enum ���
	NPC_RESPONSE_MEET_WAIT_TIME_EXPIRED,		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.

	NPC_RESPONSE_WAIT_FOR_APART_COUPLE,			// ����� ����� �̸��� �Է��ϼ���
	NPC_RESPONSE_COUPLE_APART_SUCCESS,			// ��������ϴ�.
	NPC_RESPONSE_NOT_COUPLE,					// Ŀ���� �ƴ϶� ����� �� �����ϴ�. CoupleMessage Enum ���
	NPC_RESPONSE_APART_WAIT_TIME_EXPIRED,		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.

	NPC_RESPONSE_APART_COUPLE_FORCE,			// �Ϲ������� ����� ����� �̸��� �Է��ϼ���.
	NPC_RESPONSE_QUEST,							// ����Ʈ ���� �޽��� --;
	NPC_RESPONSE_LOTTERY,                       // ���� �����ֱ�
	NPC_RESPONSE_CANNOT_BUY,                    // ������ ������ �������� ã�� �� �����ϴ�.
	
	NPC_RESPONSE_CLEAR_RANK_BONUS_OK,           // �����Ͻ� ����� ��ų�� ���� �Ǿ����ϴ�.
    NPC_RESPONSE_NO_RANK_BONUS,                 // �ش� �ڰ��� �����ϴ�.
    NPC_RESPONSE_ALREADY_CLEAR_RANK_BONUS,      // �����Ͻ� ��� ��ų�� ������ ���� �ֽ��ϴ�.
    NPC_RESPONSE_GNOME_CONTRACT_OK,             // ���� ���ɰ��� ����� �ξ����ϴ�.
    NPC_RESPONSE_DOWN_SKILL,                    // �ٿ��ų ��ų�� �����ϼ���>.<
	
		// �ƿ콺���� ��� ����
	NPC_RESPONSE_GUILD_REGIST_FAIL_ALREADY_JOIN,		// ��� �ѹ� ����? �ڳ״� �̹� <guild_name> ��� �Ҽ��̶�� ���� �ֱ�
	NPC_RESPONSE_GUILD_REGIST_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
	NPC_RESPONSE_GUILD_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_GUILD_REGIST_FAIL_LEVEL,				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�
	NPC_RESPONSE_GUILD_REGIST_FAIL_MONEY,				// ��带 ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...
	NPC_RESPONSE_GUILD_REGIST_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
	NPC_RESPONSE_GUILD_REGIST_FAIL_NAME,				// ��� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����
	NPC_RESPONSE_GUILD_REGIST_FAIL_DENY,				// �źεǾ����ϴ�.

	NPC_RESPONSE_GUILD_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� ��忡 ���ԵǾ� �ֽ��ϴ�.
	NPC_RESPONSE_GUILD_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�
	NPC_RESPONSE_GUILD_STARTING_FAIL_CANCEL_TIMEOUT,	// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�
	NPC_RESPONSE_GUILD_STARTING_FAIL_LEVEL,				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.
	NPC_RESPONSE_GUILD_STARTING_FAIL_MONEY,				// <player_name>, ��� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�
	NPC_RESPONSE_GUILD_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�
	NPC_RESPONSE_GUILD_STARTING_FAIL_DENY,				// �źεǾ����ϴ�.

	// 2004, 8, 26, sobeit add start - ������ ����
	NPC_RESPONSE_TOO_MANY_GUILD_REGISTERED,             // ���� ��û�� ��尡 �ʹ� ���Ƽ� ��û�� �� �����ϴ�.   // 120
    NPC_RESPONSE_REINFORCE_DENYED,                      // ������ ���� ��û�� �̹� �źδ��ؼ� ���û �� �� �����ϴ�.    // 121
    NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED,            // ������ ���� ��û�� �㰡�� ��尡 �̹� �־ ��û�� �� �����ϴ�. // 122
    NPC_RESPONSE_NO_WAR_REGISTERED,                     // ���� ��û�� ��尡 ��� ������ ���� ��û�� �� �� �����ϴ�. 

	NPC_RESPONSE_CANNOT_ACCEPT,                         // ������ ���� ��û�� ������ �� �����ϴ�.
    NPC_RESPONSE_ACCEPT_OK,                             // ���� ��û�� �����Ͽ����ϴ�.
	NPC_RESPONSE_CANNOT_DENY,							// ������ ���� ��û�� �ź��� �� �����ϴ�.
    NPC_RESPONSE_DENY_OK,                               // ���� ��û�� �ź��Ͽ����ϴ�.

	// 2004, 8, 26, sobeit add end - ������ ����

	// 2004, 10, 25, sobeit add start
	NPC_RESPONSE_SHOW_TAX_RATIO,						// ������ �춧�� ���� ����
	NPC_RESPONSE_MODIFY_TAX_RATIO_OK,					// ���� ���� ������~
	NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL,					// ���� ���� ����
	// 2004, 10, 25, sobeit add end

	NPC_RESPONSE_SWAP_ADVANCEMENT_ITEM,                 // ���� ���������� ��ȯ���ش�.
    NPC_RESPONSE_NOT_ADVANCED,                          // �������� �ʾƼ� ������ ��ȯ�� �ȵ˴ϴ�.

	NPC_RESPONSE_SHOW_DONATION_DAILOG,                  // ���â�� ����.
    NPC_RESPONSE_SHOW_DONATION_COMPLETE_DAILOG,         // ��� ���� â�� ����.

	NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG,    // �̺�Ʈ ������ �ޱ� Ȯ�� ���̾�α׸� ����.
	NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG,            // ���� �޽��� ���̾�α׸� ����.

	NPC_RESPONSE_SHOW_DONATION_WEDDING_COMPLETE_DIALOG, // ��μ���â�� ����.
	NPC_RESPONSE_SHOW_ALEADY_DONATED_DIALOG,			// �̹� ���Ǳ��� ���̽��ϴ�.

	NPC_RESPONSE_NOT_CAHNGE_COLOR,                      // ������ �ߺ��Ǿ� �ٲܼ� ����.
    NPC_RESPONSE_NOT_ENOUGH_MONEY_CAHNGE_COLOR,         // ���� ������� �ʾ� ������ �ٲܼ� ����.
    NPC_RESPONSE_CHANGE_COLOR_OK,                       // ������ �Ϸ� �Ǿ����ϴ�.
	
	NPC_NOT_ENOUGH_EXCHANGE_OF_MONEY,                   // ���� ������� �ʾ� ��ǥ�� �ٲܼ� ����
    NPC_ENOUGH_PLAYER_MONEY,                            // �÷��̾��� �������� �ִ� �����ݾ��� �Ѿ���
    NPC_NOT_ENOUGH_CHECK_MONEY,                         // ��ǥ�� ����!
    NPC_EXCHANGE_OF_MONEY_OK,                           // ���������� �ŷ��� �Ϸ� �Ǿ����ϴ�
	NPC_NOT_ENOUGH_SOCCER_BALL,
	NPC_NOT_ENOUGH_EXCHANGE_SEALING_STONE,

	NPC_RESPONSE_NOT_ENOUGH_LEVEL,                      // ������ ��� ���� �ʴ� 
    NPC_RESPONSE_NOT_ENOUGH_GUILD_MEMBER,               // ������ �����ϴ� 
    NPC_RESPONSE_NOT_ENOUGH_GUILD_LEVEL,                // ������ ��� ������ �����ϴ� 

	NPC_RESPONSE_NOT_ENTER_SURVIVAL_ZONE,				// �����̹� ���� ���� �Ұ����ϴ�. (���� �Ұ��� �ð�, ���� �ο�)

	NPC_RESPONSE_GIVE_GAMBLE_ITEM_OK,					// �׺����� �������� �޾��� ��
	NPC_RESPONSE_GAMBLE_INIT_OK,						// �׺� �������� �ʱ�ȭ �� ��

	NPC_NOT_ENOUGH_EVENT_ITEM,							// ��ȯ�� �ʿ��� �̺�Ʈ �������� ������ ��
	NPC_NOT_ENOUGH_ITEM,								// ��ȯ�� �ʿ��� �������� ������ ��

	NPC_RESPONSE_DENY_ATTEND,                           // �ű� ���� ȸ���� �̺�Ʈ�� ���� ���� �մϴ�.
    NPC_RESPONSE_TODAY_NOT_ATTEND,                      // �̹� �⼮ �ϼ̽��ϴ�. ���� �ٽ� ������ �ּ���.
	NPC_RESPONSE_CHECK_COUNT_ATTEND,					// [ĳ����]���� [�⼮ üũ ȸ��]�� �⼮�ϼ̽��ϴ�.

#if __CONTENTS(__BLITZ_COUPON_EVENT)
	NPC_RESPONSE_BLITZ_COUPON,							// ���������� ���� ���� ����
	NPC_RESPONSE_REWORD_ITEM_OK,						// ������ ����� �����۸����� �����ִ� ���̾�α׶�ﶧ
#endif //__BLITZ_COUPON_EVENT
#if __CONTENTS(__REPAIRSYSTEM_RENEWAL)
	NPC_RESPONSE_REPAIR_FAIL_NOT_NEED,
#endif //__REPAIRSYSTEM_RENEWAL
	NPC_RESPONSE_MAX
};

enum CommonMessage
{
	YOU_CAN_GET_EVENT_200412_COMBACK_ITEM = 0,          // 0    �Ĺ� ����� �������� ���� �� �ֽ��ϴ�.
	YOU_CAN_GET_EVENT_200412_COMBACK_PREMIUM_ITEM,      // 1    �Ĺ� ����� ���� �������� ���� �� �ֽ��ϴ�.
	YOU_CAN_GET_EVENT_200412_COMBACK_RECOMMEND_ITEM,    // 2    �Ĺ� ����� ��õ �������� ���� �� �ֽ��ϴ�.
	YOU_GET_EVENT_ITEM,                                 // 3    �̺�Ʈ �������� �޾ҽ��ϴ�.
	NOT_ENOUGH_INVENTORY_SPACE,                         // 4    �κ��丮�� ������ �����մϴ�.
	ALEADY_GET_EVENT_ITEM,                              // 5    �̹� �̺�Ʈ �������� �����ϼ̽��ϴ�.
	FAIL_GET_EVENT_ITEM,                                // 6    �̺�Ʈ ������ �ޱ� ����
	YOU_ARE_NOT_EVENT_USER,                             // 7    �̺�Ʈ ����ڰ� �ƴ�

	YOU_CAN_GET_EVENT_200507_COMEBACK_ITEM,				// 8	�Ĺ� ����� �������� ���� �� �ֽ��ϴ�. 2005.7
	YOU_CAN_GET_EVENT_200507_COMEBACK_PREMIUM_ITEM,		// 9	�Ĺ� ����� ���� �������� ���� �� �ֽ��ϴ�. 2005.7
	YOU_CAN_GET_EVENT_200507_COMEBACK_RECOMMEND_ITEM,	// 10	�Ĺ� ����� ��õ �������� ���� �� �ֽ��ϴ�. 2005.7
	
	YOU_CAN_GET_EVENT_COMEBACK_200604_ITEM,				// 11   �Ĺ� ����� �������� ���� �� �ֽ��ϴ�. 2006.4
	YOU_CAN_GET_EVENT_COMEBACK_200604_PREMIUM_ITEM,     // 12   �Ĺ� ����� ���� �������� ���� �� �ֽ��ϴ�. 2006.4

	COMMON_MESSAGE_MAX
};

enum CoupleMessage
{
	COUPLE_MESSAGE_NOT_EVENT_TERM = 1,			// Ŀ�� �̺�Ʈ �Ⱓ�� �ƴմϴ�.
	COUPLE_MESSAGE_ALREADY_WAITING,				// �̹� ��븦 ��ٸ��� �ֽ��ϴ�.
	COUPLE_MESSAGE_LOGOFF,						// ������ �α��� ���� �ʾҽ��ϴ�.
	COUPLE_MESSAGE_DIFFERENT_RACE,				// ���� �ٸ� �����Դϴ�.
	COUPLE_MESSAGE_SAME_SEX,					// ���� ���̿��� Ŀ���� �����˴ϴ�.
	COUPLE_MESSAGE_NOT_PAY_PLAYER,				// ���� ����ڰ� �ƴմϴ�.
	COUPLE_MESSAGE_ALREADY_COUPLE,				// �̹� Ŀ���Դϴ�.
	COUPLE_MESSAGE_WAS_COUPLE,					// Ŀ���� ���� ���� �ֽ��ϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_GOLD,				// �������� �����մϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_ATTR,				// �ɷ�ġ�� �����մϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_LEVEL,			// ������ �����մϴ�.
	COUPLE_MESSAGE_INVENTORY_FULL,				// Ŀ�ø��� ���� ������ �����մϴ�.
	COUPLE_MESSAGE_NO_WAITING,					// ����� ��ٸ��� ��Ʈ�ʰ� �����ϴ�.
	COUPLE_MESSAGE_NOT_COUPLE,					// Ŀ���� �ƴմϴ�.

	COUPLE_MESSAGE_MAX
};

enum QuestMessage
{
	START_SUCCESS = 0,
	START_FAIL_QUEST_NUM_EXCEEDED,
	START_FAIL_DUPLICATED_QUEST_ID,
	START_FAIL_PC,
	COMPLETE_SUCCESS,
	COMPLETE_FAIL_NOT_COMPLETE,
	COMPLETE_FAIL_NO_INVENTORY_SPACE,
    COMPLETE_FAIL_NOT_IN_QUEST,
    COMPLETE_FAIL_TIME_EXPIRED,
	START_FAIL_CANNOT_APPLY_QUEST,
	CANCEL_SUCCESS,
	CANCEL_NOT_IN_QUEST,
	COMPLETE_FAIL_INVALID_NPC,
	
	FAIL_BUG
};




//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponse
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponse : public Packet 
{

public:
	GCNPCResponse() { m_Code = NPC_RESPONSE_MAX; m_Parameter = 0;}
	virtual ~GCNPCResponse() {}

public:
	void read(SocketInputStream & iStream);
	void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_GC_NPC_RESPONSE; }
	size_t getPacketSize() const;
#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const { return "GCNPCResponse"; }
	std::string toString() const;
#endif 
	
public:
	BYTE getCode(void) const { return m_Code;}
	void setCode(WORD code) { m_Code = code;}

	uint getParameter(void) const { return m_Parameter; }
	void setParameter(uint parameter) { m_Parameter = parameter; }

private: 
	BYTE m_Code;
	uint m_Parameter;

};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponseFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponseFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCNPCResponse(); }
	std::string getPacketName() const { return "GCNPCResponse"; }
	PacketID_t getPacketID() const { return Packet::PACKET_GC_NPC_RESPONSE; }
	PacketSize_t getPacketMaxSize() const { return szBYTE + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponseHandler
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponseHandler 
{
public:
	static void execute( GCNPCResponse* pPacket, Player* pPlayer);
};

#endif
