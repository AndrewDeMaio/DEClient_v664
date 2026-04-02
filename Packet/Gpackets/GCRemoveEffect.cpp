//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveEffect.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCRemoveEffect.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCRemoveEffect::GCRemoveEffect () 
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCRemoveEffect::~GCRemoveEffect () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCRemoveEffect::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_ObjectID);
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ListNum );

	EffectID_t value;
	for( int i = 0; i < m_ListNum; i++ ) {
		iStream.read( value );
		m_EffectList.push_back(value);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCRemoveEffect::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID);
	
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ListNum );

    for ( std::list<EffectID_t>:: const_iterator itr = m_EffectList.begin(); itr!= m_EffectList.end(); itr++) {
		oStream.write(*itr);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCRemoveEffect::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCRemoveEffectHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// GCRemoveEffect::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void GCRemoveEffect::addEffectList( EffectID_t Value )
{
	__BEGIN_TRY

	// ���ϴ� ���� �������� List�� �ִ´�.
	m_EffectList.push_back( Value );

	// ��ȭ ���� ������ �ϳ� ���� ��Ų��.
	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCRemoveEffect::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCRemoveEffect( "
			<< "objectID: " << (int)m_ObjectID 
			<< ",ListNum: " << (int)m_ListNum 
			<< " ListSet( " ;

		for ( std::list<EffectID_t>::const_iterator itr = m_EffectList.begin(); itr!= m_EffectList.end() ; itr++ ) {
			msg << (int)(*itr) << ",";
		}

		msg << ")";

		return msg.toString();

		__END_CATCH
	}

#endif