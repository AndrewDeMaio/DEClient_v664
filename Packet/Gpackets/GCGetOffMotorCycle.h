//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_H__
#define __GC_GET_OFF_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycle;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycle : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycle ();
	
	// destructor
	~GCGetOffMotorCycle ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_GET_OFF_MOTORCYCLE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCGetOffMotorCycle"; }
		
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
// class GCGetOffMotorCycleFactory;
//
// Factory for GCGetOffMotorCycle
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFactory () {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCGetOffMotorCycle(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCGetOffMotorCycle"; }	
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleHandler {

public :

	// execute packet's handler
	static void execute ( GCGetOffMotorCycle * pGCGetOffMotorCycle , Player * pPlayer );

};

#endif
