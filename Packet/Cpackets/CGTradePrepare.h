////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradePrepare.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_PREPARE_H__
#define __CG_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ���� ó�� ��ȯ�� ���ϴ� �÷��̾ �� �ڵ�� ��Ŷ�� ������.
	CG_TRADE_PREPARE_CODE_REQUEST = 0,

	// ��ȯ ��û�ϴٰ� ����� ���
	CG_TRADE_PREPARE_CODE_CANCEL,

	// ��ȯ�� ��û���� �÷��̾ ��ȯ�� ���� ���
	CG_TRADE_PREPARE_CODE_ACCEPT,

	// ��ȯ�� ��û���� �÷��̾ ��ȯ�� ������ ���� ���
	CG_TRADE_PREPARE_CODE_REJECT,

	// ��ȯ�� ��û���� �÷��̾ ���� ��ȯ�� �� �� ���� ���
	CG_TRADE_PREPARE_CODE_BUSY,

	CG_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradePrepare : public Packet 
{
public:
	void read ( SocketInputStream & iStream );
	void write ( SocketOutputStream & oStream ) const;
	void execute ( Player * pPlayer );
	PacketID_t getPacketID () const { return PACKET_CG_TRADE_PREPARE; }
	size_t getPacketSize () const { return szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradePrepare"; }
		std::string toString () const;
	#endif
	
public:
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

	BYTE getCode(void) const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ OID
	BYTE       m_Code;           // ��ȯ �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGTradePrepareFactory : public PacketFactory 
{
public:
	Packet * createPacket () { return new CGTradePrepare(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGTradePrepare"; }
	#endif

	PacketID_t getPacketID () const { return Packet::PACKET_CG_TRADE_PREPARE; }
	PacketSize_t getPacketMaxSize () const { return szObjectID + szBYTE; }
};
#endif


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGTradePrepareHandler 
	{
	public:
		static void execute ( CGTradePrepare * pPacket , Player * player );
		static void executeSlayer ( CGTradePrepare * pPacket , Player * player );
		static void executeVampire ( CGTradePrepare * pPacket , Player * player );
		static void executeError ( CGTradePrepare * pPacket , Player * player, BYTE ErrorCode );
	};
#endif

#endif
