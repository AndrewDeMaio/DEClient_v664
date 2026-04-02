////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_REMOVE_ITEM_H__
#define __CG_TRADE_REMOVE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItem : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_CG_TRADE_REMOVE_ITEM; }
	size_t getPacketSize () const { return szObjectID*2; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradeRemoveItem"; }
		std::string toString () const;
	#endif
	
public:
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID() const { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id) { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	ObjectID_t m_ItemObjectID;   // ��ȯ ����Ʈ�� �߰��� �������� OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemFactory;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGTradeRemoveItemFactory : public PacketFactory {
public:
	Packet * createPacket () { return new CGTradeRemoveItem(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradeRemoveItem"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketMaxSize () const { return szObjectID*2; }
};
#endif

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGTradeRemoveItemHandler 
	{
	public:
		static void execute ( CGTradeRemoveItem * pPacket , Player * player );
		static void executeSlayer ( CGTradeRemoveItem * pPacket , Player * player );
		static void executeVampire ( CGTradeRemoveItem * pPacket , Player * player );
		static void executeError ( CGTradeRemoveItem * pPacket , Player * player, BYTE ErrorCode );
	};
#endif

#endif
