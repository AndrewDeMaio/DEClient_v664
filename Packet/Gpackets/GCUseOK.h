//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_OK_H__
#define __GC_USE_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseOK : public ModifyInfo {

public :

	// Constructor
	GCUseOK();

	// Desctructor
	~GCUseOK();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_USE_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUseOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKFactory;
//
// Factory for GCUseOK
//
//////////////////////////////////////////////////////////////////////

class GCUseOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCUseOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUseOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_USE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return 255; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GCUseOK * pPacket , Player * player );
};

#endif
