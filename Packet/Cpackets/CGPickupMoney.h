//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPickupMoney.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PICKUP_MONEY_H__
#define __CG_PICKUP_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoney;
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoney : public Packet {
public :

	// constructor
	CGPickupMoney();

	// destructor
	~CGPickupMoney();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_PICKUP_MONEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID + szCoord + szCoord; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGPickupMoney"; }
		
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

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// �������� �ִ� Zone��  X, Y ��ǥ.
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyFactory;
//
// Factory for CGPickupMoney
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGPickupMoneyFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGPickupMoney(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGPickupMoney"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_PICKUP_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szCoord + szCoord; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyHandler;
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_CLIENT__
class CGPickupMoneyHandler {
	
public :

	// execute packet's handler
	static void execute ( CGPickupMoney * pPacket , Player * player );
};
#endif

#endif
