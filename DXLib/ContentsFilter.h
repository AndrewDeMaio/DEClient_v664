//-----------------------------------------------------------------------------
// ContentsFilter.h
//-----------------------------------------------------------------------------
// define�� ����Ͽ� �������� ���͸��Ѵ�.
// ���� �ð��� ���͸��ϴ� ���� ��ŷ�� ������ �ֱ� ������
// ������ �ð��� ���͸��ǵ��� �Ѵ�.
//-----------------------------------------------------------------------------

#pragma once

#define __ON	(1)
#define __OFF	(0)

//////////////////////////////////////////////////////////////////////////
// Korea

#ifdef __DESIGNED_KOREA
#define __DESIGN_NAME "Designed Korea"

#	define __ADVANCEMENT_CHARACTER			__ON
#	define __LANGUAGE_CHANGE				__ON

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__ON	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__ON
#	define __SMS_SERVICES					__OFF
#	define __RARE_SKILL						__ON

#	define __INTERNATIONAL_PREMIUM_SYSTEM	__OFF
#	define __NEW_SYSTEM_AVAILABILITIES		__OFF
#	define __ENCHANT_REQUIRE_LEVE			__OFF
#	define __ID_PASSWORD					__OFF

#	define __CHAR_DELETE					__OFF
#	define __KOREAN_UI						__ON
#	define __INTERNATIONAL_UI				__OFF
#	define __ENGLISH_STRFILTER				__OFF
#	define __CRYPT							__OFF
#	define __CONECT_LIMITER					__OFF
#	define __PERSNALSHOP_NAMING				__ON
#	define __HERO_SYSTEM					__ON
#	define __CONTRIBUTE_SYSTEM				__ON
#	define __LEVEL_WAR_RENEWAL				__ON
#	define __SERVER_SELECT_REVEWAL			__ON
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__ON
#	define __2008_NEW_YEAR_EVENT			__ON
#	define __2008_FIRST_CHARGE_ITEM			__ON	// 2008 1�� ���� ������
#	define __DSG_EFFECT						__ON
#	define __GEAR_SWAP_CHANGE				__ON	//								����,	�׼�,	���߼�
#	define __2008_WHITEDAY_LOVECANDY		__ON	// 2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__ON	// 2008 ��ް����� �𷡽ð�				�׼�,	���߼�
#	define __PAYZONE_PASS_TICKET			__ON	// ������ �����
#	define __QUEST_RENEWAL					__ON	//										�׼�,	���߼�
#	define __EFFECT_RENEWAL					__ON	//								����,	�׼�,	���߼�
#	define __SECOND_RARE_SKILL				__ON	//										�׼�,	���߼�
#	define __080405_FIREST_UI_UPDATE		__ON	//										�׼�,	���߼�
#	define __LIMITED_ITEM_UNISEX			__ON	
#	define __FAST_TRANSFORTER				__ON	
#	define __CLOVER_EVENT					__ON
#	define __QUEST_RENEWAL2					__ON	// __QUEST_RENEWAL�� �̸� ��ġ �Ǿ��� __QUEST_RENEWAL2�� ���� �߿� �ִ� �����̴�.
#	define __GORE_BLOOD_BIBLE				__ON	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__ON	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����

#	define __TIPOJYU_CASTLE					__ON
#	define __2008_JUNE_EVENT_EX_STONE		__ON	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __NEW_ADVANCEMENT_ITEM			__ON	// ���ο� ����������
#	define __TUNING_ITEM					__ON	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__OFF	// �Ϻ� ������ ������
#	define __CHINESE_UI						__OFF	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__OFF	// �Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__ON	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__ON	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__ON	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)
#	define __AUTO_ITEM_ROOTING				__OFF	// ������ �ڵ� ���� �ڵ�(�׽�Ʈ �ڵ��� �����)
#	define __LOCALIZING_LONGNAME			__OFF	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__ON	// OX�̺�Ʈ
#	define __ITEM_SHOW						__ON	// ������ ����

#	define __BLITZ_COUPON_EVENT				__ON	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__ON	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__ON	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF	// 
#	define __PREMIUM_GIVE_ITEM_UI			__ON	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ			2008.10.1 ��ġ
#	define __2008_OCTOBER_MAKETITEM			__ON	// 10�� ���� ������
#	define __PREMIUM_CARD					__ON	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__ON	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__ON	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__ON	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__ON	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__ON	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__ON	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__ON	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__ON	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__ON	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__ON	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__ON	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__ON	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__ON	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__ON	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__ON	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__ON	
#	define __CONTRIBUTE_SYSTEM_ITEM			__ON	
#	define __LEVEL_WAR_RENEWAL_ITEM			__ON	
#	define __MENEGROTH_ITEM					__ON
#	define __LC_SELECT_WORLD_ERROR			__ON	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__ON	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__ON	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ����� �ִ� �༮���� ����

#	define __REPAIRSYSTEM_RENEWAL			__ON	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__ON	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__ON	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__ON	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__ON	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__ON	// ���� ����
#	define __THIRD_ENCHANT_2				__ON	// ������þƮ 2
#	define __XTRAP							__OFF	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__OFF	// NProtect �ְ� ����	2021-08-13 off by kim
#	define __PREMIUM_CARD_ADAY				__ON	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__ON	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__ON	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__ON	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__ON	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__ON	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__ON	// PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__ON	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__ON	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__ON	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__ON	// ���Һ��� ������ ������ - 2009.06.29
#	define __AUTO_ATTACT					__OFF	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__OFF	// IMI �������̽�
#	define __DARKEDEN_MARKET				__ON   // �ٵ����� ����
#	define __CREDIT							__ON	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__ON	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__ON	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__ON	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__ON	// ���ø���
#	define __TREASURE_BOX					__ON	// ��������
#	define __PET_CATS						__ON	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__ON	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__ON	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __UPGRADE_MONSTER_PET			__ON	// ���׷��̵� ���� �� - 2009.10.09
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__OFF	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16	
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#	define __OPTION_NAME_PRINT		__ON	// ������ �ɼ� ���̻� ���� - 2021.08.15
#endif	// DESIGNED_KOREA

//////////////////////////////////////////////////////////////////////////
// Internation

#ifdef __DESIGNED_INTERNATION
#define __DESIGN_NAME "Designed Internation"

#	define __ADVANCEMENT_CHARACTER			__OFF
#	define __LANGUAGE_CHANGE				__OFF

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__ON	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__OFF
#	define __SMS_SERVICES					__OFF
#	define __RARE_SKILL						__ON
#	define __INTERNATIONAL_PREMIUM_SYSTEM	__ON

#	define __NEW_SYSTEM_AVAILABILITIES		__ON
#	define __ENCHANT_REQUIRE_LEVE			__ON
#	define __ID_PASSWORD					__ON

#	define __CHAR_DELETE					__ON
#	define __KOREAN_UI						__OFF
#	define __INTERNATIONAL_UI				__ON
#	define __ENGLISH_STRFILTER				__ON
#	define __CRYPT							__ON
#	define __CONECT_LIMITER					__ON
#	define __PERSNALSHOP_NAMING				__OFF

#	define __HERO_SYSTEM					__OFF	//-- ���� ������ ���鶩 ON ���� ������ OFF
#	define __CONTRIBUTE_SYSTEM				__OFF	//-- ���� ������ ���鶩 ON ���� ������ OFF
#	define __LEVEL_WAR_RENEWAL				__OFF	//-- ���� ������ ���鶩 ON ���� ������ OFF
#	define __SERVER_SELECT_REVEWAL			__OFF
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__OFF
#	define __2008_NEW_YEAR_EVENT			__OFF
#	define __2008_FIRST_CHARGE_ITEM			__OFF	// 2008 1�� ���� ������
#	define __DSG_EFFECT						__OFF
#	define __GEAR_SWAP_CHANGE				__OFF	// ���� ���� â
#	define __2008_WHITEDAY_LOVECANDY		__OFF	// 2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__OFF	// 2008 ��ް����� �𷡽ð�
#	define __PAYZONE_PASS_TICKET			__OFF
#	define __QUEST_RENEWAL					__OFF	// ����Ʈ ������
#	define __EFFECT_RENEWAL					__OFF
#	define __SECOND_RARE_SKILL				__OFF
#	define __080405_FIREST_UI_UPDATE		__OFF
#	define __LIMITED_ITEM_UNISEX			__OFF
#	define __FAST_TRANSFORTER				__ON
#	define __CLOVER_EVENT					__OFF
#	define __QUEST_RENEWAL2					__OFF
#	define __GORE_BLOOD_BIBLE				__OFF	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__OFF	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����
#	define __TIPOJYU_CASTLE					__ON
#	define __HERO_CONTRINBUTE_LEVEL			__OFF	// �޳ױ׷ν��� �⿩��, ����, �������� ����Ʈ�� ���� �־� Info  ������ ���鶧�� ON ���� ������ OFF�� �Ѵ�.
#	define __2008_JUNE_EVENT_EX_STONE		__OFF	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __CREATURE_INDEX_BLANK_SUCCESS	__ON	// ũ���� ������ �θ��� ���� �۾��Ұ�� �� �ε��� ���� �ذ�.
#	define __NEW_ADVANCEMENT_ITEM			__OFF	// ���ο� ����������
#	define __TUNING_ITEM					__OFF	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__OFF	// �Ϻ� ������ ������
#	define __CHINESE_UI						__OFF	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__OFF	// �Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__ON	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__ON	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__OFF	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)
#	define __LOCALIZING_LONGNAME			__OFF	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__OFF	// OX�̺�Ʈ
#	define __ITEM_SHOW						__ON	// ������ ����
#	define __BLITZ_COUPON_EVENT				__OFF	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__OFF	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__OFF	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF
#	define __PREMIUM_GIVE_ITEM_UI			__OFF	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ
#	define __2008_OCTOBER_MAKETITEM			__ON	// 10�� ���� ������
#	define __PREMIUM_CARD					__OFF	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__OFF	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__OFF	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__OFF	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__OFF	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__ON	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__OFF	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__OFF	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__OFF	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__ON	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__OFF	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__OFF	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__OFF	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__OFF	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__OFF	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__OFF	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__ON	
#	define __CONTRIBUTE_SYSTEM_ITEM			__OFF	
#	define __LEVEL_WAR_RENEWAL_ITEM			__ON	
#	define __MENEGROTH_ITEM					__ON
#	define __LC_SELECT_WORLD_ERROR			__OFF	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__OFF	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__OFF	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ������ �ִ� �༮���� ����
#	define __REPAIRSYSTEM_RENEWAL			__ON	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__OFF	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__OFF	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__OFF	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__OFF	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__OFF	// ���� ����
#	define __THIRD_ENCHANT_2				__OFF	// ������þƮ 2
#	define __XTRAP							__OFF	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__OFF	// NProtect �ְ� ����
#	define __PREMIUM_CARD_ADAY				__OFF	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__OFF	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__OFF	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__OFF	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__OFF	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__OFF	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__ON   // PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__ON	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__OFF	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__OFF	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__ON	// ���Һ��� ������ ������ - 2009.06.29  ** flipped ON to match item.inf layout **
#	define __AUTO_ATTACT					__OFF	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__OFF	// IMI �������̽�
#	define __DARKEDEN_MARKET				__OFF   // �ٵ����� ����
#	define __CREDIT							__OFF	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__OFF	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__OFF	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__OFF	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__OFF	// ���ø���
#	define __TREASURE_BOX					__OFF	// ��������
#	define __PET_CATS						__OFF	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__OFF	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__OFF	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __UPGRADE_MONSTER_PET			__ON	// ���׷��̵� ���� �� - 2009.10.09
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__OFF	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#endif	// DESIGNED_INTERNATION



