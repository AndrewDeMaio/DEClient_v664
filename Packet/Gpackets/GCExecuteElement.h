//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExecuteElement.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_EXECUTE_ELEMENT_H__
#define __GC_EXECUTE_ELEMENT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElement;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElement : public Packet 
{
public:
	GCExecuteElement();
	~GCExecuteElement();
	
public:
    void read(SocketInputStream & iStream) { iStream.read(m_dwQuestID); iStream.read(m_Condition); iStream.read(m_Index); }
    void write(SocketOutputStream & oStream) const { oStream.write(m_dwQuestID); oStream.write(m_Condition); oStream.write(m_Index); }
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_EXECUTE_ELEMENT; }
	size_t getPacketSize() const { return szDWORD + szBYTE + szWORD; }
#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCExecuteElement"; }
	string toString() const;
#endif
public:
	BYTE	getCondition() const { return m_Condition; }
	void	setCondition(BYTE cond) { m_Condition = cond; }

	WORD	getQuestID() const { return m_dwQuestID; }

	WORD	getIndex() const { return m_Index; }
	void	setIndex(WORD idx) { m_Index = idx; }

private:
	DWORD	m_dwQuestID;	// ����Ʈ ID
	BYTE	m_Condition;	// ��� ���ǿ� �ִ°� 0 : Happen, 1 : Complete, 2 : Fail, 3 : Reward
	WORD	m_Index;		// �ش� ������ ���° element�ΰ�
};


//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElementFactory;
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElementFactory : public PacketFactory 
{
public :
	GCExecuteElementFactory() {}
	virtual ~GCExecuteElementFactory() {}
	
public:
	Packet* createPacket() { return new GCExecuteElement(); }
#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCExecuteElement"; }
#endif
	PacketID_t getPacketID() const { return Packet::PACKET_GC_EXECUTE_ELEMENT; }
	PacketSize_t getPacketMaxSize() const { return szDWORD + szBYTE + szWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElementHandler;
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElementHandler 
{
public:
	static void execute(GCExecuteElement* pGCExecuteElement, Player* pPlayer);

};

#endif
