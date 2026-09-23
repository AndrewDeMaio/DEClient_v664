//----------------------------------------------------------------------
// MTypeDef.h
//----------------------------------------------------------------------

#ifndef	__MTYPEDEF_H__
#define	__MTYPEDEF_H__

#pragma warning(disable:4786)

#include "ContentsFilter.h"

//------------------------------------------------------------------
// NULL��
//------------------------------------------------------------------
#define	ZONEID_NULL						0xFFFF
#define	OBJECTID_NULL					0xFFFFFFFF		// �ƹ��͵� ���ٴ� �ǹ�..
#define	INTERACTIONOBJECTTYPE_NULL		0xFFFF
#define	SECTORPOSITION_NULL				0xFFFF

#define	ITEMTYPE_NULL					0xFFFF
#define	ITEM_OPTION_NULL				0xFFFF
#define	ITEM_DURATION_NULL				0xFFFFFFFF
#define	ITEM_PRICE_NULL					0xFFFFFFFF
#define	ITEM_NUMBER_NULL				0xFFFFFFFF
#define	ITEM_WEIGHT_NULL				0xFFFF


//------------------------------------------------------------------
// sizeof( TYPE_... )
//------------------------------------------------------------------
#define	SIZE_OBJECTID					4
#define	SIZE_ZONEID						2
//#define	SIZE_ITEMCLASS					2
#define	SIZE_INTERACTIONOBJECTTYPE		2
#define	SIZE_SECTORPOSITION				2

#define	SIZE_ITEMTYPE					2
#define	SIZE_ITEM_OPTION				2
#define	SIZE_ITEM_DURATION				4
#define	SIZE_ITEM_PRICE					4
#define	SIZE_ITEM_NUMBER				4
#define	SIZE_ITEM_WEIGHT				2


//------------------------------------------------------------------
// typedef
//------------------------------------------------------------------
typedef	unsigned short	TYPE_ZONEID;
typedef	unsigned int	TYPE_OBJECTID;
//typedef	unsigned short	TYPE_ITEMCLASS;
typedef	unsigned short	TYPE_INTERACTIONOBJECTTYPE;
typedef	unsigned short	TYPE_SECTORPOSITION;

typedef	unsigned short	TYPE_ITEMTYPE;
typedef	unsigned char	TYPE_ITEM_OPTION;
typedef	unsigned int	TYPE_ITEM_DURATION;
//typedef	unsigned short	TYPE_ITEM_DURATION;
typedef	unsigned int	TYPE_ITEM_PRICE;
typedef	unsigned int	TYPE_ITEM_NUMBER;
typedef	unsigned short	TYPE_ITEM_WEIGHT;


//----------------------------------------------------------------------
//
//                 Creature ����
//
//----------------------------------------------------------------------

#define	CREATURETYPE_NULL				0xFFFF

#define	SIZE_CREATURETYPE				2

typedef	unsigned short	TYPE_CREATURETYPE;

//----------------------------------------------------------------------
// ���⿡ ���� ��
//----------------------------------------------------------------------
enum DIRECTIONS
{			
	DIRECTION_LEFT = 0,
	DIRECTION_LEFTDOWN,
	DIRECTION_DOWN,
	DIRECTION_RIGHTDOWN,
	DIRECTION_RIGHT,
	DIRECTION_RIGHTUP,
	DIRECTION_UP,
	DIRECTION_LEFTUP,
	DIRECTION_MAX,	
	DIRECTION_NULL
};

#define	MAX_DIRECTION	DIRECTION_MAX

//----------------------------------------------------------------------
// �ൿ�� ���� ��
//----------------------------------------------------------------------
// VAMPIRE�� SLAYER�� ���� ���� ������ ������
// FramePack������ Action��ȣ �����̴�..
//

//////////////////////////////////////////////////////////////////////////
// Common Action
enum {
	ACTION_STAND,								// 0
	ACTION_MOVE,								// 1
	ACTION_ATTACK,								// 2
	ACTION_MAGIC,								// 3
	ACTION_DAMAGED,								// 4
	ACTION_DRAINED,								// 5	//���ÿ°� �𸣰����� ������ ���Ѵ�. �ٸ� ���� ��ų�� ����Ѵ�.
	ACTION_DIE,									// 6

	ACTION_MAX_COMMON,
};

