//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnionDeny.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_DENY_H__
#define __CG_QUIT_UNION_DENY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDeny;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDeny : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_QUIT_UNION_DENY; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGQuitUnionDeny"; }

	// get packet's debug string
	string toString() const;
#endif
	// get/set GuildID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyFactory;
//
// Factory for CGQuitUnionDeny
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDenyFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionDenyFactory() {}
	
	// destructor
	virtual ~CGQuitUnionDenyFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGQuitUnionDeny(); }

	// get packet name
	string getPacketName() const { return "CGQuitUnionDeny"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_QUIT_UNION_DENY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGQuitUnionDenyHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnionDeny* pCGQuitUnionDeny, Player* pPlayer);

};
#endif
#endif
