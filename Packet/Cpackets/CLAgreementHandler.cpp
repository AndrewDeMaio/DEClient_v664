//////////////////////////////////////////////////////////////////////////////
// Filename    : CLAgreementHandler.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLAgreement.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////

// �� ��Ŷ�� Ŭ���̾�Ʈ�� ���̵�� �н����带 ��ȣȭ�ؼ� 

// �α��� ������ �����Ѵ�. �α��� ������ �� ��Ŷ�� �޾Ƽ�

// �÷��̾��� ���̵�� �н����尡 ��Ȯ���� DB�κ��� �о

// ���� ��, �α����� ���� ���θ� �����Ѵ�.

//////////////////////////////////////////////////////////////////////////////

void CLAgreementHandler::execute (CLAgreement* pPacket , Player* pPlayer)


{

	__BEGIN_TRY __BEGIN_DEBUG_EX

		

#ifdef __LOGIN_SERVER__

#ifdef __NETMARBLE_SERVER__



	Assert(pPacket != NULL);

	Assert(pPlayer != NULL);



	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	Assert( pLoginPlayer != NULL );



	if ( pLoginPlayer->isAgree() )

	{

		Statement*   pStmt        = NULL;



		BEGIN_DB

		{

			//----------------------------------------------------------------------

			// �ݸ��� ��� �̵��� ����Ʈ���� ����

			//----------------------------------------------------------------------

			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery( "DELETE FROM PrivateAgreementRemain WHERE PlayerID = '%s'", pLoginPlayer->getID().c_str() );



			// ���� �ܰ�� ������ �� �ְ� ����

			pLoginPlayer->setAgree( true );



			SAFE_DELETE(pStmt);

		}

		END_DB(pStmt)

	}



#endif
#endif



	__END_DEBUG_EX __END_CATCH

}
#endif