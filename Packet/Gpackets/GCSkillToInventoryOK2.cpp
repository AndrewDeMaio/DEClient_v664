//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK2.cpp 
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
#include "GCSkillToInventoryOK2.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK2::GCSkillToInventoryOK2 () 
{
	__BEGIN_TRY

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK2::~GCSkillToInventoryOK2 () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK2::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_SkillType ); m_SkillType = static_cast<decltype(m_SkillType)>(TranslateServerSkillType(m_SkillType));
	iStream.read( m_Duration );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK2::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_Duration );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCSkillToInventoryOK2::execute()
// 
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK2::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSkillToInventoryOK2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCSkillToInventoryOK2::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCSkillToInventoryOK2(SkillType:" << (int)m_SkillType 
			<< ",ObjectID:" << (int)m_ObjectID
			<< ",Duration: " << (int)m_Duration 
			<< ")";

		return msg.toString();

		__END_CATCH
	}

#endif
