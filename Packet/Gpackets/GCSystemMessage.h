//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSystemMessage.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SYSTEM_MESSAGE_H__
#define __GC_SYSTEM_MESSAGE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


enum SystemMessageType
{
	SYSTEM_MESSAGE_NORMAL = 0,
	SYSTEM_MESSAGE_OPERATOR,	// ��� ����
	SYSTEM_MESSAGE_MASTER_LAIR,	// ������ ���� ����
	SYSTEM_MESSAGE_COMBAT,		// ���� ����
	SYSTEM_MESSAGE_INFO, 		// Ư���� ���� ����
	SYSTEM_MESSAGE_HOLY_LAND,	// �ƴ��� ���� ����
	SYSTEM_MESSAGE_RANGER_CHAT,	// �������� ������ ê
	SYSTEM_MESSAGE_TIMER,		// Ÿ�̸� �������̽� ���
	SYSTEM_MESSAGE_EVENT,		// OX���� ������ �̺�Ʈ �޼��� ����ó�� - ȭ�� �߻�ܿ� ũ��~~ ���.. �� ���ڳ� �α׾ƿ�, �� �̵� �ϱ� �������� ������.

	SYSTEM_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessage;
//
// ���� ������ Ư�� �÷��̾��� SystemMessage �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� SystemMessage ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessage : public Packet {

public :
	GCSystemMessage() 
	: m_Color(0x006040E8), m_Type(SYSTEM_MESSAGE_NORMAL)
	{
	}
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SYSTEM_MESSAGE; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Message.size() + szuint + szBYTE; }

	// get packet name
	std::string getPacketName() const { return "GCSystemMessage"; }
	
	// get packet's debug std::string
	std::string toString() const;

	// get/set chatting message
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }

	// get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	SystemMessageType getType() const { return m_Type; }
	void setType( SystemMessageType Type ) { m_Type = Type; }


	

private :
	
	// chatting message
	std::string m_Message;

	// text color
	uint m_Color;
	
	SystemMessageType m_Type;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageFactory;
//
// Factory for GCSystemMessage
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCSystemMessage(); }

	// get packet name
	std::string getPacketName() const { return "GCSystemMessage"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SYSTEM_MESSAGE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 256 + szuint + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSystemMessage* pPacket, Player* pPlayer);

};

#endif
