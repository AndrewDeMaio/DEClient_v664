//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCKnocksTargetBackOK1.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK1Handler::execute ( GCKnocksTargetBackOK1 * pPacket , Player * pPlayer )
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

		//------------------------------------------------------
		// ���� ��츸 ���� ������ ���δ�.
		//------------------------------------------------------
		if (pPacket->getSkillSuccess())
		{
			// Creature���� Damage ����
			if (pCreature != NULL)
			{			
				unsigned short x = pPacket->getX();
				unsigned short y = pPacket->getY();

				// �������¹���(direction)����..
				// �̵��� ���� ��ǥ�� �´�.
				//MCreature::GetPositionToDirection(x, y, pPacket->getDir());

				MActionResult* pResult = new MActionResult;

				pResult->Add( new MActionResultNodeChangePosition(
										pPacket->getObjectID(),
										x, y)
							);

			

				// Creature�� ��ǥ�� �ٷ� �ٲ۴�.
				//pCreature->SetPosition( x, y );
				//pCreature->SetServerPosition( x, y );
				//pCreature->SetStop();

				// ��� �ٷ� ǥ��
				//pCreature->PacketSpecialActionResult( 
				//					RESULT_SKILL_KNOCKS_TARGET_BACK//pPacket->getSkillType() + g_ActionInfoTable.GetMinResultActionInfo()
				//);			

				g_pPlayer->PacketAddActionResult( 0 , pResult);

				//------------------------------------------------------
				// ����ȭ ���� ������..
				// ���� ��ġ�� �ٷ� �����Ѵ�.
				//------------------------------------------------------
				pCreature->SetServerPosition( x, y );
			}
		}
		
		//------------------------------------------------------
		// �Ѿ� ���ش�.
		//------------------------------------------------------
		if (g_pCurrentMagazine==NULL)
		{
			DEBUG_ADD("[Error] Current Magazine Not Exist!");			
		}
		else
		{
			g_pCurrentMagazine->SetNumber( pPacket->getBullet() );
		}
	}

	
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
