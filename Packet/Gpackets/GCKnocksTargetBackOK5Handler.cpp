//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCKnocksTargetBackOK5.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5Handler::execute ( GCKnocksTargetBackOK5 * pPacket , Player * pPlayer )
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
		
		return;
	}	

	//------------------------------------------------------
	// ����� �Ǵ� creature�� ��´�.
	//------------------------------------------------------
	MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );
	MCreature* pTargetCreature = g_pZone->GetCreature( pPacket->getTargetObjectID() );
	
	if (pCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : ID=%d, Skill=%d", pPacket->getObjectID(), pPacket->getSkillType());				
		
		return;
	}

	if (pTargetCreature==NULL)
	{
		// �׷� creature�� ���� ���
		DEBUG_ADD_FORMAT("There's no such creature : TargetID=%d, Skill=%d", pPacket->getTargetObjectID(), pPacket->getSkillType());
		
		return;
	}


	int skillType = pPacket->getSkillType();	//pCreature->GetBasicActionInfo()	

	if( skillType >= g_pActionInfoTable->GetSize() )
	{
		DEBUG_ADD_FORMAT("[GCKnocksTargetBackOK5] SkillType Error %d", skillType );
		return;
	}

	//------------------------------------------------------
	// �������¹���(direction)����..
	//------------------------------------------------------	
	unsigned short x = pPacket->getX();
	unsigned short y = pPacket->getY();

	// �̵��� ���� ��ǥ�� �´�.
	//MCreature::GetPositionToDirection(x, y, pPacket->getDir());

	//------------------------------------------------------
	// ���(�ٸ� ĳ���Ͱ� �´� ���)�� �����Ѵ�.
	//------------------------------------------------------
	MActionResult* pResult = new MActionResult;
	pResult->Add( new MActionResultNodeActionInfo( 
								skillType, // �� ����									
								pPacket->getObjectID(), 
								pPacket->getTargetObjectID(),
								pTargetCreature->GetX(),
								pTargetCreature->GetY()
								 ) 
				);

	// target object�� ��ǥ�� �ٲ�
	pResult->Add( new MActionResultNodeChangePosition( 
								pPacket->getTargetObjectID(),
								x, y)
				);
								
	//------------------------------------------------------
	// �ൿ�ϴ� Creature�� TargetCreature�� �ٶ󺸵��� �Ѵ�.
	//------------------------------------------------------
	pCreature->SetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );

	//------------------------------------------------------
	// Creature�� �ൿ�� ���ϵ��� �Ѵ�.
	//------------------------------------------------------
	pCreature->PacketSpecialActionToOther(
					// �� ����
					skillType	, 
					pPacket->getTargetObjectID(), 
					pResult
	);

	//------------------------------------------------------
	// ����ȭ ���� ������..
	// ���� ��ġ�� �ٷ� �����Ѵ�.
	//------------------------------------------------------
	pTargetCreature->SetServerPosition( x, y );

#endif

	__END_CATCH
}
