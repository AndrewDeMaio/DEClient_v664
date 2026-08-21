//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddNPC.cc 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GPacket_PCH.h"
#include "GCAddNPC.h"

//////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////
GCAddNPC::GCAddNPC()
{
	__BEGIN_TRY

	m_pEffectInfo = NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////
GCAddNPC::~GCAddNPC()
{
	__BEGIN_TRY

	delete m_pEffectInfo;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddNPC::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	
	int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
	localLongName = 12;
#endif //__LOCALIZING_LONGNAME
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );

	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 + localLongName)
		throw InvalidProtocolException("too large name length");
		
	iStream.read( m_Name , szName );
	iStream.read( m_NPCID );

	iStream.read( m_SpriteType );

	iStream.read( m_MainColor );
	iStream.read( m_SubColor );

	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );

	//�޳ױ׷ν� ������ ���ǽÿ� ����Ʈ�� ���̸鼭 ó���� ��Ȯ�ϱ� ���ؼ�...
#if __CONTENTS(__MENEGROTH)
	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );
#endif //__MENEGROTH
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddNPC::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY
	int localLongName = 0;
#if __CONTENTS(__LOCALIZING_LONGNAME)
	localLongName = 12;
#endif //__LOCALIZING_LONGNAME
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );

	BYTE szName = (BYTE)m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 + localLongName)
		throw InvalidProtocolException("too large name length");

	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_NPCID );

	oStream.write( m_SpriteType );

	oStream.write( m_MainColor );
	oStream.write( m_SubColor );

	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );


#if __CONTENTS(__MENEGROTH)	
	m_pEffectInfo->write( oStream );
#endif //__MENEGROTH

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddNPC::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCAddNPCHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAddNPC::toString () const
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAddNPC("
			<< "ObjectID:" << m_ObjectID 
			<< ",Name:" << m_Name 
			<< ",NPCID:" << m_NPCID
			<< ",SpriteType:" << m_SpriteType
			<< ",MainColor:" << m_MainColor
			<< ",SubColor:" << m_SubColor
			<< ",X:" << (int)m_X 
			<< ",Y:" << (int)m_Y 
			<< ",Dir: " << (int)m_Dir 
#if __CONTENTS(__MENEGROTH)
			<< ",EffectInfo: " << (int)m_pEffectInfo
#endif //__MENEGROTH
			<< ")" ;

		return msg.toString();

		__END_CATCH
	}
#endif

