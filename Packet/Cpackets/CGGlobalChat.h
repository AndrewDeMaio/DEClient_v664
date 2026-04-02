//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGlobalChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GLOBAL_CHAT_H__
#define __CG_GLOBAL_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChat;
//
// Ŭ���̾�Ʈ�� �������� ������ GlobalChat ��Ŷ�̴�.
// ���ο� GlobalChat String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChat : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_GLOBAL_CHAT; }
	
	// get packet's body size
	size_t getPacketSize() const { return szuint + szBYTE + m_Message.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGGlobalChat"; }
	
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
// class CGGlobalChatFactory;
//
// Factory for CGGlobalChat
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGGlobalChat(); }

	// get packet name
	std::string getPacketName() const { return "CGGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_GLOBAL_CHAT; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const { return szuint + szBYTE + 128; }

};
#endif


#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatHandler {

public:

	// execute packet's handler
	static void execute(CGGlobalChat* pPacket, Player* pPlayer);

};
#endif

#endif
