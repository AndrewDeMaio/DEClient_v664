//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnionAccept.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_ACCEPT_H__
#define __CG_QUIT_UNION_ACCEPT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionAccept;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionAccept : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_QUIT_UNION_ACCEPT; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGQuitUnionAccept"; }

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
// class CGQuitUnionAcceptFactory;
//
// Factory for CGQuitUnionAccept
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionAcceptFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionAcceptFactory() {}
	
	// destructor
	virtual ~CGQuitUnionAcceptFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGQuitUnionAccept(); }

	// get packet name
	string getPacketName() const { return "CGQuitUnionAccept"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_QUIT_UNION_ACCEPT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionAcceptHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGQuitUnionAcceptHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnionAccept* pCGQuitUnionAccept, Player* pPlayer);

};
#endif
#endif
