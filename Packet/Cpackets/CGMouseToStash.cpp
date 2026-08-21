////////////////////////////////////////////////////////////////////////////////
// Filename    : CGMouseToStash.cpp 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "CGMouseToStash.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void CGMouseToStash::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	iStream.read( m_ObjectID );
	iStream.read( m_Rack );
	iStream.read( m_Index );

	__END_DEBUG
	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
////////////////////////////////////////////////////////////////////////////////
void CGMouseToStash::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	oStream.write( m_ObjectID );
	oStream.write( m_Rack );
	oStream.write( m_Index );

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void CGMouseToStash::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	#ifndef __GAME_CLIENT__
		CGMouseToStashHandler::execute ( this , pPlayer );
	#endif	
		
	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGMouseToStash::toString () 
		const
	{
		__BEGIN_TRY
		__BEGIN_DEBUG
			
		StringStream msg;
		msg << "CGMouseToStash("
			<< " ObjectID : " << (int)m_ObjectID 
			<< " Rack : "     << (int)m_Rack
			<< " Index : "    << (int)m_Index
			<< ")";
		return msg.toString();

		__END_DEBUG
		__END_CATCH
	}
#endif