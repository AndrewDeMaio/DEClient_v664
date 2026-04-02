//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradePrepareHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradePrepare.h"
#include "ClientDef.h"
#include "MGameStringTable.h"
#include "UIDialog.h"
#include "TempInformation.h"
#include "MTradeManager.h"
#include "Cpackets/CGRequestInfo.h"
#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "CPackets\CGTradePrepare.h"
	#include "UIFunction.h"

#endif


void GCTradePrepareHandler::execute ( GCTradePrepare * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	ObjectID_t targetID = pPacket->getTargetObjectID();

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);
		
	//----------------------------------------------------------------------
	//
	//			���� ������ �ŷ����ڰ� ��û�ϴ� ����̴�.
	//
	//----------------------------------------------------------------------
	// �̹� �ŷ� ���� ���... ���.. ���� �ϰ� ������.. --> �ź�
	//----------------------------------------------------------------------
	if (g_pPlayer->IsWaitVerify() && g_pPlayer->GetWaitVerify()!=MPlayer::WAIT_VERIFY_TRADE			// ���� �޾ƾ� �ϴ°� �ִ� ���
		|| g_pPlayer->IsRepeatAction()		// �ݺ� �ൿ ���� ���
		|| g_pUIDialog->IsLockInput()		// NPC�� ��ȭ��..
		|| g_pPlayer->GetCreatureType()==CREATURETYPE_BAT	// ������ ���
		|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_GHOST	// ����Ʈ�� ���
		|| g_pPlayer->GetCreatureType()==CREATURETYPE_WOLF	// ������ ���
#if __CONTENTS(__FAST_TRANSFORTER)
		|| g_pPlayer->GetCreatureType()==CREATURETYPE_FLITTERMOUSE
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| g_pPlayer->GetCreatureType()==CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
		
		)
	{
		// ��ȯ �ź�
		CGTradePrepare _CGTradePrepare;
		_CGTradePrepare.setTargetObjectID( targetID );
		_CGTradePrepare.setCode( CG_TRADE_PREPARE_CODE_REJECT );

		pClientPlayer->sendPacket( &_CGTradePrepare );

		return;
	}


	// �̹� �ٸ� ���� ������ �ŷ����ڰ� �ع��� ��� --> �ź� [�������� ó��]
	switch (pPacket->getCode())
	{
		//----------------------------------------------------------------------
		//
		// �ٸ� ����� ������ ��ȯ ��û�Ҷ�
		//
		//----------------------------------------------------------------------
		case GC_TRADE_PREPARE_CODE_REQUEST :
		{
			bool bLookMe = false;

			//----------------------------------------------------------------------
			// �̹� ���� �ٸ� �������� �ŷ����ڰ� �� ��� 
			//----------------------------------------------------------------------
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_TRADE
				&& g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_REQUEST)
			{
				int code;

				//----------------------------------------------------------------------
				// �� ����� ������ �ŷ� ��û�� ��� --> OK
				//----------------------------------------------------------------------
				if (g_pTempInformation->Value1==targetID)
				{
					code = CG_TRADE_PREPARE_CODE_ACCEPT;

					g_pTempInformation->SetMode(TempInformation::MODE_NULL);

					//-------------------------------------------
					// ��ȯâ ����.
					//-------------------------------------------
					UI_RunExchange( targetID );

					bLookMe = true;
				}
				//----------------------------------------------------------------------
				// �ƴ� ���
				//----------------------------------------------------------------------
				else
				{
					code = CG_TRADE_PREPARE_CODE_BUSY;
				}

				CGTradePrepare _CGTradePrepare;
				_CGTradePrepare.setTargetObjectID( targetID );
				_CGTradePrepare.setCode( code );				

				pClientPlayer->sendPacket( &_CGTradePrepare );

			}
			//----------------------------------------------------------------------
			// ��ȯ�ұ�? Y/N
			//----------------------------------------------------------------------
			else
			{
				//-------------------------------------------
				// ��ȯ�ұ�?
				//-------------------------------------------
				UI_RunExchangeAsk( targetID );	
				
				bLookMe = true;
			}

			//----------------------------------------------------------------------
			// �ٸ� ĳ���Ͱ� ���� �ٶ󺸴� ���
			//----------------------------------------------------------------------
			if (bLookMe)
			{
				MCreature* pCreature = g_pZone->GetCreature( targetID );
				
				if (pCreature!=NULL)
				{
					pCreature->SetDirectionToPosition( g_pPlayer->GetX(), g_pPlayer->GetY() );
				}
				else
				{
					DEBUG_ADD_FORMAT("[Error] No Such Creature. id=%d", targetID);
				}
			}
		}
		break;

		//----------------------------------------------------------------------
		//
		// ��ȯ ��û�� ����� ��ȯ ����� ���
		//
		//----------------------------------------------------------------------
		case GC_TRADE_PREPARE_CODE_CANCEL :

			if (g_pTempInformation->GetMode() == TempInformation::MODE_TRADE_REQUEST)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);
			}		

			// �̹� ���� OK ������ ��ȯâ�� �� �ִ� ���
			if (UI_IsRunningExchange())
			{
				UI_CloseExchange();
			}
			else
			{
				UI_CloseExchangeAsk();
			}
		break;

		//----------------------------------------------------------------------
		//
		// �� ��ȯ��û�� �޾Ƶ鿩����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_PREPARE_CODE_ACCEPT :
			//----------------------------------------------------------------------
			// �̹� ���� �ٸ� �������� �ŷ����ڰ� �� ��� 
			//----------------------------------------------------------------------
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_TRADE
				&& g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_REQUEST)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				//-------------------------------------------
				// ��ȯâ�� ����.
				//-------------------------------------------
				UI_RunExchange( targetID );
				
				CGRequestInfo _CGRequestInfo;
				_CGRequestInfo.setValue( targetID );
				_CGRequestInfo.setCode( CGRequestInfo::REQUEST_CHARACTER_INFO );
				
				pPlayer->sendPacket( &_CGRequestInfo );
				MCreature* pCreature = g_pZone->GetCreature(targetID);
				if(pCreature != NULL)
					UI_RunOtherInfo(pCreature);
			}

		break;


		//----------------------------------------------------------------------
		//
		// �� ��ȯ��û�� �źεɶ�
		//
		//----------------------------------------------------------------------
		case GC_TRADE_PREPARE_CODE_REJECT :
		{
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_TRADE
				&& g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_REQUEST)
			{			
				// ������ data����
				g_pPlayer->SetWaitVerifyNULL();
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// ��ȯ����ҷ�?�� �ݴ´�.
				UI_CloseExchangeCancel();

				// �ŷ� �ź� dialog
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_REJECTED].GetString());
			}
		}
		break;

		//----------------------------------------------------------------------
		//
		// ��ȯ ��û�� ����� ���� ��ȯ ���̴�. (Ȥ�� �����Ѵ�..)
		//
		//----------------------------------------------------------------------
		case GC_TRADE_PREPARE_CODE_BUSY :
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_TRADE
				&& g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_REQUEST)
			{			
				// ������ data����
				g_pPlayer->SetWaitVerifyNULL();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);				

				UI_CloseExchangeAsk();
				UI_CloseExchangeCancel();

				// busy�� ��ȯ �ȵ�
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_TRADE_BUSY].GetString());
			}
		break;

	}

#endif

	__END_CATCH
}
