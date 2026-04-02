//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCUntransformOK.h 
// Written By  :  Elca
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNTRANSFORM_OK_H__
#define __GC_UNTRANSFORM_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOK;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�. (CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCUntransformOK : public Packet {

public :

	// constructor
	GCUntransformOK () {}
	GCUntransformOK ( Coord_t x , Coord_t y , Dir_t dir ) : m_X(x), m_Y(y), m_Dir(dir) {}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_UNTRANSFORM_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize �� ����, �����϶�.
	size_t getPacketSize () const { return szCoord + szCoord + szDir; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCUntransformOK"; }
		
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

	// get/set Dir
	Dir_t getDir() const { return m_Dir; }
	void setDir( Dir_t dir) { m_Dir = dir; }
	

private : 

	Coord_t m_X;   // ��ǥ X ��ǥ
	Coord_t m_Y;   // ��ǥ Y ��ǥ
	Dir_t m_Dir;   // ��ǥ ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCUntransformOKFactory;
//
// Factory for GCUntransformOK
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCUntransformOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCUntransformOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_UNTRANSFORM_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szCoord + szCoord + szDir; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKHandler {

public :

	// execute packet's handler
	static void execute (  GCUntransformOK * pPacket , Player * pPlayer );

};

#endif
