//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRDisconnect.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CR_DISCONNECT_H__
#define __CR_DISCONNECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CRDisconnect;
//
// �ٸ� Ŭ���̾�Ʈ���� ������ ������ ���´�.
//
//////////////////////////////////////////////////////////////////////

class CRDisconnect : public Packet
{

public :
	
	// constructor
	CRDisconnect ();
	
	// destructor
	~CRDisconnect ();
	
public :
    PacketID_t getPacketID () const { return PACKET_CR_DISCONNECT; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CRDisconnect"; }
		
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
	size_t getPacketSize () const { return 0; }
	static PacketSize_t getPacketMaxSize() { return 0;}

protected :

};

//////////////////////////////////////////////////////////////////////
//
// class CRDisconnectFactory;
//
// Factory for CRDisconnect
//
//////////////////////////////////////////////////////////////////////

class CRDisconnectFactory : public PacketFactory {

public :
	
	// constructor
	CRDisconnectFactory () {}
	
	// destructor
	virtual ~CRDisconnectFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new CRDisconnect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRDisconnect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CR_DISCONNECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return 0;}

};


//////////////////////////////////////////////////////////////////////
//
// class CRDisconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class CRDisconnectHandler {

public :

	// execute packet's handler
	static void execute ( CRDisconnect * pCRDisconnect , Player * pPlayer );

};


#endif
