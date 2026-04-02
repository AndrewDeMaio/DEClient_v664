//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveEffect.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __REMOVE_EFFECT_H__
#define __REMOVE_EFFECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffect;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// RemoveEffectrmation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffect : public Packet
{

public :
	
	// constructor
	GCRemoveEffect ();
	
	// destructor
	~GCRemoveEffect ();
	
public :
    PacketID_t getPacketID () const { return PACKET_GC_REMOVE_EFFECT; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "GCRemoveEffect"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;
	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szObjectID + szBYTE + szEffectID * m_ListNum; }
	static PacketSize_t getPacketMaxSize() { return 255;}

	// get / set ListNumber
	BYTE getListNum() const { return m_ListNum; }
	void setListNum( BYTE ListNum ) { m_ListNum = ListNum; }

	// get&set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID;}
	void setObjectID( ObjectID_t id) { m_ObjectID = id;}

	// add / delete / clear S List
	void addEffectList( EffectID_t id ); 

	// ClearList
	void clearList() { m_EffectList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	WORD popFrontListElement() { EffectID_t effectID = m_EffectList.front(); m_EffectList.pop_front(); return effectID; }

protected :
	
	ObjectID_t m_ObjectID;
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	std::list<EffectID_t> m_EffectList;

};

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffectFactory;
//
// Factory for GCRemoveEffect
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffectFactory : public PacketFactory {

public :
	
	// constructor
	GCRemoveEffectFactory () {}
	
	// destructor
	virtual ~GCRemoveEffectFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCRemoveEffect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRemoveEffect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_REMOVE_EFFECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return 255;}

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffectHandler {

public :

	// execute packet's handler
	static void execute ( GCRemoveEffect * pGCRemoveEffect , Player * pPlayer );

};


#endif
