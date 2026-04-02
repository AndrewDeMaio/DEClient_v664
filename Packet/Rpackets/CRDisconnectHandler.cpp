//////////////////////////////////////////////////////////////////////
//
// Filename    : CRDisconnectHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "client_PCH.h"
#include "CRDisconnect.h"
#include "RequestServerPlayer.h"
#include "RequestFunction.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CRDisconnectHandler::execute ( CRDisconnect * pPacket , Player * pPlayer )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	RequestServerPlayer* pRequestServerPlayer = dynamic_cast<RequestServerPlayer*>( pPlayer );

	if (pRequestServerPlayer!=NULL)
	{
		// ���ӵ� ����ڸ� �������� ��Ų��.
		RequestDisconnect( pRequestServerPlayer->getName().c_str() );
	}

#endif

	__END_CATCH
}