//////////////////////////////////////////////////////////////////////////
// China

#ifdef __DESIGNED_CHINA
#define __DESIGN_NAME "Designed China"

#	define __ADVANCEMENT_CHARACTER			__ON
#	define __LANGUAGE_CHANGE				__ON

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__ON	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__OFF
#	define __SMS_SERVICES					__ON
#	define __RARE_SKILL						__ON
#	define __INTERNATIONAL_PREMIUM_SYSTEM	__OFF

#	define __NEW_SYSTEM_AVAILABILITIES		__OFF
#	define __ENCHANT_REQUIRE_LEVE			__OFF
#	define __ID_PASSWORD					__OFF

#	define __CHAR_DELETE					__ON
#	define __INTERNATIONAL_UI				__OFF
#	define __KOREAN_UI						__OFF
#	define __ENGLISH_STRFILTER				__OFF
#	define __CRYPT							__OFF
#	define __CONECT_LIMITER					__OFF
#	define __PERSNALSHOP_NAMING				__ON

#	define __HERO_SYSTEM					__ON
#	define __CONTRIBUTE_SYSTEM				__ON
#	define __LEVEL_WAR_RENEWAL				__ON
#	define __SERVER_SELECT_REVEWAL			__ON
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__ON
#	define __2008_NEW_YEAR_EVENT			__ON
#	define __2008_FIRST_CHARGE_ITEM			__ON	//2008 1�� ���� ������
#	define __DSG_EFFECT						__ON
#	define __GEAR_SWAP_CHANGE				__ON	//���� ���� â
#	define __2008_WHITEDAY_LOVECANDY		__ON	//2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__ON	//2008 ��ް����� �𷡽ð�
#	define __PAYZONE_PASS_TICKET			__ON
#	define __QUEST_RENEWAL					__ON	//����Ʈ ������
#	define __EFFECT_RENEWAL					__ON
#	define __SECOND_RARE_SKILL				__ON
#	define __080405_FIREST_UI_UPDATE		__ON
#	define __LIMITED_ITEM_UNISEX			__ON
#	define __FAST_TRANSFORTER				__ON
#	define __CLOVER_EVENT					__ON
#	define __QUEST_RENEWAL2					__ON
#	define __GORE_BLOOD_BIBLE				__OFF	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__OFF	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����

#	define __TIPOJYU_CASTLE					__OFF
#	define __2008_JUNE_EVENT_EX_STONE		__OFF	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __NEW_ADVANCEMENT_ITEM			__OFF	// ���ο� ����������
#	define __TUNING_ITEM					__OFF	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__OFF	// �Ϻ� ������ ������
#	define __CHINESE_UI						__ON	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__OFF	//�Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__OFF	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__OFF	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__OFF	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)
#	define __LOCALIZING_LONGNAME			__OFF	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__OFF	//OX�̺�Ʈ
#	define __ITEM_SHOW						__OFF	// ������ ����
#	define __BLITZ_COUPON_EVENT				__OFF	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__OFF	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__OFF	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF
#	define __PREMIUM_GIVE_ITEM_UI			__OFF	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ
#	define __2008_OCTOBER_MAKETITEM			__OFF	// 10�� ���� ������
#	define __PREMIUM_CARD					__OFF	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__OFF	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__OFF	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__OFF	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__OFF	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__OFF	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__OFF	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__OFF	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__OFF	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__OFF	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__OFF	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__OFF	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__OFF	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__OFF	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__OFF	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__OFF	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__OFF	
#	define __CONTRIBUTE_SYSTEM_ITEM			__OFF	
#	define __LEVEL_WAR_RENEWAL_ITEM			__OFF	
#	define __MENEGROTH_ITEM					__OFF
#	define __LC_SELECT_WORLD_ERROR			__OFF	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__OFF	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__OFF	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ������ �ִ� �༮���� ����
#	define __REPAIRSYSTEM_RENEWAL			__OFF	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__OFF	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__OFF	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__OFF	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__OFF	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__OFF	// ���� ����
#	define __THIRD_ENCHANT_2				__OFF	// ������þƮ 2
#	define __XTRAP							__OFF	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__OFF	// NProtect �ְ� ����
#	define __PREMIUM_CARD_ADAY				__OFF	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__OFF	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__OFF	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__OFF	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__OFF	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__OFF	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__OFF   // PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__OFF	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__OFF	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__OFF	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__OFF	// ���Һ��� ������ ������ - 2009.06.29
#	define __AUTO_ATTACT					__OFF	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__OFF	// IMI �������̽�
#	define __DARKEDEN_MARKET				__OFF   // �ٵ����� ����
#	define __CREDIT							__OFF	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__OFF	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__OFF	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__OFF	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__OFF	// ���ø���
#	define __TREASURE_BOX					__OFF	// ��������
#	define __PET_CATS						__OFF	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__OFF	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__OFF	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __UPGRADE_MONSTER_PET			__ON	// ���׷��̵� ���� �� - 2009.10.09
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__OFF	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#endif	// __DESIGNED_CHINA



