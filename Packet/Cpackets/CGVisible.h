//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVisible.h 
// Written By  : crazydog
// Description : ���㳪 ���뿡�� ����������� ���ƿ���������..
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VISIBLE_H__
#define __CG_VISIBLE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGVisible;
//
//////////////////////////////////////////////////////////////////////

class CGVisible : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_VISIBLE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGVisiblePacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGVisible"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

};


//////////////////////////////////////////////////////////////////////
//
// class CGVisibleFactory;
//
// Factory for CGVisible
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGVisibleFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGVisible(); }

	// get packet name
	std::string getPacketName () const { return "CGVisible"; }
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_VISIBLE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGVisiblePacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return 0; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGVisibleHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGVisibleHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGVisible * pPacket , Player * player );
	};
#endif

#endif