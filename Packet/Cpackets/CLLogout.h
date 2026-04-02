//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLLogout.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_LOGOUT_H__
#define __CL_LOGOUT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLLogout;
//
// Ŭ���̾�Ʈ�� �������� �α׾ƿ��� �˸��� ��Ŷ�̴�.
// data field �� ���� ������ getSize()�� 0 �� �����ϸ�, read(), write() 
// �޽��� �ƹ��� ���ҵ� ���� �ʴ´�.
//
//////////////////////////////////////////////////////////////////////

class CLLogout : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_LOGOUT; }
	
	// get packet's body size
	size_t getPacketSize () const { return 0; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName () const { return "CLLogout"; }
	
	// get packet's debug string
	std::string toString () const { return "CLLogout"; }
#endif

};


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutFactory;
//
// Factory for CLLogout
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLLogoutFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLLogout(); }

	// get packet name
	std::string getPacketName () const { return "CLLogout"; }

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_LOGOUT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return 0; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLLogoutHandler {

	public :

		// execute packet's handler
		static void execute ( CLLogout * pPacket , Player * player );

	};
#endif

#endif
