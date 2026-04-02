//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildMemberInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_MEMBER_INFO_H__
#define __GC_SHOW_GUILD_MEMBER_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfo;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SHOW_GUILD_MEMBER_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const
	{ 
		return szGuildID +					// Guild ID
			   szBYTE +						// Name length
			   m_Name.size() +				// Name
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   m_GuildMemberIntro.size();	// Guild Member Intro
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCShowGuildMemberInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif
	// get/set Guild ID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) { m_GuildID = GuildID; }

	// get/set Name
	const std::string& getName() const { return m_Name; }
	void setName( const std::string& name ) { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank() const { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t guildMemberRank ) { m_GuildMemberRank = guildMemberRank; }

	// get/set Guild Member Intro
	const std::string& getGuildMemberIntro() const { return m_GuildMemberIntro; }
	void setGuildMemberIntro( const std::string& intro ) { m_GuildMemberIntro = intro; }

private :
	
	// Guild ID
	GuildID_t m_GuildID;

	// Name
	std::string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	std::string m_GuildMemberIntro;

};

//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfoFactory;
//
// Factory for GCShowGuildMemberInfo
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCShowGuildMemberInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCShowGuildMemberInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SHOW_GUILD_MEMBER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const
	{
		return szGuildID +					// Guild ID
			   szBYTE +						// Name length
			   20 +							// Name max size
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   256;							// Guild Member Intro max size
	}

};

//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfo;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildMemberInfo* pPacket, Player* pPlayer);

};

#endif
