//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLRegisterPlayer.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_REGISTER_PLAYER_H__
#define __CL_REGISTER_PLAYER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PlayerInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class CLRegisterPlayer;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CLRegisterPlayer : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const;

	// execute packet's handler
	void execute ( Player * pPlayer );

	// get packet id
	PacketID_t getPacketID () const { return PACKET_CL_REGISTER_PLAYER; }
	
	// get packet's body size
	size_t getPacketSize () const
	{
		// ����ȭ�� �̸� ���� ����� ����ϵ��� �Ѵ�.
		return    szBYTE + m_ID.size() 			// ���̵�
				+ szBYTE + m_Password.size() 	// ��ȣ
				+ szBYTE + m_Name.size() 		// �̸�
				+ szBYTE						// ����
				+ szBYTE + m_SSN.size() 		// �ֹε�Ϲ�ȣ
				+ szBYTE + m_Telephone.size() 	// ��ȭ��ȣ
				+ szBYTE + m_Cellular.size() 	// �޴�����ȣ
				+ szBYTE + m_ZipCode.size() 	// ������ȣ
				+ szBYTE + m_Address.size() 	// �ּ�
				+ szBYTE 						// �����ڵ�
				+ szBYTE + m_Email.size() 		// ���ڸ���
				+ szBYTE + m_Homepage.size() 	// Ȩ������
				+ szBYTE + m_Profile.size() 	// �ڱ�Ұ���
				+ szBYTE;						// ��������
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName () const { return "CLRegisterPlayer"; }
	
	// get packet's debug string
	std::string toString () const;
#endif

public :

	//----------------------------------------------------------------------
	// *CAUTION* 
	// �� setXXX()���� �ִ� ���̸� üũ�ؼ� truncate ������, �ּұ��̴� 
	// üũ���� �ʴ´�. �ּ� ���̴� read()/write() ���� üũ�ȴ�. 
	//----------------------------------------------------------------------

    // get/set player's id
	const std::string& getID () const { return m_ID; }
	void setID ( std::string id ) { m_ID = ( id.size() > PlayerInfo::maxIDLength ) ? id.substr(0,PlayerInfo::maxIDLength) : id; }

    // get/set player's password
    const std::string& getPassword () const { return m_Password; }
    void setPassword ( std::string password ) { m_Password = ( password.size() > PlayerInfo::maxPasswordLength ) ? password.substr(0,PlayerInfo::maxPasswordLength) : password; }

    // get/set player's name
    const std::string& getName () const { return m_Name; }
    void setName ( std::string name ) { m_Name = ( name.size() > PlayerInfo::maxNameLength ) ? name.substr(0,PlayerInfo::maxNameLength) : name; }

    // get/set player's sex
    Sex getSex () const { return m_Sex; }
    void setSex ( Sex sex ) { m_Sex = sex; }

    // get/set player's ssn
    const std::string& getSSN () const { return m_SSN; }
    void setSSN ( std::string ssn ) { m_SSN = ( ssn.size() > PlayerInfo::maxSSNLength ) ? ssn.substr(0,PlayerInfo::maxSSNLength) : ssn; }

    // get/set player's telephone
    const std::string& getTelephone () const { return m_Telephone; }
    void setTelephone ( std::string telephone ) { m_Telephone = ( telephone.size() > PlayerInfo::maxTelephoneLength ) ? telephone.substr(0,PlayerInfo::maxTelephoneLength) : telephone; }

    // get/set player's cellular
    const std::string& getCellular () const { return m_Cellular; }
    void setCellular ( std::string cellular ) { m_Cellular = ( cellular.size() > PlayerInfo::maxCellularLength ) ? cellular.substr(0,PlayerInfo::maxCellularLength) : cellular; }

    // get/set player's zipcode
    const std::string& getZipCode () const { return m_ZipCode; }
    void setZipCode ( std::string zipcode ) { m_ZipCode = ( zipcode.size() > PlayerInfo::maxZipCodeLength ) ? zipcode.substr(0,PlayerInfo::maxZipCodeLength) : zipcode; }

    // get/set player's address
    const std::string& getAddress () const { return m_Address; }
    void setAddress ( std::string address ) { m_Address = ( address.size() > PlayerInfo::maxAddressLength ) ? address.substr(0,PlayerInfo::maxAddressLength) : address; }

    // get/set player's nation
    Nation getNation () const { return m_Nation; }
    void setNation ( Nation nation ) { m_Nation = nation; }

    // get/set player's email
    const std::string& getEmail () const { return m_Email; }
    void setEmail ( std::string email ) { m_Email = ( email.size() > PlayerInfo::maxEmailLength ) ? email.substr(0,PlayerInfo::maxEmailLength) : email; }

    // get/set player's homepage
    const std::string& getHomepage () const { return m_Homepage; }
    void setHomepage ( std::string homepage ) { m_Homepage = ( homepage.size() > PlayerInfo::maxHomepageLength ) ? homepage.substr(0,PlayerInfo::maxHomepageLength) : homepage; }

    // get/set player's profile
    const std::string& getProfile () const { return m_Profile; }
    void setProfile ( std::string profile ) { m_Profile = ( profile.size() > PlayerInfo::maxProfileLength ) ? profile.substr(0,PlayerInfo::maxProfileLength) : profile; }

	// get/set player info's publicability (?) 
	bool getPublic () const { return m_bPublic; }
	void setPublic ( bool bPublic ) { m_bPublic = bPublic; }

private :

	//--------------------------------------------------
	// �÷��̾� �⺻ ����
	//--------------------------------------------------
    std::string m_ID; 			// ���̵�
    std::string m_Password; 		// �н�����
	//--------------------------------------------------
	// �÷��̾� ���� ����
	//--------------------------------------------------
    std::string m_Name; 			// �̸�
    Sex m_Sex; 				// ����
    std::string m_SSN; 			// �ֹε�Ϲ�ȣ
	//--------------------------------------------------
	// �÷��̾� ����ó/�ּ�
	//--------------------------------------------------
    std::string m_Telephone; 	// ��ȭ��ȣ
    std::string m_Cellular; 		// �ڵ���
    std::string m_ZipCode; 		// ������ȣ
    std::string m_Address; 		// �ּ�
    Nation m_Nation; 		// ���� �ڵ�
	//--------------------------------------------------
	// �÷��̾� ��������
	//--------------------------------------------------
    std::string m_Email; 		// ���ڸ���
    std::string m_Homepage; 		// Ȩ������
	//--------------------------------------------------
	// ��Ÿ 
	//--------------------------------------------------
    std::string m_Profile; 		// �ϰ��¸�
	bool m_bPublic; 		// ���� ����

};


