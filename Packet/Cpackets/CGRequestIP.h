//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestIP.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_IP_H__
#define __CG_REQUEST_IP_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestIP;
//
// client���� server�� �������� IP�� ��û�ϴµ�
// �������� ��ó�� �ִٸ� objectID�� ��û�ϰ�
// �ƴϸ�.. ĳ���� �̸����� ��û�Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class CGRequestIP : public Packet
{

public :
	
	// constructor
	CGRequestIP ();
	
	// destructor
	~CGRequestIP ();
	
public :
    PacketID_t getPacketID () const { return PACKET_CG_REQUEST_IP; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CGRequestIP"; }
		
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
	size_t getPacketSize () const { return szBYTE + m_Name.size(); }
	static PacketSize_t getPacketMaxSize() { return szBYTE + 10;}

	// get&set ObjectID
	const std::string& getName() const { return m_Name; }
	void setName( const char* pName) { m_Name = pName;}


protected :
	

	std::string			m_Name;

};

//////////////////////////////////////////////////////////////////////
//
// class CGRequestIPFactory;
//
// Factory for CGRequestIP
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGRequestIPFactory : public PacketFactory {

public :
	
	// constructor
	CGRequestIPFactory () {}
	
	// destructor
	virtual ~CGRequestIPFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new CGRequestIP(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGRequestIP"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_REQUEST_IP; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szBYTE + 10;}

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGRequestIPHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestIPHandler {

public :

	// execute packet's handler
	static void execute ( CGRequestIP * pCGRequestIP , Player * pPlayer );

};


#endif
