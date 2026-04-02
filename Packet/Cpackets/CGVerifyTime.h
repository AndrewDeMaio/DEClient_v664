//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVerifyTime.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VERIFY_TIME_H__
#define __CG_VERIFY_TIME_H__

// include files

//#ifdef __GAME_SERVER__
//#include "GamePlayer.h"
//#endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTime;
//
// Ŭ���̾�Ʈ�� �������� ������ VerifyTime ��Ŷ�̴�.
// ���ο� VerifyTime String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class Player;
class GamePlayer;

class CGVerifyTime : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_VERIFY_TIME; }
	
	// get packet's body size
	size_t getPacketSize () const { return 0;} //sizeof(DWORD); }

	void	SetTimeStamp(DWORD	dwTimeStamp) {m_TimeStamp	= dwTimeStamp;	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGVerifyTime"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
private :
	DWORD m_TimeStamp;
};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeFactory;
//
// Factory for CGVerifyTime
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGVerifyTimeFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGVerifyTime(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGVerifyTime"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_VERIFY_TIME; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize () const { return 0; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGVerifyTimeHandler {

	public :

		// execute packet's handler
		static void execute ( CGVerifyTime * pPacket , Player * pPlayer );

	};
#endif

#endif
