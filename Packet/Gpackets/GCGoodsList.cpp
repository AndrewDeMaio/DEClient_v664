//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGoodsList.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCGoodsList.h"
#include "Assert.h"

#ifdef __GAME_SERVER__
	#include "Item.h"
	#include "ItemInfoManager.h"
	#include "Inventory.h"
	#include "AR.h"
	#include "SR.h"
	#include "SG.h"
	#include "SMG.h"
	#include "Belt.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GCGoodsList::GCGoodsList() 
{
	__BEGIN_TRY

	m_GoodsList.clear();
 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCGoodsList::~GCGoodsList() 
{
	__BEGIN_TRY

	std::list<GoodsInfo*>::iterator itr = m_GoodsList.begin();
	std::list<GoodsInfo*>::iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ;)
	{
		GoodsInfo *pInfo = *itr;
		++itr;
		if ( pInfo != NULL) 
		{
			delete pInfo;
			pInfo = NULL;
		}		
	}

	m_GoodsList.clear();
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	BYTE totalNum;
	iStream.read( totalNum );
	if ( totalNum > MAX_GOODS_LIST ) throw DisconnectException("GCGoodsList : ���� ������ ������ �ʰ��߽��ϴ�.");

	for ( int i=0; i < totalNum ; ++i )
	{
		GoodsInfo* pGI = new GoodsInfo;

		iStream.read( pGI->objectID );
		iStream.read( pGI->itemClass );
		iStream.read( pGI->itemType );
		iStream.read( pGI->grade );

		BYTE optionNum;
		iStream.read( optionNum );

		pGI->optionType.clear();

		for ( int j=0; j < optionNum ; ++j )
		{
			OptionType_t optionType;
			iStream.read( optionType );
			pGI->optionType.push_back( optionType );
		}
		
		iStream.read( pGI->num );
		iStream.read( pGI->timeLimit );

		addGoodsInfo( pGI );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	BYTE totalNum = m_GoodsList.size();
	if ( totalNum > MAX_GOODS_LIST ) throw DisconnectException("GCGoodsList : ������ ������ Ʋ���Ծ����ϴ�.");

	oStream.write( totalNum );
	
	std::list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
	std::list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		GoodsInfo* pGI = *itr;
		Assert( pGI != NULL );

		oStream.write( pGI->objectID );
		oStream.write( pGI->itemClass );
		oStream.write( pGI->itemType );
		oStream.write( pGI->grade );
		
		BYTE optionNum = pGI->optionType.size();
		oStream.write( optionNum );

		std::list<OptionType_t>::const_iterator oitr = pGI->optionType.begin();
		std::list<OptionType_t>::const_iterator endoItr = pGI->optionType.end();

		for ( ; oitr != endoItr ; ++oitr )
		{
			oStream.write( *oitr );
		}

		oStream.write( pGI->num );
		oStream.write( pGI->timeLimit );
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCGoodsListHandler::execute( this , pPlayer );

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCGoodsList::getPacketSize () const 
{ 
	__BEGIN_TRY
	__BEGIN_DEBUG

	PacketSize_t size = szBYTE;

	std::list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
	std::list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		size += (*itr)->getPacketSize();
	}

	return size;

	__END_DEBUG
	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__

//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCGoodsList::toString () const
{
	__BEGIN_TRY
		
//	StringStream msg;
//	msg << "GCGoodsList(";
//
//	std::list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
//	std::list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();
//
//	for ( ; itr != endItr ; ++itr )
//	{
////		msg << (*itr)->toString();
//	}
//
//	msg << ")";
////	return msg.toString();
//
	__END_CATCH

	return "";
//		
}


#endif