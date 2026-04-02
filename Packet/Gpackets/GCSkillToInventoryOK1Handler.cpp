//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToInventoryOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToInventoryOK1.h"
#include "ClientDef.h"
#include "ClientFunction.h"
#include "MInventory.h"
#include "MSkillManager.h"
#include "SkillDef.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"

extern bool				g_bZonePlayerInLarge;
extern int				g_nZoneLarge;
extern int				g_nZoneSmall;
extern int				g_MorphCreatureType;


MItem*	PacketSkillToMakeItem(MItem* pItem,
						  ITEM_CLASS itemClass, 
						  int itemType,
						  int itemID,
						  int x, int y, 
						  int targetX, int targetY);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1Handler::execute ( GCSkillToInventoryOK1 * pPacket, Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__


	//------------------------------------------------------------------
	// Player�� ��ٸ��� skill�� ���������� �����޾Ҵ�.
	//------------------------------------------------------------------	
	if (1)//g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_SKILL_SUCCESS)
	{		
		g_pPlayer->SetWaitVerifyNULL();

		//------------------------------------------------------------------	
		// Item Check Buffer�� Ȯ���Ѵ�.
		//------------------------------------------------------------------
		MItem* pItem = g_pPlayer->GetItemCheckBuffer();

		//----------------------------------------------------
		// Check Buffer�� item�� �ִ� ���
		//----------------------------------------------------
		if (pItem!=NULL)
		{
			MPlayer::ITEM_CHECK_BUFFER status =	g_pPlayer->GetItemCheckBufferStatus();

			//----------------------------------------------------
			// Inventory�� item�� ���
			//----------------------------------------------------
			if (status==MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY)			
			{
				DWORD dwSubInventoryID = g_pPlayer->GetItemIDCheckBufferSubInventory();

				//--------------------------------------------------
				// Item Check Buffer�� �����.
				//--------------------------------------------------
				g_pPlayer->ClearItemCheckBuffer();
		
				// ���� �ð� ��ȯ
				DWORD delayFrame = 32;//ConvertDurationToFrame( pPacket->getDuration() );
					
				//pPacket->getX(),	
				//pPacket->getY(), 
				//pPacket->getCEffectID();				
				int				skillID = pPacket->getSkillType();
				
				if( skillID >= g_pActionInfoTable->GetSize() )
					return;
				TYPE_OBJECTID	itemID	= pItem->GetID();

				switch (skillID)
				{
					//----------------------------------------------------
					// ����/��ź/���� �����
					//----------------------------------------------------
					case MAGIC_CREATE_HOLY_WATER :
					case SKILL_MAKE_BOMB :
					case SKILL_MAKE_MINE :					
					case SKILL_CREATE_HOLY_POTION :
					case SKILL_ABSORB_SOUL:
					{
						// pItem�� �����ϰ� holy water�� �߰��Ѵ�.
						int x		= pItem->GetGridX();
						int y		= pItem->GetGridY();
						int targetX = pPacket->getX();
						int targetY = pPacket->getY();
						int itemType = pPacket->getItemType();
						int newItemID	= pPacket->getObjectID();
						int	ItemNum = pItem->GetNumber();
						
						ITEM_CLASS itemClass;
						
						if (skillID==MAGIC_CREATE_HOLY_WATER)	itemClass = ITEM_CLASS_HOLYWATER;
						if (skillID==SKILL_MAKE_BOMB)			itemClass = ITEM_CLASS_BOMB;
						if (skillID==SKILL_MAKE_MINE)			itemClass = ITEM_CLASS_MINE;
						if (skillID==SKILL_ABSORB_SOUL)			itemClass = ITEM_CLASS_PUPA;
						if (skillID==SKILL_CREATE_HOLY_POTION)
						{
							itemClass = ITEM_CLASS_POTION;
							itemType = (*g_pItemTable)[pItem->GetItemClass()][pItem->GetItemType()].Value3;
						}							

						MItem* pResultItem = PacketSkillToMakeItem(pItem,
																	itemClass, 
																	itemType,
																	newItemID,
																	x, y,
																	targetX, targetY);
						if (pResultItem!=NULL)
						{
							itemID = pResultItem->GetID();
							if( skillID == MAGIC_CREATE_HOLY_WATER )
								pResultItem->SetNumber( ItemNum );
						}

						// ��� üũ..
						//g_SkillAvailable.CheckMP();					
					}
					break;

					//----------------------------------------------------
					// Install Mine
					//----------------------------------------------------
					case SKILL_INSTALL_MINE :
						// Inventory���� ����ϰ� �����.
						g_pPlayer->SetItemCheckBuffer( pItem, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);

						UseItemOK();

						// inventory effect
						skillID = SKILL_INSTALL_MINE;

						delayFrame = 14;

						g_pSkillAvailable->SetAvailableSkills();
					break;

					//----------------------------------------------------
					// Vampire Portal
					//----------------------------------------------------
					case MAGIC_BLOODY_TUNNEL :
						// Inventory���� ����ϰ� �����.
						g_pPlayer->SetItemCheckBuffer( pItem, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY, dwSubInventoryID);

						UseItemOK();

						// inventory effect
						skillID = MAGIC_BLOODY_MARK;

						delayFrame = 14;
					break;

					case MAGIC_BLOODY_MARK :
						//-------------------------------------------------
						// VampirePortal�� ���
						//-------------------------------------------------
						if (pItem->GetItemClass()==ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
						{
							MVampirePortalItem* pPortalItem = (MVampirePortalItem*)pItem;

							if (!pPortalItem->IsMarked())
							{
								int zoneID = (g_bZonePlayerInLarge? g_nZoneLarge : g_nZoneSmall);
								int zoneX = g_pPlayer->GetServerX();
								int zoneY = g_pPlayer->GetServerY();
								pPortalItem->SetZone(zoneID, zoneX, zoneY);
							}
						}

						// inventory effect
						skillID = MAGIC_BLOODY_MARK;

						delayFrame = 14;
					break;

					//----------------------------------------------------
					// ���� / ���� ����
					//----------------------------------------------------
					case MAGIC_TRANSFORM_TO_WOLF :
					case MAGIC_TRANSFORM_TO_BAT :
					case SKILL_TRANSFORM_TO_WERWOLF :
					{
						//----------------------------------------------------
						// pItem�� �����Ѵ�.
						//----------------------------------------------------
						/*
						int x = pItem->GetGridX();
						int y = pItem->GetGridY();
						
						MItem* pRemovedItem = g_pInventory->RemoveItem( x, y );

						if (pRemovedItem!=NULL)
						{
							delete pRemovedItem;
						}
						else
						{
							DEBUG_ADD_FORMAT("[Error] No Removed Item from Inventory=(%d, %d)", x, y);
						}
						*/
						// Inventory���� ����ϰ� �����.
						g_pPlayer->SetItemCheckBuffer( pItem, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY, dwSubInventoryID);

						UseItemOK();

						//----------------------------------------------------
						// ����
						//----------------------------------------------------
						MActionResult* pResult = new MActionResult;

						const int wolfCreatureType			= CREATURETYPE_WOLF;
						const int batCreatureType			= CREATURETYPE_BAT;
						const int werwolfCreatureType		= CREATURETYPE_WER_WOLF;
						const int ghostCreatureType			= CREATURETYPE_VAMPIRE_GHOST;
#if __CONTENTS(__FAST_TRANSFORTER)
						const int flittermouseCreatureType	= CREATURETYPE_FLITTERMOUSE;
#endif //__FAST_TRANSFORTER
						int resultSkillID;

						int creatureType = 0;

						if (skillID==MAGIC_TRANSFORM_TO_WOLF)
						{
							pResult->Add( new MActionResultNodeChangeCreatureType( g_pPlayer->GetID(), wolfCreatureType ) );
							resultSkillID = RESULT_MAGIC_TRANSFORM_TO_WOLF;							

							creatureType = wolfCreatureType;
						}
						else if ( skillID == SKILL_TRANSFORM_TO_WERWOLF )
						{
							pResult->Add( new MActionResultNodeChangeCreatureType( g_pPlayer->GetID(), werwolfCreatureType ) );
							resultSkillID = RESULT_SKILL_TRANSFORM_TO_WERWOLF;
							
							creatureType = werwolfCreatureType;
						}
						else	// MAGIC_TRANSFORM_TO_BAT
						{
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
							if(pPacket->getItemClass() == ITEM_CLASS_VAMPIREWING_ITEM)
							{
								if(pPacket->getItemType()==0)
								{
									creatureType = flittermouseCreatureType;
									g_pPlayer->SetWingEffect1();
								}
#if __CONTENTS(__SECOND_TRANSFORTER)
								else if(pPacket->getItemType()==1)
								{
									creatureType = CREATURETYPE_SHAPE_OF_DEMON;
									g_pPlayer->SetWingEffect2();
								}
#endif //__SECOND_TRANSFORTER
							}
							// ���� �����̾� ĳ������ ��� ���㰡 �ƴ϶� ����Ʈ��.
							else 
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
							if( g_pPlayer->IsVampire() && g_pPlayer->IsAdvancementClass() )
							{
								creatureType = ghostCreatureType;
								g_pPlayer->SetAdvanceBatEffect();
							}
							else
							{
								creatureType = batCreatureType;
							}

							pResult->Add( new MActionResultNodeChangeCreatureType( g_pPlayer->GetID(), creatureType ) );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
							if(pPacket->getItemClass() == ITEM_CLASS_VAMPIREWING_ITEM)
							{
								if(pPacket->getItemType()==0)
									resultSkillID = SKILL_CLIENT_FLITTERMOUSE;
#if __CONTENTS(__SECOND_TRANSFORTER)
								if(pPacket->getItemType()==1)
									resultSkillID = SKILL_CLIENT_SHAPE_OF_DEMON;
#endif //__SECOND_TRANSFORTER
							}
							else
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
								resultSkillID = RESULT_MAGIC_TRANSFORM_TO_BAT;
						}							

						//--------------------------------------------------
						// ���� ����Ʈ�� ��� �߰�
						//--------------------------------------------------
						ExecuteActionInfoFromMainNode(
							resultSkillID,										// ��� ��� ��ȣ
						
							g_pPlayer->GetX(), g_pPlayer->GetY(), 0,
							g_pPlayer->GetDirection(),														// ��� ����
							
							OBJECTID_NULL,												// ��ǥ�� ���� ����
							g_pPlayer->GetX(), g_pPlayer->GetY(), 0, 
							
							0,													// ����� (����) ���� �ð�		
							
							pResult, //NULL,
							
							false);			// ��� ÷���� �����Ѵ�.

						g_pPlayer->SetDelay( 1000 );

						//--------------------------------------------------
						// ���� ó���� ����� �ȵǰ� 
						// �ٸ� ������ �Ѿ�� ��찡 �־
						// �ӽ÷�.. -_-;
						// �̰Ŵ� MActionResultNodeChangeCreatureType��
						// GCUpdateInfoHandler���� �����Ѵ�.
						//--------------------------------------------------
						g_MorphCreatureType = creatureType;


						//--------------------------------------------------
						// ��� üũ..
						//--------------------------------------------------
						g_pSkillAvailable->SetAvailableSkills();
							
					}
					break;
				}

				
				// Inventory�� Item�� ����� ����ؾ� �Ѵ�.
				AddNewInventoryEffect( itemID,
										skillID + (*g_pActionInfoTable).GetMinResultActionInfo(),
										delayFrame
									);

			}
			//----------------------------------------------------
			// �ٸ� ����??
			//----------------------------------------------------
			else
			{
				DEBUG_ADD_FORMAT("[Error] ItemCheck Buffer is not Use Status: status=%d", (int)status);
			}
		}
		
	}
	else
	{
		DEBUG_ADD("[Error] Player is not WaitVerifySkillSuccess");
	}

	int skillID = pPacket->getSkillType();
	int resultActionInfo = skillID + (*g_pActionInfoTable).GetMinResultActionInfo();
	
	//------------------------------------------------------------
	// Delay Frame ����
	//------------------------------------------------------------
	DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );
	g_pPlayer->SetEffectDelayFrame(resultActionInfo, delayFrame );

	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	//------------------------------------------------------------------
	// effect status�� �����Ų��.
	//------------------------------------------------------------------
	if (g_pPlayer->GetEFFECT_STAT()!=EFFECTSTATUS_NULL)
	{
		//int esDelayFrame = ConvertDurationToFrame( g_pPlayer->GetDURATION() );

		// effect�� ���δ�.
		g_pPlayer->AddEffectStatus((EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), delayFrame);	
		
		g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
	}
	else
	{
		//------------------------------------------------------
		// EffectStatus�� �ִٸ� ���δ�.
		//------------------------------------------------------
		EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();

		
		if (es!=EFFECTSTATUS_NULL)
		{
			g_pPlayer->AddEffectStatus( es, delayFrame );
		}
	}

#endif

	__END_CATCH
}

