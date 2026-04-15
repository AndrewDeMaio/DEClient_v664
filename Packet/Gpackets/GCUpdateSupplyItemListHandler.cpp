////////////////////////////////////////////////////////////////////////////////
// Filename    : GCUpdateSupplyItemListHandler.cpp
// Written By  : rappi76
// Description :
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCUpdateSupplyItemList.h"

#ifdef __GAME_CLIENT__

	#include "VS_UI.h"
	#include "MPremiumGiveItemInfo.h"
	#include "MTimeItemManager.h"

#endif

void GCUpdateSupplyItemListHandler::execute ( GCUpdateSupplyItemList * pPacket , Player * pPlayer )
{
	__BEGIN_TRY //__BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_CLIENT__
	// cout << pPacket->toString() << endl;
	
	g_pPremiumGiveItemInfoList->Give_Item_List_ClearAll();
	
	SupplyItemInfo* pSupplyItemInfo = NULL;
	while(pSupplyItemInfo = pPacket->popSupplyItemInfo())
	{
		MItem *pItem = MItem::NewItem( (ITEM_CLASS)pSupplyItemInfo->itemClass );
		pItem->SetItemType(pSupplyItemInfo->itemType);
		pItem->SetItemOptionList(pSupplyItemInfo->optionType);
		pItem->SetGrade(pSupplyItemInfo->grade); // �ð��� ������ Ȳ��ó�� �ϱ�
		pItem->SetNumber(pSupplyItemInfo->num);
		//pItem->SetTimeLimitStatic(pSupplyItemInfo->timeLimit);
		pItem->SetCurrentDurability(pItem->GetMaxDurability());

		MPremiumGiveItemInfo *pPremiumGiveItemInfo = new MPremiumGiveItemInfo(pItem,pSupplyItemInfo->ID,pSupplyItemInfo->timeLimit);
		g_pPremiumGiveItemInfoList->AddItem(pPremiumGiveItemInfo);

		DeleteNew(pSupplyItemInfo);
	}
	
#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)
	gC_vs_ui.Request_PremiumGiveItem();
#endif

#endif
	
	__END_DEBUG
//	__END_DEBUG_EX
	__END_CATCH
}
