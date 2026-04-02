//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneSay.h 
// Written By  : elca 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_SAY_H__
#define __GC_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSay;
//
// ���� ������ Ư�� �÷��̾��� PhoneSay �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸��� PhoneSay ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSay : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_PHONE_SAY; }
	
	// get packet's body size
	size_t getPacketSize () const { return szSlotID + szBYTE + m_Message.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCPhoneSay"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get/set SlotID
	SlotID_t getSlotID() const { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) { m_SlotID = SlotID; }

	// get/set chatting message
	const std::string& getMessage () const { return m_Message; }
	void setMessage ( const std::string & msg ) { m_Message = msg; }
	

private :

	// SlotID
	SlotID_t m_SlotID;
	
	// chatting message
	std::string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayFactory;
//
// Factory for GCPhoneSay
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCPhoneSay(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCPhoneSay"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_PHONE_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPhoneSayPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const { return szSlotID + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayHandler {
	
public :
	
	// execute packet's handler
	static void execute ( GCPhoneSay * pPacket , Player * pPlayer );

};

#endif
