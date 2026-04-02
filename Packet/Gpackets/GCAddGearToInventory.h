//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddGearToInventory.h 
// Written By  : crazydog
// Description : Skill ShieldStrike�� ���� �߻�. 
// 				shield�� ����â���� inventory�� ������.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_GEAR_TO_INVENTORY_H__
#define __GC_ADD_GEAR_TO_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCAddGearToInventory;
//
//////////////////////////////////////////////////////////////////////

class GCAddGearToInventory : public Packet {
public :

	// constructor
	GCAddGearToInventory();

	// destructor
	~GCAddGearToInventory();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_GEAR_TO_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddGearToInventoryPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szSlotID + szCoordInven + szCoordInven; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddGearToInventory"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	SlotID_t getSlotID() { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID; }

	// get / set Ivnentory X, Y Coordicate
	CoordInven_t getInvenX() const { return m_InvenX; }
	void setInvenX( CoordInven_t InvenX ) { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getInvenY() const { return m_InvenY; }
	void setInvenY( CoordInven_t InvenY ) { m_InvenY = InvenY; }

private :
	
	// wear part ID
	SlotID_t m_SlotID;

	// Inventory�� X, Y ��ǥ.
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddGearToInventoryFactory;
//
// Factory for GCAddGearToInventory
//
//////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddGearToInventory(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddGearToInventory"; }
	#endif	
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_GEAR_TO_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCAddGearToInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szSlotID + szCoordInven + szCoordInven; }

};

//////////////////////////////////////////////////////////////////////
//
// class GCAddGearToInventoryHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryHandler {
	
public :

	// execute packet's handler
	static void execute ( GCAddGearToInventory * pPacket , Player * player );
};


#endif
