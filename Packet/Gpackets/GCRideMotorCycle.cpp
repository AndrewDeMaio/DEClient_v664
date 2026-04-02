//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycle.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCRideMotorCycle.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCRideMotorCycle::GCRideMotorCycle () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCRideMotorCycle::~GCRideMotorCycle () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCRideMotorCycle::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
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
void GCRideMotorCycle::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
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
void GCRideMotorCycle::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCRideMotorCycleHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCRideMotorCycle::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCRideMotorCycle( ObjectID:" << (int)m_ObjectID 
			<< " TargetObjectID : " << (int)m_TargetObjectID 
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
			<< " MotorType : " << (int)m_MotorType 
			<< " WingBodyColor : " << (int)m_WingBodyColor 
			<< " WingEffectColor : " << (int)m_WingEffectColor 
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
			<< " )";

		return msg.toString();

		__END_CATCH
	}

#endif
