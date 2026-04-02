//--------------------------------------------------------------------------------
//
// Filename    : GCAddSlayerCorpseHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddSlayerCorpse.h"
#include "ClientDef.h"
#include "MItem.h"
#include "AddonDef.h"
#include "DrawTypeDef.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddSlayerCorpseHandler::execute ( GCAddSlayerCorpse * pPacket , Player * pPlayer )
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
		const PCSlayerInfo3 & si = pPacket->getSlayerInfo();	
			
		//----------------------------------------	
		// �̹� �ִ� Creature�ΰ�?
		//----------------------------------------	
		MCreature* pCreature = g_pZone->GetCreatureOnly( si.getObjectID() );
		
		//---------------------------------------------------------
		//
		//					Zone�� ���� ���
		//
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			// �̹� ��ü�� �ֳ�?
			MItem* pItem = g_pZone->GetItem( si.getObjectID() );

			//---------------------------------------------------------
			//
			// ���ο� ��ü�� ����
			//
			//---------------------------------------------------------
			if (pItem==NULL)
			{
				DEBUG_ADD("New SlayerCorpse");
				
				//----------------------------------------	
				//
				// ���� Creature�� �����Ѵ�.
				//
				//----------------------------------------	
				MCreatureWear*	pDeadCreature = new MCreatureWear;
				
				pDeadCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, si.getAdvancementLevel() );

				pDeadCreature->SetZone( g_pZone );
				
				//----------------------------------------	
				// ������ �����Ѵ�.
				//----------------------------------------					
				if (si.getCompetence()==0)
				{
					pDeadCreature->SetCompetence( 0 );
					pDeadCreature->SetCreatureType( CREATURETYPE_SLAYER_OPERATOR );
					pDeadCreature->SetMale( si.getSex()==MALE );
				}
				else
				{
					pDeadCreature->SetCreatureType( (si.getSex()==MALE)? CREATURETYPE_SLAYER_MALE : CREATURETYPE_SLAYER_FEMALE );
				}

				pDeadCreature->SetGuildNumber( si.getGuildID() );
				pDeadCreature->SetOriginServerNum( si.getBorn() );

				// creatureType�� Slayer���ڸ� 0, Slayer���ڸ� 1 
				pDeadCreature->SetGroundCreature();
				pDeadCreature->SetID( si.getObjectID() );
				pDeadCreature->SetPosition( si.getX(), si.getY() );
				pDeadCreature->SetServerPosition( si.getX(), si.getY() );
				pDeadCreature->SetDirection( si.getDir() );
				pDeadCreature->SetCurrentDirection( si.getDir() );

				// �Ǻλ�
				pDeadCreature->SetBodyColor1( si.getSkinColor() );

				pDeadCreature->SetStatus( MODIFY_MAX_HP, si.getMaxHP() );
				pDeadCreature->SetStatus( MODIFY_CURRENT_HP, 0 );			
				
				SetAddonToSlayer( pDeadCreature, &si );	

				// ��ü�� �ٲ۴�.
				pDeadCreature->SetCorpse();
				pDeadCreature->SetName( si.getName().c_str() );				

				//----------------------------------------	
				//
				// ��üitem�� �����Ѵ�.
				//
				//----------------------------------------	
				MCorpse* pCorpse = (MCorpse*)MItem::NewItem( ITEM_CLASS_CORPSE );
				pCorpse->SetID( si.getObjectID() );
				pCorpse->SetItemType( 0 );
				pCorpse->SetCreature( pDeadCreature );
				pCorpse->SetPosition( si.getX(), si.getY() );	
				
				pCorpse->SetNumber( pPacket->getTreasureCount() );

				//----------------------------------------
				// Zone�� Item�߰�
				//----------------------------------------
				if (!g_pZone->AddItem( pCorpse ))
				{
					DEBUG_ADD("[Error] Can't Add to Zone.");
					
					//---------------------------------------------------------
					// �߰��� �ȵ� ���
					// �̹� �ִ� Item�� �����ϰ� �ٽ� �߰��Ѵ�.
					//---------------------------------------------------------
					TYPE_OBJECTID oldItemID = g_pZone->GetItemID( si.getX(), si.getY() );

					DEBUG_ADD_FORMAT("Remove old Item id=%d", oldItemID);
						
					if (g_pZone->RemoveItem( oldItemID ))				
					{
						// �ٽ� �߰��Ѵ�.
						if (!g_pZone->AddItem( pCorpse ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't add Corpse to Zone, too. id=%d, xy=(%d, %d)", si.getObjectID(), si.getX(), si.getY());
							
							delete pCorpse;
						}
					}
					else
					{
						// �̹� �ִ� item�� ������ �� ���� ���
						DEBUG_ADD_FORMAT("[Error] Can't remove old Item. id=%d, xy=(%d, %d)", oldItemID, si.getX(), si.getY());
						
						delete pCorpse;
					}	
				}				
			}
			//---------------------------------------------------------
			//
			// �̹� ��ü�� �ִ� ��� 
			//
			//---------------------------------------------------------
			else
			{
				DEBUG_ADD_FORMAT("[Error] Already Exist Another Item : class=%d type=%d", (int)pItem->GetItemClass(), (int)pItem->GetItemType());
				
				if (pItem->GetItemClass()==ITEM_CLASS_CORPSE)
				{
					//---------------------------------------------------------					
					// ��ü�� �̹� �ִ� ���
					// ��ü�� ����ִ� Item ���� ����
					//---------------------------------------------------------
					pItem->SetNumber( pPacket->getTreasureCount() );
				}
				else
				{
					DEBUG_ADD("The Item is Not Corpse");
				}
			}
		}
		//---------------------------------------------------------
		//
		//				Zone�� �̹� �ִ� ���
		//
		//---------------------------------------------------------		
		else
		{
			DEBUG_ADD_FORMAT("Already Exist Creature. Set Dead id=%d", si.getObjectID());

			const PCSlayerInfo3 & si = pPacket->getSlayerInfo();

			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, si.getAdvancementLevel() );

			int creatureType = ((si.getSex()==MALE)? CREATURETYPE_SLAYER_MALE : CREATURETYPE_SLAYER_FEMALE);

			if (pCreature->GetCreatureType()!=creatureType)
			{
				if (si.getCompetence()==0)
				{
					pCreature->SetCompetence( 0 );
					pCreature->SetCreatureType( CREATURETYPE_SLAYER_OPERATOR );
					pCreature->SetMale( si.getSex()==MALE );
				}
				else
				{
					pCreature->SetCreatureType(creatureType);
				}

				pCreature->SetGroundCreature();				
			}

			pCreature->SetGuildNumber( si.getGuildID() );
			pCreature->SetOriginServerNum( si.getBorn() );
			
			pCreature->MovePosition( si.getX(), si.getY() );
			pCreature->SetServerPosition( si.getX(), si.getY() );
			pCreature->SetDirection( si.getDir() );
			pCreature->SetCurrentDirection( si.getDir() );			
			
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
		}
	}

#endif

	__END_CATCH
}
