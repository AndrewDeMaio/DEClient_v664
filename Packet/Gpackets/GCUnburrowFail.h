//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUnburrowFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNBURROW_FAIL_H__
#define __GC_UNBURROW_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCUnburrowFail;
//
//////////////////////////////////////////////////////////////////////

class GCUnburrowFail : public Packet {

public :

	// constructor
	GCUnburrowFail () {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_UNBURROW_FAIL; }
	
	// get packet's body size
	size_t getPacketSize () const { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCUnburrowFail"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowFailFactory;
//
// Factory for  GCUnburrowFail
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCUnburrowFail(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUnburrowFail"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_UNBURROW_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowFailHandler {

public :

	// execute packet's handler
	static void execute ( GCUnburrowFail * pPacket , Player * pPlayer );

};

#endif
