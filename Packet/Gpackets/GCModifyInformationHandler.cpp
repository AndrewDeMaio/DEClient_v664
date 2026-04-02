//////////////////////////////////////////////////////////////////////
//
// Filename    : GCModifyInformationHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCModifyInformation.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCModifyInformationHandler::execute ( GCModifyInformation * pPacket, Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	// message

	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	//------------------------------------------------------------------
	// effect status�� �����Ų��.
	//------------------------------------------------------------------
	if (g_pPlayer->GetEFFECT_STAT()!=EFFECTSTATUS_NULL)
	{
		DWORD esDelayFrame = ConvertDurationToFrame( g_pPlayer->GetDURATION() );

		// effect�� ���δ�.
		g_pPlayer->AddEffectStatus((EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), esDelayFrame);	
		
		g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
	}

	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );

#endif

	__END_CATCH
}
