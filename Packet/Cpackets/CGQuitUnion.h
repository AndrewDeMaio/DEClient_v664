//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_H__
#define __CG_QUIT_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnion;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnion : public Packet
{
public:
	enum{
		QUIT_NORMAL = 0,		// ������ ���� ��û
		QUIT_QUICK,				// �Ϲ������� Ż��
		QUIT_MAX
	};	

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_QUIT_UNION; }
	
	// get packet's body size
	size_t getPacketSize() const { return szGuildID+szBYTE; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "CGQuitUnion"; }

	// get packet's debug string
	string toString() const;
#endif
    // get/set GuildID
    GuildID_t getGuildID() const { return m_GuildID; }
    void setGuildID( GuildID_t GuildID ) { m_GuildID = GuildID; }

	// get/set Quit Method
	BYTE	getQuitMethod()	const { return m_Method; }
	void	setQuitMethod( BYTE Method ) { m_Method = Method; }


private :

	// Guild ID
	GuildID_t	m_GuildID;
	BYTE		m_Method;


};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionFactory;
//
// Factory for CGQuitUnion
//
//////////////////////////////////////////////////////////////////////
//#ifdef __DEBUG_OUTPUT__
class CGQuitUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionFactory() {}
	
	// destructor
	virtual ~CGQuitUnionFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGQuitUnion(); }

	// get packet name
	string getPacketName() const { return "CGQuitUnion"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_QUIT_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szGuildID + szBYTE; }
};

//#endif
//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGQuitUnionHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnion* pCGQuitUnion, Player* pPlayer);

};
#endif
#endif
