//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddBatHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddBat.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddBatHandler::execute ( GCAddBat * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	int batCreatureType = 0;
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	int batType = pPacket->getBatType();
	//���� �ڽſ��� ���ƿ� GCAddBat�̰�, �ű��̵������� ���..... �� �÷����� ���Ѵ�.
	if (g_pPlayer->GetID() == pPacket->getObjectID())
	{
		if(batType == 2)
		{
#if __CONTENTS(__SECOND_TRANSFORTER)
			if(pPacket->getItemType()==0)
			{
#endif //__SECOND_TRANSFORTER
				if (pPacket->getWingColor1() != 0)
					g_pPlayer->SetWingColor( pPacket->getWingColor1() );
				else
					g_pPlayer->SetWingColor( 403 );
				g_pPlayer->SetWingEffectColor( pPacket->getWingColor2() );

#if __CONTENTS(__SECOND_TRANSFORTER)
			}
			else if(pPacket->getItemType()==1)
			{
				if (pPacket->getWingColor1() != 0)
					g_pPlayer->SetWingColor( pPacket->getWingColor1() );
				else
					g_pPlayer->SetWingColor( 403 );
				g_pPlayer->SetWingEffectColor( pPacket->getWingColor2() );
			}
#endif //__SECOND_TRANSFORTER
			//�׸�����.. �ٷ� ����.
			// ��? GCSkillToInventoryOk1Handler���� �÷����� ó������ ���ϱ� ������.. �ڽſ��Ե� GCAddBat�� �������� �Ͽ�.. Color���� ���ϱ� ����.
			g_pPlayer->SetWingType(batType);
			return;
		}
	}
	if (batType == 2)										//battype�� 2�� ��찡 �ű��̵����� ..
	{
		if(pPacket->getItemType() == 0)						//�ø��� ���콺(�� ������Ÿ�Թ�ȣ)
			batCreatureType = CREATURETYPE_FLITTERMOUSE;
#if __CONTENTS(__SECOND_TRANSFORTER)
		else if(pPacket->getItemType() == 1)				//���� (�� ������Ÿ�Թ�ȣ)
			batCreatureType = CREATURETYPE_SHAPE_OF_DEMON;
#endif //__SECOND_TRANSFORTER
		else												//itemtype��  �߰����� ���� �ű� �̵�����? �׷� �� ����.
			batCreatureType = CREATURETYPE_BAT;
	}
	else
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
		batCreatureType = CREATURETYPE_BAT;

	_MinTrace("%d\n", pPacket->getBatColor() );

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
		//AfxMessageBox( pPacket->toString().c_str() );
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;

			pCreature->SetZone( g_pZone );
			
			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( batCreatureType );


			pCreature->SetName( pPacket->getName().c_str() );

			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			pCreature->SetFlyingCreature();

			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			
			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			//pPacket->getName()
			// ���� ����
			
			if( pPacket->getBatColor() != 0 )
				pCreature->SetBatColor( pPacket->getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );

			pCreature->SetAdvanceBatColor( pPacket->getAdvanceBatColor() );

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
			}
			pCreature->SetWingType(pPacket->getBatType());
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			//pCreature->SetCreatureType( batCreatureType );
			
			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			//pCreature->SetAction( ACTION_STAND );			

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			if( pPacket->getBatColor() != 0 )
				pCreature->SetBatColor( pPacket->getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );

			pCreature->SetAdvanceBatColor( pPacket->getAdvanceBatColor() );
			
#if __CONTENTS(__FAST_TRANSFORTER)||__CONTENTS(__SECOND_TRANSFORTER)
			if(batType == 2
#if __CONTENTS(__SECOND_TRANSFORTER)
				&& pCreature->GetWingItemType()==0
#endif //__SECOND_TRANSFORTER
				)
			{
				//�ű� �̵����� Wingcolor�� ��������.
				if (pPacket->getWingColor1() != 0)
					pCreature->SetWingColor(pPacket->getWingColor1());
				else
					pCreature->SetWingColor(403);
				pCreature->SetWingEffectColor( pPacket->getWingColor2());

				pCreature->SetWingEffect1();
			}
			// ���� �����̾��� ��� ���㰡 �ƴ϶� ����Ʈ��.
			else 
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
			if(batType == 2 && pCreature->GetWingItemType()==1)
			{
				if (pPacket->getWingColor1() != 0)
					pCreature->SetWingColor(pPacket->getWingColor1());
				else
					pCreature->SetWingColor(403);
				pCreature->SetWingEffectColor( pPacket->getWingColor2());

				pCreature->SetWingEffect2();
			}
			// ���� �����̾��� ��� ���㰡 �ƴ϶� ����Ʈ��.
			else 
#endif //__SECOND_TRANSFORTER
			if( pCreature->IsVampire() && pCreature->IsAdvancementClass() )
			{
				batCreatureType = CREATURETYPE_VAMPIRE_GHOST;
				pCreature->SetAdvanceBatEffect();
			}
			else
			{
				pCreature->SetFlyingCreature();
			}
			pCreature->SetWingType(pPacket->getBatType());

			//--------------------------------------------------
			// ����� �����ϴ� ���
			//--------------------------------------------------
			MActionResult* pResult = new MActionResult;

			pResult->Add( new MActionResultNodeChangeCreatureType( pCreature->GetID(), batCreatureType ) );

			int skillType = 0;
#if __CONTENTS(__FAST_TRANSFORTER)
			if (batType == 2 && pPacket->getItemType() == 0)
				skillType = SKILL_CLIENT_FLITTERMOUSE;
			else
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
			if (batType == 2 && pPacket->getItemType() == 1)
				skillType = SKILL_CLIENT_SHAPE_OF_DEMON;
			else
#endif //__SECOND_TRANSFORTER
				skillType = RESULT_MAGIC_TRANSFORM_TO_BAT;

			//--------------------------------------------------
			// ���� ���� 
			//--------------------------------------------------								
			ExecuteActionInfoFromMainNode(
				skillType,													// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),									// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				pResult, //NULL,
				
				false);			// ��� ÷���� �����Ѵ�.

			//pCreature->SetDelay( 1000 );
		}	
	}

	// [����] Vampire�� ��Ÿ����
//	__BEGIN_HELP_EVENT
//		//ExecuteHelpEvent( HE_CREATURE_APPEAR_VAMPIRE );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
