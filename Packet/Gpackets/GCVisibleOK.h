//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCVisibleOK.h 
// Written By  :  Elca
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_VISIBLE_OK_H__
#define __GC_VISIBLE_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleOK;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCVisibleOK : public Packet {

public :

	// constructor
	GCVisibleOK () {}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_VISIBLE_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static GCVisibleOKPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCVisibleOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	

public :
};


//////////////////////////////////////////////////////////////////////
//
// class GCVisibleOKFactory;
//
// Factory for GCVisibleOK
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCVisibleOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCVisibleOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_VISIBLE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCVisibleOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleOKHandler {

public :

	// execute packet's handler
	static void execute (  GCVisibleOK * pPacket , Player * pPlayer );

};

#endif
