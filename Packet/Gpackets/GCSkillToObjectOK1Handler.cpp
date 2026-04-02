//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToObjectOK1.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "PacketFunction2.h"

// [�����2]
#include "SkillDef.h"	
#include "MFakeCreature.h"
void	SkillShadowDancing(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID);
extern void Add_RocketRuncher(MCreature* UserCreature, MCreature* TargetCreature);
extern void Add_XRL_RocketRuncher(MCreature* UserCreature, MCreature* TargetCreature);
extern void Add_Wild_Wolf(MCreature* UserCreature, MCreature* TargetCreature, bool IsEatCorpse);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK1Handler::execute ( GCSkillToObjectOK1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
		
	//------------------------------------------------------
	// ����� �޽��� ����
	//------------------------------------------------------
// 	if(g_pUserInformation->attrOperator.GetValue() &&
// 	   g_pOperatorOption->bShowAddEffect)
// 	{	
// 		MCreature*	pTargetCreature = g_pZone->GetCreature(pPacket->getObjectID());
// 		DWORD		delayFrame		= ConvertDurationToFrame( pPacket->getDuration() );
// 
// 		const char* pName;
// 		if(pTargetCreature)	pName = pTargetCreature->GetName();
// 		else				pName = "?";
// 
// 		char szBuf[128];
// 		sprintf(szBuf, "targetName=%s, cid=%d, eid=%d, duration=%d, delayFrame=%d",
// 				pName, pPacket->getObjectID(), pPacket->getEffectID(),
// 				pPacket->getDuration(), delayFrame);
// 
// 		UI_AddChatToHistory(szBuf, "Recv GCAddEffect", 6, RGB(255, 255, 0));
// 	}
		
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

	//------------------------------------------------------------------
	// Player�� Skill�� ������Ų ��쿡 ���ƿ��� Packet�̹Ƿ�
	// ����� �ݿ����Ѿ� �Ѵ�.
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
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getTargetObjectID() );

		// [ TEST CODE ]
		// �������� Effect�̸� Result�� �߰��ؾ� �Ѵ�. 
		// Result�� �����ϰ�..
		// g_pPlayer->>AddActionResult( ... )

		// 2005, 1, 3, sobeit add start
		if(pPacket->getSkillType() == SKILL_WILD_WOLF)
		{
			if(pCreature != NULL)
				Add_Wild_Wolf(g_pPlayer, pCreature, pPacket->getGrade()?true:false);
			else
			{
				MItem* pItem = g_pZone->GetItem(pPacket->getTargetObjectID());
				if(pItem != NULL && pItem->GetItemClass() == ITEM_CLASS_CORPSE)
				{
					pCreature = ((MCorpse*)pItem)->GetCreature();
					if(pCreature != NULL)
					{
						Add_Wild_Wolf(g_pPlayer, pCreature, pPacket->getGrade()?true:false);
					}
				}
			}
		}

		// 2005, 1, 3, sobeit add end
		// Creature���� Damage ����
		if (pCreature != NULL)
		{	
			// �ڱ� �ڽ��� ���� SkillStep�� ���� �������� �ʿ� ����.
			//pCreature->SetSkillStep(pPacket->getSkillStep());

			int skillID = pPacket->getSkillType();
			//char cstrOutput[256] ; 
			//wsprintf(cstrOutput , "GCSkillToObjectOK1Handler() %d\n" ,skillID  ) ; 

			//OutputDebugString(cstrOutput) ; 
			
			if( g_pActionInfoTable->GetSize() <= skillID )
			{
				DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
				
				SendBugReport("[Error:GCSTOOK1H] Exceed SkillType %d", skillID );
				return;
			}

			// 2004, 11, 13, sobeit add start 
			if(skillID == SKILL_PLASMA_ROCKET_LAUNCHER)
			{
				Add_RocketRuncher(g_pPlayer, pCreature);
			}
#if __CONTENTS(__SECOND_RARE_SKILL)
			else if(skillID == SKILL_XRL)
			{
				Add_XRL_RocketRuncher(g_pPlayer, pCreature);
			}
#endif //__SECOND_RARE_SKILL
			// 2004, 11, 13, sobeit add end
//			// 2005, 1, 3, sobeit add start
			else if(skillID == SKILL_HEAL_PASS)
			{
				ExecuteActionInfoFromMainNode(SKILL_HEAL_PASS,g_pPlayer->GetX(), g_pPlayer->GetY(), 0,g_pPlayer->GetDirection(),pCreature->GetID()	,	
					pCreature->GetX(), pCreature->GetY(), 0, 20 , NULL, false);
				
			}
//			// 2005, 1, 3, sobeit add end
			// ���� ������ ������ �޴� ����̸�..
			if ((*g_pActionInfoTable)[skillID].IsAffectCurrentWeaponAction())
			{
				skillID = g_pPlayer->GetBasicActionInfo();	

				if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
				{
					DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
					return;
				}
			}
			
			//int OrigskillID = skillID	;

			if((*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
				skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);
			
			 // 2005.07.08 Sjheon Combo Add
			/*if((*g_pActionInfoTable)[skillID].GetComboAttackSkill())
			{	
				g_pPlayer->SetCombo(pPacket->getCombo()) ; 
				g_pPlayer->SetCurrentCombo(0) ; 
			}
			else
			{
				if((*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
					skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);
			}*/	
			// 2005.07.08 Sjheon Combo End

				
			// ��ų�� ���� ���� ó��.
			switch( skillID )
			{
			case SKILL_SHADOW_DANCING :
				SkillShadowDancing(g_pPlayer, pCreature, SKILL_SINGLE_BLOW);
				break;
				
			case SKILL_ILLENDUE :
				// 2004, 12, 15, sobeit modify start - ������ ��æ ����Ʈ�� ���°� ����.
				//SkillIllendue( g_pPlayer, pCreature, SKILL_LIGHT_BALL);
				SkillIllendue( g_pPlayer, pCreature, MAGIC_CAUSE_SERIOUS_WOUNDS);
				// 2004, 12, 15, sobeit modify end
				break;
#if __CONTENTS(__ONIBLA)
			case SKILL_AGONY_CHILD_SHADOW_FOUR :
				SkillIllendue( pCreature, g_pPlayer, SKILL_ATTACK_MELEE);
				break;
			case SKILL_VILLAIN_LADY_GHOST_SHADOW :
				SkillGhostShadow(pCreature, g_pPlayer, MAGIC_RAPID_GLIDING, 4, 2);
				break;
#endif //__ONIBLA
			case SKILL_BLAZE_WALK :
				SkillBlazeWalk( dynamic_cast<MCreature*>(g_pPlayer), pCreature, SKILL_BLAZE_WALK_ATTACK , pPacket->getGrade() );
				break;

			case SKILL_BITE_OF_DEATH :
				pCreature->SetDrainCreatureID( g_pPlayer->GetID() );
				break;
			case SKILL_SET_AFIRE:
				g_pPlayer->AddEffectStatus(EFFECTSTATUS_SET_AFIRE_ATTACK, 20);
				break;
				
			case SKILL_ILLUSION_INVERSION:
				SkillIllendue( g_pPlayer, pCreature, SKILL_DUMMY_ACTION_MAGIC, 2);
				break;
			}
			
			MActionResult* pResult = new MActionResult;

			// ���� creature�� ���� player�� ������ �ٶ󺸱�
			//pCreature->SetDirectionToPosition(g_pPlayer->GetX(), g_pPlayer->GetY());

			DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

			// ��� ǥ��
			//pCreature->PacketSpecialActionResult( pPacket->getSkillType() + g_ActionInfoTable.GetMinResultActionInfo());
			pResult->Add( new MActionResultNodeActionInfo( 
											skillID,
											g_pPlayer->GetID(), 
											pCreature->GetID(), 
											pCreature->GetX(),
											pCreature->GetY(),
											delayFrame ) 
							);	

			//------------------------------------------------------
			//
			// skill�� ����� ������ ���� ��Ų��.
			//
			//------------------------------------------------------
			MActionResultNode* pActionResultNode = CreateActionResultNode(pCreature, skillID, pPacket->getGrade() );

			//------------------------------------------------------
			// NULL�� �ƴϸ� ����
			//------------------------------------------------------
			if (pActionResultNode!=NULL)
			{
				pResult->Add( pActionResultNode );
			}


			//------------------------------------------------------
			// EffectStatus�� �ִٸ� ���δ�.
			//------------------------------------------------------
			EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
			
			if (es!=EFFECTSTATUS_NULL)
			{
				pResult->Add( new MActionResultNodeAddEffectStatus( pCreature->GetID(), 
																			es, 
																			delayFrame ) );
			}
			
			// [ TEST CODE ] 
			// �´� ��� damage�� ǥ���� �ش�.			
			/*
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( g_pPlayer->GetID(), g_pPlayer->GetID(), SKILL_ATTACK_MELEE ) );			

			g_pPlayer->PacketAddActionResult(pPacket->getCEffectID(), pResult);
			*/

			// Player�� ���� ���� ���� ����� ����� �߰���Ų��.
			g_pPlayer->PacketAddActionResult( pPacket->getCEffectID(), pResult );		
		}
		
	}
	

#endif

	__END_CATCH
}
