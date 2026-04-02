////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeFinish.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_FINISH_H__
#define __GC_TRADE_FINISH_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ����� �� ������ �ڵ�
	GC_TRADE_FINISH_ACCEPT = 0,

	// ��ȯ�� �ź��� �� ������ �ڵ�
	GC_TRADE_FINISH_REJECT,

	// ��ȯ�� ������� �� ������ �ڵ�
	GC_TRADE_FINISH_RECONSIDER,

	// ��ȯ ����
	GC_TRADE_FINISH_EXECUTE,

	GC_TRADE_FINISH_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinish;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinish : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_GC_TRADE_FINISH; }
	size_t getPacketSize () const { return szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeFinish"; }
		std::string toString () const;
	#endif

public:
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	BYTE       m_Code;           // ��ȯ �ڵ�


};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinishFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinishFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new GCTradeFinish(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCTradeFinish"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_GC_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize () const { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinishHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinishHandler 
{
public:
	static void execute ( GCTradeFinish * pPacket , Player * pPlayer );

};

#endif
