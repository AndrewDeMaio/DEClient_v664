//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCrossCounterOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CROSS_COUNTER_OK_2_H__
#define __GC_CROSS_COUNTER_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2 : public ModifyInfo {

public :
	
	// constructor
	GCCrossCounterOK2 ();
	
	// destructor
	~GCCrossCounterOK2 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_CROSS_COUNTER_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + ModifyInfo::getPacketSize() + szSkillType; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCCrossCounterOK2"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set CEffectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t SkillType ) { m_SkillType = SkillType; }
	

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2Factory;
//
// Factory for GCCrossCounterOK2
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCCrossCounterOK2Factory () {}
	
	// destructor
	virtual ~GCCrossCounterOK2Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCCrossCounterOK2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCCrossCounterOK2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_CROSS_COUNTER_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szObjectID + ModifyInfo::getPacketMaxSize() + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2Handler {

public :

	// execute packet's handler
	static void execute ( GCCrossCounterOK2 * pGCCrossCounterOK2 , Player * pPlayer );

};

#endif
