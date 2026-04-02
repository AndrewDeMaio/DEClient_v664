//////////////////////////////////////////////////////////////////////
//
// Filename    : GCPhoneSayHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCPhoneSay.h"
#include "UserInformation.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCPhoneSayHandler::execute ( GCPhoneSay * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	

	int slot = pPacket->getSlotID();

	char message[128];
	sprintf(message, "[%s] %s", 
						g_pUserInformation->PCSUserName[ slot ].GetString(), 
						pPacket->getMessage().c_str());

	//--------------------------------------------------
	// �� ����
	//--------------------------------------------------
	//g_pChatManager->RemoveCurse( message );

	//------------------------------------------------------
	// Ư�� slot�� message�� �߰����Ѿ� �Ѵ�.
	//------------------------------------------------------
	//UI_AddChatToHistory( message );


#endif

	__END_CATCH
}
