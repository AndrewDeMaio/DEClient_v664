////////////////////////////////////////////////////////////////////////////////

// Filename    : CGGetEventItem.h 

// Written By  : �輺��

// Description : 

////////////////////////////////////////////////////////////////////////////////



#ifndef __CG_GET_EVENT_ITEM_H__

#define __CG_GET_EVENT_ITEM_H__



#include "Packet.h"

#include "PacketFactory.h"



////////////////////////////////////////////////////////////////////////////////

// ��� ����

////////////////////////////////////////////////////////////////////////////////

enum EventType

{

	EVENT_TYPE_200412_COMBACK_ITEM = 0,			// ���ƿ� ����� �� ������ �ֱ� �̺�Ʈ

	EVENT_TYPE_200412_COMBACK_PREMIUM_ITEM,		// ���ƿ� ����� ���� �� ������ �ֱ� �̺�Ʈ

	EVENT_TYPE_200412_COMBACK_RECOMMEND_ITEM,	// ���ƿ� ����� ���� �� ��õ ���� �� ������ �ֱ� �̺�Ʈ

	EVENT_TYPE_200507_COMEBACK_ITEM,			// ���ƿ� ����ڿ��� ������ �ֱ� �̺�Ʈ 2005.7

	EVENT_TYPE_200507_COMEBACK_PREMIUM_ITEM,	// ���ƿ� ����� ���� �� ������ �ֱ� �̺�Ʈ 2005.7

	EVENT_TYPE_200507_COMEBACK_RECOMMEND_ITEM,	// ���ƿ� ����� ���� �� ��õ ���� �� ������ �ֱ� �̺�Ʈ 2005.7

	EVENT_TYPE_MAX

};



////////////////////////////////////////////////////////////////////////////////

//

// class CGGetEventItem

//

////////////////////////////////////////////////////////////////////////////////

class CGGetEventItem : public Packet 

{

public:

	void read(SocketInputStream & iStream);

	void write(SocketOutputStream & oStream) const;

	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_CG_GET_EVENT_ITEM; }

	size_t getPacketSize() const { return szBYTE; }

	string getPacketName() const { return "CGGetEventItem"; }

	string toString() const;

	

public:

	// get / set Event Type

	BYTE getEventType() const { return m_EventType; }

	void setEventType( BYTE eventType ) { m_EventType = eventType; }



private:

	BYTE		m_EventType;		// �̺�Ʈ ����

};





////////////////////////////////////////////////////////////////////////////////

//

// class CGGetEventItemFactory

//

////////////////////////////////////////////////////////////////////////////////



class CGGetEventItemFactory : public PacketFactory 

{

public:

	Packet* createPacket() { return new CGGetEventItem(); }

	string getPacketName() const { return "CGGetEventItem"; }

	PacketID_t getPacketID() const { return Packet::PACKET_CG_GET_EVENT_ITEM; }

	PacketSize_t getPacketMaxSize() const { return szBYTE; }

};





////////////////////////////////////////////////////////////////////////////////

//

// class CGGetEventItemHandler

//

////////////////////////////////////////////////////////////////////////////////

class CGGetEventItemHandler 

{

public:

//	static void execute(CGGetEventItem* pPacket, Player* player);

};



#endif



