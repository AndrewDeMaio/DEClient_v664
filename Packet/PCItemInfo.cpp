//////////////////////////////////////////////////////////////////////////////
// Filename    : PCItemInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Packet_PCH.h"
#include "PCItemInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "StringStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
PCItemInfo::PCItemInfo ()
{
	__BEGIN_TRY

	m_ObjectID     = 0;
	m_IClass       = 0;
	m_ItemType     = 0;
	m_Durability   = 0;
	m_Silver       = 0;
	m_Grade        = 0;
	m_EnchantLevel = 0;
	m_ItemNum      = 0;
	m_MainColor    = 0;
	m_ListNum      = 0;
	m_ThirdEnchantType = 99;
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	m_CashItem		= 0;
#endif

#if __CONTENTS(__PET_VISION_AMPLE)
	m_AddedInfo1 = 255;	//1208 wlzzi
	m_AddedInfo2 = 255;	// - default ������ 255��... 
#endif //__PET_VISION_AMPLE

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
PCItemInfo::~PCItemInfo ()
{
	__BEGIN_TRY

	while (!m_SubItemInfoList.empty()) 
	{
		SubItemInfo* pSubItemInfo = m_SubItemInfoList.front();
		delete pSubItemInfo;
		m_SubItemInfoList.pop_front();
	}

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void PCItemInfo::read ( SocketInputStream & iStream )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_IClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );

	m_OptionType.clear();
	for (int i = 0; i < optionSize; i++) 
	{
		OptionType_t optionType;
		iStream.read( optionType );
		m_OptionType.push_back( optionType );
	}

	iStream.read( m_Durability );
	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_EnchantLevel );
	iStream.read( m_ItemNum );
	iStream.read( m_MainColor );
	iStream.read( m_ListNum );

	for (int j = 0; j < m_ListNum; j++)
	{
		SubItemInfo* pSubItemInfo = new SubItemInfo();
		pSubItemInfo->read(iStream);
		m_SubItemInfoList.push_back( pSubItemInfo );
	}
	BYTE thirdOptionSize;
	iStream.read( thirdOptionSize );
//20071009 by diesirace ��������ۿɼ� �߰� 
	m_ThirdOptionType.clear();
	for (int thirdindex = 0; thirdindex < thirdOptionSize; thirdindex++) 
	{
		OptionType_t optionType;
		iStream.read( optionType );
		m_ThirdOptionType.push_back( optionType );
	}

	iStream.read( m_ThirdEnchantType );
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	iStream.read(m_CashItem);
#endif

#if __CONTENTS(__PET_VISION_AMPLE)
	iStream.read(m_AddedInfo1);
	iStream.read(m_AddedInfo2);
#endif //__PET_VISION_AMPLE
#if __CONTENTS(__PET_MIXINGFORGE)
	BYTE mixOptionSize;
	iStream.read( mixOptionSize );

	m_MixOptionType.clear();

	for ( int k=0; k < mixOptionSize ; ++k )
	{
		OptionType_t mixOptionType;
		iStream.read( mixOptionType );
		m_MixOptionType.push_back( mixOptionType );
	}
#endif //__PET_MIXINGFORGE
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void PCItemInfo::write ( SocketOutputStream & oStream ) const
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_IClass );
	oStream.write( m_ItemType );

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );

	std::list<OptionType_t>::const_iterator iOption = m_OptionType.begin();
    for (; iOption!= m_OptionType.end(); iOption++) 
	{
		OptionType_t optionType = *iOption;
		oStream.write( optionType );
	}

	oStream.write( m_Durability );
	oStream.write( m_Silver );
	oStream.write( m_Grade);
	oStream.write( m_EnchantLevel );
	oStream.write( m_ItemNum );
	oStream.write( m_MainColor );
	oStream.write( m_ListNum );

	std::list<SubItemInfo*>::const_iterator itr = m_SubItemInfoList.begin();
    for (; itr!= m_SubItemInfoList.end(); itr++) 
		(*itr)->write(oStream);

	//20071009 by diesirace ��������ۿɼ� �߰� 
	BYTE thirdOptionSize = m_ThirdOptionType.size();
	oStream.write( thirdOptionSize );

	std::list<OptionType_t>::const_iterator iThirdOption = m_ThirdOptionType.begin();
    for (; iThirdOption!= m_ThirdOptionType.end(); iThirdOption++) 
	{
		OptionType_t optionType = *iThirdOption;
		oStream.write( optionType );
	}
	oStream.write( m_ThirdEnchantType );
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	oStream.write(m_CashItem);
#endif

#if __CONTENTS(__PET_VISION_AMPLE)
	oStream.write(m_AddedInfo1);
	oStream.write(m_AddedInfo2);
#endif //__PET_VISION_AMPLE
#if __CONTENTS(__PET_MIXINGFORGE)
	BYTE mixOptionSize = m_MixOptionType.size();
	oStream.write( mixOptionSize );
	std::list<OptionType_t>::const_iterator mixitr = m_MixOptionType.begin();
	for (; mixitr!=m_MixOptionType.end(); mixitr++)
	{
		OptionType_t mixOptionType = *mixitr;
		oStream.write( mixOptionType );
	}
#endif //__PET_MIXINGFORGE
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__	
//////////////////////////////////////////////////////////////////////////////
// debug string
//////////////////////////////////////////////////////////////////////////////
std::string PCItemInfo::toString() const

{
	StringStream msg;
	msg << "PCItemInfo("
		<< "ObjectID:"	<< (int)m_ObjectID
		<< "ItemClass:"	<< (int)m_IClass
		<< "ItemType:"	<< (int)m_ItemType
		<< "OptionTypeSize:"<< (int)m_OptionType.size()
		<< "Durability:"	<< (int)m_Durability
		<< "Silver:"	<< (int)m_Silver
		<< "Grade:"		<< (int)m_Grade
		<< "EnchantLevel:" << (int)m_EnchantLevel
		<< "ItemNum:"	<< (int)m_ItemNum
		<< "MainColor:" << (int)m_MainColor
		<< "ListNum:"	<< (int)m_ListNum
		<< "ThirdOptionTypeSize:"	<< (int)m_ThirdOptionType.size()
		<< "ThirdEnchantType"		<<	(int)m_ThirdEnchantType;
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
		msg << "CashItem"	<< (int)m_CashItem;
#endif

#if __CONTENTS(__PET_VISION_AMPLE)
		msg << "AddedInfo1"	<< (int)m_AddedInfo1
		<< "AddedInfo2"	<< (int)m_AddedInfo2;
#endif //__PET_VISION_AMPLE
#if __CONTENTS(__PET_MIXINGFORGE)
		msg << ", MixOptions : (";

		std::list<OptionType_t>::const_iterator mixitr = m_MixOptionType.begin();
		std::list<OptionType_t>::const_iterator mixendItr = m_MixOptionType.end();

		for ( ; mixitr != mixendItr ; ++mixitr )
		{
			msg << *mixitr << ", ";
		}
#endif //__PET_MIXINGFORGE
		msg << ")";
	return msg.toString();
}
#endif