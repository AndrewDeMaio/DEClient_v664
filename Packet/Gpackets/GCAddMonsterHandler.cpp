//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddMonsterHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddMonster.h"
#include "ClientDef.h"
#include "SkillDef.h"
#include "PacketFunction.h"
#include "MTopView.h"

extern void Add_GDR_Effect(int nEffect, bool bAppearBossMonster);
extern void Add_Race_SlayerMonster(GCAddMonster * pPacket);
extern void Add_Race_OustersMonster(GCAddMonster * pPacket);
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddMonsterHandler::execute ( GCAddMonster * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
		

	/*
	if(pPacket->getMonsterType() == 814)
	{
		char szBuf[128];
		sprintf(szBuf, "[GCAddMonster] TYPE=%d, NAME=%s, X=%d, Y=%d\n",
			pPacket->getMonsterType(), pPacket->getMonsterName().c_str(), pPacket->getX(), pPacket->getY());
		OutputDebugString(szBuf);
	}
	*/

	//	cout << pPacket->toString() << endl;

	//AfxMessageBox( pPacket->toString().c_str() );
	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	// by kim 2021-08-13 ���� ��������
	EFFECTSTATUS	statusShadowCheck;
	//EFFECTSTATUS	statusShadowCheck = EFFECT_CLASS_TRANSLUCENCY;
	//end kim
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
		#ifdef __DEBUG_OUTPUT__
			DEBUG_ADD_FORMAT("[AddMonster] type=%d, id=%d, xy=(%d,%d), dir=%d", 
								pPacket->getMonsterType(),
								pPacket->getObjectID(), 
								pPacket->getX(), pPacket->getY(), 
								pPacket->getDir());
		#endif

		//AfxMessageBox( pPacket->toString().c_str() );
		WORD wMonsterType = pPacket->getMonsterType();	
		// ����������� ����(�����̾� ��� ���ʹ� ���� ó�� ���ص� �ǳ�..����)

		if(wMonsterType == 735 || wMonsterType == 793 || wMonsterType == 796 || wMonsterType == 797)
		{
			Add_Race_SlayerMonster(pPacket);
			
			return;
		}
		else if(wMonsterType == 737 || wMonsterType == 795 || wMonsterType == 800)
		{
			Add_Race_OustersMonster(pPacket);
			return;
		}
		// 2004, 9, 1, sobeit add start - �������� Ʈ���� ��� ������������ ������ �ʴ´�.
		else if( wMonsterType == 738 ||
			wMonsterType == 739 ||
			wMonsterType == 740 ||
			wMonsterType == 741 )
		{
			EffectInfo* pTempEffectInfo = pPacket->getEffectInfo();
			
			if(NULL != pTempEffectInfo)
			{
				if(pTempEffectInfo->getListNum()>0)
				{

					std::list<std::pair<WORD,DWORD> > TemList = pTempEffectInfo->GetList();
					std::list<std::pair<WORD,DWORD> >::iterator itr = TemList.begin();

					for(;itr != TemList.end(); ++itr)
					{
						EFFECTSTATUS	status		= (EFFECTSTATUS)itr->first;
						
						if(status == EFFECTSTATUS_HIDE_TO_ATTACKER)
						{
							if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_1) || 
								g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_2) || 
								g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_3) || 
								g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_4) || 
								g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_5) )
								return;
						}
					}
				}
			}
		}
#if __CONTENTS(__TIPOJYU_CASTLE)	//���� ������ �׸��� ����
		else
		{
			EffectInfo* pTempEffectInfo = pPacket->getEffectInfo();
			
			if(NULL != pTempEffectInfo)
			{
				if(pTempEffectInfo->getListNum()>0)
				{

					std::list<std::pair<WORD,DWORD> > TemList = pTempEffectInfo->GetList();
					std::list<std::pair<WORD,DWORD> >::iterator itr = TemList.begin();

					for(;itr != TemList.end(); ++itr)
					{
						EFFECTSTATUS	status		= (EFFECTSTATUS)itr->first;
						if(status	== EFFECT_CLASS_TRANSLUCENCY)
							statusShadowCheck	= EFFECT_CLASS_TRANSLUCENCY;
					}	
				}
			}
		}
#endif // __TIPOJYU_CASTLE
	
		// 2004, 9, 1, sobeit add end - �������� Ʈ���� ��� ������������ ������ �ʴ´�.
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreature;

			pCreature->SetZone( g_pZone );

			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( pPacket->getMonsterType() );
			pCreature->SetGroundCreature();
			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			if( pPacket->getMonsterType() == 808 ||
				pPacket->getMonsterType() == 809 
#if __CONTENTS(__ONIBLA)
				|| pPacket->getMonsterType() == 1071
#endif //__ONIBLA
				)
				pCreature->SetAction( ACTION_VAMPIRE_DRAIN );
			else	pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// [ TEST CODE ]
			// �̸� ����
			//char str[20];
			//sprintf(str, "ID=%d", pCreature->GetID());

			//by viva
			pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
			//pCreature->SetName( pPacket->getMonsterName().c_str() );
			//end

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );

			// �̸�
			//pCreature->SetName( pPacket->getName().toString().c_str() );

