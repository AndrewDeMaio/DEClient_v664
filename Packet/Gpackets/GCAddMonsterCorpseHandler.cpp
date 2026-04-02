//--------------------------------------------------------------------------------
//
// Filename    : GCAddMonsterCorpseHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddMonsterCorpse.h"
#include "ClientDef.h"
#include "MItem.h"
#include "MChatManager.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddMonsterCorpseHandler::execute ( GCAddMonsterCorpse * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
	

	// Creature�� �����ؼ� MCorpse�� �߰��ؼ� Zone�� �ִ´�.
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
		//----------------------------------------	
		// �̹� �ִ� Creature�ΰ�?
		//----------------------------------------	
		MCreature* pCreature = g_pZone->GetCreatureOnly( pPacket->getObjectID() );
		
		static bool IsIKilled = false;
		
		// 2005, 1, 18 , sobeit add start - ����, ����, �ƿ� ����� ���͵��� ��ü ����(���Ĵ� ��� ���µ�..��ư..)
		// gcaddslayercorps�� gcaddousterscorps�� ����;� �� �ñ�µ�...��ư...�̷� ���� ������ ����..
		int MonsterType = pPacket->getMonsterType();

		if(MonsterType == 735 || MonsterType == 736 ||MonsterType == 737 || (MonsterType>= 792 && MonsterType<=800))
			return ;

		// 2005, 1, 18 , sobeit add end
		//---------------------------------------------------------
		//
		//					Zone�� ���� ���
		//
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			// �̹� ��ü�� �ֳ�?
			MItem* pItem = g_pZone->GetItem( pPacket->getObjectID() );

			//---------------------------------------------------------
			//
			// ���ο� ��ü�� ����
			//
			//---------------------------------------------------------
			if (pItem==NULL)
			{
				DEBUG_ADD("New MonsterCorpse");
				
				//----------------------------------------	
				//
				// ���� Creature�� �����Ѵ�.
				//
				//----------------------------------------	
				MCreature*	pCreature = new MCreature;

				pCreature->SetZone( g_pZone );
				
				pCreature->SetCreatureType( pPacket->getMonsterType() );
				pCreature->SetGroundCreature();
				pCreature->SetID( pPacket->getObjectID() );
				pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
				pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
				pCreature->SetDirection( pPacket->getDir() );
				pCreature->SetCurrentDirection( pPacket->getDir() );
				
				pCreature->SetStatus( MODIFY_MAX_HP, 100 );
				pCreature->SetStatus( MODIFY_CURRENT_HP, 0 );

				// ��ü�� �ٲ۴�.
				pCreature->SetCorpse();
				//pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
				pCreature->SetName( pPacket->getMonsterName().c_str() );
				pCreature->SetDrainCreatureID( pPacket->getLastKiller() );

				// 2004, 5, 7 sobeit add start - ���� ���� ���� �� �� - ���� ����
				if(pPacket->getLastKiller() == g_pPlayer->GetID() && !IsIKilled)
				{
					ExecuteHelpEvent(HELP_EVENT_KILL);
					IsIKilled = true;
				}
				// 2004, 5, 7 sobeit add end

				// �ӽ÷�..
				pCreature->SetGuildNumber( 1 );				

				
				// �Ӹ��� ������ -_-;
				if (!pPacket->gethasHead())
				{
					pCreature->RemoveHead();
				}

				//----------------------------------------	
				//
				// ��üitem�� �����Ѵ�.
				//
				//----------------------------------------	
				MCorpse* pCorpse = (MCorpse*)MItem::NewItem( ITEM_CLASS_CORPSE );
				pCorpse->SetID( pPacket->getObjectID() );
				pCorpse->SetItemType( 0 );
				pCorpse->SetCreature( pCreature );
				pCorpse->SetPosition( pPacket->getX(), pPacket->getY() );		

				//---------------------------------------------------------
				// ��ü�� ����ִ� Item ���� ����
				//---------------------------------------------------------
				pCorpse->SetNumber( pPacket->getTreasureCount() );


				//----------------------------------------
				// Zone�� Item�߰�
				//----------------------------------------
				if (g_pZone->AddItem( pCorpse ))
				{
					//------------------------------------------------------------
					// Load���� �ʾ����� load�Ѵ�.
					//------------------------------------------------------------
//					LoadCreatureType( pPacket->getMonsterType() );			
				}
				else
				{
					DEBUG_ADD_FORMAT("[Error] Can't add Corpse to Zone. id=%d, xy=(%d, %d)", pPacket->getObjectID(), pPacket->getX(), pPacket->getY());
					
					//---------------------------------------------------------
					// �߰��� �ȵ� ���
					// �̹� �ִ� Item�� �����ϰ� �ٽ� �߰��Ѵ�.
					//---------------------------------------------------------
					TYPE_OBJECTID oldItemID = g_pZone->GetItemID( pPacket->getX(), pPacket->getY() );

					DEBUG_ADD_FORMAT("Remove old Item id=%d", oldItemID);
						
					if (g_pZone->RemoveItem( oldItemID ))				
					{
						// �ٽ� �߰��Ѵ�.
						if (!g_pZone->AddItem( pCorpse ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't add Corpse to Zone, too. id=%d, xy=(%d, %d)", pPacket->getObjectID(), pPacket->getX(), pPacket->getY());
							
							delete pCorpse;
						}
					}
					else
					{
						// �̹� �ִ� item�� ������ �� ���� ���
						DEBUG_ADD_FORMAT("[Error] Can't remove old Item. id=%d, xy=(%d, %d)", oldItemID, pPacket->getX(), pPacket->getY());
						
						delete pCorpse;
					}								
				}
				
				// ũ���� ���� Ʈ���� ����Ʈ ���δ�.
				if(pCreature->GetCreatureType() == 482 ||
				   pCreature->GetCreatureType() == 650 ||
				   pCreature->GetCreatureType() == 819)
				{
					if(pCreature->GetCreatureType() == 482)
					{
						pCreature->AddEffectStatus(EFFECTSTATUS_CLIENTONLY_XMAS_TREE, 0xFFFF);
					}
					else if(pCreature->GetCreatureType() == 819)
					{
						pCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_TOUGH_SNOWMAN_SWORD, 0xFFFF);
						pCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_TOUGH_SNOWMAN_EYES, 0xFFFF);
					}

					// �� ���͸�
					char szBuf[128];
					strcpy(szBuf, pCreature->GetName());
					g_pChatManager->RemoveCurse(szBuf);

					pCreature->SetChatString(szBuf);
				}
			}
			//---------------------------------------------------------
			//
			// �̹� ��ü�� �ִ� ��� 
			//
			//---------------------------------------------------------
			else
			{
				#ifdef	OUTPUT_DEBUG
					if (pItem->GetItemClass()==ITEM_CLASS_CORPSE)
					{
						// ��ü�� �̹� �ִ� ���
						DEBUG_ADD("[Collide] Already Exist the Corpse");
					}					
				#endif								

				//---------------------------------------------------------
				// ��ü�� ����ִ� Item ���� ����
				//---------------------------------------------------------
				pItem->SetNumber( pPacket->getTreasureCount() );
			}

		}
		//---------------------------------------------------------
		//
		//				Zone�� �̹� �ִ� ���
		//
		//---------------------------------------------------------		
		else
		{
			DEBUG_ADD("[Collide] exist Creature");

			if (pCreature->GetCreatureType()!=pPacket->getMonsterType())
			{
				pCreature->SetCreatureType(pPacket->getMonsterType());
				pCreature->SetGroundCreature();
			}

			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );

			//pCreature->SetStatus( MODIFY_MAX_HP, 100 );
			pCreature->SetStatus( MODIFY_CURRENT_HP, 0 );

			//---------------------------------------------------------
			// Creature�� �׿��� �Ѵ�.
			//---------------------------------------------------------
			if (!pCreature->IsDead())
			{
				pCreature->SetStop();
				pCreature->SetDead();		
			}

			pCreature->SetItemCount( pPacket->getTreasureCount() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );
			pCreature->SetDrainCreatureID( pPacket->getLastKiller() );

			// 2004, 5, 7 sobeit add start - ���� ���� ���� �� �� - ���� ����
			if(pPacket->getLastKiller() == g_pPlayer->GetID() && !IsIKilled)
			{
				ExecuteHelpEvent(HELP_EVENT_KILL);
				IsIKilled = true;
			}
			// 2004, 5, 7 sobeit add end
			// �Ӹ��� ������ -_-;
			if (!pPacket->gethasHead())
			{
				pCreature->RemoveHead();
			}
		}

	}

	// [����] ��ü ���� ��
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_ITEM_APPEAR_CORPSE );	
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
