//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCOtherGuildName.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCOtherGuildName.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCOtherGuildName::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	BYTE szGuildName;
	
	iStream.read( m_ObjectID );
	iStream.read( m_GuildID );

	iStream.read( szGuildName );
	//if ( szGuildName == 0 )
	//	throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 30 )
		throw InvalidProtocolException("too long GuildName length");

	if ( szGuildName!=0 )
		iStream.read( m_GuildName, szGuildName );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCOtherGuildName::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	BYTE szGuildName = (BYTE)m_GuildName.size();

	//if ( szGuildName == 0 )
	//	throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 30 )
		throw InvalidProtocolException("too long GuildName length");

	oStream.write( m_ObjectID );
	oStream.write( m_GuildID );
	oStream.write( szGuildName );

	if ( szGuildName != 0 )
		oStream.write( m_GuildName );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCOtherGuildName::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCOtherGuildNameHandler::execute( this , pPlayer );

	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
std::string GCOtherGuildName::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCOtherGuildName("
		<< "ObjectID:" << (int)m_ObjectID
		<< "GuildID:" << (int)m_GuildID
		<< "GuildName:" << m_GuildName
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


#endif