//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMixItem.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MIX_ITEM_H__
#define __CG_MIX_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class CGMixItem;
//////////////////////////////////////////////////////////////////////////////

class CGMixItem : public Packet 
{
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_CG_MIX_ITEM; }
	size_t getPacketSize() const { return szObjectID + szCoordInven + szCoordInven + ( szObjectID * 2 ); }

#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const { return "CGMixItem"; }
	std::string toString() const;
#endif
	
public:
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

	CoordInven_t getX() const { return m_InvenX; }
	void setX(CoordInven_t InvenX) { m_InvenX = InvenX; }

	CoordInven_t getY() const { return m_InvenY; }
	void setY(CoordInven_t InvenY) { m_InvenY = InvenY; }

	ObjectID_t getTargetObjectID( uint index ) const { Assert(index<2); return m_TargetObjectID[index]; }
	void setTargetObjectID( uint index, ObjectID_t oid ) { Assert(index<2); m_TargetObjectID[index] = oid; }

private:
	ObjectID_t   m_ObjectID; // �������� object id 
	CoordInven_t m_InvenX;   // �������� �κ��丮 ��ǥ X
	CoordInven_t m_InvenY;   // �������� �κ��丮 ��ǥ Y

	ObjectID_t	m_TargetObjectID[2];	// ��ĥ �� �������� ������Ʈ ID
};


//////////////////////////////////////////////////////////////////////////////
// class CGMixItemFactory;
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGMixItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new CGMixItem(); }
	std::string getPacketName() const { return "CGMixItem"; }
	PacketID_t getPacketID() const { return Packet::PACKET_CG_MIX_ITEM; }
	PacketSize_t getPacketMaxSize() const { return szObjectID + szCoordInven + szCoordInven + ( szObjectID * 2 ); }
};
#endif

//////////////////////////////////////////////////////////////////////////////
// class CGMixItemHandler;
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

class CGMixItemHandler 
{
public:
	static void execute(CGMixItem* pPacket, Player* pPlayer);
};

#endif