#if __CONTENTS(__TIPOJYU_CASTLE)	//���� ������ �׸��� ����
			if(statusShadowCheck == EFFECT_CLASS_TRANSLUCENCY)
			{
				SMonsterHalfAlpha	MonsterHalfAlpha;
				MonsterHalfAlpha.Release();
				MonsterHalfAlpha.bHalfAlpha			= true;
				MonsterHalfAlpha.iCreatureObjectID	= pPacket->getObjectID();
				MonsterHalfAlpha.iCreatureID		= pCreature->GetCreatureType();
				pCreature->SetAlpha(TRUE);

				if(g_pTopView)
				{
					g_pTopView->SetMonsterHalfAlpha(MonsterHalfAlpha);
				}
			}
#endif

			// ���� ����			

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
				pCreature = NULL;
			}
			else
			{			
				//------------------------------------------------------------
				// Load���� �ʾ����� load�Ѵ�.
				//------------------------------------------------------------
//				LoadCreatureType( pPacket->getMonsterType() );			
			}
		}
		else
		{
			if (pCreature->GetCreatureType()!=pPacket->getMonsterType())
			{
				pCreature->SetCreatureType(pPacket->getMonsterType());
			}

			pCreature->SetGroundCreature();
			
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );
		}

		if (pCreature!=NULL)
		{
			//--------------------------------------------------
			// Effect ���̱�..
			//--------------------------------------------------
			bool bShowComeFromPotal = true;
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );
			// 2004, 6, 25, sobeit add start - ���巹 ���� �� ȿ�� 

			TYPE_CREATURETYPE creatureType = pCreature->GetCreatureType();

			switch(creatureType)
			{
				case 724: // �����̾� ��ȯü 1
					Add_GDR_Effect(1, true);
					break;
				case 725: // // �����̾� ��ȯü 2
					Add_GDR_Effect(2, true);
					break;
				case 739: // Ʈ�� - ���� ����
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_LAND_MINE_LIGHT,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(),	pCreature->GetID(),	
						pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
					break;
				case 738: // Ʈ�� - �÷��� �����̼�
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_PLEASUER_STATION_LIGHT,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(),	pCreature->GetID(),	
						pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
					break;
				case 753:
					bShowComeFromPotal = false;
					pCreature->SetAction(ACTION_VAMPIRE_DRAIN);  
					break;
				case 765: // �׷���Ʈ ���Ǿ� ���� �ٴ� ����Ʈ
//				case 891: // �ﰡ�� �׷���Ʈ ���Ǿ�
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_GREAT_RUFFIAN_BODY,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(),	pCreature->GetID(),	
						pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
					break;
				case 768: // miga
					bShowComeFromPotal = false;
					pCreature->AddEffectStatus((EFFECTSTATUS)(EFFECTSTATUS_SUMMON_MIGA_FIRE), 0xFFFF);
					break;
				case 786: // �屳
					pCreature->AddEffectStatus((EFFECTSTATUS)(EFFECTSTATUS_GRAND_MASTER_VAMPIRE), 0xFFFF);
					break;
				case 788: // 
					bShowComeFromPotal = false;
					pCreature->AddEffectStatus((EFFECTSTATUS)(EFFECTSTATUS_DRAGON_TORNADO), 0xFFFF);
					break;
				case 789:
					bShowComeFromPotal = false;
					pCreature->AddEffectStatus((EFFECTSTATUS)(EFFECTSTATUS_DRAGON_TORNADO_CHILD), 0xFFFF);
					break;
				case 793:
				case 794:
				case 795: // ������
					bShowComeFromPotal = false;
					pCreature->AddEffectStatus(EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS, 0xffff);
					ExecuteActionInfoFromMainNode(RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS,pCreature->GetX(), pCreature->GetY(), 0,2,	pCreature->GetID(),	
						pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);		
					break;
				case 808:
				case 809:
					bShowComeFromPotal = false;
					break;
				case 814: // ����� ����
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_GREAT_RUFFIAN_BODY,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(), pCreature->GetID(),	
						pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);
					break;
			}

			// ���� ����Ʈ�� �ٴ� Creature��� ����Ʈ�� �ٿ��ش�.
			if(creatureType < g_pCreatureTable->GetSize())
			{
				CREATURETABLE_INFO &creatureInfo = g_pCreatureTable->Get(creatureType);

				if(creatureInfo.EffectStatus != EFFECTSTATUS_NULL)
				{
					pCreature->AddEffectStatus((EFFECTSTATUS)creatureInfo.EffectStatus, 0xFFFF);
				}
			}


			// 2004, 6, 25, sobeit add end - ���巹 ���� 
			//--------------------------------------------------
			// ������ ��쿡�� 0, ��Ż�� ������ ��쿡�� 1
			//--------------------------------------------------
			if (pPacket->getFromFlag()==1 && bShowComeFromPotal)
			{
//				if(pCreature->GetCreatureType() == 753)
//				{
//					pCreature->SetAction(ACTION_VAMPIRE_DRAIN);  
//				}
//				else
//				{
					g_pTopView->VampireComeFromPortal( pCreature );
					
					// �ٴ� ����Ʈ ���̱�
					int x			= pCreature->GetX();
					int y			= pCreature->GetY();
					DWORD delayFrame	= ConvertDurationToFrame( 18 );
					
					ExecuteActionInfoFromMainNode(
						RESULT_MAGIC_BLOODY_TUNNEL,		// �� ��ü�� RESULT_ACTIONINFO�̴�.
						
						x, y, 0,
						DIRECTION_DOWN,
						
						OBJECTID_NULL,
						x, y, 0,
						
						delayFrame,	
						
						NULL
						);
//				}
			}
			
			
		}
	}
	
	// [����] ���� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_MONSTER );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
