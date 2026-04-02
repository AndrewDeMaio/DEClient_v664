//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MOVE_H__
#define __GC_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCMove;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCMove : public Packet {

public :

	// constructor
	GCMove ()
	{
	}

	GCMove ( ObjectID_t objectID , Coord_t x , Coord_t y , Dir_t dir )
		: m_ObjectID(objectID), m_X(x), m_Y(y), m_Dir(dir)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMovePacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szObjectID + szCoord + szCoord + szDir ; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCMove"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set Creature ID 
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t objectID ) { m_ObjectID = objectID; }

	// get/set X
	Coord_t getX () const { return m_X; }
	void setX ( Coord_t x ) { m_X = x; }
	
	// get/set Y
	Coord_t getY () const { return m_Y; }
	void setY ( Coord_t y ) { m_Y = y; }

	// get/set Dir
	Dir_t getDir () const { return m_Dir; }
	void setDir ( Dir_t dir ) { m_Dir = dir; }


private :
	
	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_X;				// X ��ǥ
	Coord_t m_Y;				// Y ��ǥ
	Dir_t m_Dir;				// ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCMoveFactory;
//
// Factory for GCMove
//
//////////////////////////////////////////////////////////////////////

class GCMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCMove(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCMove"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szCoord + szCoord + szDir ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMoveHandler {

public :

	// execute packet's handler
	static void execute ( GCMove * pPacket , Player * pPlayer );

};

#endif
