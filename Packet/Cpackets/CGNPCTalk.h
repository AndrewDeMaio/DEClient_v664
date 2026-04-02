//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCTalk.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_TALK_H__
#define __CG_NPC_TALK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCTalk;
//
//--------------------------------------------------------------------------------

class CGNPCTalk : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_NPC_TALK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGNPCTalk"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCTalkFactory;
//
// Factory for CGNPCTalk
//
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
class CGNPCTalkFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGNPCTalk(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGNPCTalk"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_NPC_TALK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID; }

};

#endif


//--------------------------------------------------------------------------------
//
// class CGNPCTalkHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
class CGNPCTalkHandler {
	
public :

	// execute packet's handler
	static void execute ( CGNPCTalk * pPacket , Player * player );
};
#endif

#endif
