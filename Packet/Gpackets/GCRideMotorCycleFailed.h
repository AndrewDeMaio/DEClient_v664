//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_FAILED_H__
#define __GC_RIDE_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailed;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCRideMotorCycleFailed ();
	
	// destructor
	~GCRideMotorCycleFailed ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RIDE_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCRideMotorCycleFailed"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedFactory;
//
// Factory for GCRideMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleFailedFactory () {}
	
	// destructor
	virtual ~GCRideMotorCycleFailedFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRideMotorCycleFailed(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRideMotorCycleFailed"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RIDE_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute ( GCRideMotorCycleFailed * pGCRideMotorCycleFailed , Player * pPlayer );

};

#endif
