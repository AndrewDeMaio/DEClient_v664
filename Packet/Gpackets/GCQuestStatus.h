//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMonsterKillQuestStatus.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MONSTER_KILL_QUEST_STATUS_H__
#define __GC_MONSTER_KILL_QUEST_STATUS_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatus;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatus : public Packet 
{
public:
	GCQuestStatus();
	~GCQuestStatus();
	
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_QUEST_STATUS; }
	size_t getPacketSize() const { return szWORD + szWORD + szDWORD; }

#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const { return "GCQuestStatus"; }
	std::string toString() const;
#endif

public:
	WORD getQuestID() const { return m_QuestID; }
	void setQuestID(WORD e) { m_QuestID = e; }
	
	WORD getCurrentNum() const { return m_CurrentNum; }
	void setCurrentNul(WORD n) { m_CurrentNum = n; }

	DWORD getRemainTime() const { return m_Time; }
	void setRemainTime(DWORD d) { m_Time = d; }
	
private :
	WORD m_QuestID;
	WORD m_CurrentNum;
	DWORD m_Time;
};


//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatusFactory;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusFactory : public PacketFactory 
{
public :
	GCQuestStatusFactory() {}
	virtual ~GCQuestStatusFactory() {}
	
public:
	Packet* createPacket() { return new GCQuestStatus(); }
#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const { return "GCQuestStatus"; }
#endif
	PacketID_t getPacketID() const { return Packet::PACKET_GC_QUEST_STATUS; }
	PacketSize_t getPacketMaxSize() const { return szWORD + szWORD + szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatusHandler;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusHandler 
{
public:
	static void execute(GCQuestStatus* pGCQuestStatus, Player* pPlayer);

};

#endif
