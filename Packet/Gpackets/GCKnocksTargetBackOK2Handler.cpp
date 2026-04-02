//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCKnocksTargetBackOK2.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK2Handler::execute ( GCKnocksTargetBackOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	//------------------------------------------------------------------
	// Player�� ��ٸ��� skill�� ���������� �����޾Ҵ�.
	//------------------------------------------------------------------
	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_SKILL_SUCCESS)
	{		
		g_pPlayer->SetWaitVerifyNULL();
	}
	else
	{
		DEBUG_ADD("[Error] Player is not WaitVerifySkillSuccess");
	}

	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
		
		return;
	}	


	int skillType = pPacket->getSkillType();	//pCreature->GetBasicActionInfo(),	// �⺻ ���� == ��!? 	
	
	if( skillType >= g_pActionInfoTable->GetSize() )
	{
		DEBUG_ADD_FORMAT("[GCKnocksTargetBackOK2] SkillType Error %d",skillType );
		return;
	}
	
	//------------------------------------------------------
	// �������¹���(direction)����..
	//------------------------------------------------------
	unsigned short x = pPacket->getX();
	unsigned short y = pPacket->getY();
		

	//------------------------------------------------------
	// ����� �Ǵ� creature�� ��´�.
	//------------------------------------------------------
	MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );
	
	if (pCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), pPacket->getSkillType());
		
		// �ٷ� ����
		g_pPlayer->SetServerPosition( x, y );		
		g_pPlayer->MovePosition( x, y );
		g_pPlayer->SetStop();

		// ��� �ٷ� ǥ��
		g_pPlayer->PacketSpecialActionResult( 
							pPacket->getSkillType() + (*g_pActionInfoTable).GetMinResultActionInfo(),
							OBJECTID_NULL,
							x,
							y
		);
	}
	else
	{	
		// �̵��� ���� ��ǥ�� �´�.
		//MCreature::GetPositionToDirection(x, y, pPacket->getDir());


		//------------------------------------------------------
		// �ൿ�ϴ� Creature�� player�� �ٶ󺸵��� �Ѵ�.
		//------------------------------------------------------
		pCreature->SetDirectionToPosition( g_pPlayer->GetX(), g_pPlayer->GetY() );

		//------------------------------------------------------
		// ��� ����
		//------------------------------------------------------
		// Creature�� Player�� �����ϴ� ���
		//g_pPlayer->PacketSpecialActionResult( SKILL_ATTACK_MELEE + (*g_pActionInfoTable).GetMinResultActionInfo() );

		/*
		MActionResult* pResult = new MActionResult;
		pResult->Add( new MActionResultNodeActionInfo( 
									skillType,		// �⺻ ���� == ��!? 
									pPacket->getObjectID(), 
									g_pPlayer->GetID(), 
									g_pPlayer->GetX(),
									g_pPlayer->GetY()
						) 
					);

		// Player�� ��ǥ�� �ٲ�� ���
		pResult->Add( new MActionResultNodeChangePosition( g_pPlayer->GetID(), x, y) );
		*/

		//------------------------------------------------------
		// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
		//------------------------------------------------------
		pCreature->PacketSpecialActionToOther(
						skillType,
						g_pPlayer->GetID(), 
						NULL	//pResult
		);

		//------------------------------------------------------
		// ����ȭ ���� ������..
		// ����� �ٷ� ǥ���Ѵ�.
		//------------------------------------------------------
		// �ٷ� ����
		g_pPlayer->SetServerPosition( x, y );		
		g_pPlayer->MovePosition( x, y );
		g_pPlayer->SetStop();

		// ��� �ٷ� ǥ��
		g_pPlayer->PacketSpecialActionResult( 
							pPacket->getSkillType() + (*g_pActionInfoTable).GetMinResultActionInfo(),
							pCreature->GetID(),
							pCreature->GetX(),
							pCreature->GetY()
		);
	}

	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );

#endif

	__END_CATCH
}
