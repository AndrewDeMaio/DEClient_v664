//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveFromGear.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_FROM_GEAR_H__
#define __GC_REMOVE_FROM_GEAR_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGear;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGear : public Packet {

public :
	
	// constructor
	GCRemoveFromGear ();
	
	// destructor
	~GCRemoveFromGear ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_REMOVE_FROM_GEAR; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szSlotID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCRemoveFromGear"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set SlotID
	SlotID_t getSlotID() const { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID; }

private :

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGearFactory;
//
// Factory for GCRemoveFromGear
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGearFactory : public PacketFactory {

public :
	
	// constructor
	GCRemoveFromGearFactory () {}
	
	// destructor
	virtual ~GCRemoveFromGearFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRemoveFromGear(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRemoveFromGear"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_REMOVE_FROM_GEAR; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGearHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGearHandler {

public :

	// execute packet's handler
	static void execute ( GCRemoveFromGear * pGCRemoveFromGear , Player * pPlayer );

};

#endif
