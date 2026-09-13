//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodBibleListHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////
#include "GPacket_PCH.h"
#pragma warning(disable:4786)
// include files
#include "GCBloodBibleList.h"


#include "ClientDef.h"
#include "TalkBox.h"
#include "UIDialog.h"
#include "SystemAvailabilities.h"
#include "MGameStringTable.h"
#include "TempInformation.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCBloodBibleListHandler::execute ( GCBloodBibleList * pPacket , Player * pPlayer )
{
	__BEGIN_TRY 
	
#ifdef __GAME_CLIENT__
	if (g_pPlayer==NULL
		|| g_pZone==NULL
		|| g_pUIDialog==NULL
		|| g_pPCTalkBox==NULL)
	{
		DEBUG_ADD("[Error] Some Object is NULL");
		return;
	}

	g_pPlayer->SetWaitVerifyNULL();

	g_pPCTalkBox->Release();		// 

	std::vector<ItemType_t>	BloodBibleList = pPacket->getList();

	g_pPCTalkBox->SetType( PCTalkBox::BLOOD_BIBLE_SIGN );

	char str[512];
	char str2[512];
	int bibletype;
	for(int i = 0; i< BloodBibleList.size(); i++)
	{
		bibletype = BloodBibleList[i];

		//--------------------------------------------------------------
		// The menu id is parsed back out of the first three characters
		// by UIDialog, and the string table is indexed unchecked, so a
		// type outside the known range has to be dropped rather than
		// formatted. Plain bibles are 0-11, the six clan tiers are
		// 12-83 (twelve bibles each).
		//--------------------------------------------------------------
		if (bibletype < 0 || bibletype >= BLOOD_BIBLE_TYPE_MAX)
		{
			continue;
		}

		str2[0] = '\0';

		if(bibletype < 12)
		{
			sprintf(str2, (*g_pGameStringTable)[UI_STRING_MESSAGE_RENT_BLOOD_BIBLE2].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_BLOOD_BIBLE_ARMEGA+bibletype].GetString(),
				(*g_pGameStringTable)[STRING_MESSAGE_BLOOD_BIBLE_BONUS_ARMEGA+bibletype].GetString());
		}
#if __CONTENTS(__CONTRIBUTE_SYSTEM) || __CONTENTS(__BLOOD_BIBLE_TIERS)
		else
		{
			sprintf(str2, (*g_pGameStringTable)[UI_STRING_MESSAGE_RENT_BLOOD_BIBLE3].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_GRUN+(bibletype/12 - 1)].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_BLOOD_BIBLE_ARMEGA+bibletype%12].GetString(),
				(*g_pGameStringTable)[STRING_MESSAGE_BLOOD_BIBLE_BONUS_ARMEGA+bibletype%12].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_BLOOD_BIBLE_BONUS_GRUN_ARMEGA+(bibletype-12)].GetString()
				);
		}
#else
		else
		{
			// No clan tier strings in this build - skip rather than
			// printing an unformatted row.
			continue;
		}
#endif //__CONTRIBUTE_SYSTEM || __BLOOD_BIBLE_TIERS
		sprintf(str, "%3d %s", bibletype, str2);
		g_pPCTalkBox->AddString( str );
	}
	
	// ������ �߰�
	std::string szMsg;
	szMsg += "999";
	szMsg += (*g_pGameStringTable)[UI_STRING_MESSAGE_RENT_LATER_BLOOD_BIBLE].GetString();
	g_pPCTalkBox->AddString( szMsg.c_str() );


	strcpy(str, (*g_pGameStringTable)[UI_STRING_MESSAGE_RENT_BLOOD_BIBLE].GetString());

	g_pPCTalkBox->SetContent( str );

	g_pUIDialog->PopupPCTalkDlg();
	g_pTempInformation->SetMode(TempInformation::MODE_SKILL_LEARN);

#endif

	__END_CATCH
}
