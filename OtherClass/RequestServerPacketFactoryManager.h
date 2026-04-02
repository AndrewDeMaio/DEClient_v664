//////////////////////////////////////////////////////////////////////
// 
// Filename    : RequestServerPacketFactoryManager.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __REQUEST_SERVER_PACKET_FACTORY_MANAGER_H__
#define __REQUEST_SERVER_PACKET_FACTORY_MANAGER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class RequestServerPacketFactoryManager
//
//////////////////////////////////////////////////////////////////////

class RequestServerPacketFactoryManager {

public :
	
	// constructor
	RequestServerPacketFactoryManager ();
	
	// destructor
	~RequestServerPacketFactoryManager ();

	// ��Ŷ���丮�Ŵ����� �ʱ�ȭ�Ѵ�.
	// ���Ӽ�����ü�� init()���� ȣ��ȴ�.
	void init ();
	
	// ���丮 ��ü�� Ư�� �ε����� �߰��Ѵ�.
	void addFactory ( PacketFactory * pFactory );
	
	// ��Ŷ���̵�� ��Ŷ��ü�� �����Ѵ�.
	Packet * createPacket ( PacketID_t packetID );

	#ifdef	__DEBUG_OUTPUT__
		// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
		std::string getPacketName ( PacketID_t packetID );

		// get debug string
		std::string toString () const;
	#endif

	// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
	PacketSize_t getPacketMaxSize ( PacketID_t packetID );

	

private :
	
	// ��Ŷ���丮�� �迭
	PacketFactory ** m_Factories;
	
	// ��Ŷ���丮�迭�� ũ��
	ushort m_Size;

};

extern RequestServerPacketFactoryManager * g_pRequestServerPacketFactoryManager;

#endif
