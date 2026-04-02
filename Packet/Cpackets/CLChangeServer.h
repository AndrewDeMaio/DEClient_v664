//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLChangeServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_CHANGE_SERVER_H__
#define __CL_CHANGE_SERVER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLChangeServer;
//
//////////////////////////////////////////////////////////////////////

class CLChangeServer : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_CHANGE_SERVER; }
	
	// get packet's body size
	size_t getPacketSize () const { return szServerGroupID; }


	// get / set ServerGroupID
	ServerGroupID_t getServerGroupID() const { return m_ServerGroupID; }
	void setServerGroupID( ServerGroupID_t ServerGroupID ) { m_ServerGroupID = ServerGroupID; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's debug std::string
		std::string toString () const;

		// get packet name
		std::string getPacketName () const { return "CLChangeServer"; }
	#endif

private :

	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerFactory;
//
// Factory for CLChangeServer
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLChangeServerFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLChangeServer(); }

	// get packet name
	std::string getPacketName () const { return "CLChangeServer"; }
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_CHANGE_SERVER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szServerGroupID; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLChangeServerHandler {

	public :

		// execute packet's handler
		static void execute ( CLChangeServer * pPacket , Player * player );

	};
#endif

#endif