//-------------------------------------------------------------------------------
// Make Item To Inventory
//-------------------------------------------------------------------------------
// pItem�� ����� ��������� �ٸ� item�� inventory�� �����Ǵ� �� ó���Ѵ�.
//
// ����� ������ ���ο� ������
// (Ȥ�� ������ �ִ� �����ۿ� ���� ���� ���� ������)�� pointer�� �ѱ��.
//-------------------------------------------------------------------------------
MItem*
PacketSkillToMakeItem(MItem* pItem,
						  ITEM_CLASS itemClass,
						  int itemType,
						  int itemID,
						  int x, int y, 
						  int targetX, int targetY)
{
	if (pItem==NULL || g_pInventory==NULL)
	{
		return NULL;
	}

	//----------------------------------------------------
	// 1�� ���� ����̰ų�
	// ���� ��ġ�̸�.. ������ ���ش�.
	//----------------------------------------------------
	if ((pItem->GetNumber()==1 || x==targetX && y==targetY)  && (itemClass != ITEM_CLASS_VAMPIRE_PORTAL_ITEM))
	{
		MItem* pRemovedItem = g_pInventory->RemoveItem( x, y );

		if (pRemovedItem!=NULL)
		{
			delete pRemovedItem;
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] No Removed Item from Inventory=(%d, %d)", x, y);
		}
	}
	//----------------------------------------------------
	// ������ �ִ°Ÿ� ������ �ϳ� ���̸� �ȴ�.
	//----------------------------------------------------
	else if(itemClass != ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
	{
		//if (pItem->GetNumber() > 1)								
		pItem->SetNumber( pItem->GetNumber() - 1 );
	}

	MItem* pTargetItem = g_pInventory->GetItem( targetX, targetY );

	//----------------------------------------------------
	// ���� ���� �������� ���� ���
	//----------------------------------------------------
	if (pTargetItem==NULL)
	{							
		MItem* pResultItem = MItem::NewItem( itemClass );
		pResultItem->SetID( itemID );
		pResultItem->SetItemType( itemType );
		//pHolyWater->SetItemOption(
		pResultItem->SetGridXY( targetX, targetY );

		if (!g_pInventory->AddItem( pResultItem, targetX, targetY ))
		{
			DEBUG_ADD_FORMAT("[Error] Cannot Add pResultItem to Inventory=(%d, %d)", targetX, targetY);
			
			delete pResultItem;
		}
		else
		{
			return pResultItem;
		}
	}
	//----------------------------------------------------
	// ���� ���� �������� �ִ� ���
	//----------------------------------------------------	
	else
	{
		// Ȯ��.. ���� �ʿ�����ŵ� ������..
		if (pTargetItem->GetItemClass()==itemClass
			&& pTargetItem->GetItemType()==itemType
			&& pTargetItem->GetID()==itemID)
		{
			// Max üũ�� ����..
			pTargetItem->SetNumber( pTargetItem->GetNumber() + 1 );

			return pTargetItem;
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] Wrong Item. tcls=%d, ttype=%d, tid=%d, type=%d, id=%d", 
											pTargetItem->GetItemClass(), 
											pTargetItem->GetItemType(), 
											pTargetItem->GetID(),
											itemType,
											itemID);
		}
	}

	return NULL;
}