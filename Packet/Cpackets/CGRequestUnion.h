//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_UNION_H__
#define __CG_REQUEST_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnion;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnion : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_REQUEST_UNION; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGRequestUnion"; }

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
// class CGRequestUnionFactory;
//
// Factory for CGRequestUnion
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestUnionFactory() {}
	
	// destructor
	virtual ~CGRequestUnionFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGRequestUnion(); }

	// get packet name
	string getPacketName() const { return "CGRequestUnion"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_REQUEST_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGRequestUnionHandler {

public:

	// execute packet's handler
	static void execute(CGRequestUnion* pCGRequestUnion, Player* pPlayer);

};
#endif
#endif
