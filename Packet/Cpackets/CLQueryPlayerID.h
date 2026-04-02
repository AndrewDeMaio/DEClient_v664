//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryPlayerID.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_PLAYER_ID_H__
#define __CL_QUERY_PLAYER_ID_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryPlayerID;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

class CLQueryPlayerID : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_QUERY_PLAYER_ID; }
	
	// get packet's body size
	size_t getPacketSize () const
	{ 
		return szBYTE + m_PlayerID.size(); 
	}

#ifdef __DEBUG_OUTPUT__	
	// get packet name
	std::string getPacketName () const { return "CLQueryPlayerID"; }
	
	// get packet's debug std::string
	std::string toString () const;
#endif

public :

	// get/set player's id
	const std::string& getPlayerID () const { return m_PlayerID; }
	void setPlayerID ( const std::string & playerID ) { m_PlayerID = playerID; }

private :

	// �÷��̾� ���̵�
	std::string m_PlayerID;

};


//--------------------------------------------------------------------------------
//
// class CLQueryPlayerIDFactory;
//
// Factory for CLQueryPlayerID
//
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
class CLQueryPlayerIDFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLQueryPlayerID(); }

	// get packet name
	std::string getPacketName () const { return "CLQueryPlayerID"; }

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_QUERY_PLAYER_ID; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const 
	{ 
		return szBYTE + 20; 
	}

};

#endif


//--------------------------------------------------------------------------------
//
// class CLQueryPlayerIDHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
	class CLQueryPlayerIDHandler {

	public :

		// execute packet's handler
		static void execute ( CLQueryPlayerID * pPacket , Player * pPlayer );

	};
#endif

#endif
