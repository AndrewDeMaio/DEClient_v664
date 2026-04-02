//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyGuildMemberInfo.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_GUILD_MEMBER_INFO_H__
#define __GC_MODIFY_GUILD_MEMBER_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfo;
//
// ���� ������ Ư�� �÷��̾��� ModifyGuildMemberInfo �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� ModifyGuildMemberInfo ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID + szBYTE + m_GuildName.size() + szGuildMemberRank; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCModifyGuildMemberInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set Guild ID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) { m_GuildID = guildID; }

	// get/set Guild Name
	const std::string& getGuildName() const { return m_GuildName; }
	void setGuildName(const std::string& guildName) { m_GuildName = guildName; }

	// get/set Guild ID
	GuildMemberRank_t getGuildMemberRank() const { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t guildMemberRank ) { m_GuildMemberRank = guildMemberRank; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	std::string m_GuildName;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoFactory;
//
// Factory for GCModifyGuildMemberInfo
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCModifyGuildMemberInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCModifyGuildMemberInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCModifyGuildMemberInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szGuildID + szBYTE + 30 + szGuildMemberRank; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCModifyGuildMemberInfo* pPacket, Player* pPlayer);

};

#endif