//////////////////////////////////////////////////////////////////////////
// Slayer Action

// 2007.09.06 - Slayer Renewal
enum {
	ACTION_SLAYER_GUN_SR = ACTION_MAX_COMMON,	// 7			// ���ݿ�(TR)
	ACTION_SLAYER_GUN_AR,						// 8			// ����(AG)
	ACTION_SLAYER_GUN_SG,						// 9			// ����(SG)
	ACTION_SLAYER_GUN_SMG,						// 10			// �ڵ�����(SMG)

	ACTION_SLAYER_SWORD,						// 11			// Į
	ACTION_SLAYER_BLADE,						// 12			// ��
	ACTION_SLAYER_SWORD_2,						// 13			// Į Ư������
	ACTION_SLAYER_BLADE_2,						// 14			// �� Ư������

	ACTION_SLAYER_MOTOR_MOVE,					// 15
	ACTION_SLAYER_MOTOR_STAND,					// 16

	ACTION_SLAYER_GUN_SR_SLOW,					// 17			// ���ݿ�(TR)
	ACTION_SLAYER_GUN_SR_FAST,					// 18			// ���ݿ�(TR)
	ACTION_SLAYER_GUN_AR_SLOW,					// 19			// ����(AG)
	ACTION_SLAYER_GUN_AR_FAST,					// 20	 		// ����(AG)
	ACTION_SLAYER_GUN_SG_SLOW,					// 21			// ����(SG)
	ACTION_SLAYER_GUN_SG_FAST,					// 22			// ����(SG)
	ACTION_SLAYER_GUN_SMG_SLOW,					// 23			// �ڵ�����(SMG)
	ACTION_SLAYER_GUN_SMG_FAST,					// 24			// �ڵ�����(SMG)

	ACTION_SLAYER_SWORD_SLOW,					// 25			// Į
	ACTION_SLAYER_SWORD_FAST,					// 26			// Į
	ACTION_SLAYER_BLADE_SLOW,					// 27			// ��
	ACTION_SLAYER_BLADE_FAST,					// 28			// ��

	ACTION_SLAYER_SWORD_2_SLOW,					// 29			// Į Ư������
	ACTION_SLAYER_SWORD_2_FAST,					// 30			// Į Ư������
	ACTION_SLAYER_BLADE_2_SLOW,					// 31			// �� Ư������
	ACTION_SLAYER_BLADE_2_FAST,					// 32			// �� Ư������

	ACTION_SLAYER_BATTLE_STAND_GUN,				// 33
	ACTION_SLAYER_BATTLE_STAND_SWORD,			// 34
	ACTION_SLAYER_BATTLE_STAND_BLADE,			// 35

	ACTION_SLAYER_MOVE_GUN,						// 36

	ACTION_SLAYER_MAGIC_CASTING,				// 37
	
	ACTION_SLAYER_SWORD_2_REPEAT,				// 38
	ACTION_SLAYER_BLADE_2_REPEAT,				// 39

	ACTION_MAX_SLAYER,
};

//////////////////////////////////////////////////////////////////////////
// Vampire Action
enum {
	// 2001.6.5 �߰��Ȱ�
	ACTION_VAMPIRE_DRAIN = ACTION_MAX_COMMON,	// 7
	ACTION_VAMPIRE_ATTACK_SLOW,					// 8			// vampire����
	ACTION_VAMPIRE_ATTACK_FAST,					// 9			// vampire����

	// chyaya 2007.05.06 �����̾� ���� ���x2, ������ ���� ��� �߰�
	ACTION_VAMPIRE_ATTACK_2,					// 10
	ACTION_VAMPIRE_ATTACK_2_SLOW,				// 11
	ACTION_VAMPIRE_ATTACK_2_FAST,				// 12
	ACTION_VAMPIRE_ATTACK_3,					// 13
	ACTION_VAMPIRE_ATTACK_3_SLOW,				// 14
	ACTION_VAMPIRE_ATTACK_3_FAST,				// 15
	ACTION_VAMPIRE_MAGIC_CASTING,				// 16

	ACTION_MAX_VAMPIRE,
};

/*
// 2005.6.20 �߰��Ȱ�
#define	ACTION_VAMPIRE_SKILL_ATTACK				10			// vampire����
#define	ACTION_VAMPIRE_SKILL_ATTACK_SLOW		11			// vampire����
#define	ACTION_VAMPIRE_SKILL_ATTACK_FAST		12			// vampire����
*/

