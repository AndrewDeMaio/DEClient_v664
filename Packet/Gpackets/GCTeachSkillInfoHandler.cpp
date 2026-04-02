//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTeachSkillInfoHandler.cc
// Written By  : �輺�� 
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTeachSkillInfo.h"
#include "TempInformation.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCTeachSkillInfoHandler::execute ( GCTeachSkillInfo * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	// get/set NPC's object id
	//pPacket->getObjectID();
	
	// Skill�� ���� ���ؼ� SkillTree�� ����.
	UI_RunSkillTree( (int)pPacket->getDomainType(), 100 );//pPacket->getMaxLevel() );
	
	// �ӽ÷� ���� ����
	g_pTempInformation->SetMode(TempInformation::MODE_SKILL_LEARN);
	g_pTempInformation->Value1	=	pPacket->getDomainType();
	g_pTempInformation->Value2	=	100;//pPacket->getMaxLevel();
	

#endif

	__END_CATCH
}
