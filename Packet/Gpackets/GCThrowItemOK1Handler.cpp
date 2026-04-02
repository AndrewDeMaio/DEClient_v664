//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowItemOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCThrowItemOK1.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowItemOK1Handler::execute ( GCThrowItemOK1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	TYPE_ACTIONINFO skillType = MAGIC_THROW_HOLY_WATER;//g_pPlayer->GetWaitVerifyActionInfo();

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
	/*
	int size = pPacket->getListNum();

	for (int i=0; i<size; i++)
	{
		int part = pPacket->popFrontListElement();
		int value = pPacket->popFrontListElement();
		
		//------------------------------------------------------------------
		// Player���� ���¸� �����Ų��.
		//------------------------------------------------------------------
		g_pPlayer->SetStatus( part, value );		
	}
	*/

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

		// [ TEST CODE ]
		// �������� Effect�̸� Result�� �߰��ؾ� �Ѵ�.
		// Result�� �����ϰ�..
		// g_pPlayer->>AddActionResult( ... )

		// Creature���� Damage ����
		if (pCreature != NULL)
		{			
			MActionResult* pResult = new MActionResult;

			// ���� creature�� ���� player�� ������ �ٶ󺸱�
			//pCreature->SetDirectionToPosition(g_pPlayer->GetX(), g_pPlayer->GetY());

			//int delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

			// ��� ǥ��
			//pCreature->PacketSpecialActionResult( pPacket->getSkillType() + g_ActionInfoTable.GetMinResultActionInfo());
			pResult->Add( new MActionResultNodeActionInfo( 
											skillType,
											g_pPlayer->GetID(), 
											pCreature->GetID(), 
											pCreature->GetX(),
											pCreature->GetY())
											//delayFrame ) 
							);	

			
			// [ TEST CODE ] 
			// �´� ��� damage�� ǥ���� �ش�.			
			/*
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( g_pPlayer->GetID(), g_pPlayer->GetID(), SKILL_ATTACK_MELEE ) );			

			g_pPlayer->PacketAddActionResult(pPacket->getCEffectID(), pResult);
			*/

			// Player�� ���� ���� ���� ����� ����� �߰���Ų��.
			//g_pPlayer->PacketAddActionResult( pPacket->getCEffectID(), pResult );		
			g_pPlayer->PacketAddActionResult( 0, pResult );		
		}
		
	}
		

#endif

	__END_CATCH
}
