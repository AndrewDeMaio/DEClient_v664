//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGetDamageHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCGetDamage.h"
#include "ClientDef.h"
#include "MActionInfoTable.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCGetDamageHandler::execute ( GCGetDamage * pGCGetDamage , Player * pPlayer )
{
	__BEGIN_TRY

	// message

	//------------------------------------------------------
	// Player�� Damage�� �޾�����..
	//------------------------------------------------------
	if (pGCGetDamage->getObjectID()==g_pPlayer->GetID())
	{
		g_pPlayer->PacketSpecialActionResult( 
					SKILL_ATTACK_MELEE + (*g_pActionInfoTable).GetMinResultActionInfo(),
					g_pPlayer->GetID(),
					g_pPlayer->GetX(),
					g_pPlayer->GetY()
			);
	}
	else
	{
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
			MCreature* pCreature = g_pZone->GetCreature( pGCGetDamage->getObjectID() );

			// Creature���� Damage ����
			if (pCreature != NULL)
			{
				// SKILL_ATTACK_MELEE�� ���� ����� ǥ�����ش�.
				pCreature->PacketSpecialActionResult( 
								SKILL_ATTACK_MELEE + (*g_pActionInfoTable).GetMinResultActionInfo(),
								pCreature->GetID(),
								pCreature->GetX(),
								pCreature->GetY()
				);
				
			}
		}
	}

	__END_CATCH
}
