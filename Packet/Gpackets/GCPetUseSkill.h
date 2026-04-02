//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetUseSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_USE_SKILL_H__
#define __GC_PET_USE_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkill;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkill : public Packet 
{
public:
	GCPetUseSkill();
	~GCPetUseSkill();
	
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_PET_USE_SKILL; }
	size_t getPacketSize() const { return szObjectID + szObjectID; }

#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCPetUseSkill"; }
	string toString() const;
#endif

public:
	ObjectID_t	getAttacker() const { return m_Attacker; }
	ObjectID_t	getTarget() const { return m_Target; }

	void	setAttacker( ObjectID_t Attacker ) { m_Attacker = Attacker; }
	void	setTarget( ObjectID_t Target ) { m_Target = Target; }

private:
	ObjectID_t	m_Attacker, m_Target;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkillFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkillFactory : public PacketFactory 
{
public :
	GCPetUseSkillFactory() {}
	virtual ~GCPetUseSkillFactory() {}
	
public:
	Packet* createPacket() { return new GCPetUseSkill(); }
	string getPacketName() const { return "GCPetUseSkill"; }
	PacketID_t getPacketID() const { return Packet::PACKET_GC_PET_USE_SKILL; }
	PacketSize_t getPacketMaxSize() const { return szObjectID + szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkillHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkillHandler 
{
public:
	static void execute(GCPetUseSkill* pGCPetUseSkill, Player* pPlayer);

};

#endif
