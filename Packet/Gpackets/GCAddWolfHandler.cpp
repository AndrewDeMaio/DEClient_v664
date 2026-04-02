//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddWolfHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddWolf.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddWolfHandler::execute ( GCAddWolf * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	
	int wolfCreatureType = 186;

	if( pPacket->getItemType() == 39 )			// Were Wolf�� ����
		wolfCreatureType = CREATURETYPE_WER_WOLF;
	
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
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;
//			pCreature->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, vi.getAdvancementLevel() );

			pCreature->SetZone( g_pZone );
			
			
			pCreature->SetName( pPacket->getName().c_str() );


			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( wolfCreatureType );
			pCreature->SetGroundCreature();
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
			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
				pCreature = NULL;
			}
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			pCreature->SetCreatureType( wolfCreatureType );

			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			pCreature->SetGroundCreature();
			
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );			

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			//--------------------------------------------------
			// ����� �����ϴ� ���
			//--------------------------------------------------
			MActionResult* pResult = new MActionResult;

			pResult->Add( new MActionResultNodeChangeCreatureType( pCreature->GetID(), wolfCreatureType ) );

			//--------------------------------------------------
			// ���� ���� 
			//--------------------------------------------------								
			ExecuteActionInfoFromMainNode(
				RESULT_MAGIC_TRANSFORM_TO_WOLF,										// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),														// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				pResult, //NULL,
				
				false);			// ��� ÷���� �����Ѵ�.

			//pCreature->SetDelay( 1000 );
		}	

		if( wolfCreatureType == CREATURETYPE_WER_WOLF )
			pCreature->SetBodyColor1( pPacket->getColor() );
	}

	// [����] Vampire�� ��Ÿ����
//	__BEGIN_HELP_EVENT
//		//ExecuteHelpEvent( HE_CREATURE_APPEAR_VAMPIRE );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
