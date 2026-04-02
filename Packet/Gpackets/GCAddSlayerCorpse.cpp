//--------------------------------------------------------------------------------
// 
// Filename    : GCAddSlayerCorpse.cpp
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCAddSlayerCorpse.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCAddSlayerCorpse::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	//--------------------------------------------------
	// read slayer info
	//--------------------------------------------------
	m_SlayerInfo.read( iStream );
	iStream.read( m_TreasureCount );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCAddSlayerCorpse::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	//--------------------------------------------------
	// write slayer info
	//--------------------------------------------------
	m_SlayerInfo.write( oStream );
	oStream.write( m_TreasureCount );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCAddSlayerCorpse::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddSlayerCorpseHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
std::string GCAddSlayerCorpse::toString () const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddSlayerCorpse("
		<< m_SlayerInfo.toString()
		<< ", Count : " << (int)m_TreasureCount
		<< ")";

	return msg.toString();

	__END_CATCH
}


#endif