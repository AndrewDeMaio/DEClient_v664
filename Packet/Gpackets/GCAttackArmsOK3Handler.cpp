//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackArmsOK3.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "MSlayerGear.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK3Handler::execute ( GCAttackArmsOK3 * pPacket , Player * pPlayer )
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
	
	if (pCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), pPacket->getSkillType());				
		
		return;
	}

	//------------------------------------------------------
	// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
	//------------------------------------------------------
	pCreature->SetDirectionToPosition( pPacket->getTargetX(), pPacket->getTargetY() );

	//------------------------------------------------------
	// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
	// ��밡 zone�� ���� ����̴�.
	//------------------------------------------------------
	if( pPacket->getSkillType() == SKILL_JABBING_VEIN || pPacket->getSkillType() == SKILL_MOLE_SHOT ||
					pPacket->getSkillType() == SKILL_TRIDENT || pPacket->getSkillType() == SKILL_GAE_BULGA || pPacket->getSkillType() == SKILL_QUICK_FIRE ||
					pPacket->getSkillType() == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
	{
		pCreature->PacketSpecialActionToNobody(
						pPacket->getSkillType()	,	// �� ����
						pPacket->getTargetX(),
						pPacket->getTargetY()						
		);
	} else
	{
		pCreature->PacketSpecialActionToNobody(
						pCreature->GetBasicActionInfo()	,	// �� ����
						pPacket->getTargetX(),
						pPacket->getTargetY()						
		);
	}



#endif

	__END_CATCH
}
