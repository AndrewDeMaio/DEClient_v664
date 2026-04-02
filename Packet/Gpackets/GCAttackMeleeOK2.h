//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackMeleeOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_MELEE_OK_2_H__
#define __GC_ATTACK_MELEE_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2 : public ModifyInfo {

public :
	
	// constructor
	GCAttackMeleeOK2 ();
	
	// destructor
	~GCAttackMeleeOK2 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ATTACK_MELEE_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + ModifyInfo::getPacketSize() + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAttackMeleeOK2"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set CEffectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	BYTE getActionStep() const { return m_ActionStep;		}
	void setActionStep(BYTE actionStep) { m_ActionStep = actionStep; }

private :
	
	// ObjectID
	ObjectID_t	m_ObjectID;

	BYTE		m_ActionStep;
};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2Factory;
//
// Factory for GCAttackMeleeOK2
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackMeleeOK2Factory () {}
	
	// destructor
	virtual ~GCAttackMeleeOK2Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCAttackMeleeOK2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAttackMeleeOK2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ATTACK_MELEE_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + ModifyInfo::getPacketMaxSize() + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2Handler {

public :

	// execute packet's handler
	static void execute ( GCAttackMeleeOK2 * pGCAttackMeleeOK2 , Player * pPlayer );

};

#endif
