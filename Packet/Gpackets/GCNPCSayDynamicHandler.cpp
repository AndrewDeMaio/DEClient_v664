//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCSayDynamicHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCNPCSayDynamic.h"
#include "ClientDef.h"
#include "MChatManager.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCNPCSayDynamicHandler::execute(GCNPCSayDynamic* pPacket, Player* pPlayer)
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

		//------------------------------------------------------
		// Zone�� ���� �������� ���� ���
		//------------------------------------------------------
		if (g_pZone == NULL)
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
			MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

			if (pCreature == NULL)
			{
				// �׷� ĳ���Ͱ� ������ �����Ѵ�.
			}
			else
			{
				//-------------------------------------------------
				// �������� ��ȭ
				//-------------------------------------------------
				if (g_pChatManager->IsAcceptID(pCreature->GetName()))
				{
					// ä��~~
					char str[256];
					strcpy(str, pPacket->getMessage().c_str());

					pCreature->SetChatString(str);
				}
				//-------------------------------------------------
				// ��ȭ �źη� �����Ǿ� �ִٸ� ��¾��Ѵ�.
				//-------------------------------------------------
				else
				{
					//pCreature->SetChatString("......");
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
