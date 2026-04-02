//--------------------------------------------------------------------------------
//
// Filename    : GCUnburrowOKHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCUnburrowOK.h"
#include "ClientDef.h"
#include "SkillDef.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCUnburrowOKHandler::execute ( GCUnburrowOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	/*
	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	// ���� ��ǥ�� �÷��̾ ������ ���´�.
	pClientPlayer->setX( pPacket->getX() );
	pClientPlayer->setY( pPacket->getY() );
	pClientPlayer->setDir( pPacket->getDir() );

	cout << "Unburrow OK to (" << (int)pPacket->getX() << "," << (int)pPacket->getY() << ","
		<< Dir2String[pPacket->getDir()] << ")" << endl;
	*/


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

	//-----------------------------------------------------------------
	// ��ġ ����
	//-----------------------------------------------------------------
	g_pPlayer->SetServerPosition( pPacket->getX(), pPacket->getY() );	
	g_pPlayer->MovePosition( pPacket->getX(), pPacket->getY() );
	g_pPlayer->SetDirection( pPacket->getDir() );

	//-----------------------------------------------------------------
	// �������� ���´�.
	//-----------------------------------------------------------------
	g_pPlayer->SetGroundCreature();

	//--------------------------------------------------
	// Burrow���� ���������� Effect == Burrowing�ϴ� Effect
	//--------------------------------------------------		
	ExecuteActionInfoFromMainNode(
		RESULT_MAGIC_HIDE,										// ��� ��� ��ȣ
	
		g_pPlayer->GetX(), g_pPlayer->GetY(), 0,
		g_pPlayer->GetDirection(),														// ��� ����
		
		OBJECTID_NULL,												// ��ǥ�� ���� ����
		g_pPlayer->GetX(), g_pPlayer->GetY(), 0, 
		
		0,													// ����� (����) ���� �ð�		
		
		NULL,
		
		false);			// ��� ÷���� �����Ѵ�.

#endif

	__END_CATCH
}
