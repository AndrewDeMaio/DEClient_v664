//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseBonusPointOK.h 
// Written By  : crazydog
// Description : vamp�� bonus����� �㰡 �޴�.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_BONUS_POINT_OK_H__
#define __GC_USE_BONUS_POINT_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOK : public ModifyInfo {

public :

	// Constructor
	GCUseBonusPointOK();

	// Desctructor
	~GCUseBonusPointOK();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_USE_BONUS_POINT_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseBonusPointOKPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUseBonusPointOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOKFactory;
//
// Factory for GCUseBonusPointOK
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCUseBonusPointOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUseBonusPointOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_USE_BONUS_POINT_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseBonusPointOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GCUseBonusPointOK * pPacket , Player * player );
};

#endif
