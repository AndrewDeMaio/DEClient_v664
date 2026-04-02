//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillFailed2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillFailed2.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2Handler::execute ( GCSkillFailed2 * pPacket , Player * pPlayer )
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
	
	//------------------------------------------------------
	// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
	//------------------------------------------------------
	int skilltype = pPacket->getSkillType();
	
//	if(skilltype == SKILL_BLOOD_DRAIN)
//	{
//		DEBUG_ADD("���� ���Ф���");
//	}
	if( skilltype >= g_pActionInfoTable->GetSize() )
		return;
	
	if(pTargetCreature == NULL && pCreature != NULL && pCreature->IsOusters() && skilltype == SKILL_ABSORB_SOUL)
	{
		MItem *pItem = g_pZone->GetItem( pPacket->getTargetObjectID() );
		if(pItem != NULL)
		{
			pTargetCreature = ((MCorpse *)pItem)->GetCreature();
		}
	}

	if (pCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), SKILL_ATTACK_MELEE);				
		
		return;
	}

	//------------------------------------------------------
	// ������ ���⿡ ���� ���� ����� �����ϴ� ���..
	//------------------------------------------------------
	if (skilltype==SKILL_ATTACK_MELEE
		|| skilltype==SKILL_ATTACK_ARMS)
	{
		skilltype = pCreature->GetBasicActionInfo();
	}

	//
	if (skilltype >= g_pActionInfoTable->GetMinResultActionInfo())
	{
		DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skilltype);
		return;
	}
	
	int OrigskillType = skilltype	;

	if( pPacket->getGrade() > 0 && (*g_pActionInfoTable)[skilltype].IsUseActionStep() )
		skilltype = (*g_pActionInfoTable)[skilltype].GetActionStep( pPacket->getGrade() - 1 );


	DEBUG_ADD_FORMAT("SkillType = %d", skilltype);

	int resultSkillID = g_pActionInfoTable->GetMinResultActionInfo() + skilltype;

	if (pCreature->IsOusters() && skilltype==SKILL_ABSORB_SOUL)
	{
		pCreature->SetStopAbsorbSoul();
	}
	
	// 2005, 1, 10, sobeit add start - 784 ���� ����ź ������ ��ų ���н� � ���۵� ���� �ʰ�..
	if(skilltype == SKILL_GRENADE_ATTACK) 
		return;
	// 2005, 1, 10, sobeit add end

#if __CONTENTS(__TIPOJYU_CASTLE)						//��ų�� ���� �ϸ� ����� ������ �ʴ´�.
	if(skilltype >= 465 && skilltype <= 492)	//Ƽ���� ���� ��ų
		return;
#endif // __TIPOJYU_CASTLE

	//------------------------------------------------------
	// Other
	//------------------------------------------------------
	if ((*g_pActionInfoTable)[skilltype].IsTargetOther())
	{		
		if (skilltype==SKILL_BLOOD_DRAIN || skilltype == SKILL_BITE_OF_DEATH )
		{
			pCreature->SetStopBloodDrain();
			//DEBUG_ADD("���� �׽�Ʈ����");
		}
		
		// �´� �ְ� ���� ���..  
		if (pTargetCreature==NULL)
		{
			// �׷� creature�� ���� ���
			DEBUG_ADD_FORMAT("There's no such creature : TargetID=%d, Skill=%d", pPacket->getTargetObjectID(), SKILL_ATTACK_MELEE);

			//------------------------------------------------------
			// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
			//------------------------------------------------------

			pCreature->PacketSpecialActionToNobody(
							skilltype,
							pCreature->GetX(),
							pCreature->GetY()						
			);			
			
			return;
		}
		
		// �ڽſ��� ���� ���? - -;
		if (pCreature==pTargetCreature)
		{
			pCreature->PacketSpecialActionToSelf(
						skilltype, 				
						NULL
			);

			return;
		}
		
		//------------------------------------------------------
		// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
		//------------------------------------------------------
		pCreature->SetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );

		pCreature->PacketSpecialActionToOther(
						skilltype, 
						pPacket->getTargetObjectID(), 
						NULL
		);		
		
	}
	//------------------------------------------------------
	// Self
	//------------------------------------------------------
	else if ((*g_pActionInfoTable)[skilltype].IsTargetSelf())
	{
		pCreature->PacketSpecialActionToSelf(
						skilltype, 				
						NULL
		);
	}
	//------------------------------------------------------
	// Zone
	//------------------------------------------------------
	else if ((*g_pActionInfoTable)[skilltype].IsTargetZone())
	{
		pCreature->PacketSpecialActionToSector(
						skilltype, 
						pCreature->GetX(),
						pCreature->GetY(),
						NULL
		);
	}

#endif

	__END_CATCH
}
