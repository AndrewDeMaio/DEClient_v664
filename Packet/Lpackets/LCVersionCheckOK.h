//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCVersionCheckOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_VERSION_CHECK_OK_H__
#define __LC_VERSION_CHECK_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOK : public Packet {

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_VERSION_CHECK_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCVersionCheckOKPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "LCVersionCheckOK"; }
		
		// get packet's debug std::string
		std::string toString () const { return "LCVersionCheckOK"; }
	#endif
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOKFactory;
//
// Factory for LCVersionCheckOK
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCVersionCheckOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCVersionCheckOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_VERSION_CHECK_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckOKHandler {

public :

	// execute packet's handler
	static void execute ( LCVersionCheckOK * pPacket , Player * pPlayer );

};

#endif
