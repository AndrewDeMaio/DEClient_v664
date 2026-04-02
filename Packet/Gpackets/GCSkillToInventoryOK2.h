//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_INVENTORY_OK_2_H__
#define __GC_SKILL_TO_INVENTORY_OK_2_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2 : public Packet {

public :
	
	// constructor
	GCSkillToInventoryOK2 ();
	
	// destructor
	~GCSkillToInventoryOK2 ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_SKILL_TO_INVENTORY_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szSkillType + szObjectID + szDuration; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCSkillToInventoryOK2"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ObjectID 
	CEffectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t SkillType ) { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration() const { return m_Duration; }
	void setDuration ( Duration_t Duration ) { m_Duration = Duration; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Factory;
//
// Factory for GCSkillToInventoryOK2
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToInventoryOK2Factory () {}
	
	// destructor
	virtual ~GCSkillToInventoryOK2Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCSkillToInventoryOK2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCSkillToInventoryOK2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_SKILL_TO_INVENTORY_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szSkillType + szObjectID + szDuration; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Handler {

public :

	// execute packet's handler
	static void execute ( GCSkillToInventoryOK2 * pGCSkillToInventoryOK2 , Player * pPlayer );

};

#endif
