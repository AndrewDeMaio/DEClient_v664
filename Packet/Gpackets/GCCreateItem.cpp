//////////////////////////////////////////////////////////////////////////////
// Filename    : GCCreateItem.cpp
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCCreateItem.h"
#if __CONTENTS(__PCITEMINFO)
GCCreateItem::GCCreateItem()
{
	__BEGIN_TRY
	
	m_InvenX       = 0;
	m_InvenY       = 0;
	// 2007 03 29 Add
	m_InventoryItemObjectID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_InvenX );
	iStream.read( m_InvenY );
	
	m_PCItemInfo.read(iStream);
	
	iStream.read( m_InventoryItemObjectID );
		
	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );
	
	m_PCItemInfo.write(oStream);
	
	oStream.write( m_InventoryItemObjectID );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCCreateItemHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCCreateItem::toString () const
{
	__BEGIN_TRY

	StringStream msg;
#ifdef __DEBUG_OUTPUT__
	msg << "GCCreateItem("
		<< ",InvenX:"       << (int)m_InvenX
		<< ",InvenY:"       << (int)m_InvenY
		<< ",PCItemInfo:"       << m_PCItemInfo.toString()
		<< ",InventorySlotInfo:" << (int)m_InventoryItemObjectID
		<< ")";
#endif //__DEBUG_OUTPUT__
	return msg.toString();
	__END_CATCH
}
#else //__PCITEMINFO
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//20070329 by diesirace ���� �κ��丮 ���� ����
GCCreateItem::GCCreateItem()
{
	__BEGIN_TRY

	m_ObjectID     = 0;
	m_ItemClass    = 0;
	m_ItemType     = 0;
	m_Durability   = 0;
	m_Silver       = 0;
	m_Grade        = 0;
	m_EnchantLevel = 0;
	m_ItemNum      = 0;
	m_InvenX       = 0;
	m_InvenY       = 0;
	m_InventoryItemObjectID = 0;
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	m_CashItem		= 0;
#endif
	m_ThirdEnchantType = 99;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read( m_ObjectID );
	iStream.read( m_ItemClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );
	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}

	iStream.read( m_Durability );
	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_EnchantLevel );
	iStream.read( m_ItemNum );
	iStream.read( m_InvenX );
	iStream.read( m_InvenY );
	iStream.read( m_InventoryItemObjectID );
//20071009 by diesirace ��������ۿɼ� �߰� (���� �ɼ� �޸� �������� ����������� ���� ���ܴ�...)
//	BYTE thirdOptionSize;
// 	iStream.read( thirdOptionSize );
//	m_ThirdOptionType.clear();
//	for (int thirdindex = 0; thirdindex < thirdOptionSize; thirdindex++) 
//	{
//		OptionType_t optionType;
//		iStream.read( optionType );
//		m_ThirdOptionType.push_back( optionType );
//	}
//
//	iStream.read( m_ThirdEnchantType );
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	iStream.read(m_CashItem);
#endif	//__INTERNATIONAL_PREMIUM_SYSTEM	
	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_ItemClass );
	oStream.write( m_ItemType );
	
	size_t optionSize = m_OptionType.size();
	oStream.write( optionSize );

	std::list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
		oStream.write( optionType );
	}

	oStream.write( m_Durability );
	oStream.write( m_Silver );
	oStream.write( m_Grade );
	oStream.write( m_EnchantLevel );
	oStream.write( m_ItemNum );
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );
	oStream.write( m_InventoryItemObjectID );
//20071009 by diesirace ��������ۿɼ� �߰� (���� �ɼ� �޸� �������� ����������� ���� ���ܴ�...)
//	BYTE thirdOptionSize = m_ThirdOptionType.size();
//	oStream.write( thirdOptionSize );
//	std::list<OptionType_t>::const_iterator iThirdOption = m_ThirdOptionType.begin();
//    for (; iThirdOption!= m_ThirdOptionType.end(); iThirdOption++) 
//	{
//		OptionType_t optionType = *iThirdOption;
//		oStream.write( optionType );
//	}
//	oStream.write( m_ThirdEnchantType );
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	oStream.write(m_CashItem);
#endif	//__INTERNATIONAL_PREMIUM_SYSTEM
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCCreateItemHandler::execute( this , pPlayer );
		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__	
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCCreateItem::toString () const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCCreateItem("
		<< "ObjectID:"      << (int)m_ObjectID
		<< ",ItemClass:"    << (int)m_ItemClass
		<< ",ItemType:"     << (int)m_ItemType
		<< ",OptionTypeSize:"   << (int)m_OptionType.size()
		<< ",Durability:"   << (int)m_Durability
		<< ",Silver:"       << (int)m_Silver
		<< ",Grade:"        << (int)m_Grade
		<< ",EnchantLEvel:" << (int)m_EnchantLevel
		<< ",ItemNum:"      << (int)m_ItemNum
		<< ",InvenX:"       << (int)m_InvenX
		<< ",InvenY:"       << (int)m_InvenY
		<< ",InventoryItemObjectID:"		<< (int)m_InventoryItemObjectID
//20071009 by diesirace ��������ۿɼ� �߰� (���� �ɼ� �޸� �������� ����������� ���� ���ܴ�...)
//		<< "ThirdOptionTypeSize:"	<< (int)m_ThirdOptionType.size()
//		<< "ThirdEnchantType"		<<	(int)m_ThirdEnchantType
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
		<< "CashItem"		<< (int)m_CashItem
#endif //__INTERNATIONAL_PREMIUM_SYSTEM
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif //__DEBUG_OUTPUT__

#endif //__PCITEMINFO