//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCOtherGuildName.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_GUILD_NAME_H__
#define __GC_OTHER_GUILD_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildName;
//
// ���� ������ Ư�� �÷��̾��� OtherGuildName �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� OtherGuildName ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildName : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_OTHER_GUILD_NAME; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID + szGuildID + szBYTE + m_GuildName.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCOtherGuildName"; }
	
	// get packet's debug string
	std::string toString() const;
#endif

	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t objectID ) { m_ObjectID = objectID; }

	// get/set Guild ID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) { m_GuildID = guildID; }

	// get/set Guild Name
	const std::string& getGuildName() const { return m_GuildName; }
	void setGuildName(const std::string& guildName) { m_GuildName = guildName; }

private :

	ObjectID_t m_ObjectID;

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	std::string m_GuildName;

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameFactory;
//
// Factory for GCOtherGuildName
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCOtherGuildName(); }

	// get packet name
	std::string getPacketName() const { return "GCOtherGuildName"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_OTHER_GUILD_NAME; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCOtherGuildNamePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szObjectID + szGuildID + szBYTE + 30; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameHandler;
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCOtherGuildName* pPacket, Player* pPlayer);

};

#endif
