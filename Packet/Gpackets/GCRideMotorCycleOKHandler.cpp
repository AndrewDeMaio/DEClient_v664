//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRideMotorCycleOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCRideMotorCycleOK.h"
#include "ClientDef.h"
#include "MItem.h"
#include "SoundDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycleOKHandler::execute ( GCRideMotorCycleOK * pPacket , Player * pPlayer )
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
	//------------------------------------------------------
	else
	{
		MItem* pItem = g_pZone->GetItem( pPacket->getObjectID() );

		//------------------------------------------					
		// pItem�� ������̿��� �Ѵ�.
		// player�� ��� ��Ų��.
		//------------------------------------------					
		if (pItem != NULL)
		{
			if (pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
			{
				//------------------------------------------					
				// ������� addon ����.
				//------------------------------------------					
				g_pPlayer->SetAddonItem( pItem );
				
				//------------------------------------------
				// �����̴� ��� �ٲ�
				//------------------------------------------					
				//g_pPlayer->SetMoveDevice( MCreature::MOVE_DEVICE_RIDE );

				//------------------------------------------
				// Server�� ���ӵ� ��찡 �ƴϸ�..
				// �ٷ� mouse�� item�� �ٴ´�.
				//------------------------------------------
				//PlaySound( pItem->GetTileSoundID(),
				//			false,
				//			g_pPlayer->GetX(), g_pPlayer->GetY());

				//gC_vs_ui.PickUpItem(pItem);
				g_pZone->RemoveItem( pItem->GetID() );
				//20090325 helltest
//				g_pPlayer->SetHellBikeEffect( 0 );

				PlaySound( SOUND_WORLD_BIKE_GO );
			}
			else
			{
				DEBUG_ADD_FORMAT("[Error] id=%d is Not Motorcycle", pPacket->getObjectID());			
			}
		}
	}
	
	//------------------------------------------
	// ��¶�� ����.. ������ �Ǿ��ٰ� ����.
	//------------------------------------------
	g_pPlayer->SetWaitVerifyNULL();

	// [����] ������� ź ���
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_ITEM_RIDE_MOTORCYCLE );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
