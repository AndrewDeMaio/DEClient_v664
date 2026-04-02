//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGetOffMotorCycleHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGetOffMotorCycle.h"
#include "ClientDef.h"
#include "SoundDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGetOffMotorCycleHandler::execute ( GCGetOffMotorCycle * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	
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
	//
	// Creature�� ������̸� �������� �Ѵ�.
	//------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature!=NULL)
		{
			// ���������� creature�� ���
			if (pCreature->IsWear())
			{
				MCreatureWear* pCreatureWear = (MCreatureWear*)pCreature;
			
				//------------------------------------------
				// ������� �׸��� �����ش�.
				//------------------------------------------
				pCreatureWear->RemoveAddon( ADDON_MOTOR );

				//------------------------------------------
				// �����̴� ��� �ٲ�
				//------------------------------------------
				pCreatureWear->SetMoveDevice( MCreature::MOVE_DEVICE_WALK );

				//------------------------------------------
				// ������ �Ҹ� ���
				//------------------------------------------
				PlaySound( SOUND_WORLD_BIKE_STOP,
							false,
							g_pPlayer->GetX(),
							g_pPlayer->GetY());
			}
			else
			{
				DEBUG_ADD_FORMAT("[Error] Creature is not WearCreature id=%d", pPacket->getObjectID());
			}
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] Not Exist Creature id=%d", pPacket->getObjectID());
		}
	}

#endif

	__END_CATCH
}
