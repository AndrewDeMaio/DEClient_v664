//--------------------------------------------------------------------------------
// 
// Filename    : GCRemoveCorpseHead.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_REMOVE_CORPSE_HEAD_H__
#define __GC_REMOVE_CORPSE_HEAD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCRemoveCorpseHead;
//
// ���� Ư�� ��ü�� �þ߿��� ����� ��쿡 ���۵Ǹ�, Ŭ���̾�Ʈ�� �� ��Ŷ�� ������
// ��Ŷ ������ OID�� ����ؼ� �ش�Ǵ� ��ü�� ã�Ƽ� Ŭ���̾�Ʈ�� ������ �����ؾ� �Ѵ�.
//
// ������ �� ��Ŷ�� ���۵Ǵ� ��ü���� ��Ȳ�� �����̴�.
//
// (1) PC�� �α׾ƿ��� ���
// (2) �������� ũ��ó�� �ݴ� ���
// (3) Ư�� ����Ʈ�� ����� ���
// (4) ��ü�� ����� ���
//
// *CAUTION*
//
// (3) Ư�� ����Ʈ�� ����� ���.. �� ����Ʈ�� ������ ��, ������� �ð��� ���۵Ǳ�
// ������, �����Ǿ ������ ���̴�. -_-;
//
//--------------------------------------------------------------------------------

class GCRemoveCorpseHead : public Packet {

public :

	// constructor
	GCRemoveCorpseHead ()
	{
	}

	GCRemoveCorpseHead ( ObjectID_t objectID )
		: m_ObjectID(objectID)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_REMOVE_CORPSE_HEAD; }
	
	// get packet's body size
	size_t getPacketSize () const 
	{ 
		return szObjectID; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRemoveCorpseHead"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

public :

	// get/set object id
	ObjectID_t getObjectID () const { return m_ObjectID; }
	void setObjectID ( ObjectID_t objectID ) { m_ObjectID = objectID; }

private :

	// object id
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveCorpseHeadFactory;
//
// Factory for GCRemoveCorpseHead
//
//////////////////////////////////////////////////////////////////////

class GCRemoveCorpseHeadFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCRemoveCorpseHead(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCRemoveCorpseHead"; }
	#endif	

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_REMOVE_CORPSE_HEAD; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szObjectID; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveCorpseHeadHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveCorpseHeadHandler {

public :

	// execute packet's handler
	static void execute ( GCRemoveCorpseHead * pPacket , Player * player );

};

#endif
