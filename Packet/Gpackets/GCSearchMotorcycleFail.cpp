//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleFail.cpp 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCSearchMotorcycleFail.h"
#include "Assert.h"

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCSearchMotorcycleFail::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCSearchMotorcycleFail::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCSearchMotorcycleFail::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSearchMotorcycleFailHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCSearchMotorcycleFail::toString () const
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GCSearchMotorcycleFail()";
		return msg.toString();
			
		__END_CATCH
	}
#endif

