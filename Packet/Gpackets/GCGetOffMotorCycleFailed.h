//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_FAILED_H__
#define __GC_GET_OFF_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailed;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycleFailed ();
	
	// destructor
	~GCGetOffMotorCycleFailed ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCGetOffMotorCycleFailed"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedFactory;
//
// Factory for GCGetOffMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFailedFactory () {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFailedFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCGetOffMotorCycleFailed(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCGetOffMotorCycleFailed"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute ( GCGetOffMotorCycleFailed * pGCGetOffMotorCycleFailed , Player * pPlayer );

};

#endif
