//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowItemOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCThrowItemOK2.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowItemOK2Handler::execute ( GCThrowItemOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	int skillType = MAGIC_THROW_HOLY_WATER;

	//int delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

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
			
		// Creature���� Damage ����
		if (pCreature == NULL)
		{
			
		}
		else
		{
			// ��(Player)�� �������� ����� SKill�� ���� ���..
			// [ TEST CODE ]
			MActionResult* pResult = new MActionResult;
			pResult->Add( new MActionResultNodeActionInfo( 
									skillType, 
									pCreature->GetID(), 
									g_pPlayer->GetID(), 
									g_pPlayer->GetX(),
									g_pPlayer->GetY()
									)
						);
									//delayFrame ) );		

			// [ TEST CODE ]
			//
			// ����� ����&�����ؼ� ������ �Ѵ�.
			//
			// ������ �ٶ󺸱�
			pCreature->SetDirectionToPosition(g_pPlayer->GetX(), g_pPlayer->GetY());

			//Duration_t	m_Duration;
			pCreature->PacketSpecialActionToOther(
								skillType, 
								g_pPlayer->GetID(),		// player�� �´´�.
								pResult						// ���
			);
		}
	}	
	
	/*
	//------------------------------------------------------
	// Player�� ����� ������ ���� ���..
	//------------------------------------------------------
	int resultActionInfo =  pPacket->getSkillType() + g_ActionInfoTable.GetMinResultActionInfo();
	g_pPlayer->PacketSpecialActionResult( 
						resultActionInfo,
						g_pPlayer->GetID(),
						g_pPlayer->GetX(),
						g_pPlayer->GetY()
	);

	//------------------------------------------------------------
	// Delay Frame ����
	//------------------------------------------------------------
	g_pPlayer->SetEffectDelayFrame( resultActionInfo, delayFrame );
	*/

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

#endif

	__END_CATCH
}
