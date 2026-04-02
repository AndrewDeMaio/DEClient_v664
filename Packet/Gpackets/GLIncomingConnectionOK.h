//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLIncomingConnectionOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GL_INCOMING_CONNECTION_OK_H__
#define __GL_INCOMING_CONNECTION_OK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOK;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOK : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Datagram & iDatagram );
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( Datagram & oDatagram ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GL_INCOMING_CONNECTION_OK; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szBYTE + m_PlayerID.size() 
				+ szuint
				+ szDWORD; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GLIncomingConnectionOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set player id
	const std::string& getPlayerID () const { return m_PlayerID; }
	void setPlayerID ( std::string playerID ) { m_PlayerID = playerID; }

	// get/set tcp port
	uint getTCPPort () const { return m_TCPPort; }
	void setTCPPort ( uint tcpPort ) { m_TCPPort = tcpPort; }

	// get/set auth key
	DWORD getKey () const { return m_Key; }
	void setKey ( DWORD key ) { m_Key = key; }

private :

	// � �÷��̾�� LCReconnect ��Ŷ�� ������ �ϴ����� �˾ƾ� �Ѵ�.
	std::string m_PlayerID;

	// ���� ������ �ڽ��� TCP ��Ʈ�� �˷������ν� 
	// �α��� ������ ���� ������ TCP ��Ʈ�� ���� �����ϴ�.
	uint m_TCPPort;

	// ���� �������� ������ ���� Ű
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOKFactory;
//
// Factory for GLIncomingConnectionOK
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GLIncomingConnectionOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GLIncomingConnectionOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GL_INCOMING_CONNECTION_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLIncomingConnectionOKPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szBYTE + 20
				+ szuint
				+ szDWORD; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GLIncomingConnectionOK * pPacket );

};

#endif
