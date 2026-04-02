//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGuildResponse.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GUILD_RESPONSE_H__
#define __GC_GUILD_RESPONSE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCGuildResponse
//////////////////////////////////////////////////////////////////////////////
enum UNION_ERROR
{
		OK = 0,
        ALREADY_IN_UNION,		
        ALREADY_OFFER_SOMETHING,
        TARGET_IS_NOT_MASTER,   // ������ �����Ͱ� �ƴ϶��;;
        NOT_IN_UNION,           // ���տ� ���Ե� ���°� �ƴ�
        MASTER_CANNOT_QUIT,     // ������ ������ ���� ������ Ż��Ұ�(������尡 �������� ����-�ڵ��̷�)
        NO_TARGET_UNION,        // �ش��ϴ� ������ ����
        NOT_YOUR_UNION,         // �Ҽӵ� ������ �ƴϴ�.
        SOURCE_IS_NOT_MASTER,   // ��û�� ����� �����Ͱ� �ƴϴ�    
		YOU_HAVE_PENALTY,        // ������ Ż���� ����� �ִ�.
		NOT_ENOUGH_SLOT,			// �����ִ� ������ ����.
		TOO_MANY_MEMBER,		// ����� 50���̻��̶� ������ �� �����ϴ�.
};

class GCGuildResponse : public Packet 
{

public:
	GCGuildResponse() { m_Code = 0; m_Parameter = 0;}
	virtual ~GCGuildResponse() {}

public:
	void read(SocketInputStream & iStream);
	void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_GC_GUILD_RESPONSE; }
	size_t getPacketSize() const;
#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCGuildResponse"; }
	string toString() const;
#endif	
public:
	BYTE getCode(void) const { return m_Code;}
	void setCode(WORD code) { m_Code = code;}

	uint getParameter(void) const { return m_Parameter; }
	void setParameter(uint parameter) { m_Parameter = parameter; }

private: 
	WORD m_Code;
	uint m_Parameter;

};


//////////////////////////////////////////////////////////////////////////////
// class GCGuildResponseFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGuildResponseFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCGuildResponse(); }
	string getPacketName() const { return "GCGuildResponse"; }
	PacketID_t getPacketID() const { return Packet::PACKET_GC_GUILD_RESPONSE; }
	PacketSize_t getPacketMaxSize() const { return szWORD + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCGuildResponseHandler
//////////////////////////////////////////////////////////////////////////////

class GCGuildResponseHandler 
{
public:
	static void execute( GCGuildResponse* pPacket, Player* pPlayer);
};

#endif
