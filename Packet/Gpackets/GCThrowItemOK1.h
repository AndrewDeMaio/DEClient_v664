//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_1_H__
#define __GC_THROW_ITEM_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1 : public Packet {

public :
	
	// constructor
	GCThrowItemOK1 ();
	
	// destructor
	~GCThrowItemOK1 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_THROW_ITEM_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID ; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCThrowItemOK1"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set TargetObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

private :
	
	// TargetObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1Factory;
//
// Factory for GCThrowItemOK1
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK1Factory () {}
	
	// destructor
	virtual ~GCThrowItemOK1Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCThrowItemOK1(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCThrowItemOK1"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_THROW_ITEM_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK1Handler {

public :

	// execute packet's handler
	static void execute ( GCThrowItemOK1 * pGCThrowItemOK1 , Player * pPlayer );

};

#endif
