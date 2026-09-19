//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToTileOK2.h"
#include "ClientDef.h"
#include "MEffectStatusDef.h"
#include "PacketFunction2.h"
#include "SkillDef.h"

extern void Add_FakeCreature_Storm(MCreature* UserCreature, int CreatureType,
								   int TargetX, int TargetY, int RangeW, int RangeH, float density);
extern void		SkillBatBreakerShadows(MCreature* pUserCreature, int tx, int ty);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK2Handler::execute ( GCSkillToTileOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

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
		//------------------------------------------------------
		// Player�� ����� ����̶�� packet�� ���ƿ� ���
		// --> Error��
		//------------------------------------------------------
		if (pPacket->getObjectID()==g_pPlayer->GetID())
		{
			DEBUG_ADD("[Error] the User of GCSkillToTileOK2 is Player!");			
		}
		else
		{
			//------------------------------------------------------
			// �����
			//------------------------------------------------------
			int creatureID = pPacket->getObjectID();
			MCreature* pCreature = g_pZone->GetCreature( creatureID );

			int skillID = pPacket->getSkillType();

			if( g_pActionInfoTable->GetSize() <= skillID )
			{
				//DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);				
				SendBugReport("[%s,%d] %d,%d",__FILE__, __LINE__, skillID );
				return;
			}
	
			// 2004, 9, 9, sobeit add start
			if(skillID == SKILL_BURNING_SOUL_LAUNCH)
			{
				int TempskillID = SKILL_CLIENT_BURNING_SOL_1+pPacket->getGrade();
				ExecuteActionInfoFromMainNode(TempskillID,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(), pCreature->GetID()	,	
					pPacket->getX(), pPacket->getY(), 0, ConvertDurationToFrame( pPacket->getDuration() ), NULL, false);
			//	return;
			}
			else if(skillID == SKILL_ROTTEN_APPLE)
			{
				ExecuteActionInfoFromMainNode(SKILL_CLIENT_ROTTEN_APPLE,pPacket->getX(), pPacket->getY(), 0,0,0	,	
					pPacket->getX(), pPacket->getY(), 0, ConvertDurationToFrame( pPacket->getDuration() ), NULL, false);
			}
			// 2004, 9, 9, sobeit add end
			else if(skillID == SKILL_BAT_STORM1)
			{
				Add_FakeCreature_Storm(pCreature, CREATURETYPE_BAT_STORM_1,
					pPacket->getX(), pPacket->getY(), 5, 5, 0.5f);
			}
			else if(skillID == SKILL_BAT_STORM2)
			{
				Add_FakeCreature_Storm(pCreature, CREATURETYPE_BAT_STORM_2,
					pPacket->getX(), pPacket->getY(), 5, 5, 0.7f);
			}
			else if(skillID == SKILL_BAT_BREAKER)
			{
				SkillBatBreakerShadows(pCreature, pPacket->getX(), pPacket->getY());	// four shadow clones claw once
			}

			DEBUG_ADD_FORMAT("GRADE : %d %d",skillID, pPacket->getGrade());
			if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
				skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);

				int useSkillID = skillID;
		
			DEBUG_ADD("CurWA");

			if ((*g_pActionInfoTable)[skillID].IsAffectCurrentWeaponAction()
				&& pCreature!=NULL&& skillID != SKILL_PIERCING )
			{
				DEBUG_ADD("SetBA");

				useSkillID = pCreature->GetBasicActionInfo();

				if (useSkillID >= g_pActionInfoTable->GetMinResultActionInfo())
				{
					DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", useSkillID);
					return;
				}
			}

			//------------------------------------------------------
			// TileOK2�� ���� ��� 
			//------------------------------------------------------				
			int size = pPacket->getCListNum();

			MActionResult* pResult = new MActionResult;

			//------------------------------------------------------------------
			// effect status�� �����Ų��.
			//------------------------------------------------------------------
			if (g_pPlayer->GetEFFECT_STAT()!=EFFECTSTATUS_NULL)
			{
				DEBUG_ADD("AddES");

				pResult->Add( new MActionResultNodeAddEffectStatus( 
											g_pPlayer->GetID(), 
											(EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), 
											delayFrame ));

				g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
			}

			DEBUG_ADD("AResultID?");

			int targetID = creatureID;
			if ((*g_pActionInfoTable)[skillID].GetActionResultID()==ACTIONRESULTNODE_ACTIONINFO)
			{
				targetID = OBJECTID_NULL;
			}

			DEBUG_ADD("AddAI");
			
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
					creatureID, 
					targetID,
					pPacket->getX(),
					pPacket->getY(),
					delayFrame ) 
					);
			}

			
		
			if (size!=0)
			{
				// ����� ���ϴ� ������ creature�� ���ؼ� ��� ǥ��
				for (int i=0; i<size; i++)
				{
					//MCreature* pTargetCreature = g_pZone->GetCreature( pPacket->getCListElement() );
						
					// Creature���� Damage ����
					//if (pTargetCreature != NULL)
					//{
						// ��(Player)�� �������� ����� SKill�� ���� ���..
						// [ TEST CODE ]
						
					//	pResult->Add( new MActionResultNodeActionInfo( 
					//								pCreature->GetID(), 
					//								pPacket->popCListElement(), 
					//								pPacket->getSkillType(),
					//								delayFrame ) 
					//				);
					//}
					int targetID = pPacket->popCListElement();

					DEBUG_ADD("getTC");

					MCreature* pTargetCreature = g_pZone->GetCreature( targetID );

					if (pTargetCreature!=NULL)
					{
						DEBUG_ADD("TCNotNULL");

						//------------------------------------------------------
						// EffectStatus�� �ִٸ� ���δ�.
						//------------------------------------------------------
						EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
						
						if (es!=EFFECTSTATUS_NULL)
						{
							pResult->Add( new MActionResultNodeAddEffectStatus( targetID, es, delayFrame ) );
						}

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
								
								DEBUG_ADD("ANodeAI");

								pActionResultNode =  new MActionResultNodeActionInfo( 
																	skillID, //(*g_pActionInfoTable)[skillID].GetActionResultValue(),
																	creatureID, 
																	targetID, 
																	pTargetCreature->GetX(),
																	pTargetCreature->GetY(),
																	delayFrame);

								DEBUG_ADD("ANodeAI-ok");
							break;

							//------------------------------------------------------
							// Burrow ���.. 
							//------------------------------------------------------
							default :
								DEBUG_ADD("default");
								pActionResultNode = CreateActionResultNode(pTargetCreature, useSkillID);
						}

						//------------------------------------------------------
						// NULL�� �ƴϸ� ���� ����
						//------------------------------------------------------
						if (pActionResultNode!=NULL)
						{
							DEBUG_ADD("add");
							pResult->Add( pActionResultNode );
							DEBUG_ADD("ok");
						}
					}
					else
					{
						DEBUG_ADD("TCNull");
					}
				}
			}


			DEBUG_ADD("pCreture?");

			//------------------------------------------------------
			// ����� ĳ���Ͱ� ���� ��� --> ��� �ٷ� ǥ��
			//------------------------------------------------------
			if (pCreature==NULL)
			{
				DEBUG_ADD_FORMAT("[Error] The Creature is not Exist. id=%d", pPacket->getObjectID());
				
				int direction = 0;

				//------------------------------------------------------
				// range�� direction�� �����Ű�� ���
				//------------------------------------------------------
				if ((*g_pActionInfoTable)[skillID].IsOptionRangeToDirection())
				{
					direction = pPacket->getRange();
				}

				ExecuteActionInfoFromMainNode(
							skillID,										// ��� ��� ��ȣ
						
							pPacket->getX(), pPacket->getY(), 0,
							direction,														// ��� ����
							
							OBJECTID_NULL,		// 2002.3.6�� �ٲ�. ������ pPacket->getObjectID()����.
							pPacket->getX(), pPacket->getY(), 0,
							
							delayFrame,													// ����� (����) ���� �ð�		
							
							pResult,
							
							false);			// ��� ÷���� �����Ѵ�.);
			}
			//------------------------------------------------------
			// ����
			//------------------------------------------------------
			else
			{				
				DEBUG_ADD("C-OK");

				//------------------------------------------------------
				// ������ �ٶ󺸱�
				//------------------------------------------------------
				pCreature->SetDirectionToPosition(pPacket->getX(), pPacket->getY());		

				//------------------------------------------------------
				// range�� direction�� �����Ű�� ���
				//------------------------------------------------------
				if ((*g_pActionInfoTable)[pPacket->getSkillType()].IsOptionRangeToDirection())
				{
					pCreature->SetDirection( pPacket->getRange() );
				}

				//------------------------------------------------------
				// TileOK2�� ���� ��� �߰�
				//------------------------------------------------------
				//Duration_t	m_Duration;
				DEBUG_ADD("AtoSector");

				pCreature->PacketSpecialActionToSector(
									skillID, 
									pPacket->getX(), pPacket->getY(),
									pResult						// ���
				);

				DEBUG_ADD("AtoSectorOK");
			}
//			_MinTrace("Incomming GCSkillToTileOK2Handler(SkillType:%d X:%d Y:%d Dir:%d",
//				pPacket->getSkillType(), pPacket->getX(), pPacket->getY(), pCreature->GetDirection() );			
		}
	}

	
	//------------------------------------------------------------
	// Delay Frame ����
	//------------------------------------------------------------
	//g_pPlayer->SetEffectDelayFrame( resultActionInfo, delayFrame );




	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );
	
	DEBUG_ADD("TileOK2End");

#endif

	__END_CATCH
}
