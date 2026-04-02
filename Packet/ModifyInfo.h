//////////////////////////////////////////////////////////////////////////////
// Filename    : ModifyInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// �÷��̾��� ���°� ���� ��, Ŭ���̾�Ʈ���� ���ư��� ��Ŷ�̴�.
// �ַ� �÷��̾ ���� ����� ���� ��� ��Ŷ�� �� ��Ŷ�� ��ӹ޾Ƽ�
// ���� ��찡 ����.
//////////////////////////////////////////////////////////////////////////////

#ifndef __MODIFY_INFO_H__
#define __MODIFY_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "Types/ModifyDef.h"
#include <list>


const std::string ModifyType2String[] = 
{
	"BASIC_STR",					// �⺻ STR�� ����
	"CURRENT_STR",					// ���� STR�� ����
	"MAX_STR",						// �ƽ� STR�� ����
	"STR_EXP_REMAIN",				// STR ����ġ�� ����

	"BASIC_DEX",					// �⺻ DEX�� ����
	"CURRENT_DEX",					// ���� DEX�� ����
	"MAX_DEX",						// �ƽ� DEX�� ����
	"DEX_EXP_REMAIN",				// DEX ����ġ�� ����

	"BASIC_INT",					// �⺻ INT�� ����
	"CURRENT_INT",					// ���� INT�� ����
	"MAX_INT",						// �ƽ� INT�� ����
	"INT_EXP_REMAIN",				// INT ����ġ�� ����

	"CURRENT_HP",					// ���� HP�� ����
	"MAX_HP",						// �ƽ� HP�� ����

	"CURRENT_MP",					// ���� MP�� ����
	"MAX_MP",						// �ƽ� MP�� ����

	"MIN_DAMAGE",					// �ּ� �������� ����
	"MAX_DAMAGE",					// �ƽ� �������� ����

	"DEFENSE",						// ���潺�� ����
	"PROTECTION",					// �����ؼ��� ����
	"TOHIT",						// ���߷��� ����

	"VISION",						// �þ߸� ����
	"FAME",							// ������ ����
	"GOLD",							// �������� ����

	"SWORD_DOMAIN_LEVEL",			// �� �迭 ������ ����
	"SWORD_DOMAIN_EXP_REMAIN",		// �� �迭 ������ ����
	"SWORD_DOMAIN_GOAL_EXP",		// �� �迭 ������ ����
	"BLADE_DOMAIN_LEVEL",			// �� �迭 ������ ����
	"BLADE_DOMAIN_EXP_REMAIN",		// �� �迭 ������ ����
	"BLADE_DOMAIN_GOAL_EXP",		// �� �迭 ������ ����
	"HEAL_DOMAIN_LEVEL",			// �� �迭 ������ ����
	"HEAL_DOMAIN_EXP_REMAIN",		// �� �迭 ������ ����
	"HEAL_DOMAIN_GOAL_EXP",			// �� �迭 ������ ����
	"ENCHANT_DOMAIN_LEVEL",			// ��æƮ �迭 ������ ����
	"ENCHANT_DOMAIN_EXP_REMAIN",	// ��æƮ �迭 ������ ����
	"ENCHANT_DOMAIN_GOAL_EXP",		// ��æƮ �迭 ������ ����
	"GUN_DOMAIN_LEVEL",				// �� �迭 ������ ����
	"GUN_DOMAIN_EXP_REMAIN",		// �� �迭 ������ ����
	"GUN_DOMAIN_GOAL_EXP",			// �� �迭 ������ ����
	"ETC_DOMAIN_LEVEL",				// ��Ÿ �迭 ������ ����
	"ETC_DOMAIN_EXP_REMAIN",		// ��Ÿ �迭 ������ ����
	"ETC_DOMAIN_GOAL_EXP",			// ��Ÿ �迭 ������ ����

	"SKILL_LEVEL",					// Ư�� ��ų ������ ����
	"LEVEL",						// �����̾� ������ ����
	"EFFECT_STAT",					// ����Ʈ ���¸� ����
	"DURATION",						// ����Ʈ ���� �ð��� ����
	"BULLET",						// ��� �ִ� �Ѿ��� �Ѿ� ���� ����
	"BONUS_POINT",					// �����̾��� ���ʽ� ����Ʈ�� ����
	"DURABILITY",					// ��� �ִ� ������ �� �ϳ��� �������� ����
	"NOTORIETY",					// �Ǹ�ġ�� ����
	"VAMP_EXP_REMAIN",				// �����̾��� ����ġ�� ����

	"SILVER_DAMAGE",				// �� �������� ����
	"ATTACK_SPEED",					// ���� �ӵ��� ����
	"ALIGNMENT",					// ����

	"SILVER_DURABILITY",			// ������ ������..

	"REGEN_RATE",					// ���� �ð��� �������� ���� �ϴܽ�-_-
	"GUILDID",						// ��� ���̵� �ٲ�����

	"RANK",							// ��� �ܰ�
	"RANK_EXP_REMAIN",				// ��� ����ġ

	"OUSTERS_EXP_REMAIN",			// �ƿ콺�ͽ��� ����ġ�� ����
	"SKILL_BONUS_POINT",			// �ƿ콺�ͽ��� ��ų ���ʽ� ����Ʈ�� ����
	
	"ELEMENTAL_FIRE",
	"ELEMENTAL_WATER",
	"ELEMENTAL_EARTH",
	"ELEMENTAL_WIND",
	
	"SKILL_EXP",					// ��ų ����ġ ����
	
    "PET_HP",
    "PET_EXP_REMAIN",               // �� ����
	
	"LAST_TARGET",

	"UNIONID",
	"UNIONGRADE",
	
    "ADVANCEMENT_CLASS_LEVEL",		// ���� ����
    "ADVANCEMENT_CLASS_GOAL_EXP",	// ���� ����ġ

	"ATTACK_BLOOD_BURST_POINT",		// ���� ���� ����Ʈ
	"DEFENSE_BLOOD_BURST_POINT",	// ���� ���� ����Ʈ
	"PARTY_BLOOD_BURST_POINT",		// ��Ƽ ���� ����Ʈ
	
	"ADVANCED_SLAYERSTR",
	"ADVANCED_SLAYERDEX",
	"ADVANCED_SLAYERINT",			

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	"CONTRIBUTE_POINT",				// MODIFY_CONTRIBUTE_POINT �⿩�� ����
#endif	
	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// 2����Ʈ�� ����� �������� ���, �� ����ü�� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
typedef struct _SHORTDATA
{
	BYTE   type;
	ushort value;

} SHORTDATA;

//////////////////////////////////////////////////////////////////////////////
// 4����Ʈ�� ����� �������� ���, �� ����ü�� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
typedef struct _LONGDATA
{
	BYTE  type;
	ulong value;

} LONGDATA;


//////////////////////////////////////////////////////////////////////////////
// class ModifyInfo;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// ModifyInformation, SkillToObjectOK � �Ƿ��� ���ư���.
//////////////////////////////////////////////////////////////////////////////

class ModifyInfo : public Packet
{
public:
	ModifyInfo ();
	virtual ~ModifyInfo ();
	
public:
    void read (SocketInputStream & iStream);
    void write (SocketOutputStream & oStream) const;
	size_t getPacketSize() const { return szBYTE * 2 + m_ShortCount * (szBYTE + szshort) + m_LongCount * (szBYTE + szlong); }
	static PacketSize_t getPacketMaxSize() { return szBYTE*2 + 255*(szBYTE+szshort+szBYTE+szlong); }

#ifdef __DEBUG_OUTPUT__
	std::string toString () const;
#endif

public:
	BYTE getShortCount(void) const { return m_ShortCount; }
	BYTE getLongCount(void) const { return m_LongCount; }

	void addShortData(ModifyType type, ushort value);
	void addLongData(ModifyType type, ulong value);

	void popShortData(SHORTDATA& rData);
	void popLongData(LONGDATA& rData);

	void clearList(void) { m_ShortCount = 0; m_LongCount = 0; m_ShortList.clear(); m_LongList.clear(); }

protected:
	BYTE            m_ShortCount;
	std::list<SHORTDATA> m_ShortList;

	BYTE            m_LongCount;
	std::list<LONGDATA>  m_LongList;
};

#endif
