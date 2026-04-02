//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycleOK.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_OK_H__
#define __GC_GET_OFF_MOTORCYCLE_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleOK;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleOK : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycleOK ();
	
	// destructor
	~GCGetOffMotorCycleOK ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_GET_OFF_MOTORCYCLE_OK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const {return 0;}

#ifdef __DEBUG_OUTPUT__
	// get packet's name
	std::string getPacketName () const { return "GCGetOffMotorCycleOK"; }
	
	// get packet's debug std::string
	std::string toString () const;
#endif

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleOKFactory;
//
// Factory for GCGetOffMotorCycleOK
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleOKFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleOKFactory () {}
	
	// destructor
	virtual ~GCGetOffMotorCycleOKFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCGetOffMotorCycleOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCGetOffMotorCycleOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const {return 0;}

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleOKHandler;
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleOKHandler {

public :

	// execute packet's handler
	static void execute ( GCGetOffMotorCycleOK * pGCGetOffMotorCycleOK , Player * pPlayer );

};

#endif
