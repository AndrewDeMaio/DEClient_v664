//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK4.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#include "GCKnocksTargetBackOK4.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK4::GCKnocksTargetBackOK4 ()
{
	__BEGIN_TRY

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK4::~GCKnocksTargetBackOK4 ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK4::read ( SocketInputStream & iStream )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
//	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
//	iStream.read( m_X);
//	iStream.read( m_Y );
//	iStream.read( m_bSuccess);

	iStream.read( m_SkillType);
	iStream.read( m_dir );
	iStream.read( m_X );
	iStream.read( m_Y );
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK4::write ( SocketOutputStream & oStream )
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
//	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
//	oStream.write( m_X);
//	oStream.write( m_Y);
//	oStream.write( m_bSuccess);

	oStream.write( m_SkillType);
	oStream.write( m_dir );
	oStream.write( m_X );
	oStream.write( m_Y );
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK4::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCKnocksTargetBackOK4Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCKnocksTargetBackOK4::toString () 
		const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCKnocksTargetBackOK4(TargetObjectID: " << (int)m_TargetObjectID 
			<< "(Dir,X,Y): "<<(int)m_dir<<(int)m_X<<(int)m_Y
	//		<< ",Success: "<< m_bSuccess
	//		<< ",TargetXY: " << (int)m_X<<","<<(int)m_Y
			<< ")";

		return msg.toString();

		__END_CATCH
	}
#endif