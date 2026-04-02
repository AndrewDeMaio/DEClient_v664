//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_2_H__
#define __GC_THROW_ITEM_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2 : public ModifyInfo {

public :
	
	// constructor
	GCThrowItemOK2 ();
	
	// destructor
	~GCThrowItemOK2 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_THROW_ITEM_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCThrowItemOK2"; }
		
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
// class GCThrowItemOK2Factory;
//
// Factory for GCThrowItemOK2
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK2Factory () {}
	
	// destructor
	virtual ~GCThrowItemOK2Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCThrowItemOK2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCThrowItemOK2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_THROW_ITEM_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2Handler {

public :

	// execute packet's handler
	static void execute ( GCThrowItemOK2 * pGCThrowItemOK2 , Player * pPlayer );

};

#endif
