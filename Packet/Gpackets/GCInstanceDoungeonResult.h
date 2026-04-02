//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCInstanceDoungeonResult.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_INSTANCEDOUNGEON_RESULT_H__
#define __GC_INSTANCEDOUNGEON_RESULT_H__

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildInfo.h"

typedef std::list<GuildInfo*> GuildInfoList;
typedef std::list<GuildInfo*>::const_iterator GuildInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResult;
//
// Ŭ���̾�Ʈ�� ��� ������� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////
#if __CONTENTS(__TIPOJYU_CASTLE)
class GCInstanceDoungeonResult : public Packet {

public :

	// constructor
	GCInstanceDoungeonResult();

	// destructor
	~GCInstanceDoungeonResult();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_INSTANCEDOUNGEON_RESULT; }
	
	// get packet's body size
	size_t getPacketSize() const;

	// get packet name
	string getPacketName() const { return "GCInstanceDoungeonResult"; }
	
	// get packet's debug string
	string toString() const;
	
	DWORD	getExp()		const{ return m_ExpBonus; }
	DWORD	getRankExp()	const{ return m_RankExpBonus; }
	WORD	getRemainTime()	const{ return m_RemainTime; }
	string	getTitleName()	const{ return m_strDoungeonTitle; }

public:


private :
	
	string m_strDoungeonTitle;
	
	Exp_t m_ExpBonus;
	RankExp_t m_RankExpBonus;
	Duration_t m_RemainTime;
};


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResultFactory;
//
// Factory for GCInstanceDoungeonResult
//
//////////////////////////////////////////////////////////////////////

class GCInstanceDoungeonResultFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCInstanceDoungeonResult(); }

	// get packet name
	string getPacketName() const { return "GCInstanceDoungeonResult"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_INSTANCEDOUNGEON_RESULT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 200 + szExp + szRankExp + szDuration; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResult;
//
//////////////////////////////////////////////////////////////////////

class GCInstanceDoungeonResultHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCInstanceDoungeonResult* pPacket, Player* pPlayer);

};
#endif // __TIPOJYU_CASTLE
#endif
