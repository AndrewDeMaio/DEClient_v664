//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPartySay 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_SAY_H__
#define __CG_PARTY_SAY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPartySay; //
//////////////////////////////////////////////////////////////////////

class CGPartySay : public Packet {

public:
	
	// constructor
	CGPartySay();
	
	// destructor
	~CGPartySay();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_PARTY_SAY; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Message.size() + szuint; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGPartySay"; }
	
	// get packet's debug string
	string toString() const;
#endif
public:
	void	setMessage( const string& msg ) { m_Message = msg; }
	const std::string&	getMessage() const { return m_Message; }

	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }
	
private :
	uint	m_Color;
	string	m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGPartySayFactory;
//
// Factory for CGPartySay
//
//////////////////////////////////////////////////////////////////////

class CGPartySayFactory : public PacketFactory {

public:
	
	// constructor
	CGPartySayFactory() {}
	
	// destructor
	virtual ~CGPartySayFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGPartySay(); }

	// get packet name
	string getPacketName() const { return "CGPartySay"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_PARTY_SAY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szBYTE + 128 + szuint; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPartySayHandler {
	
public:

	// execute packet's handler
	static void execute(CGPartySay* pCGPartySay, Player* player);
};

#endif
