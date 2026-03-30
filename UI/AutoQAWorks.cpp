#include "client_PCH.h"
#include "AutoQAWorks.h"
#include "ItemClassDef.h"
#include "VS_UI_Base.h"
#include "MItem.h"
#include "Packet/Packet.h"
#include <sstream>

using namespace aqa;

AQAWork_Base::AQAWork_Base(const std::string& name, const std::string& desc)
	: Work(name, desc)
{
}



AQAWork_Item::AQAWork_Item(const std::string& name, const std::string& desc)
	: AQAWork_Base(name, desc)
{
}

//////////////////////////////////////////////////////////////////////////
// 달빛 상자 확률 테스트
// 2009.09.23
AQAWork_MoonlightBox::AQAWork_MoonlightBox()
	: AQAWork_Item("MoonlightBox", "Monnlight Box Probability Test")
{
}

void AQAWork_MoonlightBox::Do(IFunctions& func, IReport& report)
{
	typedef std::pair<int, int> ItemPair;
	typedef std::map<ItemPair, int> ItemPairMap;

	ItemPairMap itemPairMap;

	//char buffer[256];

	const int count = 20;

	for(int i = 0; i < count; ++i)
	{
		func.Call("ClearInventory");
		
		// 생성 한다음에 사용
		func.Call("CreateItem", MAKEDWORD(ITEM_CLASS_EVENT_GIFT_BOX, 51));
		
		func.Call("UseItem", MAKEDWORD(0, 0));
		func.Call("WaitForPacket", Packet::PACKET_GC_CREATE_ITEM);

		// 생긴 아이템을 확인
		MItem* pItem = (MItem*)func.Call("GetItem", MAKEDWORD(0, 0));

		if(pItem)
		{
			//sprintf(buffer, "Class:%d, Type:%d", pItem->GetItemClass(), pItem->GetItemType());
			//report.AddUnit(ReportUnit(eNormal, buffer));

			++itemPairMap[ItemPair(pItem->GetItemClass(), pItem->GetItemType())];
		}
		else	
		{
			report.AddUnit(ReportUnit(eError, "Create Fail"));
		}
	}

	func.Call("ClearInventory");

	ItemPairMap::iterator iter = itemPairMap.begin();
	ItemPairMap::iterator endIter = itemPairMap.end();

	for(; iter != endIter; ++iter)
	{
		const ItemPair& itemPair = iter->first;

		ITEMTABLE_INFO& itemInfo = (*g_pItemTable)[itemPair.first][itemPair.second];

		std::stringstream ss;

		ss << itemInfo.HName.GetString() << "("
			<< itemInfo.EName.GetString()<<") ";

		report.AddUnit(ReportUnit(eNormal, ss.str()));

		std::stringstream ss2;

		const int get = iter->second;
		ss2 << "- 획득:" << get << "개, 확률:" << (get/(float)count)*100 << "%";

		report.AddUnit(ReportUnit(eNormal, ss2.str()));
	}
}


//////////////////////////////////////////////////////////////////////////
// 달빛 상자 확률 테스트
// 2009.09.23
AQAWork_NormalCase::AQAWork_NormalCase(int itemType)
	: AQAWork_Item("NormalCase", "Normal Case Probability Test")
{
	m_ItemType = itemType;
	SetName((*g_pItemTable)[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName.GetString());
}

void AQAWork_NormalCase::Do(IFunctions& func, IReport& report)
{
	typedef std::pair<int, int> ItemPair;
	typedef std::map<ItemPair, int> ItemPairMap;

	ItemPairMap itemPairMap;

	//char buffer[256];

	const int count = 20;

	for(int i = 0; i < count; ++i)
	{
		func.Call("ClearInventory");
		
		// 일단 키를 생성
		func.Call("CreateItem", MAKEDWORD(ITEM_CLASS_COMMON_QUEST_ITEM, 35));
		func.Call("PickUpItem", MAKEDWORD(0, 0));

		func.Call("CreateItem", MAKEDWORD(ITEM_CLASS_COMMON_QUEST_ITEM, m_ItemType));

		func.Call("ItemToItem", MAKEDWORD(0, 0));

		// 생긴 아이템을 확인
		MItem* pItem = (MItem*)func.Call("GetItem", MAKEDWORD(0, 0));

		if(pItem)
		{
			++itemPairMap[ItemPair(pItem->GetItemClass(), pItem->GetItemType())];
		}
		else
		{
			pItem = (MItem*)func.Call("GetItem", MAKEDWORD(0, 1));

			if(pItem)
			{
				++itemPairMap[ItemPair(pItem->GetItemClass(), pItem->GetItemType())];
			}
			else
			{
				report.AddUnit(ReportUnit(eError, "Create Fail"));
			}
		}
	}

	func.Call("ClearInventory");

	ItemPairMap::iterator iter = itemPairMap.begin();
	ItemPairMap::iterator endIter = itemPairMap.end();

	for(; iter != endIter; ++iter)
	{
		const ItemPair& itemPair = iter->first;

		ITEMTABLE_INFO& itemInfo = (*g_pItemTable)[itemPair.first][itemPair.second];

		std::stringstream ss;

		ss << itemInfo.HName.GetString() << "("
			<< itemInfo.EName.GetString()<<") ";

		report.AddUnit(ReportUnit(eNormal, ss.str()));

		std::stringstream ss2;

		const int get = iter->second;
		ss2 << "- 획득:" << get << "개, 확률:" << (get/(float)count)*100 << "%";

		report.AddUnit(ReportUnit(eNormal, ss2.str()));
	}
}

