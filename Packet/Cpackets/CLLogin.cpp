//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "CLLogin.h"
#include "UserInformation.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CLLogin::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	BYTE szID;

	iStream.read( szID );

	if ( szID == 0 )
		throw InvalidProtocolException("szID == 0");

	if ( szID > 30 )
		throw InvalidProtocolException("too large ID length");

	iStream.read( m_ID , szID );

	BYTE szPassword;

	iStream.read( szPassword );

	if ( szPassword == 0 )
		throw InvalidProtocolException("szPassword == 0");

	if ( szPassword > 32 )
		throw InvalidProtocolException("too large password length");

	iStream.read( m_Password , szPassword );

	iStream.read( (char*)m_MacAddress , 6 );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CLLogin::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

#ifdef __DESIGNED_JAPAN
	if( g_pUserInformation == NULL || g_pUserInformation->IsNetmarbleJapan || !g_pUserInformation->IsNetmarble )
#else
	if( g_pUserInformation == NULL || !g_pUserInformation->IsNetmarbleLogin || !g_pUserInformation->IsNetmarble )
#endif
	{
		BYTE szID = (BYTE)m_ID.size();

		if ( szID == 0 )
			throw InvalidProtocolException("empty ID");

		if ( szID > 30 )
			throw InvalidProtocolException("too large ID length");

		oStream.write( szID );

		oStream.write( m_ID );

		BYTE szPassword = (BYTE)m_Password.size();

		if ( szPassword == 0 )
			throw InvalidProtocolException("szPassword == 0");
		if ( szPassword > 32 )
			throw InvalidProtocolException("too large password length");

		oStream.write( szPassword );

		oStream.write( m_Password );

		oStream.write( (char*)m_MacAddress, 6*sizeof(BYTE) );
		
	//	BYTE loginMode = 0;
		oStream.write( m_LoginMode );
	}
	else
	{
		int	szID = m_ID.size();

		if ( szID == 0 )
			throw InvalidProtocolException("empty ID");
		if ( szID > 2048 )
			throw InvalidProtocolException("too large ID length");

		oStream.write( szID );
		oStream.write( m_ID );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CLLogin::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CLLoginHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CLLogin::toString () const
	{
		char szTemp[10];

		StringStream msg;

		msg << "CLLogin("
			<< "ID:" << m_ID 
			<< ",Password:" << m_Password 
			<< ",MacAddress:"
			<< itoa( m_MacAddress[0], szTemp, 16 )
			<< itoa( m_MacAddress[1], szTemp, 16 )
			<< itoa( m_MacAddress[2], szTemp, 16 )
			<< itoa( m_MacAddress[3], szTemp, 16 )
			<< itoa( m_MacAddress[4], szTemp, 16 )
			<< itoa( m_MacAddress[5], szTemp, 16 )
			<< ")";

		return msg.toString();
	}

#endif

size_t CLLogin::getPacketSize () const
{
	if( g_pUserInformation == NULL || !g_pUserInformation->IsNetmarble )
	{
		return szBYTE + m_ID.size() + szBYTE + m_Password.size() + 6 + szBYTE;
	}
	
	return szint + m_ID.size();
}