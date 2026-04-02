//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCCreatePCOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_CREATE_PC_OK_H__
#define __LC_CREATE_PC_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCOK : public Packet {

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) {}
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const {}

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_CREATE_PC_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCCreatePCOKPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "LCCreatePCOK"; }
		
		// get packet's debug std::string
		std::string toString () const { return "LCCreatePCOK"; }
	#endif
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCOKFactory;
//
// Factory for LCCreatePCOK
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCCreatePCOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCCreatePCOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_CREATE_PC_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCOKHandler {

public :

	// execute packet's handler
	static void execute ( LCCreatePCOK * pPacket , Player * pPlayer );

};

#endif
