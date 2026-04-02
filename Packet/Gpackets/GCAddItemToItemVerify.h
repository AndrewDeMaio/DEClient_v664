//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_ITEM_VERIFY_H__
#define __GC_ADD_ITEM_TO_ITEM_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	ADD_ITEM_TO_ITEM_VERIFY_ERROR,					// error

	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE,		// enchant ���� �Ұ�
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH,		// enchant ����: ������ �μ���
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE,	// enchant ����: �ɼ� ������
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK,				// enchant ����
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM,	// enchant �Ұ� : �����̾� �ƴ�

	ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK,
	ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE,
	
	ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK,
	ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK,

	ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAILED_SAME_OPTION_GROUP,	// �������� �ɼ� �׷��� ���Ƽ� ���� �� �����ϴ�.
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL,				// enchant ����

	ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK,					// �� ��Ȱ ����

	ADD_ITEM_TO_ITEM_VERIFY_CLEAR_OPTION_OK,			// option ���� ����
	ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK,				// grade�ø��� ����

	ADD_ITEM_TO_ITEM_VERIFY_PET_MAGIC_ENCHANT_OK,		// Pet Magic Enchant ����

	ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_LEVEL_FAIL,		// �� ������ ���� ��æ �Ұ�
	ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_DUPLICATE_FAIL,		// �Ȱ��� ��æ�� �Ϸ��� �õ�

	ADD_ITEM_TO_ITEM_VERIFY_PET_ENCHANT_OK_MESSAGE,				// enchant ���� �޽���

#if __CONTENTS(__ENCHANT_REQUIRE_LEVE)
	ADD_ITEM_TO_ITEM_VERIFY_NEED_LEVEL_FAIL,
#endif

	ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL,
	ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK,
#if __CONTENTS (__2008_FIRST_CHARGE_ITEM)
	ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK,
#endif	//__2008_FIRST_CHARGE_ITEM				
#if __CONTENTS(__TUNING_ITEM)
	ADD_ITEM_TO_ITEM_VERIFY_TUNING_OK = 22,
#endif	//__TUNING_ITEM
	ADD_ITEM_TO_ITEM_VERIFY_PET_EXPERT_ENCHANT_OK = 23,	// Pet Expert --> 1202 wlzzi �� ���� ����
	
	ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_OK = 24,			//20090527 ksym555
	ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_FAIL = 25,		//20090527 ksym555

#if __CONTENTS(__TREASURE_BOX)
	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_OK = 26,
	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_NOT_ENOUGH_SPACE = 27,	// �κ��丮 ������ ������
	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_NO_ITEM = 28,			// ���ڿ� �������� ����
	ADD_ITEM_TO_ITEM_VERIFY_OPEN_CASE_FAIL_INCORRECT_KEY = 29,		// ���ڿ� ���� �ʴ� ����

#endif //__TREASURE_BOX
#if __CONTENTS(__IMI_LOW_LEVEL_ITEM)
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DOWN_GRADE = 30,
#endif //__IMI_LOW_LEVEL_ITEM

	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DELETE_DEFENSE = 31,
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_THIRDOPTION_PENALTY_DEFENSE = 32,
	
	ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAIL = 33,
	
	ADD_ITEM_TO_ITEM_VERIFY_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerify
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerify : public Packet 
{

public:
	GCAddItemToItemVerify() { m_Code = ADD_ITEM_TO_ITEM_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCAddItemToItemVerify() {}

public:
	void read(SocketInputStream & iStream);
	void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	size_t getPacketSize() const;
	string getPacketName() const { return "GCAddItemToItemVerify"; }
	string toString() const;
	
public:
	BYTE getCode(void) const { return m_Code;}
	void setCode(BYTE code) { m_Code = code;}

	uint getParameter(void) const { return m_Parameter; }
	void setParameter(uint parameter) { m_Parameter = parameter; }

	void setThirdOptionType(const list<OptionType_t>& optionType) { m_ThirdOptionType = optionType; }
	std::list<OptionType_t>& getThirdOptionType() { return m_ThirdOptionType; }
	BYTE getThirdEnchantType() const { return m_EnchantClass; }
	void setThirdEnchantType(BYTE ThirdEnchantType) {m_EnchantClass = ThirdEnchantType; }
	BYTE getGrade() const { return m_Grade; }
	void setGrade(BYTE grade) { m_Grade = grade; }

private: 
	BYTE m_Code;
	uint m_Parameter;

	list<OptionType_t> m_ThirdOptionType;
	BYTE m_EnchantClass;
	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCAddItemToItemVerify(); }
	string getPacketName() const { return "GCAddItemToItemVerify"; }
	PacketID_t getPacketID() const { return Packet::PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	PacketSize_t getPacketMaxSize() const { return szBYTE + szuint + 255 + szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyHandler 
{
public:
	static void execute( GCAddItemToItemVerify* pPacket, Player* pPlayer);
};

#endif
