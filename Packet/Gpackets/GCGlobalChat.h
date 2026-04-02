//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGlobalChat.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GLOBAL_CHAT_H__
#define __GC_GLOBAL_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChat;
//
// ���� ������ Ư�� �÷��̾��� GlobalChat �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� GlobalChat ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChat : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_GLOBAL_CHAT; }
	
	// get packet's body size
	size_t getPacketSize() const { return szuint + szBYTE + m_Message.size() + szBYTE; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCGlobalChat"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	//get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	// get/set chatting message
	std::string getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }

	// get/set chatting message
	Race_t getRace() const { return m_Race; }
	void setRace(Race_t race) { m_Race = race; }
	

private :
	
	// chatting message
	std::string m_Message;

	// text color
	uint m_Color;

	// race
	Race_t m_Race;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChatFactory;
//
// Factory for GCGlobalChat
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChatFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCGlobalChat(); }

	// get packet name
	std::string getPacketName() const { return "GCGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_GLOBAL_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCGlobalChatPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szuint + szBYTE + 128 + szBYTE ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChatHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGlobalChat* pPacket, Player* pPlayer);

};

#endif
