//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneConnectionFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_CONNECTION_FAILED_H__
#define __GC_PHONE_CONNECTION_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailed;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailed : public Packet {

public :
	
	// constructor
	GCPhoneConnectionFailed ();
	
	// destructor
	~GCPhoneConnectionFailed ();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_PHONE_CONNECTION_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCPhoneConnectionFailed"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

private :

};

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailedFactory;
//
// Factory for GCPhoneConnectionFailed
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneConnectionFailedFactory () {}
	
	// destructor
	virtual ~GCPhoneConnectionFailedFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCPhoneConnectionFailed(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCPhoneConnectionFailed"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_PHONE_CONNECTION_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailedHandler {

public :

	// execute packet's handler
	static void execute ( GCPhoneConnectionFailed * pGCPhoneConnectionFailed , Player * pPlayer );

};

#endif
