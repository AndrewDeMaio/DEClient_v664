//----------------------------------------------------------------------
// 
// Filename    : GCMorphSlayer2.cpp
// Written By  : crazydog
// 
//----------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCMorphSlayer2.h"


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCMorphSlayer2::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_SlayerInfo3.read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCMorphSlayer2::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

		
	m_SlayerInfo3.write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCMorphSlayer2::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCMorphSlayer2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCMorphSlayer2::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCMorphSlayer2("
			<< m_SlayerInfo3.toString()
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}
#endif