//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycleOK.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCRideMotorCycleOK.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCRideMotorCycleOK::GCRideMotorCycleOK () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCRideMotorCycleOK::~GCRideMotorCycleOK () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycleOK::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	iStream.read( m_MotorType );

	switch(m_MotorType)
	{
		case 4:
			iStream.read( m_WingBodyColor );
			iStream.read( m_WingEffectColor );
			break;
		default :
			break;
	}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycleOK::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	oStream.write( m_MotorType );

	switch(m_MotorType)
	{
		case 4:
			oStream.write( m_WingBodyColor );
			oStream.write( m_WingEffectColor );
			break;
		default :
			break;
	}

#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycleOK::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCRideMotorCycleOKHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCRideMotorCycleOK::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCRideMotorCycleOK( ObjectID:" << (int)m_ObjectID 
			<< " )";

		return msg.toString();

		__END_CATCH
	}
#endif
