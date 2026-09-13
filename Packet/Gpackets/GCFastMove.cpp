//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFastMove.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "ServerSkillDisplay.h"
#include "GCFastMove.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCFastMove::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_FromX );
	iStream.read( m_FromY );
	iStream.read( m_ToX );
	iStream.read( m_ToY );
	iStream.read( m_SkillType ); m_SkillType = static_cast<decltype(m_SkillType)>(TranslateServerSkillType(m_SkillType));

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCFastMove::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_FromX );
	oStream.write( m_FromY );
	oStream.write( m_ToX );
	oStream.write( m_ToY );
	oStream.write( m_SkillType );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFastMove::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCFastMoveHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCFastMove::toString () const
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCFastMove(ObjectID:" << m_ObjectID 
			<< ",From(X,Y):" << (int)m_FromX<<","<<(int)m_FromY 
			<< ",To(X,Y):" << (int)m_ToX<<","<<(int)m_ToY;
		return msg.toString();

		__END_CATCH
	}
#endif

