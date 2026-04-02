//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGQuestInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGQuestInventory.h"
#include "Client.h"
#include "vs_ui.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGQuestInventoryHandler::execute ( GCGQuestInventory * pGCGQuestInventory , Player * pPlayer )
{
	__BEGIN_TRY 
//		__BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
	}
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		std::vector<MItem*> QuestItemList;

		std::vector<ItemType_t>	TempItemList = pGCGQuestInventory->getItemList();

		for(int i = 0; i<TempItemList.size(); i++)
		{
			ItemType_t TempType = TempItemList[i];

			MItem* pItem;
			pItem = MItem::NewItem( ITEM_CLASS_GQUEST_ITEM );
			pItem->SetItemType( TempType );
			pItem->SetCurrentDurability( 1 );	
			QuestItemList.push_back(pItem);
		}
		gC_vs_ui.UpdateQuestItemInfo(QuestItemList); 

	// ������ ����Ʈ �޾Ƽ� �������� �������� UI�� �Ѱ�����..
	// ���߿� ����Ʈ ������ �߰� �ǹ� �۾�����
	//gC_vs_ui.UpdateQuestItemInfo(������ ����Ʈ)



	}
//#elif __WINDOWS__

#endif

//	__END_DEBUG_EX
	__END_CATCH
}
