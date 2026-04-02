//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCAskAnswer.h 
// Written By  : �輺��
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_ASKANSWER_H__
#define __CG_NPC_ASKANSWER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswer;
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswer : public Packet {

public :
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream );
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_NPC_ASK_ANSWER; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID + szScriptID + szAnswerID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGNPCAskAnswer"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }
	
	ScriptID_t getScriptID() { return m_ScriptID;}
	void setScriptID(ScriptID_t scriptID) { m_ScriptID = scriptID;}
	
	AnswerID_t getAnswerID() { return m_AnswerID;}
	void setAnswerID(AnswerID_t answerID) { m_AnswerID = answerID;}

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
	ScriptID_t m_ScriptID;
	AnswerID_t m_AnswerID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerFactory;
//
// Factory for CGNPCAskAnswer
//
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
class CGNPCAskAnswerFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGNPCAskAnswer(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGNPCAskAnswer"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_NPC_ASK_ANSWER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szScriptID + szAnswerID; }

};

#endif


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
	class CGNPCAskAnswerHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGNPCAskAnswer * pPacket , Player * player );
	};
#endif

#endif
