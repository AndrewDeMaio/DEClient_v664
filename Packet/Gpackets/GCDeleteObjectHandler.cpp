//--------------------------------------------------------------------------------
//
// Filename    : GCDeleteObjectHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCDeleteObject.h"
#include "ClientDef.h"
#include "UIFunction.h"


#ifdef __GAME_CLIENT__
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCDeleteObjectHandler::execute ( GCDeleteObject * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	//cout << "Object[" << pPacket->getObjectID() << "] deleted from zone." << endl;

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
	// � Object�� �����ϴµ�..
	// --> �����غ��� Ȯ���ؾ� �Ѵ�.
	//------------------------------------------------------
	else
	{	
		TYPE_OBJECTID objectID = pPacket->getObjectID();

		if (g_pPlayer->IsItemCheckBufferDropToRelicTable())
		{
			//---------------------------------------------
			// ����߸����� item
			//---------------------------------------------
			MItem* pItem = g_pPlayer->GetItemCheckBuffer();

			if(pItem->GetID() == objectID)UI_DropItem();
			g_pPlayer->ClearItemCheckBuffer();
		}

		//------------------------------------------------------
		// Creature�� ���??
		//------------------------------------------------------
		if ( g_pZone->RemoveCreature( objectID ) )
		{
			DEBUG_ADD_FORMAT("Remove Creature OK. ID=%d", objectID);
		}
		//------------------------------------------------------
		// Item�� ���??
		//------------------------------------------------------
		else if ( g_pZone->RemoveItem( objectID ) )
		{			
			DEBUG_ADD_FORMAT("Remove Item OK. ID=%d", objectID);
		}
		//------------------------------------------------------
		// ����???
		//------------------------------------------------------
		else
		{
			DEBUG_ADD_FORMAT("[Error] Can't Remove Object. ID=%d", objectID);
		}
	}

#endif

	__END_CATCH
}
