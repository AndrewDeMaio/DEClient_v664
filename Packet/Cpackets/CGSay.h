//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSay.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SAY_H__
#define __CG_SAY_H__

// include files

//#ifdef __GAME_SERVER__
//#include "GamePlayer.h"
//#endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSay;
//
// Ŭ���̾�Ʈ�� �������� ������ Say ��Ŷ�̴�.
// ���ο� Say String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class Player;
class Creature;
class GamePlayer;

class CGSay : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_SAY; }
	
	// get packet's body size
	size_t getPacketSize() const { return szuint + szBYTE + m_Message.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGSay"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	// get/set chatting message
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }
	

private :
	
	// text color
	uint m_Color;

	// chatting message
	std::string m_Message;
	
};


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGSayFactory;
//
// Factory for CGSay
//
//////////////////////////////////////////////////////////////////////

class CGSayFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGSay(); }

	// get packet name
	std::string getPacketName() const { return "CGSay"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_SAY; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const { return szuint + szBYTE + 128; }

};
#endif


#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGSayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSayHandler {

public:

	// execute packet's handler
	static void execute(CGSay* pPacket, Player* pPlayer);

#ifdef __GAME_SERVER__

	static void opExecute( Creature* pCreature, GamePlayer* pPlayer, std::string msg, int i );

	// for guild test
	static void opzone( std::string msg, int i );
	static void opguild( std::string msg, int i );

	// ���� �ý��� ���� 
	static void opcombat( GamePlayer* pPlayer, std::string msg, int i );

	// set �̺�Ʈ ������ Ȯ��
	static void opset( GamePlayer* pPlayer, std::string msg, int i );

	static void opview( GamePlayer* pPlayer, std::string msg, int i );

	// save
	static void opsave(GamePlayer* pPlayer, std::string msg, int i);

	// wall
	static void opwall(GamePlayer* pPlayer, std::string msg, int i);

	// Shutdown
	static void opshutdown(GamePlayer* pPlayer, std::string msg, int i);

	// kick
	static void opkick(GamePlayer* pPlayer, std::string msg, int i);

	// mute
	static void opmute(GamePlayer* pPlayer, std::string msg, int i);

	// freezing
	static void opfreezing(GamePlayer* pPlayer, std::string msg, int i);

	// deny
	static void opdeny(GamePlayer* pPlayer, std::string msg, int i);

	// info
	static void opinfo(GamePlayer* pPlayer, std::string msg, int i);

	// trace
	static void optrace(GamePlayer* pPlayer, std::string msg, int i);

	// warp
	static void opwarp(GamePlayer* pPlayer, std::string msg, int i);

	// create
	static void opcreate(GamePlayer* pPlayer, std::string msg, int i);

	// grant
	static void opgrant(GamePlayer* pPlayer, std::string msg, int i);

	// recall
	static void oprecall(GamePlayer* pPlayer, std::string msg, int i);

	// mrecall
	static void opmrecall(GamePlayer* pPlayer, std::string msg, int i);

	// user
	static void opuser(GamePlayer* pPlayer, std::string msg, int i);

	// summon
	static void opsummon(GamePlayer* pPlayer, std::string msg, int i);

	// notice 
	static void opnotice(GamePlayer* pPlayer, std::string msg, int i);

	// pay 
	static void oppay(GamePlayer* pPlayer, std::string msg, int i);

	// world 
	static void opworld(GamePlayer* pPlayer, std::string msg, int i, bool bSameWorldOnly);

	// command 
	static void opcommand(GamePlayer* pPlayer, std::string msg, int i);
#endif

};
#endif

#endif
