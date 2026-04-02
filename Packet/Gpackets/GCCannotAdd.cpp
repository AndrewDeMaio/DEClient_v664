//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCannotAdd.cc 
// Written By  : elca@ewestsoft.com
// Description : CGMove�� ���� ������ �ڱ� �ڽſ��� OK ������ ������
//               ���� ��Ŷ Ŭ���� �Լ� ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCCannotAdd.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCCannotAdd::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_ObjectID );

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// GCCannotAdd::read
	iStream.read( m_CannotReason );
#endif // __GEAR_SWAP_CHANGE
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCCannotAdd::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// GCCannotAdd::write
	oStream.write( m_CannotReason );
#endif // __GEAR_SWAP_CHANGE

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCCannotAdd::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCCannotAddHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCCannotAdd::toString () const
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCCannotAdd("
			<< "ObjectId:" << (int)m_ObjectID
			<< ")";
		return msg.toString();

		__END_CATCH
	}
#endif
