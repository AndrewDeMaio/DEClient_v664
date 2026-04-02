//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToSelfOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCSkillToSelfOK2.h"
#include "ClientDef.h"
#include "PacketFunction2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK2Handler::execute ( GCSkillToSelfOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		

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
		//
		// Creature�� ��� ��� 
		//
		//------------------------------------------------------
		if (pCreature != NULL)
		{	
			// [ TEST CODE ]
			//
			// ����� ����&�����ؼ� ������ �Ѵ�.
			//
			// ����(Player)�� �����ο��� SKill�� ����� ���..
			// [ TEST CODE ]

			int skillID = pPacket->getSkillType();
			
			if( g_pActionInfoTable->GetSize() <= skillID )
			{
				DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
				SendBugReport("[Error:GCSTSOK2H] Exceed SkillType %d", skillID );

				return;
			}			
			
			if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
				skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);
				
			MActionResult* pResult = new MActionResult;

			DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

			pResult->Add( new MActionResultNodeActionInfo( 
									skillID, 
									pCreature->GetID(), 
									pCreature->GetID(), 
									pCreature->GetX(),
									pCreature->GetY(),
									delayFrame ) );

			//------------------------------------------------------
			// EffectStatus�� �ִٸ� ���δ�.
			//------------------------------------------------------
			EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
			
			if (es!=EFFECTSTATUS_NULL)
			{
				pResult->Add( new MActionResultNodeAddEffectStatus( pCreature->GetID(), 
																		es, 
																		delayFrame ) );
			}

			//------------------------------------------------------
			//
			// skill�� ����� ������ ���� ���� ��Ų��.
			//
			//------------------------------------------------------
			MActionResultNode* pActionResultNode = CreateActionResultNode(pCreature, skillID);

			//------------------------------------------------------
			// NULL�� �ƴϸ� ���� ����
			//------------------------------------------------------
			if (pActionResultNode!=NULL)
			{
				pResult->Add( pActionResultNode );
			}

			//Duration_t	m_Duration;
			pCreature->PacketSpecialActionToSelf( 
									pPacket->getSkillType(),
									pResult	// ���
				);
		}
	
	}


	__END_CATCH
}
