//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackArmsOK2.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK2Handler::execute ( GCAttackArmsOK2 * pPacket , Player * pPlayer )
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
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), SKILL_ATTACK_MELEE);				
		
		if( pPacket->getSkillType() == SKILL_JABBING_VEIN || pPacket->getSkillType() == SKILL_MOLE_SHOT ||
					pPacket->getSkillType() == SKILL_TRIDENT || pPacket->getSkillType() == SKILL_QUICK_FIRE ||
					pPacket->getSkillType() == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
		{
			TYPE_ACTIONINFO resultActionInfo = pPacket->getSkillType() + g_pActionInfoTable->GetMinResultActionInfo();
			// �ٷ� �´� ����� ���̰� �Ѵ�.
			g_pPlayer->PacketSpecialActionResult( 
									resultActionInfo,	// �⺻ ���� == ��!? 
									g_pPlayer->GetID(), 
									g_pPlayer->GetX(),
									g_pPlayer->GetY()								
					);
		} else
		{
			// �ٷ� �´� ����� ���̰� �Ѵ�.
			g_pPlayer->PacketSpecialActionResult( 
									RESULT_SKILL_ATTACK_GUN_AR,	// �⺻ ���� == ��!? 
									g_pPlayer->GetID(), 
									g_pPlayer->GetX(),
									g_pPlayer->GetY()								
					);
		}
	}
	else
	{
		TYPE_ACTIONINFO actionInfo = pPacket->getSkillType();
		//------------------------------------------------------
		// �ൿ�ϴ� Creature�� player�� �ٶ󺸵��� �Ѵ�.
		//------------------------------------------------------
		pCreature->SetDirectionToPosition( g_pPlayer->GetX(), g_pPlayer->GetY() );

		//------------------------------------------------------
		// Creature�� Player�� �����ϴ� ���
		//------------------------------------------------------
		//g_pPlayer->PacketSpecialActionResult( SKILL_ATTACK_MELEE + g_ActionInfoTable.GetMinResultActionInfo() );

		if( actionInfo == SKILL_JABBING_VEIN || actionInfo == SKILL_TRIDENT || actionInfo == SKILL_MOLE_SHOT ||
			actionInfo == SKILL_QUICK_FIRE || actionInfo == SKILL_ULTIMATE_BLOW || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
		{
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( 
										actionInfo,	// �⺻ ���� == ��!? 
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
							actionInfo,	// �⺻ ���� == ��!? 
							g_pPlayer->GetID(), 
							pResult
			);
		} else
		{
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( 
										pCreature->GetBasicActionInfo(),	// �⺻ ���� == ��!? 
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
							pCreature->GetBasicActionInfo(),	// �⺻ ���� == ��!? 
							g_pPlayer->GetID(), 
							pResult
			);
		}
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
