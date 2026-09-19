//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackArmsOK5.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "MSlayerGear.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK5Handler::execute ( GCAttackArmsOK5 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

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
		
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), pPacket->getSkillType() );

		if( pPacket->getSkillType() == SKILL_JABBING_VEIN || pPacket->getSkillType() == SKILL_MOLE_SHOT ||
					pPacket->getSkillType() == SKILL_TRIDENT || pPacket->getSkillType() == SKILL_GAE_BULGA || pPacket->getSkillType() == SKILL_QUICK_FIRE ||
					pPacket->getSkillType() == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
		{
			pTargetCreature->PacketSpecialActionResult( 
					pPacket->getSkillType()+g_pActionInfoTable->GetMinResultActionInfo(),
					pTargetCreature->GetID(),
					pTargetCreature->GetX(),
					pTargetCreature->GetY()
			);
		} else
		{
			pTargetCreature->PacketSpecialActionResult( 
					RESULT_SKILL_ATTACK_GUN_AR,				//pPacket->getSkillType()+g_ActionInfoTable.GetMinResultActionInfo()
					pTargetCreature->GetID(),
					pTargetCreature->GetX(),
					pTargetCreature->GetY()
			);
		}
		
		return;
	}
	//------------------------------------------------------
	// ������ ����� �ִ� ���� ������ ���۸� �����ش�.
	//------------------------------------------------------
	else if (pTargetCreature==NULL)
	{
		
		DEBUG_ADD_FORMAT("There's no such creature : TargetID=%d, Skill=%d", pPacket->getTargetObjectID(), SKILL_ATTACK_MELEE);

		if( pPacket->getSkillType() == SKILL_JABBING_VEIN || pPacket->getSkillType() == SKILL_MOLE_SHOT ||
					pPacket->getSkillType() == SKILL_TRIDENT || pPacket->getSkillType() == SKILL_GAE_BULGA || pPacket->getSkillType() == SKILL_ULTIMATE_BLOW)
		{
			pCreature->PacketSpecialActionToNobody(
							pPacket->getSkillType(), 
							pCreature->GetX(),
							pCreature->GetY()						
			);
		} else
		{
			//------------------------------------------------------
			// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
			//------------------------------------------------------
			pCreature->PacketSpecialActionToNobody(
							pCreature->GetBasicActionInfo(), 
							pCreature->GetX(),
							pCreature->GetY()						
			);
		}
		
		return;
	}


	//------------------------------------------------------
	// ���(�ٸ� ĳ���Ͱ� �´� ���)�� �����Ѵ�.
	//------------------------------------------------------
	MActionResult* pResult = NULL;

	TYPE_ACTIONINFO actionInfo = pPacket->getSkillType();
	
	if (pPacket->getSkillSuccess())
	{
		pResult = new MActionResult;

		if( actionInfo == SKILL_JABBING_VEIN || actionInfo == SKILL_MOLE_SHOT || actionInfo == SKILL_TRIDENT || actionInfo == SKILL_GAE_BULGA ||
			actionInfo == SKILL_QUICK_FIRE  || actionInfo == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
		{
			pResult->Add( new MActionResultNodeActionInfo( 
										actionInfo,
										pPacket->getObjectID(), 
										pPacket->getTargetObjectID(), 
										pTargetCreature->GetX(),
										pTargetCreature->GetY()								
								 ) 
						);
		} else
		{
			pResult->Add( new MActionResultNodeActionInfo( 
										pCreature->GetBasicActionInfo(),	// �� ����
										pPacket->getObjectID(), 
										pPacket->getTargetObjectID(), 
										pTargetCreature->GetX(),
										pTargetCreature->GetY()								
								 ) 
						);
		}
	}

	//------------------------------------------------------
	// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
	//------------------------------------------------------
	pCreature->SetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );

	//------------------------------------------------------
	// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
	//------------------------------------------------------

	if( actionInfo == SKILL_JABBING_VEIN || actionInfo == SKILL_MOLE_SHOT || actionInfo == SKILL_TRIDENT || actionInfo == SKILL_GAE_BULGA ||
		actionInfo == SKILL_QUICK_FIRE || actionInfo == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
	{
		pCreature->PacketSpecialActionToOther(
						// �� ����
						actionInfo,
						pPacket->getTargetObjectID(), 
						pResult
		);
	} else
	{
		pCreature->PacketSpecialActionToOther(
						// �� ����
						pCreature->GetBasicActionInfo()	, 
						pPacket->getTargetObjectID(), 
						pResult
		);
	}


#endif

	__END_CATCH
}
