//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopList.cpp 
// Written By  : �輺��
// Description :
// �÷��̾ ���� ���� ������ ������ �ִ� �Ͱ� �ٸ� ���,
// �÷��̾�� ������ ������ �ִ� ��ǰ ����� �䱸�ϰ� �ȴ�.
// �� ��Ŷ�� �� �� �÷��̾�� �����ϰ� �Ǵ� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCShopList.h"
#include "Assert.h"
//#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCShopList::GCShopList()
{
	__BEGIN_TRY

		for (int i = 0; i < SHOP_RACK_INDEX_MAX; i++)
			m_pBuffer[i].bExist = false;

	m_ShopType = 0;

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCShopList::~GCShopList()
{
	__BEGIN_TRY
		__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCShopList::read(SocketInputStream& iStream)
{
	__BEGIN_TRY


		BYTE i = 0;
	BYTE nTotal = 0;
	BYTE index = 0;

	// read NPC id & version & rack type & number of item
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_RackType);
	iStream.read(nTotal);

	// read each item info
	for (i = 0; i < nTotal; i++)
	{
		iStream.read(index);

		_SHOPLISTITEM& item = m_pBuffer[index];

		iStream.read(item.objectID);
		iStream.read(item.itemClass);
		iStream.read(item.itemType);

		BYTE optionSize;
		iStream.read(optionSize);
		for (int j = 0; j < optionSize; j++)
		{
			OptionType_t optionType;
			iStream.read(optionType);
			item.optionType.push_back(optionType);
		}

		iStream.read(item.durability);
		iStream.read(item.silver);
		iStream.read(item.grade);
		iStream.read(item.enchantLevel);

		m_pBuffer[index].bExist = true;
	}

	iStream.read(m_MarketCondBuy);
	iStream.read(m_MarketCondSell);
	iStream.read(m_ShopType);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCShopList::write(SocketOutputStream& oStream) const
{
	__BEGIN_TRY

		BYTE i = 0;
	BYTE nTotal = 0;

	// calculate total number of items
	for (i = 0; i < SHOP_RACK_INDEX_MAX; i++)
		if (m_pBuffer[i].bExist) nTotal++;

	// write NPC id & version & rack type & number of item
	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_RackType);
	oStream.write(nTotal);

	// write each item info
	for (i = 0; i < SHOP_RACK_INDEX_MAX; i++)
	{
		const _SHOPLISTITEM& item = m_pBuffer[i];

		if (item.bExist)
		{
			oStream.write(i);
			oStream.write(item.objectID);
			oStream.write(item.itemClass);
			oStream.write(item.itemType);

			BYTE optionSize = item.optionType.size();
			oStream.write(optionSize);

			std::list<OptionType_t>::const_iterator itr;
			for (itr = item.optionType.begin(); itr != item.optionType.end(); itr++)
			{
				OptionType_t optionType = *itr;
				oStream.write(optionType);
			}

			oStream.write(item.durability);
			oStream.write(item.silver);
			oStream.write(item.grade);
			oStream.write(item.enchantLevel);
		}
	}

	oStream.write(m_MarketCondBuy);
	oStream.write(m_MarketCondSell);
	oStream.write(m_ShopType);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCShopList::execute(Player* pPlayer)
{
	__BEGIN_TRY

		GCShopListHandler::execute(this, pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

size_t GCShopList::getPacketSize() const
{
	size_t size = szObjectID +     // NPC id
		szShopVersion +  // shop version
		szShopRackType + // rack type
		szBYTE;          // total number of item

	for (int i = 0; i < SHOP_RACK_INDEX_MAX; i++)
	{
		if (m_pBuffer[i].bExist)
		{
			size += szBYTE;         // Item index in shop rack
			size += szObjectID;     // item OID
			size += szBYTE;         // item class
			size += szItemType;     // item type
			size += szBYTE + m_pBuffer[i].optionType.size();   // item option type
			size += szDurability;   // item durability
			size += szSilver;       // silver coating amount
			size += szGrade;        // grade
			size += szEnchantLevel; // enchant level
		}
	}

	size += szMarketCond + szMarketCond;

	return size;
}


#ifdef __DEBUG_OUTPUT__	
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCShopList::toString() const
{
	__BEGIN_TRY

		StringStream msg;

	msg << "GCShopList(" << "ObjectID:" << m_ObjectID << ","
		<< "ShopVersion:" << (int)m_Version << ","
		<< "RackType:" << (int)m_RackType << ",";

	for (int i = 0; i < SHOP_RACK_INDEX_MAX; i++)
	{
		msg << "(Item" << i << ":";
		if (m_pBuffer[i].bExist)
		{
			msg << "ObjectID:" << (int)(m_pBuffer[i].objectID)
				<< "ItemClass:" << (int)(m_pBuffer[i].itemClass)
				<< "ItemType:" << (int)(m_pBuffer[i].itemType)
				<< "OptionTypeSize:" << (int)(m_pBuffer[i].optionType.size())
				<< "Durability:" << (int)(m_pBuffer[i].durability)
				<< "Silver:" << (int)(m_pBuffer[i].silver)
				<< "Grade:" << (int)(m_pBuffer[i].grade)
				<< "EnchantLevel:" << (int)(m_pBuffer[i].enchantLevel);
			msg << ")";
		}
	}

	msg << "MarketCondBuy:" << (int)m_MarketCondBuy
		<< "MarketCondSell:" << (int)m_MarketCondSell
		<< "ShopType:" << (int)m_ShopType;

	msg << ")";

	return msg.toString();

	__END_CATCH
}
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SHOPLISTITEM GCShopList::getShopItem(BYTE index) const
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX)
	{
		SHOPLISTITEM emptyItem;
		emptyItem.bExist = false;
		return emptyItem;
	}

	// return shop item info
	return m_pBuffer[index];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
void GCShopList::setShopItem(BYTE index, const Item* pItem)
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX) return;

	// check pointer 
	Assert(pItem != NULL);

	// set shop item info
	m_pBuffer[index].bExist = true;
	m_pBuffer[index].objectID = pItem->getObjectID();
	m_pBuffer[index].itemClass = pItem->getItemClass();
	m_pBuffer[index].itemType = pItem->getItemType();
	m_pBuffer[index].optionType = pItem->getOptionTypeList();
	m_pBuffer[index].durability = pItem->getDurability();
	m_pBuffer[index].silver = pItem->getSilver();
	m_pBuffer[index].grade = pItem->getGrade();
	m_pBuffer[index].enchantLevel = pItem->getEnchantLevel();
}

#endif
