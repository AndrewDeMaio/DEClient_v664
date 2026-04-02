//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCBloodDrainOK3.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK3Handler::execute ( GCBloodDrainOK3 * pPacket , Player * pPlayer )
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
		MCreature* pUserCreature = g_pZone->GetCreature( pPacket->getObjectID() );
		MCreature* pTargetCreature = g_pZone->GetCreature( pPacket->getTargetObjectID() );		

		// Creature���� Damage ����
		if (pUserCreature != NULL && pTargetCreature != NULL)
		{
			// TargetCreature���� UserCreature�� �����ϱ� �ִٱ� �˷��ش�.
			pTargetCreature->SetDrainCreatureID( pPacket->getObjectID() );

			pUserCreature->ClearStopBloodDrain();

			// [ TEST CODE ]
			//
			// ����� ����&�����ؼ� ������ �Ѵ�.
			//
			// ������(target)�� �������� ����� SKill�� ���� ���..
			// [ TEST CODE ]
			MActionResult* pResult = new MActionResult;

			//DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

			pResult->Add( new MActionResultNodeActionInfo( 
											SKILL_BLOOD_DRAIN,
											pPacket->getObjectID(), 
											pPacket->getTargetObjectID(), 
											pTargetCreature->GetX(),
											pTargetCreature->GetY()
											 ) );

			// ���� �ٶ󺸱�
			pUserCreature->SetDirectionToPosition(pTargetCreature->GetX(), pTargetCreature->GetY());
			//pTargetCreature->SetDirectionToPosition(pUserCreature->GetX(), pUserCreature->GetY());

			//Duration_t	m_Duration;
			pUserCreature->PacketSpecialActionToOther(
								SKILL_BLOOD_DRAIN,
								pPacket->getTargetObjectID(),
								pResult			// ���
			);		

			int delayFrame = 691200;	// 12�ð�*60��*60��*16frame = 12*60*60*16;
			pTargetCreature->AddEffectStatus( EFFECTSTATUS_BLOOD_DRAIN, delayFrame );
		}
	}	

#endif

	__END_CATCH
}
