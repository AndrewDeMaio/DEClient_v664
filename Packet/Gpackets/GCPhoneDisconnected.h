//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneDisconnected.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_DISCONNECTED_H__
#define __GC_PHONE_DISCONNECTED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnected;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnected : public Packet {

public :
	
	// constructor
	GCPhoneDisconnected ();
	
	// destructor
	~GCPhoneDisconnected ();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_PHONE_DISCONNECTED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szPhoneNumber + szSlotID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCPhoneDisconnected"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const { return m_PhoneNumber; }
	void setPhoneNumber( PhoneNumber_t PhoneNumber ) { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedFactory;
//
// Factory for GCPhoneDisconnected
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneDisconnectedFactory () {}
	
	// destructor
	virtual ~GCPhoneDisconnectedFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCPhoneDisconnected(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCPhoneDisconnected"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_PHONE_DISCONNECTED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szPhoneNumber + szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedHandler {

public :

	// execute packet's handler
	static void execute ( GCPhoneDisconnected * pGCPhoneDisconnected , Player * pPlayer );

};

#endif
