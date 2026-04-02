//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireFromBurrowing.cpp
// Written By  : Reiot
// 
//----------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddVampireFromBurrowing.h"

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
GCAddVampireFromBurrowing::~GCAddVampireFromBurrowing()
{
	__BEGIN_TRY
	
	if( m_pEffectInfo != NULL )
	{
		delete m_pEffectInfo;
		m_pEffectInfo = NULL;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCAddVampireFromBurrowing::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_VampireInfo.read( iStream );

	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCAddVampireFromBurrowing::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	m_VampireInfo.write( oStream );

	m_pEffectInfo->write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCAddVampireFromBurrowing::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddVampireFromBurrowingHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCAddVampireFromBurrowing::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAddVampireFromBurrowing("
			<< "VampireInfo:" << m_VampireInfo.toString()
			<< "EffectInfo:" << m_pEffectInfo->toString()
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}
#endif