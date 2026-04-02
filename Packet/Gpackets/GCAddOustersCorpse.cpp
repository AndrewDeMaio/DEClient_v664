//----------------------------------------------------------------------
// 
// Filename    : GCAddOustersCorpse.cpp
// Written By  : Reiot
// 
//----------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddOustersCorpse.h"


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCAddOustersCorpse::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	m_OustersInfo.read( iStream );
	iStream.read( m_TreasureCount );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCAddOustersCorpse::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	m_OustersInfo.write( oStream );
	oStream.write( m_TreasureCount );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCAddOustersCorpse::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddOustersCorpseHandler::execute( this , pPlayer );
		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
std::string GCAddOustersCorpse::toString () const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddOustersCorpse("
		<< m_OustersInfo.toString()
		<< ", Count : " << (int)m_TreasureCount
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
#endif