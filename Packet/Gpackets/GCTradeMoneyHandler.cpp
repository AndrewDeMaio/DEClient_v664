//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeMoneyHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradeMoney.h"
#include "ClientDef.h"
#include "MTradeManager.h"

void GCTradeMoneyHandler::execute ( GCTradeMoney * pPacket , Player * pPlayer )
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
	
	int money = pPacket->getAmount();

	bool bRefuseAccept = false;
	bool bNextAcceptTime = false;
	
	switch (pPacket->getCode())
	{
		//---------------------------------------------------------------
		// ������ ��ȯ�� ���� �׼��� �÷ȴ�.
		//---------------------------------------------------------------
		case GC_TRADE_MONEY_INCREASE :
			g_pTradeManager->GetOtherMoneyManager()->AddMoney( money );

			bRefuseAccept = true;
		break;

		//---------------------------------------------------------------
		// ������ ��ȯ�� ���� �׼��� �ٿ���.
		//---------------------------------------------------------------
		case GC_TRADE_MONEY_DECREASE :
			g_pTradeManager->GetOtherMoneyManager()->UseMoney( money );

			bRefuseAccept = true;
			bNextAcceptTime = true;
		break;
		
		//---------------------------------------------------------------
		// [����] ��ȯ�� �� �߰��� �� 
		//---------------------------------------------------------------
		case GC_TRADE_MONEY_INCREASE_RESULT :			
			g_pMoneyManager->UseMoney( money );
			g_pTradeManager->GetMyMoneyManager()->AddMoney( money );	
			
			bRefuseAccept = true;
		break;

		//---------------------------------------------------------------
		// [����] ��ȯ���� ���� ��
		//---------------------------------------------------------------
		case GC_TRADE_MONEY_DECREASE_RESULT :			
			g_pTradeManager->GetMyMoneyManager()->UseMoney( money );
			g_pMoneyManager->AddMoney( money );	

			bRefuseAccept = true;
		break;
	}

	//-----------------------------------------------------------
	// ���� �ٲ�ٸ�... OK���
	//-----------------------------------------------------------
	if (bRefuseAccept)
	{
		g_pTradeManager->RefuseOtherTrade();
		g_pTradeManager->RefuseMyTrade();

		if(bNextAcceptTime)
			g_pTradeManager->SetNextAcceptTime();
	}
	

#endif

	__END_CATCH
}
