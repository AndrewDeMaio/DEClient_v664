//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTakeOffHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCTakeOff.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCTakeOffHandler::execute ( GCTakeOff * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	//------------------------------------------------------
	//
	//  Creature�� Addon�� �����Ѵ�.
	//
	//------------------------------------------------------
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

		//--------------------------------------------------
		// Creature�� ���� ���
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			DEBUG_ADD_FORMAT("[Error] Not Exist Creature. ID=%d", pPacket->getObjectID());
		}
		//--------------------------------------------------
		// �����ϴ� Creature�� ���
		// ������ �ִ� creature�̸� --> Addon����
		//--------------------------------------------------
		else if (pCreature->IsWear())
		{
			MCreatureWear* pCreatureWear = (MCreatureWear*)pCreature;
			
			// ĳ���͸� ������Ų��.
			pCreatureWear->SetStop();

			#ifdef	OUTPUT_DEBUG				
				if (pCreatureWear->RemoveAddon( pPacket->getSlotID() ))
				{
					DEBUG_ADD_FORMAT("[OK] RemoveAddon. ID=%d, Slot=%d", pPacket->getObjectID(), (int)pPacket->getSlotID());
				}
				else
				{
					const MCreatureWear::ADDON_INFO& addonInfo = pCreatureWear->GetAddonInfo(pPacket->getSlotID());
					DEBUG_ADD_FORMAT("[Error] RemoveAddon. ID=%d, Slot=%d, AddonFrameID=%d", pPacket->getObjectID(), (int)pPacket->getSlotID(), addonInfo.FrameID);					
				}				
			#else
				pCreatureWear->RemoveAddon( pPacket->getSlotID() );
			#endif
		}
			
		//--------------------------------------------------
		// ���� ���� �� ���� Creature�� ���
		//--------------------------------------------------
		else 
		{
			DEBUG_ADD_FORMAT("[Error] Creature is Not CreatureWear. ID=%d", pPacket->getObjectID());
		}
	}
	

#endif

	__END_CATCH
}
