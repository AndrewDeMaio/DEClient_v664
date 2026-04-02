//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSubmitScore 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SUBMIT_SCORE_H__
#define __CG_SUBMIT_SCORE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"



//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScore;
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScore : public Packet {

public:
	
	// constructor
	CGSubmitScore();
	
	// destructor
	~CGSubmitScore();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_SUBMIT_SCORE; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + szBYTE + szWORD; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGSubmitScore"; }
	
	// get packet's debug string
	std::string toString() const;
#endif

public:
	BYTE	getGameType() const { return m_GameType; }
	void	setGameType(BYTE type) { m_GameType = type; }

	BYTE	getLevel() const { return m_Level; }
	void	setLevel(BYTE level) { m_Level = level; }

	WORD	getScore() const { return m_Score; }
	void	setScore(WORD score) { m_Score = score; }
private :
	BYTE	m_GameType;
	BYTE	m_Level;
	WORD	m_Score;
};


//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScoreFactory;
//
// Factory for CGSubmitScore
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScoreFactory : public PacketFactory {

public:
	
	// constructor
	CGSubmitScoreFactory() {}
	
	// destructor
	virtual ~CGSubmitScoreFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGSubmitScore(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGSubmitScore"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_SUBMIT_SCORE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szBYTE + szBYTE + szWORD; }

};

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScoreHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScoreHandler {
	
public:

	// execute packet's handler
	static void execute(CGSubmitScore* pCGSubmitScore, Player* player);
};
#endif

#endif
