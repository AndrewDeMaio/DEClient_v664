//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleOK.cpp 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCSearchMotorcycleOK.h"
#include "Assert.h"

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCSearchMotorcycleOK::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_ZoneID );
	iStream.read( m_ZoneX );
	iStream.read( m_ZoneY );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCSearchMotorcycleOK::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	oStream.write( m_ZoneID );
	oStream.write( m_ZoneX );
	oStream.write( m_ZoneY );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCSearchMotorcycleOK::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSearchMotorcycleOKHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCSearchMotorcycleOK::toString () const
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "GCSearchMotorcycleOK(" 
			<< " ZoneID : " << (int)m_ZoneID
			<< " ZoneX  : " << (int)m_ZoneX
			<< " ZoneY  : " << (int)m_ZoneY
			<< ")";
		
		return msg.toString();
			
		__END_CATCH
	}
#endif

