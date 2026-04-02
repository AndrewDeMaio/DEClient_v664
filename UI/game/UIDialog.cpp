//-----------------------------------------------------------------------------
// UIDialog.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "Client.h"			// �̰� �� �����ϱ� ambigious.. T_T;;
#include "UIDialog.h"
#include "VS_UI_ExtraDialog.h" 
#include "TalkBox.h"
#include "PacketDef.h"
#include "MStringArray.h"
#include "TempInformation.h"
#include "VS_UI.h"
#include "ServerInfo.h"
#include "DebugInfo.h"
#include "UIFunction.h"
//#include <string>



#include "CPackets/CGSelectQuest.h"
#include "CPackets/CGSelectBloodBible.h"

#ifdef OUTPUT_DEBUG
#include "MZone.h"
#include "MTopView.h"
#include "AddonDef.h"
#endif

// WTF!!
bool g_bPartyRunning = false;		// ����...

using namespace std;

//-----------------------------------------------------------------------------
// global
//-----------------------------------------------------------------------------
UIDialog* g_pUIDialog = NULL;

//-----------------------------------------------------------------------------
// static
//-----------------------------------------------------------------------------
DWORD				UIDialog::s_LockGameInput = 0;

//-----------------------------------------------------------------------------
//
// constructor / destructor
//
//-----------------------------------------------------------------------------
UIDialog::UIDialog()
{
	m_pPCTalkDlg = NULL;

	m_pMessageDlg = NULL;

	//m_pHelpDlg = NULL;

	for (int i = 0; i < MAX_MESSAGE; i++)
	{
		m_ppDlgMessage[i] = NULL;
	}

#ifdef OUTPUT_DEBUG
	m_pAddonSelectDlg = NULL;
	m_pActionSelectDlg = NULL;
	m_pDirectionSelectDlg = NULL;
#endif

}

UIDialog::~UIDialog()
{
	Release();
}

//-----------------------------------------------------------------------------
//
//	member functions
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Init
//-----------------------------------------------------------------------------
void
UIDialog::Init()
{
	/*
		char* str = new char[128];

		//-------------------------------------------------------------
		// MESSAGE_CANNOT_BUY_NO_SPACE
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_CANNOT_BUY_NO_SPACE] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_CANNOT_BUY_NO_SPACE].GetString());
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_SPACE] = new char* [1];
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_SPACE][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_SPACE][0], str);

		//-------------------------------------------------------------
		// MESSAGE_CANNOT_BUY_NO_MONEY
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_CANNOT_BUY_NO_MONEY] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_CANNOT_BUY_NO_MONEY].GetString());
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_MONEY] = new char* [1];
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_MONEY][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_MONEY][0], str);

		//-------------------------------------------------------------
		// MESSAGE_CANNOT_BUY_NO_ITEM
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_CANNOT_BUY_NO_ITEM] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_CANNOT_BUY_NO_ITEM].GetString());
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_ITEM] = new char* [1];
		m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_ITEM][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_CANNOT_BUY_NO_ITEM][0], str);

		//-------------------------------------------------------------
		// MESSAGE_CANNOT_BUY_NO_ITEM
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_CANNOT_SELL] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_CANNOT_SELL].GetString());
		m_ppDlgMessage[MESSAGE_CANNOT_SELL] = new char* [1];
		m_ppDlgMessage[MESSAGE_CANNOT_SELL][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_CANNOT_SELL][0], str);

		//-------------------------------------------------------------
		// MESSAGE_SKILL_DIFFER_DOMAIN
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_SKILL_DIFFER_DOMAIN] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_SKILL_DIFFER_DOMAIN].GetString());
		m_ppDlgMessage[MESSAGE_SKILL_DIFFER_DOMAIN] = new char* [1];
		m_ppDlgMessage[MESSAGE_SKILL_DIFFER_DOMAIN][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_SKILL_DIFFER_DOMAIN][0], str);

		//-------------------------------------------------------------
		// MESSAGE_SKILL_EXCEED_LEVEL
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_SKILL_EXCEED_LEVEL] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_SKILL_EXCEED_LEVEL].GetString());
		m_ppDlgMessage[MESSAGE_SKILL_EXCEED_LEVEL] = new char* [1];
		m_ppDlgMessage[MESSAGE_SKILL_EXCEED_LEVEL][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_SKILL_EXCEED_LEVEL][0], str);

		//-------------------------------------------------------------
		// MESSAGE_SKILL_CANNOT_LEARN
		//-------------------------------------------------------------
		m_ppDlgMessageSize[MESSAGE_SKILL_CANNOT_LEARN] = 1;
		strcpy(str, g_GameStringTable[STRING_MESSAGE_SKILL_CANNOT_LEARN].GetString());
		m_ppDlgMessage[MESSAGE_SKILL_CANNOT_LEARN] = new char* [1];
		m_ppDlgMessage[MESSAGE_SKILL_CANNOT_LEARN][0] = new char [strlen(str)+1];
		strcpy(m_ppDlgMessage[MESSAGE_SKILL_CANNOT_LEARN][0], str);

		delete [] str;
	*/

	//-------------------------------------------------------------
	// MESSAGE_PCTALK
	//-------------------------------------------------------------
	m_ppDlgMessageSize[MESSAGE_PCTALK] = 1;
	m_ppDlgMessage[MESSAGE_PCTALK] = new std::string[1];



	//-------------------------------------------------------------
	// MESSAGE_FREE
	//-------------------------------------------------------------
	m_ppDlgMessageSize[MESSAGE_FREE] = 2;
	m_ppDlgMessage[MESSAGE_FREE] = new std::string[2];
}

//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void
UIDialog::Release()
{
	// PC Talk Dlg
	if (m_pPCTalkDlg != NULL)
	{
		delete m_pPCTalkDlg;
		m_pPCTalkDlg = NULL;
	}

	// Cannot buy Dlg
	if (m_pMessageDlg != NULL)
	{
		delete m_pMessageDlg;
		m_pMessageDlg = NULL;
	}

	// help
	/*
	if (m_pHelpDlg!=NULL)
	{
		delete m_pHelpDlg;
		m_pHelpDlg = NULL;
	}
	*/

	// dlg message
	for (int i = 0; i < MAX_MESSAGE; i++)
	{
		if (m_ppDlgMessage[i] != NULL)
		{
			delete[] m_ppDlgMessage[i];
			m_ppDlgMessage[i] = NULL;
		}
	}


	// �Է� ���� ����
	s_LockGameInput = 0;

#ifdef OUTPUT_DEBUG
	if (m_pAddonSelectDlg != NULL)
	{
		delete m_pAddonSelectDlg;
		m_pAddonSelectDlg = NULL;
	}

	if (m_pActionSelectDlg != NULL)
	{
		delete m_pActionSelectDlg;
		m_pActionSelectDlg = NULL;
	}

	if (m_pDirectionSelectDlg != NULL)
	{
		delete m_pDirectionSelectDlg;
		m_pDirectionSelectDlg = NULL;
	}
#endif
}

