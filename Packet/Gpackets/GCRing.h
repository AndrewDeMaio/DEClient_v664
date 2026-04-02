//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRing.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RING_H__
#define __GC_RING_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRing;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCRing : public Packet {

public :
	
	// constructor
	GCRing ();
	
	// destructor
	~GCRing ();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RING; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szPhoneNumber + szSlotID + szBYTE + m_Name.size(); }

	#ifdef __DEBUG_OUTPUT__	
		// get packet's name
		std::string getPacketName () const { return "GCRing"; }
	
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const { return m_PhoneNumber; }
	void setPhoneNumber( PhoneNumber_t PhoneNumber ) { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID; }

	// get / set Name 
	const std::string& getName() const { return m_Name; }
	void setName( const std::string & Name ) { m_Name = Name; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

	// ��ȭ �� ����� �̸�.
	std::string m_Name;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRingFactory;
//
// Factory for GCRing
//
//////////////////////////////////////////////////////////////////////

class GCRingFactory : public PacketFactory {

public :
	
	// constructor
	GCRingFactory () {}
	
	// destructor
	virtual ~GCRingFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRing(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRing"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RING; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szPhoneNumber + szSlotID + szBYTE + 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRingHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRingHandler {

public :

	// execute packet's handler
	static void execute ( GCRing * pGCRing , Player * pPlayer );

};

#endif
