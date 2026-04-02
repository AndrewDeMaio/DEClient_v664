//--------------------------------------------------------------------------------
// 
// Filename    : GCLightning.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCLightning.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCLightning::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_Delay );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCLightning::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_Delay );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCLightning::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCLightningHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCLightning::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCLightning("
			<< "Delay:" << (int)m_Delay
			<< ")";

		return msg.toString();

		__END_CATCH
	}

#endif
