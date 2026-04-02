//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_LOGIN_H__
#define __GC_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLogin;
//
// �α��� �������� ������ �ް�, ĳ���͸� ������ Ŭ���̾�Ʈ�� ���,
// ĳ���Ͱ� ���� ���ῡ �����ߴ� ���� �˾Ƴ���, �� ���� �����ϴ�
// ���� ������ �������϶�� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLogin : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RECONNECT_LOGIN; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szBYTE + m_LoginServerIP.size() 	// ���� ���� ������
			+ szuint							// ���� ���� ��Ʈ
			+ szDWORD; 							// ���� Ű
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReconnectLogin"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set game server's ip
	const std::string& getLoginServerIP () const { return m_LoginServerIP; }
	void setLoginServerIP ( const std::string & ip ) { m_LoginServerIP = ip; }

	// get/set game server's port
	uint getLoginServerPort () const { return m_LoginServerPort; }
	void setLoginServerPort ( uint port ) { m_LoginServerPort = port; }

	// get/set key
	DWORD getKey () const { return m_Key; }
	void setKey ( DWORD key ) { m_Key = key; }

private :
	
	// New LoginServer's IP
	std::string m_LoginServerIP;

	// New LoginServer's TCP Port
	uint m_LoginServerPort;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginFactory;
//
// Factory for GCReconnectLogin
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCReconnectLogin(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReconnectLogin"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RECONNECT_LOGIN; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectLoginPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szBYTE + 15 	// ���� ���� ������
			+ szuint		// ���� ���� ��Ʈ
			+ szDWORD; 		// ���� Ű
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginHandler {

public :

	// execute packet's handler
	static void execute ( GCReconnectLogin * pPacket , Player * pPlayer );

};

#endif
