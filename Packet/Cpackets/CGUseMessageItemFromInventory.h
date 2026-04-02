//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseMessageItemFromInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "CGUseItemFromInventory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventory : public CGUseItemFromInventory 
{
public:
#ifdef __DEBUG_OUTPUT__
    void read(SocketInputStream & iStream);
#endif

    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	size_t getPacketSize() const 
	{ 
		return CGUseItemFromInventory::getPacketSize() 
				+ szBYTE + m_Message.size(); 
	}

#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const { return "CGUseMessageItemFromInventory"; }
	std::string toString() const;
#endif
	
public:
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string& msg) { m_Message = msg; }

private:
	std::string m_Message;
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGUseMessageItemFromInventoryFactory : public CGUseItemFromInventoryFactory 
{
public:
	Packet* createPacket() { return new CGUseMessageItemFromInventory(); }
	std::string getPacketName() const { return "CGUseMessageItemFromInventory"; }
	PacketID_t getPacketID() const { return Packet::PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketMaxSize() const 
	{ 
		return CGUseItemFromInventoryFactory::getPacketMaxSize() 
				+ szBYTE + 128; 
	}
};
#endif

//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGUseMessageItemFromInventoryHandler 
{
public:
	static void execute(CGUseMessageItemFromInventory* pPacket, Player* player);

protected:
	static void executeEventTree(CGUseMessageItemFromInventory* pPacket, Player* player);
};
#endif
#endif
