//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRRequest.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CR_REQUEST_H__
#define __CR_REQUEST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

enum CR_REQUEST_CODE
{
	CR_REQUEST_NULL,

	// ������ ���� ����.. ����.. - -;
	CR_REQUEST_FILE_GUILD_MARK,
	CR_REQUEST_FILE_PROFILE,
};

//////////////////////////////////////////////////////////////////////
//
// class CRRequest;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// RemoveEffectrmation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////
class CRRequest : public Packet
{

public :
	
	// constructor
	CRRequest ();
	
	// destructor
	~CRRequest ();
	
public :
    PacketID_t getPacketID () const { return PACKET_CR_REQUEST; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const { return "CRRequest"; }
		
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
	size_t getPacketSize () const { return szBYTE + szBYTE + m_RequestName.size(); }
	static PacketSize_t getPacketMaxSize() { return szBYTE + szBYTE + 20;}

	// get / set ListNumber
	CR_REQUEST_CODE getCode() const { return m_Code; }
	void setCode( CR_REQUEST_CODE code) { m_Code = code; }

	const std::string& getRequestName() const { return m_RequestName; }
	void setRequestName(const char* pName) { m_RequestName = pName; }

protected :
	
	CR_REQUEST_CODE		m_Code;

	std::string				m_RequestName;
};

//////////////////////////////////////////////////////////////////////
//
// class CRRequestFactory;
//
// Factory for CRRequest
//
//////////////////////////////////////////////////////////////////////

class CRRequestFactory : public PacketFactory {

public :
	
	// constructor
	CRRequestFactory () {}
	
	// destructor
	virtual ~CRRequestFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new CRRequest(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CRRequest"; }
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

class CRRequestHandler {

public :

	// execute packet's handler
	static void execute ( CRRequest * pCRRequest , Player * pPlayer );

};


#endif
