//////////////////////////////////////////////////////////////////////
// 
// Filename	: GCNicknameList.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//			   ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCNicknameList.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCNicknameList::GCNicknameList () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCNicknameList::~GCNicknameList () 
{
	__BEGIN_TRY
  
	BYTE Num = m_Nicknames.size();
	
	std::vector<NicknameInfo*>::iterator itr = m_Nicknames.begin();
	std::vector<NicknameInfo*>::iterator endItr = m_Nicknames.end();

	// Memory leak sol Sjheon 2006.03.07
	for ( ; itr != endItr; ++itr )
	{
		delete (*itr); 
	}
	m_Nicknames.clear() ; 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCNicknameList::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	m_Nicknames.clear();

	BYTE Num;
	iStream.read(Num);

	for ( int i=0; i<Num; ++i )
	{
		NicknameInfo* pUnit = new NicknameInfo;
		pUnit->read(iStream);
		m_Nicknames.push_back( pUnit );
	}
		
	__END_CATCH
}

			
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCNicknameList::write ( SocketOutputStream & oStream ) 
	 const
{
	__BEGIN_TRY

	BYTE Num = m_Nicknames.size();
	oStream.write(Num);

	std::vector<NicknameInfo*>::const_iterator itr = m_Nicknames.begin();
	std::vector<NicknameInfo*>::const_iterator endItr = m_Nicknames.end();

	for ( ; itr != endItr; ++itr )
	{
		(*itr)->write(oStream);
	}
		
	__END_CATCH
}

PacketSize_t GCNicknameList::getPacketSize() const
{
	__BEGIN_TRY

	PacketSize_t ret = szBYTE;

	std::vector<NicknameInfo*>::const_iterator itr = m_Nicknames.begin();
	std::vector<NicknameInfo*>::const_iterator endItr = m_Nicknames.end();

	for ( ; itr != endItr; ++itr )
	{
		ret += (*itr)->getSize();
	}

	return ret;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////

void GCNicknameList::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCNicknameListHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
string GCNicknameList::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCNicknameList("
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif
