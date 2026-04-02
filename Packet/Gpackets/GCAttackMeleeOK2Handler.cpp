//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackMeleeOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackMeleeOK2.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackMeleeOK2Handler::execute ( GCAttackMeleeOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	// message

	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
		
		return;
	}	

	//------------------------------------------------------
	// ����� �Ǵ� creature�� ��´�.
	//------------------------------------------------------
	MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

	if (pCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d", pPacket->getObjectID());				
		
		//------------------------------------------------------------------
		// �ٷ� �´� ���
		//------------------------------------------------------------------
		g_pPlayer->PacketSpecialActionResult( 
								RESULT_SKILL_ATTACK_MELEE,//pCreature->GetBasicActionInfo(),
								g_pPlayer->GetID(), 
								g_pPlayer->GetX(),
								g_pPlayer->GetY()
					);
	}
	else
	{
		//------------------------------------------------------
		// �����ϴ� Creature�� �׼� Step�� �����Ѵ�.
		//------------------------------------------------------
		pCreature->SetActionStep(pPacket->getActionStep());
		
		//------------------------------------------------------
		// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
		//------------------------------------------------------
		pCreature->SetDirectionToPosition( g_pPlayer->GetX(), g_pPlayer->GetY() );

		//------------------------------------------------------
		// Creature�� Player�� �����ϴ� ���
		//------------------------------------------------------
		//g_pPlayer->PacketSpecialActionResult( SKILL_ATTACK_MELEE + g_ActionInfoTable.GetMinResultActionInfo() );
		MActionResult* pResult = new MActionResult;
		pResult->Add( new MActionResultNodeActionInfo( 
									pCreature->GetBasicActionInfo(),
									pPacket->getObjectID(), 
									g_pPlayer->GetID(), 
									g_pPlayer->GetX(),
									g_pPlayer->GetY()
						)	 
					);

		//------------------------------------------------------
		// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
		//------------------------------------------------------
		pCreature->PacketSpecialActionToOther(
						pCreature->GetBasicActionInfo(), 
						g_pPlayer->GetID(), 
						pResult
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
