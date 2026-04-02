//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRConnect.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CR_CONNECT_H__
#define __CR_CONNECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CRConnect;
//
// Ŭ���̾�Ʈ���� �ٸ� Ŭ���̾�Ʈ�� ������ ��û�ϴ°Ŵ�.
//
// �ڱ� ĳ���� �̸��� ����� ĳ���� �̸��� �˾ƾ� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class CRConnect : public Packet
{

public :
	
	// constructor
	CRConnect ();
	
	// destructor
	~CRConnect ();
	
public :
    PacketID_t getPacketID () const { return PACKET_CR_CONNECT; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CRConnect"; }
		
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
	size_t getPacketSize () const { return szBYTE + m_RequestServerName.size() + szBYTE + m_RequestClientName.size(); }
	static PacketSize_t getPacketMaxSize() { return  szBYTE + 10 + szBYTE + 10;}

	// get / set ListNumber
	const std::string& getRequestServerName() const { return m_RequestServerName; }
	void setRequestServerName(const char* pName) { m_RequestServerName = pName; }

	const std::string& getRequestClientName() const { return m_RequestClientName; }
	void setRequestClientName(const char* pName) { m_RequestClientName = pName; }
	

protected :
	
	std::string		m_RequestServerName;
	std::string		m_RequestClientName;
};

//////////////////////////////////////////////////////////////////////
//
// class CRConnectFactory;
//
// Factory for CRConnect
//
//////////////////////////////////////////////////////////////////////

class CRConnectFactory : public PacketFactory {

public :
	
	// constructor
	CRConnectFactory () {}
	
	// destructor
	virtual ~CRConnectFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new CRConnect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRConnect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CR_CONNECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return  szBYTE + 10 + szBYTE + 10; }

};


//////////////////////////////////////////////////////////////////////
//
// class CRConnectHandler;
//
//////////////////////////////////////////////////////////////////////

class CRConnectHandler {

public :

	// execute packet's handler
	static void execute ( CRConnect * pCRConnect , Player * pPlayer );

};


#endif
