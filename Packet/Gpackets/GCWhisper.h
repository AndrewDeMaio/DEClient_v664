//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWhisper.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_WHISPER_H__
#define __GC_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCWhisper;
//
// ���� ������ Ư�� �÷��̾��� Whisper �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� Whisper ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCWhisper : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_WHISPER; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Name.size() + szuint + szBYTE + m_Message.size() + szBYTE; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCWhisper"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set sender's creature id
	const std::string& getName() const { return m_Name ; }
	void setName(const std::string & Name) { m_Name = Name ; }

	//get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	// get/set chatting message
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }
	
	// get/set chatting message
	Race_t getRace() const { return m_Race; }
	void setRace(Race_t race) { m_Race = race; }

private :
	
	// character's creature Name
	std::string m_Name;
	
	// text color
	uint m_Color;

	// chatting message
	std::string m_Message;

	// Race
	Race_t m_Race;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFactory;
//
// Factory for GCWhisper
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCWhisper(); }

	// get packet name
	std::string getPacketName() const { return "GCWhisper"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_WHISPER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCWhisperPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 10 + szuint + szBYTE + 128 + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class GCWhisperHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCWhisper* pPacket, Player* pPlayer);

};

#endif
