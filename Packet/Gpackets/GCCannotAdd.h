//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCannotAdd.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CANNOT_ADD_H__
#define __GC_CANNOT_ADD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCCannotAdd;
//
//////////////////////////////////////////////////////////////////////

class GCCannotAdd : public Packet {

public :
	
	GCCannotAdd()
	{
#if __CONTENTS(__GEAR_SWAP_CHANGE)	//GCCannotAdd				m_CannotReason = CANNOT_REASON_FAIL;
		m_CannotReason = CANNOT_REASON_FAIL;
#endif
	}

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_CANNOT_ADD; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCCannotAddPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const 
	{ 
		PacketSize_t	szSize	= 0;
		szSize	+=	szObjectID; 
#if __CONTENTS(__GEAR_SWAP_CHANGE)		//  GCCannotAdd		eCannotReason ������ ��Ŷ �߰�
		szSize	+=	sizeof(int);
#endif // __GEAR_SWAP_CHANGE
		return szSize;
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCCannotAdd"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :
#if __CONTENTS(__GEAR_SWAP_CHANGE)	// GCCannotAdd	eCannotReason ��� ����
	enum eCannotReason
	{
		CANNOT_REASON_FAIL = 0,

		CANNOT_REASON_NOT_EXIST_ITEM = 1,
		CANNOT_REASON_PREMIUM_FEATURE = 2,

		// GearSlot
		CANNOT_REASON_DIFFERENT_GEARSLOTID = 10,

	};
#endif // __GEAR_SWAP_CHANGE

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

#if __CONTENTS(__GEAR_SWAP_CHANGE)		//GCCannotAdd  eCannotReason ����� ���� �� ��� �Լ�
	int getCannotreason() { return m_CannotReason; }
	void setCannotreason( int CannotReason ) { m_CannotReason = CannotReason; }
#endif // __GEAR_SWAP_CHANGE

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

#if __CONTENTS(__GEAR_SWAP_CHANGE)	////  GCCannotAdd		eCannotReason ���� �߰�
	int m_CannotReason;
#endif // __GEAR_SWAP_CHANGE
};


//////////////////////////////////////////////////////////////////////
//
// class GCCannotAddFactory;
//
// Factory for GCCannotAdd
//
//////////////////////////////////////////////////////////////////////

class GCCannotAddFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCCannotAdd(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCCannotAdd"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_CANNOT_ADD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCCannotAddPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{
		PacketSize_t	szSize	= 0;
		szSize	+= szObjectID;
#if __CONTENTS(__GEAR_SWAP_CHANGE)		//  GCCannotAddFactory		eCannotReason ������ ��Ŷ �߰�
		szSize	+= sizeof(int);
#endif // __GEAR_SWAP_CHANGE
		return szSize; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCCannotAddHandler;
//
//////////////////////////////////////////////////////////////////////

class GCCannotAddHandler {
	
public :

	// execute packet's handler
	static void execute ( GCCannotAdd * pPacket , Player * player );
};

#endif
