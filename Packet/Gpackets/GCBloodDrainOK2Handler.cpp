//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
// include files
#include "GCBloodDrainOK2.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK2Handler::execute ( GCBloodDrainOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


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
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		// ���� Creature���� �������ϱ� �ִٱ� �˷��ش�
		g_pPlayer->SetDrainCreatureID( pPacket->getObjectID() );
		
		// Creature���� Damage ����
		if (pCreature == NULL)
		{
			// �ٷ� ���ϴ� ���
			g_pPlayer->PacketSpecialActionResult( 
										RESULT_SKILL_BLOOD_DRAIN,
										g_pPlayer->GetID(),	
										g_pPlayer->GetX(),
										g_pPlayer->GetY()
			 );
		}
		else
		{
			pCreature->ClearStopBloodDrain();

			// ��(Player)�� �������� ����� SKill�� ���� ���..
			// [ TEST CODE ]
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( 
										SKILL_BLOOD_DRAIN,
										pCreature->GetID(), 
										g_pPlayer->GetID(), 
										g_pPlayer->GetX(),
										g_pPlayer->GetY()
										 ) );		

			// [ TEST CODE ]
			//
			// ����� ����&�����ؼ� ������ �Ѵ�.
			//
			// ������ �ٶ󺸱�
			pCreature->SetDirectionToPosition(g_pPlayer->GetX(), g_pPlayer->GetY());

			//Duration_t	m_Duration;
			pCreature->PacketSpecialActionToOther(
								SKILL_BLOOD_DRAIN,
								g_pPlayer->GetID(),
								pResult						// ���
			);
		}
	}	
	
	//------------------------------------------------------
	// Player�� ����� ������ ���� ���..
	//------------------------------------------------------
	/*
	int resultActionInfo =  SKILL_BLOOD_DRAIN + g_ActionInfoTable.GetMinResultActionInfo();
	g_pPlayer->PacketSpecialActionResult( 
						resultActionInfo,
						g_pPlayer->GetID(),
						g_pPlayer->GetX(),
						g_pPlayer->GetY()
				);
	*/
	//------------------------------------------------------------
	// Delay Frame ����
	//------------------------------------------------------------
	//g_pPlayer->SetEffectDelayFrame( resultActionInfo, delayFrame );

	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);
	
	//------------------------------------------------------------------
	// ���� ����..
	//------------------------------------------------------------------
	if (g_pPlayer->GetEFFECT_STAT()!=EFFECTSTATUS_NULL)
	{
		DWORD delayFrame = ConvertDurationToFrame( g_pPlayer->GetDURATION() );

		g_pPlayer->AddEffectStatus((EFFECTSTATUS)g_pPlayer->GetEFFECT_STAT(), delayFrame);	
		
		g_pPlayer->SetStatus( MODIFY_EFFECT_STAT, EFFECTSTATUS_NULL );
	}

	//------------------------------------------------------------------
	// UI�� ���̴� ���� �ٲ��ش�.
	// �񱳿����ϴ°ź��� �̰� �� ������ ������.. ��.. - -;
	//------------------------------------------------------------------
	//UI_SetHP( g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP() );
	//UI_SetMP( g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP() );
	
#endif

	__END_CATCH
}
