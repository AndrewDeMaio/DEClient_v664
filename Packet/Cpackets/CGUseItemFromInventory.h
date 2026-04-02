//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromInventory : public Packet 
{
public:
	CGUseItemFromInventory ();
	~CGUseItemFromInventory ();

    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_CG_USE_ITEM_FROM_INVENTORY; }
	size_t getPacketSize() const { return szObjectID + szObjectID + szCoordInven + szCoordInven; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const { return "CGUseItemFromInventory"; }
		std::string toString() const;
	#endif	
	
public:
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) { m_InventoryItemObjectID = InventoryItemObjectID; }
	
	CoordInven_t getX() const { return m_InvenX; }
	void setX(CoordInven_t InvenX) { m_InvenX = InvenX; }

	CoordInven_t getY() const { return m_InvenY; }
	void setY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t   m_ObjectID; // �������� object id 
	// ���� �κ��丮 �������� ������Ʈ ���̵�. 0�̸� ���� �κ��丮���� ���
	ObjectID_t	 m_InventoryItemObjectID;
	CoordInven_t m_InvenX;   // �������� �κ��丮 ��ǥ X
	CoordInven_t m_InvenY;   // �������� �κ��丮 ��ǥ Y
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGUseItemFromInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new CGUseItemFromInventory(); }
	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const { return "CGUseItemFromInventory"; }
	#endif
	PacketID_t getPacketID() const { return Packet::PACKET_CG_USE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketMaxSize() const { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
};
#endif

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

#ifndef __GAME_CLIENT__
	class CGUseItemFromInventoryHandler 
	{
	public:
		static void execute(CGUseItemFromInventory* pPacket, Player* player);

	protected:
		static void executePotion(CGUseItemFromInventory* pPacket, Player* player);
		static void executeMagazine(CGUseItemFromInventory* pPacket, Player* player);
		static void executeETC(CGUseItemFromInventory* pPacket, Player* player);
		static void executeSerum(CGUseItemFromInventory* pPacket, Player* player);
		static void executeVampireETC(CGUseItemFromInventory* pPacket, Player* player);
	};
#endif

#endif
