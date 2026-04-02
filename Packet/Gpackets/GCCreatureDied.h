//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCreatureDied.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CREATURE_DIED_H__
#define __GC_CREATURE_DIED_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDied;
//
// ���� ������ Ư�� �÷��̾��� CreatureDied �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� CreatureDied ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDied : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_CREATURE_DIED; }
	
	// get packet's body size
	size_t getPacketSize () const { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCCreatureDied"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set dead creature's creature id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( const ObjectID_t & creatureID ) { m_ObjectID = creatureID; }
	

private :
	
	// dead creature's creature id
	ObjectID_t m_ObjectID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDiedFactory;
//
// Factory for GCCreatureDied
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDiedFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCCreatureDied(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCCreatureDied"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_CREATURE_DIED; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCCreatureDiedPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCreatureDiedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCCreatureDiedHandler {
	
public :
	
	// execute packet's handler
	static void execute ( GCCreatureDied * pPacket , Player * pPlayer );

};

#endif
