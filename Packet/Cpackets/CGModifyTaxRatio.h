//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyTaxRatio.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_TAX_RATIO_H__
#define __CG_MODIFY_TAX_RATIO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatio;
//
//////////////////////////////////////////////////////////////////////

class CGModifyTaxRatio : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_CG_MODIFY_TAX_RATIO; }
	
	// get packet's body size
	size_t getPacketSize() const { return szuint; }
#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "CGModifyTaxRatio"; }

	// get packet's debug string
	std::string toString() const;
#endif
	// get/set Ratio
	uint getRatio() const { return m_Ratio; }
	void setRatio( uint ratio ) { m_Ratio = ratio; }


private :

	uint m_Ratio;
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatioFactory;
//
// Factory for CGModifyTaxRatio
//
//////////////////////////////////////////////////////////////////////

class CGModifyTaxRatioFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyTaxRatioFactory() {}
	
	// destructor
	virtual ~CGModifyTaxRatioFactory() {}

	
public:
	
	// create packet
	Packet* createPacket() { return new CGModifyTaxRatio(); }

	// get packet name
	string getPacketName() const { return "CGModifyTaxRatio"; }
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_CG_MODIFY_TAX_RATIO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szuint; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatioHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGModifyTaxRatioHandler {

public:

	// execute packet's handler
	static void execute(CGModifyTaxRatio* pCGModifyTaxRatio, Player* pPlayer);

};
#endif
#endif
