//--------------------------------------------------------------------------------
//
// Filename    : GCAddVampireCorpseHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddVampireCorpse.h"
#include "ClientDef.h"
#include "MItem.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddVampireCorpseHandler::execute ( GCAddVampireCorpse * pPacket , Player * pPlayer )
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
		const PCVampireInfo3 & vi = pPacket->getVampireInfo();

		//----------------------------------------	
		// �̹� �ִ� Creature�ΰ�?
		//----------------------------------------	
		MCreature* pCreature = g_pZone->GetCreatureOnly( vi.getObjectID() );
		
		//---------------------------------------------------------
		//
		//					Zone�� ���� ���
		//
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			// �̹� ��ü�� �ֳ�?
			MItem* pItem = g_pZone->GetItem( vi.getObjectID() );

			//---------------------------------------------------------
			//
			// ���ο� ��ü�� ����
			//
			//---------------------------------------------------------
			if (pItem==NULL)
			{
				//Color_t getHairColor () const { return m_Colors[VAMPIRE_COLOR_HAIR]; }
				//Color_t getSkinColor () const { return m_Colors[VAMPIRE_COLOR_SKIN]; }
				//Color_t getCoatColor ( ColorType colorType = MAIN_COLOR ) const { return m_Colors[VAMPIRE_COLOR_COAT1 + (int)colorType]; }

				//----------------------------------------	
				//
				// ���� Creature�� �����Ѵ�.
				//
				//----------------------------------------	
				DEBUG_ADD("New VampireCorpse");
				
				MCreatureWear*	pDeadCreature = new MCreatureWear;
				pDeadCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );

				pDeadCreature->SetZone( g_pZone );
				
				// creatureType�� Vamp���ڸ� 2, Vamp���ڸ� 3
				//--------------------------------------------------
				// CreatureType ����
				//--------------------------------------------------
				Shape_t shape	= vi.getShape();
				bool bMale		= vi.getSex()==MALE;
				ItemType_t coatType = vi.getCoatType();

				if (vi.getCompetence()==0)
				{
					pDeadCreature->SetCompetence( 0 );
					pDeadCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
					pDeadCreature->SetMale( bMale );
				}
				else
				{
					pDeadCreature->SetCreatureType( GetVampireCreatureType( shape, bMale, coatType ) );
				}

				pDeadCreature->SetMale( bMale );				
				
				// �� �ǹ� ������
				if (pDeadCreature->GetCreatureType()==CREATURETYPE_BAT)
				//if (pDeadCreature->GetCreatureType()==CREATURETYPE_BAT || pDeadCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_GHOST)
				{
					pDeadCreature->SetFlyingCreature();
				}
				else
				{
					pDeadCreature->SetGroundCreature();
				}

				pDeadCreature->SetID( vi.getObjectID() );
				pDeadCreature->SetPosition( vi.getX(), vi.getY() );
				pDeadCreature->SetServerPosition( vi.getX(), vi.getY() );
				pDeadCreature->SetDirection( vi.getDir() );
				pDeadCreature->SetCurrentDirection( vi.getDir() );

				pDeadCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
				pDeadCreature->SetStatus( MODIFY_CURRENT_HP, 0 );
				
				// ��ü�� �ٲ۴�.
				pDeadCreature->SetCorpse();
				pDeadCreature->SetName( vi.getName().c_str() );

				// �ӽ÷�
				pDeadCreature->SetGuildNumber( vi.getGuildID() );
				pDeadCreature->SetOriginServerNum( vi.getBorn() );

				pDeadCreature->SetWeaponSpeed( vi.getAttackSpeed() );
				pDeadCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );

				// ����
				pDeadCreature->SetBodyColor1( vi.getSkinColor() );
				pDeadCreature->SetBodyColor2( vi.getCoatColor() );
				

				//--------------------------------------------------
				// [ TEST CODE ]
				//--------------------------------------------------
				// �� ���� �����ϱ�
				//--------------------------------------------------
				/*
				if (pDeadCreature->IsMale())
				{
					pDeadCreature->SetBodyColor2( 91 );
				}
				else
				{
					pDeadCreature->SetBodyColor2( 38 );
				}
				*/

				// Vampire Coat & Weapon - chyaya
				MCreatureWear* pCreatureWear = dynamic_cast<MCreatureWear*>(pDeadCreature);
				if(pCreatureWear)
					SetAddonToVampire(pCreatureWear, &vi);

				//----------------------------------------	
				//
				// ��üitem�� �����Ѵ�.
				//
				//----------------------------------------	
				MCorpse* pCorpse = (MCorpse*)MItem::NewItem( ITEM_CLASS_CORPSE );
				pCorpse->SetID( vi.getObjectID() );
				pCorpse->SetItemType( 0 );
				pCorpse->SetCreature( pDeadCreature );
				pCorpse->SetPosition( vi.getX(), vi.getY() );		

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
					TYPE_OBJECTID oldItemID = g_pZone->GetItemID( vi.getX(), vi.getY() );

					DEBUG_ADD_FORMAT("Remove old Item id=%d", oldItemID);
						
					if (g_pZone->RemoveItem( oldItemID ))				
					{
						// �ٽ� �߰��Ѵ�.
						if (!g_pZone->AddItem( pCorpse ))
						{
							DEBUG_ADD_FORMAT("[Error] Can't add Corpse to Zone, too. id=%d, xy=(%d, %d)", vi.getObjectID(), vi.getX(), vi.getY());
							
							delete pCorpse;
						}
					}
					else
					{
						// �̹� �ִ� item�� ������ �� ���� ���
						DEBUG_ADD_FORMAT("[Error] Can't remove old Item. id=%d, xy=(%d, %d)", oldItemID, vi.getX(), vi.getY());
						
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
			const PCVampireInfo3 & vi = pPacket->getVampireInfo();

			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );

			Shape_t shape	= vi.getShape();
			bool bMale		= vi.getSex()==MALE;
			ItemType_t coatType = vi.getCoatType();

			int creatureType = GetVampireCreatureType( shape, bMale, coatType );
			
			if(creatureType == CREATURETYPE_BAT && pCreature->IsVampire() && pCreature->IsAdvancementClass())
				creatureType = CREATURETYPE_VAMPIRE_GHOST ; 

			if (pCreature->GetCreatureType()!=creatureType)
			{
				if (vi.getCompetence()==0)
				{
					pCreature->SetCompetence( 0 );
					pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
					pCreature->SetMale( bMale );
				}
				else
				{
					pCreature->SetCreatureType(creatureType);
				}

				pCreature->SetGroundCreature();
			}

			pCreature->MovePosition( vi.getX(), vi.getY() );
			pCreature->SetServerPosition( vi.getX(), vi.getY() );
			pCreature->SetDirection( vi.getDir() );
			pCreature->SetCurrentDirection( vi.getDir() );

		//	pCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, 0 );

			pCreature->SetWeaponSpeed( vi.getAttackSpeed() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );

			// �ӽ÷�
			pCreature->SetGuildNumber( vi.getGuildID() );
			pCreature->SetOriginServerNum( vi.getBorn() );


			// Vampire Coat & Weapon - chyaya
			MCreatureWear* pCreatureWear = dynamic_cast<MCreatureWear*>(pCreature);
			if(pCreatureWear)
				SetAddonToVampire(pCreatureWear, &vi);


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
