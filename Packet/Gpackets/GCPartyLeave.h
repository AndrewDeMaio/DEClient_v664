//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyLeave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_LEAVE_H__
#define __GC_PARTY_LEAVE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeave;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeave : public Packet 
{
public:
	void read(SocketInputStream & iStream);
	void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_PARTY_LEAVE; }
	size_t getPacketSize() const 
	{ 
		return szBYTE*2 + m_Expeller.size() + m_Expellee.size();
	}
	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const { return "GCPartyLeave"; }
		std::string toString() const;
	#endif

public:
	const std::string& getExpeller(void) const { return m_Expeller; }
	void setExpeller(const std::string& name) { m_Expeller = name; }

	const std::string& getExpellee(void) const { return m_Expellee; }
	void setExpellee(const std::string& name) { m_Expellee = name; }

private:
	// �������� ȥ�� ��Ƽ���� ������ ���������� ��쿡��
	// �߹����� �̸��� NULL�̴�.
	// �������� �ٸ� ����� ���ؼ� ���������� ��쿡��
	// �߹����� �̸��� NULL�� �ƴϴ�.
	// ��� ��쿡�� �߹���� ���� �̸��� NULL�� ���� ����.
	std::string m_Expeller; // �߹���
	std::string m_Expellee; // �߹���� ��
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeaveFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeaveFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCPartyLeave(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const { return "GCPartyLeave"; }
	#endif
	PacketID_t getPacketID() const { return Packet::PACKET_GC_PARTY_LEAVE; }
	PacketSize_t getPacketMaxSize() const { return szBYTE*2 + 20; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeaveHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeaveHandler 
{
public:
	static void execute(GCPartyLeave* pPacket, Player* pPlayer);
};

#endif
