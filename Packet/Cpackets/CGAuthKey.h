//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAuthKey.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_AUTH_KEY_H__
#define __CG_AUTH_KEY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAuthKey;
// NPC �� ��縦 �ֺ��� PC �鿡�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class CGAuthKey : public Packet 
{
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_CG_AUTH_KEY; }
	size_t getPacketSize() const { return szDWORD; }

#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "CGAuthKey"; }
	string toString() const;
#endif
	DWORD getKey() const { return m_Key; }
	void setKey(DWORD key) { m_Key = key; }

private:
	DWORD		m_Key;
	
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthKeyFactory;
//////////////////////////////////////////////////////////////////////////////


class CGAuthKeyFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new CGAuthKey(); }
	string getPacketName() const { return "CGAuthKey"; }
	PacketID_t getPacketID() const { return Packet::PACKET_CG_AUTH_KEY; }
	PacketSize_t getPacketMaxSize() const { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthKeyHandler;
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGAuthKeyHandler 
{
public:
	static void execute(CGAuthKey* pPacket, Player* pPlayer);

};
#endif
#endif
