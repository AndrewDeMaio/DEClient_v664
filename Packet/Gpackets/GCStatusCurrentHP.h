//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStatusCurrentHP.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_STATUS_CURRENT_HP_H__
#define __GC_STATUS_CURRENT_HP_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHP;
//
////////////////////////////////////////////////////////////////////

class GCStatusCurrentHP : public Packet {

public :

	GCStatusCurrentHP();

	virtual ~GCStatusCurrentHP();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_STATUS_CURRENT_HP; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize �� ����, �����϶�.
	size_t getPacketSize () const 
	{ 
		return szObjectID + szHP; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCStatusCurrentHP"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif	

public :

	// get/set creature ID 
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) { m_ObjectID = creatureID; }

	// get /set CurrentHP
	HP_t getCurrentHP() const { return m_CurrentHP; }
	void setCurrentHP( HP_t CurrentHP ) { m_CurrentHP = CurrentHP; }

private :
	
    // �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
    ObjectID_t m_ObjectID;

	// ���� ���� ü��
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPFactory;
//
// Factory for GCStatusCurrentHP
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCStatusCurrentHP(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCStatusCurrentHP"; }
	#endif

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_STATUS_CURRENT_HP; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szObjectID + szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPHandler;
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPHandler {

public :

	// execute packet's handler
	static void execute ( GCStatusCurrentHP * pPacket , Player * pPlayer );

};

#endif
