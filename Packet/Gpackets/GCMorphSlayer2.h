//----------------------------------------------------------------------
// 
// Filename    : GCMorphSlayer2.h 
// Written By  : crazydog
// 
//----------------------------------------------------------------------

#ifndef __GC_MORPH_SLAYER2_H__
#define __GC_MORPH_SLAYER2_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCMorphSlayer2;
//
// slayer���� vampire�� �����ϴ� �� ���Ѻ��� �е鿡�� ������.
//----------------------------------------------------------------------

class GCMorphSlayer2 : public Packet {

public :

	// constructor
	GCMorphSlayer2 () {}
	GCMorphSlayer2 ( PCSlayerInfo3 info ) : m_SlayerInfo3(info) {}
	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_MORPH_SLAYER_2; }
	
	// get packet's body size
	size_t getPacketSize () const { return m_SlayerInfo3.getSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCMorphSlayer2"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set vampire info
	const PCSlayerInfo3& getSlayerInfo () { return m_SlayerInfo3; }
	void setSlayerInfo ( PCSlayerInfo3  info ) { m_SlayerInfo3 = info; }


private :
	
	// �ܸ� ����
	PCSlayerInfo3 m_SlayerInfo3;
	
};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Factory;
//
// Factory for GCMorphSlayer2
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Factory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCMorphSlayer2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCMorphSlayer2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_MORPH_SLAYER_2; }

	// get packet's body size
	PacketSize_t getPacketMaxSize () const
	{ 
		return PCSlayerInfo3::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Handler;
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Handler {

public :

	// execute packet's handler
	static void execute ( GCMorphSlayer2 * pPacket , Player * pPlayer );

};

#endif
