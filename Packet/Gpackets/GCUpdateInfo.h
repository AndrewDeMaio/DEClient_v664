//--------------------------------------------------------------------------------
// 
// Filename    : GCUpdateInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_UPDATE_INFO_H__
#define __GC_UPDATE_INFO_H__

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
#include "NicknameInfo.h"
#include "BloodBibleSignInfo.h"
#include "InstanceDoungeonInfo.h"


#define FLAG_PREMIUM_ZONE			0x10	// premium���� ������ ���̴�.
#define FLAG_PREMIUM_PLAY			0x01	// premium play�� �ϴ� ���ΰ�?

//--------------------------------------------------------------------------------
//
// class GCUpdateInfo;
//
// Ŭ���̾�Ʈ�� ���� ������ �����ؼ� CGConnect ��Ŷ�� ������, ���� ������ ũ��ó��
// ���� �������� �ε��ؼ� ���� �� �غ� �ϰ� �ȴ�. �״��� PC�� ������ ����,
// �׸��� �� ������ GCUpdateInfo�� ��Ƽ� Ŭ���̾�Ʈ�� �����ϰ� �ȴ�.
//
//--------------------------------------------------------------------------------

class GCUpdateInfo : public Packet {

public :

	// constructor
	GCUpdateInfo();

	// destructor
	~GCUpdateInfo();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_UPDATE_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const 
	{ 
		// [PCType][PCInfo]
		// [GameTime][Weather][WeatherLevel][DarkLevel][LightLevel]
		// [#NPCTypes][NPCType1]...[NPCTypeN]
		// [#MonsterTypes][MonsterType1]...[MonsterTypeM]
		PacketSize_t size = 0;

		WORD MotorcycleSize = 0;
		if(m_hasMotorcycle) 
		{
			MotorcycleSize = m_pRideMotorcycleInfo->getSize();
		}

		size += szBYTE;
		size += m_pPCInfo->getSize();
		size += m_pInventoryInfo->getSize();
		size += m_pGearInfo->getSize();
		size += m_pExtraInfo->getSize();
		size += szBYTE;
		size += MotorcycleSize;
		size += m_pEffectInfo->getSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += m_GameTime.getSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* m_nNPCs;
		size += szBYTE;
		size += szMonsterType* m_nMonsters;

		size += szBYTE;
		std::list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
		for(; itr != m_NPCInfos.end(); itr++)
		{
			NPCInfo* pInfo = *itr;
			size += pInfo->getSize();
		}
		// ���� ����
		size += szBYTE;
		// �����̾�
		size += szBYTE;
			// SMS
		size += szDWORD;
		// �г���
		size += m_pNicknameInfo->getSize();

		size += szBYTE; // non pk ����
		
		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		// blood bible ����
		size += m_pBloodBibleSign->getSize();

		// power jjang point
		size += sizeof(uint);

#if __CONTENTS(__TIPOJYU_CASTLE) // GCUpdateInfoFactory	��Ŷ ���� ����		
		size += m_pInstanceDoungeonInfo->getSize();
#endif // __TIPOJYU_CASTLE

		return size;
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCUpdateInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif


//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get/set PC info
	PCInfo* getPCInfo() const { return m_pPCInfo; }
	void setPCInfo(PCInfo* pPCInfo) { m_pPCInfo = pPCInfo; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo() const { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo) { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo() const { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo) { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo() const { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo) { m_pExtraInfo = pExtraInfo; }

	// get/set EffectInfo
	EffectInfo* getEffectInfo() const { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) { m_pEffectInfo = pEffectInfo; }

	// get/set hasMotorcycle
	bool hasMotorcycle() const { return m_hasMotorcycle; }

	// get/set RideMotorcycleInfo
	RideMotorcycleInfo* getRideMotorcycleInfo() const { return m_pRideMotorcycleInfo; }
	void setRideMotorcycleInfo(RideMotorcycleInfo* pRideMotorcycleInfo) {
		m_pRideMotorcycleInfo = pRideMotorcycleInfo;
		m_hasMotorcycle = true; }

#if __CONTENTS(__TIPOJYU_CASTLE) // GCUpdateInfoFactory	��Ŷ ���� ����
	InstanceDoungeonInfo* getInstanceDoungeonInfo() const { return m_pInstanceDoungeonInfo; }
	void SetInstanceDoungeonInfo(InstanceDoungeonInfo* pInstanceDoungeonInfo) { m_pInstanceDoungeonInfo = pInstanceDoungeonInfo; }
#endif // __TIPOJYU_CASTLE

	// get/set ZoneID
	ZoneID_t getZoneID() const { return m_ZoneID; }
	void setZoneID(const ZoneID_t & zoneID) { m_ZoneID = zoneID; }

	// get / set ZoneX
	Coord_t getZoneX() const { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) { m_ZoneX = ZoneX; }

	// get / set ZoneY
	Coord_t getZoneY() const { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) { m_ZoneY = ZoneY; }

	// get/set GameTime
	GameTime getGameTime() const { return m_GameTime; }
	void setGameTime(const GameTime & gameTime) { m_GameTime = gameTime; }

	// get/set weather
	Weather getWeather() const { return m_Weather; }
	void setWeather(Weather weather) { m_Weather = weather; }

	// get/set weather level
	WeatherLevel_t getWeatherLevel() const { return m_WeatherLevel; }
	void setWeatherLevel(WeatherLevel_t weatherLevel) { m_WeatherLevel = weatherLevel; }

	// get/set darklevel
	DarkLevel_t getDarkLevel() const { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) { m_DarkLevel = darkLevel; }

	// get/set lightlevel
	LightLevel_t getLightLevel() const { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) { m_LightLevel = lightLevel; }

	// get/set # of NPC
	uint getNPCCount() const { return m_nNPCs; }
	void setNPCCount(uint n) { Assert(n <= maxNPCPerZone); m_nNPCs = n; }

	// get/set NPC type
	NPCType_t getNPCType(uint n) const { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType) { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	// get/set # of monster
	uint getMonsterCount() const { return m_nMonsters; }
	void setMonsterCount(uint n) { Assert(n <= maxMonsterPerZone); m_nMonsters = n; }

	// get/set Monster type
	MonsterType_t getMonsterType(uint n) const { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType) { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	// get/set npc info
	void addNPCInfo(NPCInfo* pInfo) { m_NPCInfos.push_back(pInfo);}
	NPCInfo* popNPCInfo(void) { if (m_NPCInfos.empty()) return NULL; NPCInfo* pInfo = m_NPCInfos.front(); m_NPCInfos.pop_front(); return pInfo; }

	// get/set ServerStat
	void setServerStat( BYTE ServerStat ) { m_ServerStat = ServerStat; }
	BYTE getServerStat() const { return m_ServerStat; }

	// premium play ����
	BYTE isPremiumZone() const { return m_fPremium & FLAG_PREMIUM_ZONE; }
	BYTE isPremiumPlay() const { return m_fPremium & FLAG_PREMIUM_PLAY; }

	DWORD GetSMSCharge() const {return m_SMS_Charge;}

	NicknameInfo* getNicknameInfo() const { return m_pNicknameInfo; }

    BYTE    isNonPK() const { return m_NonPK; }

	BYTE	getGuildUnionUserType() const { return m_GuildUnionUserType; }
	void	setGuildUnionUserType(BYTE type) { m_GuildUnionUserType= type; }

	uint	getGuildUnionID() const { return m_GuildUnionID; }
	void	setGuildUnionID(uint ID) { m_GuildUnionID = ID; }

	BloodBibleSignInfo*	getBloodBibleSignInfo() { return m_pBloodBibleSign; }
	void	setBloodBibleSignInfo( BloodBibleSignInfo* pInfo ) { m_pBloodBibleSign = pInfo; }

	DWORD GetPowerjjang_Point() const {return m_PowerjjangPoint;}
//--------------------------------------------------
// data members
//--------------------------------------------------
private :

	//--------------------------------------------------------------------------------
	// PC Information
	//--------------------------------------------------------------------------------
	// PCSlayerInfo2 �Ǵ� PCVampireInfo2 �� ����Ѵ�.
	PCInfo* m_pPCInfo;

	//--------------------------------------------------------------------------------
	// Inventory Information
	//--------------------------------------------------------------------------------
	InventoryInfo* m_pInventoryInfo;

	//--------------------------------------------------------------------------------
	// Gear Information
	//--------------------------------------------------------------------------------
	GearInfo* m_pGearInfo;


#if __CONTENTS(__TIPOJYU_CASTLE) // GCUpdateInfoFactory		InstanceDoungeonInfo ����
	//--------------------------------------------------------------------------------
	// InstanceDoungeon Information
	//--------------------------------------------------------------------------------
	InstanceDoungeonInfo*	m_pInstanceDoungeonInfo;
#endif // __TIPOJYU_CASTLE


	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	ExtraInfo* m_pExtraInfo;

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	EffectInfo* m_pEffectInfo;

	//--------------------------------------------------------------------------------
	// �������Ŭ�� �ֳ� ����.
	//--------------------------------------------------------------------------------
	bool m_hasMotorcycle;

	//--------------------------------------------------------------------------------
	// Motorcycle Information
	//--------------------------------------------------------------------------------
	RideMotorcycleInfo* m_pRideMotorcycleInfo;

	// inventory
	// quick item slot
	// gear

	// ����(PDA)
	// ���� ����Ʈ ����
	// ��������, �̺�Ʈ ����
	// ����.. ����� ó�� PDS�� �� �� �ٿ�����.. - -;

	//--------------------------------------------------------------------------------
	// Zone Information
	//--------------------------------------------------------------------------------
	// �� ���̵�
	ZoneID_t m_ZoneID;	

	// ��Ÿ�� ��ǥ�� �밭�� ��ġ
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

	// Game Time
	GameTime m_GameTime;
	
	// Weather(���� ����)
	Weather m_Weather;
	WeatherLevel_t m_WeatherLevel;

	// Dark/Light
	DarkLevel_t m_DarkLevel;
	LightLevel_t m_LightLevel;

	// ���� �����ϴ� NPC ��������Ʈ Ÿ���� ����, ��������Ʈ Ÿ�� �迭
	BYTE m_nNPCs;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// ���� �����ϴ� ���� ��������Ʈ Ÿ���� ����, ��������Ʈ Ÿ�� �迭
	BYTE m_nMonsters;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// ���� ���� �����ϴ� NPC�鿡 ���� ����
	std::list<NPCInfo*> m_NPCInfos;

	// ���� ����
	BYTE m_ServerStat;

	// �����̾� ����
	BYTE m_fPremium;
	
	DWORD m_SMS_Charge;

	NicknameInfo*	m_pNicknameInfo;

	BYTE    m_NonPK;
	// ���ձ�� ����
	uint	m_GuildUnionID;
	BYTE	m_GuildUnionUserType;

	BloodBibleSignInfo* m_pBloodBibleSign;
	uint	m_PowerjjangPoint;
};


//--------------------------------------------------------------------------------
//
// class GCUpdateInfoFactory;
//
// Factory for GCUpdateInfo
//
//--------------------------------------------------------------------------------

class GCUpdateInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCUpdateInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCUpdateInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_UPDATE_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUpdateInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		size += PCSlayerInfo2::getMaxSize();
		size += InventoryInfo::getMaxSize();
		size += GearInfo::getMaxSize();
		size += ExtraInfo::getMaxSize();
		size += EffectInfo::getMaxSize();
		size += szBYTE;
		size += RideMotorcycleInfo::getMaxSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += GameTime::getMaxSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* maxNPCPerZone;
		size += szBYTE;
		size += szMonsterType* maxMonsterPerZone; 

		size += szBYTE;
		size += NPCInfo::getMaxSize()* 255;
		// ���� ����
		size += szBYTE;
		// �����̾�
		size += szBYTE;

		size += szDWORD;
		size += NicknameInfo::getMaxSize();

		size += szBYTE; // non pk ����

		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		// blood bible ����
		size += BloodBibleSignInfo::getMaxSize();

		// power jjang point
		size += sizeof(uint);

#if __CONTENTS(__TIPOJYU_CASTLE) // GCUpdateInfoFactory		InstanceDoungeonInfo ��Ŷ ������ �߰�		�������� ���� �غ� �ȵ�
		size += InstanceDoungeonInfo::getMaxSize();
#endif // __TIPOJYU_CASTLE
		return size;
	}

};



//--------------------------------------------------------------------------------
//
// class GCUpdateInfoHandler;
//
//--------------------------------------------------------------------------------

class GCUpdateInfoHandler {

public :

	// execute packet's handler
	static void execute(GCUpdateInfo* pPacket, Player* pPlayer);

};

#endif
