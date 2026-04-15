//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLQueryPlayerID.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CLQueryPlayerID.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CLQueryPlayerID::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read player id
	//--------------------------------------------------
	BYTE szPlayerID;

	iStream.read( szPlayerID );

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long PlayerID length");

	iStream.read( m_PlayerID , szPlayerID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CLQueryPlayerID::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write player id
	//--------------------------------------------------
	size_t szPlayerID = m_PlayerID.size();

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("empty PlayerID");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long PlayerID length");

	oStream.write( szPlayerID );

	oStream.write( m_PlayerID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CLQueryPlayerID::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CLQueryPlayerIDHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CLQueryPlayerID::toString () const
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CLQueryPlayerID("
			<< "PlayerID:" << m_PlayerID 
			<< ")";
		return msg.toString();
			
		__END_CATCH
	}

#endif