//-----------------------------------------------------------------------------
// Close PCTalk Dlg
//-----------------------------------------------------------------------------
void
UIDialog::ClosePCTalkDlg()
{
	if (m_pPCTalkDlg != NULL)
	{
#if __CONTENTS(__DYNAMIC_UI)
		m_pPCTalkDlg->Run(DIALOG_EXECID_CANCEL);
#else
		delete m_pPCTalkDlg;
		m_pPCTalkDlg = NULL;
#endif //__DYNAMIC_UI

		UnSetLockInputPCTalk();

		// ��Ƽ�� �� �־��ٸ�... �ٽ� ����.
		if (g_bPartyRunning)
		{
			UI_RunParty();
			g_bPartyRunning = false;
		}
	}
}

bool
UIDialog::IsRunningPCTalkDlg()
{
	if (m_pPCTalkDlg)
	{
		return m_pPCTalkDlg->Running();
	}

	return false;
}

//-----------------------------------------------------------------------------
// Close FreeMessage Dlg
//-----------------------------------------------------------------------------
void
UIDialog::CloseMessageDlg()
{
	if (m_pMessageDlg != NULL)
	{
		delete m_pMessageDlg;
		m_pMessageDlg = NULL;

		UnSetLockInputMessage();
	}
}

#if __CONTENTS(__DYNAMIC_UI)
bool UIDialog::Is_ActiveMessageDlg()
{
	if (m_pMessageDlg == NULL)
		return false;
	else
		return m_pMessageDlg->Is_ActiveDlg();
}
#endif //__DYNAMIC_UI

//-----------------------------------------------------------------------------
// Close Help Dlg
//-----------------------------------------------------------------------------
/*
void
UIDialog::CloseHelpDlg()
{
	if (m_pHelpDlg!=NULL)
	{
		delete m_pHelpDlg;
		m_pHelpDlg = NULL;
	}
}
*/

//-----------------------------------------------------------------------------
// Hide PCTalk Dlg
//-----------------------------------------------------------------------------
void
UIDialog::HidePCTalkDlg()
{
	if (m_pPCTalkDlg != NULL)
	{
		m_pPCTalkDlg->Finish();
	}
}

//-----------------------------------------------------------------------------
// Show PCTalk Dlg
//-----------------------------------------------------------------------------
void
UIDialog::ShowPCTalkDlg()
{
	if (m_pPCTalkDlg != NULL)
	{
		m_pPCTalkDlg->Start();
	}
}

