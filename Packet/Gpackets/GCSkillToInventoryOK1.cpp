//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "ServerSkillDisplay.h"
#include "GCSkillToInventoryOK1.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::GCSkillToInventoryOK1 () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::~GCSkillToInventoryOK1 () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_SkillType ); m_SkillType = static_cast<decltype(m_SkillType)>(TranslateServerSkillType(m_SkillType));
	iStream.read( m_ObjectID );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	iStream.read( m_ItemClass );
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	iStream.read( m_ItemType );
	iStream.read( m_CEffectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Duration );

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	oStream.write( m_ItemClass );
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	oStream.write( m_ItemType );
	oStream.write( m_CEffectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Duration );
	ModifyInfo::write( oStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSkillToInventoryOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCSkillToInventoryOK1::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCSkillToInventoryOK1(SkillType: " << (int)m_SkillType 
			<< ",ObjectID: " << (int)m_ObjectID
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
			<< ",ItemClass: " << (int)m_ItemClass
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
			<< ",ItemType: " << (int)m_ItemType
			<< ",CEffectID: " << (int)m_CEffectID 
			<< ",X: "  << (int)m_X
			<< ",Y: " << (int)m_Y 
			<< ",Duration: " << (int)m_Duration;

		msg << ModifyInfo::toString();

		msg << ")";

		return msg.toString();

		__END_CATCH
	}
#endif
