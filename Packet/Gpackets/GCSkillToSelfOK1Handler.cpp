//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToSelfOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToSelfOK1.h"
#include "ClientDef.h"
#include "PacketFunction2.h"
#include "SkillDef.h"
#include "MSkillManager.h"
#include "UIMessageManager.h"
#include "MEventManager.h"
#include "UIFunction.h"
#include "MGameStringTable.h"
#include "VS_UI.h"


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK1Handler::execute ( GCSkillToSelfOK1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		

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

	int skillID = pPacket->getSkillType();

	if( g_pActionInfoTable->GetSize() <= skillID )
	{
		DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
		SendBugReport("[ErrorGCSTSOK1H] Exceed SkillType %d", skillID );
		return;
	}

	if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
		skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);

	int resultActionInfo = skillID + (*g_pActionInfoTable).GetMinResultActionInfo();
	
	if( skillID == MAGIC_UN_TRANSFORM)
	{
		// �ƿ콺����� summon sylph ���� ������ untransform �� �����ִµ� �׿����� �������� �̰� ����´�-_-
		// ���ľ� �ϴµ�.. �ϴ� ���� ó����!
		if(g_pPlayer->IsOusters())
		{
			g_pPlayer->SetWaitVerifyNULL();
#if __CONTENTS(__FAST_TRANSFORTER)
			if(g_pPlayer->HasEffectStatus( EFFECTSTATUS_CLIENT_WING_SYLPH))
			{
				for (int j = 0; j < 16; j += 2)
					g_pPlayer->RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_STOP + j);
			}
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
			if(g_pPlayer->HasEffectStatus( EFFECTSTATUS_CLIENT_UNICORN))
			{
				for (int j = 0; j < 12; j += 2)
					g_pPlayer->RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_WHITE + j);
			}
#endif //__SECOND_TRANSFORTER
			return;
		}
		else if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_INSTALL_TURRET))
		{
			return;
			//resultActionInfo = RESULT_SKILL_INSTALL_TURRET;
		}
	}
	
	if( skillID == SKILL_ETERNITY && g_pPlayer->IsSlayer() )
	{	
		MEvent event;
		event.eventID = EVENTID_RESURRECT;
		event.eventDelay = 5000;
		event.eventFlag = EVENTFLAG_SHOW_DELAY_STRING;
		event.eventType = EVENTTYPE_ZONE;
		event.m_StringsID.push_back(STRING_MESSAGE_RESURRECT_AFTER_SECONDS);
		
		g_pEventManager->AddEvent(event);
		UI_CloseRequestResurrectWindow();
	}

	//------------------------------------------------------------
	// Delay Frame ����
	//------------------------------------------------------------
	DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );
	if(resultActionInfo == RESULT_SKILL_CONCEALMENT)				// ����Ʈ�� �°� �������� ������ �������ش�.
	{
		int FrameSize = (*g_pActionInfoTable)[resultActionInfo][1].Count;
		int RemainFrame = delayFrame % FrameSize;
		if(RemainFrame < FrameSize / 2 && delayFrame > FrameSize)
		{
			delayFrame -= RemainFrame;
		} else
		{
			delayFrame += FrameSize - RemainFrame;
		}
	}

	g_pPlayer->SetEffectDelayFrame(resultActionInfo, delayFrame );

	// �ҿ� ü���� ��� ��� �������� �ƴ϶� OK������ delay����
	if(skillID == SKILL_SOUL_CHAIN)
	{
		if (skillID < MIN_RESULT_ACTIONINFO)
		{
			g_pSkillInfoTable->SetNextAvailableTime(skillID);
		}
//		g_pUIMessageManager->Execute(UI_CLOSE_TRACE_WINDOW, 0, 0, NULL);
	}

	//------------------------------------------------------
	// Player�� ����� ���������� ���..
	//------------------------------------------------------
	g_pPlayer->PacketSpecialActionResult( 
					resultActionInfo,
					g_pPlayer->GetID(),
					g_pPlayer->GetX(),
					g_pPlayer->GetY()
	);

	//------------------------------------------------------------------
	// Player�� Skill�� ������Ų ��쿡 ���ƿ��� Packet�̹Ƿ�
	// ����� �ݿ����Ѿ� �Ѵ�.
	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	//------------------------------------------------------------------
	// effect status�� �����Ų��.
	//------------------------------------------------------------------
	if (g_pPlayer->GetEFFECT_STAT()!=EFFECTSTATUS_NULL)
	{
		//int esDelayFrame = ConvertDurationToFrame( g_pPlayer->GetDURATION() );

		// effect�� ���δ�.
		g_pPlayer->AddEffectStatus((EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), delayFrame);	
		
		g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
	}
	else
	{
		//------------------------------------------------------
		// EffectStatus�� �ִٸ� ���δ�.
		//------------------------------------------------------
		EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();

		
		if (es!=EFFECTSTATUS_NULL)
		{
			g_pPlayer->AddEffectStatus( es, delayFrame );
		}
	}

	if(skillID == SKILL_WILL_OF_LIFE )
	{
		g_pPlayer->CheckRegen();
		g_pSkillInfoTable->SetAvailableTime(skillID, (3 + (g_pPlayer->GetLEVEL() / 10)) * 2 * 1000 );
	}

	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );


	if(skillID == SKILL_WIDE_BLOOD_DRAIN
		|| skillID == SKILL_BLOOD_DRAIN2
		)
	{
		g_pPlayer->SetSpecialActionInfo(gC_vs_ui.GetSelectedSkillID());
	}
	
	//------------------------------------------------------
	//
	// skill�� ����� ������ ���� ��Ų��.
	//
	//------------------------------------------------------
	MActionResultNode* pActionResultNode = CreateActionResultNode(g_pPlayer, skillID);

	//------------------------------------------------------
	// NULL�� �ƴϸ� ����
	//------------------------------------------------------
	if (pActionResultNode!=NULL)
	{
		pActionResultNode->Execute();

		delete pActionResultNode;
	}


	__END_CATCH
}
