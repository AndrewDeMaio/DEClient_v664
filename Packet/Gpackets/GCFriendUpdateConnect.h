//----------------------------------------------------------------------
// 
// Filename    : GCFriendUpdateConnect.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GC_FRIEND_UPDATE_CONNECT_H__
#define __GC_FRIEND_UPDATE_CONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include "StringInfo.h"

#if __CONTENTS(__FRIEND_ADDITION)
class GCFriendUpdateConnect : public Packet {

public:
	GCFriendUpdateConnect();
	virtual ~GCFriendUpdateConnect();
	
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);

	PacketID_t getPacketID() const { return PACKET_GC_FRIEND_UPDATE_CONNECT; }
	size_t getPacketSize() const;

	string getPacketName() const { return "GCFriendUpdateConnect"; }
	string toString() const;
	
	string GetPCName() const { return m_PCName.GetString(); }
	void SetPCName(const string& strPCName) { m_PCName.SetString(strPCName); }
	
	string GetServerName() const { return m_ServerName.GetString(); }
	void SetServerName(const string& strServerName) { m_ServerName.SetString(strServerName); }
	
	bool GetConnect() const { return m_Connect == 0 ? false : true ; }
	void SetConnect(bool bConnect) { m_Connect = bConnect ? 1 : 0; } 

private :
	StringInfo m_PCName;
	StringInfo m_ServerName;
	BYTE m_Connect;
};


//////////////////////////////////////////////////////////////////////
//
// class GCFriendUpdateConnectFactory;
//
// Factory for GCFriendUpdateConnect
//
//////////////////////////////////////////////////////////////////////

class GCFriendUpdateConnectFactory : public PacketFactory {

public:
	
	Packet* createPacket() { return new GCFriendUpdateConnect(); }
	string getPacketName() const { return "GCFriendUpdateConnect"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_FRIEND_UPDATE_CONNECT; }

	PacketSize_t getPacketMaxSize() const 
	{ 
		return StringInfo::getMaxSize() + StringInfo::getMaxSize() + szBYTE;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFriendUpdateConnectHandler {
	
public:

	// execute packet's handler
	static void execute(GCFriendUpdateConnect* pPacket, Player* pPlayer);

};
#endif //__FRIEND_ADDITION

#endif