// 2001.7.6
#define	ACTION_MONSTER_DIE_BODY		10			// Vampire Monster���� - �Ӹ����� �� �ִ� ��


//////////////////////////////////////////////////////////////////////////
// Ousters Action
enum {
	ACTION_OUSTERS_STAND = ACTION_MAX_COMMON,	// 7			// ���ֱ�
	ACTION_OUSTERS_MOVE,						// 8			// �ȱ�
	ACTION_OUSTERS_CHAKRAM,						// 9			// ��ũ�� ����
	ACTION_OUSTERS_MAGIC_ATTACK,				// 10			// ���� ����
	ACTION_OUSTERS_DRAIN,						// 11			// ����
	ACTION_OUSTERS_FAST_MOVE_STAND,				// 12			// ���� ����
	ACTION_OUSTERS_FAST_MOVE_MOVE,				// 13			// ���� ������
	ACTION_OUSTERS_ATTACK_SLOW,					// 14			// �Ϲ� ���� ����
	ACTION_OUSTERS_ATTACK_FAST,					// 15			// �Ϲ� ���� ����
	ACTION_OUSTERS_CHAKRAM_SLOW,				// 16			// ��ũ�� ���� ����
	ACTION_OUSTERS_CHAKRAM_FAST,				// 17			// ��ũ�� ���� ����
//#if __CONTENTS(__FAST_TRANSFORTER)
	ACTION_OUSTERS_WING_STAND,					// 18
	ACTION_OUSTERS_WING_MOVE,					// 19
//#endif //__FAST_TRANSFORTER
//#if __CONTENTS(__SECOND_TRANSFORTER)
	ACTION_OUSTERS_UNICORN_STAND,				// 20
	ACTION_OUSTERS_UNICORN_MOVE,				// 21
//#endif //__SECOND_TRANSFORTER
	ACTION_MAX_OUSTERS,							// 20
};


#define	ACTION_MAX_NPC	2
#define	ACTION_MAX		19



//----------------------------------------------------------------------
// Addon��ġ
// ADDON_NULL�� ������ �� ��� ������ �̿�ȴ� ���������� ADDON_MOTOR���� enum������ ������ �Ǿ� ������ 
// ����� ���� ��ȭ ���� ������ ����ȴ�. ���������� �߰��Ͽ� ADDON_MAX���� ���� ������ ����� �߰��ϸ� ������ 
// ���������� ���� ������ ���⵵ �ϰŴϿ� ���ҽ� �����͸� �ǵ���� �� �κ��� ���� ������ �Ǵ� �ȴ�. 
// ���Ŀ� �����̾� �������� �ְų� addon������ ���̰ų� ���϶� �� ū �۾��� ������ ������ ����ȭ�� ���ߴ� ���� ���������� �Ǵܵȴ�.
//----------------------------------------------------------------------
enum ADDON
{
	ADDON_HAIR,			// �Ӹ�
	ADDON_HELM,			// ����
	ADDON_COAT,			// ����
	ADDON_TROUSER,		// ����
	//ADDON_SHOES,		// �Ź�
	//ADDON_LEFTGLOVE,		// �޼� �尩
	//ADDON_RIGHTGLOVE,		// ������ �尩
	ADDON_LEFTHAND,		// �޼�			
	ADDON_RIGHTHAND,	// ������
	//ADDON_CLOAK,		// ����
	ADDON_MOTOR,		// �������
	ADDON_MAX,
	ADDON_NULL	= 0xFFFF,
};



//----------------------------------------------------------------------
//
//                          Effect ����
//
//----------------------------------------------------------------------
#define	ACTIONINFO_NULL					0xFFFF
#define	SIZE_ACTIONINFO					2
typedef	unsigned short	TYPE_ACTIONINFO;


//----------------------------------------------------------------------
//
//                       EffectGenerator ����
//
//----------------------------------------------------------------------
typedef	unsigned short TYPE_EFFECTGENERATORID;
#define	SIZE_EFFECTGENERATORID			2
#define	EFFECTGENERATORID_NULL			0xFFFF



//----------------------------------------------------------------------
//
//                       Sound / Music ����
//
//----------------------------------------------------------------------