//-----------------------------------------------------------------------------
// NPC ��ȭ ���� dialog
//-----------------------------------------------------------------------------
void
UIDialog::ProcessPCTalkDlg(C_VS_UI_DIALOG* pDlg, id_t id)
{
	//-----------------------------------------------------------
	// ������ �������� ��, 
	// server�� ���õ� ���� ������.
	//-----------------------------------------------------------
	// ���� �ڵ�.. - -;
	g_pPCTalkBox->SetAnswerID(id);

	int answerID;
	//--------------------------------------------------
	// dialog�� '��'���� ��..
	//--------------------------------------------------
	//if (id==DIALOG_EXECID_EXIT)
	//{
	//	answerID = 99;		// - -;;

		//UnSetLockInputPCTalk();		
	//}
	//--------------------------------------------------
	// �������� ����..
	//--------------------------------------------------
	//else
	{
		answerID = g_pPCTalkBox->GetAnswerID();
	}


	//--------------------------------------------------
	// ���� ������ ���� ��쿡�� packet�� ������.
	//--------------------------------------------------
	if (g_Mode == MODE_GAME)
	{
		if (g_pPlayer->IsWaitVerifyNULL())
		{
			//--------------------------------------------------
			// �ٸ� UI�� ������ �ʴ� ��쿡..
			//--------------------------------------------------
			if (!UI_IsRunningStorage()
				&& !UI_IsRunningExchange()
				&& !UI_IsRunningShop()
				&& !UI_IsRunningBookcase()
				&& !UI_IsRunningRepair()
				&& !UI_IsRunningSell()
				&& !UI_IsRunningSwapAdvancementItem())
			{
				switch (g_pPCTalkBox->GetType())
				{
					//--------------------------------------------------
					// �Ϲ����� ��ȭ
					//--------------------------------------------------
#if __CONTENTS(__GLOBAL_NPC)
				case PCTalkBox::GLOBAL_NPC:
#endif //__GLOBAL_NPC
				case PCTalkBox::NORMAL:
				{
					if (g_pPCTalkBox->m_AnswerIDMap.size() >= answerID)
						answerID = g_pPCTalkBox->m_AnswerIDMap[answerID - 1] + 1;

					CGNPCAskAnswer _CGNPCAskAnswer;

					_CGNPCAskAnswer.setObjectID(g_pPCTalkBox->GetNPCID());
					_CGNPCAskAnswer.setScriptID(g_pPCTalkBox->GetScriptID());
					_CGNPCAskAnswer.setAnswerID(answerID);

					g_pSocket->sendPacket(&_CGNPCAskAnswer);

					//--------------------------------------------------
					// ���� packet�� ��ٸ��� mode�� �����Ѵ�.
					//--------------------------------------------------
					g_pPlayer->SetWaitVerify(MPlayer::WAIT_VERIFY_NPC_ASK);
					if ((g_pPCTalkBox->m_AnswerIDMap.size() != answerID) &&
						(g_pPCTalkBox->GetScriptID() == 8521 || g_pPCTalkBox->GetScriptID() == 8522 || // ��Ÿ�ν�
							g_pPCTalkBox->GetScriptID() == 9721 || g_pPCTalkBox->GetScriptID() == 9722 || // ��ѵ�
							g_pPCTalkBox->GetScriptID() == 8920 || g_pPCTalkBox->GetScriptID() == 9420 || // ���� 
							g_pPCTalkBox->GetScriptID() == 13610 || g_pPCTalkBox->GetScriptID() == 13310)  // �ƿ콺���� 

						)
					{
						int answerStartID = 0;

						if (g_pPCTalkBox->GetScriptID() == 9721 || g_pPCTalkBox->GetScriptID() == 13310)
							answerStartID = 12;
						else if (g_pPCTalkBox->GetScriptID() == 8522 || g_pPCTalkBox->GetScriptID() == 8920)
							answerStartID = 24;
						else if (g_pPCTalkBox->GetScriptID() == 9722 || g_pPCTalkBox->GetScriptID() == 9420)
							answerStartID = 36;

						g_pPlayer->SetPrevDyeColorSet(answerStartID + answerID);
					}
				}
				break;

				//--------------------------------------------------
				// ��� ��� ��
				//--------------------------------------------------
				case PCTalkBox::SKILL_LEARN:
				{
					if (id != DIALOG_EXECID_EXIT)
					{
						if (id == 999)
						{
							// ���� ������
							pDlg->Run(DIALOG_EXECID_EXIT);

							UnSetLockInputPCTalk();

							g_pPlayer->SetWaitVerifyNULL();

							g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else if (g_pTempInformation->GetMode() == TempInformation::MODE_SKILL_LEARN)
						{
							g_pTempInformation->SetMode(TempInformation::MODE_NULL);

							CGLearnSkill _CGLearnSkill;

							//_CGLearnSkill.setObjectID( (*g_pPCTalkBox).GetNPCID() );
							_CGLearnSkill.setSkillType(id);
							_CGLearnSkill.setSkillDomainType((*g_pTempInformation).Value1);

							g_pSocket->sendPacket(&_CGLearnSkill);

							//--------------------------------------------------
							// ���� packet�� ��ٸ��� mode�� �����Ѵ�.
							//--------------------------------------------------
							//g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_NPC_ASK );						

							// Dialog ���� ������
							pDlg->Run(DIALOG_EXECID_EXIT);

							g_pPlayer->SetWaitVerifyNULL();

							UnSetLockInputPCTalk();

							g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else
						{
							DEBUG_ADD("[Error] Mode is Not SKILL_LEARN");
						}
					}
				}
				break;
				case PCTalkBox::SELECT_QUEST:
				{
					if (id != DIALOG_EXECID_EXIT)
					{
						if (id == 9999)
						{
							pDlg->Run(DIALOG_EXECID_EXIT);
							UnSetLockInputPCTalk();
							g_pPlayer->SetWaitVerifyNULL();
							g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else if (g_pTempInformation->GetMode() == TempInformation::MODE_SELECT_QUEST)
						{
							CGSelectQuest _CGSelectQuest;

							_CGSelectQuest.setQuestID(id);
							_CGSelectQuest.setNPCObjectID(g_pPCTalkBox->GetNPCID());
							g_pSocket->sendPacket(&_CGSelectQuest);

							pDlg->Run(DIALOG_EXECID_EXIT);
							g_pPlayer->SetWaitVerifyNULL();
							UnSetLockInputPCTalk();
							g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else
						{
							DEBUG_ADD("[Error] Mode is Not SELECT_QUEST");
						}
					}
				}
				break;
				//--------------------------------------------------
				// ������ ���̺�  ��� ��
				//--------------------------------------------------
				case PCTalkBox::BLOOD_BIBLE_SIGN:
				{
					if (id != DIALOG_EXECID_EXIT)
					{
						if (id == 999)
						{
							// ���� ������
							pDlg->Run(DIALOG_EXECID_EXIT);

							UnSetLockInputPCTalk();

							g_pPlayer->SetWaitVerifyNULL();

							g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else if (g_pTempInformation->GetMode() == TempInformation::MODE_SKILL_LEARN)
						{
							//	g_pTempInformation->SetMode(TempInformation::MODE_NULL);

							CGSelectBloodBible _CGSelectBloodBible;

							//_CGLearnSkill.setObjectID( (*g_pPCTalkBox).GetNPCID() );
							_CGSelectBloodBible.setBloodBibleID(id);

							g_pSocket->sendPacket(&_CGSelectBloodBible);

							//--------------------------------------------------
							// ���� packet�� ��ٸ��� mode�� �����Ѵ�.
							//--------------------------------------------------
							//g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_NPC_ASK );						

							// Dialog ���� ������
//								pDlg->Run( DIALOG_EXECID_EXIT );
//
//								g_pPlayer->SetWaitVerifyNULL();								
//
//								UnSetLockInputPCTalk();
//
//								g_pTempInformation->SetMode(TempInformation::MODE_NULL);
						}
						else
						{
							DEBUG_ADD("[Error] Mode is Not SKILL_LEARN");
						}
					}
				}
				break;
				}
			}
		}
	}

	//-------------------------------------------------------------
	// ESC �����ų�.. �׳� ������.. ����... ����.. ���� �Ҿ�.. - -;
	//-------------------------------------------------------------
	if (id == DIALOG_EXECID_EXIT)
	{
		UnSetLockInputPCTalk();

		g_pPlayer->SetWaitVerifyNULL();

		g_pTempInformation->SetMode(TempInformation::MODE_NULL);

		// ��Ƽ�� �� �־��ٸ�... �ٽ� ����.
		if (g_bPartyRunning)
		{
			UI_RunParty();
			g_bPartyRunning = false;
		}
	}
}

//-----------------------------------------------------------------------------
// PopupPCTalkDlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupPCTalkDlg(int x, int y)
{
	//				C_VS_UI_DIALOG m_pC_dialog = new C_VS_UI_DIALOG(50, 20, 6, 2, func, DIALOG_OK);
	//
	//				DIALOG_MENU d_menu[] = {
	//					{"���, 0},
	//					{"�ȱ�", 1},
	//					{"������", DIALOG_EXECID_EXIT},
	//				};
	//				m_pC_dialog->SetMenu(d_menu, 3);
	//
	//				static char * pp_dmsg[] = { // Message�� �ݵ�� static or global�� �ؾ� �Ѵ�.
	//					"line 1",
	//					"line 2",
	//				};
	//
	//				m_pC_dialog->SetMessage(pp_dmsg, sizeof(pp_dmsg)/sizeof(char *))

	extern bool	g_bTestMode;

	if (g_bActiveGame == false
#ifdef OUTPUT_DEBUG
		&& !g_bTestMode
#endif
		)
		return;

	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
#if __CONTENTS(__DYNAMIC_UI)
	BOOL bDynamicEnd = TRUE;
#endif //__DYNAMIC_UI
	if (m_pPCTalkDlg != NULL)
	{
#if __CONTENTS(__DYNAMIC_UI)
		bDynamicEnd = m_pPCTalkDlg->IsDynamicEnd();
#endif //__DYNAMIC_UI
		delete m_pPCTalkDlg;
		m_pPCTalkDlg = NULL;
	}

	// ��Ƽ�� �� �־����� Ȯ��
	if (UI_IsRunningParty() || g_bPartyRunning)
	{
		g_bPartyRunning = true;
	}
	else
	{
		g_bPartyRunning = false;
	}

	//---------------------------------------------------------
	// �ٸ� dialog�� �ݱ�
	//---------------------------------------------------------
	DEBUG_ADD("UID-CloseUIDlg");

	//	gC_vs_ui.CloseInfo();
	//	gC_vs_ui.CloseShop();
	//	gC_vs_ui.ServerDisconnectMessage();
	gC_vs_ui.CloseAllDialog();

	DEBUG_ADD("UID_COK");

	CloseMessageDlg();

	//---------------------------------------------------------
	// size üũ
	//---------------------------------------------------------
	int msgSize = g_pPCTalkBox->size();

	if (msgSize == 0)
	{
		return;
	}

	//---------------------------------------------------------
	// ����
	//---------------------------------------------------------
	const char* content = g_pPCTalkBox->GetContent();
	int lenContent = strlen(content);

	//---------------------------------------------------------
	// dialog�� ���̸� ���Ѵ�.
	//---------------------------------------------------------
	// -1 ������ �ڵ��̴�.
	/*
	int lengthY;

	if (g_pPCTalkBox->size() < 2)
	{
		lengthY = 0;
	}
	else
	{
		lengthY = g_pPCTalkBox->size() / 3;
	}

	lengthY += lenContent/150 + 1;	//(lenContent/40)/3 + 1;
	*/
	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	DEBUG_ADD("newNPCDLG");

	m_pPCTalkDlg = new C_VS_UI_NPC_DIALOG(ProcessPCTalkDlg,
		g_pPCTalkBox->GetCreatureType(),
		(*g_pCreatureTable)[g_pPCTalkBox->GetCreatureType()].Name.GetString());
	//g_pZone->GetCreature(g_pPCTalkBox->GetNPCID())->GetName());//, SMO_NOFIT);

#if __CONTENTS(__DYNAMIC_UI)
	if (bDynamicEnd)
	{
		m_pPCTalkDlg->SetDynamicStart();
	}
#endif //__DYNAMIC_UI
	//---------------------------------------------------------
	// ���� ���
	//---------------------------------------------------------	
	/*
	char* pContent = new char [lenContent+1];
	strcpy( pContent, content );
	char* pContentTemp = pContent;

	//-------------------------------------------------------------
	// 40���� �̻�
	//-------------------------------------------------------------
	// �ᰡ��~~~ ��.��; ������.. ����..
	int numStr = 0;

	while (lenContent > 40)
	{
		char* str = pContentTemp + 40;

		for (int i=40; i>0; i--)
		{
			if (*str==' ')
			{
				break;
			}

			str--;
		}

		strncpy(m_ppDlgMessage[MESSAGE_PCTALK][numStr], pContentTemp, i);
		m_ppDlgMessage[MESSAGE_PCTALK][numStr][i] = '\0';

		lenContent -= i+1;

		pContentTemp += i+1;		// +1�� �����̴�.

		numStr++;
	}

	//-------------------------------------------------------------
	// 40���� ����
	//-------------------------------------------------------------
	strcpy(m_ppDlgMessage[MESSAGE_PCTALK][numStr], pContentTemp);
	numStr++;

	m_pPCTalkDlg->SetMessage(m_ppDlgMessage[MESSAGE_PCTALK], numStr);//sizeof(pp_dmsg)/sizeof(char *));
	*/


	//---------------------------------------------------------
	// �޴� ����..
	//---------------------------------------------------------
	DEBUG_ADD("newDLGMENU");
	DIALOG_MENU* pMenu = new DIALOG_MENU[msgSize];// + 1];

	MStringList::iterator iString = g_pPCTalkBox->begin();

	int i = 0;

	switch (g_pPCTalkBox->GetType())
	{
		//-----------------------------------------------------
		// �Ϲ����� ��ȭ
		//-----------------------------------------------------
	case PCTalkBox::NORMAL:
#if __CONTENTS(__GLOBAL_NPC)
	case PCTalkBox::GLOBAL_NPC:
#endif//__GLOBAL_NPC
		while (iString != g_pPCTalkBox->end())
		{
			MString* pString = *iString;

			// menu ���� ����
			pMenu[i].exec_id = i + 1;						// ID+1
			pMenu[i].sz_menu_str = pString->GetString();		// ����..

			// ����..
			iString++;
			i++;
		}
		break;

		//-----------------------------------------------------
		// ��� ��� ��
		//-----------------------------------------------------
		// %3d%s �������� �Ǿ� �ִ�. �ӽ�!~~~ ��~~
		//-----------------------------------------------------
	case PCTalkBox::SKILL_LEARN:
	case PCTalkBox::BLOOD_BIBLE_SIGN:
		while (iString != g_pPCTalkBox->end())
		{
			MString* pString = *iString;
			DEBUG_ADD(pString->GetString());

			char strID[128] = { 0, };
			char strName[128] = { 0, };



			strncpy(strID, pString->GetString(), 3);
			strID[3] = NULL;


			strcpy(strName, pString->GetString() + 3);

			// �̸� �ٽ� ����
			*pString = strName;

			// menu ���� ����
			pMenu[i].exec_id = atoi(strID);
			pMenu[i].sz_menu_str = pString->GetString();		// ����..

			// ����..
			iString++;
			i++;
		}
		break;
	case PCTalkBox::SELECT_QUEST:
		while (iString != g_pPCTalkBox->end())
		{
			MString* pString = *iString;
			DEBUG_ADD(pString->GetString());

			char strID[80];
			char strName[80];

			strncpy(strID, pString->GetString(), 4);
			strID[4] = NULL;
			strcpy(strName, pString->GetString() + 4);

			// �̸� �ٽ� ����
			*pString = strName;

			// menu ���� ����
			pMenu[i].exec_id = atoi(strID);
			pMenu[i].sz_menu_str = pString->GetString();		// ����..

			// ����..
			iString++;
			i++;
		}
		break;
	}


	// "������"�߰�
	//pMenu[i].exec_id		= DIALOG_EXECID_EXIT;			// UI���� ���� ID
	//pMenu[i].sz_menu_str	= new char [10];
	//strcpy(pMenu[i].sz_menu_str, "������");

	//---------------------------------------------------------
	// �޴� ���
	//---------------------------------------------------------
	DEBUG_ADD("setMENU");
	m_pPCTalkDlg->SetMenu(pMenu, msgSize, false);// + 1, false);		// ������ ����

	DEBUG_ADD("spMenu");
	//---------------------------------------------------------
	// �� �κ��� ó���� Info���� ���ڿ��� ���� �κп� ������
	// �ԷµǸ� ���� ���ʿ� '��'�� �����Ƿ� ������ �ִ� �κ��̴�.
	// info������ ��¿�� ���� �κ��̹Ƿ� Ŭ�󿡼� ó��
	//								2009.07.14 by Li,Kwon-Hwak
	// ���� �ڵ�
	// strcpy(m_ppDlgMessage[MESSAGE_PCTALK][0], g_pPCTalkBox->GetContent());
	//---------------------------------------------------------
	std::string message_content = g_pPCTalkBox->GetContent();
	std::size_t pos = message_content.find("\n");
	while (pos != std::string::npos)
	{
		message_content.replace(pos - 1, 1, "");
		pos = message_content.find("\n", pos);
	}
	m_ppDlgMessage[MESSAGE_PCTALK][0] = message_content;

	//const char* pFirstString = m_ppDlgMessage[MESSAGE_PCTALK][0];

	DEBUG_ADD("setMsg");

	//m_pPCTalkDlg->SetMessage(m_ppDlgMessage[MESSAGE_PCTALK], 1);//sizeof(pp_dmsg)/sizeof(char *));
	m_pPCTalkDlg->SetMessage(m_ppDlgMessage[MESSAGE_PCTALK], 1, SMO_FIT, C_VS_UI_DIALOG::LINECHECK_USE_BOTH); // ,   105);

	//---------------------------------------------------------
	// delete
	//---------------------------------------------------------
	//delete [] pMenu[i].sz_menu_str;		// ������ string�� �����ָ� �ȴ�.
	delete[] pMenu;
	//	delete [] pContent;

		//---------------------------------------------------------
		// dialog ����..
		//---------------------------------------------------------
	DEBUG_ADD("startTalk");
	m_pPCTalkDlg->Start();

	//---------------------------------------------------------
	// game������ �Է��� �����Ѵ�.
	//---------------------------------------------------------
	SetLockInputPCTalk();
}

//-----------------------------------------------------------------------------
// Help dialog
//-----------------------------------------------------------------------------
/*
void
UIDialog::ProcessHelpDlg(C_VS_UI_DIALOG * pDlg, id_t id)
{
	//--------------------------------------------------
	// dialog�� '��'���� ��..
	//--------------------------------------------------
	if (id==DIALOG_EXECID_EXIT)
	{
		//UnSetLockInputHelp();
	}
}
*/

//-----------------------------------------------------------------------------
// PopupHelpDlg
//-----------------------------------------------------------------------------
/*
void
UIDialog::PopupHelpDlg(int x, int y)
{
//				C_VS_UI_DIALOG m_pC_dialog = new C_VS_UI_DIALOG(50, 20, 6, 2, func, DIALOG_OK);
//
//				DIALOG_MENU d_menu[] = {
//					{"���, 0},
//					{"�ȱ�", 1},
//					{"������", DIALOG_EXECID_EXIT},
//				};
//				m_pC_dialog->SetMenu(d_menu, 3);
//
//				static char * pp_dmsg[] = { // Message�� �ݵ�� static or global�� �ؾ� �Ѵ�.
//					"line 1",
//					"line 2",
//				};
//
//				m_pC_dialog->SetMessage(pp_dmsg, sizeof(pp_dmsg)/sizeof(char *))

	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pHelpDlg!=NULL)
	{
		delete m_pHelpDlg;
	}


	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pHelpDlg = new C_VS_UI_DIALOG(x, y, 4, 3, ProcessHelpDlg, SMO_NOFIT);

	//---------------------------------------------------------
	// ������ Loading�Ѵ�.
	//---------------------------------------------------------
	if (m_ppDlgMessage[MESSAGE_HELP]==NULL)
	{
		MStringArray	helpMessage;

		std::ifstream file(FILE_INFO_HELP, ios::binary);
		helpMessage.LoadFromFile( file );
		file.close();

		int lines = helpMessage.GetSize();

		m_ppDlgMessage[MESSAGE_HELP] = new char* [lines];

		for (int i=0; i<lines; i++)
		{
			m_ppDlgMessage[MESSAGE_HELP][i] = new char [helpMessage[i].GetLength()+1];
			strcpy(m_ppDlgMessage[MESSAGE_HELP][i], helpMessage[i].GetString());
		}

		m_ppDlgMessageSize[MESSAGE_HELP] = lines;
	}

	m_pHelpDlg->SetMessage(m_ppDlgMessage[MESSAGE_HELP], m_ppDlgMessageSize[MESSAGE_HELP]);

	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pHelpDlg->Start();

	//---------------------------------------------------------
	// game������ �Է��� �����Ѵ�.
	//---------------------------------------------------------
	//SetLockInputHelp();
}
*/

//-----------------------------------------------------------------------------
// Popup MessageDlg
//-----------------------------------------------------------------------------
/*
void
UIDialog::PopupMessageDlg(UIDIALOG_MESSAGE msg, int x, int y)
{
//				C_VS_UI_DIALOG m_pC_dialog = new C_VS_UI_DIALOG(50, 20, 6, 2, func, DIALOG_OK);
//
//				DIALOG_MENU d_menu[] = {
//					{"���, 0},
//					{"�ȱ�", 1},
//					{"������", DIALOG_EXECID_EXIT},
//				};
//				m_pC_dialog->SetMenu(d_menu, 3);
//
//				static char * pp_dmsg[] = { // Message�� �ݵ�� static or global�� �ؾ� �Ѵ�.
//					"line 1",
//					"line 2",
//				};
//
//				m_pC_dialog->SetMessage(pp_dmsg, sizeof(pp_dmsg)/sizeof(char *))

	if (msg >= MAX_MESSAGE || msg==MESSAGE_FREE)
	{
		return;
	}

	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pMessageDlg!=NULL)
	{
		delete m_pMessageDlg;
	}

	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pMessageDlg = new C_VS_UI_DIALOG(x, y, 3, 0, ProcessMessageDlg, DIALOG_OK);

	m_pMessageDlg->SetMessage(m_ppDlgMessage[msg], m_ppDlgMessageSize[msg], SMO_NOFIT);//sizeof(pp_dmsg)/sizeof(char *));


	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pMessageDlg->Start();

	//---------------------------------------------------------
	// game������ �Է��� �����Ѵ�.
	//---------------------------------------------------------
	SetLockInputHelp();
}
*/

//-----------------------------------------------------------------------------
// Popup Free MessageDlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupFreeMessageDlg(const char* msg, int x, int y, WORD fButton, bool IsAfterExit)
{
	int msgID = MESSAGE_FREE;

	//-------------------------------------------------------------
	// MESSAGE_FREE
	//-------------------------------------------------------------
	int msgSize = strlen(msg);

	int dlgSizeY, numStr;

	//-------------------------------------------------------------
	// 46���� �̻�
	//-------------------------------------------------------------
	// �ᰡ��~~~ ��.��; ������.. ����..
	int i;
	if (msgSize > 46)
	{
		dlgSizeY = 1;
		char* str = (char*)msg + 46;

		for (i = 46; i > 0; i--)
		{
			if (*str == ' ')
			{
				break;
			}

			str--;
		}

		m_ppDlgMessage[msgID][0].assign(msg, i);
		m_ppDlgMessage[msgID][1] = str + 1;
		numStr = 2;
	}
	//-------------------------------------------------------------
	// 46���� ����
	//-------------------------------------------------------------
	else
	{
		dlgSizeY = 0;
		m_ppDlgMessage[msgID][0] = msg;
		numStr = 1;
	}

	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pMessageDlg != NULL)
	{
		delete m_pMessageDlg;
		m_pMessageDlg = NULL;
	}

	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pMessageDlg = new C_VS_UI_DIALOG(x, y, 3, dlgSizeY, ProcessMessageDlg, fButton);

	//DEBUG_ADD_FORMAT("UIDIALOG(%s)", m_ppDlgMessage[msgID][0]);
	m_pMessageDlg->SetMessage(m_ppDlgMessage[msgID], numStr, SMO_NOFIT, C_VS_UI_DIALOG::LINECHECK_USE_BOTH);//sizeof(pp_dmsg)/sizeof(char *));
	//DEBUG_ADD_FORMAT("UIDIALOG(%s)after", m_ppDlgMessage[msgID][0]);


	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pMessageDlg->Start();

	//---------------------------------------------------------
	// game������ �Է��� �����Ѵ�.
	//---------------------------------------------------------
	SetLockInputMessage();
}

#if __CONTENTS(__DYNAMIC_UI)
//-----------------------------------------------------------------------------
// Popup Free MessageAndItemDlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupFreeMessageAndItemDlg(const char* msg, int Item_FrameID, int x, int y, WORD fButton, bool IsAfterExit)
{
	int msgID = MESSAGE_FREE;

	//-------------------------------------------------------------
	// MESSAGE_FREE
	//-------------------------------------------------------------
	int msgSize = strlen(msg);

	int dlgSizeY, numStr;

	//-------------------------------------------------------------
	// 40���� �̻�
	//-------------------------------------------------------------
	// �ᰡ��~~~ ��.��; ������.. ����..
	if (msgSize > 42)
	{
		dlgSizeY = 1;
		char* str = (char*)msg + 42;

		for (int i = 42; i > 0; i--)
		{
			if (*str == ' ')
			{
				break;
			}

			str--;
		}

		m_ppDlgMessage[msgID][0].assign(msg, i);
		m_ppDlgMessage[msgID][1] = str + 1;
		numStr = 2;
	}
	//-------------------------------------------------------------
	// 40���� ����
	//-------------------------------------------------------------
	else
	{
		dlgSizeY = 0;
		m_ppDlgMessage[msgID][0] = msg;
		numStr = 1;
	}

	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pMessageDlg != NULL)
	{
		delete m_pMessageDlg;
		m_pMessageDlg = NULL;
	}

	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pMessageDlg = new C_VS_UI_DIALOG(x, y, 3, dlgSizeY, ProcessMessageDlg, fButton);


	//DEBUG_ADD_FORMAT("UIDIALOG(%s)", m_ppDlgMessage[msgID][0]);
	m_pMessageDlg->SetMessage(m_ppDlgMessage[msgID], numStr, SMO_FIT_ITEM, true);//sizeof(pp_dmsg)/sizeof(char *));

	if (Item_FrameID != -1)
	{
		m_pMessageDlg->SetFit_Item(Item_FrameID); // ���̾�α׿� ��� ������ �̹���.
		m_pPCTalkDlg->SetThisDlg_End_InventoryPopUp();
	}
	//DEBUG_ADD_FORMAT("UIDIALOG(%s)after", m_ppDlgMessage[msgID][0]);


	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pMessageDlg->Start();
	//---------------------------------------------------------
	// game������ �Է��� �����Ѵ�.
	//---------------------------------------------------------
	SetLockInputMessage();
}
#endif //__DYNAMIC_UI

//-----------------------------------------------------------------------------
// ProcessCannotBuyDlg
//-----------------------------------------------------------------------------
void
UIDialog::ProcessMessageDlg(C_VS_UI_DIALOG* pDlg, unsigned long id)
{
	//if (id==DIALOG_OK)
	//{
	UnSetLockInputMessage();
	//}

}



#ifdef OUTPUT_DEBUG
//-----------------------------------------------------------------------------
// Popup AddonSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupAddonSelectDlg(int x, int y)
{
	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pAddonSelectDlg != NULL)
	{
		delete m_pAddonSelectDlg;
	}


	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pAddonSelectDlg = new C_VS_UI_DIALOG(x, y, 1, 2, ProcessAddonSelectDlg);//, SMO_NOFIT);

	//---------------------------------------------------------
	// �޴� ����..
	//---------------------------------------------------------
	const int menuSize = 9;
	DIALOG_MENU menu[menuSize] = {
				{"�Ӹ�", 1},
				{"����", 2},
				{"����", 3},
				{"����", 4},
				{"��������", 5},
				{"��", 6},
				{"����", 7},
				{"�������", 8},
				{"EXIT", DIALOG_EXECID_EXIT},
	};

	//---------------------------------------------------------
	// �޴� ���
	//---------------------------------------------------------
	m_pAddonSelectDlg->SetMenu(menu, menuSize);		// ������ ����

	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pAddonSelectDlg->Start();
}

//-----------------------------------------------------------------------------
// Process AddonSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::ProcessAddonSelectDlg(C_VS_UI_DIALOG* pDlg, unsigned long id)
{
	switch (id)
	{
	case DIALOG_EXECID_EXIT:
		break;

		//----------------------------------------------------------------------
		// �Ӹ�
		//----------------------------------------------------------------------
	case 1:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_HAIR);
		}
		else
		{
			const int hairFrame[] =
			{
				ADDONID_HAIR1,
				ADDONID_HAIR2,
				ADDONID_HAIR3
			};

			g_pPlayer->SetAddonHair(hairFrame[count - 1], 0);
		}

		if (++count == 4) count = 0;
	}
	break;

	//----------------------------------------------------------------------
	// ����
	//----------------------------------------------------------------------
	case 2:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_HELM);
		}
		else
		{
			const int helmType[] =
			{
				0, 4
			};

			MItem* pHelm = new MHelm;	pHelm->SetItemType(helmType[count - 1]); pHelm->ClearItemOption();
			g_pPlayer->SetAddonItem(pHelm);
			delete pHelm;
		}

		if (++count == 3) count = 0;
	}
	break;

	//----------------------------------------------------------------------
	// ����
	//----------------------------------------------------------------------
	case 3:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_COAT);
		}
		else
		{
			const int coatType[] =
			{
				0, 4
			};

			MItem* pCoat = new MCoat;	pCoat->SetItemType(coatType[count - 1]); pCoat->ClearItemOption();
			g_pPlayer->SetAddonItem(pCoat);
			delete pCoat;
		}

		if (++count == 3) count = 0;
	}
	break;

	//----------------------------------------------------------------------
	// ����
	//----------------------------------------------------------------------
	case 4:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_TROUSER);
		}
		else
		{
			const int TrouserType[] =
			{
				0, 4
			};

			MItem* pTrouser = new MTrouser;	pTrouser->SetItemType(TrouserType[count - 1]); pTrouser->ClearItemOption();
			g_pPlayer->SetAddonItem(pTrouser);
			delete pTrouser;
		}

		if (++count == 3) count = 0;
	}
	break;

	//----------------------------------------------------------------------
	// ��������
	//----------------------------------------------------------------------
	case 5:
	{
		static int count = 1;

		g_pPlayer->RemoveAddon(ADDON_RIGHTHAND);

		switch (count)
		{
			//-------------------------------------------------------
			// BLADE
			//-------------------------------------------------------
		case 1:
		{
			MItem* pBlade = new MBlade;	pBlade->SetItemType(0); pBlade->ClearItemOption();
			g_pPlayer->SetAddonItem(pBlade);
			delete pBlade;
		}
		break;

		//-------------------------------------------------------
		// SWORD
		//-------------------------------------------------------
		case 2:
		{
			MItem* pSword = new MSword;	pSword->SetItemType(0);	pSword->ClearItemOption();
			g_pPlayer->SetAddonItem(pSword);
			delete pSword;
		}
		break;

		//-------------------------------------------------------
		// CROSS
		//-------------------------------------------------------
		case 3:
		{
			MItem* pCross = new MCross;	pCross->SetItemType(0);	pCross->ClearItemOption();
			g_pPlayer->SetAddonItem(pCross);
			delete pCross;
		}
		break;
		}

		if (++count == 4)	count = 0;

	}
	break;

	//----------------------------------------------------------------------
	// ��
	//----------------------------------------------------------------------
	case 6:
	{
		static int count = 1;

		g_pPlayer->RemoveAddon(ADDON_RIGHTHAND);
		g_pPlayer->RemoveAddon(ADDON_LEFTHAND);


		MGunItem* pGunItem;

		if (count != 0)
		{
			switch (count)
			{
			case 1:
				pGunItem = new MGunTR;
				break;

			case 2:
				pGunItem = new MGunSMG;
				break;

			case 3:
				pGunItem = new MGunAR;
				break;

			case 4:
				pGunItem = new MGunSG;
				break;
			}

			pGunItem->SetItemType(0); pGunItem->ClearItemOption();

			MMagazine* pMagazine = (MMagazine*)MItem::NewItem((ITEM_CLASS)ITEM_CLASS_MAGAZINE);

			// �ǹ� ���� - -;
			pMagazine->SetID(0);

			// �̰Ŵ� �ѿ� ���缭 ����ߵȴ�.
			for (int j = 0; j < (*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)
			{
				pMagazine->SetItemType(j);

				if (pMagazine->IsInsertToItem(pGunItem))
				{
					break;
				}
			}

			// �ǹ� ����
			pMagazine->ClearItemOption();

			// źâ ����
			pMagazine->SetNumber(0xFFFF);

			//------------------------------------
			// źâ ����
			//------------------------------------
			pGunItem->SetMagazine(pMagazine);

			g_pPlayer->SetAddonItem(pGunItem);

			delete pGunItem;
		}


		if (++count == 5) count = 0;
	}
	break;


	//----------------------------------------------------------------------
	// ����
	//----------------------------------------------------------------------
	case 7:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_LEFTHAND);
		}
		else
		{
			const int itemType[] = { 0, 5 };
			MItem* pShield = new MShield;	pShield->SetItemType(itemType[count - 1]); pShield->ClearItemOption();

			g_pPlayer->RemoveAddon(ADDON_LEFTHAND);

			g_pPlayer->SetAddonItem(pShield);

			delete pShield;
		}


		if (++count == 3) count = 0;
	}
	break;

	//----------------------------------------------------------------------
	// �������
	//----------------------------------------------------------------------
	case 8:
	{
		static int count = 1;

		if (count == 0)
		{
			g_pPlayer->RemoveAddon(ADDON_MOTOR);
		}
		else
		{
			MItem* pMotor = new MMotorcycle;	pMotor->SetItemType(0); pMotor->ClearItemOption();
			g_pPlayer->SetAddonItem(pMotor);
			delete pMotor;
		}

		if (++count == 2) count = 0;
	}
	break;
	}
}

//-----------------------------------------------------------------------------
// Popup ActionSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupActionSelectDlg(int x, int y)
{
	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pActionSelectDlg != NULL)
	{
		delete m_pActionSelectDlg;
	}


	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pActionSelectDlg = new C_VS_UI_DIALOG(x, y, 1, 3, ProcessActionSelectDlg);//, SMO_NOFIT);

	//---------------------------------------------------------
	// �޴� ����..
	//---------------------------------------------------------
	const int menuSize = 11;//21;
	DIALOG_MENU menu[menuSize] = {
				{ "STAND",				0 },
				{ "MOVE", 				1 },
				{ "ATTACK", 			2 },
				{ "MAGIC", 				3 },
				{ "DAMAGED", 			4 },
				{ "DRAINED", 			5 },
				{ "DIE", 				6 },
				{ "VAMP_DRAIN",		7 },
				{ "THROW_WEAPON",	11 },
				{ "THROW_POTION",	17 },

				/*
				{ "SLAYER_GUN_TR",		7 },
				{ "SLAYER_GUN_SG",		8 },
				{ "SLAYER_SWORD",		9 },
				{ "SLAYER_BLADE",		10 },
				{ "SLAYER_MOTOR_MOVE", 	12 },
				{ "SLAYER_GUN_AR", 		13 },
				{ "SLAYER_GUN_SMG", 	14 },
				{ "SLAYER_SWORD_2", 	15 },
				{ "SLAYER_BLADE_2", 	16 },
				{ "SLAYER_MOTOR_STAND", 18 },
				*/

				{"EXIT", DIALOG_EXECID_EXIT}
	};

	//---------------------------------------------------------
	// �޴� ���
	//---------------------------------------------------------
	m_pActionSelectDlg->SetMenu(menu, menuSize);		// ������ ����

	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pActionSelectDlg->Start();
}

