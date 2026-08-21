//////////////////////////////////////////////////////////////////////
// 
// Filename    : RCCharacterInfo.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "RCCharacterInfo.h"


RCCharacterInfo::RCCharacterInfo()
{
	m_GuildID = 0;
}

//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void RCCharacterInfo::read ( Datagram & iDatagram ) 
{
	__BEGIN_TRY

	// Name
	BYTE szName;

	iDatagram.read( szName );

	//if ( szName == 0 )
	//	throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long Name length");

	if (szName > 0)
	{
		iDatagram.read( m_Name , szName );
	}

	// 
	iDatagram.read( m_GuildID );	

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void RCCharacterInfo::write ( Datagram & oDatagram ) const 
{
	__BEGIN_TRY

	// Name
	BYTE szName = m_Name.size();

	//if ( szName == 0 )
	//	throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long Name length");

	oDatagram.write( szName );

	if (szName > 0)
	{
		oDatagram.write( m_Name );
	}

	oDatagram.write( m_GuildID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void RCCharacterInfo::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	RCCharacterInfoHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string RCCharacterInfo::toString () const
	{
		StringStream msg;
		
		msg << "RCCharacterInfo( "
			<< ",GuildID" << (int)m_GuildID
			<< ")";


		return msg.toString();
	}
#endif

