//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCSayHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCNPCSay.h"
#include "ClientDef.h"
#include "MChatManager.h"
#include "MNPCScriptTable.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCNPCSayHandler::execute ( GCNPCSay * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
		// Debug Message

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
		//---------------------------------------------------------------
		// ĳ���� �Ӹ� ���� ä���� ����.
		//---------------------------------------------------------------
		MCreature*	pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature==NULL)
		{
			// �׷� ĳ���Ͱ� ������ �����Ѵ�.
		}
		else
		{		
			//-------------------------------------------------
			// �������� ��ȭ
			//-------------------------------------------------
			if (g_pChatManager->IsAcceptID( pCreature->GetName() ))
			{
				int scriptID = pPacket->getScriptID();
				int subjectID = pPacket->getSubjectID();

				// ä��~~
				char str[256];
				const char* pString = g_pNPCScriptTable->GetSubject( scriptID, subjectID );

				if (pString!=NULL)
				{
					strcpy(str, pString );
				
					pCreature->SetChatString( str );
				}
			}
			//-------------------------------------------------
			// ��ȭ �źη� �����Ǿ� �ִٸ� ��¾��Ѵ�.
			//-------------------------------------------------
			else
			{
				pCreature->SetChatString( "......" );
			}

			// history�� �߰�
			//char temp[128];
			//sprintf(temp, "%s> %s", pCreature->GetName(), str);
			//UI_AddChatToHistory( temp );
		}
	}
#endif

	__END_CATCH
}
