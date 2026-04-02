//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopBuyOKHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShopBuyOK.h"
#include "ClientDef.h"
#include "MShop.h"
#include "MShopShelf.h"
#include "MInventory.h"
#include "TempInformation.h"
#include "MMoneyManager.h"
#include "MPriceManager.h"
#include "MItemFinder.h"
#include "UIFunction.h"

#define SAFE_DELETE(x)		{ if(x!=NULL) delete x; x=NULL; }

// PacketFunction.cpp�� �ִ�. compile �ð� �����..
void	CheckItemForSkillIcon(const MItem* pItem);

void GCShopBuyOKHandler::execute ( GCShopBuyOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	//--------------------------------------------------------------
	// Item ��� packet�� �޴°� �³�?
	//--------------------------------------------------------------
	if (g_pTempInformation->GetMode() == TempInformation::MODE_SHOP_BUY)
	{
		MShop* pShop = (MShop*)g_pTempInformation->pValue;		
		int ShelfType	= g_pTempInformation->Value1;
		int index		= g_pTempInformation->Value2;
		int x			= g_pTempInformation->Value3;
		int y			= g_pTempInformation->Value4;

		DEBUG_ADD_FORMAT("[BuyOK] TempInfo. ShelfType=%d, index=%d, xy=(%d, %d)", ShelfType, index, x, y);
		
		
		MShopShelf* pShopShelf = pShop->GetShelf( ShelfType );

		//--------------------------------------------------------------
		// �������� item�� �����Ѵ�.			
		//--------------------------------------------------------------
		if (pShopShelf!=NULL)
		{
			//------------------------------------------------------
			// Normal shelf�� �ƴ� ��쿡�� delete�Ѵ�.
			//------------------------------------------------------
			if (ShelfType==SHOP_RACK_SPECIAL)
			{
				pShopShelf->DeleteItem( index );
			}

			// ������ Version�� �ٲ۴�.
			pShopShelf->SetVersion( pPacket->getShopVersion() );
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] No Shelf.. type=%d", ShelfType);
		}

		//--------------------------------------------------------------
		// ��� ������ item�� �����Ѵ�.
		//--------------------------------------------------------------		
		MItem* pItem = MItem::NewItem( (ITEM_CLASS)pPacket->getItemClass() );

		pItem->SetID( pPacket->getItemObjectID() );
		pItem->SetItemType( pPacket->getItemType() );
		pItem->SetItemOptionList( pPacket->getOptionType() );
		pItem->SetNumber( pPacket->getItemNum() );	// �̹� �׿��� ����
		pItem->SetCurrentDurability( pPacket->getDurability() );
		pItem->SetSilver( pPacket->getSilver() );
		pItem->SetGrade( pPacket->getGrade() );
		pItem->SetEnchantLevel( pPacket->getEnchantLevel() );

		const MItem* pOldItem = g_pInventory->GetItem( x, y );

		//--------------------------------------------------------------		
		// �� ��ġ�� �ƹ��͵� ���� ��� --> �׳� �߰��ϸ� �ȴ�.
		//--------------------------------------------------------------				
		if (pOldItem==NULL)
		{				
		}
		//--------------------------------------------------------------		
		// ���� �� �ִ��� üũ�Ѵ�.
		//--------------------------------------------------------------				
		else
		{
			if (pOldItem->GetID()	== pItem->GetID())
			{
				if (pItem->IsInsertToItem( pOldItem ))
				{
					int total = //pOldItem->GetNumber() + 
								pItem->GetNumber();
					
					//------------------------------------------------
					// ���� �ʰ�					
					//------------------------------------------------
					if ( total > pItem->GetMaxNumber() )
					{
						DEBUG_ADD_FORMAT("[Error] Cannot Add. MaxNum exceed=%d", total);
					}
					//------------------------------------------------
					// ���������� �׿��� �� �ִ� ���					
					//------------------------------------------------
					else
					{
						//pItem->SetNumber( total );

						// ������ �ִ� item�� �����Ѵ�.
						MItem* pRemovedItem = g_pInventory->RemoveItem( x, y );
						
						SAFE_DELETE( pRemovedItem );

	//					if (pRemovedItem!=NULL)
	//					{
	//						delete pRemovedItem;
	//					}
					}
				}
				else
				{
					DEBUG_ADD("[Error] Cannot Add. No match item");
				}
			}
		}

		//--------------------------------------------------------------
		// item�� inventory�� �߰��Ѵ�.
		//--------------------------------------------------------------
		if (g_pInventory->AddItem( pItem, x, y ))
		{
			// ����� �߰��� ��� --> sound���
			PlaySound( pItem->GetTileSoundID() );

			// skill icon üũ
			CheckItemForSkillIcon( pItem );
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] Cannot Add to Inventory(%d,%d)", x,y);
			
			// �߰��� �ȵǴ� ��� ������ �Ѵ�.
			delete pItem;
		}
	
		//--------------------------------------------------------------
		// ������ ���� ���� ��°�?..
		//--------------------------------------------------------------
		switch (pShop->GetShopType())
		{
			//--------------------------------------------------------------
			// ��
			//--------------------------------------------------------------
			case MShop::SHOP_NORMAL :
				//--------------------------------------------------------------
				// ���� �ٲ��ش�.
				//--------------------------------------------------------------
				if (!g_pMoneyManager->SetMoney( pPacket->getPrice() ))
				{
					DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), pPacket->getPrice());
				}
			break;

			//--------------------------------------------------------------
			// ��
			//--------------------------------------------------------------
			case MShop::SHOP_EVENT_STAR :
				// ������ ������ŭ�� inventory���� �����ش�.
				if (pItem!=NULL)
				{
					STAR_ITEM_PRICE starPrice;

					g_pPriceManager->GetItemPrice( pItem, starPrice );

					int remainNum = starPrice.number;

					if (starPrice.type!=-1 && starPrice.number!=0)
					{
						// ��� �ִ��� ã�ƺ���.
						MItemClassTypeFinder starFinder(ITEM_CLASS_EVENT_STAR, starPrice.type);

						// ������ŭ inventory���� �����Ѵ�.
						while (remainNum > 0)
						{
							MItem* pStarItem = g_pInventory->FindItemGridOrder( starFinder );

							// ���� ���� ��� - -;
							if (pStarItem==NULL)
							{
								DEBUG_ADD("[Error] Not Enough Star -_-");
								break;
							}

							int itemNum = pStarItem->GetNumber();

							if (itemNum > remainNum)
							{
								pStarItem->SetNumber( itemNum - remainNum );
								remainNum = 0;
							}
							else
							{
								// ���ų� ���� ���
								remainNum -= itemNum;

								MItem* pRemovedItem = g_pInventory->RemoveItem( 
																pStarItem->GetGridX(), 
																pStarItem->GetGridY() );

								if (pRemovedItem!=NULL)
								{
									delete pRemovedItem;
								}
								else
								{
									DEBUG_ADD_FORMAT("[Error] Can't remove star(%d, %d)", pStarItem->GetGridX(), pStarItem->GetGridY());
								}
							}
						}
					}
				}
			break;
		}

		
		// mode�� ���ش�.
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);

		// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
		UI_UnlockItemTrade();

		//--------------------------------------------------------------
		// ������� (���踦) �� ���
		//--------------------------------------------------------------
//		__BEGIN_HELP_EVENT
//			if (pItem->GetItemClass()==ITEM_CLASS_KEY 
//				&& pItem->GetItemType()==2)
//			{
//				// [����] ������� �� ���
////				ExecuteHelpEvent( HE_ITEM_BUY_MOTORCYCLE );
//			}
//		__END_HELP_EVENT
	}
	else
	{
		DEBUG_ADD("[Error] Buy? -_-; No Temp Information!");
	}

#endif

	__END_CATCH
}
