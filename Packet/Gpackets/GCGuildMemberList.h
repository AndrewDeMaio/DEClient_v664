//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGuildMemberList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GUILD_MEMBER_LIST_H__
#define __GC_GUILD_MEMBER_LIST_H__

#pragma warning(disable:4786)

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildMemberInfo.h"

typedef std::list<GuildMemberInfo*> GuildMemberInfoList;
typedef std::list<GuildMemberInfo*>::const_iterator GuildMemberInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberList;
//
// Ŭ���̾�Ʈ�� ��� ������� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberList : public Packet {

public :

	// constructor
	GCGuildMemberList();

	// destructor
	~GCGuildMemberList();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_GUILD_MEMBER_LIST; }
	
	// get packet's body size
	size_t getPacketSize() const;

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCGuildMemberList"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

public:

	BYTE getListNum() const { return m_GuildMemberInfoList.size(); }

	// add GuildMemberInfoList
	void addGuildMemberInfo( GuildMemberInfo* pGuildMemberInfo ) { m_GuildMemberInfoList.push_front( pGuildMemberInfo ); }

	// clear GuildMemberInfoList
	void clearGuildMemberInfoList();

	// pop front Element in GuildMemberInfoList
	GuildMemberInfo* popFrontGuildMemberInfoList()
	{
		if ( !m_GuildMemberInfoList.empty() )
		{
			GuildMemberInfo* pGuildMemberInfo = m_GuildMemberInfoList.front();
			m_GuildMemberInfoList.pop_front();
			return pGuildMemberInfo;
		}
		return NULL;
	}
	BYTE getType() const { return m_Type; }
	void setType(BYTE type) { m_Type = type; }

private :
	BYTE m_Type;
	GuildMemberInfoList m_GuildMemberInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberListFactory;
//
// Factory for GCGuildMemberList
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCGuildMemberList(); }

	// get packet name
	std::string getPacketName() const { return "GCGuildMemberList"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_GUILD_MEMBER_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return  szBYTE + GuildMemberInfo::getMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildMemberList;
//
//////////////////////////////////////////////////////////////////////

class GCGuildMemberListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGuildMemberList* pPacket, Player* pPlayer);

};

#endif
