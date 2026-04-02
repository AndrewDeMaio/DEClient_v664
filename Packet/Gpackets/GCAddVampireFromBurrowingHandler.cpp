//--------------------------------------------------------------------------------
//
// Filename    : GCAddVampireFromBurrowingHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddVampireFromBurrowing.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "MTestDef.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddVampireFromBurrowingHandler::execute ( GCAddVampireFromBurrowing * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


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
		const PCVampireInfo3 & vi = pPacket->getVampireInfo ();

		MCreature* pCreature = g_pZone->GetCreature(vi.getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );

			pCreature->SetZone( g_pZone );

	
			//pCreature->SetCreatureType( 0 );
			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			Shape_t shape	= vi.getShape();
			bool bMale		= vi.getSex()==MALE;
			ItemType_t coatType = vi.getCoatType();

			if (vi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
				pCreature->SetMale( bMale );
			}
			else
			{
				pCreature->SetCreatureType( GetVampireCreatureType( shape, bMale, coatType ) );
			}

			pCreature->SetMale( bMale );

			if (pCreature->GetCreatureType()==CREATURETYPE_BAT)
			//if (pCreature->GetCreatureType()==CREATURETYPE_BAT || pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_GHOST)
			{
				pCreature->SetFlyingCreature();
			}
			else
			{
				pCreature->SetGroundCreature();
			}

			pCreature->SetName( vi.getName().c_str() );
			
			pCreature->SetOriginServerNum(vi.getBorn()) ;  
			// �ӽ÷�
			pCreature->SetGuildNumber( vi.getGuildID() );
			pCreature->SetOriginServerNum( vi.getBorn() );
			
			pCreature->SetID(vi.getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( vi.getX(), vi.getY() );
			pCreature->SetServerPosition( vi.getX(), vi.getY() );
			pCreature->SetDirection( vi.getDir() );
			pCreature->SetCurrentDirection( vi.getDir() );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, vi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );

			// ����
			pCreature->SetBodyColor1( vi.getSkinColor() );
			pCreature->SetBodyColor2( vi.getCoatColor() );

			// speed
			pCreature->SetWeaponSpeed( vi.getAttackSpeed() );

			
			//--------------------------------------------------
			// [ TEST CODE ]
			//--------------------------------------------------
			// �� ���� �����ϱ�
			//--------------------------------------------------
			/*
			if (pCreature->IsMale())
			{
				pCreature->SetBodyColor2( 91 );
			}
			else
			{
				pCreature->SetBodyColor2( 38 );
			}
			*/


			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
				pCreature = NULL;
			}

#ifdef __METROTECH_TEST__
			extern int	g_iSpeed;
			if(g_iSpeed < 0)
				g_iSpeed = -1;
#endif
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�̸�.
		//--------------------------------------------------
		else
		{
			pCreature->SetZone( g_pZone );
			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );

			pCreature->SetName( vi.getName().c_str() );

			// �ӽ÷�
			pCreature->SetGuildNumber( vi.getGuildID() );
			pCreature->SetOriginServerNum( vi.getBorn() );

			//pCreature->SetCreatureType( 0 );
			//--------------------------------------------------
			// CreatureType ����
			//--------------------------------------------------
			Shape_t shape	= vi.getShape();
			bool bMale		= vi.getSex()==MALE;
			ItemType_t coatType = vi.getCoatType();

			if (vi.getCompetence()==0)
			{
				pCreature->SetCompetence( 0 );
				pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
				pCreature->SetMale( bMale );
			}
			else
			{
				pCreature->SetCreatureType( GetVampireCreatureType( shape, bMale, coatType ) );
			}

			pCreature->SetMale( bMale );

			if (pCreature->GetCreatureType()==CREATURETYPE_BAT)
			//if (pCreature->GetCreatureType()==CREATURETYPE_BAT || pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_GHOST)
			{
				pCreature->SetFlyingCreature();
			}
			else
			{
				pCreature->SetGroundCreature();
			}

			pCreature->SetID(vi.getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( vi.getX(), vi.getY() );
			pCreature->SetServerPosition( vi.getX(), vi.getY() );			
			pCreature->SetDirection( vi.getDir() );
			//pCreature->SetCurrentDirection( vi.getDir() );
			pCreature->SetAction( ACTION_STAND );

			// ����
			pCreature->SetBodyColor1( vi.getSkinColor() );
			pCreature->SetBodyColor2( vi.getCoatColor() );


			// speed
			pCreature->SetWeaponSpeed( vi.getAttackSpeed() );

			//--------------------------------------------------
			// [ TEST CODE ]
			//--------------------------------------------------
			// �� ���� �����ϱ�
			//--------------------------------------------------
			/*
			if (pCreature->IsMale())
			{
				pCreature->SetBodyColor2( 91 );
			}
			else
			{
				pCreature->SetBodyColor2( 38 );
			}
			*/

			pCreature->SetStatus( MODIFY_MAX_HP, vi.getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, vi.getCurrentHP() );
			pCreature->SetStatus( MODIFY_ALIGNMENT, vi.getAlignment() );
		}

		if (pCreature!=NULL)
		{
			// Vampire Coat & Weapon - chyaya
			MCreatureWear* pCreatureWear = dynamic_cast<MCreatureWear*>(pCreature);
			if(pCreatureWear)
				SetAddonToVampire(pCreatureWear, &vi);

			//--------------------------------------------------
			// Effect ���̱�..
			//--------------------------------------------------
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );

			//--------------------------------------------------
			// Burrow���� ���������� Effect == Burrowing�ϴ� Effect
			//--------------------------------------------------		
			ExecuteActionInfoFromMainNode(
				RESULT_MAGIC_HIDE,										// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),														// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				NULL,
				
				false);			// ��� ÷���� �����Ѵ�.
		}
	}

	// [����] Vampire�� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_VAMPIRE );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
