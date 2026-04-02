//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMoveError.h 
// Written By  : Elca
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MOVEError_H__
#define __GC_MOVEError_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMoveError;
//
//////////////////////////////////////////////////////////////////////

class GCMoveError : public Packet {

public :

	// constructor
	GCMoveError () {}
	GCMoveError ( Coord_t x , Coord_t y ) : m_X(x), m_Y(y) {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_MOVE_ERROR; }
	
	// get packet's body size
	size_t getPacketSize () const { return szCoord + szCoord; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCMoveError"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	

public :

	// get/set X
	Coord_t getX() const { return m_X; }
	void setX( Coord_t x) { m_X = x; }
	
	// get/set Y
	Coord_t getY() const { return m_Y; }
	void setY( Coord_t y) { m_Y = y ; }


private : 

	Coord_t m_X;   // ���� X ��ǥ
	Coord_t m_Y;   // ���� Y ��ǥ

};


//////////////////////////////////////////////////////////////////////
//
// class  GCMoveErrorFactory;
//
// Factory for  GCMoveError
//
//////////////////////////////////////////////////////////////////////

class  GCMoveErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCMoveError(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCMoveError"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_MOVE_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szCoord + szCoord; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCMoveErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCMoveErrorHandler {

public :

	// execute packet's handler
	static void execute ( GCMoveError * pPacket , Player * pPlayer );

};

#endif
