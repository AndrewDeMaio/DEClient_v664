//--------------------------------------------------------------------------------
// 
// Filename    : GCShopMarketCondition.cpp 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCShopMarketCondition.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopMarketCondition::GCShopMarketCondition() 
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopMarketCondition::~GCShopMarketCondition() 
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCShopMarketCondition::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	// read object id
	iStream.read( m_ObjectID );

	iStream.read( m_MarketCondBuy );

	iStream.read( m_MarketCondSell );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCShopMarketCondition::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	// write object id
	oStream.write( m_ObjectID );

	oStream.write( m_MarketCondBuy );

	oStream.write( m_MarketCondSell );
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopMarketCondition::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCShopMarketConditionHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCShopMarketCondition::toString () const
	{
		__BEGIN_TRY
			
	StringStream msg;
	
	msg << "GCShopMarketCondition(" 
	    << "ObjectID: "       << (int)m_ObjectID << ", "
	    << "MarketCondBuy: "  << (int)m_MarketCondBuy << ", "
	    << "MarketCondsell: " << (int)m_MarketCondSell << ", ";
	msg << ")";
	
	return msg.toString();
			
		__END_CATCH
	}
#endif

