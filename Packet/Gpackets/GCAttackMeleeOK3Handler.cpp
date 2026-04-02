//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackMeleeOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackMeleeOK3.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackMeleeOK3Handler::execute ( GCAttackMeleeOK3 * pPacket , Player * pPlayer )
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
	MCreature* pTargetCreature = g_pZone->GetCreature( pPacket->getTargetObjectID() );
	
	if (pCreature==NULL && pTargetCreature==NULL)
	{
		return;
	}

	//------------------------------------------------------
	// �´� ����� �ִ� ���� �´� ���۸� �����ָ� �ȴ�.
	//------------------------------------------------------
	if (pCreature==NULL)
	{
		
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), SKILL_ATTACK_MELEE);

		pTargetCreature->PacketSpecialActionResult( 
				RESULT_SKILL_ATTACK_MELEE,				//pPacket->getSkillType()+g_ActionInfoTable.GetMinResultActionInfo()
				pTargetCreature->GetID(),
				pTargetCreature->GetX(),
				pTargetCreature->GetY()
		);
		
		return;
	}
	//------------------------------------------------------
	// ������ ����� �ִ� ���� ������ ���۸� �����ش�.
	//------------------------------------------------------
	else if (pTargetCreature==NULL)
	{
		
		DEBUG_ADD_FORMAT("There's no such creature : TargetID=%d, Skill=%d", pPacket->getTargetObjectID(), SKILL_ATTACK_MELEE);

		//------------------------------------------------------
		// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
		//------------------------------------------------------
		pCreature->PacketSpecialActionToNobody(
						pCreature->GetBasicActionInfo(), 
						pCreature->GetX(),
						pCreature->GetY()						
		);

		// PacketSpecialActionToNobody���ٰ� MActionResult�� �߰��ؼ�
		// �ǰ� Ƣ�°� �����ִ� �͵� ������ ���̴�..
		// �ٵ�, targetCreature�� ���� ������..
		// ��Ȯ�� ��ǥ�� �������� �޾ƿ��°� �����ϱ�... ����~~		
		
		return;
	}

	//------------------------------------------------------
	// �����ϴ� Creature�� �׼� Step�� �����Ѵ�.
	//------------------------------------------------------
	pCreature->SetActionStep(pPacket->getActionStep());

	//------------------------------------------------------
	// ���(�ٸ� ĳ���Ͱ� �´� ���)�� �����Ѵ�.
	//------------------------------------------------------
	MActionResult* pResult = new MActionResult;
	pResult->Add( new MActionResultNodeActionInfo( 
								pCreature->GetBasicActionInfo(),
								pPacket->getObjectID(), 
								pPacket->getTargetObjectID(), 
								pTargetCreature->GetX(),
								pTargetCreature->GetY()
								 ) 
				);

	//------------------------------------------------------
	// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
	//------------------------------------------------------
	pCreature->SetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );

	//------------------------------------------------------
	// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
	//------------------------------------------------------
	pCreature->PacketSpecialActionToOther(
					pCreature->GetBasicActionInfo(), 
					pPacket->getTargetObjectID(), 
					pResult
	);

#endif

	__END_CATCH
}
