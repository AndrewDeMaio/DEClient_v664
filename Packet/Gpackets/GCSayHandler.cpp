//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSayHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSay.h"
#include "ClientDef.h"
#include "UserInformation.h"
#include "MChatManager.h"
#include "MSkillManager.h"
#include "MZoneTable.h"	
#include "MZone.h"	
#include "UIFunction.h"
#include "MGameStringTable.h"
#if __CONTENTS(__FUNCTION_PETFOOD)
#include "MFakeCreature.h"
#endif //__FUNCTION_PETFOOD
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCSayHandler::execute ( GCSay * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
//#ifdef __GAME_CLIENT__

	// Debug Message	
	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
	}
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		//---------------------------------------------------------------
		// ĳ���� �Ӹ� ���� ä���� ����.
		//---------------------------------------------------------------
		//DEBUG_ADD("Zone-GetCreature");

		MCreature*	pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature==NULL)
		{
			// �׷� ĳ���Ͱ� ������ �����Ѵ�.
			DEBUG_ADD("No such Character");
		}
		else
		{			
			bool IsGildre	= pCreature->GetCreatureType() == 717 || 
							  pCreature->GetCreatureType() == 723 ; // ���巹 �϶�
			bool bMasterWords = pCreature->GetCreatureType()==CREATURETYPE_SLAYER_OPERATOR
								|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_OPERATOR
								|| pCreature->GetCreatureType()==CREATURETYPE_OUSTERS_OPERATOR
								|| strncmp( pCreature->GetName(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetString(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetLength() ) == 0
								|| IsGildre ;
//								|| (strstr(pCreature->GetName(), "GM")!=NULL);

			//DEBUG_ADD_FORMAT("isMasterWords=%d", bMasterWords);

			//-------------------------------------------------
			// �������� ��ȭ
			//-------------------------------------------------
			if (bMasterWords 
				|| g_pChatManager->IsAcceptID( pCreature->GetName() ))
			{
				//DEBUG_ADD("can see");

				// ä��~~
				char str[256];
				int creatureType = pCreature->GetCreatureType();

				bool isPlayerVampire = creatureType==CREATURETYPE_VAMPIRE_MALE1
										|| creatureType==CREATURETYPE_VAMPIRE_FEMALE1
										|| creatureType==CREATURETYPE_VAMPIRE_MALE2
										|| creatureType==CREATURETYPE_VAMPIRE_FEMALE2
										|| creatureType==CREATURETYPE_VAMPIRE_MALE3
										|| creatureType==CREATURETYPE_VAMPIRE_FEMALE3
										|| creatureType==CREATURETYPE_VAMPIRE_MALE4
										|| creatureType==CREATURETYPE_VAMPIRE_FEMALE4
										|| creatureType==CREATURETYPE_VAMPIRE_OPERATOR
										|| creatureType==CREATURETYPE_BAT
										|| creatureType==CREATURETYPE_VAMPIRE_GHOST
										|| creatureType==CREATURETYPE_WOLF
										|| creatureType==CREATURETYPE_WER_WOLF
#if __CONTENTS(__FAST_TRANSFORTER)
										|| creatureType==CREATURETYPE_FLITTERMOUSE
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
										|| creatureType==CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
										;

				bool isPlayerCharacter = (isPlayerVampire 
											|| pCreature->IsSlayer()
											|| pCreature->IsOusters()
											|| creatureType==CREATURETYPE_SLAYER_OPERATOR);

				//DEBUG_ADD("strcpy");
// �÷��̾ ���� ��ȯ �ϰ� �ְ� �� ���� �뿪 ����� ������ �ִ��� ������ üũ 
#if __CONTENTS(__FUNCTION_PETFOOD)
				MFakeCreature *pFakeCreature = (MFakeCreature *)g_pZone->GetFakeCreature(g_pPlayer->GetPetID());
				int functionPetfoodType = 0;
				if(pFakeCreature)
				{
					MPetItem *pPetItem = pFakeCreature->GetPetItem();
					functionPetfoodType = pPetItem->getFunctionPetfoodType();
				}
#endif //__FUNCTION_PETFOOD

				//---------------------------------------------------------------
				// �ϼ��� --> ������
				//---------------------------------------------------------------
				//UI_WansungToJohap( pPacket->getMessage().c_str(), str );
				strcpy( str, pPacket->getMessage().c_str() );
				bool	bTranslation = g_pSkillAvailable->IsEnableSkill(SKILL_HOLYLAND_BLOOD_BIBLE_HILLEL) || 
					!g_pZoneTable->Get( g_pZone->GetID() )->ChatMaskByRace ||
					g_pPlayer->HasEffectStatus( EFFECTSTATUS_TRANSLATION ) ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_SLAYER_OPERATOR ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_VAMPIRE_OPERATOR ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_OUSTERS_OPERATOR
#if __CONTENTS(__FUNCTION_PETFOOD)
					|| functionPetfoodType == 2
#endif //__FUNCTION_PETFOOD
					;

				bool bHasHallu = g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION);

				//--------------------------------------------------
				// �� ����
				// ��ڰ� �� ���� �ƴϰ� ���� ��ڰ� �ƴϸ� filter�Ѵ�.
				// --> ����� ���� �� ���̰� ��ڴ� �� ����.
				//--------------------------------------------------
				if (!bMasterWords && !g_pUserInformation->IsMaster 
					&& !g_pPlayer->HasEffectStatus( EFFECTSTATUS_GHOST )
#ifdef __METROTECH_TEST__
					&& !g_bLight
#endif
					)
				{
					
					// player�� ��츸 ���۸� ����
					if (isPlayerCharacter)
					{
						g_pChatManager->RemoveCurse( str );
						
						
						if (g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION))
						{
							g_pChatManager->AddMask(str, 50);
						}
					}			

//					#ifndef _DEBUG
					//--------------------------------------------------
					// ������ �ٸ� ���
					//--------------------------------------------------
					if (g_pPlayer->GetRace() != pCreature->GetRace()
						// player�� ��츸.. �� ���..
						//&& isPlayerVampire 
						&& isPlayerCharacter
						&& !bTranslation 
						&& !g_pPlayer->HasEffectStatus( EFFECTSTATUS_GHOST )
#ifdef __METROTECH_TEST__
						&& !g_bLight
#endif
						)
					{
						//DEBUG_ADD("add mask1");
						
						// INT�� 150�����̹Ƿ�..  
						int percent;
						percent = min(75, 25+g_pPlayer->GetINT()*100/(min(2, g_pPlayer->GetRace()+1)*150));
						
						g_pChatManager->AddMask(str, percent);
						
						
					}
					// �ҷ� ���´� ä�õ� ����� �� ���δ�.
					else if (bHasHallu)
					{
						g_pChatManager->AddMask(str, 50);
					}
					//					#endif//_DEBUG
				}
				pCreature->SetChatString( str, pPacket->getColor() );
				// history�� �߰�
				char strName[256];
				// ������ �ٸ��� hallu name�� �о�´�
				if(bHasHallu || !bMasterWords && !g_pUserInformation->IsMaster && g_pPlayer->GetRace() != pCreature->GetRace() && !bTranslation)
					strcpy(strName, pCreature->GetHalluName());
				else
					strcpy(strName, pCreature->GetName());

				// player�� ��츸 ä��â�� �� �ִ´�.
				if (isPlayerCharacter /*|| IsGildre*/) // ���巹 �ϰ�� �� ä������ �����ٰ� �ؼ� ����..
				{
					//DEBUG_ADD("UI add");
					UI_AddChatToHistory( str, strName, 0, pPacket->getColor() );
					//DEBUG_ADD("UI add");
				}
			}
			//-------------------------------------------------
			// ��ȭ �źη� �����Ǿ� �ִٸ� ��¾��Ѵ�.
			//-------------------------------------------------
			else
			{
				//DEBUG_ADD("no see");
				//pCreature->SetChatString( "......", pPacket->getColor() );
			}
		}
	}
//#endif

	__END_CATCH
}
