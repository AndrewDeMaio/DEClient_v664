//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRRequest.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CR_REQUEST2_H__
#define __CR_REQUEST2_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"

enum CR_REQUEST_CODE2
{
	CR_REQUEST2_NULL,

	// ������ ���� ����.. ����.. - -;
	CR_REQUEST2_CHARACTER_INFO,
};

//////////////////////////////////////////////////////////////////////
//
// class CRRequest;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// RemoveEffectrmation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////
class CRRequest2 : public DatagramPacket
{

public :
	
	// constructor
	CRRequest2 ();
	
	// destructor
	~CRRequest2 ();
	
public :
    PacketID_t getPacketID () const { return PACKET_CR_REQUEST; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CRRequest2"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Datagram & iDatagram );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( Datagram & oDatagram ) const;
	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return szBYTE + szBYTE + m_RequestName.size(); }
	static PacketSize_t getPacketMaxSize() { return szBYTE + szBYTE + 20;}

	// get / set ListNumber
	CR_REQUEST_CODE2 getCode() const { return m_Code; }
	void setCode( CR_REQUEST_CODE2 code) { m_Code = code; }

	const std::string& getRequestName() const { return m_RequestName; }
	void setRequestName(const char* pName) { m_RequestName = pName; }

protected :
	
	CR_REQUEST_CODE2	m_Code;

	std::string				m_RequestName;
};

//////////////////////////////////////////////////////////////////////
//
// class CRRequestFactory;
//
// Factory for CRRequest
//
//////////////////////////////////////////////////////////////////////

class CRRequest2Factory : public PacketFactory {

public :
	
	// constructor
	CRRequest2Factory () {}
	
	// destructor
	virtual ~CRRequest2Factory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new CRRequest2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRRequest2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CR_REQUEST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const { return szBYTE + szBYTE + 20;}

};


//////////////////////////////////////////////////////////////////////
//
// class CRRequestHandler;
//
//////////////////////////////////////////////////////////////////////

class CRRequest2Handler {

public :

	// execute packet's handler
	static void execute ( CRRequest2 * pCRRequest );

};


#endif
