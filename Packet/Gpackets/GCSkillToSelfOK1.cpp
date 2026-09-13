//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToSelfOK1.cpp 
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
#include "GCSkillToSelfOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToSelfOK1::GCSkillToSelfOK1 () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToSelfOK1::~GCSkillToSelfOK1 () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK1::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_SkillType ); m_SkillType = static_cast<decltype(m_SkillType)>(TranslateServerSkillType(m_SkillType));
	iStream.read( m_CEffectID );
	iStream.read( m_Duration );
	iStream.read( m_Grade );

	ModifyInfo::read( iStream);
	

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK1::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_CEffectID );
	oStream.write( m_Duration );
	oStream.write( m_Grade );

	ModifyInfo::write( oStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK1::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCSkillToSelfOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
std::string GCSkillToSelfOK1::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToSelfOK1("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",Duration:" << (int)m_Duration
		<< ",Grade:" << (int)m_Grade;
	msg << ModifyInfo::toString();
	msg << ")";
	return msg.toString();

	__END_CATCH
}
#endif