//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_INJURIOUS_CREATURE_H__
#define __GC_ADD_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreature;
//
// Ŭ���̾�Ʈ�� �������� ������ AddInjuriousCreature ��Ŷ�̴�.
// ���ο� AddInjuriousCreature String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreature : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_ADD_INJURIOUS_CREATURE; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Name.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "GCAddInjuriousCreature"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif

	// get/set Name
	const std::string& getName() const { return m_Name; }
	void setName(const std::string & Name) { m_Name = Name; }

private :

	std::string m_Name;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureFactory;
//
// Factory for GCAddInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new GCAddInjuriousCreature(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "GCAddInjuriousCreature"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_ADD_INJURIOUS_CREATURE; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const {
	int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
	localLongName = 22;
#endif //__LOCALIZING_LONGNAME
		return szBYTE + 10 + localLongName; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(GCAddInjuriousCreature* pPacket, Player* pPlayer);

};

#endif
