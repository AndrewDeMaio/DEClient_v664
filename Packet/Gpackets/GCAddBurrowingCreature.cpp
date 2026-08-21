//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddBurrowingCreature.cc 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddBurrowingCreature.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddBurrowingCreature::read ( SocketInputStream & iStream ) 
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


	iStream.read( m_X );
	iStream.read( m_Y );
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddBurrowingCreature::write ( SocketOutputStream & oStream ) const 
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

	if ( szName > 20 + localLongName )
		throw InvalidProtocolException("too large name length");

	oStream.write( szName );
	oStream.write( m_Name );

	oStream.write( m_X );
	oStream.write( m_Y );
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddBurrowingCreature::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddBurrowingCreatureHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAddBurrowingCreature::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAddBurrowingCreature("
			<< "ObjectID:" << m_ObjectID 
			<< ",Name:" << m_Name 
			<< ",X:" << (int)m_X 
			<< ",Y:" << (int)m_Y 
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}

#endif
