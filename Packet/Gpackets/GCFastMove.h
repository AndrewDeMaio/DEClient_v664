//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFastMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FAST_MOVE_H__
#define __GC_FAST_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFastMove;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCFastMove : public Packet {

public :

	// constructor
	GCFastMove ()
	{
	}

	GCFastMove ( ObjectID_t objectID , Coord_t x , Coord_t y , Coord_t x2, Coord_t y2)
		: m_ObjectID(objectID), m_FromX(x), m_FromY(y), m_ToX(x2), m_ToY(y2)
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
	PacketID_t getPacketID () const { return PACKET_GC_FAST_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCFastMovePacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szObjectID + 4*szCoord + szSkillType; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCFastMove"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set Creature ID 
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t objectID ) { m_ObjectID = objectID; }

	void setXY( Coord_t x, Coord_t y, Coord_t x2, Coord_t y2)
	{
		m_FromX = x; m_FromY = y; m_ToX = x2; m_ToY = y2;
	}

	// get
	Coord_t getFromX () const { return m_FromX; }
	Coord_t getFromY () const { return m_FromY; }
	Coord_t getToX () const { return m_ToX; }
	Coord_t getToY () const { return m_ToY; }
	
	void setSkillType( SkillType_t skillType ) { m_SkillType = skillType; }
	SkillType_t getSkillType() const { return m_SkillType; }


private :
	
	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_FromX,m_FromY, m_ToX, m_ToY;				// �����ǥ, ������ǥ 
	SkillType_t m_SkillType;	// ����� ��ų Ÿ��
};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveFactory;
//
// Factory for GCFastMove
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCFastMove(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCFastMove"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_FAST_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCFastMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + 4*szCoord + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveHandler {

public :

	// execute packet's handler
	static void execute ( GCFastMove * pPacket , Player * pPlayer );

};

#endif
