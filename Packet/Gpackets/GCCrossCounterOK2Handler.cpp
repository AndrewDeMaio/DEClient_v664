//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCrossCounterOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCCrossCounterOK2.h"
#include "ClientDef.h"
#include "MFakeCreature.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCrossCounterOK2Handler::execute ( GCCrossCounterOK2 * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	// ���� objectID���� �´´�.
	//------------------------------------------------------------------
	// ���°��� �ٲ۴�.
	//------------------------------------------------------------------
	AffectModifyInfo(g_pPlayer, pPacket);


	//int delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

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

		SkillCrossCounter( pUserCreature, g_pPlayer, pPacket->getSkillType() );
		
	}	

#endif

	__END_CATCH
}
