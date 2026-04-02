////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinish.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_FINISH_H__
#define __CG_TRADE_FINISH_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ����� �� ������ �ڵ�
	CG_TRADE_FINISH_ACCEPT = 0,
	
	// ��ȯ�� �ź��� �� ������ �ڵ�
	CG_TRADE_FINISH_REJECT,

	// ��ȯ�� ������� �� ������ �ڵ�
	CG_TRADE_FINISH_RECONSIDER,


	CG_TRADE_FINISH_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinish;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinish : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_CG_TRADE_FINISH; }
	size_t getPacketSize () const { return szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradeFinish"; }
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
// class CGTradeFinishFactory;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGTradeFinishFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new CGTradeFinish(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradeFinish"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_CG_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize () const { return szObjectID + szBYTE; }
};
#endif

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinishHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGTradeFinishHandler 
	{
	public:
		static void execute ( CGTradeFinish * pPacket , Player * player );
		static void executeSlayer ( CGTradeFinish * pPacket , Player * player );
		static void executeVampire ( CGTradeFinish * pPacket , Player * player );
		static void executeError ( CGTradeFinish * pPacket , Player * player, BYTE ErrorCode );
	};
#endif

#endif
