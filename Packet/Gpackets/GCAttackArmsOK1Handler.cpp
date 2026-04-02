//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAttackArmsOK1.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "MSlayerGear.h"
#include "Skilldef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK1Handler::execute ( GCAttackArmsOK1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	
	// message

	//------------------------------------------------------------------
	// Player�� Skill�� ������Ų ��쿡 ���ƿ��� Packet�̹Ƿ�
	// ����� �ݿ����Ѿ� �Ѵ�.
	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

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
		/*
		if (pCreature != NULL)
		{
			// �ٷ� �´� ����
			// SKILL_ATTACK_GUN1~4?�� ���� ����� ǥ�����ش�.
			pCreature->PacketSpecialActionResult( 
				g_pPlayer->GetBasicActionInfo() + g_ActionInfoTable.GetMinResultActionInfo(),
				g_pPlayer->GetID(),
				g_pPlayer->GetX(),
				g_pPlayer->GetY()
			);
			
		}
		*/

		//------------------------------------------------------
		// ���� ��츸 ���� ������ ���δ�.
		//------------------------------------------------------
		if (pPacket->getSkillSuccess())
		{
			// action�� ������ �´� ����
			if (pCreature!=NULL)
			{
				MActionResult* pResult = new MActionResult;

				if( pPacket->getSkillType() == SKILL_JABBING_VEIN || pPacket->getSkillType() == SKILL_MOLE_SHOT ||
					pPacket->getSkillType() == SKILL_TRIDENT || pPacket->getSkillType() == SKILL_QUICK_FIRE || 
					pPacket->getSkillType() == SKILL_ULTIMATE_BLOW  || pPacket->getSkillType() == SKILL_HARPOON_BOMB)
				{
					pResult->Add( new MActionResultNodeActionInfo( 
												pPacket->getSkillType(),
												g_pPlayer->GetID(), 
												pCreature->GetID(), 
												pCreature->GetX(),
												pCreature->GetY()
												 ) 
								);
				} else
				{			
					pResult->Add( new MActionResultNodeActionInfo( 
												g_pPlayer->GetBasicActionInfo(),
												g_pPlayer->GetID(), 
												pCreature->GetID(), 
												pCreature->GetX(),
												pCreature->GetY()
												 ) 
								);
				}

				//g_pPlayer->PacketAddActionResult( effectID, pResult );
				g_pPlayer->PacketAddActionResult( 0, pResult );
			}
		}
					
		//------------------------------------------------------
		// �Ѿ� ���ش�.
		//------------------------------------------------------
		if (g_pCurrentMagazine==NULL)
		{
			DEBUG_ADD("[Error] Current Magazine Not Exist!");			
		}
		else
		{
			g_pCurrentMagazine->SetNumber( pPacket->getBullet() );
		}

	}	
		

#endif

	__END_CATCH
}
