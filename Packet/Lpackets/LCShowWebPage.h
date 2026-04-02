//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCShowWebPage.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SHOW_WEB_PAGE_H__
#define __LC_SHOW_WEB_PAGE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCShowWebPage;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCShowWebPage : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_SHOW_WEB_PAGE; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCShowWebPagePacketSize �� ����, �����϶�.
	size_t getPacketSize() const { return szBYTE + m_Message.size() + szBYTE + m_URL.size(); }
	
	// get packet's name
	string getPacketName() const { return "LCShowWebPage"; }

	// get / set message
	const string& getMessage() const { return m_Message; }
	void setMessage( const string& message ) { m_Message = message; }
	
	// get / set url
	const string& getURL() const { return m_URL; }
	void setURL( const string& url ) { m_URL = url; }
	
	// get packet's debug string
	string toString() const;

private:
	string m_Message;
	string m_URL;
};


//////////////////////////////////////////////////////////////////////
//
// class LCShowWebPageFactory;
//
// Factory for LCShowWebPage
//
//////////////////////////////////////////////////////////////////////

class LCShowWebPageFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCShowWebPage(); }

	// get packet name
	string getPacketName() const { return "LCShowWebPage"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_SHOW_WEB_PAGE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const { return szBYTE + 128 + szBYTE + 128; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCShowWebPageHandler;
//
//////////////////////////////////////////////////////////////////////

class LCShowWebPageHandler {

public:

	// execute packet's handler
	static void execute(LCShowWebPage* pPacket, Player* pPlayer);

};

#endif
