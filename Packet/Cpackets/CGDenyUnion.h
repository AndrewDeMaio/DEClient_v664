//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDenyUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DENY_UNION_H__
#define __CG_DENY_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGDenyUnion;
//
//////////////////////////////////////////////////////////////////////

class CGDenyUnion : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_DENY_UNION; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGDenyUnion"; }

	// get packet's debug string
	string toString() const;
#endif
	// get/set GuildID
	GuildID_t getGuildID() const { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGDenyUnionFactory;
//
// Factory for CGDenyUnion
//
//////////////////////////////////////////////////////////////////////

class CGDenyUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGDenyUnionFactory() {}
	
	// destructor
	virtual ~CGDenyUnionFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGDenyUnion(); }

	// get packet name
	string getPacketName() const { return "CGDenyUnion"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_DENY_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDenyUnionHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGDenyUnionHandler {

public:

	// execute packet's handler
	static void execute(CGDenyUnion* pCGDenyUnion, Player* pPlayer);

};
#endif
#endif
