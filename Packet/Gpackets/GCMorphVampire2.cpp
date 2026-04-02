//----------------------------------------------------------------------
// 
// Filename    : GCMorphVampire2.cpp
// Written By  : crazydog
// 
//----------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCMorphVampire2.h"


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCMorphVampire2::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_VampireInfo3.read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCMorphVampire2::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

		
	m_VampireInfo3.write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCMorphVampire2::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCMorphVampire2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCMorphVampire2::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCMorphVampire2("
			<< m_VampireInfo3.toString()
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}
#endif