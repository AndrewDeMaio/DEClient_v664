//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddWolf.cc 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddWolf.h"

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddWolf::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
	localLongName = 12;
#endif //__LOCALIZING_LONGNAME		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );

	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 + localLongName)
		throw InvalidProtocolException("too large name length");
		
	iStream.read( m_Name , szName );
/*
	iStream.read( m_SpriteType );

	iStream.read( m_SubColor );
*/
	iStream.read( m_MainColor );
	
	iStream.read( m_ItemType );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );
	iStream.read( m_CurrentHP);
	iStream.read( m_MaxHP);
	iStream.read( m_GuildID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddWolf::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
	localLongName = 12;
#endif //__LOCALIZING_LONGNAME		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );

	BYTE szName = (BYTE)m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 + localLongName)
		throw InvalidProtocolException("too large name length");

	oStream.write( szName );
	oStream.write( m_Name );
/*
	oStream.write( m_SpriteType );

	oStream.write( m_SubColor );
*/
	oStream.write( m_MainColor );
	
	oStream.write( m_ItemType );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );
	oStream.write( m_CurrentHP);
	oStream.write( m_MaxHP);
	oStream.write( m_GuildID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddWolf::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddWolfHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	
	std::string GCAddWolf::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAddWolf("
			<< "ObjectID:" << m_ObjectID 
			<< ",Name:" << m_Name 
			<< ",ItemType:" << (int)m_ItemType
			<< ",X:" << (int)m_X 
			<< ",Y:" << (int)m_Y 
			<< ",Dir: " << (int)m_Dir 
			<< ",CurrentHP: " << (int)m_CurrentHP 
			<< ",MaxHP: " << (int)m_MaxHP 
			<< ",GuildID: " << (int)m_GuildID
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}

#endif
