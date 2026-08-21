//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventory.cpp 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
#include "Packet_PCH.h"
#include "CGUseItemFromInventory.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"

CGUseItemFromInventory::CGUseItemFromInventory () 
{
	__BEGIN_TRY

	m_InventoryItemObjectID = 0;
	
	__END_CATCH
}
	
CGUseItemFromInventory::~CGUseItemFromInventory () 
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUseItemFromInventory::read (SocketInputStream & iStream) 
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_InventoryItemObjectID),
							pEIStream->readEncrypt(m_InvenX),
							pEIStream->readEncrypt(m_InvenY));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_InventoryItemObjectID);
		iStream.read(m_InvenX);
		iStream.read(m_InvenY);
	}

	__END_CATCH
}
		    
void CGUseItemFromInventory::write (SocketOutputStream & oStream) const 
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_InventoryItemObjectID),
							pEOStream->writeEncrypt(m_InvenX),
							pEOStream->writeEncrypt(m_InvenY));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_InventoryItemObjectID);
		oStream.write(m_InvenX);
		oStream.write(m_InvenY);
	}

	__END_CATCH
}

void CGUseItemFromInventory::execute (Player* pPlayer) 
{
	__BEGIN_TRY

#ifndef __GAME_CLIENT__
	CGUseItemFromInventoryHandler::execute (this , pPlayer);
#endif
	
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
std::string CGUseItemFromInventory::toString () 
	const
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseItemFromInventory("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",InvenX:" << (int)m_InvenX
		<< ",InvenY:" << (int)m_InvenY
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif