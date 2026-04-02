//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMineExplosionOK2.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCMineExplosionOK2.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCMineExplosionOK2::GCMineExplosionOK2 () 
{
	__BEGIN_TRY

	m_CListNum = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCMineExplosionOK2::~GCMineExplosionOK2 () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );
	iStream.read( m_ItemType);
    iStream.read( m_CListNum );

    ObjectID_t m_Value;
	int i;

	for( i = 0; i < m_CListNum; i++ ) {
		iStream.read( m_Value );
		m_CList.push_back( m_Value );
	}

	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );
	oStream.write( m_ItemType);
    oStream.write( m_CListNum );

    for ( std::list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		oStream.write( *itr );
	}

	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCMineExplosionOK2::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2::addCListElement( ObjectID_t ObjectID )
{
    __BEGIN_TRY

    // Creature ID�� �߰��Ѵ�.
    m_CList.push_back( ObjectID );

    // ũ��ó ID count�� ������Ų��.
    m_CListNum++;

    __END_CATCH

}

/*
//////////////////////////////////////////////////////////////////////
//
// GCMineExplosionOK2::deleteCListElement()
// 
// Creature List�� ��Ҹ� ���ﶧ �ʿ��� ��� �Լ�.
//
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2::deleteCListElement()
{
    __BEGIN_TRY

    // ũ���� ���̵� �ϳ� �����.
    m_CList.pop_front();

    // ũ��ó ����Ʈ ī���͸� �ϳ� �����.
    m_CListNum--;

    __END_CATCH
}
*/


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCMineExplosionOK2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCMineExplosionOK2::toString () const
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCMineExplosionOK2( X:" << (int)m_X
			<< ",Y:" << (int)m_Y
			<< ",Dir:" << (int)m_Dir
			<< ",ItemType:" << (int)m_ItemType
			<< ",CListNum: " << (int)m_CListNum 
			<< " CListSet(";

		for ( std::list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
			msg << (int)(*itr) << ",";
		}

		msg << ")";



		return msg.toString();

		__END_CATCH
	}
#endif

