//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampire.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_VAMPIRE_H__
#define __GC_ADD_VAMPIRE_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampire;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ�
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampire ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampire��
// ��Ƽ� �ް� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class GCAddVampire : public Packet 
{
public:
	GCAddVampire() : m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	GCAddVampire(const PCVampireInfo3 & vampireInfo) : m_VampireInfo(vampireInfo), m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	virtual ~GCAddVampire();
	
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const { return PACKET_GC_ADD_VAMPIRE; }
	size_t getPacketSize() const
	{
		PacketSize_t ret = m_VampireInfo.getSize() + m_pEffectInfo->getSize() + ((m_pPetInfo!=NULL)?m_pPetInfo->getSize():szPetType) + szBYTE;

		if ( m_pNicknameInfo == NULL )
		{
			NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			ret += noNick.getSize();
		}
		else
		{
			ret += m_pNicknameInfo->getSize();
		}

		ret += m_StoreOutlook.getSize();

		return ret;
	}
#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCAddVampire"; }
	string toString() const;
#endif
public:
	PCVampireInfo3 & getVampireInfo() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) { m_VampireInfo = vampireInfo; }

	EffectInfo* getEffectInfo() const { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo() const { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo() const { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

	BYTE getFromFlag(void) const { return m_FromFlag; }
	void setFromFlag(BYTE flag) { m_FromFlag = flag; }

private:
	PCVampireInfo3 m_VampireInfo; // �����̾� �ܸ� ����
	EffectInfo*    m_pEffectInfo; // ����Ʈ ����
	PetInfo*	   m_pPetInfo;	  // �� ����
	NicknameInfo*	   m_pNicknameInfo;	  // �� ����
	StoreOutlook		m_StoreOutlook;	// ���λ��� ����
	BYTE           m_FromFlag;    // ���κ����ΰ�? ������ ��쿡�� 0, ��Ż�� ������ ��쿡�� 1
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireFactory : public PacketFactory 
{
public:
	Packet* createPacket() { return new GCAddVampire(); }
#ifdef __DEBUG_OUTPUT__
	string getPacketName() const { return "GCAddVampire"; }
#endif
	PacketID_t getPacketID() const { return Packet::PACKET_GC_ADD_VAMPIRE; }
	PacketSize_t getPacketMaxSize() const { return PCVampireInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize() + szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireHandler 
{
public:
	static void execute(GCAddVampire* pPacket, Player* pPlayer);

};

#endif
