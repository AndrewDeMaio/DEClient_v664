//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddEffectToTile.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_TO_TILE_H__
#define __GC_ADD_EFFECT_TO_TILE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAddEffectToTile;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAddEffectToTile : public Packet {

public :
	
	// constructor
	GCAddEffectToTile ();
	
	// destructor
	~GCAddEffectToTile ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_EFFECT_TO_TILE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + szCoord*2 + szEffectID + szTurn; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddEffectToTile"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set EffectID 
	EffectID_t getEffectID() const { return m_EffectID; }
	void setEffectID( EffectID_t e ) { m_EffectID = e; }
	

	// get / set Duration 
	Turn_t getDuration() const { return m_Duration; }
	void setDuration( Turn_t d ) { m_Duration = d; }

	// get / set ObjectID 
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t d ) { m_ObjectID = d; }

	// get & set X, Y
	Coord_t getX() const { return m_X;}
	Coord_t getY() const { return m_Y;}
	void setXY( Coord_t x, Coord_t y) { m_X = x; m_Y = y;}
	
private :
	
	Coord_t  m_X, m_Y;
	ObjectID_t m_ObjectID;

	EffectID_t	m_EffectID;
	Turn_t		m_Duration;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddEffectToTileFactory;
//
// Factory for GCAddEffectToTile
//
//////////////////////////////////////////////////////////////////////

class GCAddEffectToTileFactory : public PacketFactory {

public :
	
	// constructor
	GCAddEffectToTileFactory () {}
	
	// destructor
	virtual ~GCAddEffectToTileFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCAddEffectToTile(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddEffectToTile"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_EFFECT_TO_TILE; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize() const { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE * m_ListNum * 2 ; }
	PacketSize_t getPacketMaxSize() const { return szObjectID + szCoord*2 + szEffectID + szTurn; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddEffectToTileHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddEffectToTileHandler {

public :

	// execute packet's handler
	static void execute ( GCAddEffectToTile * pGCAddEffectToTile , Player * pPlayer );

};

#endif
