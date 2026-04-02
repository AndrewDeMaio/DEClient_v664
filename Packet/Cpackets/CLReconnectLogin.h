//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_RECONNECT_LOGIN_H__
#define __CL_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLogin;
//
// Ŭ���̾�Ʈ�� �������� ������ ���� ��Ŷ�̴�.
// ������ �̵��� ���Ǹ�, ���� ������ �� Key �� �� �������� �����ؼ�
// ������ �޴´�. ����, �� �������� ����� ũ��ó ���̵� ��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CLReconnectLogin : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_RECONNECT_LOGIN; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szDWORD+szBYTE; 						// authentication key
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CLReconnectLogin"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set key
	DWORD getKey () const { return m_Key; }
	void setKey ( DWORD key ) { m_Key = key; }

	void SetLoginMode(BYTE n) { m_LoginMode = n;}
	BYTE GetLoginMode() { return m_LoginMode;}
private :
	
	// authentication key
	DWORD m_Key;
	// Login mode
	BYTE m_LoginMode;

};


//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginFactory;
//
// Factory for CLReconnectLogin
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLReconnectLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLReconnectLogin(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CLReconnectLogin"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_RECONNECT_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const
	{ 
		return szDWORD+szBYTE; 			// authentication key
	}

};

#endif

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLReconnectLoginHandler {

	public :

		// execute packet's handler
		static void execute ( CLReconnectLogin * pPacket , Player * pPlayer );

	};
#endif

#endif
