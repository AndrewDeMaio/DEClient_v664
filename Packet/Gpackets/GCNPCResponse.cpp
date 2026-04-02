//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCResponse.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCNPCResponse.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY :
		case NPC_RESPONSE_SHOW_TAX_RATIO :
		case NPC_RESPONSE_SHOW_DONATION_DAILOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
		case NPC_RESPONSE_GIVE_GAMBLE_ITEM_OK:
		case NPC_RESPONSE_CHECK_COUNT_ATTEND:
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		case NPC_RESPONSE_BLITZ_COUPON:					// ���������� ���� ���� ����
		case NPC_RESPONSE_REWORD_ITEM_OK:				// ������ ����� �����۸����� �����ִ� ���̾�α׶�ﶧ
#endif //__BLITZ_COUPON_EVENT
			iStream.read(m_Parameter);
			break;
		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		default:
			break;
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY :
		case NPC_RESPONSE_SHOW_TAX_RATIO :
		case NPC_RESPONSE_SHOW_DONATION_DAILOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
		case NPC_RESPONSE_GIVE_GAMBLE_ITEM_OK:
		case NPC_RESPONSE_CHECK_COUNT_ATTEND:
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		case NPC_RESPONSE_BLITZ_COUPON:					// ���������� ���� ���� ����
		case NPC_RESPONSE_REWORD_ITEM_OK:				// ������ ����� �����۸����� �����ִ� ���̾�α׶�ﶧ
#endif //__BLITZ_COUPON_EVENT
			oStream.write(m_Parameter);
			break;
		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		default:
			break;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCNPCResponseHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��Ŷ ������
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCNPCResponse::getPacketSize () const  
{
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY :
        case NPC_RESPONSE_SHOW_TAX_RATIO :
		case NPC_RESPONSE_SHOW_DONATION_DAILOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
		case NPC_RESPONSE_GIVE_GAMBLE_ITEM_OK:
		case NPC_RESPONSE_CHECK_COUNT_ATTEND:
#if __CONTENTS(__BLITZ_COUPON_EVENT)
		case NPC_RESPONSE_BLITZ_COUPON:					// ���������� ���� ���� ����
		case NPC_RESPONSE_REWORD_ITEM_OK:				// ������ ����� �����۸����� �����ִ� ���̾�α׶�ﶧ
#endif //__BLITZ_COUPON_EVENT
			size += szuint;
			break;
		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
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
std::string GCNPCResponse::toString () const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCNPCResponse(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
#endif