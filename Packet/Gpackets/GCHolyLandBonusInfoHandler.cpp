//////////////////////////////////////////////////////////////////////
//
// Filename    : GCHolyLandBonusInfoHandler.cpp
// Written By  : 
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCHolyLandBonusInfo.h"
#include "ClientDef.h"
#include "MSkillManager.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void GCHolyLandBonusInfoHandler::execute ( GCHolyLandBonusInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	if(g_pPlayer == NULL || g_pSkillAvailable == NULL)
		return;

	BloodBibleBonusInfo *pInfo = pPacket->popFrontBloodBibleBonusInfoList();
	
	int i = 0;
	while(pInfo != NULL)
	{
		if(g_pPlayer->GetRace() == pInfo->getRace())
//		if(g_pPlayer->IsSlayer() && pInfo->getRace() == RACE_SLAYER
//			|| g_pPlayer->IsVampire() && pInfo->getRace() == RACE_VAMPIRE
//			|| g_pPlayer->IsOusters() && pInfo->getRace() == RACE_OUSTERS
//			)
		{
			g_abHolyLandBonusSkills[i] = true;
		}
		else
		{
			// ��ų ����Ʈ���� ���ش�?		���� Ʋ���� �ٺ� �ȴ�
			g_abHolyLandBonusSkills[i] = false;
		}
		
		delete pInfo;

		pInfo = pPacket->popFrontBloodBibleBonusInfoList();
		i++;
	}

	//--------------------------------------------------
	// ���� ��� ������ skill���� �ٽ� üũ�Ѵ�.
	//--------------------------------------------------
	g_pSkillAvailable->SetAvailableSkills();

#endif

	__END_CATCH
}
