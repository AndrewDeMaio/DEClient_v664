//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCGetDamage.h 
// Written By  :  elca@ewestsoft.com
// Description :  Ŭ���̾�Ʈ�� ���� CGMove ��Ŷ�� ���� ������ 
//                ���� Ŭ���̾�Ʈ���� �����ص� ���ٴ� �㰡�� ����
//                �����ִ� ��Ŷ Ŭ�����̴�.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_DAMAGE_H__
#define __GC_GET_DAMAGE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamage;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCGetDamage : public Packet {

public :
	
	// constructor
	GCGetDamage ();
	
	// destructor
	~GCGetDamage ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_GET_DAMAGE; }
	
	// get packet size
	size_t getPacketSize () const { return szObjectID + szWORD; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCGetDamage"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
	// get/set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

	// get/set Damage
	WORD getDamage() const { return m_GetDamage; }
	void setDamage( WORD GetDamage ) { m_GetDamage = GetDamage; }
	
private : 
	ObjectID_t m_ObjectID;  // ObjectID..
	WORD m_GetDamage;   		// Damage..

};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageFactory;
//
// Factory for  GCGetDamage
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageFactory : public PacketFactory {

public :
	
	// constructor
	 GCGetDamageFactory () {}
	
	// destructor
	virtual ~GCGetDamageFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCGetDamage(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCGetDamage"; }	
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_GET_DAMAGE; }
	
	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szObjectID + szWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageHandler {

public :

	// execute packet's handler
	static void execute (  GCGetDamage * pGCGetDamage , Player * pPlayer );

};

#endif
