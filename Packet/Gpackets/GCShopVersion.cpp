//--------------------------------------------------------------------------------
// 
// Filename    : GCShopVersion.cpp 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCShopVersion.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopVersion::GCShopVersion() 
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopVersion::~GCShopVersion() 
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCShopVersion::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	// read object id
	iStream.read( m_ObjectID );
#if __CONTENTS(__GLOBAL_NPC)
	iStream.read(m_NPCID);
#endif //__GLOBAL_NPC

	// read versions
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
		iStream.read(m_Version[i]);

	iStream.read(m_MarketCondSell);
	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCShopVersion::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
		
	// write object id
	oStream.write( m_ObjectID );
#if __CONTENTS(__GLOBAL_NPC)
	oStream.write(m_NPCID);
#endif//__GLOBAL_NPC
	// write versions
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
		oStream.write(m_Version[i]);
	
	oStream.write( m_MarketCondSell );
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopVersion::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCShopVersionHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCShopVersion::toString () const
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "GCShopVersion(" << "ObjectID:" << (int)m_ObjectID;
#if __CONTENTS(__GLOBAL_NPC)
		msg << "NPCID" << (NPCID_t)m_NPCID;
#endif//__GLOBAL_NPC
		msg << "Ratio:" << (int)m_MarketCondSell;
		
		for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
			msg << " Version[" << (int)i << "] : " << (int)m_Version[i];

		//msg << ")" << endl;
		
		return msg.toString();
			
		__END_CATCH
	}
#endif

