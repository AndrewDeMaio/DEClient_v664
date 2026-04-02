//////////////////////////////////////////////////////////////////////
//
// Filename    : GCPhoneDisconnectedHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCPhoneDisconnected.h"
#include "UserInformation.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCPhoneDisconnectedHandler::execute ( GCPhoneDisconnected * pPacket , Player * pPlayer )
{
	__BEGIN_TRY


	//------------------------------------------------------------------
	// ������ ���� slot üũ�Ѵ�.
	//------------------------------------------------------------------
	int slot = pPacket->getSlotID();
	g_pUserInformation->OtherPCSNumber[ slot ] = 0;
	g_pUserInformation->PCSUserName[ slot ].Release();

	//------------------------------------------------------------------
	// PCS ���� ����
	//------------------------------------------------------------------
	//UI_AcquireQuitPCSOnlineModeMessage();
//	UI_DisconnectPCS( slot );

	__END_CATCH
}
