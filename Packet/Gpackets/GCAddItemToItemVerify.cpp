//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCAddItemToItemVerify.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
#if __CONTENTS(__2008_FIRST_CHARGE_ITEM)
		case ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK :					//ũ����Ż ������
#endif	//__2008_FIRST_CHARGE_ITEM
#if __CONTENTS(__TUNING_ITEM)
		case ADD_ITEM_TO_ITEM_VERIFY_TUNING_OK :
#endif	//__TUNING_ITEM
#if __CONTENTS(__IMI_LOW_LEVEL_ITEM)
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DOWN_GRADE:
#endif //__IMI_LOW_LEVEL_ITEM
			iStream.read(m_Parameter);
			break;
		// �����ϸ� ����� ������ 0�̸� ��� ��ȭ�� ���� ��޺�ȭ ���� ���д� �ɼ��� 0
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL:
			{
				iStream.read(m_Grade);
			}
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK:
			{
				BYTE thirdoptionSize;
				iStream.read( thirdoptionSize );
				m_ThirdOptionType.clear();
				
				for (int i = 0; i < thirdoptionSize; i++) 
				{
					OptionType_t thirdoptionType;
					iStream.read( thirdoptionType );
					m_ThirdOptionType.push_back( thirdoptionType );
				}
				iStream.read(m_EnchantClass);
			}
		// �Ķ���͸� ����� �ٸ� �����͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH:
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
			oStream.write(m_Parameter);
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL:
			{
				oStream.write(m_Grade);
			}
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK:
			{
				size_t thirdoptionSize = m_ThirdOptionType.size();
				oStream.write( thirdoptionSize );
				std::list<OptionType_t>::const_iterator iOption = m_ThirdOptionType.begin();
				for (; iOption!= m_ThirdOptionType.end(); iOption++) 
				{
					OptionType_t thirdoptionType = *iOption;
					oStream.write( thirdoptionType );
				}
				oStream.write(m_EnchantClass);
			}
			break;

		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddItemToItemVerifyHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��Ŷ ������
//////////////////////////////////////////////////////////////////////////////

size_t GCAddItemToItemVerify::getPacketSize () const  
{
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
#if __CONTENTS(__IMI_LOW_LEVEL_ITEM)
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_DOWN_GRADE:
#endif //__IMI_LOW_LEVEL_ITEM
			size += szuint;
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL:
			{
				size += szBYTE;
			}
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK:
			{
				size += szBYTE;
				size += m_ThirdOptionType.size();
				size += szBYTE;
			}
			break;
		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	return size;

	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCAddItemToItemVerify::toString () const
{
	__BEGIN_TRY
		
		StringStream msg;
	msg << "GCAddItemToItemVerify(" 
		<< "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
		<< "EnchantClass : " << (int)m_EnchantClass
		<< "Grade : " << (int)m_Grade
		<< ")";
	return msg.toString();
	
	__END_CATCH
}
#endif
