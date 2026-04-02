//////////////////////////////////////////////////////////////////////
// 
// Filename    : RCRequestVerify.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __RC_REQUEST_VERIFY_H__
#define __RC_REQUEST_VERIFY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

enum REQUEST_VERIFY
{
	REQUEST_VERIFY_NULL,
	REQUEST_VERIFY_WHISPER_FAILED,
	REQUEST_VERIFY_PROFILE_NOT_EXIST,		// profile�� �ƿ� ���� ���
	REQUEST_VERIFY_PROFILE_WRONG_USER,		// �߸��� ����ڿ��� ��û�� ���
	REQUEST_VERIFY_PROFILE_DONE,			// profile �� ���´�.
};

//////////////////////////////////////////////////////////////////////
//
// class RCRequestVerify;
//
//////////////////////////////////////////////////////////////////////

class RCRequestVerify : public Packet {

public :
	
	// constructor
	RCRequestVerify ();
	
	// destructor
	~RCRequestVerify ();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_RC_REQUEST_VERIFY; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "RCRequestVerify"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	REQUEST_VERIFY getCode() const { return m_Code ; }
	void setCode ( REQUEST_VERIFY code ) { m_Code = code ; }


private :
	REQUEST_VERIFY		m_Code;

};

//////////////////////////////////////////////////////////////////////
//
// class RCRequestVerifyFactory;
//
// Factory for RCRequestVerify
//
//////////////////////////////////////////////////////////////////////

class RCRequestVerifyFactory : public PacketFactory {

public :
	
	// constructor
	RCRequestVerifyFactory () {}
	
	// destructor
	virtual ~RCRequestVerifyFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new RCRequestVerify(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "RCRequestVerify"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_RC_REQUEST_VERIFY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class RCRequestVerifyHandler;
//
//////////////////////////////////////////////////////////////////////

class RCRequestVerifyHandler {

public :

	// execute packet's handler
	static void execute ( RCRequestVerify * pRCRequestVerify , Player * pPlayer );

};

#endif