//////////////////////////////////////////////////////////////////////
//
// class CLRegisterPlayerFactory;
//
// Factory for CLRegisterPlayer
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLRegisterPlayerFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () { return new CLRegisterPlayer(); }

	// get packet name
	std::string getPacketName () const { return "CLRegisterPlayer"; }

	// get packet id
	PacketID_t getPacketID () const { return Packet::PACKET_CL_REGISTER_PLAYER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const
	{
		// ����ȭ�� �̸� ���� ����� ����ϵ��� �Ѵ�.
		return    szBYTE + PlayerInfo::maxIDLength 			// ���̵�
				+ szBYTE + PlayerInfo::maxPasswordLength 	// �н�����
				+ szBYTE + PlayerInfo::maxNameLength 		// �̸�
				+ szBYTE									// ����
				+ szBYTE + PlayerInfo::maxSSNLength 		// �ֹε�Ϲ�ȣ
				+ szBYTE + PlayerInfo::maxTelephoneLength 	// ��ȭ��ȣ
				+ szBYTE + PlayerInfo::maxCellularLength 	// �޴�����ȣ
				+ szBYTE + PlayerInfo::maxZipCodeLength 	// ������ȣ
				+ szBYTE + PlayerInfo::maxAddressLength 	// �ּ�
				+ szBYTE 									// �����ڵ�
				+ szBYTE + PlayerInfo::maxEmailLength 		// ���ڸ���
				+ szBYTE + PlayerInfo::maxHomepageLength 	// Ȩ������
				+ szBYTE + PlayerInfo::maxProfileLength 	// �ڱ�Ұ�
				+ szBYTE;									// ��������
	}


};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CLRegisterPlayerHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLRegisterPlayerHandler {

	public :

		// execute packet's handler
		static void execute ( CLRegisterPlayer * pPacket , Player * pPlayer );

	};
#endif

#endif
