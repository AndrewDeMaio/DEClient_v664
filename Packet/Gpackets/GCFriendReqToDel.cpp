//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFriendReqToDel.cpp 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCFriendReqToDel.h"

#if __CONTENTS(__FRIEND_ADDITION)
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCFriendReqToDel::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	BYTE szPCName;

	iStream.read( szPCName );
	
	if ( szPCName == 0 )
	{
		throw InvalidProtocolException( "szPCName == 0" );
	}
	if ( szPCName > 20 )
	{
		throw InvalidProtocolException( "szPCName > 20" );
	}
	
	iStream.read( m_strPCName, szPCName );
	iStream.read( m_Result );
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCFriendReqToDel::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	BYTE szPCName;
	
	szPCName = m_strPCName.size();

	if ( szPCName == 0 )
	{
		throw InvalidProtocolException( "szPCName == 0" );
	}
	if ( szPCName > 20 )
	{
		throw InvalidProtocolException( "szPCName > 20" );
	}
	
	oStream.write( szPCName );
	oStream.write( m_strPCName );
	oStream.write( m_Result );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFriendReqToDel::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCFriendReqToDelHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GCFriendReqToDel::toString () const
{
	StringStream msg;

	msg << "GCFriendReqToDel ("
		<< "PCName:" << m_strPCName
		<< "Result:" << m_Result
		<< " )";

	return msg.toString();
}
#endif //__FRIEND_ADDITION
