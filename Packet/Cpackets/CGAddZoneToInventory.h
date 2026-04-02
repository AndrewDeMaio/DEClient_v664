//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddZoneToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ZONE_TO_INVENTORY_H__
#define __CG_ADD_ZONE_TO_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAddZoneToInventory;
//
//////////////////////////////////////////////////////////////////////

class CGAddZoneToInventory : public Packet {
public :

	// constructor
	CGAddZoneToInventory();

	// destructor
	~CGAddZoneToInventory();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_ADD_ZONE_TO_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGAddZoneToInventoryPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGAddZoneToInventory"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get/set X Coordicate
	Coord_t getZoneX () const { return m_ZoneX; }
	void setZoneX ( Coord_t ZoneX ) { m_ZoneX = ZoneX; }

	// get/set Y Coordicate
	Coord_t getZoneY () const { return m_ZoneY; }
	void setZoneY ( Coord_t ZoneY ) { m_ZoneY = ZoneY; }

	// get / set Ivnentory X, Y Coordicate
	CoordInven_t getInvenX() const { return m_InvenX; }
	void setInvenX( CoordInven_t InvenX ) { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getInvenY() const { return m_InvenY; }
	void setInvenY( CoordInven_t InvenY ) { m_InvenY = InvenY; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// �������� �ִ� Zone��  X, Y ��ǥ.
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

	// Inventory�� X, Y ��ǥ.
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGAddZoneToInventoryFactory;
//
// Factory for CGAddZoneToInventory
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGAddZoneToInventoryFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGAddZoneToInventory(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGAddZoneToInventory"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_ADD_ZONE_TO_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGAddZoneToInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGAddZoneToInventoryHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGAddZoneToInventoryHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGAddZoneToInventory * pPacket , Player * player );
	};

#endif
#endif
