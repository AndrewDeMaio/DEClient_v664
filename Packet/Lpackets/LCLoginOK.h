//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCLoginOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_LOGIN_OK_H__
#define __LC_LOGIN_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCLoginOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCLoginOK : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_LOGIN_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCLoginOKPacketSize �� ����, �����϶�.
	size_t getPacketSize() const;
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName() const { return "LCLoginOK"; }

	#endif

	// get / set GoreLevel
	bool isAdult() const { return m_isAdult; }
	void setAdult(bool isAdult) { m_isAdult = isAdult; }

	// is UnderFifthteen
	bool isUnderFifthteen() const { return m_bUnderFifthteen; }
	void setUnderFifthteen( bool bUnderFifthteen ) { m_bUnderFifthteen = bUnderFifthteen; }

	bool isFamily() const { return m_bFamily; }
	void setFamily(bool isFamily) { m_bFamily = isFamily; }

	BYTE getStat() const { return m_Stat; }
	void setStat(BYTE Stat) { m_Stat = Stat; }

	WORD getLastDays() const { return m_LastDays; }
	void setLastDays( WORD day ) { m_LastDays = day; }
#if __CONTENTS(__PAYZONE_PASS_TICKET)
	//	20080312 ������ Ƽ�� �߰��� PayType �߰�
	BYTE getPayType() const { return m_PayType; }
	void setPayType(BYTE PayType) { m_PayType = PayType; }
#endif //__PAYZONE_PASS_TICKET
	// get packet's debug string
	string toString() const { return "LCLoginOK"; }

#if __CONTENTS(__LOGIN_PACKET)
	BYTE getReservedValue() const { return m_ReservedValue; }
	void setReservedValue(BYTE ReservedValue) { m_ReservedValue = ReservedValue; }
#endif //__LOGIN_PACKET

private :

	// ���� ���� : ���� �÷��̾ �̼����� �ΰ�?
	// true�� ��� ����
	// false �� ��� �̼�����
	bool m_isAdult;
	
	// 15�� �̸��ΰ�?
	bool m_bUnderFifthteen;
	
	// Family ������ΰ�?
	bool m_bFamily;

	// ������ ����
	BYTE m_Stat;

	WORD m_LastDays;
#if __CONTENTS(__PAYZONE_PASS_TICKET)
	BYTE m_PayType;	//20080312 ������ Ƽ�� �߰��� PayType �߰�
#endif //__PAYZONE_PASS_TICKET
#if __CONTENTS(__LOGIN_PACKET)
	BYTE m_ReservedValue;	// ���� Ŭ���̾�Ʈ ������ �����ϱ� ���� �ʵ� �߰�
#endif //__LOGIN_PACKET
};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKFactory;
//
// Factory for LCLoginOK
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCLoginOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const { return "LCLoginOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_LOGIN_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const { return szBYTE + szBYTE + szBYTE + szBYTE + szWORD 
#if __CONTENTS(__PAYZONE_PASS_TICKET)
		+ szBYTE
#endif //__PAYZONE_PASS_TICKET

#if __CONTENTS(__LOGIN_PACKET)
		+ szBYTE 
#endif //__LOGIN_PACKET
	;}
};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKHandler {

public:

	// execute packet's handler
	static void execute(LCLoginOK* pPacket, Player* pPlayer);

};

#endif
