//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_LOGIN_H__
#define __CL_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLLogin;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CLLogin : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_LOGIN; }
	
	// get packet's body size
	size_t getPacketSize () const;// { return szBYTE + m_ID.size() + szBYTE + m_Password.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName () const { return "CLLogin"; }
	
	// get packet's debug string
	std::string toString () const;
#endif

public :

	// get/set player's id
	const std::string& getID () const { return m_ID; }
	void setID ( std::string id ) { m_ID = id; }

	// get/set player's password
	const std::string& getPassword () const { return m_Password; }
	void setPassword ( std::string password ) { m_Password = password; }

	const BYTE* getMacAddress() const { return m_MacAddress; }
	void setMacAddress( const BYTE* macAddress ) { memcpy( m_MacAddress, macAddress, 6 * sizeof(BYTE) ); }

	void SetLoginMode(BYTE n) { m_LoginMode = n;}
private :

	// �÷��̾� ���̵�
	std::string m_ID;

	// �÷��̾� �н�����
	std::string m_Password;

	// Mac address
	BYTE m_MacAddress[6];

	// Login mode
	BYTE m_LoginMode;

};


//////////////////////////////////////////////////////////////////////
//
// class CLLoginFactory;
//
// Factory for CLLogin
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLLogin(); }

	// get packet name
	std::string getPacketName () const { return "CLLogin"; }

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szBYTE + 30 + szBYTE + 20 + 6 + szBYTE; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CLLoginHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLLoginHandler {

	public :

		// execute packet's handler
		static void execute ( CLLogin * pPacket , Player * pPlayer );

	};
#endif

#endif
