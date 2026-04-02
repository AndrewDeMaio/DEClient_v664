//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUntransform.h 
// Written By  : crazydog
// Description : ���㳪 ���뿡�� ����������� ���ƿ���������..
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_UNTRANSFORM_H__
#define __CG_UNTRANSFORM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUntransform;
//
//////////////////////////////////////////////////////////////////////

class CGUntransform : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_UNTRANSFORM; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUntransformPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGUntransform"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
};


//////////////////////////////////////////////////////////////////////
//
// class CGUntransformFactory;
//
// Factory for CGUntransform
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGUntransformFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGUntransform(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGUntransform"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_UNTRANSFORM; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUntransformPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return 0; }
	

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGUntransformHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGUntransformHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGUntransform * pPacket , Player * player );
	};

#endif

#endif