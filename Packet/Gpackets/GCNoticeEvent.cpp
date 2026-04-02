//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNoticeEvent.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCNoticeEvent.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCNoticeEvent::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NOTICE_EVENT_MASTER_COMBAT_TIME :
		case NOTICE_EVENT_KICK_OUT_FROM_ZONE :
		case NOTICE_EVENT_CONTINUAL_GROUND_ATTACK :
		case NOTICE_EVENT_METEOR_STRIKE :
		case NOTICE_EVENT_SHOP_TAX_CHANGE :
		case NOTICE_EVENT_WAR_OVER :
		case NOTICE_EVENT_RESULT_LOTTERY :
		case NOTICE_EVENT_MASTER_LAIR_OPEN :
		case NOTICE_EVENT_MASTER_LAIR_CLOSED :
		case NOTICE_EVENT_MASTER_LAIR_COUNT :
		case NOTICE_EVENT_MINI_GAME:
		case NOTICE_EVENT_FLAG_WAR_FINISH:
		case NOTICE_EVENT_LEVEL_WAR_ARRANGED :            // �� ������ ������ ���۵˴ϴ�.
		case NOTICE_EVENT_LEVEL_WAR_STARTED :             // ������ ������ ���۵Ǿ����ϴ�.
		case NOTICE_EVENT_RACE_WAR_SOON:
		case NOTICE_EVENT_ENTER_BEGINNER_ZONE:
		case NOTICE_EVENT_FLAG_WAR_READY:
		case NOTICE_EVENT_LOGIN_JUST_NOW:
		case NOTICE_EVENT_HOLYDAY:
		case NOTICE_EVENT_GOLD_MEDALS:
		case NOTICE_EVENT_CROWN_PRICE:
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
void GCNoticeEvent::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NOTICE_EVENT_MASTER_COMBAT_TIME :
		case NOTICE_EVENT_KICK_OUT_FROM_ZONE :
		case NOTICE_EVENT_CONTINUAL_GROUND_ATTACK :
		case NOTICE_EVENT_METEOR_STRIKE :
		case NOTICE_EVENT_SHOP_TAX_CHANGE :
		case NOTICE_EVENT_WAR_OVER :
		case NOTICE_EVENT_RESULT_LOTTERY :
		case NOTICE_EVENT_MASTER_LAIR_OPEN :
		case NOTICE_EVENT_MASTER_LAIR_CLOSED :
		case NOTICE_EVENT_MASTER_LAIR_COUNT :
		case NOTICE_EVENT_MINI_GAME:
		case NOTICE_EVENT_FLAG_WAR_FINISH:
		case NOTICE_EVENT_LEVEL_WAR_ARRANGED :            // �� ������ ������ ���۵˴ϴ�.
		case NOTICE_EVENT_LEVEL_WAR_STARTED :             // ������ ������ ���۵Ǿ����ϴ�.
		case NOTICE_EVENT_RACE_WAR_SOON:
		case NOTICE_EVENT_ENTER_BEGINNER_ZONE:
		case NOTICE_EVENT_FLAG_WAR_READY:
		case NOTICE_EVENT_LOGIN_JUST_NOW:
		case NOTICE_EVENT_HOLYDAY:
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
void GCNoticeEvent::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCNoticeEventHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��Ŷ ������
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCNoticeEvent::getPacketSize () const  
{
	__BEGIN_TRY

	PacketSize_t size = szWORD;

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case NOTICE_EVENT_MASTER_COMBAT_TIME :
		case NOTICE_EVENT_KICK_OUT_FROM_ZONE :
		case NOTICE_EVENT_CONTINUAL_GROUND_ATTACK :
		case NOTICE_EVENT_METEOR_STRIKE :
		case NOTICE_EVENT_SHOP_TAX_CHANGE :
		case NOTICE_EVENT_WAR_OVER :
		case NOTICE_EVENT_RESULT_LOTTERY :
		case NOTICE_EVENT_MASTER_LAIR_OPEN :
		case NOTICE_EVENT_MASTER_LAIR_CLOSED :
		case NOTICE_EVENT_MASTER_LAIR_COUNT :
		case NOTICE_EVENT_MINI_GAME:
		case NOTICE_EVENT_FLAG_WAR_FINISH:
		case NOTICE_EVENT_LEVEL_WAR_ARRANGED :            // �� ������ ������ ���۵˴ϴ�.
		case NOTICE_EVENT_LEVEL_WAR_STARTED :             // ������ ������ ���۵Ǿ����ϴ�.
		case NOTICE_EVENT_RACE_WAR_SOON:
		case NOTICE_EVENT_ENTER_BEGINNER_ZONE:
		case NOTICE_EVENT_FLAG_WAR_READY:
		case NOTICE_EVENT_LOGIN_JUST_NOW:
		case NOTICE_EVENT_HOLYDAY:
			//		case NOTICE_EVENT_RACE_WAR_TODAY:
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
std::string GCNoticeEvent::toString () const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCNoticeEvent(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
#endif