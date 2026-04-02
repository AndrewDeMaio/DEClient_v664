//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSold.h 
// Written By  : �輺��
// Description : �� �÷��̾ ���� NPC���� ������ �����ߴµ�,
//               �ٸ� �÷��̾ ���� ���� NPC�� ��ȭ ���̾��ٸ�,
//               �� �÷��̾�� ������ ����� ����ȭ�����־�� �Ѵ�.
//               �� ��Ŷ�� �׸� ���� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SOLD_H__
#define __GC_SHOP_SOLD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSold;
//
//--------------------------------------------------------------------------------

class GCShopSold : public Packet 
{

public :

	GCShopSold();
	virtual ~GCShopSold();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream );
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_SHOP_SOLD; }
	
	// get packet's body size
	size_t getPacketSize () const { return szObjectID + szShopVersion + szShopRackType + szBYTE;}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCShopSold"; }	
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set NPC's object id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) { m_ObjectID = creatureID; }

	// get/set shop version	
	ShopVersion_t getShopVersion(void) const { return m_Version;}
	void setShopVersion(const ShopVersion_t ver) { m_Version = ver;}

	// get/set rack type
	ShopRackType_t getShopType(void) const { return m_RackType;}
	void setShopType(ShopRackType_t type) { m_RackType = type;}
	
	// get/set rack index
	BYTE getShopIndex(void) const { return m_RackIndex;}
	void setShopIndex(BYTE index) { m_RackIndex = index;}

private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
	
	// ���� ����
	ShopVersion_t m_Version;

	// ������ ����	
	ShopRackType_t m_RackType;
	
	// ������ �ε���
	BYTE m_RackIndex;
	
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldFactory;
//
// Factory for GCShopSold
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet * createPacket () { return new GCShopSold(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCShopSold"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_SHOP_SOLD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSoldPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szObjectID + szShopVersion + szShopRackType + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldHandler 
{
	
public :
	
	// execute packet's handler
	static void execute ( GCShopSold * pPacket , Player * pPlayer );

};

#endif
