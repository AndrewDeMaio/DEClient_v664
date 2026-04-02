//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMakeItemOK.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MAKE_ITEM_OK_H__
#define __GC_MAKE_ITEM_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "GCChangeInventoryItemNum.h"
#include "GCAddItemToInventory.h"
#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOK;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOK : public GCChangeInventoryItemNum, public GCAddItemToInventory, public ModifyInfo {

public :
	
	// constructor
	GCMakeItemOK ();
	
	// destructor
	~GCMakeItemOK ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_MAKE_ITEM_OK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize () const { return GCChangeInventoryItemNum::getPacketSize() 
		+ GCAddItemToInventory::getPacketSize()
		+ ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCMakeItemOK"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif

private :

};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOKFactory;
//
// Factory for GCMakeItemOK
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOKFactory : public PacketFactory {

public :
	
	// constructor
	GCMakeItemOKFactory () {}
	
	// destructor
	virtual ~GCMakeItemOKFactory () {}

	
public :
	
	// create packet
	Packet * createPacket () { return new GCMakeItemOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCMakeItemOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_MAKE_ITEM_OK; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize() const { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE * m_ListNum * 2 ; }
	PacketSize_t getPacketMaxSize() const { return  255 + 255 + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOKHandler {

public :

	// execute packet's handler
	static void execute ( GCMakeItemOK * pGCMakeItemOK , Player * pPlayer );

};

#endif
