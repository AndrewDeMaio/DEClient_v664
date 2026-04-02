//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToCodeSheetHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////
/*

// �� �������� �� �ٸ� �����ۿ� �ִ´�.
 [Client]                                               [Server]
           -- CGAddItemToCodeSheet
              (mouseItem_ObjectID, invenX, invenY) 
			  =(���콺�� ����ִ� ��, upgrade�� item XY) -->

            <-- GCAddItemToCodeSheetVerify(����ڵ�, ���ð�) ---
   
//-------------+---------------------------------------------
// ��� packet | client ó��
//-------------+---------------------------------------------
// �Ұ� packet | �Ұ� message ���
// ���� packet | ���� message ���, �� ����, [������ ����]
// ���� packet | �� ����, option����
//-------------+---------------------------------------------
*/

#include "Client_PCH.h"
#include "CGAddItemToCodeSheet.h"

#ifdef __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddItemToCodeSheetHandler::execute (CGAddItemToCodeSheet* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

#endif	// __GAME_SERVER__
