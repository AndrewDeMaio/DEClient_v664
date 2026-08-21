//--------------------------------------------------------------------------------
// 
// Filename    : CGRequestRepair.cpp 
// Written By  : �輺��
// Description : 
//--------------------------------------------------------------------------------

// include files
#include "Packet_PCH.h"
#include "CGRequestRepair.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CGRequestRepair::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void CGRequestRepair::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CGRequestRepair::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGRequestRepairHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string CGRequestRepair::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "CGRequestRepair( ObjectID : " << (int)m_ObjectID << ")";
		return msg.toString();

		__END_CATCH
	}
#endif