//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCAskVariableHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "MNPCScriptTable.h"
#include "GCNPCAskVariable.h"

#include "ClientDef.h"
#include "TalkBox.h"
#include "UIDialog.h"
#include "SystemAvailabilities.h"


//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCNPCAskVariableHandler::execute ( GCNPCAskVariable * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	
	if (g_pPlayer==NULL
		|| g_pZone==NULL
		|| g_pNPCScriptTable==NULL
		|| g_pUIDialog==NULL
		|| g_pPCTalkBox==NULL)
	{
		DEBUG_ADD("[Error] Some Object is NULL");
		return;
	}


	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK)
	{
		g_pPlayer->SetWaitVerifyNULL();
		
		// NPC
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature!=NULL)
		{			
			//---------------------------------------------------
			// g_PCTalkBox�� �߰��ϸ� �ȴ�.
			//---------------------------------------------------
			// ������ �ִ��� ����
			g_pPCTalkBox->Release();

			DEBUG_ADD("TalkBoxRelease - GCNPCAskVariableHandler");

			//---------------------------------------------------
			// normal
			//---------------------------------------------------
			g_pPCTalkBox->SetType( PCTalkBox::NORMAL );

			
			int scriptID = pPacket->getScriptID();

			//---------------------------------------------------
			// PC Talk Box�� ���� ����
			//---------------------------------------------------
			// SetContent��� �̸��� �Ǿ�������.. Subject�̴�. - -;
			std::string title;
			g_pNPCScriptTable->GetSubjectParameter(scriptID, 0, pPacket->getScriptParameters(), title);
			g_pPCTalkBox->SetContent( title.c_str() );
			g_pPCTalkBox->SetNPCID( pPacket->getObjectID() );
			g_pPCTalkBox->SetCreatureType( pCreature->GetCreatureType() );
			g_pPCTalkBox->SetScriptID( scriptID );

			DEBUG_ADD("SetScript - GCNPCAskVariableHandler");

			//---------------------------------------------------
			// �� std::string �߰�
			//---------------------------------------------------
			int contentSize = g_pNPCScriptTable->GetContentSize( scriptID );

			g_pPCTalkBox->m_AnswerIDMap.clear();
			
			for (int i=0; i<contentSize; i++)
			{
				// g_PCTalkBox�� �߰�
				std::string str;
				g_pNPCScriptTable->GetContentParameter( scriptID, i ,pPacket->getScriptParameters(),str);
				if( g_pSystemAvailableManager->ScriptFiltering( scriptID, i ) )
				{
					g_pPCTalkBox->AddString( str.c_str() );
					g_pPCTalkBox->m_AnswerIDMap.push_back( i );
				}
				DEBUG_ADD(str.c_str());				
			}
			DEBUG_ADD("SetContent - GCNPCAskVariableHandler");			
			g_pUIDialog->PopupPCTalkDlg();
		}

		//---------------------------------------------------
		// Dialog�� ����.
		//---------------------------------------------------
		//POINT point = ConvertPositionMapToScreen(pCreature->GetX(), pCreature->GetY());

		//point.y -= pCreature->GetHeight();

		//g_pUIDialog->PopupPCTalkDlg(point.x, point.y - size*20-100);							
	}
	else
	{
		DEBUG_ADD("[Error] WaitVerifyMode is Not WAIT_VERIFY_NPC_ASK");
	}
#endif

	__END_CATCH
}