typedef unsigned short TYPE_SOUNDID;
#define	SIZE_SOUNDID	2
#define	SOUNDID_NULL	0xFFFF

typedef unsigned short TYPE_MUSICID;
#define	SIZE_MUSICID	2
#define	MUSICID_NULL	0xFFFF


//----------------------------------------------------------------------
// EffectSpriteType ����
//----------------------------------------------------------------------
typedef	unsigned short				TYPE_EFFECTSPRITETYPE;
#define	SIZE_EFFECTSPRITETYPE		2
#define	EFFECTSPRITETYPE_NULL		0xFFFF


//----------------------------------------------------------------------
// link Count
//----------------------------------------------------------------------
#define	MAX_LINKCOUNT				0xFFFF

enum {
	ACTION_ADVANCEMENT_SLAYER_STOP_SWORD = 100,
	ACTION_ADVANCEMENT_SLAYER_STOP_BLADE,
	ACTION_ADVANCEMENT_SLAYER_STOP_GUN,
	ACTION_ADVANCEMENT_SLAYER_STOP_MACE_AND_CROSS,
	
	ACTION_ADVANCEMENT_SLAYER_MOVE_SWORD,
	ACTION_ADVANCEMENT_SLAYER_MOVE_BLADE,
	ACTION_ADVANCEMENT_SLAYER_MOVE_GUN,
	ACTION_ADVANCEMENT_SLAYER_MOVE_MACE_AND_CROSS,

	ACTION_ADVANCEMENT_SLAYER_ATTACK_SWORD_SLOW,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_SWORD_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_SWORD_FAST,
	
	ACTION_ADVANCEMENT_SLAYER_ATTACK_BLADE_SLOW,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_BLADE_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_BLADE_FAST,
	
	ACTION_ADVANCEMENT_SLAYER_ATTACK_AR_GUN_SLOW,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_AR_GUN_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_AR_GUN_FAST,
	
	ACTION_ADVANCEMENT_SLAYER_ATTACK_SR_GUN_SLOW,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_SR_GUN_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_ATTACK_SR_GUN_FAST,

	ACTION_ADVANCEMENT_SLAYER_SKILL_SWORD_SLOW,
	ACTION_ADVANCEMENT_SLAYER_SKILL_SWORD_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_SKILL_SWORD_FAST,

	ACTION_ADVANCEMENT_SLAYER_SKILL_BLADE_SLOW,
	ACTION_ADVANCEMENT_SLAYER_SKILL_BLADE_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_SKILL_BLADE_FAST,

	ACTION_ADVANCEMENT_SLAYER_SKILL_GUN_SLOW,
	ACTION_ADVANCEMENT_SLAYER_SKILL_GUN_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_SKILL_GUN_FAST,
	
	ACTION_ADVANCEMENT_SLAYER_MAGIC,
	ACTION_ADVANCEMENT_SLAYER_MAGIC_ATTACK,

	ACTION_ADVANCEMENT_SLAYER_DRAINED,
	ACTION_ADVANCEMENT_SLAYER_DAMAGED_SWORD,
	ACTION_ADVANCEMENT_SLAYER_DAMAGED_BLADE,
	ACTION_ADVANCEMENT_SLAYER_DAMAGED_GUN,
	ACTION_ADVANCEMENT_SLAYER_DAMAGED_CROSS_MACE,
	ACTION_ADVANCEMENT_SLAYER_DIE,

	ACTION_ADVANCEMENT_SLAYER_BIKE_MOVE,
	ACTION_ADVANCEMENT_SLAYER_BIKE_STOP,

	ACTION_ADVANCEMENT_SLAYER_SPECIAL,
	ACTION_ADVANCEMENT_SLAYER_SPECIAL_2,
	
	ACTION_ADVANCEMENT_SLAYER_SLIDING,
	ACTION_ADVANCEMENT_SLAYER_SLIDING_END,

