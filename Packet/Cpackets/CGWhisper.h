//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGWhisper.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_WHISPER_H__
#define __CG_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGWhisper;
//
// Ŭ���̾�Ʈ�� �������� ������ Whisper ��Ŷ�̴�.
// ���ο� Whisper String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGWhisper : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_WHISPER; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Name.size() + szuint + szBYTE + m_Message.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGWhisper"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set Name
	const std::string& getName() const { return m_Name; }
	void setName(const std::string & Name) { m_Name = Name; }

	// get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	// get/set chatting message
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }
	

private :

	std::string m_Name;
	
	// text color
	uint m_Color;

	// chatting message
	std::string m_Message;
	
};


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGWhisperFactory;
//
// Factory for CGWhisper
//
//////////////////////////////////////////////////////////////////////

class CGWhisperFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new CGWhisper(); }

	// get packet name
	std::string getPacketName() const { return "CGWhisper"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_WHISPER; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 10 + szuint + szBYTE + 128; }

};
#endif


#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class CGWhisperHandler {

public:

	// execute packet's handler
	static void execute(CGWhisper* pPacket, Player* pPlayer);

};
#endif


#endif
