//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MOVE_H__
#define __CG_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGMove;
//
//////////////////////////////////////////////////////////////////////

class CGMove : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGMovePacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szCoord + szCoord + szDir; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGMove"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get/set X Coordicate
	Coord_t getX () const { return m_X; }
	void setX ( Coord_t x ) { m_X = x; }

	// get/set Y Coordicate
	Coord_t getY () const { return m_Y; }
	void setY ( Coord_t y ) { m_Y = y; }

	// get/set Direction
	Dir_t getDir () const { return m_Dir; }
	void setDir ( Dir_t dir ) { m_Dir = dir; }
	
private :
	
	Coord_t m_X;			// X ��ǥ
	Coord_t m_Y;			// Y ��ǥ
	Dir_t m_Dir;			// ����

};


//////////////////////////////////////////////////////////////////////
//
// class CGMoveFactory;
//
// Factory for CGMove
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGMove(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGMove"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGMovePacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szCoord + szCoord + szDir; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGMoveHandler;
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGMoveHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGMove * pPacket , Player * player );
	};

#endif
#endif
