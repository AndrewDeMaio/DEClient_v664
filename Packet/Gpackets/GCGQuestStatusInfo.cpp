//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGQuestStatusInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCGQuestStatusInfo.h"
#include "Client.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusInfo::GCGQuestStatusInfo () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusInfo::~GCGQuestStatusInfo () 
{
	__BEGIN_TRY

	std::list<QuestStatusInfo*>::iterator itr = m_Infos.begin();

	for ( ; itr != m_Infos.end() ; ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	m_Infos.clear();
	BYTE size;
	iStream.read(size);

	for ( int i=0; i<size; i++ )
	{
		QuestStatusInfo* pInfo = new QuestStatusInfo;
		pInfo->read(iStream);
		m_Infos.push_back(pInfo);
	}

	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY

	BYTE size = m_Infos.size();
	oStream.write(size);

	std::list<QuestStatusInfo*>::const_iterator itr = m_Infos.begin();

	for ( ; itr != m_Infos.end(); ++itr )
	{
		(*itr)->write(oStream);
	}
		
	__END_CATCH
}

PacketSize_t	addSize( PacketSize_t tot, const QuestStatusInfo* pInfo )
{
	return tot + pInfo->getSize();
}

PacketSize_t GCGQuestStatusInfo::getPacketSize() 
const 
{ 
	return std::accumulate( m_Infos.begin(), m_Infos.end(), szBYTE, addSize ); 
}
//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusInfo::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCGQuestStatusInfoHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
string GCGQuestStatusInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCGQuestStatusInfo("
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif

