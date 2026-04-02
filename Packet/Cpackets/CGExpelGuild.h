//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGExpelGuild.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_EXPEL_GUILD_H__
#define __CG_EXPEL_GUILD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGExpelGuild;
//
//////////////////////////////////////////////////////////////////////

class CGExpelGuild : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_EXPEL_GUILD; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGExpelGuild"; }

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
// class CGExpelGuildFactory;
//
// Factory for CGExpelGuild
//
//////////////////////////////////////////////////////////////////////

class CGExpelGuildFactory : public PacketFactory {

public:
	
	// constructor
	CGExpelGuildFactory() {}
	
	// destructor
	virtual ~CGExpelGuildFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGExpelGuild(); }

	// get packet name
	string getPacketName() const { return "CGExpelGuild"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_EXPEL_GUILD; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGExpelGuildHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGExpelGuildHandler {

public:

	// execute packet's handler
	static void execute(CGExpelGuild* pCGExpelGuild, Player* pPlayer);

};
#endif
#endif
