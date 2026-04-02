//--------------------------------------------------------------------------------
// 
// Filename    : GCShopVersion.h 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_VERSION_H__
#define __GC_SHOP_VERSION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopVersion;
//
//--------------------------------------------------------------------------------

class GCShopVersion : public Packet 
{

public :

	GCShopVersion();
	virtual ~GCShopVersion();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream );
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_SHOP_VERSION; }
	
	// get packet's body size
	size_t getPacketSize () const { return szObjectID 
#if __CONTENTS(__GLOBAL_NPC)
		+ szNPCID
#endif //__GLOBAL_NPC
		+ szShopVersion*3+ szMarketCond; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCShopVersion"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set NPC's object id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) { m_ObjectID = creatureID; }

	// get/set shop version
	ShopVersion_t getVersion(ShopRackType_t type) const
	{
		if (type >= SHOP_RACK_TYPE_MAX) : Out of Bound!");
		return m_Version[type];
	}
	
	void setVersion(ShopRackType_t type, ShopVersion_t ver)
	{
		if (type >= SHOP_RACK_TYPE_MAX) : Out of Bound!");
		m_Version[type] = ver;
	}

	// get/set market condition sell
	MarketCond_t getMarketCondSell(void) const { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond) { m_MarketCondSell = cond;}

#if __CONTENTS(__GLOBAL_NPC)
	NPCID_t getNPCID() const						{return m_NPCID; }
	void setNPCID (NPCID_t n)					{m_NPCID = n;}
#endif //__GLOBAL_NPC

	
private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
#if __CONTENTS(__GLOBAL_NPC)
	NPCID_t m_NPCID;
#endif //NPCID_t
	
	// shop version
	ShopVersion_t m_Version[SHOP_RACK_TYPE_MAX];
	
	MarketCond_t m_MarketCondSell;

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionFactory;
//
// Factory for GCShopVersion
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet * createPacket () { return new GCShopVersion(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCShopVersion"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_SHOP_VERSION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopVersionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID
#if __CONTENTS(__GLOBAL_NPC)
		+ szNPCID
#endif //__GLOBAL_NPC
		+ szShopVersion*3+ szMarketCond; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionHandler 
{
	
public :
	
	// execute packet's handler
	static void execute ( GCShopVersion * pPacket , Player * pPlayer );

};

#endif
