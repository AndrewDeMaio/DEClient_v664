
//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAuthKeyHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAuthKey.h"
#ifdef __GAME_CLIENT__ 
	#include "Client.h"
	#include "nProtect.h"
#endif
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////

void GCAuthKeyHandler::execute ( GCAuthKey * pPacket , Player * pPlayer )
{
	__BEGIN_TRY 
//		__BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__ 

#if !defined(OUTPUT_DEBUG) && !defined(_DEBUG) && !defined(__DEBUG_OUTPUT__)
	Set_Auth(pPacket->getKey());
//	MessageBox(g_hWnd, "GCAuthKeyHandler����1", "Warning", MB_OK);
#endif
//	MessageBox(g_hWnd, "GCAuthKeyHandler����2", "Warning", MB_OK);
//#ifdef __NPROTECT__
//	//cout << pPacket->toString() << endl;
//	Set_Auth(pPacket->getKey());
//	MessageBox(g_hWnd, "GCAuthKeyHandler����1", "Warning", MB_OK);
//#endif
//	MessageBox(g_hWnd, "GCAuthKeyHandler����2", "Warning", MB_OK);
#endif

//	__END_DEBUG_EX
	__END_CATCH
}