//////////////////////////////////////////////////////////////////////////
// Japan

#ifdef __DESIGNED_JAPAN
#define __DESIGN_NAME "Designed Japan"

#	define __ADVANCEMENT_CHARACTER			__ON
#	define __LANGUAGE_CHANGE				__ON

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__ON	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__OFF
#	define __SMS_SERVICES					__OFF
#	define __RARE_SKILL						__ON
#	define __INTERNATIONAL_PREMIUM_SYSTEM	__OFF

#	define __NEW_SYSTEM_AVAILABILITIES		__OFF
#	define __ENCHANT_REQUIRE_LEVE			__OFF
#	define __ID_PASSWORD					__OFF

#	define __CHAR_DELETE					__ON
#	define __INTERNATIONAL_UI				__OFF
#	define __KOREAN_UI						__OFF
#	define __ENGLISH_STRFILTER				__OFF
#	define __CRYPT							__OFF
#	define __CONECT_LIMITER					__OFF
#	define __PERSNALSHOP_NAMING				__ON

#	define __HERO_SYSTEM					__ON
#	define __CONTRIBUTE_SYSTEM				__ON
#	define __LEVEL_WAR_RENEWAL				__ON
#	define __SERVER_SELECT_REVEWAL			__ON
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__ON
#	define __2008_NEW_YEAR_EVENT			__ON
#	define __2008_FIRST_CHARGE_ITEM			__ON	//2008 1�� ���� ������
#	define __DSG_EFFECT						__ON
#	define __GEAR_SWAP_CHANGE				__ON	//���� ���� â
#	define __2008_WHITEDAY_LOVECANDY		__ON	//2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__ON	//2008 ��ް����� �𷡽ð�
#	define __PAYZONE_PASS_TICKET			__ON
#	define __QUEST_RENEWAL					__ON	//����Ʈ ������
#	define __EFFECT_RENEWAL					__ON
#	define __SECOND_RARE_SKILL				__ON
#	define __080405_FIREST_UI_UPDATE		__ON
#	define __LIMITED_ITEM_UNISEX			__ON
#	define __FAST_TRANSFORTER				__ON
#	define __CLOVER_EVENT					__ON
#	define __QUEST_RENEWAL2					__ON
#	define __GORE_BLOOD_BIBLE				__ON	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__ON	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����

#	define __TIPOJYU_CASTLE					__ON
#	define __2008_JUNE_EVENT_EX_STONE		__ON	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __NEW_ADVANCEMENT_ITEM			__ON	// ���ο� ����������
#	define __TUNING_ITEM					__ON	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__ON	// �Ϻ� ������ ������
#	define __CHINESE_UI						__OFF	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__ON	// �Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__ON	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__ON	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__ON	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)

#	define __LOCALIZING_LONGNAME			__ON	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__ON	// OX�̺�Ʈ
#	define __ITEM_SHOW						__ON	// ������ ����
#	define __BLITZ_COUPON_EVENT				__ON	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__ON	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__ON	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF
#	define __PREMIUM_GIVE_ITEM_UI			__ON	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ
#	define __2008_OCTOBER_MAKETITEM			__ON	// 10�� ���� ������
#	define __PREMIUM_CARD					__ON	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__ON	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__ON	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__ON	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__ON	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__ON	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__ON	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__ON	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__ON	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__ON	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__ON	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__ON	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__ON	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__ON	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__ON	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__ON	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__ON	
#	define __CONTRIBUTE_SYSTEM_ITEM			__ON	
#	define __LEVEL_WAR_RENEWAL_ITEM			__ON	
#	define __MENEGROTH_ITEM					__ON
#	define __LC_SELECT_WORLD_ERROR			__ON	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__ON	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__ON	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ������ �ִ� �༮���� ����
#	define __REPAIRSYSTEM_RENEWAL			__ON	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__ON	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__ON	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__OFF	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__ON	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__ON	// ���� ����
#	define __THIRD_ENCHANT_2				__ON	// ������þƮ 2
#	define __XTRAP							__ON	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__OFF	// NProtect �ְ� ����
#	define __PREMIUM_CARD_ADAY				__ON	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__ON	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__ON	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__ON	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__ON	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__ON	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__ON   // PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__ON	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__ON	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__OFF	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__ON	// ���Һ��� ������ ������ - 2009.06.29
#	define __AUTO_ATTACT					__OFF	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__OFF	// IMI �������̽�
#	define __DARKEDEN_MARKET				__ON   // �ٵ����� ����
#	define __CREDIT							__ON	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__ON	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__ON	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__ON	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__ON	// ���ø���
#	define __TREASURE_BOX					__ON	// ��������
#	define __PET_CATS						__ON	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__ON	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__ON	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __UPGRADE_MONSTER_PET			__ON	// ���׷��̵� ���� �� - 2009.10.09
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__OFF	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#endif	// __DESIGNED_JAPAN


