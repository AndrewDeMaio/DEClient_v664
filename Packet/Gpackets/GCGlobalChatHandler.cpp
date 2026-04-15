//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGlobalChatHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGlobalChat.h"
#include "ClientDef.h"
#include "MChatManager.h"
#include "UserInformation.h"
#include "MSkillManager.h"
#include "MZone.h"
#include "MZoneTable.H"
#include "UIFunction.h"
#include "MGameStringTable.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCGlobalChatHandler::execute ( GCGlobalChat * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	
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
		char str[256];
		char strName[256];

		//---------------------------------------------------------------
		// �ϼ��� --> ������
		//---------------------------------------------------------------
		//UI_WansungToJohap( pPacket->getMessage().c_str(), str );
		strcpy( str, pPacket->getMessage().c_str() );

		//UI_AddChatToHistory( str );
		char* pLB = strchr( str, ' ' );

		if (pLB!=NULL)
		{
			if (*(pLB+1)!=NULL)
			{
				// ' '�� NULL��
				*pLB = NULL;

				strcpy(strName, str);
 
				//bool bMasterWords = (strstr(strName, "GM")!=NULL);
				bool bMasterWords = strncmp( strName, (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetString(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetLength() ) == 0 ;

				//--------------------------------------------------
				// ������ ���̴� ���ΰ�? (����� ���� ������ ���δ�)
				//--------------------------------------------------
				if (bMasterWords 
					|| g_pChatManager->IsAcceptID( strName ))
				{
					//--------------------------------------------------
					// �� ����
					// ��ڰ� �� ���� �ƴϰ� ���� ��ڰ� �ƴϸ� filter�Ѵ�.
					// --> ����� ���� �� ���̰� ��ڴ� �� ����.
					//--------------------------------------------------			

					if (!bMasterWords && 
						!g_pUserInformation->IsMaster 
						&& !g_pPlayer->HasEffectStatus( EFFECTSTATUS_GHOST )
#ifdef __METROTECH_TEST__
				&& !g_bLight
#endif
					)
					{
						//--------------------------------------------------
						// �� ����
						//--------------------------------------------------
						g_pChatManager->RemoveCurse( pLB+1 );

#if __CONTENTS(__JAPAN_UI)						
						ZONETABLE_INFO *pZoneInfo = g_pZoneTable->Get( g_pZone->GetID() );
						if( pZoneInfo->ChatMaskByRace == true && 
							!g_pSkillAvailable->IsEnableSkill(SKILL_HOLYLAND_BLOOD_BIBLE_HILLEL) &&
							!g_pPlayer->HasEffectStatus( EFFECTSTATUS_TRANSLATION ))
						{
							//--------------------------------------------------
							// ������ �ٸ� ���
							//--------------------------------------------------
							Race race = (Race)pPacket->getRace();
							if (g_pPlayer->GetRace() != race)
							{
								// INT�� 150�����̹Ƿ�..  
								int percent = min(75, 25+g_pPlayer->GetINT()*100/(min(2, g_pPlayer->GetRace()+1)*150));
								//if(g_pPlayer->GetRace() == RACE_OUSTERS || race == RACE_OUSTERS)
									//percent = 70;
								
								g_pChatManager->AddMask(str, percent);
							}
//							if (g_pPlayer->IsSlayer() && race != RACE_SLAYER)
//							{
//								// INT�� 150�����̹Ƿ�..  
//								int percent = min(75, 25+g_pPlayer->GetINT()*100/150);
//								if(race == RACE_OUSTERS)
//									percent = 70;
//								g_pChatManager->AddMask(pLB+1, percent);
//							}
//							else if (g_pPlayer->IsVampire() && race != RACE_VAMPIRE)
//							{
//								// INT�� 300�����̹Ƿ�..  
//								int percent = min(75, 25+g_pPlayer->GetINT()*100/300);
//								if(race == RACE_OUSTERS)
//									percent = 70;
//								g_pChatManager->AddMask(pLB+1, percent);
//							}
//							else if (g_pPlayer->IsOusters() && race != RACE_OUSTERS)
//							{
//								// INT�� 300�����̹Ƿ�..  
//								//int percent = min(75, 25+g_pPlayer->GetINT()*100/300);
//								int percent = 70;
//								g_pChatManager->AddMask(pLB+1, percent);
//							}
						}
#endif //__JAPAN_UI

					}

					// ZONECHAT = 1
					UI_AddChatToHistory( pLB+1, strName, 1, pPacket->getColor() );

					// [����] ��ġ�� �� ��
//					__BEGIN_HELP_EVENT
////						ExecuteHelpEvent( HE_CHAT_SHOUTED );	
//					__END_HELP_EVENT
				}
			}
		}
	}

#endif

	__END_CATCH
}
