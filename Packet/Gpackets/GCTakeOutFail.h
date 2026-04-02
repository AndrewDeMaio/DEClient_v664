//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOutFail.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OUT_FAIL_H__
#define __GC_TAKE_OUT_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFail;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFail : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_TAKE_OUT_FAIL; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize() const { return szObjectID; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCTakeOutFail"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailFactory;
//
// Factory for GCTakeOutFail
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCTakeOutFail(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCTakeOutFail"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_TAKE_OUT_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailHandler {
	
public :

	// execute packet's handler
	static void execute(GCTakeOutFail* pPacket, Player* player);
};

#endif