#ifdef __DESIGNED_ITEMMANIA
#define __DESIGN_NAME "Designed IMI"

#	define __ADVANCEMENT_CHARACTER			__ON
#	define __LANGUAGE_CHANGE				__ON

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__ON	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__ON
#	define __SMS_SERVICES					__OFF
#	define __RARE_SKILL						__ON

#	define __INTERNATIONAL_PREMIUM_SYSTEM	__OFF
#	define __NEW_SYSTEM_AVAILABILITIES		__OFF
#	define __ENCHANT_REQUIRE_LEVE			__OFF
#	define __ID_PASSWORD					__OFF

#	define __CHAR_DELETE					__ON
#	define __KOREAN_UI						__ON
#	define __INTERNATIONAL_UI				__OFF
#	define __ENGLISH_STRFILTER				__OFF
#	define __CRYPT							__OFF
#	define __CONECT_LIMITER					__OFF
#	define __PERSNALSHOP_NAMING				__ON
#	define __HERO_SYSTEM					__ON
#	define __CONTRIBUTE_SYSTEM				__ON
#	define __LEVEL_WAR_RENEWAL				__ON
#	define __SERVER_SELECT_REVEWAL			__ON
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__ON
#	define __2008_NEW_YEAR_EVENT			__ON
#	define __2008_FIRST_CHARGE_ITEM			__ON	// 2008 1�� ���� ������
#	define __DSG_EFFECT						__ON
#	define __GEAR_SWAP_CHANGE				__ON	//								����,	�׼�,	���߼�
#	define __2008_WHITEDAY_LOVECANDY		__ON	// 2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__ON	// 2008 ��ް����� �𷡽ð�				�׼�,	���߼�
#	define __PAYZONE_PASS_TICKET			__ON	// ������ �����
#	define __QUEST_RENEWAL					__ON	//										�׼�,	���߼�
#	define __EFFECT_RENEWAL					__ON	//								����,	�׼�,	���߼�
#	define __SECOND_RARE_SKILL				__ON	//										�׼�,	���߼�
#	define __080405_FIREST_UI_UPDATE		__ON	//										�׼�,	���߼�
#	define __LIMITED_ITEM_UNISEX			__ON	
#	define __FAST_TRANSFORTER				__ON	
#	define __CLOVER_EVENT					__ON
#	define __QUEST_RENEWAL2					__ON	// __QUEST_RENEWAL�� �̸� ��ġ �Ǿ��� __QUEST_RENEWAL2�� ���� �߿� �ִ� �����̴�.
#	define __GORE_BLOOD_BIBLE				__ON	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__ON	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����

#	define __TIPOJYU_CASTLE					__ON
#	define __2008_JUNE_EVENT_EX_STONE		__ON	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __NEW_ADVANCEMENT_ITEM			__ON	// ���ο� ����������
#	define __TUNING_ITEM					__ON	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__OFF	// �Ϻ� ������ ������
#	define __CHINESE_UI						__OFF	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__OFF	// �Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__ON	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__ON	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__ON	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)
#	define __AUTO_ITEM_ROOTING				__OFF	// ������ �ڵ� ���� �ڵ�(�׽�Ʈ �ڵ��� �����)
#	define __LOCALIZING_LONGNAME			__OFF	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__ON	// OX�̺�Ʈ
#	define __ITEM_SHOW						__ON	// ������ ����

#	define __BLITZ_COUPON_EVENT				__ON	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__ON	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__ON	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF	// 
#	define __PREMIUM_GIVE_ITEM_UI			__ON	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ			2008.10.1 ��ġ
#	define __2008_OCTOBER_MAKETITEM			__ON	// 10�� ���� ������
#	define __PREMIUM_CARD					__ON	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__ON	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__ON	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__ON	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__ON	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__ON	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__ON	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__ON	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__ON	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__ON	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__ON	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__ON	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__ON	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__ON	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__ON	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__ON	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__ON	
#	define __CONTRIBUTE_SYSTEM_ITEM			__ON	
#	define __LEVEL_WAR_RENEWAL_ITEM			__ON	
#	define __MENEGROTH_ITEM					__ON
#	define __LC_SELECT_WORLD_ERROR			__ON	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__ON	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__ON	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ����� �ִ� �༮���� ����

