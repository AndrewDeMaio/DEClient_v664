//////////////////////////////////////////////////////////////////////
//
// Filename    : GCPhoneConnectedHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCPhoneConnected.h"
#include "UserInformation.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCPhoneConnectedHandler::execute ( GCPhoneConnected * pPacket , Player * pPlayer )
{
	__BEGIN_TRY


	int pcsNumber = pPacket->getPhoneNumber();
	int slot = pPacket->getSlotID();

	// ��ȣ�� ������ �д�.
	g_pUserInformation->OtherPCSNumber[ slot ] = pcsNumber;
	g_pUserInformation->PCSUserName[ slot ] = pPacket->getName().c_str();

	// PCS�� ����.
	char pName[128];
	strcpy(pName, pPacket->getName().c_str());

//	UI_OnLinePCS(pName, pcsNumber);

	__END_CATCH
}
