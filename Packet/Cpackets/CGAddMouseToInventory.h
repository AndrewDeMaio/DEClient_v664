//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddMouseToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_INVENTORY_H__
#define __CG_ADD_MOUSE_TO_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAddMouseToInventory;
//
//////////////////////////////////////////////////////////////////////

class CGAddMouseToInventory : public Packet {
public :

	// constructor
	CGAddMouseToInventory();

	// destructor
	~CGAddMouseToInventory();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGAddMouseToInventoryPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID + szObjectID + szCoordInven + szCoordInven; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGAddMouseToInventory"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) { m_InventoryItemObjectID = InventoryItemObjectID; }

	// get / set Ivnentory X, Y Coordicate
	CoordInven_t getInvenX() const { return m_InvenX; }
	void setInvenX( CoordInven_t InvenX ) { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getInvenY() const { return m_InvenY; }
	void setInvenY( CoordInven_t InvenY ) { m_InvenY = InvenY; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// ���� �κ��丮 �������� ������Ʈ ���̵�. 0�̸� ���� �κ��丮���� ����
	ObjectID_t m_InventoryItemObjectID;
	
	// Inventory�� X, Y ��ǥ.
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGAddMouseToInventoryFactory;
//
// Factory for CGAddMouseToInventory
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGAddMouseToInventoryFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGAddMouseToInventory(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGAddMouseToInventory"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_ADD_MOUSE_TO_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGAddMouseToInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szObjectID + szCoordInven + szCoordInven; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGAddMouseToInventoryHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGAddMouseToInventoryHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGAddMouseToInventory * pPacket , Player * player );
	};

#endif
#endif
