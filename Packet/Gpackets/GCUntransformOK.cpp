//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUntransformOK.cc 
// Written By  : crazydog
// Description : CGUntransform�� ���� ������ �ڱ� �ڽſ��� OK ������ ������
//               ���� ��Ŷ Ŭ���� �Լ� ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCUntransformOK.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCUntransformOK::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCUntransformOK::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCUntransformOK::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCUntransformOKHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCUntransformOK::toString () const
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCUntransformOK("
			<< "X:" << (int)m_X 
			<< ",Y:" << (int) m_Y 
			<< ",Dir:" << Dir2String[m_Dir] 
			<< ")";
		return msg.toString();

		__END_CATCH
	}
#endif

