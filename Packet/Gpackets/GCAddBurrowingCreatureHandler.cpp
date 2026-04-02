//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddBurrowingCreatureHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddBurrowingCreature.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddBurrowingCreatureHandler::execute ( GCAddBurrowingCreature * pPacket , Player * pPlayer )
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
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreature;

			pCreature->SetZone( g_pZone );

			// ������ �� �����ϰŴϱ� �������.
			pCreature->SetCreatureType( CREATURETYPE_VAMPIRE_MALE1 );	


			pCreature->SetName( pPacket->getName().c_str() );

			
			pCreature->SetUndergroundCreature();
			pCreature->SetID(pPacket->getObjectID());
			
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( DIRECTION_DOWN );
			pCreature->SetCurrentDirection( DIRECTION_DOWN );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetGuildNumber( -1 );

			pCreature->SetStatus( MODIFY_MAX_HP, 100 );
			pCreature->SetStatus( MODIFY_CURRENT_HP, 100 );

			//si.getName()
			// ���� ����

			

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
			}
		}
		else
		{
			// �̹� �ִٸ�.. Underground Creature�� �����.
			pCreature->SetUndergroundCreature();

			// �̸� �ٽ� ���� - -;
			pCreature->SetName( pPacket->getName().c_str() );

			// ��ǥ ����
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );

			pCreature->SetGuildNumber( -1 );
		}
	}

#endif

	__END_CATCH
}
