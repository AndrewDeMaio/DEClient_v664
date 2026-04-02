//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGLogout.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_LOGOUT_H__
#define __CG_LOGOUT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGLogout;
//
// Ŭ���̾�Ʈ�� �������� �α׾ƿ��� �˸��� ��Ŷ�̴�.
// data field �� ���� ������ getSize()�� 0 �� �����ϸ�, read(), write() 
// �޽��� �ƹ��� ���ҵ� ���� �ʴ´�.
//
//////////////////////////////////////////////////////////////////////

class CGLogout : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_LOGOUT; }
	
	// get packet's body size
	size_t getPacketSize () const { return 0; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGLogout"; }
		
		// get packet's debug std::string
		std::string toString () const { return "CGLogout"; }
	#endif

};


//////////////////////////////////////////////////////////////////////
//
// class CGLogoutFactory;
//
// Factory for CGLogout
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGLogoutFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGLogout(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGLogout"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_LOGOUT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGLogoutHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGLogoutHandler {

	public :

		// execute packet's handler
		static void execute ( CGLogout * pPacket , Player * player );

	};
#endif

#endif
