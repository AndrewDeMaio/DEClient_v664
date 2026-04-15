//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLDeletePC.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CLDeletePC.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CLDeletePC::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	BYTE szName;
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_Name , szName );

	BYTE slot;
	iStream.read( slot );
	m_Slot = Slot(slot);

	BYTE szSSN;
	iStream.read( szSSN );

	if ( szSSN == 0 )
		throw InvalidProtocolException("szSSN == 0");

	if ( szSSN > 18 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_SSN, szSSN );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CLDeletePC::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	size_t szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	oStream.write( szName );
	oStream.write( m_Name );

	oStream.write( (BYTE)m_Slot );

	size_t szSSN = m_SSN.size();

	if ( szSSN== 0 )
		throw InvalidProtocolException("szSSN == 0");

	if ( szSSN > 18 )
		throw InvalidProtocolException("too long name length");

	oStream.write( szSSN );
	oStream.write( m_SSN );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CLDeletePC::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CLDeletePCHandler::execute( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CLDeletePC::toString () const
	{
		__BEGIN_TRY

		StringStream msg;
		
		msg << "CLDeletePC(Name:" << m_Name
			<< ",Slot:" << (int)m_Slot
			<< ",SSN:" << m_SSN
			<< ")" ;
		
		return msg.toString();

		__END_CATCH
	}

#endif