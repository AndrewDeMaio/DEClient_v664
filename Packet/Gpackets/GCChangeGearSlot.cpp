//-------------------------------------------------------------------------------- // 
// Filename    : GCChangeGearSlot.cpp 
// Written By  : shootkj 
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GPacket_PCH.h"
#include "GCChangeGearSlot.h"
#include "Client.h"
#include "Assert.h"
#if __CONTENTS(__GEAR_SWAP_CHANGE) // GCChangeGearSlot.cpp
//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCChangeGearSlot::GCChangeGearSlot ()
: m_GearSlotID(0), m_pGearInfo(NULL)
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCChangeGearSlot::~GCChangeGearSlot ()
{
	m_GearSlotID	= 0;
	SAFE_DELETE(m_pGearInfo);
}

//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCChangeGearSlot::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	iStream.read(m_GearSlotID);

	m_pGearInfo = new GearInfo();
	m_pGearInfo->read( iStream );
		
	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCChangeGearSlot::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write(m_GearSlotID );

	m_pGearInfo->write( oStream );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCChangeGearSlot::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCChangeGearSlotHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCChangeGearSlot::toString () const
{
	__BEGIN_TRY

//	m_pGearInfo->toString();
		
	StringStream msg;
	msg << "GCChangeGearSlot("
// ��������� ������ ����.
//		<< "GearInfo:" << m_pGearInfo->toString();
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif //__GEAR_SWAP_CHANGE