//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeFinishHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradeFinish.h"
#include "ClientDef.h"
#include "TempInformation.h"
#include "MTradeManager.h"
#include "UIFunction.h"
#include "UIFunction.h"

void GCTradeFinishHandler::execute ( GCTradeFinish * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	//------------------------------------------------------------------------
	// TradeManager�� �������� ���� ��� --> -_-;;
	//------------------------------------------------------------------------
	/*
	if (g_pTradeManager==NULL)
	{
		DEBUG_ADD(DEBUG_ADD( "[Error] TradeManager is NULL");
		
		return;
	}
	*/


	switch (pPacket->getCode())
	{
		//------------------------------------------------------------------------
		// ���� OK
		//------------------------------------------------------------------------
		case GC_TRADE_FINISH_ACCEPT :
			if (g_pTradeManager!=NULL)
			{
				g_pTradeManager->AcceptOtherTrade();
			}
		break;

		//------------------------------------------------------------------------
		// ��ȯ �ź�..
		//------------------------------------------------------------------------
		case GC_TRADE_FINISH_REJECT :
			if (g_pTradeManager!=NULL)
			{
				g_pTradeManager->CancelTrade();
			}

			if (UI_IsRunningExchange())
			{
				UI_CloseExchange();
			}
			//else 
			{
				if (g_pTempInformation->GetMode() == TempInformation::MODE_TRADE_REQUEST)
				{
					UI_CloseExchangeCancel();
					UI_CloseExchangeAsk();					
				}				
			}

		break;

		//------------------------------------------------------------------------
		// ������ cancel�� ���
		//------------------------------------------------------------------------
		case GC_TRADE_FINISH_RECONSIDER :
			if (g_pTradeManager!=NULL)
			{
				g_pTradeManager->RefuseOtherTrade();
			}
		break;

		//------------------------------------------------------------------------
		// ��ȯ~~
		//------------------------------------------------------------------------
		case GC_TRADE_FINISH_EXECUTE :
			if (g_pTradeManager!=NULL)
			{
				g_pTradeManager->Trade();

				//----------------------------------------------------------------
				// OK ���
				//----------------------------------------------------------------
				g_pTradeManager->RefuseMyTrade();
				g_pTradeManager->RefuseOtherTrade();
			}			
			//UI_CloseExchange();
		break;
	}

#endif

	__END_CATCH
}
