//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRideMotorCycleHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCRideMotorCycle.h"
#include "ClientDef.h"
#include "MItem.h"
#include "SoundDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycleHandler::execute ( GCRideMotorCycle * pPacket , Player * pPlayer )
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
	// Creature�� pItem(�������)�� �����Ѵ�.
	//------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		//-------------------------------------------------------------
		// ĳ���Ͱ� �ִ� ���
		//-------------------------------------------------------------
		if (pCreature!=NULL)
		{
			// ���������� creature�� ���
			if (pCreature->IsWear())
			{
				MCreatureWear* pCreatureWear = (MCreatureWear*)pCreature;

				MItem* pItem = g_pZone->GetItem( pPacket->getTargetObjectID() );

				//------------------------------------------					
				// pItem�� ������̿��� �Ѵ�.
				// creature�� ��� ��Ų��.
				//------------------------------------------					
				if (pItem != NULL)
				{
					if (pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
					{
						//------------------------------------------					
						// ���� / ���ڿ� ����..
						// ������� addon ����.
						//------------------------------------------
						pCreatureWear->SetAddonItem( pItem );						
						
						//------------------------------------------
						// �����̴� ��� �ٲ�
						//------------------------------------------					
						//pCreatureWear->SetMoveDevice( MCreature::MOVE_DEVICE_RIDE );

						//------------------------------------------
						// Server�� ���ӵ� ��찡 �ƴϸ�..
						// �ٷ� mouse�� item�� �ٴ´�.
						//------------------------------------------
						//PlaySound( pItem->GetTileSoundID(),
						//			false,
						//			pCreatureWear->GetX(), pCreatureWear->GetY());

						//gC_vs_ui.PickUpItem(pItem);
						g_pZone->RemoveItem( pItem->GetID() );
						//20090325 helltest
//						pCreatureWear->SetHellBikeEffect( 0 );
						// ������� Ÿ�� �Ҹ� ���
						PlaySound( SOUND_WORLD_BIKE_GO,
									false,
									g_pPlayer->GetX(),
									g_pPlayer->GetY());
					}
					else
					{
						DEBUG_ADD_FORMAT("[Error] id=%d is Not Motorcycle", pPacket->getTargetObjectID());
					}
				}
			}
		}
		//-------------------------------------------------------------
		// ĳ���Ͱ� ���� ���
		//-------------------------------------------------------------
		else
		{
			MItem* pItem = g_pZone->GetItem( pPacket->getTargetObjectID() );

			//------------------------------------------					
			// pItem�� ������̿��� �Ѵ�.
			// �� ���ش�.
			//------------------------------------------					
			if (pItem != NULL)
			{
				if (pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
				{
					g_pZone->RemoveItem( pItem->GetID() );
				}
			}
		}
	}
	
#endif

	__END_CATCH
}