#	define __REPAIRSYSTEM_RENEWAL			__ON	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__ON	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__ON	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__ON	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__ON	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__ON	// ���� ����
#	define __THIRD_ENCHANT_2				__ON	// ������þƮ 2
#	define __XTRAP							__OFF	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__ON	// NProtect �ְ� ����
#	define __PREMIUM_CARD_ADAY				__ON	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__ON	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__ON	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__ON	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__ON	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__ON	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__ON	// PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__ON	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__ON	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__ON	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__ON	// ���Һ��� ������ ������ - 2009.06.29
#	define __AUTO_ATTACT					__ON	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__ON	// IMI �������̽�
#	define __DARKEDEN_MARKET				__OFF   // �ٵ����� ����
#	define __CREDIT							__OFF	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__ON	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__ON	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__ON	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__ON	// ���ø���
#	define __TREASURE_BOX					__ON	// ��������
#	define __PET_CATS						__ON	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__ON	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__ON	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __UPGRADE_MONSTER_PET			__ON	// ���׷��̵� ���� �� - 2009.10.09
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__OFF	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#endif	// __DESIGNED_ITEMMANIA



//////////////////////////////////////////////////////////////////////////
// Taiwan

#ifdef __DESIGNED_TAIWAN
#define __DESIGN_NAME "Designed Taiwan"

#	define __ADVANCEMENT_CHARACTER			__ON
#	define __LANGUAGE_CHANGE				__ON

//#	define __POWER_JJANG_ID					__OFF
#	define __RACE_OUSTERS					__OFF	// �븸 1������. 2009.10.12
#	define __USER_GRADE						__OFF
#	define __SMS_SERVICES					__OFF
#	define __RARE_SKILL						__ON

#	define __INTERNATIONAL_PREMIUM_SYSTEM	__OFF
#	define __NEW_SYSTEM_AVAILABILITIES		__OFF
#	define __ENCHANT_REQUIRE_LEVE			__OFF
#	define __ID_PASSWORD					__OFF

#	define __CHAR_DELETE					__ON
#	define __KOREAN_UI						__OFF
#	define __INTERNATIONAL_UI				__OFF
#	define __ENGLISH_STRFILTER				__OFF
#	define __CRYPT							__OFF
#	define __CONECT_LIMITER					__OFF
#	define __PERSNALSHOP_NAMING				__ON
#	define __HERO_SYSTEM					__ON
#	define __CONTRIBUTE_SYSTEM				__ON
#	define __LEVEL_WAR_RENEWAL				__ON
#	define __SERVER_SELECT_REVEWAL			__ON
#	define __MENEGROTH						__ON
#	define __GPS_ADD						__ON
#	define __2008_NEW_YEAR_EVENT			__ON
#	define __2008_FIRST_CHARGE_ITEM			__ON	// 2008 1�� ���� ������
#	define __DSG_EFFECT						__ON
#	define __GEAR_SWAP_CHANGE				__ON	//								����,	�׼�,	���߼�
#	define __2008_WHITEDAY_LOVECANDY		__ON	// 2008 ȭ��Ʈ���̾�����
#	define __080327_ORDINIS_VAPOR			__ON	// 2008 ��ް����� �𷡽ð�				�׼�,	���߼�
#	define __PAYZONE_PASS_TICKET			__ON	// ������ �����
#	define __QUEST_RENEWAL					__ON	//										�׼�,	���߼�
#	define __EFFECT_RENEWAL					__ON	//								����,	�׼�,	���߼�
#	define __SECOND_RARE_SKILL				__ON	//										�׼�,	���߼�
#	define __080405_FIREST_UI_UPDATE		__ON	//										�׼�,	���߼�
#	define __LIMITED_ITEM_UNISEX			__ON	
#	define __FAST_TRANSFORTER				__ON	
#	define __CLOVER_EVENT					__ON
#	define __QUEST_RENEWAL2					__ON	// __QUEST_RENEWAL�� �̸� ��ġ �Ǿ��� __QUEST_RENEWAL2�� ���� �߿� �ִ� �����̴�.
#	define __GORE_BLOOD_BIBLE				__ON	// ���Ǽ��� ��޿� ���� �������̹���
#	define __AN_ADVANCEMENT_GUN_REFLAME		__ON	// ����������̾� �ѱ�ȭ������Ʈ(�⺻,��������,�����������Ʈ)��ǥ ����

#	define __TIPOJYU_CASTLE					__ON
#	define __2008_JUNE_EVENT_EX_STONE		__ON	// ������ �� �̺�Ʈ(13���� �ݿ���)
#	define __NEW_ADVANCEMENT_ITEM			__ON	// ���ο� ����������
#	define __TUNING_ITEM					__ON	// Ʃ�׾�����
#	define __JAPAN_REVERSE_DEVELOP			__OFF	// �Ϻ� ������ ������
#	define __CHINESE_UI						__ON	// �߱� ��Ʈ Ű���� UI���泻�� ����
#	define __JAPAN_UI						__OFF	// �Ϻ� UI
#	define __NEW_PET_FIRE_ELEMENTAL			__ON	// �űԸ��� ������(���̾� ������Ż)
#	define __SECOND_TRANSFORTER				__ON	// �ű��̵����� 2��
#	define __ADD_MAGICPROTECTION			__ON	// �������� �߰� - �׼������� �����ۿ� �߰� (�ھ������ ���������� ����)
#	define __AUTO_ITEM_ROOTING				__OFF	// ������ �ڵ� ���� �ڵ�(�׽�Ʈ �ڵ��� �����)
#	define __LOCALIZING_LONGNAME			__OFF	// �Ϻ� ���ö���¡�� ���� �̸��� ����ϴµ� �� �̸��� ����ϱ� ���� ���
#	define __OX_EVENT						__ON	// OX�̺�Ʈ
#	define __ITEM_SHOW						__ON	// ������ ����

