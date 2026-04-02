//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryStartToOthers.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCHPRecoveryStartToOthers.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCHPRecoveryStartToOthers::GCHPRecoveryStartToOthers () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCHPRecoveryStartToOthers::~GCHPRecoveryStartToOthers () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_Delay );
	iStream.read( m_Period );
	iStream.read( m_Quantity );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_Delay );
	oStream.write( m_Period );
	oStream.write( m_Quantity );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCHPRecoveryStartToOthersHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCHPRecoveryStartToOthers::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCHPRecoveryStartToOthers( ObjectID:" << (int)m_ObjectID 
			<< " Delay : " << (int)m_Delay
			<< " Period : " << (int)m_Period
			<< " Quantity : " << (int)m_Quantity
			<< " )";

		return msg.toString();

		__END_CATCH
	}
#endif

