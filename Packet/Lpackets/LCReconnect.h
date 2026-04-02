//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCReconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_RECONNECT_H__
#define __LC_RECONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCReconnect;
//
// �α��� �������� ������ �ް�, ĳ���͸� ������ Ŭ���̾�Ʈ�� ���,
// ĳ���Ͱ� ���� ���ῡ �����ߴ� ���� �˾Ƴ���, �� ���� �����ϴ�
// ���� ������ �������϶�� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCReconnect : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LC_RECONNECT; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szBYTE + m_GameServerIP.size() 	// ���� ���� ������
			+ szuint							// ���� ���� ��Ʈ
			+ szDWORD; 							// ���� Ű
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCReconnect"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set game server's ip
	const std::string& getGameServerIP () const { return m_GameServerIP; }
	void setGameServerIP ( const std::string & ip ) { m_GameServerIP = ip; }

	// get/set game server's port
	uint getGameServerPort () const { return m_GameServerPort; }
	void setGameServerPort ( uint port ) { m_GameServerPort = port; }

	// get/set key
	DWORD getKey () const { return m_Key; }
	void setKey ( DWORD key ) { m_Key = key; }

private :
	
	// New GameServer's IP
	std::string m_GameServerIP;

	// New GameServer's TCP Port
	uint m_GameServerPort;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class LCReconnectFactory;
//
// Factory for LCReconnect
//
//////////////////////////////////////////////////////////////////////

class LCReconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LCReconnect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LCReconnect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LC_RECONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LCReconnectPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szBYTE + 15 	// ���� ���� ������
			+ szuint		// ���� ���� ��Ʈ
			+ szDWORD; 		// ���� Ű
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCReconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class LCReconnectHandler {

public :

	// execute packet's handler
	static void execute ( LCReconnect * pPacket , Player * pPlayer );

};

#endif
