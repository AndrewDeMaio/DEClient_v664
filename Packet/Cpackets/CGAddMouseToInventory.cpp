//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddMouseToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Packet_PCH.h"
#include "CGAddMouseToInventory.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGAddMouseToInventory::CGAddMouseToInventory () 
{
	__BEGIN_TRY
	m_InventoryItemObjectID = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGAddMouseToInventory::~CGAddMouseToInventory () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGAddMouseToInventory::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read(m_InventoryItemObjectID);
	iStream.read( m_InvenX );
	iStream.read( m_InvenY );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CGAddMouseToInventory::write ( SocketOutputStream & oStream ) const 
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write(m_InventoryItemObjectID);
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGAddMouseToInventory::execute ( Player * pPlayer ) 
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGAddMouseToInventoryHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGAddMouseToInventory::toString () 
		const
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CGAddMouseToInventory( ObjectID : " << (int)m_ObjectID << ", InventoryX : " << (int)m_InvenX << ", InventoryY : " << (int)m_InvenY << ")";
		return msg.toString();

		__END_CATCH
	}

	// global variable definition
	//CGAddMouseToInventoryFactory g_CGAddMouseToInventoryFactory;
#endif
