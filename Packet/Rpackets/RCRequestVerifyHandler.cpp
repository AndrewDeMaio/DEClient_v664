//////////////////////////////////////////////////////////////////////
//
// Filename    : RCRequestVerifyHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "RCRequestVerify.h"
#include "MGameStringTable.h"
#include "RequestClientPlayer.h"
#include "RequestUserManager.h"
#include "ProfileManager.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void RCRequestVerifyHandler::execute ( RCRequestVerify * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

	RequestClientPlayer* pRequestClientPlayer = dynamic_cast<RequestClientPlayer*>( pPlayer );

	if (pRequestClientPlayer!=NULL
		&& g_pRequestUserManager!=NULL
		&& g_pGameStringTable!=NULL)
	{
		switch (pPacket->getCode())
		{
			//-----------------------------------------------------------------
			// �ӼӸ��� ���޵��� ���� ���
			//-----------------------------------------------------------------
			case REQUEST_VERIFY_WHISPER_FAILED :
			{
				// info = 5
				UI_AddChatToHistory( (*g_pGameStringTable)[STRING_MESSAGE_WHISPER_FAILED].GetString(), NULL, 5, RGB(255, 255, 255) );

				// �߸��� IP�ų�..
				// �� IP�� ����� �ٸ� ����ڷ� �����߰ų� �ؼ�...
				// �� �̻� ������� �����̹Ƿ� �����Ѵ�.
				g_pRequestUserManager->RemoveRequestUser( pRequestClientPlayer->getRequestServerName().c_str() );
			}
			break;

			//-----------------------------------------------------------------
			// �߸��� ����ڿ��� Profile�� ��û�� ���
			//-----------------------------------------------------------------
			case REQUEST_VERIFY_PROFILE_WRONG_USER :
			{
				// �߸��� IP�ų�..
				// �� IP�� ����� �ٸ� ����ڷ� �����߰ų� �ؼ�...
				// �� �̻� ������� �����̹Ƿ� �����Ѵ�.
				g_pRequestUserManager->RemoveRequestUser( pRequestClientPlayer->getRequestServerName().c_str() );
			}
			break;

			//-----------------------------------------------------------------
			// Profile�� �ƿ� ���� ���
			//-----------------------------------------------------------------
			case REQUEST_VERIFY_PROFILE_NOT_EXIST :
			{
				g_pProfileManager->AddProfileNULL( pRequestClientPlayer->getRequestServerName().c_str() );
			}
			break;

			//-----------------------------------------------------------------
			// Profile �� ���´ٰ� ���ƿ� ���
			//-----------------------------------------------------------------
			case REQUEST_VERIFY_PROFILE_DONE :
			{
				//pRequestClientPlayer->disconnect( UNDISCONNECTED );
				throw DisconnectException("Profile Done");
			}
			break;
		}	
	}

	__END_CATCH
}
