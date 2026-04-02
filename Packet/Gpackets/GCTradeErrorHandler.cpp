//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeErrorHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradeError.h"
#include "ClientDef.h"
#include "UIDialog.h"
#include "MGameStringTable.h"
#include "TempInformation.h"
#include "MTradeManager.h"
#include "UIFunction.h"

void GCTradeErrorHandler::execute ( GCTradeError * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	
	if (g_pPlayer==NULL
		|| g_pTempInformation==NULL
		|| g_pUIDialog==NULL
		|| g_pGameStringTable==NULL)
	{
		return;
	}


	int code = pPacket->getCode();

	//----------------------------------------------------------------------
	//
	//	��ȯ�� ��ҵǴ� ����� �������� ó��
	//
	//----------------------------------------------------------------------
	if (code==GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST
		|| code==GC_TRADE_ERROR_CODE_RACE_DIFFER
		|| code==GC_TRADE_ERROR_CODE_NOT_SAFE)
	{	
		if (g_pTempInformation->GetMode() == TempInformation::MODE_TRADE_REQUEST)
		{
			// ��ȯ����ҷ�?�� �ݴ´�.
			UI_CloseExchangeCancel();

			// ���� ����..
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_TRADE)
			{
				g_pPlayer->SetWaitVerifyNULL();
			}

			g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		}
	}

	switch (code)
	{
		//----------------------------------------------------------------------
		// ��ȯ�� �䱸�� ����� �������� �ʴ´�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST :						
			// �׷� ��� ����~
			UI_CloseExchangeCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_NOBODY].GetString());
		break;
		
		
		//----------------------------------------------------------------------
		// ��ȯ�� �䱸�� ����� �ٸ� �����̴�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_RACE_DIFFER :
			// ��ȯ�� �� ����~
			UI_CloseExchangeCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TRADE].GetString());
		break;

		//----------------------------------------------------------------------
		// ��ȯ�� �Ϸ��� �ϴ� ���� ���� ���밡 �ƴϴ�.
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_NOT_SAFE :
			// ��ȯ�� �� ����~
			UI_CloseExchangeCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_SAFETY_ZONE_ONLY].GetString());			
		break;

		//----------------------------------------------------------------------
		// ���ͻ���Ŭ�� ź ä�� ��ȯ�� �Ϸ��� �ϰ� �ִ�.
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_MOTORCYCLE :
			// ��ȯ�� �� ����~
			UI_CloseExchangeCancel();

			if( g_pPlayer->IsSlayer() )
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_CANNOT_ON_MOTORCYCLE].GetString());
			else if ( g_pPlayer->IsOusters() )
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TRADE_SUMMON_SYLPH].GetString() );
		break;
		

		//----------------------------------------------------------------------
		// ��ȯ ���̸鼭 �ٽ� ��ȯ�� �Ϸ��� �Ѵ�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_ALREADY_TRADING :
			
			UI_CloseExchangeCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TRADE_ALREADY_TRADING].GetString());
		break;

		//----------------------------------------------------------------------
		// ��ȯ ���� �ƴѵ� : ��ȯ ���� ��Ŷ�� ���ƿԴ�.
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_NOT_TRADING :
			// - -;
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] Server is Not Trade Mode");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// ��ȯ ��� ���Ϸ��� �ϴ� �������� ������ ���� �ʴ�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_ADD_ITEM :
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] There is no such item to Add");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// ��ȯ ��󿡼� ������ �ϴ� �������� ������ ���� �ʴ�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_REMOVE_ITEM :
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] There is no such item to Remove");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// ��ȯ ��� ���Ϸ��� �ϴ� ���� ������ ���� �ʴ�.
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_INCREASE_MONEY :
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_TRADE_ERROR_CODE_INCREASE_MONEY");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// ��ȯ ��󿡼� ������ �ϴ� ���� ������ ���� �ʴ�.
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_DECREASE_MONEY :
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_TRADE_ERROR_CODE_DECREASE_MONEY");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// ��ȯ�� �ߴµ� : �ڸ��� ���ڶ� �����ߴ�
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE :
			
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TRADE_NO_SPACE].GetString());

			#ifdef OUTPUT_DEBUG			
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// �� �� ���� �����̴�...
		//----------------------------------------------------------------------
		case GC_TRADE_ERROR_CODE_UNKNOWN :
			
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_TRADE].GetString());

			#ifdef OUTPUT_DEBUG			
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_TRADE_ERROR_CODE_UNKNOWN");
				}
			#endif
		break;
		
		case GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX:
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_CANNOT_EVENT_GIFT_BOX].GetString());
			break;
	}

	//----------------------------------------------------------------------
	// Trade Error�� ���� ������ ��ȯâ�� �ݴ´�.
	//----------------------------------------------------------------------
	if (g_pTradeManager!=NULL)
	{
		g_pTradeManager->CancelTrade();
	}

	UI_CloseExchange();

#endif

	__END_CATCH
}
