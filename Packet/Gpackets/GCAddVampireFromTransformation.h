//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireFromTransformation.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_VAMPIRE_FROM_TRANSFORMATION_H__
#define __GC_ADD_VAMPIRE_FROM_TRANSFORMATION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"
#include "EffectInfo.h"

//----------------------------------------------------------------------
//
// class GCAddVampireFromTransformation;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���, (1) �̹� �� �����̾ ���� ������ ���� �ִ�
// (�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���, (2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampireFromTransformation ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����, (3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampireFromTransformation��
// ��Ƽ� �ް� �ȴ�.
//
//----------------------------------------------------------------------

class GCAddVampireFromTransformation : public Packet {

public :

	// constructor
	GCAddVampireFromTransformation () : m_pEffectInfo(NULL) {}
	GCAddVampireFromTransformation ( const PCVampireInfo3 & vampireInfo ) : m_VampireInfo(vampireInfo), m_pEffectInfo(NULL) {}

	virtual ~GCAddVampireFromTransformation();

	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_GC_ADD_VAMPIRE_FROM_TRANSFORMATION; }
	
	// get packet's body size
	size_t getPacketSize () const { return m_VampireInfo.getSize() + m_pEffectInfo->getSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const { return "GCAddVampireFromTransformation"; }
		
		// get packet's debug std::string
		std::string toString () const;
	#endif


public :

	// get/set vampire info
	PCVampireInfo3 & getVampireInfo () { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo () const { return m_VampireInfo; }
	void setVampireInfo ( const PCVampireInfo3 & vampireInfo ) { m_VampireInfo = vampireInfo; }

	// get /set Effect Info
	EffectInfo * getEffectInfo () const { return m_pEffectInfo; }
	void setEffectInfo ( EffectInfo * pEffectInfo ) { m_pEffectInfo = pEffectInfo; }


private :
	
	// �����̾� �ܸ� ����
	PCVampireInfo3 m_VampireInfo;

	// ����Ʈ ����
	EffectInfo * m_pEffectInfo;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddVampireFromTransformationFactory;
//
// Factory for GCAddVampireFromTransformation
//
//--------------------------------------------------------------------------------

class GCAddVampireFromTransformationFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new GCAddVampireFromTransformation(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const { return "GCAddVampireFromTransformation"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_GC_ADD_VAMPIRE_FROM_TRANSFORMATION; }

	// get packet's body size
	PacketSize_t getPacketMaxSize () const
	{ 
		return PCVampireInfo3::getMaxSize() + EffectInfo::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddVampireFromTransformationHandler;
//
//--------------------------------------------------------------------------------

class GCAddVampireFromTransformationHandler {

public :

	// execute packet's handler
	static void execute ( GCAddVampireFromTransformation * pPacket , Player * pPlayer );

};

#endif
