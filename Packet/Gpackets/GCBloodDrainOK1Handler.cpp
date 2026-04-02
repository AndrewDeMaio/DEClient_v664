//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCBloodDrainOK1.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK1Handler::execute ( GCBloodDrainOK1 * pPacket , Player * pPlayer )
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
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		// Creature���� Damage ����
		if (pCreature != NULL)
		{	
			// Creature���� ���� �����ϰ� �ִٰ� �˷��ش�
			pCreature->SetDrainCreatureID( g_pPlayer->GetID() );

			// ��� �ٷ� ǥ��
			pCreature->PacketSpecialActionResult( 
					SKILL_BLOOD_DRAIN + (*g_pActionInfoTable).GetMinResultActionInfo(),
					pCreature->GetID(),
					pCreature->GetX(),
					pCreature->GetY()
			);	

			int delayFrame = 691200;	// 12�ð�*60��*60��*16frame = 12*60*60*16;
			pCreature->AddEffectStatus( EFFECTSTATUS_BLOOD_DRAIN, delayFrame );	
			
//			// 2004, 6, 9 sobeit add start - �׽�Ʈ, ���� ���� �޼��� �´㿡 �����ϰ�..-_-
//			if(g_pPlayer->IsVampire())
//			{
//				g_pPlayer->SetDirectionToPosition(pCreature->GetX(), pCreature->GetY());
//				g_pPlayer->SetAction(ACTION_VAMPIRE_DRAIN);
//				
//			}
//			// 2004, 6, 9 sobeit add end
		}
	}
	
	g_pPlayer->ClearStopBloodDrain();

#endif

	__END_CATCH
}
