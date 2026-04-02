//--------------------------------------------------------------------------------
//
// Filename    : GCChangeDarkLightHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "ClientDef.h"
#include "MTopView.h"

#include "GPacket_PCH.h"
#include "GCChangeDarkLight.h"
#include "UserInformation.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCChangeDarkLightHandler::execute ( GCChangeDarkLight * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	#ifdef __EXPO_CLIENT__
		return;
	#endif

	// message


	int darkLevel = pPacket->getDarkLevel();
	int lightSight = pPacket->getLightLevel();

	if (g_pUserInformation->IsMaster)
	{
		darkLevel = 0;
		lightSight = 13;
	}

	// ȭ���� ��ӱ�
	g_pTopView->SetDarkBits( darkLevel );		
	
	// Player�þ� ���� ũ��
	g_pPlayer->SetTimeLightSight( lightSight );		

	

#endif

	__END_CATCH
}
