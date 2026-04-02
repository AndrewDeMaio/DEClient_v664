//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryEnd.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MP_RECOVERY_END_H__
#define __GC_MP_RECOVERY_END_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEnd;
//
////////////////////////////////////////////////////////////////////

class GCMPRecoveryEnd : public Packet {

public :

	GCMPRecoveryEnd();

	virtual ~GCMPRecoveryEnd();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_MP_RECOVERY_END; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize �� ����, �����϶�.
	size_t getPacketSize () const 
	{ 
		return szMP; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCMPRecoveryEnd"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get /set CurrentMP
	MP_t getCurrentMP() const { return m_CurrentMP; }
	void setCurrentMP( MP_t CurrentMP ) { m_CurrentMP = CurrentMP; }

private :
	
	// ���� ü��
	MP_t m_CurrentMP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndFactory;
//
// Factory for GCMPRecoveryEnd
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCMPRecoveryEnd(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCMPRecoveryEnd"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_MP_RECOVERY_END; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szMP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndHandler {

public :

	// execute packet's handler
	static void execute ( GCMPRecoveryEnd * pPacket , Player * pPlayer );

};

#endif
