//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackMeleeOK3.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_MELEE_OK_3_H__
#define __GC_ATTACK_MELEE_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK3;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK3 : public Packet {

public :
	
	// constructor
	GCAttackMeleeOK3 ();
	
	// destructor
	~GCAttackMeleeOK3 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ATTACK_MELEE_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAttackMeleeOK3"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	void setTargetObjectID( ObjectID_t TargetObjectID ) { m_TargetObjectID = TargetObjectID; }
	
	BYTE getActionStep() const { return m_ActionStep;		}
	void setActionStep(BYTE ActionStep) { m_ActionStep = ActionStep; }

private :
	
	// ObjectID
	ObjectID_t	m_ObjectID;

	// TargetObjectID
	ObjectID_t	m_TargetObjectID;

	BYTE		m_ActionStep;
};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK3Factory;
//
// Factory for GCAttackMeleeOK3
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackMeleeOK3Factory () {}
	
	// destructor
	virtual ~GCAttackMeleeOK3Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCAttackMeleeOK3(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAttackMeleeOK3"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ATTACK_MELEE_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + szObjectID + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK3Handler {

public :

	// execute packet's handler
	static void execute ( GCAttackMeleeOK3 * pGCAttackMeleeOK3 , Player * pPlayer );

};

#endif
