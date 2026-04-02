//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK6Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToTileOK6.h"
#include "ClientDef.h"
#include "PacketFunction2.h"
#include "SkillDef.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK6Handler::execute ( GCSkillToTileOK6 * pPacket , Player * pPlayer )
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
		
		//------------------------------------------------------
		// ����ڰ� ���� ����̴�.
		//------------------------------------------------------
		int startX = pPacket->getOrgX();
		int startY = pPacket->getOrgY();
	
		int skillID = pPacket->getSkillType();

		if( g_pActionInfoTable->GetSize() <= skillID )
		{
			DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
			SendBugReport("[Error:GCSTTOK6H] Exceed SkillType %d", skillID );
			return;
		}
		// 2004, 9, 9, sobeit add start
		if(skillID == SKILL_BURNING_SOUL_LAUNCH)
		{
			int TempskillID = RESULT_CLIENT_BURNING_SOL_1+pPacket->getGrade();
			ExecuteActionInfoFromMainNode(TempskillID,pPacket->getX(), pPacket->getY(), 0,0,0	,	
				pPacket->getX(), pPacket->getY(), 0, ConvertDurationToFrame( pPacket->getDuration() ), NULL, false);
		//	return;
		}
		// 2004, 9, 9, sobeit add end
		
		if( (*g_pActionInfoTable)[skillID].IsUseActionStep() &&pPacket->getGrade() > 0 )
			skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);

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
			//int esDelayFrame = ConvertDurationToFrame( g_pPlayer->GetDURATION() );
			pResult->Add( new MActionResultNodeAddEffectStatus( 
										g_pPlayer->GetID(), 
										(EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), 
										delayFrame ));

			g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
		}

		/*
		
		pResult->Add( new MActionResultNodeActionInfo( 
											skillID,
											pCreature->GetID(), 
											pCreature->GetID(), 
											pPacket->getX(),
											pPacket->getY(),
											delayFrame ) 
							);	
		*/

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

				MCreature* pTargetCreature = g_pZone->GetCreature( targetID );

				if (pTargetCreature!=NULL)
				{
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
							if( (*g_pActionInfoTable)[skillID].IsUseActionGrade() )
							{
								pActionResultNode =  new MActionResultNodeActionInfo( 
									(*g_pActionInfoTable)[skillID].GetActionResultValue(),
									OBJECTID_NULL,//pCreature->GetID(), 
									targetID, 
									pTargetCreature->GetX(),
									pTargetCreature->GetY(),
									delayFrame, pPacket->getRange() );
							} else
							{
								pActionResultNode =  new MActionResultNodeActionInfo( 
									(*g_pActionInfoTable)[skillID].GetActionResultValue(),
									OBJECTID_NULL,//pCreature->GetID(), 
									targetID, 
									pTargetCreature->GetX(),
									pTargetCreature->GetY(),
									delayFrame);
							}
						break;

						//------------------------------------------------------
						// Burrow���.
						//------------------------------------------------------
						default :
							pActionResultNode = CreateActionResultNode(pTargetCreature, skillID);						
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
		int direction = pPacket->getRange();

		if (direction >= 8) direction = 0;

		//------------------------------------------------------
		// TileOK2�� ���� ��� �߰�
		//------------------------------------------------------
		//Duration_t	m_Duration;
		//pCreature->PacketSpecialActionToSector(
		//					pPacket->getSkillType(), 
		//					pPacket->getX(), pPacket->getY(),
		//					pResult						// ���
		//);			
	

		//------------------------------------------------------
		// ��� �������� �ٷ� ���۵ǰ� �Ѵ�.
		//------------------------------------------------------
		ExecuteActionInfoFromMainNode(
				skillID + (*g_pActionInfoTable).GetMinResultActionInfo(),

				startX, startY, 0,
		
				direction,														// ��� ����
		
				OBJECTID_NULL,												// ��ǥ�� ���� ����
		
				pPacket->getX(), pPacket->getY(), 0, 
		
				delayFrame,													// ����� (����) ���� �ð�		
		
				pResult,
				
				false);			// ��� ÷���� �����Ѵ�.
		
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

#endif

	__END_CATCH
}
