//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowBombOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCThrowBombOK2.h"
#include "ClientDef.h"
#include "MEffectStatusDef.h"
#include "PacketFunction2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowBombOK2Handler::execute ( GCThrowBombOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

		
	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);

	// �ǹ̾���.
	DWORD delayFrame = 16;//ConvertDurationToFrame( pPacket->getDuration() );

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
			DEBUG_ADD("[Error] the User of GCSkillToBombOK2 is Player!");			
		}
		else
		{
			//------------------------------------------------------
			// �����
			//------------------------------------------------------
			int creatureID = pPacket->getObjectID();
			MCreature* pCreature = g_pZone->GetCreature( creatureID );

			int skillID = GetBombActionInfo( pPacket->getItemType() );//pPacket->getSkillType();	

			if (skillID < 0)
			{
				DEBUG_ADD_FORMAT("[Error] no match skillType. itemType=%d", pPacket->getItemType());
				return;
			}

			int useSkillID = skillID;

			DEBUG_ADD("CurWA");

			if ((*g_pActionInfoTable)[skillID].IsAffectCurrentWeaponAction()
				&& pCreature!=NULL)
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
			// BombOK2�� ���� ��� 
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

			pResult->Add( new MActionResultNodeActionInfo( 
												skillID,
												creatureID, 
												targetID,
												pPacket->getX(),
												pPacket->getY(),
												delayFrame ) 
								);	
		
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
																	useSkillID, //(*g_pActionInfoTable)[skillID].GetActionResultValue(),
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
				
				int direction = pPacket->getDir();
				
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
				pCreature->SetDirection( pPacket->getDir() );				

				//------------------------------------------------------
				// BombOK2�� ���� ��� �߰�
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
	
	DEBUG_ADD("BombOK2End");

#endif

	__END_CATCH
}
