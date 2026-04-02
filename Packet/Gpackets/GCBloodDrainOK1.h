//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_1_H__
#define __GC_BLOOD_DRAIN_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1 : public ModifyInfo {

public :
	
	// constructor
	GCBloodDrainOK1 ();
	
	// destructor
	~GCBloodDrainOK1 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_BLOOD_DRAIN_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCBloodDrainOK1"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set CEffectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Factory;
//
// Factory for GCBloodDrainOK1
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK1Factory () {}
	
	// destructor
	virtual ~GCBloodDrainOK1Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCBloodDrainOK1(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCBloodDrainOK1"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_BLOOD_DRAIN_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Handler {

public :

	// execute packet's handler
	static void execute ( GCBloodDrainOK1 * pGCBloodDrainOK1 , Player * pPlayer );

};

#endif
