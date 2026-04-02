//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellOK.cpp 
// Written By  : �輺��
// Description : �÷��̾ ���� NPC���� ���� ������ ��û���� ��, �����
//               ������ �Ǹ� �� ��Ŷ�� �÷��̾�� ���ư���.
//               Ŭ���̾�Ʈ�� �� ��Ŷ�� �޾Ƽ� ���� ������ ������Ʈ�ϰ�,
//               ������Ʈ ID�� ������ ������ üũ�� ����, ������ �̿���
//               �÷��̾��� ���� ������Ʈ�Ѵ�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCShopSellOK.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopSellOK::GCShopSellOK() 
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopSellOK::~GCShopSellOK() 
{
	__BEGIN_TRY 
	
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCShopSellOK::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_ItemObjectID);
	iStream.read(m_Price);

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCShopSellOK::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_ItemObjectID);
	oStream.write(m_Price);
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopSellOK::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCShopSellOKHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug std::string
//--------------------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string GCShopSellOK::toString () const
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "GCShopSellOK(";
		msg << "ObjectID:"     << m_ObjectID << ","
			<< "Version:"      << m_Version << ","
				<< "ItemObejctID:" << m_ItemObjectID << ","
				<< "Price:"        << m_Price;
	//	msg << ")" << endl;

		return msg.toString();
			
		__END_CATCH
	}
#endif

