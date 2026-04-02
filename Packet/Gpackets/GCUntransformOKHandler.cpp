//--------------------------------------------------------------------------------
//
// Filename    : GCUntransformOKHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCUntransformOK.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "MVampireGear.h"
#include "UserInformation.h"
#include "EffectSpriteTypeDef.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCUntransformOKHandler::execute ( GCUntransformOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	bool bWerWolf = g_pPlayer->GetCreatureType() == CREATURETYPE_WER_WOLF;

#if __CONTENTS(__FAST_TRANSFORTER)
	bool bFlitterMouse = g_pPlayer->GetCreatureType () == CREATURETYPE_FLITTERMOUSE;
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	bool bShapeOfDemon = g_pPlayer->GetCreatureType () == CREATURETYPE_SHAPE_OF_DEMON;
#endif //__SECOND_TRANSFORTER
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

	int x = pPacket->getX();
	int y = pPacket->getY();
	int dir = pPacket->getDir();

	int creatureType = g_pPlayer->IsMale()?CREATURETYPE_VAMPIRE_MALE1:CREATURETYPE_VAMPIRE_FEMALE1;

	MItem *pItem = g_pVampireGear->GetItem(MVampireGear::GEAR_VAMPIRE_COAT);
//	_MinTrace("Adasd2:%d %d\n",creatureType,g_pPlayer->IsMale());

	bool male = g_pPlayer->IsMale();
	TYPE_ITEMTYPE itemType = ITEMTYPE_NULL;

	if(pItem != NULL)
	{
		itemType = pItem->GetItemType();
	} 
	else
	{
		itemType = male;
	}

	creatureType = GetVampireCreatureType(SHAPE_NORMAL, male, itemType);

	if (g_pPlayer->GetCompetence()==0)
	{
		creatureType = CREATURETYPE_VAMPIRE_OPERATOR;
	}
	
	MActionResult* pResult = new MActionResult;

	pResult->Add( new MActionResultNodeChangeCreatureType( g_pPlayer->GetID(), creatureType ) );

	//--------------------------------------------------
	// ���ķ� ���ư���.
	//--------------------------------------------------								
	ExecuteActionInfoFromMainNode(
		RESULT_MAGIC_UN_TRANSFORM,										// ��� ��� ��ȣ
	
		x, y, 0,
		dir,
		
		OBJECTID_NULL,												// ��ǥ�� ���� ����
		x, y, 0, 
		
		0,													// ����� (����) ���� �ð�		
		
		pResult, //NULL,
		
		false);			// ��� ÷���� �����Ѵ�.

	g_pPlayer->SetDelay( 1000 );


	g_pPlayer->SetServerPosition( x, y );
	g_pPlayer->MovePosition( x, y );
	g_pPlayer->SetDirection( dir );
	g_pPlayer->SetCurrentDirection( dir );
#if __CONTENTS(__FAST_TRANSFORTER || __SECOND_TRANSFORTER)
	//����, �ø��͸��콺 �̴����� �ϴ� �ΰ������� �������� ���� �ΰ������� �����Ѵ�.
	g_pPlayer->SetWingType(0);
#endif //__FAST_TRANSFORTER

	// ���� �����̾ ������ Ǯ���� �� ����Ʈ ����Ʈ�� ������ �����
	if(g_pPlayer->IsVampire() && g_pPlayer->IsAdvancementClass())
	{
		for(int i = 0; i < 6; ++i)
			g_pPlayer->RemoveAttachEffect(EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLACK + i);
	}
#if __CONTENTS(__FAST_TRANSFORTER)
	// �ű��̵����� ����Ʈ�� ������ �����.
	if (bFlitterMouse)
	{
		for (int j = 0; j < 12; j += 2)
			g_pPlayer->RemoveAttachEffect(EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_ORANGE + j);
	}
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	if (bShapeOfDemon)
	{
		for (int j = 0; j < 8; j ++)
			g_pPlayer->RemoveAttachEffect(EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_WHITE + j);
	}
#endif //__SECOND_TRANSFORTER
	if( bWerWolf )
	{
		g_pPlayer->SetBodyColor1( g_pUserInformation->SkinColor );
		if( pItem != NULL )
			g_pPlayer->SetBodyColor2( pItem->GetItemOptionColorSet() );
		else
			g_pPlayer->SetBodyColor2( 377 );
	}
	

#endif

	__END_CATCH
}
