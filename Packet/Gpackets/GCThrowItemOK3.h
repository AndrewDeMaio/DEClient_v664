//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK3.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_3_H__
#define __GC_THROW_ITEM_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK3;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3 : public Packet {

public :
	
	// constructor
	GCThrowItemOK3 ();
	
	// destructor
	~GCThrowItemOK3 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_THROW_ITEM_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCThrowItemOK3"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
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
// class GCThrowItemOK3Factory;
//
// Factory for GCThrowItemOK3
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK3Factory () {}
	
	// destructor
	virtual ~GCThrowItemOK3Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCThrowItemOK3(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCThrowItemOK3"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_THROW_ITEM_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK3Handler {

public :

	// execute packet's handler
	static void execute ( GCThrowItemOK3 * pGCThrowItemOK3 , Player * pPlayer );

};

#endif
