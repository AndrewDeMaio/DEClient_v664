//--------------------------------------------------------------------------------
//
// Filename    : LCDeletePCOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "client_PCH.h"
#include "LCDeletePCOK.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"
#endif

#include "ClientDef.h"
#include "UIFunction.h"

#ifdef __GAME_CLIENT__
	#include "UserInformation.h"

	extern int g_Dimension;

//--------------------------------------------------------------------------------
// The client keys a character's local files by name alone, and the server lets a
// deleted character's name be reused, so a new character with that name would
// load the old skill hotkeys, window layout and cached mail. Remove them once the
// server has confirmed the delete. The names match the ones VS_UI_Game.cpp reads.
//--------------------------------------------------------------------------------
static void DeleteCharacterLocalFiles(const char* name)
{
	if (name == NULL || name[0] == '\0' || strpbrk(name, "\\/:*?\"<>|.") != NULL)
		return;

	const int world = g_pUserInformation->WorldID;
	char path[MAX_PATH];

	sprintf_s(path, "UserSet\\%s.set", name);
	DeleteFile(path);
	sprintf_s(path, "UserSet\\%s-%d.set", name, world);
	DeleteFile(path);
	sprintf_s(path, "UserSet\\%s-%d-%d.set", name, g_Dimension, world);
	DeleteFile(path);
	sprintf_s(path, "UserSet\\%s-%d-%d.mail", name, g_Dimension, world);
	DeleteFile(path);
}
#endif

//--------------------------------------------------------------------------------
//
// PC �� ���������� �����ߴٴ� ���̴�.
//
//--------------------------------------------------------------------------------
void LCDeletePCOKHandler::execute ( LCDeletePCOK * pPacket , Player * pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	#if __LINUX__

		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		cout << "                            " << endl;
		cout << "+--------------------------+" << endl;
		cout << "| PC deleted successfully! |" << endl;
		cout << "+--------------------------+" << endl;
		cout << "                            " << endl;

		// �ٽ� PC LIST �� �޾ƿ;� �Ѵ�.
		CLGetPCList clGetPCList;
		pClientPlayer->sendPacket( &clGetPCList );	

		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

	// __WINDOWS__ is never defined anywhere in this tree, and #if treats an
	// unknown identifier as 0 -- so with __LINUX__ also undefined, BOTH branches
	// compiled out and this handler was an empty function. The client therefore
	// never sent CLGetPCList after a delete, sat in MODE_WAIT_PCLIST until
	// CWaitPacketUpdate::Update hit its timeout, and dropped to the main menu.
	// _WIN32 is defined by MSVC for both 32- and 64-bit targets.
	#elif defined(_WIN32)

		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		// the list is only refreshed after this, so the slot still names the deleted character
		if (g_pUserInformation->Slot >= 0 && g_pUserInformation->Slot < 3)
		{
			DeleteCharacterLocalFiles(g_pUserInformation->Character[g_pUserInformation->Slot].GetString());
		}

		// delete����
		UI_DeleteCharacterOK();

		// �ٽ� PC LIST�� �޾ƾ� �Ѵ�.
		CLGetPCList clGetPCList;
		pClientPlayer->sendPacket( &clGetPCList );	

		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

		// PC List�� ��ٸ��� mode
		g_ModeNext = MODE_WAIT_PCLIST;

	#endif
	
#endif

	__END_CATCH
}
