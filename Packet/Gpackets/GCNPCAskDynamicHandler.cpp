//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCAskDynamicHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCNPCAskDynamic.h"
#include "ClientDef.h"
#include "TalkBox.h"
#include "UIDialog.h"
#include "SystemAvailabilities.h"


//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCNPCAskDynamicHandler::execute ( GCNPCAskDynamic * pPacket , Player * pPlayer )
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
		if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK)
		{
			g_pPlayer->SetWaitVerifyNULL();

			int size = pPacket->getContentsCount();

			if (size==0)
			{
				DEBUG_ADD_FORMAT("[Error] No Answer String.. ScriptID=%d", (int)pPacket->getScriptID());			
			}
			else
			{
				// NPC
				MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

				if (pCreature==NULL)
				{
					// �׷� ĳ���Ͱ� ������ �����Ѵ�.
				}
				else
				{
					//---------------------------------------------------
					// g_PCTalkBox�� �߰��ϸ� �ȴ�.
					//---------------------------------------------------
					// ������ �ִ��� ����
					g_pPCTalkBox->Release();

					//---------------------------------------------------
					// normal
					//---------------------------------------------------
					g_pPCTalkBox->SetType( PCTalkBox::NORMAL );

					//---------------------------------------------------
					// PC Talk Box�� ���� ����
					//---------------------------------------------------
					g_pPCTalkBox->SetContent( pPacket->getSubject().c_str() );
					g_pPCTalkBox->SetNPCID( pPacket->getObjectID() );
					g_pPCTalkBox->SetCreatureType( pCreature->GetCreatureType() );
					g_pPCTalkBox->SetScriptID( pPacket->getScriptID() );

					//---------------------------------------------------
					// �� std::string �߰�
					//---------------------------------------------------

					g_pPCTalkBox->m_AnswerIDMap.clear();
					for (int i=0; i<size; i++)
					{
						// g_PCTalkBox�� �߰�
						if( g_pSystemAvailableManager->ScriptFiltering( pPacket->getScriptID(), i ) )
						{
							g_pPCTalkBox->AddString( pPacket->popContent().c_str() );
							g_pPCTalkBox->m_AnswerIDMap.push_back( i );
						}
					}
					
					g_pUIDialog->PopupPCTalkDlg();
				}

				//---------------------------------------------------
				// Dialog�� ����.
				//---------------------------------------------------
				//POINT point = ConvertPositionMapToScreen(pCreature->GetX(), pCreature->GetY());

				//point.y -= pCreature->GetHeight();

				//g_pUIDialog->PopupPCTalkDlg(point.x, point.y - size*20-100);				
			}
		}
		else
		{
			DEBUG_ADD("[Error] WaitVerifyMode is Not WAIT_VERIFY_NPC_ASK");
		}
	}

#endif

	__END_CATCH
}
