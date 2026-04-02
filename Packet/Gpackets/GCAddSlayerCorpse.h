//----------------------------------------------------------------------
// 
// Filename    : GCAddSlayerCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_SLAYER_CORPSE_H__
#define __GC_ADD_SLAYER_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"

//----------------------------------------------------------------------
//
// class GCAddSlayerCorpse;
//
// �����̾��� ��ü ������ ��Ƽ� Ŭ���̾�Ʈ�� �����Ѵ�.
//
//----------------------------------------------------------------------

class GCAddSlayerCorpse : public Packet {

public :

	// constructor
	GCAddSlayerCorpse () { m_TreasureCount = 0; }
	GCAddSlayerCorpse ( const PCSlayerInfo3 & slayerInfo ) : m_SlayerInfo(slayerInfo) {}


public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_SLAYER_CORPSE; }
	
	// get packet's body size
	size_t getPacketSize () const { return m_SlayerInfo.getSize() + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddSlayerCorpse"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get slayer info
	PCSlayerInfo3 & getSlayerInfo () { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo () const { return m_SlayerInfo; }
	void setSlayerInfo ( const PCSlayerInfo3 & slayerInfo ) { m_SlayerInfo = slayerInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount() const { return m_TreasureCount; }
	void setTreasureCount( BYTE Count ) { m_TreasureCount = Count; }

private :
	
	// �����̾��� �ܸ� ����
	PCSlayerInfo3 m_SlayerInfo;

	// ���� ����
	BYTE m_TreasureCount;

};


//--------------------------------------------------------------------------------
//
// class GCAddSlayerCorpseFactory;
//
// Factory for GCAddSlayerCorpse
//
//--------------------------------------------------------------------------------

class GCAddSlayerCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddSlayerCorpse(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddSlayerCorpse"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_SLAYER_CORPSE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddSlayerCorpsePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const
	{ 
		return PCSlayerInfo3::getMaxSize() + szBYTE;
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddSlayerCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddSlayerCorpseHandler {

public :

	// execute packet's handler
	static void execute ( GCAddSlayerCorpse * pPacket , Player * pPlayer );

};

#endif
