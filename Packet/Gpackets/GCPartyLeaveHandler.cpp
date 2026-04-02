//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyLeaveHandler.cpp
// Written By  : �輺��
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCPartyLeave.h"
#include "MGameStringTable.h"
#include "MParty.h"
#include "UIDialog.h"
#include "UserInformation.h"
#include "ClientDef.h"
#include "UIFunction.h"

extern CMessageArray*		g_pGameMessage;

void GCPartyLeaveHandler::execute (GCPartyLeave * pPacket , Player * pPlayer)
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	if (g_pZone==NULL
		|| g_pPlayer==NULL
		|| g_pUserInformation==NULL
		|| g_pParty==NULL
		|| g_pGameMessage==NULL)
	{
		DEBUG_ADD("GCPartyLeaveHandler Failed");
		return;
	}

	
	const char* pExpeller = pPacket->getExpeller().c_str();	// �߹���
	const char* pExpellee = pPacket->getExpellee().c_str(); // �߹�� ��

	char str[256];
			
	bool bRemovePartyCheck = false;
	
	//-------------------------------------------------------------------
	// ���� Ȯ��
	//-------------------------------------------------------------------
	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_PARTY_LEAVE)
	{
		g_pPlayer->SetWaitVerifyNULL();
	}

	//-------------------------------------------------------------------
	// ���� ������ ���� ���
	//-------------------------------------------------------------------
	if (pExpeller==NULL || pExpeller[0]==NULL || !strcmp(pExpeller, pExpellee))
	{
		//----------------------------------------------------------
		// ���� ���� ���
		//----------------------------------------------------------
		if (g_pUserInformation->CharacterID==pExpellee)
		{
			g_pParty->UnSetPlayerParty();
			g_pParty->Release();	// ���� party�� ��ü�Ǵ� ���̴�..			

			g_pGameMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_REMOVE_PARTY_MYSELF].GetString() );
			//g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_REMOVE_PARTY_MYSELF].GetString() );

			UI_CloseParty();
		}
		//----------------------------------------------------------
		// ���� ���� ���
		//----------------------------------------------------------
		else if (g_pParty->RemoveMember( pExpellee ))
		{
			sprintf(str, 
					(*g_pGameStringTable)[STRING_MESSAGE_REMOVE_PARTY_HIMSELF].GetString(), 
					pExpellee);		
			
			//g_pUIDialog->PopupFreeMessageDlg( str );
			g_pGameMessage->Add( str );

			bRemovePartyCheck = true;
			// 2005.08.04 BloodBurst ��Ƽ ������ ó�� 
			//UI_SetBloodBurstSetGage() ;
		}
	}
	//-------------------------------------------------------------------
	// ���� ������ �ѾƳ� ���
	//-------------------------------------------------------------------
	else
	{
		//-------------------------------------------------------------------
		// ���� pExpellee�� �ѾƳ´�.
		//-------------------------------------------------------------------
		if (g_pUserInformation->CharacterID==pExpeller)
		{		
			if (g_pParty->RemoveMember( pExpellee ))
			{
				sprintf(str, 
						(*g_pGameStringTable)[STRING_MESSAGE_KICK_PARTY_MEMBER_OK].GetString(), 
						pExpellee);

				//g_pUIDialog->PopupFreeMessageDlg( str );
				g_pGameMessage->Add( str );
				// 2005.08.04 BloodBurst ��Ƽ ������ ó�� 
				//UI_SetBloodBurstSetGage() ;
			}

			bRemovePartyCheck = true;
		}
		//-------------------------------------------------------------------
		// ���� pExpeller���� �Ѱܳ���.
		//-------------------------------------------------------------------
		else if (g_pUserInformation->CharacterID==pExpellee)
		{
			g_pParty->UnSetPlayerParty();
			g_pParty->Release();	// ���� party�� ��ü�Ǵ� ���̴�..			

			sprintf(str, 
						(*g_pGameStringTable)[STRING_MESSAGE_KICKED_FROM_PARTY].GetString(), 
						pExpeller);		
			
			//g_pUIDialog->PopupFreeMessageDlg( str );
			g_pGameMessage->Add( str );

			bRemovePartyCheck = true;
		}
		//-------------------------------------------------------------------
		// pExpeller�� pExpeller�� �ѾƳ´�.
		//-------------------------------------------------------------------
		else if (g_pParty->RemoveMember( pExpellee ))
		{
			sprintf(str, 
					(*g_pGameStringTable)[STRING_MESSAGE_KICK_PARTY_MEMBER].GetString(), 
					pExpeller, pExpellee);

			//g_pUIDialog->PopupFreeMessageDlg( str );
			g_pGameMessage->Add( str );
			// 2005.08.04 BloodBurst ��Ƽ ������ ó�� 
			//UI_SetBloodBurstSetGage() ;
		}
	}

	
	//--------------------------------------------------
	// ��Ƽ ��ü�ΰ�?
	//--------------------------------------------------
	if (bRemovePartyCheck && g_pParty->GetSize()==0)
	{		
		UI_CloseParty();

		// �޽����� ������ָ� �ǰ���..
		//g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_REMOVE_PARTY].GetString() );		
		g_pGameMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_REMOVE_PARTY].GetString() );
	}

#endif

	__END_CATCH
}
