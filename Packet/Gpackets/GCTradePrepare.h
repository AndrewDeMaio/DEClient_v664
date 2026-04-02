////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradePrepare.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_PREPARE_H__
#define __GC_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ���� ó�� ��ȯ�� ��û���� �÷��̾�� �����ִ� �ڵ�
	GC_TRADE_PREPARE_CODE_REQUEST = 0,

	GC_TRADE_PREPARE_CODE_CANCEL,

	// ��ȯ�� ��û���� �÷��̾ ������ ��쿡, ��û�ڿ��� �����ش�.
	GC_TRADE_PREPARE_CODE_ACCEPT,

	// ��ȯ�� ��û���� �÷��̾ �ź����� ��쿡, ��û�ڿ��� �����ش�.
	GC_TRADE_PREPARE_CODE_REJECT,

	// ��ȯ�� ��û���� �÷��̾ ���� ��ȯ ���̴�.
	GC_TRADE_PREPARE_CODE_BUSY,

	GC_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepare : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_GC_TRADE_PREPARE; }
	size_t getPacketSize () const { return szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradePrepare"; }
		std::string toString () const;
	#endif

public:
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private :
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ OID
	BYTE       m_Code;           // ��ȯ �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new GCTradePrepare(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradePrepare"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_GC_TRADE_PREPARE; }
	PacketSize_t getPacketMaxSize () const { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareHandler 
{
public:
	static void execute ( GCTradePrepare * pPacket , Player * pPlayer );

};

#endif
