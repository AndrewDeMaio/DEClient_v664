//--------------------------------------------------------------------------------
//
// Filename    : GCMorph1Handler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCMorph1.h"
#include "ClientDef.h"
#include "CDirectSound.h"
#include "MQuickSlot.h"
#include "SkillDef.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCMorph1Handler::execute ( GCMorph1 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		DEBUG_ADD("[Error] g_pZone or g_pPlayer NULL");

		return;
	}

	//-----------------------------------------------------------
	// Sound�� ������� �ʴ´�.
	//-----------------------------------------------------------
	g_DXSound.SetMute();

	//-----------------------------------------------------------
	// ID�� �ٸ���.. ID�� �ٲ�� �Ѵ�.
	//-----------------------------------------------------------
	int objectID;
	
	switch (pPacket->getPCInfo2()->getPCType())
	{
		//--------------------------------------------------
		// Slayer�� ���
		//--------------------------------------------------
		case PC_SLAYER :		
			objectID = ((PCSlayerInfo2*)pPacket->getPCInfo2())->getObjectID();
		break;

		//--------------------------------------------------
		// Vampire�� ���
		//--------------------------------------------------
		case PC_VAMPIRE :
			objectID = ((PCVampireInfo2*)pPacket->getPCInfo2())->getObjectID();			
		break;

		default :
			DEBUG_ADD("[Error] wrong PC Type");
		return;
	}

	if (g_pPlayer->GetID()!=objectID)
	{
		// Zone�� ����ִ°ŵ� �ٲ۴�.
		g_pZone->RemoveCreature( g_pPlayer->GetID() );

		// ���ο� ID
		g_pPlayer->SetID( objectID );

		g_pZone->SetPlayer();
		g_pPlayer->SetZone(g_pZone);
	}

	//--------------------------------------------------
	//
	//			 Player ����
	//
	//--------------------------------------------------
	if (g_pPlayer->IsSlayer())
	{
		g_pPlayer->ChangeToVampire();

		// �ӽ÷�
		g_pPlayer->SetGuildNumber( 2 );
	}
	else
	{
		g_pPlayer->ChangeToSlayer();

		// �ӽ÷�
		g_pPlayer->SetGuildNumber( -1 );
	}


	//--------------------------------------------------
	// Ư�� ��� ����
	//--------------------------------------------------
	//g_pPlayer->SetSpecialActionInfo( MAGIC_LIGHT );

	//--------------------------------------------------
	// ���� ��� ����
	//--------------------------------------------------
//	g_pPlayer->SetAttackModeNormal();


	//--------------------------------------------------
	// QuickSlot�� ���ش�. �ʿ��Ѱ�? - -;
	//--------------------------------------------------	
	g_pQuickSlot = NULL;
	g_pArmsBand1 = NULL;
	g_pArmsBand2 = NULL;

			
	//--------------------------------------------------
	//		���� �ʱ�ȭ
	//--------------------------------------------------
	// �ʿ� ���� ��..
	//--------------------------------------------------
	DEBUG_ADD( "Remove All Addon" );
	
	//for (int i=0; i<ADDON_MAX; i++)
	//{
	//	g_pPlayer->RemoveAddon((enum ADDON)i);
	//}			

	g_pPlayer->SetBasicActionInfo( SKILL_ATTACK_MELEE );
	g_pPlayer->SetBasicAttackDistance( 1 );
		

	//--------------------------------------------------
	//
	//			 player�� ������ �����Ѵ�.
	//
	//--------------------------------------------------		
	switch (pPacket->getPCInfo2()->getPCType())
	{
		//--------------------------------------------------
		// Slayer�� ���
		//--------------------------------------------------
		case PC_SLAYER :
		{
			SetPCSlayerInfo( (PCSlayerInfo2*)pPacket->getPCInfo2() );
		}
		break;

		//--------------------------------------------------
		// Vampire�� ���
		//--------------------------------------------------
		case PC_VAMPIRE :
		{
			SetPCVampireInfo( (PCVampireInfo2*)pPacket->getPCInfo2() );
		}
		break;

		//--------------------------------------------------
		// Ousters�� ���
		//--------------------------------------------------
		case PC_OUSTERS :
		{
			SetPCOustersInfo( (PCOustersInfo2*)pPacket->getPCInfo2() );
		}
		break;
	}

	//--------------------------------------------------
	//	 Gear�� ������ �����Ѵ�.
	//--------------------------------------------------
	SetGearInfo( pPacket->getGearInfo() );

	// ����� �ٽ����ش�.
	g_pPlayer->CalculateStatus();

	//--------------------------------------------------
	//	Inventory �ʱ�ȭ
	//--------------------------------------------------
	SetInventoryInfo( pPacket->getInventoryInfo() );

	//--------------------------------------------------
	// ��Ÿ Item ���� == Mouse�� �پ� �ִ� item
	//--------------------------------------------------
	SetExtraInfo( pPacket->getExtraInfo() );
	

	//--------------------------------------------------
	// Skill 
	//--------------------------------------------------


	//-----------------------------------------------------------
	// Sound�� ����� �� �ְ� �Ѵ�.
	//-----------------------------------------------------------
	g_DXSound.UnSetMute();


#endif

	__END_CATCH
}
