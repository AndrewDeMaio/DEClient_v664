//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDialUp.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DIAL_UP_H__
#define __CG_DIAL_UP_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGDialUp;
//
//////////////////////////////////////////////////////////////////////

class CGDialUp : public Packet {
public :

	// constructor
	CGDialUp();

	// destructor
	~CGDialUp();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_DIAL_UP; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGDialUpPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szPhoneNumber; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGDialUp"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set phoneNumber
	PhoneNumber_t getPhoneNumber() const { return m_PhoneNumber; }
	void setPhoneNumber( PhoneNumber_t PhoneNumber ) { m_PhoneNumber = PhoneNumber; }

private :
	
	// SlotID
	PhoneNumber_t m_PhoneNumber;

};


//////////////////////////////////////////////////////////////////////
//
// class CGDialUpFactory;
//
// Factory for CGDialUp
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGDialUpFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGDialUp(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGDialUp"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_DIAL_UP; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGDialUpPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szPhoneNumber; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGDialUpHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGDialUpHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGDialUp * pPacket , Player * player );
	};
#endif

#endif
