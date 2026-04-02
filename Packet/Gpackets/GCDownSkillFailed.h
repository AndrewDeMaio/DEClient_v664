//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCDownSkillFailed.h 
// Written By  :  elca@ewestsoft.com
// Description :  
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DOWN_SKILL_FAILED_H__
#define __GC_DOWN_SKILL_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailed;
//
//////////////////////////////////////////////////////////////////////

class GCDownSkillFailed : public Packet 
{

public: 

	GCDownSkillFailed();
	virtual ~GCDownSkillFailed();

	
public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream);
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_DOWN_SKILL_FAILED; }
	
	// get packet size
	size_t getPacketSize() const { return szSkillType+szBYTE; }

#ifdef __DEBUG_OUTPUT__
	// get packet's name
	std::string getPacketName() const { return "GCDownSkillFailed"; }
	
	// get packet's debug string
	std::string toString() const;
#endif
	
	// get/set skill type
	SkillType_t getSkillType(void) const { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) { m_SkillType = SkillType; }

	// get/set description
	BYTE getDesc(void) const { return m_Desc;}
	void setDesc(BYTE desc) { m_Desc = desc;}

private:

	SkillType_t m_SkillType;
	BYTE        m_Desc;       // ����� ���� �� ������ �����̴�.
	                          // �ڼ��� ������ CGDownSkillHandler�� �����ϵ���.

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailedFactory;
//
// Factory for  GCDownSkillFailed
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillFailedFactory : public PacketFactory {

public :
	
	// constructor
	 GCDownSkillFailedFactory() {}
	
	// destructor
	virtual ~GCDownSkillFailedFactory() {}

	
public :
	
	// create packet
	Packet* createPacket() { return new GCDownSkillFailed(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCDownSkillFailed"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_DOWN_SKILL_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szSkillType+szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillFailedHandler {

public :

	// execute packet's handler
	static void execute( GCDownSkillFailed* pGCDownSkillFailed, Player* pPlayer);

};

#endif	// __GC_DOWN_SKILL_FAILED_H__