#	define __BLITZ_COUPON_EVENT				__ON	// ���������� ���� �̺�Ʈ
#	define __TITLE_UI_RENWEAL				__ON	// Ÿ��Ʋ UI ������(2008. 08 ������)
#	define __LOGIN_PACKET					__OFF	// ���ǵ� ���� ���� ���� Ŭ���̾�Ʈ�� �ٿ� ���� �� �ֵ��� ��Ŷ���� ���Ҵ� �κ�(2008.09.08)
#	define __PET_FOOD_ITEM_ADD				__ON	// �ƽ�Ǫ�� �߰�(2008.09.08)
#	define __DYNAMIC_UI						__OFF	// 
#	define __PREMIUM_GIVE_ITEM_UI			__ON	// �����̾� ���� ������ UI
#	define __2008_AUTUMN_LEAVES_EVENT		__ON	// ���� ���� �̺�Ʈ			2008.10.1 ��ġ
#	define __2008_OCTOBER_MAKETITEM			__ON	// 10�� ���� ������
#	define __PREMIUM_CARD					__ON	// �����̾� ī��(__INTERNATIONAL_PREMIUM_SYSTEM���� �и�)
#	define __EXTREME_FORCE_SCROLL			__ON	// �����̾� ���޾����� "�ͽ�Ʈ�� ���� ��ũ��"
#	define __PREMIUM_LOTTER					__ON	// �����̾� ���޾����� "�����̾� ����"
#	define __TIPOJYU_CASTLE_ITEM			__ON	// Ƽ���� �������� ��ä�� ������ �ε����� �߰��ؾ� �� ��찡 ���� ���� ���� ���Ŀ� ������ ���Ͱ� ���� ��������...
#	define __HALLOWEEN						__ON	// �Ϻ� �ҷ��� �̺�Ʈ ������ �ٷ� ������ �־�� ���ٵ�.
#	define __SECOND_TRANSFORTER_ITEM		__ON	// �Ϻ� �ι�°���� �̵����� �����۸� �������� �и�
#	define __GLOBAL_NPC						__ON	// npc��ȯ
#	define __MODIFY_FORCE_SCROLL			__ON	// ���� ������ũ�Ѱ� Ƽ������ ������ũ�� ��ø�����ϰ� ����
#	define __MOVE_ZONE						__ON	// ������ & ����� ���Ǹ� ���� �� �̵��ϴ� ����߰�
#	define __PREMIUM_CARD_D					__ON	// Premium Card D �߰�
#	define __NEW_PET_INCUBUS				__ON	// ��ť���� �� �߰�
#	define __EXPERT_PET_CHANGER				__ON	// �ͽ���Ʈ �� ü���� �߰�
#	define __PET_VISION_AMPLE				__ON	// �� ������ ���� ����
#	define __CHECKTIME_CONTROLL				__ON	// ���� �����Ͽ� �ð�üũ ��Ŷ�� ���� �������� �Ѵ�.
#	define __PREMIUM_CARD_C					__ON	// �����̾� ī�� C������ �����ۺ������ �������� �̸� ��� ���� ���� ������ 
#	define __TIME_STAMP						__ON	// ���� ��¿� �߰��� �ڵ�(�� �ڵ忡 ���� �α��� ������ ���� ������ �ִ�.) ID: shootkj, ��¥: 2008.12.18
#	define __CHRISTMAS_SOCKS_EVENT			__ON	// ũ�������� �縻 ������ ������ �̺�Ʈ
#	define __EVENTTREE_PILE					__ON	// �̺�Ʈ Ʈ���� ��ø �����ϳ� ���ĸ� �¿��� �ϴ� �ڵ� �������̺�Ʈ�� ON�Ǹ� ���� ON �Ǿ� �Ѵ�.

#	define __HERO_SYSTEM_ITEM				__ON	
#	define __CONTRIBUTE_SYSTEM_ITEM			__ON	
#	define __LEVEL_WAR_RENEWAL_ITEM			__ON	
#	define __MENEGROTH_ITEM					__ON
#	define __LC_SELECT_WORLD_ERROR			__ON	// �������ÿ� ������ ����� ���� ��Ŷ �߰� ���� ���� ������ �߰�
#	define __FUNCTION_PETFOOD				__ON	// ��ɼ� ��Ǫ��
#	define __PCITEMINFO						__ON	// PCItemInfo�� ���ؼ� ������ ������ �ְ� �ޱ� ���ؼ� ������ ����� �ִ� �༮���� ����

