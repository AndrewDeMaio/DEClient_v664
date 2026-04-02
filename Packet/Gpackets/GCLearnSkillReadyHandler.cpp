//////////////////////////////////////////////////////////////////////
//
// Filename    : GCLearnSkillReady1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCLearnSkillReady.h"
#include "ClientDef.h"
#include "MSkillManager.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCLearnSkillReadyHandler::execute ( GCLearnSkillReady * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__


	// �ӽ÷� skill���� ������ �����Ѵ�.
	//g_TempInformation.Mode		=	TempInformation::MODE_SKILL_LEARN;
	//g_TempInformation.Value1	=	pPacket->getSkillDomainType();

	// ���� ��� Skill�� �ִٰ� ǥ���Ѵ�.
	int domainType = pPacket->getSkillDomainType();

	(*g_pSkillManager)[domainType].SetNewSkill();
	
	g_pGameMessage->AddFormat( "%s �迭�� ����� ��� �� �ֽ��ϴ�.", SKILLDOMAIN_NAME[domainType]);

	// levelup�ߴٰ� ���� �����ش�. ����.... --;
	//UI_LevelUp();

	// [����] Skill��� �� ���� ��
//	__BEGIN_HELP_EVENT
//		switch ( domainType )
//		{
//			case SKILL_DOMAIN_BLADE :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_BLADE );
//			break;
//
//			case SKILL_DOMAIN_SWORD :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_SWORD );
//			break;
//
//			case SKILL_DOMAIN_GUN :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_GUN );
//			break;
//
//			case SKILL_DOMAIN_ENCHANT :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_ENCHANT );
//			break;
//
//			case SKILL_DOMAIN_HEAL :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_HEAL );
//			break;
//			
//			case SKILL_DOMAIN_VAMPIRE :
////				ExecuteHelpEvent( HE_SKILL_CAN_LEARN_VAMPIRE );
//			break;
//		}
//	__END_HELP_EVENT
	
#endif

	__END_CATCH
}
