//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWaitGuildList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4786)

#ifndef __GC_WAIT_GUILD_LIST_H__
#define __GC_WAIT_GUILD_LIST_H__

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildInfo.h"

typedef std::list<GuildInfo*> GuildInfoList;
typedef std::list<GuildInfo*>::const_iterator GuildInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCWaitGuildList;
//
// Ŭ���̾�Ʈ�� ��� ������� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCWaitGuildList : public Packet {

public :

	// constructor
	GCWaitGuildList();

	// destructor
	~GCWaitGuildList();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_WAIT_GUILD_LIST; }
	
	// get packet's body size
	size_t getPacketSize() const;

	// get packet name
	std::string getPacketName() const { return "GCWaitGuildList"; }
	
	// get packet's debug std::string
	std::string toString() const;

public:

	BYTE getListNum() const { return m_GuildInfoList.size(); }

	// add GuildInfo
	void addGuildInfo( GuildInfo* pGuildInfo ) { m_GuildInfoList.push_front( pGuildInfo ); }

	// clear GuildInfoList
	void clearGuildInfoList();

	// pop front Element in GuildInfoList
	GuildInfo* popFrontGuildInfoList()
	{
		if ( !m_GuildInfoList.empty() )
		{
			GuildInfo* pGuildInfo = m_GuildInfoList.front();
			m_GuildInfoList.pop_front();
			return pGuildInfo;
		}
		return NULL;
	}


private :
	
	GuildInfoList m_GuildInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCWaitGuildListFactory;
//
// Factory for GCWaitGuildList
//
//////////////////////////////////////////////////////////////////////

class GCWaitGuildListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCWaitGuildList(); }

	// get packet name
	std::string getPacketName() const { return "GCWaitGuildList"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_WAIT_GUILD_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szWORD + (GuildInfo::getMaxSize() * 5000); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWaitGuildList;
//
//////////////////////////////////////////////////////////////////////

class GCWaitGuildListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCWaitGuildList* pPacket, Player* pPlayer);

};

#endif
