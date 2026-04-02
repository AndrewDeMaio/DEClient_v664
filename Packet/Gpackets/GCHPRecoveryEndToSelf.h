//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToSelf.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_END_TO_SELF_H__
#define __GC_HP_RECOVERY_END_TO_SELF_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelf;
//
////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelf : public Packet {

public :

	GCHPRecoveryEndToSelf();

	virtual ~GCHPRecoveryEndToSelf();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_HP_RECOVERY_END_TO_SELF; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize �� ����, �����϶�.
	size_t getPacketSize () const 
	{ 
		return szHP; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCHPRecoveryEndToSelf"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get /set CurrentHP
	HP_t getCurrentHP() const { return m_CurrentHP; }
	void setCurrentHP( HP_t CurrentHP ) { m_CurrentHP = CurrentHP; }

private :
	
	// ���� ü��
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfFactory;
//
// Factory for GCHPRecoveryEndToSelf
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCHPRecoveryEndToSelf(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCHPRecoveryEndToSelf"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_HP_RECOVERY_END_TO_SELF; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfHandler {

public :

	// execute packet's handler
	static void execute ( GCHPRecoveryEndToSelf * pPacket , Player * pPlayer );

};

#endif
