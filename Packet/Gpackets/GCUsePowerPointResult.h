//--------------------------------------------------------------------------------
// 
// Filename    : GCUsePowerPointResult.h 
// Written By  : bezz
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_USE_POWER_POINT_RESULT_H__
#define __GC_USE_POWER_POINT_RESULT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResult;
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResult : public Packet
{
public:

	enum RESULT_CODE
	{
		_NO_ERROR = 0,
		NOT_ENOUGH_POWER_POINT,		// �Ŀ� ����Ʈ�� �����մϴ�.
		NOT_ENOUGH_INVENTORY_SPACE	// �κ��丮�� ������ �����մϴ�.
	};

	enum ITEM_CODE
	{
		CANDY = 0,				// ���� 1�� 
		RESURRECTION_SCROLL,	// ��Ȱ ��ũ�� 1��
		ELIXIR_SCROLL,			// ������ ��ũ�� 1��
		MEGAPHONE,				// Ȯ���� 30��
		NAMING_PEN,				// ���̹� �� 1��
		SIGNPOST,				// �˸��� 6�ð�
		BLACK_RICE_CAKE_SOUP	// ���� ���� 1��
	};

public:
	GCUsePowerPointResult();
	~GCUsePowerPointResult();

public :
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_USE_POWER_POINT_RESULT; }
	
	// get packet's body size
	size_t getPacketSize() const { return szBYTE + szBYTE + szDWORD; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "GCUsePowerPointResult"; }
	
	// get packet's debug string
	string toString() const;
#endif
	// get / set Error Code
	BYTE getErrorCode() const { return m_ErrorCode; }
	void setErrorCode( BYTE errorcode ) { m_ErrorCode = errorcode; }

	// get / set Item Code
	BYTE getItemCode() const { return m_ItemCode; }
	void setItemCode( BYTE itemcode ) { m_ItemCode = itemcode; }

	// get / set Power Point
	uint getPowerPoint() const { return m_PowerPoint; }
	void setPowerPoint( BYTE powerpoint ) { m_PowerPoint = powerpoint; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :
	// ���� �ڵ�
	BYTE	m_ErrorCode;

	// ������ �ڵ�
	BYTE	m_ItemCode;

	// �Ŀ� ����Ʈ
	uint	m_PowerPoint;
};


//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResultFactory;
//
// Factory for GCUsePowerPointResult
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResultFactory : public PacketFactory
{
public :
	// create packet
	Packet* createPacket() { return new GCUsePowerPointResult(); }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const { return "GCUsePowerPointResult"; }
#endif
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_USE_POWER_POINT_RESULT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUsePowerPointResultPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const { return szBYTE + szBYTE + szDWORD; }
};



//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResultHandler;
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResultHandler
{
public :
	// execute packet's handler
	static void execute(GCUsePowerPointResult* pPacket, Player* pPlayer);
};

#endif

