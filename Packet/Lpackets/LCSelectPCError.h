//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCSelectPCError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SELECT_PC_ERROR_H__
#define __LC_SELECT_PC_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

enum SELECT_PC_ERROR
{
	SELECT_PC_ERROR_NULL,

	SELECT_PC_CANNOT_PLAY,			// ���� �� �� ���� ĳ����(���� ����)
	SELECT_PC_NOT_BILLING_CHECK,	// ���� ���� ������ üũ���� �ʾҴ�.
	SELECT_PC_CANNOT_PLAY_BY_ATTR,  // �ɷ�ġ ������ �� �̻� ����� ���Ѵ�.
	SELECT_PC_DIDNOT_AGREE,         // �ݸ��� ����� �������� �ʾƼ� �÷��� �� �� ����.
	SELECT_PC_CANNOT_PLAY_BY_AGE,	// ���̷� ���� ��� �� �� ����.
};

//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCError;
//
// �÷��̾ ������ PC �� �������� ���� ���, �Ǵ� ������ �α׾ƿ��ߴ�
// ���� ���� ������ �ٿ�Ǿ��� ���, �Ǵ� DB ������ �ٿ�Ǿ��� ���,
// �� ��Ŷ�� ���� ������ ��Ƽ� Ŭ���̾�Ʈ�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCError : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_LC_SELECT_PC_ERROR; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE; }
	
	// get packet's name
	std::string getPacketName() const { return "LCSelectPCError"; }
	
	// get packet's debug std::string
	std::string toString() const;
	
	// get/set error message
	BYTE getCode() const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private : 

	// ���� �޽���
	BYTE  m_Code;

};


//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCErrorFactory;
//
// Factory for LCSelectPCError
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() { return new LCSelectPCError(); }

	// get packet name
	std::string getPacketName() const { return "LCSelectPCError"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_LC_SELECT_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCErrorHandler {

public:

	// execute packet's handler
	static void execute(LCSelectPCError* pPacket, Player* pPlayer);

};

#endif
