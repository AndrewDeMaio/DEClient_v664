//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMonsterKillQuestInfoHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCMonsterKillQuestInfo.h"
#include "MMonsterKillQuestInfo.h"
#include "MCreatureTable.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestInfoHandler::execute ( GCMonsterKillQuestInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
		
	while(! pPacket->empty() )
	{
		std::auto_ptr<GCMonsterKillQuestInfo::QuestInfo> pInfo( pPacket->popQuestInfo() );
//		GCMonsterKillQuestInfo::QuestInfo* pInfo = pPacket->popQuestInfo();	
		std::string str;
		//pInfo->sType
		str = (*g_pCreatureTable)[pInfo->sType].Name;
		g_pQuestInfoManager->SetInfo (pInfo->questID, pInfo->goal, pInfo->timeLimit, str);		
//		delete pInfo;
	}
	
#endif

	__END_CATCH
}