	/*ACTION_ADVANCEMENT_SLAYER_SWORD_SLIDING,
	ACTION_ADVANCEMENT_SLAYER_SWORD_SLIDING_END,

	ACTION_ADVANCEMENT_SLAYER_BLADE_SLIDING,
	ACTION_ADVANCEMENT_SLAYER_BLADE_SLIDING_END,

	// 2005.06.09 sjheon  Combo Action Add

	ACTION_ADVANCEMENT_SLAYER_COMBO_SWARD_SLOW ,
	ACTION_ADVANCEMENT_SLAYER_COMBO_SWARD_NORMAL ,
	ACTION_ADVANCEMENT_SLAYER_COMBO_SWARD_FAST ,
	
	ACTION_ADVANCEMENT_SLAYER_COMBO_BLADE_SLOW ,
	ACTION_ADVANCEMENT_SLAYER_COMBO_BLADE_NORMAL ,
	ACTION_ADVANCEMENT_SLAYER_COMBO_BLADE_FAST ,

	ACTION_ADVANCEMENT_SLAYER_COMBO_CANCEL_SWARD_SLOW,
	ACTION_ADVANCEMENT_SLAYER_COMBO_CANCEL_SWARD_NORMAL,
	ACTION_ADVANCEMENT_SLAYERN_COMBO_CANCEL_SWARD_FAST,

	ACTION_ADVANCEMENT_SLAYER_COMBO_CANCEL_BLADE_SLOW,
	ACTION_ADVANCEMENT_SLAYER_COMBO_CANCEL_BLADE_NORMAL,
	ACTION_ADVANCEMENT_SLAYER_COMBO_CANCEL_BLADE_FAST,*/

	// 2005.06.09 sjheon  Combo Action End
	ACTION_ADVANCEMENT_SLAYER_MAX,
};

enum
{
	ACTION_ADVANCEMENT_OUSTERS_CHAKRAM_STOP = 100,	//0
	ACTION_ADVANCEMENT_OUSTERS_CHAKRAM_MOVE,		//1
	ACTION_ADVANCEMENT_OUSTERS_WRISTLET_STOP,		//2
	ACTION_ADVANCEMENT_OUSTERS_WRISTLET_MOVE,		//3

	ACTION_ADVANCEMENT_OUSTERS_ATTACK_SLOW,			//4
	ACTION_ADVANCEMENT_OUSTERS_ATTACK_NORMAL,		//5
	ACTION_ADVANCEMENT_OUSTERS_ATTACK_FAST,			//6
	ACTION_ADVANCEMENT_OUSTERS_SKILL_SLOW,			//7
	ACTION_ADVANCEMENT_OUSTERS_SKILL_NORMAL,		//8
	ACTION_ADVANCEMENT_OUSTERS_SKILL_FAST,			//9

	ACTION_ADVANCEMENT_OUSTERS_MAGIC_ATTACK,		//10

	ACTION_ADVANCEMENT_OUSTERS_MAGIC,				//11
	ACTION_ADVANCEMENT_OUSTERS_ABSORB_SOUL,			//12
	ACTION_ADVANCEMENT_OUSTERS_DRAINED,				//13
	ACTION_ADVANCEMENT_OUSTERS_DIE,					//14
	ACTION_ADVANCEMENT_OUSTERS_DAMAGED,				//15
	ACTION_ADVANCEMENT_OUSTERS_SPECIAL,				//16

	ACTION_ADVANCEMENT_OUSTERS_FAST_MOVE_STOP,		//17
	ACTION_ADVANCEMENT_OUSTERS_FAST_MOVE,			//18

#if __CONTENTS(__FAST_TRANSFORTER)
	ACTION_ADVANCEMENT_OUSTERS_WING_MOVE,			//19
	ACTION_ADVANCEMENT_OUSTERS_WING_STOP,			//20
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	ACTION_ADVANCEMENT_OUSTERS_UNICORN_MOVE,		//21
	ACTION_ADVANCEMENT_OUSTERS_UNICORN_STOP,		//22
#endif //__SECOND_TRANSFORTER

	// 2005.06.09 sjheon  Combo Action Add
	/*ACTION_ADVANCEMENT_OUSTERS_SLIDING,
	ACTION_ADVANCEMENT_OUSTERS_SLIDING_END,
	
	ACTION_ADVANCEMENT_OUSTERS_COMBO_SLOW,
	ACTION_ADVANCEMENT_OUSTERS_COMBO_NORMAL,
	ACTION_ADVANCEMENT_OUSTERS_COMBO_FAST,
		
	ACTION_ADVANCEMENT_OUSTERS_COMBO_CANCEL_SLOW,
	ACTION_ADVANCEMENT_OUSTERS_COMBO_CANCEL_NORMAL,
	ACTION_ADVANCEMENT_OUSTERS_COMBO_CANCEL_FAST,*/
	// 2005.06.09 sjheon  Combo Action End

