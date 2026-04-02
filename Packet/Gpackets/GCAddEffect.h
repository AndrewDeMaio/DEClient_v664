//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddEffect.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_H__
#define __GC_ADD_EFFECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAddEffect;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAddEffect : public Packet {

public :
	
	// constructor
	GCAddEffect ();
	
	// destructor
	~GCAddEffect ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_EFFECT; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szBYTE + szEffectID + szTurn; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddEffect"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set EffectID 
	EffectID_t getEffectID() const { return m_EffectID; }
	void setEffectID( EffectID_t e ) { m_EffectID = e; }
	
	// get / set ObjectID 
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t o ) { m_ObjectID = o; }

	// get / set ObjectID 
	Turn_t getDuration() const { return m_Duration; }
	void setDuration( Turn_t d ) { m_Duration = d; }
	
private :
	
	ObjectID_t m_ObjectID;

	EffectID_t	m_EffectID;
	Turn_t		m_Duration;
};


//////////////////////////////////////////////////////////////////////
//
// class GCAddEffectFactory;
//
// Factory for GCAddEffect
//
//////////////////////////////////////////////////////////////////////

class GCAddEffectFactory : public PacketFactory {

public :
	
	// constructor
	GCAddEffectFactory () {}
	
	// destructor
	virtual ~GCAddEffectFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCAddEffect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddEffect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_EFFECT; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize() const { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE * m_ListNum * 2 ; }
	PacketSize_t getPacketMaxSize() const { return szObjectID + szEffectID + szTurn; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddEffectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddEffectHandler {

public :

	// execute packet's handler
	static void execute ( GCAddEffect * pGCAddEffect , Player * pPlayer );

};

#endif
