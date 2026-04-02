//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCWorldList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_WORLD_LIST_H__
#define __LC_WORLD_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WorldInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCWorldList;
//
//////////////////////////////////////////////////////////////////////

class LCWorldList : public Packet {

public:

	// constructor
	// PCInfo* �迭�� ���� NULL�� �����Ѵ�.
	LCWorldList();

	// destructor
	// PCInfo* �迭�� �Ҵ�� ��ü�� �����Ѵ�.
	~LCWorldList();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_WORLD_LIST; }
	
	// get packet's body size
	size_t getPacketSize() const;
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName() const { return "LCWorldList"; }
		
		// get packet's debug std::string
		std::string toString() const;
	#endif
	
public:

	// ���� ����
	WorldID_t getCurrentWorldID() const { return m_CurrentWorldID; }
	void setCurrentWorldID( WorldID_t WorldID ) { m_CurrentWorldID = WorldID; }

    BYTE getListNum() const { return m_WorldInfoList.size(); }

	// add / delete / clear S List
	void addListElement(WorldInfo* pWorldInfo) { m_WorldInfoList.push_back(pWorldInfo); }

	// ClearList
	void clearList() { m_WorldInfoList.clear(); }

	// pop front Element in Status List
	WorldInfo* popFrontListElement()
	{
		WorldInfo* TempWorldInfo = NULL;
		
		if( m_WorldInfoList.size() > 0 ) 
		{ 
			TempWorldInfo = m_WorldInfoList.front(); 
			m_WorldInfoList.pop_front(); 
		}
		
		return TempWorldInfo;
	}

private : 

	// ���� WorldID
	WorldID_t m_CurrentWorldID;

	// ĳ���� ����
	std::list<WorldInfo*> m_WorldInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCWorldListFactory;
//
// Factory for LCWorldList
//
//////////////////////////////////////////////////////////////////////

class LCWorldListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCWorldList(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "LCWorldList"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_WORLD_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const 
	{ 
		// �����̾� ������ �����̾� �������� ����� ũ�� ������,
		// �� ��Ŷ�� �ִ� ũ��� �����̾� 3 ���� ����̴�.
		return szWorldID + WorldInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCWorldListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCWorldListHandler {

public:

	// execute packet's handler
	static void execute(LCWorldList* pPacket, Player* pPlayer);

};

#endif
