//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_INFO_H__
#define __GC_SHOW_GUILD_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfo;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SHOW_GUILD_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Name length
			   m_GuildName.size() +		// Guild Name
			   szGuildState +			// Guild State
			   szBYTE +					// Guild Master length
			   m_GuildMaster.size() +	// Guild Master
			   szBYTE +					// Guild Member Count
			   szBYTE +					// Guild Intro length
			   m_GuildIntro.size() +	// Guild Intro
			   szGold;					// Join Fee
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCShowGuildInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set Guild ID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) { m_GuildID = GuildID; }

	// get/set Guild Name
	const std::string& getGuildName() const { return m_GuildName; }
	void setGuildName( const std::string& GuildName ) { m_GuildName = GuildName; }

	// get/set Guild State
	GuildState_t getGuildState() const { return m_GuildState; }
	void setGuildState( GuildState_t GuildState ) { m_GuildState = GuildState; }

	// get/set Guild Master
	const std::string& getGuildMaster() const { return m_GuildMaster; }
	void setGuildMaster( const std::string& GuildMaster ) { m_GuildMaster = GuildMaster; }

	// get/set Guild Member Count
	BYTE getGuildMemberCount() const { return m_GuildMemberCount; }
	void setGuildMemberCount( BYTE GuildMemberCount ) { m_GuildMemberCount = GuildMemberCount; }

	// get/set Guild Intro
	const std::string& getGuildIntro() const { return m_GuildIntro; }
	void setGuildIntro( const std::string& GuildIntro ) { m_GuildIntro = GuildIntro; }
	
	// get/set Guild Join Fee
	Gold_t getJoinFee() const { return m_JoinFee; }
	void setJoinFee( Gold_t JoinFee ) { m_JoinFee = JoinFee; }

private :
	
	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	std::string m_GuildName;

	// Guild State
	GuildState_t m_GuildState;

	// Guild Master
	std::string m_GuildMaster;

	// Guild Member Count
	BYTE m_GuildMemberCount;

	// Guild Intro
	std::string m_GuildIntro;

	// Guild Join Fee
	Gold_t m_JoinFee;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfoFactory;
//
// Factory for GCShowGuildInfo
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCShowGuildInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCShowGuildInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SHOW_GUILD_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const
	{
		return szGuildID +		// Guild ID
			   szBYTE +			// Guild Name length
			   30 +				// Guild Name
			   szGuildState +	// Guild State
			   szBYTE +			// Guild Master length
			   20 +				// Guild Master
			   szBYTE +			// Guild Member Count
			   szBYTE +			// Guild Intro length
			   256 +			// Guild Intro
			   szGold;			// Guild Join Fee
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfo;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildInfo* pPacket, Player* pPlayer);

};

#endif
