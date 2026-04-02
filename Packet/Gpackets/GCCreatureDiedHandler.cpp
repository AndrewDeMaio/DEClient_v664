//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCreatureDiedHandler.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCCreatureDied.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCCreatureDiedHandler::execute ( GCCreatureDied * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	// message

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
		int creatureID = pPacket->getObjectID();

		MCreature* pCreature = g_pZone->GetCreature(creatureID);

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			// message
			DEBUG_ADD_FORMAT("[Error] Not Exist Creature ID=%d", pPacket->getObjectID());
		}
		else
		{
			//---------------------------------------------------------
			// Creature�� �׿��� �Ѵ�.
			//---------------------------------------------------------
			//pCreature->SetDead();

			if (pCreature->IsAlive())
			{
				pCreature->SetDead();
			}
			else
			{
			//	pCreature->SetCorpse();
			}

			g_pZone->AddCorpseFromCreature( creatureID );
		}
	}

#endif

	__END_CATCH
}
