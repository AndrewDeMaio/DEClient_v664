//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAbsorbSoul 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ABSORB_SOUL_H__
#define __CG_ABSORB_SOUL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoul;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoul : public Packet {

public:
	
	// constructor
	CGAbsorbSoul();
	
	// destructor
	~CGAbsorbSoul();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_ABSORB_SOUL; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID + szZoneCoord*2 + szObjectID + szCoordInven*4;}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGAbsorbSoul"; }
	
	// get packet's debug string
	std::string toString() const;
#endif

	// get/set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	
	ObjectID_t getInvenObjectID() const { return m_InvenObjectID; }
	void setInvenObjectID(ObjectID_t invenObjectID) { m_InvenObjectID = invenObjectID; }

	Coord_t getInvenX() const { return m_InvenX; }
	void setInvenX( CoordInven_t x ) { m_InvenX = x; }

	Coord_t getInvenY() const { return m_InvenY; }
	void setInvenY( CoordInven_t y ) { m_InvenY = y; }

	Coord_t getTargetInvenX() const { return m_TargetInvenX; }
	void setTargetInvenX( CoordInven_t x ) { m_TargetInvenX = x; }

	Coord_t getTargetInvenY() const { return m_TargetInvenY; }
	void setTargetInvenY( CoordInven_t y ) { m_TargetInvenY = y; }

	Coord_t getTargetZoneX() const { return m_TargetZoneX; }
	void setTargetZoneX( ZoneCoord_t x ) { m_TargetZoneX = x; }

	Coord_t getTargetZoneY() const { return m_TargetZoneY; }
	void setTargetZoneY( ZoneCoord_t y ) { m_TargetZoneY = y; }
	
private :
	
	ObjectID_t m_ObjectID;  // ObjectID
	
	ObjectID_t m_InvenObjectID; // ����� ObjectID
	CoordInven_t m_InvenX;			// X ��ǥ
	CoordInven_t m_InvenY;			// Y ��ǥ
	CoordInven_t m_TargetInvenX;	// Target X ��ǥ
	CoordInven_t m_TargetInvenY;	// Target Y ��ǥ
	ZoneCoord_t m_TargetZoneX;	// Target X ��ǥ
	ZoneCoord_t m_TargetZoneY;	// Target Y ��ǥ
};


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulFactory;
//
// Factory for CGAbsorbSoul
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGAbsorbSoulFactory : public PacketFactory {

public:
	
	// constructor
	CGAbsorbSoulFactory() {}
	
	// destructor
	virtual ~CGAbsorbSoulFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGAbsorbSoul(); }

	// get packet name
	std::string getPacketName() const { return "CGAbsorbSoul"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_ABSORB_SOUL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szObjectID + szZoneCoord*2+ szObjectID + szCoordInven*4; }

};
#endif

//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoulHandler {
	
public:

	// execute packet's handler
	static void execute(CGAbsorbSoul* pCGAbsorbSoul, Player* player);
};

#endif
