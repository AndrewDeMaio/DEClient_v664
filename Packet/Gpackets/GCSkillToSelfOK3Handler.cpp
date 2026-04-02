//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToSelfOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToSelfOK3.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK3Handler::execute ( GCSkillToSelfOK3 * pPacket , Player * pPlayer )
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
		//MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );


		//------------------------------------------------------
		//
		// ��� �������� ��� ����� �ȴ�.
		//
		//------------------------------------------------------			

		int skillID = pPacket->getSkillType();
		
		if( g_pActionInfoTable->GetSize() <= skillID )
		{
			DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
			SendBugReport("[Error:GCSTSOK3H] Exceed SkillType %d", skillID );
			return;
		}


		if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
			skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);
		
		DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

		/*
		
		MActionResult* pResult = NULL;

		//------------------------------------------------------
		// EffectStatus�� �ִٸ� ���δ�.
		//------------------------------------------------------
		EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
		
		if (es!=EFFECTSTATUS_NULL)
		{
			pResult = new MActionResult;
			pResult->Add( new MActionResultNodeAddEffectStatus( g_Player->GetID(), 
																	es, 
																	delayFrame ) );
		}
	
		
		pResult->Add( new MActionResultNodeActionInfo( 
								skillID, 
								OBJECTID_NULL,//pCreature->GetID(), 
								OBJECTID_NULL,//pCreature->GetID(), 
								pPacket->getX(),//pCreature->GetX(),
								pPacket->getY(),//pCreature->GetY(),
								delayFrame ) );
		*/

		//------------------------------------------------------
		//
		// skill�� ����� ������ ���� ���� ��Ų��.
		//
		//------------------------------------------------------
		/*
		MActionResultNode* pActionResultNode = NULL;
		switch ((*g_pActionInfoTable)[skillID].GetActionResultID())
		{
			//------------------------------------------------------
			// Burrow
			//------------------------------------------------------
			case ACTIONRESULTNODE_CREATURE_BURROW :
				pActionResultNode = new MActionResultNodeCreatureBurrow(pCreature->GetID());
			break;
		}
		*/

		//------------------------------------------------------
		// NULL�� �ƴϸ� ���� ����
		//------------------------------------------------------
		/*
		if (pActionResultNode!=NULL)
		{
			pResult->Add( pActionResultNode );
		}
		*/

		//Duration_t	m_Duration;
		//pCreature->PacketSpecialActionToSelf( 
		//						pPacket->getSkillType(),
		//						pResult	// ���
		//	);

		//------------------------------------------------------
		// ��� ��ġ�� �ִ� ���...
		//------------------------------------------------------
		ExecuteActionInfoFromMainNode(
			skillID + (*g_pActionInfoTable).GetMinResultActionInfo(),
		
			pPacket->getX(), pPacket->getY(), 0, // ��� ����ϴ� ���(?) 
			0,														// ��� ����
			
			OBJECTID_NULL,												// ��ǥ�� ���� ����
			pPacket->getX(), pPacket->getY(), 0, 
			
			delayFrame,													// ����� (����) ���� �ð�		
			
			NULL,

			false);			// ��� ÷���� �����Ѵ�.
	}

#endif

	__END_CATCH
}
