//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK6.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "GPacket_PCH.h"
#include "GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////

GCSkillToObjectOK6::GCSkillToObjectOK6 () 
{
	__BEGIN_TRY
	m_Grade			= 0;
	m_ActionStep	= 0;
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////

GCSkillToObjectOK6::~GCSkillToObjectOK6 () 
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////

void GCSkillToObjectOK6::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_X);
	iStream.read( m_Y);
	iStream.read( m_SkillType );
	iStream.read( m_Duration );
	iStream.read( m_Grade );
	iStream.read( m_ActionStep );
	ModifyInfo::read( iStream );
	__END_CATCH
}
	    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////

void GCSkillToObjectOK6::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_X);
	oStream.write( m_Y);
	oStream.write( m_SkillType );
	oStream.write( m_Duration );
	oStream.write( m_Grade );
	oStream.write( m_ActionStep );
	ModifyInfo::write( oStream );
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////

void GCSkillToObjectOK6::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
	GCSkillToObjectOK6Handler::execute( this , pPlayer );
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
string GCSkillToObjectOK6::toString () 
	const
{
	__BEGIN_TRY
	StringStream msg;
	msg << "GCSkillToObjectOK6("
		<< "SkillType:" << (int)m_SkillType 
		<< ",X,Y: " << (int)m_X << "," << (int)m_Y 
		<< ",Duration:" << (int)m_Duration
		<< ",Grade:" << (int)m_Grade
		<< ",ActionStep:" << (int)m_ActionStep;
	msg << ModifyInfo::toString();
	msg << ")";
	return msg.toString();
	__END_CATCH
}

#endif 



