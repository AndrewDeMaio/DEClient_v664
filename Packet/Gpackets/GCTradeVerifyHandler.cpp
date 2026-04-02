//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeVerifyHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTradeVerify.h"
#include "ClientDef.h"
#include "TempInformation.h"
#include "MTradeManager.h"
#include "MMoneyManager.h"
#include "UIFunction.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "Cpackets\CGTradeAddItem.h"
	#include "Cpackets\CGTradeFinish.h"
	#include "cpackets/CGTradeRemoveItem.h"

#endif

#include "UIFunction.h"
#include "MGameStringTable.h"

void GCTradeVerifyHandler::execute ( GCTradeVerify * pPacket , Player * pPlayer )
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

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	switch (pPacket->getCode())
	{
		//----------------------------------------------------------------------
		//
		// GCTradeAddItem�� ���� �޾ƾ� �ϴ� ��쿡.. OK
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_ADD_ITEM_OK :
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_ADD_ITEM)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				
				pItem->SetTrade();

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------
				g_pTradeManager->RefuseOtherTrade();
				g_pTradeManager->RefuseMyTrade();
			}
		break;

		//----------------------------------------------------------------------
		//
		// GCTradeAddItem�� ���� �޾ƾ� �ϴ� ��쿡.. Fail
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL :
			// 2008.09.25	shootkj
			// ������ �߰��� ���ϴ� ��� Ŭ���̾�Ʈ������ �������� �������� �ʾƾ� �Ѵ�.
