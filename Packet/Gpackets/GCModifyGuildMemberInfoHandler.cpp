//////////////////////////////////////////////////////////////////////
//
// Filename    : GCModifyGuildMemberInfoHandler.cc
// Written By  : elca
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCModifyGuildMemberInfo.h"
#include "UserInformation.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfoHandler::execute ( GCModifyGuildMemberInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	g_pUserInformation->GuildName = pPacket->getGuildName().c_str();
	g_pUserInformation->GuildGrade = pPacket->getGuildMemberRank();
	g_pPlayer->SetGuildNumber(pPacket->getGuildID());

	UI_SetGuild(pPacket->getGuildID(), pPacket->getGuildMemberRank(), pPacket->getGuildName());
#endif

	__END_CATCH
}
