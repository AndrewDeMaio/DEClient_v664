////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeMoney.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_MONEY_H__
#define __GC_TRADE_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ������ ��ȯ�� ���� �׼��� �÷ȴ�.
	GC_TRADE_MONEY_INCREASE = 0,

	// ������ ��ȯ�� ���� �׼��� �ٿ���.
	GC_TRADE_MONEY_DECREASE,

	// ������ �κ��丮���� �پ�� ���� �׼�
	GC_TRADE_MONEY_INCREASE_RESULT,

	// ������ �κ��丮���� �þ ���� �׼�
	GC_TRADE_MONEY_DECREASE_RESULT,
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoney;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoney : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_GC_TRADE_MONEY; }
	size_t getPacketSize () const { return szObjectID + szGold + szBYTE ; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeMoney"; }
		std::string toString () const;
	#endif

public:
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

	Gold_t getAmount() const { return m_Gold; }
	void setAmount(Gold_t gold) { m_Gold = gold; }

	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	Gold_t     m_Gold;           // ���ϴ� �׼�
	BYTE       m_Code;           // �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoneyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new GCTradeMoney(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeMoney"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_GC_TRADE_MONEY; }
	PacketSize_t getPacketMaxSize () const { return szObjectID + szGold + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoneyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyHandler 
{
public:
	static void execute ( GCTradeMoney * pPacket , Player * pPlayer );

};

#endif
