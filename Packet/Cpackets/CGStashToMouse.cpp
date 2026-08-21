////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStashToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "CGStashToMouse.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void CGStashToMouse::read ( SocketInputStream & iStream ) 
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
void CGStashToMouse::write ( SocketOutputStream & oStream ) const 
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
void CGStashToMouse::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	#ifndef __GAME_CLIENT__
		CGStashToMouseHandler::execute ( this , pPlayer );
	#endif
		
	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGStashToMouse::toString () 
		const
	{
		__BEGIN_TRY
		__BEGIN_DEBUG
			
		StringStream msg;
		msg << "CGStashToMouse("
			<< " ObjectID : " << (int)m_ObjectID
			<< " Rack : "     << (int)m_Rack
			<< " Index : "    << (int)m_Index
			<< ")";
		return msg.toString();

		__END_DEBUG
		__END_CATCH
	}
#endif