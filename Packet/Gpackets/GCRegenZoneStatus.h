//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRegenZoneStatus.h 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REGEN_ZONE_STATUS_H__
#define __GC_REGEN_ZONE_STATUS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include <vector>

//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatus;
//
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatus : public Packet {

public :
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_REGEN_ZONE_STATUS; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE * 8; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCRegenZoneStatus"; }
	
	// get packet's debug string
	std::string toString() const;
#endif

	BYTE getStatus( uint index ) const { return m_Statuses[index]; }
	void setStatus( uint index, BYTE status ) { m_Statuses[index] = status; }

private :
	std::vector<BYTE>	m_Statuses;
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusFactory;
//
// Factory for GCRegenZoneStatus
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCRegenZoneStatus(); }

	// get packet name
	std::string getPacketName() const { return "GCRegenZoneStatus"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_REGEN_ZONE_STATUS; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRegenZoneStatusPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE * 8; } 
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCRegenZoneStatus* pPacket, Player* pPlayer);

};

#endif