//			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_ADD_ITEM)	
			{
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue_Cannot_ItemExchange;	//�߰��� �ڵ� 2008.09.25	shootkj
				
				//-----------------------------------------------------------
				// ���õǾ� �ִ� ������ --> ���
				//-----------------------------------------------------------
				if(pItem != NULL)															//�߰��� �ڵ� 2008.09.25	shootkj
					pItem->UnSetTrade();													//�߰��� �ڵ� 2008.09.25	shootkj

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------

				if(g_pTradeManager != NULL)													//�߰��� �ڵ� 2008.09.25	shootkj
				{
					g_pTradeManager->RefuseOtherTrade();									//�߰��� �ڵ� 2008.09.25	shootkj
					g_pTradeManager->RefuseMyTrade();										//�߰��� �ڵ� 2008.09.25	shootkj
				}

				g_pTempInformation->pValue_Cannot_ItemExchange	= NULL;						//�߰��� �ڵ� 2008.09.25	shootkj
				UI_PopupMessage( STRING_ERROR_ITEM_EXCHANGE_ERROR );
			}
		break;

		//----------------------------------------------------------------------
		//
		//		��ȯ ������� �������� �߰��ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT :
			
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_ADD_ITEM)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				
				//-----------------------------------------------------------
				// �߰� Ȯ��
				//-----------------------------------------------------------
				pItem->SetTrade();

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------
				g_pTradeManager->RefuseOtherTrade();
				g_pTradeManager->RefuseMyTrade();				
			}
			else
			{
				DEBUG_ADD( "[Error] TempMode is Wrong..");
			}
		break;

		//----------------------------------------------------------------------
		//
		//			��ȯ ��󿡼� �������� �����ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_REMOVE_ITEM :
				
		//----------------------------------------------------------------------
		//
		//					mouse --> inventory OK
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_OK :	
		
		//----------------------------------------------------------------------
		//
		//					inventory --> mouse OK
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_OK :
		
			//----------------------------------------------------------------------
			// remove item from trade
			//----------------------------------------------------------------------
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_REMOVE_ITEM)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				
				//-----------------------------------------------------------
				// ���õǾ� �ִ� ������ --> ���
				//-----------------------------------------------------------
				pItem->UnSetTrade();

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------
				g_pTradeManager->RefuseOtherTrade();
				g_pTradeManager->RefuseMyTrade();				
			}
			//----------------------------------------------------------------------
			// inventory --> mouse �� ����
			//----------------------------------------------------------------------
			else if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_PICKUP_FROM_INVENTORY)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				int gridX		= g_pTempInformation->Value2;
				int gridY		= g_pTempInformation->Value3;
				MItem* pMouseItem = UI_GetMouseItem();
			
				UI_PickUpItem( pItem );
				g_pTradeManager->GetMyInventory()->RemoveItem( gridX, gridY );

				//----------------------------------------------------------------
				// OK ���
				//----------------------------------------------------------------				
				g_pTradeManager->RefuseMyTrade();
				g_pTradeManager->RefuseOtherTrade();

				//----------------------------------------------------------------
				// ��ȯ���� ���õ� �������̸� �ڵ����� OK�� ��ҵ�����
				// �ƴ� ��������.. �������� OK��ư�� ����ϴ� packet�� ������ �Ѵ�.
				//----------------------------------------------------------------
				if (!pItem->IsTrade())
				{
					CGTradeFinish _CGTradeFinish;
					_CGTradeFinish.setTargetObjectID( g_pTradeManager->GetOtherID() );
					_CGTradeFinish.setCode( CG_TRADE_FINISH_RECONSIDER );

					pClientPlayer->sendPacket( &_CGTradeFinish );

				}			
			}
			//----------------------------------------------------------------
			// �׳� item ���� ��
			//----------------------------------------------------------------
			else if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_DROP_TO_INVENTORY)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				// pItem�� ���� ��� �ִ� item
				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				int gridX		= g_pTempInformation->Value2;
				int gridY		= g_pTempInformation->Value3;
				MItem* pMouseItem = UI_GetMouseItem();

				// pItem == pMouseItem�̴�.
				//----------------------------------------------------------------
				// mouse�� item�� ���� ��
				//----------------------------------------------------------------
				if (pMouseItem!=NULL)
				{			
					MItem* pOldItem = NULL;

					//----------------------------------------------------------------
					// inventory�� �߰���Ų��.
					//----------------------------------------------------------------
					if (g_pTradeManager->GetMyInventory()->ReplaceItem(
															pMouseItem,		// �߰��� item
															gridX, gridY,	// �߰��� ��ġ 
															pOldItem))								// �����ִ� item
					{
						if (pOldItem != NULL) // replace �Ǿ��°�?
						{
							UI_PickUpItem( pOldItem );						
						}
						else
						{
							UI_DropItem();
						}
					}

					//---------------------------------------------------
					// ���� �������� ��ȯ�ҷ��� ���õ� ���� ���
					//---------------------------------------------------
					if (pMouseItem->IsTrade())
					{
						CGTradeAddItem _CGTradeAddItem;
						_CGTradeAddItem.setTargetObjectID( g_pTradeManager->GetOtherID() );
						_CGTradeAddItem.setItemObjectID( pMouseItem->GetID() );

						pClientPlayer->sendPacket( &_CGTradeAddItem );

					}
				}
				else
				{
					// �ᰡ��
				}

				//----------------------------------------------------------------
				// OK ���
				//----------------------------------------------------------------
				g_pTradeManager->RefuseMyTrade();
				g_pTradeManager->RefuseOtherTrade();

				//----------------------------------------------------------------
				// ��ȯ���� ���õ� �������̸� �ڵ����� OK�� ��ҵ�����
				// �ƴ� ��������.. �������� OK��ư�� ����ϴ� packet�� ������ �Ѵ�.
				//----------------------------------------------------------------
				if (pMouseItem!=NULL && !pMouseItem->IsTrade())
				{
					CGTradeFinish _CGTradeFinish;
					_CGTradeFinish.setTargetObjectID( g_pTradeManager->GetOtherID() );
					_CGTradeFinish.setCode( CG_TRADE_FINISH_RECONSIDER );

					pClientPlayer->sendPacket( &_CGTradeFinish );

				}
			}
			//----------------------------------------------------------------
			// item�� �߰��ɶ�
			//----------------------------------------------------------------
			else if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_INSERT_TO_INVENTORY)				
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				MItem* pItem	= (MItem*)g_pTempInformation->pValue;
				int gridX		= g_pTempInformation->Value2;
				int gridY		= g_pTempInformation->Value3;
				MItem* pMouseItem = UI_GetMouseItem();

				//----------------------------------------------------
				// pMouseItem�� pItem�� �߰���Ų��.
				//----------------------------------------------------
				int total = pMouseItem->GetNumber() + pItem->GetNumber();
				if ( total > pItem->GetMaxNumber() )
				{
					// �Ѱ� ��ġ�� �Ѿ ���
					pMouseItem->SetNumber( total - pItem->GetMaxNumber() );
					pItem->SetNumber( pItem->GetMaxNumber() );
				}
				else
				{
					// ��� pItem�� �߰��� �� �ִ� ���
					pItem->SetNumber( total );
					UI_DropItem();

					delete pMouseItem;
				}

				//----------------------------------------------------
				// ��ȯ�߿� ���õ� �������� ���
				//----------------------------------------------------
				// Remove and Add - -;
				if (pItem->IsTrade())
				{
						//----------------------------------------------------
						// ������ �ٲ��� �����ߴٰ�..
						//----------------------------------------------------
						CGTradeRemoveItem _CGTradeRemoveItem;
						_CGTradeRemoveItem.setTargetObjectID( g_pTradeManager->GetOtherID() );
						_CGTradeRemoveItem.setItemObjectID( pItem->GetID() );

						pClientPlayer->sendPacket( &_CGTradeRemoveItem );

						#ifdef __DEBUG_OUTPUT__
							DEBUG_ADD_FORMAT( "[Send] %s", _CGTradeRemoveItem.toString().c_str() );							
						#endif
						
						//----------------------------------------------------
						// �ٽ� �߰�
						//----------------------------------------------------
						CGTradeAddItem _CGTradeAddItem;
						_CGTradeAddItem.setTargetObjectID( g_pTradeManager->GetOtherID() );
						_CGTradeAddItem.setItemObjectID( pItem->GetID() );

						pClientPlayer->sendPacket( &_CGTradeAddItem );
						
				}
				else
				{
					//----------------------------------------------------------------
					// ��ȯ���� ���õ� �������̸� �ڵ����� OK�� ��ҵ�����
					// �ƴ� ��������.. �������� OK��ư�� ����ϴ� packet�� ������ �Ѵ�.
					//----------------------------------------------------------------					
					CGTradeFinish _CGTradeFinish;
					_CGTradeFinish.setTargetObjectID( g_pTradeManager->GetOtherID() );
					_CGTradeFinish.setCode( CG_TRADE_FINISH_RECONSIDER );

					pClientPlayer->sendPacket( &_CGTradeFinish );

				}

				PlaySound( pItem->GetInventorySoundID() );
			}
			//----------------------------------------------------------------
			// �߸��� mode
			//----------------------------------------------------------------
			else
			{
				DEBUG_ADD( "[Error] TempMode is Wrong..");
			}
		break;


		//----------------------------------------------------------------------
		//
		//			��ȯ ��󿡼� ���� �߰��ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_MONEY_INCREASE :

			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_ADD_MONEY)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				int money		= g_pTempInformation->Value1;
			
				//if (!g_pMoneyManager->GetOtherMoneyManager->CanAddMoney(money))
				//{
				//	money = g_pMoneyManager->GetOtherMoneyManager->GetMaxAddMoney();
				//}

				//g_pMoneyManager->UseMoney( money );
				//g_pTradeManager->GetMyMoneyManager()->AddMoney( money );

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------
				g_pTradeManager->RefuseOtherTrade();
				g_pTradeManager->RefuseMyTrade();
			}
			else
			{
				DEBUG_ADD( "[Error] TempMode is Wrong..");
			}
		break;

		//----------------------------------------------------------------------
		//
		//			��ȯ ��󿡼� ���� �����ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_MONEY_DECREASE:

			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_REMOVE_MONEY)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				int money		= g_pTempInformation->Value1;
				
				//g_pTradeManager->GetMyMoneyManager()->UseMoney( money );
				//g_pMoneyManager->AddMoney( money );	

				//-----------------------------------------------------------
				// ���� �ٲ�ٸ�... OK���
				//-----------------------------------------------------------
				g_pTradeManager->RefuseOtherTrade();
				g_pTradeManager->RefuseMyTrade();				
			}
			else
			{
				DEBUG_ADD( "[Error] TempMode is Wrong..");
			}
		break;

		//----------------------------------------------------------------------
		// ��ȯ ������ Ȯ���ϴ� ���� ����
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_FINISH_ACCEPT:
			// ������ �ʿ����.
		break;

		//----------------------------------------------------------------------
		//
		//				��ȯ ������ ����ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_FINISH_REJECT:

			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_CLOSE)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				//----------------------------------------------------------------
				// ��ȯâ �ݱ�
				//----------------------------------------------------------------			
				if (g_pTradeManager!=NULL)
				{
					g_pTradeManager->CancelTrade();
				}

				UI_CloseExchange();
			}
		break;

		//----------------------------------------------------------------------
		//
		//				��ȯ ������ ������ϴ� ���� ����
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER:

			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_CANCEL)
			{
				g_pTempInformation->SetMode(TempInformation::MODE_NULL);

				//----------------------------------------------------------------
				// OK ���
				//----------------------------------------------------------------			
				g_pTradeManager->RefuseMyTrade();
			}
		break;

		//----------------------------------------------------------------------
		//
		//					mouse --> inventory Fail
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_FAIL:
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_DROP_TO_INVENTORY)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);
			}
			else
			{
				DEBUG_ADD( "[Error] TempMode is Not MODE_TRADE_VERIFY_DROP_TO_INVENTORY");
			}
		break;


		//----------------------------------------------------------------------
		//
		//					inventory --> mouse Fail
		//
		//----------------------------------------------------------------------
		case GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_FAIL:
			if (g_pTempInformation->GetMode()==TempInformation::MODE_TRADE_VERIFY_PICKUP_FROM_INVENTORY)
			{
				// g_pPlayer->ItemCheckBuffer�� �����ؾߵǴµ�..����.. - -;
				g_pPlayer->ClearItemCheckBuffer();

				g_pTempInformation->SetMode(TempInformation::MODE_NULL);
			}
			else
			{
				DEBUG_ADD( "[Error] TempMode is Not MODE_TRADE_VERIFY_PICKUP_FROM_INVENTORY");
			}
		break;
	}


#endif

	__END_CATCH
}
