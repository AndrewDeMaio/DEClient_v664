//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeInventoryItemNum.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CHANGE_INVENTORY_ITEM_NUM_H__
#define __GC_CHANGE_INVENTORY_ITEM_NUM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCChangeInventoryItemNum;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCChangeInventoryItemNum {

public :
	
	// constructor
	GCChangeInventoryItemNum ();
	
	// destructor
	~GCChangeInventoryItemNum ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	size_t getPacketSize () const { return szBYTE + szObjectID * m_ChangedItemListNum + szItemNum*m_ChangedItemListNum;} 

	#ifdef __DEBUG_OUTPUT__
		// get packet's debug std::string
		std::string toString () const;
	#endif

	// get / set ListNumber
	BYTE getChangedItemListNum() const { return m_ChangedItemListNum; }
	void setChangedItemListNum( BYTE ListNum ) { m_ChangedItemListNum = ListNum; }

	// add / delete / clear S List
	void addChangedItemListElement( ObjectID_t objectID , BYTE itemNum ); 

	// ClearList
	void clearChangedItemList() { m_ChangedItemList.clear(); m_ChangedItemNumList.clear(); m_ChangedItemListNum = 0; }

	// pop front Element in Object List
	ObjectID_t popFrontChangedItemListElement() { ObjectID_t item = m_ChangedItemList.front(); m_ChangedItemList.pop_front(); return item; }
	ItemNum_t popFrontChangedItemNumListElement() { ItemNum_t itemNum = m_ChangedItemNumList.front(); m_ChangedItemNumList.pop_front(); return itemNum; }

protected:
	
	// List Element Number
	BYTE m_ChangedItemListNum;

	// �������� ����� Inventory���� Item List
	std::list<ObjectID_t> m_ChangedItemList;		// ����� Item object id
	std::list<ItemNum_t> m_ChangedItemNumList;	// ����� Item object id�� ���� ����.


};

#endif
