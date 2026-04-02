//////////////////////////////////////////////////////////////////////
//
// Filename    : GCPetUseSkillHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCPetUseSkill.h"
#include "MZone.h"
#include "MFakeCreature.h"
#include "DebugInfo.h"
#include "SkillDef.h"
#include "PacketFunction.h"
#include "ClientDef.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCPetUseSkillHandler::execute ( GCPetUseSkill * pGCPetUseSkill , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__
	TYPE_OBJECTID attackerID = pGCPetUseSkill->getAttacker();
	TYPE_OBJECTID targetID = pGCPetUseSkill->getTarget();

	MCreature *pAttackerCreature = g_pZone->GetCreature(attackerID);
	MCreature *pTargetCreature = g_pZone->GetCreature(targetID);

	if( pAttackerCreature == NULL )
	{
		DEBUG_ADD_FORMAT("[GCPetUseSkillHandler] ����Ŀ(%d) ����-_-;", attackerID);
	}
	else
	{
		if( pTargetCreature == NULL )
		{
			DEBUG_ADD_FORMAT("[GCPetUseSkillHandler] Ÿ��(%d) ����-_-;", targetID);
		}
		else
		{
//			pTargetCreature->SetAction( ACTION_DAMAGED );		//������ ���� �ڵ� Ÿ ĳ���Ͱ� �н�Ʈ ���� ���϶� �߻� �� �� ����.
		
			MFakeCreature *pPet = (MFakeCreature *)g_pZone->GetFakeCreature(pAttackerCreature->GetPetID());
			
			if( pPet == NULL )
			{
				DEBUG_ADD_FORMAT("[GCPetUseSkillHandler] ��(%d) ����-_-;", pAttackerCreature->GetPetID());
			}
			else
			{
				int skillID = SKILL_STEP_NULL;
				if(pPet->GetPetItem() != NULL)
				{
					int petItemType = pPet->GetPetItem()->GetItemType();
					int petLevel = pPet->GetPetItem()->GetNumber();

					TYPE_SOUNDID soundID = (*g_pCreatureTable)[pPet->GetCreatureType()].GetActionSound( ACTION_ATTACK );

					if (soundID!=SOUNDID_NULL  )
					{
						PlaySound( soundID,
									false,
									pPet->GetX(), pPet->GetY());
					}

					switch(petItemType)
					{
					// ��ũ-_-;
					case 3:
						{
							ExecuteActionInfoFromMainNode(
								SKILL_CLIENT_TANK_ATTACKED,										// ��� ��� ��ȣ
								
								0, 0, 0,
								DIRECTION_DOWN, // ��� ����
								
								pTargetCreature->GetID(),												// ��ǥ�� ���� ����
								0, 0, 0, 
								
								0,													// ����� (����) ���� �ð�		
								
								NULL,
								
								false);	
						}

						if(petLevel >= 30 && petLevel < 40)
							skillID = SKILL_CLIENT_TANK_ATTACK_3;
						else if(petLevel >= 40 && petLevel < 50)
							skillID = SKILL_CLIENT_TANK_ATTACK_4;
						else if(petLevel >= 50)
							skillID = SKILL_CLIENT_TANK_ATTACK_5;
						break;
					case 4:	// stirge
						if(petLevel<20)
							skillID = SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1;
						else if(petLevel >= 20 && petLevel < 30)
							skillID = SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2;
						else if(petLevel >= 30 && petLevel < 40)
							skillID = SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3;
						else if(petLevel >= 40 && petLevel < 50)
							skillID = SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4;
						else if(petLevel >= 50)
							skillID = SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5;
						
						{
							ExecuteActionInfoFromMainNode(
								skillID,										// ��� ��� ��ȣ
								
								0, 0, 0,
								DIRECTION_DOWN, // ��� ����
								
								pTargetCreature->GetID(),												// ��ǥ�� ���� ����
								0, 0, 0, 
								
								0,													// ����� (����) ���� �ð�		
								
								NULL,
								
								true);	
						}
						break;
					case 5:	// pixie
						if(petLevel<20)
							skillID = SKILL_CLIENT_PIXIE_ABSORB_SOUL_1;
						else if(petLevel >= 20 && petLevel < 30)
							skillID = SKILL_CLIENT_PIXIE_ABSORB_SOUL_2;
						else if(petLevel >= 30 && petLevel < 40)
							skillID = SKILL_CLIENT_PIXIE_ABSORB_SOUL_3;
						else if(petLevel >= 40 && petLevel < 50)
							skillID = SKILL_CLIENT_PIXIE_ABSORB_SOUL_4;
						else if(petLevel >= 50)
							skillID = SKILL_CLIENT_PIXIE_ABSORB_SOUL_5;

						ExecuteActionInfoFromMainNode(
							skillID,										// ��� ��� ��ȣ
							
							0, 0, 0,
							DIRECTION_DOWN, // ��� ����
							
							pTargetCreature->GetID(),												// ��ǥ�� ���� ����
							0, 0, 0, 
							
							0,													// ����� (����) ���� �ð�		
							
							NULL,
							
							false);	
						break;

#if __CONTENTS(__NEW_PET_INCUBUS)
					case 11:	// ��ť���� ����
						{
//							pPet->SetAction( ACTION_ATTACK );
//							pPet->SyncTurretDirection();
							{
							PlaySound( SOUND_CABERUS_SKILL, false, pPet->GetX(), pPet->GetY());

							ExecuteActionInfoFromMainNode(
								SKILL_CLIENT_INCUBUS_ATTACK, 									// ��� ��� ��ȣ
								0, 0, 0,
								DIRECTION_DOWN, // ��� ����
								pTargetCreature->GetID(),										// ��ǥ�� ���� ����
								0, 0, 0, 
								0,																// ����� (����) ���� �ð�		
								NULL,								
								false);


						//	if(petLevel >= 30 && petLevel < 40)
						//		skillID = SKILL_CLIENT_TANK_ATTACK_3;
						//	else if(petLevel >= 40 && petLevel < 50)
						//		skillID = SKILL_CLIENT_TANK_ATTACK_4;
						//	else if(petLevel >= 50)
								skillID = REFLECT_AURA_PRISM;

							BYTE IncubusDirect = pPet->GetDirectionToPosition(pTargetCreature->GetX(), pTargetCreature->GetY());

							pPet->SetDirection(IncubusDirect);
							pPet->SetAction(ACTION_DRAINED);
							}
						}
						break;
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__UPGRADE_MONSTER_PET)
					case 28: case 29: case 34: case 35:
						{
							PlaySound( SOUND_CABERUS_SKILL, false, pPet->GetX(), pPet->GetY());

							ExecuteActionInfoFromMainNode(
														SKILL_CLIENT_INCUBUS_ATTACK, 	// ��� ��� ��ȣ
														0, 0, 0,
														DIRECTION_DOWN,					// ��� ����
														pTargetCreature->GetID(),		// ��ǥ�� ���� ����
														0, 0, 0, 
														0,								// ����� (����) ���� �ð�
														NULL,								
														false);

							skillID = REFLECT_AURA_PRISM;

							BYTE IncubusDirect = pPet->GetDirectionToPosition(pTargetCreature->GetX(), pTargetCreature->GetY());

							pPet->SetDirection(IncubusDirect);
							pPet->SetAction(ACTION_DRAINED);
						}
						break;
#endif //__UPGRADE_MONSTER_PET
					}
				}

				pPet->SetTurretDelay( 3 );
//				pPet->SetDirectionToPosition(pTargetCreature->GetX(), pTargetCreature->GetY());
				int sx = 0, sy = 0;
				BYTE petDirect = pPet->GetDirectionToPosition(pTargetCreature->GetX(), pTargetCreature->GetY());

				// 2004, 12, 21, sobeit add start - ��Ÿ��� �ͷ���ġ ����
				if( pPet->GetCreatureType() == 702 || pPet->GetCreatureType() == 703 || pPet->GetCreatureType() == 704 )
					pPet->SetTurretFinalDirection(petDirect);
				// 2004, 12, 21, sobeit add end

				if( pPet->GetCreatureType() == 702 )
				{
					POINT pointGap[8] = 
					{
						{ 11, 6 },	// ��
						{ 8, 2 },	// ����
						{ 0, 0 },	// ��
						{ -7, 2 },	// ����
						{ -10, 6 },	// ��
						{ -7, 10 },	// ���
						{ 0, 12 },	// ��
						{ 8, 10 },	// �»�
					};
					sx = pointGap[pPet->GetDirection()].x-pointGap[petDirect].x;
					sy = pointGap[pPet->GetDirection()].y-pointGap[petDirect].y;
				}

				ExecuteActionInfoFromMainNode(
					skillID,										// ��� ��� ��ȣ
					
					pPet->GetX(), pPet->GetY(), 0,
					petDirect, // ��� ����
					
					pPet->GetID(),												// ��ǥ�� ���� ����
					pPet->GetX(), pPet->GetY(), 0, 
					
					0,													// ����� (����) ���� �ð�		
					
					NULL,
					
					false, sx, sy);	
				
			}
		}
	}

	//cout << pGCPetUseSkill->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_CATCH
}
