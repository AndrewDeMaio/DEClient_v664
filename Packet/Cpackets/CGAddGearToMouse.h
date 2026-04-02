//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddGearToMouse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_GEAR_TO_MOUSE_H__
#define __CG_ADD_GEAR_TO_MOUSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAddGearToMouse;
//
//////////////////////////////////////////////////////////////////////

class CGAddGearToMouse : public Packet {
public :

	// constructor
	CGAddGearToMouse();

	// destructor
	~CGAddGearToMouse();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_ADD_GEAR_TO_MOUSE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGAddGearToMousePacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID + szSlotID; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName () const { return "CGAddGearToMouse"; }
	
	// get packet's debug std::string
	std::string toString () const;
#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set SlotID
	SlotID_t getSlotID() const { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID ; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class CGAddGearToMouseFactory;
//
// Factory for CGAddGearToMouse
//
//////////////////////////////////////////////////////////////////////

#ifdef __DEBUG_OUTPUT__
class CGAddGearToMouseFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGAddGearToMouse(); }

	// get packet name
	std::string getPacketName () const { return "CGAddGearToMouse"; }
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_ADD_GEAR_TO_MOUSE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGAddGearToMousePacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szSlotID; }

};
#endif


//////////////////////////////////////////////////////////////////////
//
// class CGAddGearToMouseHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGAddGearToMouseHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGAddGearToMouse * pPacket , Player * player );
	};

#endif
#endif
