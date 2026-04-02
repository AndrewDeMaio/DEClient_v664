//////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItemHandler.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGBuyStoreItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// �÷��̾ ���ϴ� ������ �Ĵ� NPC�� �� �������� �ִ���
// Ȯ���ϰ�, �Ϲ� �����۰� ���� ����Ŭ ó���κ����� �б��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGBuyStoreItemHandler::execute (CGBuyStoreItem* pPacket , Player* pPlayer)
{
	__BEGIN_TRY 
	//__BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

#endif

	//__END_DEBUG_EX 
	__END_CATCH
}


  