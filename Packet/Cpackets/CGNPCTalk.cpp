//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCTalk.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "Packet_PCH.h"
#include "CGNPCTalk.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CGNPCTalk::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void CGNPCTalk::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CGNPCTalk::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGNPCTalkHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string CGNPCTalk::toString () 
		const
	{
		StringStream msg;
		msg << "CGNPCTalk( ObjectID : " << (int)m_ObjectID << ")";
		return msg.toString();
	}
#endif
