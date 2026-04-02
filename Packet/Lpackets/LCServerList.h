//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCServerList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SERVER_LIST_H__
#define __LC_SERVER_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "ServerGroupInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCServerList;
//
//////////////////////////////////////////////////////////////////////

class LCServerList : public Packet {

public:

	// constructor
	// PCInfo* �迭�� ���� NULL�� �����Ѵ�.
	LCServerList();

	// destructor
	// PCInfo* �迭�� �Ҵ�� ��ü�� �����Ѵ�.
	~LCServerList();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_SERVER_LIST; }
	
	// get packet's body size
	size_t getPacketSize() const;
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName() const { return "LCServerList"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif
	
public:

	// ���� ���� �׷�
	ServerGroupID_t getCurrentServerGroupID() const { return m_CurrentServerGroupID; }
	void setCurrentServerGroupID( ServerGroupID_t ServerGroupID ) { m_CurrentServerGroupID = ServerGroupID; }

    BYTE getListNum() const { return m_ServerGroupInfoList.size(); }

	// add / delete / clear S List
	void addListElement(ServerGroupInfo* pServerGroupInfo) { m_ServerGroupInfoList.push_back(pServerGroupInfo); }

	// ClearList
	void clearList() { m_ServerGroupInfoList.clear(); }

	// pop front Element in Status List
	ServerGroupInfo* popFrontListElement()
	{
		ServerGroupInfo* TempServerGroupInfo = m_ServerGroupInfoList.front(); m_ServerGroupInfoList.pop_front(); return TempServerGroupInfo;
	}

private : 

	// ���� ���� �׷�
	ServerGroupID_t m_CurrentServerGroupID;

	// ĳ���� ����
	std::list<ServerGroupInfo*> m_ServerGroupInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCServerListFactory;
//
// Factory for LCServerList
//
//////////////////////////////////////////////////////////////////////

class LCServerListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCServerList(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "LCServerList"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_SERVER_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		// �����̾� ������ �����̾� �������� ����� ũ�� ������,
		// �� ��Ŷ�� �ִ� ũ��� �����̾� 3 ���� ����̴�.
		return szServerGroupID + ServerGroupInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCServerListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCServerListHandler {

public:

	// execute packet's handler
	static void execute(LCServerList* pPacket, Player* pPlayer);

};

#endif
