//--------------------------------------------------------------------------------
// 
// Filename    : CGShopRequestList.h 
// Written By  : �輺��
// Description : �÷��̾ ������ �ִ� ���� ������ ������ ������ �ִ� ������
//               ������ �ٸ� ���, �÷��̾�� �������� ��ǰ�� ����Ʈ�� 
//               ��û�ϰ� �ȴ�. �� ��Ŷ�� �׶� ������ �Ǵ� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __CG_SHOP_REQUEST_LIST_H__
#define __CG_SHOP_REQUEST_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGShopRequestList;
//
//--------------------------------------------------------------------------------

class CGShopRequestList : public Packet {

public :
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream );
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CG_SHOP_REQUEST_LIST; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGShopRequestListPacketSize �� �����ؼ� �����϶�.
	size_t getPacketSize () const { return szObjectID+szShopRackType; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGShopRequestList"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) { m_ObjectID = ObjectID; }

	ShopRackType_t getRackType(void) { return m_RackType; }
	void setRackType(ShopRackType_t type) { m_RackType = type; }

private :
	
	// ObjectID
	ObjectID_t     m_ObjectID;
	ShopRackType_t m_RackType;

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListFactory;
//
// Factory for CGShopRequestList
//
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
class CGShopRequestListFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CGShopRequestList(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "CGShopRequestList"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CG_SHOP_REQUEST_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const { return szObjectID+szShopRackType; }

};

#endif


//--------------------------------------------------------------------------------
//
// class CGShopRequestListHandler;
//
//--------------------------------------------------------------------------------
#ifndef __GAME_CLIENT__
	class CGShopRequestListHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGShopRequestList * pPacket , Player * player );
	};
#endif

#endif
