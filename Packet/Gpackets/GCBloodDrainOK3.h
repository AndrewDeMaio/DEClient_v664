//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK3.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_3_H__
#define __GC_BLOOD_DRAIN_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3 : public Packet {

public :
	
	// constructor
	GCBloodDrainOK3 ();
	
	// destructor
	~GCBloodDrainOK3 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_BLOOD_DRAIN_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCBloodDrainOK3"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif	

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID( ObjectID_t TargetObjectID ) { m_TargetObjectID = TargetObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3Factory;
//
// Factory for GCBloodDrainOK3
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK3Factory () {}
	
	// destructor
	virtual ~GCBloodDrainOK3Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCBloodDrainOK3(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCBloodDrainOK3"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_BLOOD_DRAIN_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK3Handler {

public :

	// execute packet's handler
	static void execute ( GCBloodDrainOK3 * pGCBloodDrainOK3 , Player * pPlayer );

};

#endif
