//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGMakeItem.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MAKE_ITEM_H__
#define __CG_MAKE_ITEM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItem;
//
//////////////////////////////////////////////////////////////////////

class CGMakeItem : public Packet {
public :

	// constructor
	CGMakeItem();

	// destructor
	~CGMakeItem();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_MAKE_ITEM; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szItemClass + szItemType; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGMakeItem"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :
	ItemType_t getItemType() const { return m_ItemType;}
	void setItemType( ItemType_t c) { m_ItemType = c;}

	ItemClass_t getItemClass() const { return m_ItemClass;}
	void setItemClass( ItemClass_t c) { m_ItemClass = c;}

private :

	ItemClass_t m_ItemClass;
	ItemType_t m_ItemType;	
};


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItemFactory;
//
// Factory for CGMakeItem
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGMakeItemFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGMakeItem(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGMakeItem"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_MAKE_ITEM; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const { return szItemClass + szItemType; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItemHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGMakeItemHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGMakeItem * pPacket , Player * player );
	};

#endif

#endif