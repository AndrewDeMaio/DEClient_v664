//--------------------------------------------------------------------------------
//
// Filename    : GCRemoveCorpseHeadHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCRemoveCorpseHead.h"
#include "ClientDef.h"

#ifdef __GAME_CLIENT__
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCRemoveCorpseHeadHandler::execute ( GCRemoveCorpseHead * pPacket , Player * pPlayer )
{
	__BEGIN_TRY 


	int objectID = pPacket->getObjectID();

	// Creature�� �����ؼ� MCorpse�� �߰��ؼ� Zone�� �ִ´�.
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
		//----------------------------------------	
		// �̹� �ִ� Creature�ΰ�?
		//----------------------------------------	
		MCreature* pCreature = g_pZone->GetCreature( objectID );
		
		//---------------------------------------------------------
		//
		//					Zone�� ���� ���
		//
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			// �̹� ��ü�� �ֳ�?
			MItem* pItem = g_pZone->GetItem( objectID );

			//---------------------------------------------------------
			// ��ü�� ������ ������
			//---------------------------------------------------------
			if (pItem==NULL)
			{
				// �׷� �������� ����.
				DEBUG_ADD("[Error] There is no such Item ID");
			}
			//---------------------------------------------------------
			// ��ü�� ������ �Ӹ��� ���ش�.
			//---------------------------------------------------------
			else if (pItem->GetItemClass()==ITEM_CLASS_CORPSE)
			{
				MCreature* pCreature = ((MCorpse*)pItem)->GetCreature();

				pCreature->RemoveHead();
			}
			else
			{
				// �������� �ִµ� ��ü�� �ƴ� ���
				DEBUG_ADD_FORMAT("[Error] It's not Corpse. id=%d", objectID);
			}
		}
		//---------------------------------------------------------
		// ���� ���� ������ ���.. �Ӹ� ���ֱ�
		//---------------------------------------------------------
		else
		{
			pCreature->RemoveHead();			
		}
	}


	__END_CATCH
}
