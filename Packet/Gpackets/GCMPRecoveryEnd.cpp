//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryEnd.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCMPRecoveryEnd.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCMPRecoveryEnd::GCMPRecoveryEnd()
{
	__BEGIN_TRY
	m_CurrentMP = 0;
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCMPRecoveryEnd::~GCMPRecoveryEnd()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_CurrentMP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	oStream.write( m_CurrentMP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCMPRecoveryEndHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCMPRecoveryEnd::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCMPRecoveryEnd("
			<< ",CurrentMP:" << (int)m_CurrentMP
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}
#endif