//-----------------------------------------------------------------------------
// Process ActionSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::ProcessActionSelectDlg(C_VS_UI_DIALOG* pDlg, unsigned long id)
{
	int actionID = id;

	switch (id)
	{
	case DIALOG_EXECID_EXIT:
		break;

		// Zone�� ��� ĳ������ action�� �ٲ۴�.
	default:
	{
		MZone::CREATURE_MAP::const_iterator iCreature = g_pZone->GetCreatureBegin();

		for (int i = 0; i < g_pZone->GetCreatureNumber(); i++)
		{
			MCreature* pCreature = (*iCreature).second;

			//--------------------------------------------------
			// player�� ���						
			//--------------------------------------------------
			if (pCreature->GetID() == g_pPlayer->GetID())
			{
				if (actionID == ACTION_DIE)
				{
					if (g_pPlayer->IsAlive())
					{
						g_pPlayer->SetDead();
					}
					else
					{
						g_pPlayer->SetAlive();
					}
				}
				else
				{
					// �׸��� �ִٸ� action�� �����Ѵ�.
					g_pPlayer->SetAction(actionID);
				}
			}
			//--------------------------------------------------
			// NPC�� �ƴ� ��츸...
			//--------------------------------------------------
			else if (!pCreature->IsNPC())
			{
				int body = pCreature->GetCreatureFrameID(0);
				int action = actionID;
				int	direction = pCreature->GetDirection();

				if (body < g_pTopView->m_CreatureFPK.GetSize())
				{
					ACTION_FRAME_ARRAY& AFA = g_pTopView->m_CreatureFPK[body];

					if (action < AFA.GetSize())
					{
						DIRECTION_FRAME_ARRAY& DFA = AFA[action];
						if (direction < DFA.GetSize())
						{
							FRAME_ARRAY& FA = DFA[direction];
							if (FA.GetSize() != 0)
							{
								// �׸��� �ִٸ� action�� �����Ѵ�.
								pCreature->SetNextAction(actionID);
							}
						}
					}
				}
			}

			iCreature++;
		}
	}

	}
}


