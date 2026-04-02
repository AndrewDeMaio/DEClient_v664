//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPhoneSay.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PHONE_SAY_H__
#define __CG_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSay;
//
// Ŭ���̾�Ʈ�� �������� ������ PhoneSay ��Ŷ�̴�.
// ���ο� PhoneSay String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSay : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_PHONE_SAY; }
	
	// get packet's body size
	size_t getPacketSize () const { return szSlotID + szBYTE + m_Message.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGPhoneSay"; }
		
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
// class CGPhoneSayFactory;
//
// Factory for CGPhoneSay
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGPhoneSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGPhoneSay(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGPhoneSay"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_PHONE_SAY; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize () const { return szSlotID + szBYTE + 128; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGPhoneSayHandler {

	public :

		// execute packet's handler
		static void execute ( CGPhoneSay * pPacket , Player * pPlayer );

	};
#endif

#endif
