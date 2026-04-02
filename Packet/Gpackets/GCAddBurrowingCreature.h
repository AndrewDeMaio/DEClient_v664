//--------------------------------------------------------------------------------
// 
// Filename    : GCAddBurrowingCreature.h 
// Written By  : crazydog 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_BURROWING_CREATURE_H__
#define __GC_ADD_BURROWING_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCAddBurrowingCreature;
//
// �þ� �ȿ� BurrowingCreature �� ������ ���, �� ��Ŷ�� BurrowingCreature ������ ��Ƽ� ���۹޴´�.
//
//--------------------------------------------------------------------------------

class GCAddBurrowingCreature : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_BURROWING_CREATURE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddBurrowingCreaturePacketSize �� ����, �����϶�.
	size_t getPacketSize () const 
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() 
			+ szCoord + szCoord; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddBurrowingCreature"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif	


public :

	// get/set object id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) { m_ObjectID = creatureID; }

	// get/set name
	const std::string& getName () const { return m_Name; }
	void setName ( std::string name ) { m_Name = name; }


	// get/set X
	Coord_t getX () const { return m_X; }
	void setX ( Coord_t x ) { m_X = x; }
	
	// get/set Y
	Coord_t getY () const { return m_Y; }
	void setY ( Coord_t y ) { m_Y = y; }



private :
	
    // �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
    ObjectID_t m_ObjectID;

    // BurrowingCreature�� �̸�
    std::string m_Name;

   	Coord_t m_X;				// X ��ǥ
	Coord_t m_Y;				// Y ��ǥ
};


//////////////////////////////////////////////////////////////////////
//
// class GCAddBurrowingCreatureFactory;
//
// Factory for GCAddBurrowingCreature
//
//////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddBurrowingCreature(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddBurrowingCreature"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_BURROWING_CREATURE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddBurrowingCreaturePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{
		int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
		localLongName = 12;
#endif //__LOCALIZING_LONGNAME
		return szObjectID 
			+ szBYTE + 20 + localLongName
			+ szCoord + szCoord; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddBurrowingCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureHandler {

public :

	// execute packet's handler
	static void execute ( GCAddBurrowingCreature * pPacket , Player * pPlayer );

};

#endif
