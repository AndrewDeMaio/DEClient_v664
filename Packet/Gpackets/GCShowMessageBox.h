//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowMessageBox.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_MESSAGE_BOX_H__
#define __GC_SHOW_MESSAGE_BOX_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBox : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SHOW_MESSAGE_BOX; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + m_Message.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCShowMessageBox"; }
	
	// get packet's debug std::string
	std::string toString() const;
#endif

	// get/set Message
	const std::string& getMessage() const { return m_Message; }
	void setMessage( const std::string& message ) { m_Message = message; }
	

private :
	
	// Message
	std::string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBoxFactory;
//
// Factory for GCShowMessageBox
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() { return new GCShowMessageBox(); }

	// get packet name
	std::string getPacketName() const { return "GCShowMessageBox"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SHOW_MESSAGE_BOX; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + 256; }

};

//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowMessageBox* pPacket, Player* pPlayer);

};

#endif
