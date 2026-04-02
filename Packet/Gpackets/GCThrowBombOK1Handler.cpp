//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowBombOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCThrowBombOK1.h"
#include "ClientDef.h"
#include "PacketFunction2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowBombOK1Handler::execute ( GCThrowBombOK1 * pPacket , Player * pPlayer )
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
		int skillID = GetBombActionInfo( pPacket->getItemType() );//pPacket->getSkillType();	

		if (skillID < 0)
		{
			DEBUG_ADD_FORMAT("[Error] no match skillType. itemType=%d", pPacket->getItemType());
			return;
		}

		int useSkillID = skillID;
		
		if ((*g_pActionInfoTable)[skillID].IsAffectCurrentWeaponAction())
		{
			useSkillID = g_pPlayer->GetBasicActionInfo();

			if (useSkillID >= g_pActionInfoTable->GetMinResultActionInfo())
			{
				DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", useSkillID);
				return;
			}
		}
			
		// �ǹ̾���.
		DWORD delayFrame = 16;//ConvertDurationToFrame( pPacket->getDuration() );

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

		pResult->Add( new MActionResultNodeActionInfo( 
											skillID,
											g_pPlayer->GetID(), 
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
		//if ((*g_pActionInfoTable)[skillID].IsOptionRangeToDirection())
		{
		//	g_pPlayer->SetDirection( pPacket->getDir() );	
		}		
	
		// Player�� ���� ���� ���� ����� ����� �߰���Ų��.		
		g_pPlayer->PacketAddActionResult( 0, pResult );

	}


#endif

	__END_CATCH
}