#	define __REPAIRSYSTEM_RENEWAL			__ON	// ���������� ������ ���������� ���� �Ѵ�.
#	define __DCGLOBAL_NPC					__ON	// ��ī���� NPCȣ�� ������
#	define __GAMEOPTION_ITEMBAY_MESSAGEBOX	__ON	// �������� �ȶ� �������� "�Ȱڳ�?"�� �޼��� �ڽ��� ���� �ɼǿ��� ����
#	define __WORLDCHATING					__ON	// ���尣 ä�� �ý���
#	define __FUNCTION_PETFOOD_SMART			__ON	// ����Ʈ Ǫ��
#	define __VISION_AMPLE					__ON	// ���� ����
#	define __THIRD_ENCHANT_2				__ON	// ������þƮ 2
#	define __XTRAP							__OFF	// XTrap �ְ� ���� ���� lib���� ���� �̵� ���Ѿ� �ϴ°� �翬 ����
#	define __NPROTECT						__ON	// NProtect �ְ� ����
#	define __PREMIUM_CARD_ADAY				__ON	// �����̾� ī�� A Day - ���� �߰��� ��¥�� �����̾� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_A				__ON	// �����̾� ���� A - ���� �߰��� ���� ī�� - 2009.04.28
#	define __PREMIUM_LOTTER_B				__ON	// �����̾� ���� B - ���� �߰��� ���� ī�� - 2009.04.29
#	define __ADVANCEMENT_NEW_UNIQUE_ITEM	__ON	// ��������ũ ������ - 2009.05.14
#	define __HIDDEN_BOSS_SYSTEM				__ON	// ���� ���� ������ �ý���
#	define __CHANGE_PET_INFO_WINDOW_IMAGE	__ON	// �� ����â �̹��� ���� - 2009.05.21
#	define __PET_MIXINGFORGE				__ON	// �� ���ձ�,���� ��ұ�
#	define __PCITEMINFO2					__ON	// PCItemInfo���� 2��° ���� �ع����� 1�� �����ع�����
#	define __ATTACK_SPEED					__ON	// ���� ���ǵ� ������ ����ȭ
#	define __ONIBLA							__ON	// ���Ϻ��� ����
#	define __FRIEND_ADDITION				__ON	// ģ�� �߰� ������ - 2009.06.12
#	define __ONIBLA_ITEM					__ON	// ���Һ��� ������ ������ - 2009.06.29
#	define __AUTO_ATTACT					__OFF	// �ڵ����� ���Ϳ��� ��� �����ϵ��� �Ѵ�.
#	define __IMI_INTERFACE					__OFF	// IMI �������̽�
#	define __DARKEDEN_MARKET				__ON   // �ٵ����� ����
#	define __CREDIT							__ON	// ũ����Ʈ ����
#	define __15_PVP_INHIBITION				__OFF	// ��15������ pvp���� ���� ����(12���̿밡 ���ǿ�)
#	define __SUMMER_VACTATION_COOL_EVENT	__ON	// �������� ��� ����� - �� ��� �̺�Ʈ - 2009.07.27
#	define __IMI_LOW_LEVEL_ITEM				__ON	// IMI�� ���� ������ - 2009.08.03
#	define __IMI_SENDGLASS					__ON	// IMI�� �𷡽ð�
#	define __PET_MASHIMARO					__ON	// ���ø���
#	define __TREASURE_BOX					__ON	// ��������
#	define __PET_CATS						__ON	// �ű� �Ϻ� ���� ������ ������ 3���� - 2009.08.14
#	define __MASTER_EFFECTS					__ON	// ������ ����/����� ����Ʈ ������ - 2009.08.24
#	define __IMI_NEW_ENCHANT_ITEM			__ON	// IMI�� �ű� ��þƮ ������ - 2009.08.25
#	define __MOONLIGHT_FESTIVAL_EVENT		__ON	// �޺� ���� �̺�Ʈ - 2009.09.15
#	define __TREBLE_PET_SANDGLASS			__ON	// 3�� ������ �� ������ �𷡽ð� - 2009.09.21
#	define __IMI_MIXNGFORGE					__ON	// IMI�� �ͽ� ���� - 2009.09.21
#	define __NONE_ADVANCEMENT_SANDGLASS		__ON	// ����� ���� ������ �𷡽ð� - 2009.09.22
#	define __PET_CATS_UPGRADED				__ON	// �Ϻ� ���� ���׷��̵� ������ 12���� - 2009.09.21
#	define __20091028_ADD_ITEM				__ON	// ���ο� ������ �߰� - 2009.10.28	
#	define __TAIWAN_INTERFACE				__ON	// �븸 �������̽�
#	define __CRIMSON_EVENT					__ON	// ũ���� �̺�Ʈ �߰� - 2009.11.09
#	define __20091116_ADD_RARE_SKILL		__ON	// ���ų �߰� - 2009.11.16
#	define __20091119_ADD_ENCHANT_ITEM		__ON	// �ű� ��þƮ ������ - 2009.11.19

#	define __NEW_SKIN_181		__OFF	// �ű� ��Ʈ,���ÿ��� - 2021.08.14
#endif	// __DESIGNED_TAIWAN




//////////////////////////////////////////////////////////////////////////
// Macro

// ��ũ�ΰ� define �ȵǾ� �ִٸ� __ON���� ģ��.
#define __CONTENTS(f)	((f) == __ON)


/*#ifdef __DESIGN_NAME
#	pragma message ("Darkeden project \"" __DESIGN_NAME "\"")
#else
#	pragma message ("Darkeden design macro undefined")
#endif/*/
#undef __DESIGN_NAME
