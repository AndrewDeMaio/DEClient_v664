//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_INJURIOUS_CREATURE_H__
#define __GC_REMOVE_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveInjuriousCreature;
//
// Ŭ���̾�Ʈ�� �������� ������ RemoveInjuriousCreature ��Ŷ�̴�.
// ���ο� RemoveInjuriousCreature String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreature : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_REMOVE_INJURIOUS_CREATURE; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Name.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "GCRemoveInjuriousCreature"; }
		
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
// class GCRemoveInjuriousCreatureFactory;
//
// Factory for GCRemoveInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new GCRemoveInjuriousCreature(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "GCRemoveInjuriousCreature"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_REMOVE_INJURIOUS_CREATURE; }

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
// class GCRemoveInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(GCRemoveInjuriousCreature* pPacket, Player* pPlayer);

};

#endif
