//--------------------------------------------------------------------------------
// 
// Filename    : GCRankBonusInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_RANK_BONUS_INFO_H__
#define __GC_RANK_BONUS_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

const DWORD EndOfRankBonus = 9999;


class GCRankBonusInfo : public Packet {

public :

	// constructor
	GCRankBonusInfo();

	// destructor
	~GCRankBonusInfo();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_RANK_BONUS_INFO; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + ( szDWORD * m_RankBonusInfoList.size() ); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCRankBonusInfo"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	BYTE getListNum() const { return m_RankBonusInfoList.size(); }

    // add
	void addListElement( DWORD rankBonusType ) { m_RankBonusInfoList.push_back( rankBonusType ); }
	
	// pop front Element in Status List
	DWORD popFrontListElement()
	{
		if ( !m_RankBonusInfoList.empty() )
		{
			DWORD temp = m_RankBonusInfoList.front();
			m_RankBonusInfoList.pop_front();
			return temp;
		}
		else
			return EndOfRankBonus;
	}

private :

	// Rank Bonus List
	std::list<DWORD> m_RankBonusInfoList;

};


//--------------------------------------------------------------------------------
//
// class GCRankBonusInfoFactory;
//
// Factory for GCRankBonusInfo
//
//--------------------------------------------------------------------------------

class GCRankBonusInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCRankBonusInfo(); }

	// get packet name
	std::string getPacketName() const { return "GCRankBonusInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_RANK_BONUS_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRankBonusInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szBYTE + ( szDWORD * 100 );
	}

};


//--------------------------------------------------------------------------------
//
// class GCRankBonusInfoHandler;
//
//--------------------------------------------------------------------------------

class GCRankBonusInfoHandler {

public :

	// execute packet's handler
	static void execute(GCRankBonusInfo* pPacket, Player* pPlayer);

};

#endif