//-----------------------------------------------------------------------------
// Popup DirectionSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::PopupDirectionSelectDlg(int x, int y)
{
	//---------------------------------------------------------
	// ������ �ִ� dialog�� �����.
	//---------------------------------------------------------
	if (m_pDirectionSelectDlg != NULL)
	{
		delete m_pDirectionSelectDlg;
	}


	//---------------------------------------------------------
	// dialog ����
	//---------------------------------------------------------
	m_pDirectionSelectDlg = new C_VS_UI_DIALOG(x, y, 1, 2, ProcessDirectionSelectDlg);//, SMO_NOFIT);

	//---------------------------------------------------------
	// �޴� ����..
	//---------------------------------------------------------
	const int menuSize = 9;//21;
	DIALOG_MENU menu[menuSize] = {
				{ "�� (Left)",			0 },
				{ "���� (LeftDown)", 	1 },
				{ "�� (Down)", 			2 },
				{ "���� (RightDown)",	3 },
				{ "�� (Right)", 		4 },
				{ "��� (RightUp)", 	5 },
				{ "�� (Up)", 			6 },
				{ "�»� (LeftUp)",		7 },


				{"EXIT", DIALOG_EXECID_EXIT}
	};

	//---------------------------------------------------------
	// �޴� ���
	//---------------------------------------------------------
	m_pDirectionSelectDlg->SetMenu(menu, menuSize);		// ������ ����

	//---------------------------------------------------------
	// dialog ����..
	//---------------------------------------------------------
	m_pDirectionSelectDlg->Start();
}

//-----------------------------------------------------------------------------
// Process DirectionSelect Dlg
//-----------------------------------------------------------------------------
void
UIDialog::ProcessDirectionSelectDlg(C_VS_UI_DIALOG* pDlg, unsigned long id)
{
	int direction = id;

	switch (id)
	{
	case DIALOG_EXECID_EXIT:
		break;

		// Zone�� ��� ĳ������ Direction�� �ٲ۴�.
	default:
	{
		MZone::CREATURE_MAP::const_iterator iCreature = g_pZone->GetCreatureBegin();

		for (int i = 0; i < g_pZone->GetCreatureNumber(); i++)
		{
			MCreature* pCreature = (*iCreature).second;

			//--------------------------------------------------
			// NPC�� �ƴ� ���
			//--------------------------------------------------					
			if (!pCreature->IsNPC())
			{
				pCreature->SetDirection(direction);
			}

			iCreature++;
		}
	}

	}
}
#endif
