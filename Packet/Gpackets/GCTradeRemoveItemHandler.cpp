//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeRemoveItemHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradeRemoveItem.h"
#include "MTradeManager.h"
#include "ClientDef.h"

void GCTradeRemoveItemHandler::execute ( GCTradeRemoveItem * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	//------------------------------------------------------------------------
	// TradeManager�� �������� ���� ��� --> -_-;;
	//------------------------------------------------------------------------
	if (g_pTradeManager==NULL)
	{
		DEBUG_ADD( "[Error] TradeManager is NULL");
		
		return;
	}

	//ObjectID_t getTargetObjectID() const { return m_TargetObjectID; }
	
	TYPE_OBJECTID itemID = pPacket->getItemObjectID();

	MItem* pItem = g_pTradeManager->GetOtherInventory()->RemoveItem( itemID );

	//------------------------------------------------------------------------
	// �������� ���ٸ�..
	//------------------------------------------------------------------------
	if (pItem==NULL)
	{
		DEBUG_ADD_FORMAT( "[Error] There is no such item. id=%d", itemID );
	}
	//------------------------------------------------------------------------
	// ������ �׳� ����� �ȴ�.
	//------------------------------------------------------------------------
	else
	{
		delete pItem;
	}
	
	//-----------------------------------------------------------
	// ���� �ٲ�ٸ�... OK���
	//-----------------------------------------------------------
	g_pTradeManager->RefuseOtherTrade();
	g_pTradeManager->RefuseMyTrade();

	g_pTradeManager->SetNextAcceptTime();

#endif

	__END_CATCH
}
