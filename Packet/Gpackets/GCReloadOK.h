//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReloadOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RELOAD_OK_H__
#define __GC_RELOAD_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOK;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOK : public Packet {

public :

	// Constructor
	GCReloadOK();

	// Desctructor
	~GCReloadOK();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_RELOAD_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szBullet; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReloadOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set BulletNum
	Bullet_t getBulletNum() const { return m_BulletNum; }
	void setBulletNum( Bullet_t BulletNum ) { m_BulletNum = BulletNum; }
	

private :
	
	// BulletNum
	Bullet_t m_BulletNum;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKFactory;
//
// Factory for GCReloadOK
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCReloadOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCReloadOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_RELOAD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szBullet; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GCReloadOK * pPacket , Player * player );
};

#endif
