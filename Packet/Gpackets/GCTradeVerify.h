////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeVerify.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_VERIFY_H__
#define __GC_TRADE_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ���� �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ ������� �������� �߰��ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT,

	// ��ȯ ��󿡼� �������� �����ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_REMOVE_ITEM,

	// ��ȯ ��󿡼� ���� �߰��ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_MONEY_INCREASE,

	// ��ȯ ��󿡼� ���� �����ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_MONEY_DECREASE,

	// ��ȯ ������ Ȯ���ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_FINISH_ACCEPT,

	// ��ȯ ������ ����ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_FINISH_REJECT,

	// ��ȯ ������ ������ϴ� ���� ����
	GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER,

	// ��ȯ�� �ϰ� ���� �� ���콺�� �κ��丮�� �������� �ű�� ���� ����
	GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_OK,
	GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_FAIL,

	// ��ȯ�� �ϰ� ���� �� �κ��丮���� ���콺�� �������� �ű�� ���� ����
	GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_OK,
	GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_FAIL,

	// GCTradeAddItem�� ���� �޾ƾ� �ϴ� ��쿡..
	GC_TRADE_VERIFY_CODE_ADD_ITEM_OK,
	GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL,

	// ������.
	GC_TRADE_VERIFY_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerify;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerify : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_GC_TRADE_VERIFY; }
	size_t getPacketSize () const { return szBYTE ; }
	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeVerify"; }
		std::string toString () const;
	#endif

public:
	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private:
	BYTE       m_Code;           // �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerifyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerifyFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new GCTradeVerify(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeVerify"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_GC_TRADE_VERIFY; }
	PacketSize_t getPacketMaxSize () const { return szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerifyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerifyHandler 
{
public:
	static void execute ( GCTradeVerify * pPacket , Player * pPlayer );

};

#endif
