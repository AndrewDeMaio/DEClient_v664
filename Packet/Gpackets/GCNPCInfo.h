//--------------------------------------------------------------------------------
// 
// Filename    : GCNPCInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_NPC_INFO_H__
#define __GC_NPC_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "EffectInfo.h"
#include "Assert.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"

#define FLAG_PREMIUM_ZONE			0x10	// premium���� ������ ���̴�.
#define FLAG_PREMIUM_PLAY			0x01	// premium play�� �ϴ� ���ΰ�?

//--------------------------------------------------------------------------------
//
// class GCNPCInfo;
//
// Ŭ���̾�Ʈ�� ���� ������ �����ؼ� CGConnect ��Ŷ�� ������, ���� ������ ũ��ó��
// ���� �������� �ε��ؼ� ���� �� �غ� �ϰ� �ȴ�. �״��� PC�� ������ ����,
// �׸��� �� ������ GCNPCInfo�� ��Ƽ� Ŭ���̾�Ʈ�� �����ϰ� �ȴ�.
//
//--------------------------------------------------------------------------------

class GCNPCInfo : public Packet {

public :

	// constructor
	GCNPCInfo();

	// destructor
	~GCNPCInfo();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_NPC_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		std::list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
		for(; itr != m_NPCInfos.end(); itr++)
		{
			NPCInfo* pInfo = *itr;
			size += pInfo->getSize();
		}

		return size;
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCNPCInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif


//--------------------------------------------------
// methods
//--------------------------------------------------
public :
	// get/set npc info
	void addNPCInfo(NPCInfo* pInfo) { m_NPCInfos.push_back(pInfo);}
	NPCInfo* popNPCInfo(void) { if (m_NPCInfos.empty()) return NULL; NPCInfo* pInfo = m_NPCInfos.front(); m_NPCInfos.pop_front(); return pInfo; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :
	// ���� ���� �����ϴ� NPC�鿡 ���� ����
	std::list<NPCInfo*> m_NPCInfos;
};


//--------------------------------------------------------------------------------
//
// class GCNPCInfoFactory;
//
// Factory for GCNPCInfo
//
//--------------------------------------------------------------------------------

class GCNPCInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCNPCInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCNPCInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_NPC_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCNPCInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		size += NPCInfo::getMaxSize()* 255;

		return size;
	}

};



//--------------------------------------------------------------------------------
//
// class GCNPCInfoHandler;
//
//--------------------------------------------------------------------------------

class GCNPCInfoHandler {

public :

	// execute packet's handler
	static void execute(GCNPCInfo* pPacket, Player* pPlayer);

};

#endif
