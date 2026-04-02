//--------------------------------------------------------------------------------
//
// Filename    : GCAddOustersCorpseHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddOustersCorpse.h"
#include "ClientDef.h"
#include "MItem.h"


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddOustersCorpseHandler::execute ( GCAddOustersCorpse * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
	// Creature�� �����ؼ� MCorpse�� �߰��ؼ� Zone�� �ִ´�.
	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] GCAddOusterCorpseHandler. Zone �� NULL �̿���.");
	}
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{	
		const PCOustersInfo3 & oi = pPacket->getOustersInfo();
		
		//----------------------------------------	
		// �̹� �ִ� Creature�ΰ�?
		//----------------------------------------	
		MCreature* pCreature = g_pZone->GetCreatureOnly( oi.getObjectID() );
		
		//---------------------------------------------------------
		//					Zone�� ���� ���
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			// �̹� ��ü�� �ֳ�?
			MItem* pItem = g_pZone->GetItem( oi.getObjectID() );
			
			//---------------------------------------------------------
			// ���ο� ��ü�� ����
			//---------------------------------------------------------
			if (pItem==NULL)
			{
				//----------------------------------------	
				// ���� Creature�� �����Ѵ�.
				//----------------------------------------	
				DEBUG_ADD("[GCAddOustersCorpseHandler] New OustersCorpse");				
				MCreatureWear*	pDeadCreature = new MCreatureWear;				
				pDeadCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, oi.getAdvancementLevel() );
				pDeadCreature->SetZone( g_pZone );
				
				ItemType_t		coatType	= oi.getCoatType();

				if (oi.getCompetence()==0)
				{
					pDeadCreature->SetCompetence( 0 );
					pDeadCreature->SetCreatureType( CREATURETYPE_OUSTERS_OPERATOR );
				}
				else
				{
					pDeadCreature->SetCreatureType( GetOustersCreatureType( coatType ));
				}
				
				pDeadCreature->SetID( oi.getObjectID() );
				pDeadCreature->SetPosition( oi.getX(), oi.getY() );
				pDeadCreature->SetServerPosition( oi.getX(), oi.getY() );
				pDeadCreature->SetDirection( oi.getDir() );
				pDeadCreature->SetCurrentDirection( oi.getDir() );				
				pDeadCreature->SetStatus( MODIFY_MAX_HP, oi.getMaxHP() );
				pDeadCreature->SetStatus( MODIFY_CURRENT_HP, 0 );				
				// ��ü�� �ٲ۴�.
				pDeadCreature->SetCorpse();
				pDeadCreature->SetName( oi.getName().c_str() );				
				// �ӽ÷�
				pDeadCreature->SetGuildNumber( oi.getGuildID() );
				pDeadCreature->SetOriginServerNum( oi.getBorn() );
				
				pDeadCreature->SetWeaponSpeed( oi.getAttackSpeed() );
				pDeadCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );				
				// ����
				pDeadCreature->SetBodyColor1( oi.getHairColor() );
				pDeadCreature->SetBodyColor2( oi.getCoatColor() );

				SetAddonToOusters( pDeadCreature, &oi );				
				
				//----------------------------------------	
				// ��üitem�� �����Ѵ�.
				//----------------------------------------	
				MCorpse* pCorpse = (MCorpse*)MItem::NewItem( ITEM_CLASS_CORPSE );
				
				pCorpse->SetID( oi.getObjectID() );
				pCorpse->SetItemType( 0 );
				pCorpse->SetCreature( pDeadCreature );
				pCorpse->SetPosition( oi.getX(), oi.getY() );				
				pCorpse->SetNumber( pPacket->getTreasureCount() );
				
				//----------------------------------------
				// Zone�� Item�߰�
				//----------------------------------------
				if (!g_pZone->AddItem( pCorpse ))
				{
					//---------------------------------------------------------
					// �߰��� �ȵ� ���
					// �̹� �ִ� Item�� �����ϰ� �ٽ� �߰��Ѵ�.
					//---------------------------------------------------------
					TYPE_OBJECTID oldItemID = g_pZone->GetItemID( oi.getX(), oi.getY() );
					
					DEBUG_ADD_FORMAT("Remove old Item id=%d", oldItemID);
					
					if (g_pZone->RemoveItem( oldItemID ))				
					{
						// �ٽ� �߰��Ѵ�.
						if (!g_pZone->AddItem( pCorpse ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't add Corpse to Zone, too. id=%d, xy=(%d, %d)", oi.getObjectID(), oi.getX(), oi.getY());
							
							delete pCorpse;
						}
					}
					else
					{
						// �̹� �ִ� item�� ������ �� ���� ���
						DEBUG_ADD_FORMAT("[Error] Can't remove old Item. id=%d, xy=(%d, %d)", oldItemID, oi.getX(), oi.getY());
						
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
			const PCOustersInfo3 & oi = pPacket->getOustersInfo();
		
			ItemType_t coatType = oi.getCoatType();
			
			int creatureType = GetOustersCreatureType( coatType );
			
			if (pCreature->GetCreatureType()!=creatureType)
			{
				if (oi.getCompetence()==0)
				{
					pCreature->SetCompetence( 0 );
					pCreature->SetCreatureType( CREATURETYPE_OUSTERS_OPERATOR );
				}
				else
				{
					pCreature->SetCreatureType(creatureType);
				}
				
				pCreature->SetGroundCreature();
			}			
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, oi.getAdvancementLevel() );
			pCreature->MovePosition( oi.getX(), oi.getY() );
			pCreature->SetServerPosition( oi.getX(), oi.getY() );
			pCreature->SetDirection( oi.getDir() );
			pCreature->SetCurrentDirection( oi.getDir() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, 0 );
			
			pCreature->SetWeaponSpeed( oi.getAttackSpeed() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );

			pCreature->SetGuildNumber( oi.getGuildID() );
			pCreature->SetOriginServerNum( oi.getBorn() );

			
			//---------------------------------------------------------
			// Creature�� �׿��� �Ѵ�.
			//---------------------------------------------------------
			if (!pCreature->IsDead())
			{
				pCreature->SetStop();			
				pCreature->SetDead();		
			}			
			pCreature->SetItemCount( pPacket->getTreasureCount() );
			SetAddonToOusters( dynamic_cast<MCreatureWear*>(pCreature), &oi );			
		}
	}		
	__END_CATCH
}