	ACTION_ADVANCEMENT_OUSTERS_MAX
};

enum {
	ACTION_ADVANCEMENT_STOP = 100,
	ACTION_ADVANCEMENT_MOVE,
	ACTION_ADVANCEMENT_DAMAGED,
	ACTION_ADVANCEMENT_DIE,
	ACTION_ADVANCEMENT_DRAIN,
	ACTION_ADVANCEMENT_DRAINED,

	ACTION_ADVANCEMENT_ATTACK_SLOW,
	ACTION_ADVANCEMENT_ATTACK_NORMAL,
	ACTION_ADVANCEMENT_ATTACK_FAST,

	ACTION_ADVANCEMENT_SKILL_SLOW,
	ACTION_ADVANCEMENT_SKILL_NORMAL,
	ACTION_ADVANCEMENT_SKILL_FAST,

	ACTION_ADVANCEMENT_MAGIC,
	ACTION_ADVANCEMENT_MAGIC_ATTACK,
	ACTION_ADVANCEMENT_SPECIAL,
	ACTION_ADVANCEMENT_CREATE_WEAPON,
	ACTION_ADVANCEMENT_DESTROY_WEAPON,

	// 2005.06.09 sjheon  Combo Action Add
	/*ACTION_ADVANCEMENT_SLIDING,
	ACTION_ADVANCEMENT_SLIDING_END,
	
	ACTION_ADVANCEMENT_COMBO_SLOW,
	ACTION_ADVANCEMENT_COMBO_NORMAL,
	ACTION_ADVANCEMENT_COMBO_FAST,

	ACTION_ADVANCEMENT_COMBO_CANCEL_SLOW,
	ACTION_ADVANCEMENT_COMBO_CANCEL_NORMAL,
	ACTION_ADVANCEMENT_COMBO_CANCEL_FAST,*/
	// 2005.06.09 sjheon  Combo Action End
	
	ACTION_ADVANCEMENT_MAX,
};

enum AC_SLAYER_PART
{
	AC_BODY = 0,
	AC_HELMET,
	AC_SWORD,
	AC_BLADE,
	AC_CROSS,
	AC_MACE,
	AC_GUN_AR,
	AC_GUN_SR,
	AC_SHIELD,
	AC_BIKE_1,
	AC_BIKE_2,
	AC_SHOULDER,
	AC_BIKE_2_COLOR,
#if __CONTENTS(__FAST_TRANSFORTER)
	AC_WING_BIKE,
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	AC_HOVER_VEHICLE,
#endif //__SECOND_TRANSFORTER
	AC_PART_MAX,
};

enum AC_ADDON
{
	AC_ADDON_BODY,		// ����
	AC_ADDON_HELM,		// ���
	AC_ADDON_LEFTHAND,	// �޼�
	AC_ADDON_RIGHTHAND,	// ������
	AC_ADDON_MOTOR,		// �������
	AC_ADDON_SHOULDER,	// ����
	AC_ADDON_MAX,
	AC_ADDON_NULL	= 0xFFFF,
};

// advancedslayer* layers; a layer's Osiris version is the one after it.
enum OSIRIS_SLAYER_LAYER
{
	OSIRIS_SLAYER_SWORD			= 0,
	OSIRIS_SLAYER_BLADE			= 2,
	OSIRIS_SLAYER_GUN_SR		= 4,
	OSIRIS_SLAYER_GUN_AR		= 6,
	OSIRIS_SLAYER_CROSS			= 8,
	OSIRIS_SLAYER_MACE			= 10,
	OSIRIS_SLAYER_SHIELD		= 12,
	OSIRIS_SLAYER_HAIR			= 14,
	OSIRIS_SLAYER_BIKE_1		= 15,
	OSIRIS_SLAYER_BIKE_2		= 16,
	OSIRIS_SLAYER_HELMET		= 17,
	OSIRIS_SLAYER_JACKET		= 19,
	OSIRIS_SLAYER_PANTS			= 21,
	OSIRIS_SLAYER_WING_BIKE		= 23,
	OSIRIS_SLAYER_HOVER_VEHICLE	= 24,
	OSIRIS_SLAYER_LAYER_MAX		= 27,
};

#define ADVANCEMENT_ACTION_START	100

#endif
