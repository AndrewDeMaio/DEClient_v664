//----------------------------------------------------------------------
// 
// Filename    : LGIncomingConnection.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __LG_INCOMING_CONNECTION_H__
#define __LG_INCOMING_CONNECTION_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class LGIncomingConnection;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ���������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class LGIncomingConnection : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Datagram & iDatagram );
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( Datagram & oDatagram ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_LG_INCOMING_CONNECTION; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return + szBYTE + m_PlayerID.size()	// Player ID
			+ szBYTE + m_PCName.size() 		// PC name
			+ szBYTE + m_ClientIP.size(); 	// client ip
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LGIncomingConnection"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set playerID
	const std::string& getPlayerID () const { return m_PlayerID; }
	void setPlayerID ( std::string playerID ) { m_PlayerID = playerID; }
	
	// get/set pcName
	const std::string& getPCName () const { return m_PCName; }
	void setPCName ( std::string pcName ) { m_PCName = pcName; }
	
	// get/set client ip
	const std::string& getClientIP () const { return m_ClientIP; }
	void setClientIP ( std::string ip ) { m_ClientIP = ip; }
	
private :

	// Player ID
	std::string m_PlayerID;

	// PC name
	std::string m_PCName;

	// Ŭ���̾�Ʈ�� IP
	std::string m_ClientIP;

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionFactory;
//
// Factory for LGIncomingConnection
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new LGIncomingConnection(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "LGIncomingConnection"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_LG_INCOMING_CONNECTION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return + szBYTE + 20 	// creature name
			+ szBYTE + 20 		// PC name
			+ szBYTE + 15; 		// client ip
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionHandler {
	
public :

	// execute packet's handler
	static void execute ( LGIncomingConnection * pPacket );

};

#endif
