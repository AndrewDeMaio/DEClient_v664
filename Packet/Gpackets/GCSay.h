//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSay.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SAY_H__
#define __GC_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCSay;
//
// ���� ������ Ư�� �÷��̾��� Say �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� Say ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCSay : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SAY; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID + szuint + szBYTE + m_Message.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCSay"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set sender's creature id
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID) { m_ObjectID = creatureID; }

	//get/set text color
	uint getColor() const { return m_Color; }
	void setColor( uint color ) { m_Color = color; }

	// get/set chatting message
	const std::string& getMessage() const { return m_Message; }
	void setMessage(const std::string & msg) { m_Message = msg; }
	

private :
	
	// character's creature id
	ObjectID_t m_ObjectID;

	// text color
	uint m_Color;
	
	// chatting message
	std::string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCSayFactory;
//
// Factory for GCSay
//
//////////////////////////////////////////////////////////////////////

class GCSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCSay(); }

	// get packet name
	std::string getPacketName() const { return "GCSay"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSayPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szObjectID + szuint + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSayHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSay* pPacket, Player* pPlayer);

};

#endif
