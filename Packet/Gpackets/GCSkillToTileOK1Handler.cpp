//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToTileOK1.h"
#include "ClientDef.h"
#include "PacketFunction2.h"
#include "SkillDef.h"
//#include "mintr.h"
#include "MSlayerGear.h"

extern void Add_FakeCreature_Storm(MCreature* UserCreature, int CreatureType,
								   int TargetX, int TargetY, int RangeW, int RangeH, float density);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1Handler::execute ( GCSkillToTileOK1 * pPacket, Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__
		
	//------------------------------------------------------------------
	// Player�� ��ٸ��� skill�� ���������� �����޾Ҵ�.
	//------------------------------------------------------------------
	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_SKILL_SUCCESS)
	{		
		g_pPlayer->SetWaitVerifyNULL();
	}
	else
	{
		DEBUG_ADD("[Error] Player is not WaitVerifySkillSuccess");
	}


	//------------------------------------------------------------------
	// Player�� Skill�� ������Ų ��쿡 ���ƿ��� Packet�̹Ƿ�
	// ����� �ݿ����Ѿ� �Ѵ�.
	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);
	
	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );

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
		int skillID = pPacket->getSkillType();	


		if( g_pActionInfoTable->GetSize() <= skillID )
		{
			SendBugReport("[%s,%d] %d",__FILE__, __LINE__, skillID );
			return;
		}
//		// 2004, 9, 9, sobeit add start
//		if(skillID == SKILL_BURNING_SOUL_LAUNCH)
//		{
//			skillID = RESULT_CLIENT_BURNING_SOL_1+pPacket->getGrade();
//			
//			ExecuteActionInfoFromMainNode(skillID,pPacket->getX(), pPacket->getY(), 0,0,0	,	
//				pPacket->getX(), pPacket->getY(), 0, ConvertDurationToFrame( pPacket->getDuration() ), NULL, false);
//			return;
//		}
		if(skillID == SKILL_BURNING_SOUL_CHARGING)
		{
			g_pPlayer->SetTempSelectPos(pPacket->getX(), pPacket->getY());
		}
		else if(skillID == SKILL_ROTTEN_APPLE)
		{
			ExecuteActionInfoFromMainNode(SKILL_CLIENT_ROTTEN_APPLE,pPacket->getX(), pPacket->getY(), 0,0,0	,	
				pPacket->getX(), pPacket->getY(), 0, ConvertDurationToFrame( pPacket->getDuration() ), NULL, false);
		}
		else if(skillID == SKILL_BAT_STORM1)
		{
			Add_FakeCreature_Storm(g_pPlayer, CREATURETYPE_BAT_STORM_1,
				pPacket->getX(), pPacket->getY(), 5, 5, 0.5f);
		}
		else if(skillID == SKILL_BAT_STORM2)
		{
			Add_FakeCreature_Storm(g_pPlayer, CREATURETYPE_BAT_STORM_2,
				pPacket->getX(), pPacket->getY(), 5, 5, 0.7f);
		}


//		// 2004, 9, 9, sobeit add end
		int useSkillID = skillID;
		
		if ((*g_pActionInfoTable)[skillID].IsAffectCurrentWeaponAction() && skillID != SKILL_PIERCING )
		{
			useSkillID = g_pPlayer->GetBasicActionInfo();

			if (useSkillID >= g_pActionInfoTable->GetMinResultActionInfo())
			{
				SendBugReport("[%s,%d] %d",__FILE__, __LINE__, skillID);
				return;
			}
		}

		if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0 )
			useSkillID = skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() -1 );
				
		DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

		int size = pPacket->getCListNum();

		MActionResult* pResult = new MActionResult;

		//------------------------------------------------------
		// Player�� ����� ���������� ���..
		//------------------------------------------------------
		//int resultActionInfo = skillID + (*g_pActionInfoTable).GetMinResultActionInfo();
		//g_pPlayer->PacketSpecialActionResult( resultActionInfo );

		int targetID = g_pPlayer->GetID();
		if ((*g_pActionInfoTable)[skillID].GetActionResultID()==ACTIONRESULTNODE_ACTIONINFO)
		{
			targetID = OBJECTID_NULL;
		}
		
		if((*g_pActionInfoTable)[skillID].IsUseActionGrade() )
		{
			
			pResult->Add( new MActionResultNodeActionInfo(
				skillID,
				g_pPlayer->GetID(), 
				targetID, 
				pPacket->getX(),
				pPacket->getY(),
				delayFrame, pPacket->getRange() ) 
				);	
		} else
		{
			pResult->Add( new MActionResultNodeActionInfo( 
				skillID,
				g_pPlayer->GetID(), 
				targetID, 
				pPacket->getX(),
				pPacket->getY(),
				delayFrame ) 
				);	
		}
		
