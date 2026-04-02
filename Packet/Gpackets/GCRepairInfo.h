//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRepairInfo.h 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REPAIR_INFO_H__
#define __GC_REPAIR_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRepairInfo;
//
//////////////////////////////////////////////////////////////////////

class GCRepairInfo : public Packet {

public :
	virtual ~GCRepairInfo() {}	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_REPAIR_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID + szPrice * 2; }

	// get packet name
	string getPacketName() const { return "GCRepairInfo"; }
	
	// get packet's debug string
	string toString() const;

	// get/set sender's creature id
	ObjectID_t GetItemOID() const { return m_ItemOID; }
	void SetItemOID(const ObjectID_t & ItemOID) { m_ItemOID = ItemOID; }

	Price_t GetRepairPrice() const { return m_RepairPrice; }
	void SetRepairPrice(const Price_t & RepairPrice) { m_RepairPrice = RepairPrice; }
	
	Price_t GetRepairDiscountPrice() const { return m_RepairDiscountPrice; }
	void SetRepairDiscountPrice(const Price_t & RepairDiscountPrice) { m_RepairDiscountPrice = RepairDiscountPrice; }

private :
	
	ObjectID_t m_ItemOID;

	Price_t m_RepairPrice;
	Price_t m_RepairDiscountPrice;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCRepairInfoFactory;
//
// Factory for GCRepairInfo
//
//////////////////////////////////////////////////////////////////////

class GCRepairInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCRepairInfo(); }

	// get packet name
	string getPacketName() const { return "GCRepairInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_REPAIR_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRepairInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szObjectID + szPrice * 2 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRepairInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRepairInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCRepairInfo* pPacket, Player* pPlayer);

};

#endif
