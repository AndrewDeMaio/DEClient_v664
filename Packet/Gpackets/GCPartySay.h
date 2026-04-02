//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPartySay.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_SAY_H__
#define __GC_PARTY_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPartySay;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPartySay : public Packet
{
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_PARTY_SAY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize �� ����, �����϶�.
	size_t getPacketSize() const { return szBYTE + m_Name.size() + szBYTE + m_Message.size() + szuint; }

#ifdef __DEBUG_OUTPUT__
	// get packet's name
	string getPacketName() const { return "GCPartySay"; }
	
	// get packet's debug string
	string toString() const;
#endif

public :
	const std::string&	getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	const std::string&	getMessage() const { return m_Message; }
	void	setMessage( const string& msg ) { m_Message = msg; }

	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

private :
	string	m_Name;
	uint	m_Color;
	string	m_Message;
};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayFactory;
//
// Factory for GCPartySay
//
//////////////////////////////////////////////////////////////////////

class GCPartySayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCPartySay(); }

	// get packet name
	string getPacketName() const { return "GCPartySay"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_PARTY_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 20 + szBYTE + 128 + szuint; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPartySayHandler {

public :

	// execute packet's handler
	static void execute(GCPartySay* pPacket, Player* pPlayer);

};

#endif
