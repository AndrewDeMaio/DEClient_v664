//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCVisibleFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_VISIBLE_FAIL_H__
#define __GC_VISIBLE_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCVisibleFail;
//
//////////////////////////////////////////////////////////////////////

class GCVisibleFail : public Packet {

public :

	// constructor
	GCVisibleFail () {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_VISIBLE_FAIL; }
	
	// get packet's body size
	size_t getPacketSize () const { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCVisibleFail"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleFailFactory;
//
// Factory for  GCVisibleFail
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCVisibleFail(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCVisibleFail"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_VISIBLE_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleFailHandler {

public :

	// execute packet's handler
	static void execute ( GCVisibleFail * pPacket , Player * pPlayer );

};

#endif
