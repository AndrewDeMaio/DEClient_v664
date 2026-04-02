//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToSelfOK3.h 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� �� ����� ����������, ��� �����ڸ� �� �� ���� ���
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_SELF_OK_3_H__
#define __GC_SKILL_TO_SELF_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3;
//
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3 : public Packet {

public :
	
	// constructor
	GCSkillToSelfOK3();
	
	// destructor
	~GCSkillToSelfOK3();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const;

	// execute packet's handler
	void execute(Player* pPlayer);

	// get packet id
	PacketID_t getPacketID() const { return PACKET_GC_SKILL_TO_SELF_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	size_t getPacketSize() const { return szCoord*2 + szSkillType + szDuration + szBYTE; }

#ifdef __DEBUG_OUTPUT__
	// get packet's name
	std::string getPacketName() const { return "GCSkillToSelfOK3"; }
	
	// get packet's debug string
	std::string toString() const;

#endif

	// get / set X,Y
	Coord_t getX() const { return m_X;}
	Coord_t getY() const { return m_Y;}
	void setXY(Coord_t X, Coord_t Y) { m_X = X; m_Y = Y;}


	// get / set SkillType
	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration() const { return m_Duration; }
	void setDuration(Duration_t Duration) { m_Duration = Duration; }

	BYTE getGrade() const { return m_Grade; }
	void setGrade( BYTE grade ) { m_Grade = grade; }

private :
	
	// X,Y
	Coord_t m_X, m_Y;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3Factory;
//
// Factory for GCSkillToSelfOK3
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToSelfOK3Factory() {}
	
	// destructor
	virtual ~GCSkillToSelfOK3Factory() {}

	
public :
	
	// create packet
	Packet* createPacket() { return new GCSkillToSelfOK3(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const { return "GCSkillToSelfOK3"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const { return Packet::PACKET_GC_SKILL_TO_SELF_OK_3; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const { return szCoord*2 + szSkillType + szDuration + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK3Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToSelfOK3* pGCSkillToSelfOK3, Player* pPlayer);

};

#endif
