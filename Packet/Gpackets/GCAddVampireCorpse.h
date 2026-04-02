//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_VAMPIRE_CORPSE_H__
#define __GC_ADD_VAMPIRE_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCAddVampireCorpse;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���, (1) �̹� �� �����̾ ���� ������ ���� �ִ�
// (�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���, (2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampireCorpse ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����, (3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampireCorpse��
// ��Ƽ� �ް� �ȴ�.
//
//----------------------------------------------------------------------

class GCAddVampireCorpse : public Packet {

public :

	// constructor
	GCAddVampireCorpse () { m_TreasureCount = 0; }
	GCAddVampireCorpse ( const PCVampireInfo3 & vampireInfo ) : m_VampireInfo(vampireInfo) {}

	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_VAMPIRE_CORPSE; }
	
	// get packet's body size
	size_t getPacketSize () const { return m_VampireInfo.getSize() + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddVampireCorpse"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get vampire info
	PCVampireInfo3 & getVampireInfo () { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo () const { return m_VampireInfo; }
	void setVampireInfo ( const PCVampireInfo3 & vampireInfo ) { m_VampireInfo = vampireInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount() const { return m_TreasureCount; }
	void setTreasureCount( BYTE Count ) { m_TreasureCount = Count; }
	
private :
	
	// �����̾� �ܸ� ����
	PCVampireInfo3 m_VampireInfo;

	BYTE m_TreasureCount;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseFactory;
//
// Factory for GCAddVampireCorpse
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddVampireCorpse(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddVampireCorpse"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_VAMPIRE_CORPSE; }

	// get packet's body size
	PacketSize_t getPacketMaxSize () const { return PCVampireInfo3::getMaxSize() + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseHandler {

public :

	// execute packet's handler
	static void execute ( GCAddVampireCorpse * pPacket , Player * pPlayer );

};

#endif
