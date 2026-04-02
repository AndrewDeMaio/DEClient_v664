//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_H__
#define __GC_RECONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnect;
//
// ������ �̵���, ���� ������ Ŭ���̾�Ʈ���� ���� ������ �����϶�� 
// �ϸ鼭 ������ ������ �ϴ� ��Ŷ�̴�. Ŭ���̾�Ʈ�� �� ��Ŷ�� ������,
// �������� ������ ���� ��Ŷ�� ��� ������ IP/Port �� �����ϸ� �ȴ�.
//
//////////////////////////////////////////////////////////////////////

class GCReconnect : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RECONNECT; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szBYTE + m_Name.size() 		// ĳ���� �̸�
			+ szPCType 						// �����̾� or �����̾�?
			+ szBYTE + m_ServerIP.size() 	// ���� ������ ���� ���� IP
			+ szDWORD; 						// ���� Ű
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReconnect"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set creature name
	const std::string& getName () const { return m_Name; }
	void setName ( const std::string & name ) { m_Name = name; }

	// get/set pc type
	PCType getPCType () const { return m_PCType; }
	void setPCType ( PCType pcType ) { m_PCType = pcType; }

	// get/set server ip
	const std::string& getServerIP () const { return m_ServerIP; }
	void setServerIP ( const std::string & serverIP ) { m_ServerIP = serverIP; }

	// get/set key
	DWORD getKey () const { return m_Key; }
	void setKey ( DWORD key ) { m_Key = key; }

private :
	
	// creature name
	std::string m_Name;

	// pc type
	PCType m_PCType;
	
	// New Server IP
	std::string m_ServerIP;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectFactory;
//
// Factory for GCReconnect
//
//////////////////////////////////////////////////////////////////////

class GCReconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCReconnect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReconnect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RECONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const
	{
		return szBYTE + 20 		 		// ĳ���� �̸�
			+ szPCType 					// �����̾� or �����̾�?
			+ szBYTE + 15			 	// ���� ������ ���� ���� IP
			+ szDWORD; 					// ���� Ű
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectHandler {

public :

	// execute packet's handler
	static void execute ( GCReconnect * pPacket , Player * pPlayer );

};

#endif
