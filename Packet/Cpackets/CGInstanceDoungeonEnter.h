//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGInstanceDoungeonEnter 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_INSTANCEDOUNGEON_ENTER_H__
#define __CG_INSTANCEDOUNGEON_ENTER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGInstanceDoungeonEnter;
// Ƽ���� ���� ó�� ����
//////////////////////////////////////////////////////////////////////
#if __CONTENTS(__TIPOJYU_CASTLE)
class CGInstanceDoungeonEnter : public Packet {

public:
	
	// constructor
	CGInstanceDoungeonEnter();
	
	// destructor
	~CGInstanceDoungeonEnter();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_INSTANCEDOUNGEON_ENTER; }
	
	// get packet's body size
	size_t getPacketSize() const { return szObjectID + szBYTE; }

	// get packet name
	string getPacketName() const { return "CGInstanceDoungeonEnter"; }
	
	// get packet's debug string
	string toString() const;

	// get/set ObjectID
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	
	BYTE getSelectDoungeonIndex() const { return m_SelectDoungeonIndex; }
	void setSelectDoungeonIndex(BYTE SelectDoungeonIndex) { m_SelectDoungeonIndex = SelectDoungeonIndex; }

private :
	
	ObjectID_t m_ObjectID;  // NPC ObjectID
	BYTE m_SelectDoungeonIndex;

};


//////////////////////////////////////////////////////////////////////
//
// class CGCGInstanceDoungeonEnterFactory;
//
// Factory for CGInstanceDoungeonEnter
//
//////////////////////////////////////////////////////////////////////

class CGInstanceDoungeonEnterFactory : public PacketFactory {

public:
	
	// constructor
	CGInstanceDoungeonEnterFactory() {}
	
	// destructor
	virtual ~CGInstanceDoungeonEnterFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGInstanceDoungeonEnter(); }

	// get packet name
	string getPacketName() const { return "CGInstanceDoungeonEnter"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_INSTANCEDOUNGEON_ENTER; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szObjectID + szBYTE; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGInstanceDoungeonEnterHandler;
//
//////////////////////////////////////////////////////////////////////

class CGInstanceDoungeonEnterHandler {
	
public:

	// execute packet's handler
	static void execute(CGInstanceDoungeonEnter* pCGInstanceDoungeonEnter, Player* player);
};
#endif //__TIPOJYU_CASTLE
#endif
