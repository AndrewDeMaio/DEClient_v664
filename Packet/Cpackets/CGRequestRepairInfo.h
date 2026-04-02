//-----------------------------------------------------------------------------
// 
// Filename    : CGRequestRepairInfo.h 
// Written By  : �輺��
// Description :
// 
//-----------------------------------------------------------------------------

#ifndef __CG_REQUEST_REPAIR_INFO_H__
#define __CG_REQUEST_REPAIR_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGRequestRepairInfo;
//
//--------------------------------------------------------------------------------

class CGRequestRepairInfo : public Packet {

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_REQUEST_REPAIR_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID; }

	// get packet name
	string getPacketName() const { return "CGRequestRepairInfo"; }
	
	// get packet's debug string
	string toString() const;
	
public:

	// get/set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

private :
	
	// Item Object ID
	ObjectID_t m_ObjectID;

};


//-----------------------------------------------------------------------------
//
// class CGRequestRepairInfoFactory;
//
// Factory for CGRequestRepairInfo
//
//-----------------------------------------------------------------------------

class CGRequestRepairInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGRequestRepairInfo(); }

	// get packet name
	string getPacketName() const { return "CGRequestRepairInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_REQUEST_REPAIR_INFO; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const { return szObjectID; }

};


//--------------------------------------------------------------------------------
//
// class CGRequestRepairInfoHandler;
//
//--------------------------------------------------------------------------------

class CGRequestRepairInfoHandler {
	
public:

	// execute packet's handler
	static void execute(CGRequestRepairInfo* pPacket, Player* player);
	static void executeNormal(CGRequestRepairInfo* pPacket, Player* player, float fRepairDiscountRate = 0.0f);
	static void executeMotorcycle(CGRequestRepairInfo* pPacket, Player* player, float fRepairDiscountRate = 0.0f);
	static void executeAll(CGRequestRepairInfo* pPacket, Player* player, float fRepairDiscountRate = 0.0f);
};

#endif
