//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackMeleeOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackMeleeOK1.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"
#include "MTopView.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackMeleeOK1Handler::execute ( GCAttackMeleeOK1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
	
	// message

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
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

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
			// SKILL_ATTACK_MELEE�� ���� ����� ǥ�����ش�.
			/*
			// �ٷ� �´� ���
			pCreature->PacketSpecialActionResult( 
								g_pPlayer->GetBasicActionInfo() + g_ActionInfoTable.GetMinResultActionInfo(),
								pCreature->GetID(),
								pCreature->GetX(),
								pCreature->GetY()
								);
				*/
			// action�� ������ �´� ����
			if (pCreature!=NULL)
			{
				MActionResult* pResult = new MActionResult;
			
				pResult->Add( new MActionResultNodeActionInfo( 
											g_pPlayer->GetBasicActionInfo(),
											g_pPlayer->GetID(), 
											pCreature->GetID(), 
											pCreature->GetX(),
											pCreature->GetY()
											 ) 
							);

				//g_pPlayer->PacketAddActionResult( effectID, pResult );
				g_pPlayer->PacketAddActionResult( 0, pResult );
			}
		}
	}	
		

#endif

	__END_CATCH
}
