//////////////////////////////////////////////////////////////////////
// 
// Filename    : RCConnectVerify.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __RC_CONNECT_VERIFY_H__
#define __RC_CONNECT_VERIFY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class RCConnectVerify;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// RemoveEffectrmation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////
enum RC_CONNECT_VERIFY_CODE
{
	RC_CONNECT_NULL,			// �߸��� ��

	RC_CONNECT_OK,				// ���
	RC_CONNECT_REJECT,			// �ź� - -; 
	RC_CONNECT_WRONG,			// �߸��� ����(RequestServerName�� �ٸ��ٴ���..)
};

class RCConnectVerify : public Packet
{

public :
	
	// constructor
	RCConnectVerify ();
	
	// destructor
	~RCConnectVerify ();
	
public :
    PacketID_t getPacketID () const { return PACKET_RC_CONNECT_VERIFY; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "RCConnectVerify"; }
		
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
	size_t getPacketSize () const { return szBYTE; }
	static PacketSize_t getPacketMaxSize() { return szBYTE;}

	// get / set ListNumber
	RC_CONNECT_VERIFY_CODE	getCode() const { return m_Code; }
	void					setCode( RC_CONNECT_VERIFY_CODE code ) { m_Code = code; }

protected :
	
	RC_CONNECT_VERIFY_CODE		m_Code;

};

//////////////////////////////////////////////////////////////////////
//
// class RCConnectVerifyFactory;
//
// Factory for RCConnectVerify
//
//////////////////////////////////////////////////////////////////////

class RCConnectVerifyFactory : public PacketFactory {

public :
	
	// constructor
	RCConnectVerifyFactory () {}
	
	// destructor
	virtual ~RCConnectVerifyFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new RCConnectVerify(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "RCConnectVerify"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_RC_CONNECT_VERIFY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return 255;}

};


//////////////////////////////////////////////////////////////////////
//
// class RCConnectVerifyHandler;
//
//////////////////////////////////////////////////////////////////////

class RCConnectVerifyHandler {

public :

	// execute packet's handler
	static void execute ( RCConnectVerify * pRCConnectVerify , Player * pPlayer );

};


#endif
