//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowWebMarket.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCShowWebMarket.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCShowWebMarket::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	BYTE szPlayerID, szName;

	iStream.read( szPlayerID );

	if ( szPlayerID == 0 )
		throw InvalidProtocolException( "szPlayerID == 0" );
	if ( szPlayerID > 20 )
		throw InvalidProtocolException( "too long szPlayerID length" );

	iStream.read( m_PlayerID, szPlayerID );

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	iStream.read( m_Name, szName );

	iStream.read( m_WorldID );
	iStream.read( m_Key );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCShowWebMarket::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	BYTE szPlayerID = m_PlayerID.size();
	BYTE szName = m_Name.size();

	if ( szPlayerID == 0 )
		throw InvalidProtocolException( "szPlayerID == 0" );
	if ( szPlayerID > 20 )
		throw InvalidProtocolException( "too long szPlayerID length" );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	oStream.write( szPlayerID );
	oStream.write( m_PlayerID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_WorldID );
	oStream.write( m_Key );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowWebMarket::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCShowWebMarketHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowWebMarket::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowWebMarket("
		<< "PlayerID:" << m_PlayerID
		<< "Name:" << m_Name 
		<< "WorldID:" << (int)m_WorldID
		<< "Key:" << m_Key
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