//		_MinTrace("GCSkilltoTileOK1Handler. PlayerID : %d(%d,%d) %d\n", g_pPlayer->GetID(), pPacket->getX(), pPacket->getY(), skillID );
		if (size!=0)
		{
			// ����� ���ϴ� ������ creature�� ���ؼ� ��� ǥ��
			for (int i=0; i<size; i++)
			{
				int targetID = pPacket->popCListElement();
				MCreature* pCreature = g_pZone->GetCreature( targetID );

				// Creature���� Damage? ����
				if (pCreature != NULL)
				{
					//------------------------------------------------------
					// EffectStatus�� �ִٸ� ���δ�.
					//------------------------------------------------------
				
					EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
					
					if (es!=EFFECTSTATUS_NULL)
					{
						pResult->Add( new MActionResultNodeAddEffectStatus( targetID, es, delayFrame ) );
					}

					// ��� �ٷ� ǥ��
					//pCreature->PacketSpecialActionResult( pPacket->getSkillType() + (*g_pActionInfoTable).GetMinResultActionInfo());
			
					// ����� ����� ǥ���ϴ� resultNode�� �����Ѵ�.
					//pResult->Add( new MActionResultNodeActionInfo( 
					//							g_pPlayer->GetID(), 
					//							pCreature->GetID(), 
					//							pPacket->getSkillType(),
					//							delayFrame ) 
					//			);			
					
					//------------------------------------------------------
					//
					// skill�� ����� ������ ���� ��Ų��.
					//
					//------------------------------------------------------
					MActionResultNode* pActionResultNode = NULL;

					switch ((*g_pActionInfoTable)[skillID].GetActionResultID())
					{
						//------------------------------------------------------
						// �ٸ� ActionInfo ����
						//------------------------------------------------------
						case ACTIONRESULTNODE_ACTIONINFO :
							pActionResultNode =  new MActionResultNodeActionInfo( 
																useSkillID,//(*g_pActionInfoTable)[skillID].GetActionResultValue(),
																g_pPlayer->GetID(), 
																pCreature->GetID(), 
																pCreature->GetX(), 
																pCreature->GetY(), 
																delayFrame);
						break;

						//------------------------------------------------------
						// Burrow ���..
						//------------------------------------------------------
						default :
							pActionResultNode = CreateActionResultNode(pCreature, useSkillID);
						
					}

					//------------------------------------------------------
					// NULL�� �ƴϸ� ���� ����
					//------------------------------------------------------
					if (pActionResultNode!=NULL)
					{
						pResult->Add( pActionResultNode );
					}
				}
			}			
		}			
		
		//------------------------------------------------------
		// range�� direction�� �����Ű�� ���
		//------------------------------------------------------
		if ((*g_pActionInfoTable)[skillID].IsOptionRangeToDirection())
		{
			g_pPlayer->SetDirection( pPacket->getRange() );
		}
	
		// Player�� ���� ���� ���� ����� ����� �߰���Ų��.		
		g_pPlayer->PacketAddActionResult( pPacket->getCEffectID(), pResult );

	}

#endif

	__END_CATCH
}
