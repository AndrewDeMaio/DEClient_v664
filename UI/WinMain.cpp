/*-----------------------------------------------------------------------------

  WinMain.cpp

  MS Windows Application basic routines.
  `VS UI Tester

  2000.1.5. KJTINC

-----------------------------------------------------------------------------*/
#include "client_PCH.h"
#include "Client.h"
#include <assert.h>
#include <windows.h>
#include "DXLib.h"

#include "VS_UI.h" // include VS UI master header file.
#include <math.h>
#include <stdio.h>

#include <crtdbg.h>
#include <process.h>
// include by sigi
#include "MItemOptionTable.h"
#include "MItemTable.h"
#include "ExperienceTable.h"
#include "MPriceManager.h"
#include "MSortedItemManager.h"
#include "UserOption.h"
#include "MCreatureTable.h"
#include "ClientConfig.h"
#include "VS_UI_Mouse_pointer.h"
#include "MTradeManager.h"
#include "VS_UI_filepath.h"
#include "MNPCTable.h"
#include "MSoundTable.h"
#include "CSoundPartManager.h"
#include "MParty.h"
#include "AcceleratorManager.h"
#include "KeyAccelerator.h"
#include "AcceleratorDef.h"
#include "MGuildMarkManager.h"
#include "MGuildInfoMapper.h"
#include "UserInformation.h"
#include "UtilityFunction.h"
#include "MGameStringTable.h"
#include "MTimeItemManager.h"
#include "MMonsterKillQuestInfo.h"

#include "MStringArray.h"
#include "MZoneTable.h"
#include "RankBonusTable.h"
#include "FameInfo.h"
#include "MQuestInfo.h"
#include "Properties.h"
#include "SystemAvailabilities.h"
#include "ShrineInfoManager.h"
#include "RankBonusDef.h"
#include "VS_UI_GameCommon2.h"
#include "SXml.h"

#include "VS_UI_WorldMap.h"
#include "MPortal.h"

#include "OperatorOption.h"
#include "VS_UI_TIMECOUNT.h"

bool g_bFamily = false;

BOOL InitSound();

#define CLASSNAME				"DX"
#define TITLEBARNAME			"VS UI tester~"

#define _DEBUGGING			1

//#define _FULLSCREEN
/*-----------------------------------------------------------------------------
  PROTOTYPE
-----------------------------------------------------------------------------*/
void MouseEventReceiver(CDirectInput::E_MOUSE_EVENT event, int x, int y, int z);
void KeyboardEventReceiver(CDirectInput::E_KEYBOARD_EVENT event, DWORD scan_code);
void UI_ResultReceiver(DWORD message, int dw_left, int dw_right, void* void_ptr);
void ProgramLoop();

/*-----------------------------------------------------------------------------
  GLOBALS
-----------------------------------------------------------------------------*/
HWND						g_hWnd;
HINSTANCE					g_hInstance;
int							g_Dimension = 0;

bool	gbl_ui_input_state; // UI�� �Է��� �޾Ҵ°�?
int		g_LeftPremiumDays = 10;

extern EventButton* g_EventButton;

bool						gbl_active; // Is application active?
CDirectDraw				gC_DD;
CSpriteSurface			gC_DDSurface;
extern CDirectInput* g_pDXInput;// = new CDirectInput;

DWORD				g_double_click_time;
int						g_mouse_x, g_mouse_y;

bool						gbl_info_show = false;//true;
bool						gbl_game_back = false;
bool						gbl_show_item = true;

C_VS_UI_NPC_DIALOG* m_pC_dialog = NULL;

extern CSoundPartManager* g_pSoundManager;

DWORD	g_CurrentFrame = 0;

void kk(C_VS_UI_DIALOG* b, unsigned long a)
{
	int i = 0;
}

std::map<int, bool> g_mapPremiumZone;

//IWebBrowser2*			g_pWebBrowser = NULL;
/*-----------------------------------------------------------------------------
- KeyboardEventReceiver
-
-----------------------------------------------------------------------------*/
void KeyboardEventReceiver(CDirectInput::E_KEYBOARD_EVENT event, DWORD scan_code)
{
	static int hp;
	static WORD progress;
	static bool bl_ctrl;
	static int time = 0;
	static int x = 0, y = 0;
	static int step = 2;
	static int count = 2;

	switch (event)
	{
	case CDirectInput::KEYDOWN:
		gC_vs_ui.DIKeyboardControl(event, scan_code);
		switch (scan_code)
		{
		case DIK_LCONTROL:
		case DIK_RCONTROL:
			bl_ctrl = true;
			break;

		case DIK_SPACE:
			//if (bl_ctrl == true)
			//	gC_vs_ui.HotKey_WindowToggle();
			//	gC_vs_ui.HotKey_SummonPet();
			break;

		case DIK_TAB:
			//if (bl_ctrl)
			//	gC_vs_ui.HotKey_Gear();
			//else
			//	gC_vs_ui.HotKey_Inventory();
			break;

		case DIK_ESCAPE:
			//gC_vs_ui.HotKey_ESC();
			break;

		case DIK_LEFT:
			if (g_EventButton)
			{
				g_EventButton->x--;
			}
			else
				if (bl_ctrl)
				{
					time = (time - 1 + 24) % 24;
					char temp[10];
					wsprintf(temp, "%d:56:20", time);
					gC_vs_ui.SetTime(temp);
				}
				else
				{
					progress -= 10;

					//						gC_vs_ui.SetHP(progress, 300);
					//						gC_vs_ui.SetMP(progress, 300);
					g_char_slot_ingame.HP -= 10;
					g_char_slot_ingame.MP -= 10;

					gC_vs_ui.SetProgress(progress, 100);
				}
			break;

		case DIK_RIGHT:
			if (g_EventButton)
			{
				g_EventButton->x++;
			}
			else
				if (bl_ctrl)
				{
					time = (time + 1) % 24;
					char temp[10];
					wsprintf(temp, "%d:56:20", time);
					gC_vs_ui.SetTime(temp);
				}
				else
				{
					progress += 10;

					//gC_vs_ui.SetHP(progress, 300, true, progress);
					//gC_vs_ui.SetMP(progress, 300);
					g_char_slot_ingame.SILVER_HP += 10;
					g_char_slot_ingame.HP += 10;
					g_char_slot_ingame.MP += 10;

					gC_vs_ui.SetProgress(progress, 100);
				}
			break;

		case DIK_HOME:
			gbl_game_back = !gbl_game_back;
			break;

			extern bool gbl_show_item;
		case DIK_PGUP:
			gbl_show_item = !gbl_show_item;
			break;

		case DIK_INSERT:
			gbl_info_show = !gbl_info_show;
			break;

		case DIK_UP:
			if (g_EventButton)
			{
				g_EventButton->y--;
			}
			else
				//					{
				//						char buf[50];
				//						static DWORD counter;
				//
				//						sprintf(buf, "@%d", counter++);
				//						gC_vs_ui.AddChatToHistory(buf, "��ũ����");
				//					}
				hp++;
			//gC_vs_ui.SetHP(hp, 100);
			//gC_vs_ui.SetMP(hp, 100);
			break;

		case DIK_DOWN:
			if (g_EventButton)
			{
				g_EventButton->y++;
			}
			else
				hp--;
			//gC_vs_ui.SetHP(hp, 100);
			//gC_vs_ui.SetMP(hp, 100);
			break;

			//
			// hot-key
			//
		case DIK_F1:
		{
			//if(gC_vs_ui.IsRunningWebBrowser())
			//	gC_vs_ui.CloseWebBrowser();
			//else
			//	gC_vs_ui.RunWebBrowser(g_hWnd, /*"http://market.darkeden.com/item/?race=COMMON&kind=RARE"*/"www.naver.com", (void*)g_pWebBrowser);


			//gC_vs_ui.Run_Wedding_Contribution_Unfortunate_Neighbors( 9 );
			//gC_vs_ui.PopupSummerComBack(1) ; 
			//g_pParty->

// 						PARTY_INFO *temp_party = new PARTY_INFO;
// 						temp_party->bMale = false;
// 						temp_party->hairStyle = W_FACE1;
// 						temp_party->Name = "���߻���";
// 						g_pParty->AddMember(temp_party);
// 						
// 						//temp_party->bMale = false;
// 						//temp_party->hairStyle = W_FACE1;
// 						//temp_party->Name = "���߻���1234";
// 						//g_pParty->AddMember(temp_party);
// 
// 						g_char_slot_ingame.AttackBloodBurstPoint = 3000;
// 						g_char_slot_ingame.DefenseBloodBurstPoint = 2000;
// 						g_char_slot_ingame.PartyBloodBurstPoint = 20000;
// 						
// 						//gC_vs_ui.SetGage() ; 
// 						gC_vs_ui.SetBloodBurstAttackGage() ; 
// 						gC_vs_ui.SetBloodBurstDefenseGage() ; 
// 						gC_vs_ui.SetBloodBurstPartyGage() ; 

//						gC_vs_ui.Run_Confirm_GetItemEvent(5);
//						gC_vs_ui.RunPowerjjang();
					//	gC_vs_ui.RunNaming();
						//gpC_base->SendMessage(UI_MESSAGE_BOX, STRING_MESSAGE_CANNOT_REPAIR, 0, 	NULL);
//						gC_vs_ui.AddHelpMail(0,false);
//						gC_vs_ui.AddHelpMail(1,false);
//						gC_vs_ui.AddHelpMail(2,false);
//						gC_vs_ui.AddHelpMail(3,false);
//						gC_vs_ui.AddHelpMail(4,false);
//						gC_vs_ui.AddHelpMail(5,false);
//						gC_vs_ui.AddHelpMail(6,false);
//						gC_vs_ui.AddHelpMail(7,false);
//						gC_vs_ui.AddHelpMail(8,false);
//						gC_vs_ui.AddHelpMail(9,false);
//						gC_vs_ui.AddHelpMail(10,false);
//						gC_vs_ui.AddHelpMail(11,false);
//						gC_vs_ui.AddHelpMail(12,false);
//						gC_vs_ui.AddHelpMail(13,false);
//						gC_vs_ui.AddHelpMail(14,false);
//						gC_vs_ui.AddHelpMail(15,false);
//						gC_vs_ui.AddHelpMail(16,false);
//						gC_vs_ui.AddHelpMail(17,false);
//						gC_vs_ui.AddHelpMail(18,false);
//						gC_vs_ui.AddHelpMail(19,false);
//						gC_vs_ui.AddHelpMail(20,false);
//						gC_vs_ui.AddHelpMail(21,false);
//						

//						C_VS_UI_TEAM_INFO::READY_TEAM_INFO info;
//						info.TEAM_NAME = "�������̾�";
//						info.LEADER_NAME = "����";
//			//			info.REGISTERD_DATE = "2001-12-31 06:30";
//			//			info.MEMBERS = 30;
//						info.REG_FEE = 100000;
//						info.EXPIRE_DATE = "2002-01-05 06:40";
//						info.MEMBERS_NAME.push_back("����");
//						info.MEMBERS_NAME.push_back("ġ��ǪǪ");
//						info.MEMBERS_NAME.push_back("Ǫ����");
//						info.MEMBERS_NAME.push_back("�κ��ŴϾ�");
//						info.MEMBERS_NAME.push_back("����߾�");
//						info.MEMBERS_MAX = 5;
//						info.INTRODUCTION = "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
//						gC_vs_ui.RunTeamInfo(true, &info);	

						//gC_vs_ui.RunTeamRegist(true, 100000, 1,"2002-01-01", "�������̴�",100);
					//	gC_vs_ui.RunTeamRegist(false, 100000, 2,"2002-01-01", "�������̴�",100);

		}

		{
			//						static MPetItem *tempItem;
			//						tempItem = (MPetItem *)(MItem::NewItem(ITEM_CLASS_PET_ITEM));
			//						tempItem->SetItemType(/*g_eRaceInterface+3*/3);
			//						tempItem->SetCurrentDurability(20*24*60+20*60);
			//						tempItem->SetEnchantLevel(ITEMOPTION_TABLE::PART_LUCK);
			//						tempItem->SetSilver(4);
			//						tempItem->SetNumber(50);
			//						tempItem->SetPetFoodType(0);
			//						tempItem->SetPetExpRemain(10000);
			//						tempItem->SetPetGamble(true);
			//						std::list<TYPE_ITEM_OPTION> optionList;
			//						optionList.push_back(162);
			//						tempItem->SetItemOptionList(optionList);
			//						MPetItem *pPetItem = tempItem;
			//						PETINFO petInfo;
			//						petInfo.HP = pPetItem->GetCurrentDurability();
			//						petInfo.ATTR = pPetItem->GetEnchantLevel();
			//						petInfo.ATTR_VALUE = pPetItem->GetSilver();
			//						petInfo.LEVEL = pPetItem->GetNumber();
			//						petInfo.FOODTYPE = pPetItem->GetPetFoodType();
			//						petInfo.EXP_REMAIN = pPetItem->GetPetExpRemain();
			//						petInfo.CUT_HEAD = pPetItem->IsCanCutHead();
			//						petInfo.GAMBLE = pPetItem->IsCanGamble();
			//						if(pPetItem->GetItemOptionListCount() == 0)
			//							petInfo.OPTION = -1;
			//						else
			//							petInfo.OPTION = pPetItem->GetItemOptionList().front();
			//						petInfo.ITEM_TYPE = pPetItem->GetItemType();
			//						petInfo.NAME = "����";//pPetItem->GetPetName();
			//						petInfo.NICK_NAME = "�ٺ� ��^^;";
			//						gC_vs_ui.SetPetInfo( &petInfo );
			////						gC_vs_ui.RefreshPet();
			//						gC_vs_ui.RunPetInfo(&petInfo);
			//						gC_vs_ui.RunOtherInfo();
			//						gC_vs_ui.SetOtherPetInfo(tempItem);
		}
		//					{
		//						std::string rankbonusName[RANK_BONUS_MAX] =
		//						{
		//							"RANK_BONUS_DEADLY_SPEAR.bmp",
		//							"RANK_BONUS_BEHEMOTH_ARMOR.bmp",
		//							"RANK_BONUS_DARGON_EYE.bmp",
		//							"RANK_BONUS_IMMORTAL_HEART.bmp",
		//							"RANK_BONUS_RELIANCE_BRAIN.bmp",
		//							"RANK_BONUS_SLAYING_KNIFE.bmp",
		//							"RANK_BONUS_HAWK_WING.bmp",
		//							"RANK_BONUS_HOLY_SMASHING.bmp",
		//							"RANK_BONUS_SOUL_SMASHING.bmp",
		//							"RANK_BONUS_SAPPHIRE_BLESS.bmp",
		//							"RANK_BONUS_RUBY_BLESS.bmp",
		//							"RANK_BONUS_DIAMOND_BLESS.bmp",
		//							"RANK_BONUS_EMERALD_BLESS.bmp",
		//							"RANK_BONUS_MAGIC_BRAIN.bmp",
		//							"RANK_BONUS_WIGHT_HAND.bmp",
		//							"RANK_BONUS_SEIREN_HAND.bmp",
		//							"RANK_BONUS_FORTUNE_HAND.bmp",
		//							
		//							"RANK_BONUS_IMMORTAL_BLOOD.bmp",
		//							"RANK_BONUS_BEHEMOTH_SKIN.bmp",
		//							"RANK_BONUS_SAFE_ROBE.bmp",
		//							"RANK_BONUS_CROW_WING.bmp",
		//							"RANK_BONUS_WISDOM_OF_BLOOD.bmp",
		//							"RANK_BONUS_TIGER_NAIL.bmp",
		//							"RANK_BONUS_URANUS_BLESS.bmp",
		//							"RANK_BONUS_DISRUPTION_STORM.bmp",
		//							"RANK_BONUS_WIDE_STORM.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_POISON.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_ACID.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_CURSE.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_BLOOD.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_INNATE.bmp",
		//							"RANK_BONUS_KNOWLEDGE_OF_SUMMON.bmp",
		//							"RANK_BONUS_WISDOM_OF_SWAMP.bmp",
		//							"RANK_BONUS_WISDOM_OF_SILENCE.bmp",
		//							"RANK_BONUS_WISDOM_OF_DARKNESS.bmp",
		//							"RANK_BONUS_WIDE_DARKNESS.bmp",
		//							
		//							"RANK_BONUS_WOOD_SKIN.bmp",
		//							"RANK_BONUS_WIND_SENSE.bmp",
		//							"RANK_BONUS_HOMING_EYE.bmp",
		//							"RANK_BONUS_LIFE_ENERGY.bmp",
		//							"RANK_BONUS_SOUL_ENERGY.bmp",
		//							"RANK_BONUS_STONE_MAUL.bmp",
		//							"RANK_BONUS_SWIFT_ARM.bmp",
		//							"RANK_BONUS_FIRE_ENDOW.bmp",
		//							"RANK_BONUS_WATER_ENDOW.bmp",
		//							"RANK_BONUS_EARTH_ENDOW.bmp",
		//							"RANK_BONUS_ANTI_ACID_SKIN.bmp",
		//							"RANK_BONUS_ANTI_BLOODY_SKIN.bmp",
		//							"RANK_BONUS_ANTI_CURSE_SKIN.bmp",
		//							"RANK_BONUS_ANTI_POISON_SKIN.bmp",
		//							"RANK_BONUS_ANTI_SILVER_DAMAGE_SKIN.bmp",
		//							"RANK_BONUS_BLESS_OF_NATURE.bmp",
		//							"RANK_BONUS_LIFE_ABSORB.bmp",
		//							"RANK_BONUS_SOUL_ABSORB.bmp",
		//							"RANK_BONUS_MYSTIC_RULE.bmp"
		//						};
		//						for(int i = 0; i < RANK_BONUS_MAX; i++)
		//						{
		//							int spriteID = (*g_pRankBonusTable)[i].GetSkillIconID();
		//							CSprite *sprite = &C_VS_UI_SKILL::m_C_spk[spriteID];
		//							CSpriteSurface surface;
		//							int w = sprite->GetWidth(), h = sprite->GetHeight();
		//							surface.InitOffsurface(w, h, DDSCAPS_SYSTEMMEMORY);
		//							POINT p = {0, 0};
		//							if(surface.Lock())
		//							{
		//								surface.BltSprite(&p, sprite);
		//								surface.Unlock();
		//
		//								surface.SaveToBMP(rankbonusName[i].c_str());
		//							}
		//						}
		//
		//					}
		{
			C_VS_UI_POPUP_MESSAGE::PopupWindowStyle style;

			std::string filename = "";
			switch (g_eRaceInterface)
			{
			case RACE_SLAYER:
				filename = "BeginnerZoneSlayer.txt";
				break;
			case RACE_OUSTERS:
				filename = "BeginnerZoneOusters.txt";
				break;
			case RACE_VAMPIRE:
				filename = "BeginnerZoneVampire.txt";
				break;
			}

			style.WindowX = 420;
			style.WindowY = 450;
			style.Type = C_VS_UI_POPUP_MESSAGE::POPUP_NORMAL;

			CRarFile PackFile;
			PackFile.SetRAR(RPK_TUTORIAL_ETC, RPK_PASSWORD);

			std::string sender, title, contents;
			SIZE windowSize;

			if (PackFile.IsSet())
			{
				char temp[4096];
				PackFile.Open(filename.c_str());
				ZeroMemory(temp, 4096);
				PackFile.GetString(temp, 4096);
				sscanf(temp, "%d %d", &windowSize.cx, &windowSize.cy);
				ZeroMemory(temp, 4096);
				PackFile.GetString(temp, 4096);
				sender = temp;
				ZeroMemory(temp, 4096);
				PackFile.GetString(temp, 4096);
				title = temp;
				ZeroMemory(temp, 4096);
				PackFile.GetString(temp, 4096);
				contents = temp;

				PackFile.Release();
			}
			else
				return;

			gC_vs_ui.AddMail(0, 3, windowSize, sender.c_str(), title.c_str(), 3102200, false);
			gC_vs_ui.AddMailContents(0, 3, contents.c_str());
			gC_vs_ui.RunMailBox();
			gC_vs_ui.RunPopupMessage(style);
		}
		//gC_vs_ui.RunHorn( 1006 );
//					gC_vs_ui.RunArrowTile();
//					gC_vs_ui.RunCTFStatusWindow();
//					{
//						DWORD endtime = timeGetTime() + 500;
//						int a[3] = {255,255,255};
//						
//						gC_vs_ui.SetCTFStatus( endtime, a[0], a[1], a[2] );
//					}
//					{
// 						gC_vs_ui.RunTeamRegist();
//						int step = 2;
//						gC_vs_ui.RunLotteryCard( step );}
//					gC_vs_ui.RunPopupMessage("ASKGOBEGINNERZONE.txt",C_VS_UI_POPUP_MESSAGE::POPUP_ASK_BEGINNER_ZONE);

//					gC_vs_ui.RequestShrineMinimap( 10000 );

//					gC_vs_ui.RunTeamList(true);
//					gC_vs_ui.RunWarListWindow();
//					{
//						srand(GetTickCount());
//							
//						for(int i=0;i<10;i++)
//						{
//							C_VS_UI_WAR_LIST::WarInfo warlist;
//							warlist.reinforceGuildID = rand()%1000;
//							warlist.reinforceGuildName = "�Ҵ�  ���";
//							for(int j = 0; j<5; j++)
//							{
//								warlist.challengerGuildID[j] = rand()%1000;
//								warlist.challengerGuildName[j] = "�Ҵ�  ���(����)";
//							}
//							warlist.year = 2003;
//							warlist.month = 12;
//							warlist.day = i;
//							warlist.warType = rand() & 1;
//							gC_vs_ui.AddWarList(warlist);
//						}
//					}
//					gC_vs_ui.RunBringFeeWindow(100000,0);
//					gC_vs_ui.RunRangerChat();
					//gC_vs_ui.RunInputNameWindow();
					//gC_vs_ui.RunTestWindow()();   
					//gC_vs_ui.RunDepositLimit();
//					gC_vs_ui.RunXmasCardWindow((const MItem *)1); 
//					gC_vs_ui.Run_Campaign_Help_Unfortunate_Neighbors(); 
//					g_char_slot_ingame.m_AdvancementLevel = 2;
// 					if(gC_vs_ui.IsRunningWebBrowser())
// 						gC_vs_ui.CloseWebBrowser();
// 					else
// 						gC_vs_ui.RunWebBrowser(g_hWnd, /*"http://market.darkeden.com/item/?race=COMMON&kind=RARE"*/"www.naver.com", g_hInst);
					//gC_vs_ui.RunTeamInfo(false,);

//					{
//						C_VS_UI_OTHER_INFO::PLAYER_INFO info;
//						
//						info.ALIGNMENT=2;
//						
//						info.PLAYER_NAME="SONEE12345";
//						info.STR_PURE=g_char_slot_ingame.STR_PURE;
//						info.DEX_PURE=g_char_slot_ingame.DEX_PURE;
//						info.INT_PURE=g_char_slot_ingame.INT_PURE;
//						info.STR_CUR=g_char_slot_ingame.STR_CUR;
//						info.DEX_CUR=g_char_slot_ingame.DEX_CUR;
//						info.INT_CUR=g_char_slot_ingame.INT_CUR;
//						info.FAME=9992222;
//						info.guild_id=3067;
//						info.GRADE=35;
//						info.DOMAINLEVEL[0]=5;//g_char_slot_ingame.DOMAIN_BLADE;
//						info.DOMAINLEVEL[1]=100;//g_char_slot_ingame.DOMAIN_SWORD;
//						info.DOMAINLEVEL[2]=47;//g_char_slot_ingame.DOMAIN_GUN;
//						info.DOMAINLEVEL[3]=78;//g_char_slot_ingame.DOMAIN_HEAL;
//						info.DOMAINLEVEL[4]=99;//g_char_slot_ingame.DOMAIN_ENCHANT;
//						//nfo.bMale=TRUE;14
//						info.bl_female=false;
//						info.face_type=M_FACE2;
//						srand(GetTickCount());
//						
////						if(rand()&1)
////							info.TEAM_NAME="�������׽�Ʈ��";
////						else
////							info.TEAM_NAME = "TETETS";
//						gC_vs_ui.RunOtherInfo();
//						gC_vs_ui.SetOtherInfo(info);
//					}
//				
					//gC_vs_ui.RunShop();
					//gC_vs_ui.RunEnchant();
					//gC_vs_ui.RunExchange();
//					//gC_vs_ui.RunSlayerPortal();
//					gC_vs_ui.RunFileDialog(C_VS_UI_FILE_DIALOG::MODE_PROFILE_SELECT, ".bmp;.jpg");
//					gC_vs_ui.RunSMSMessage();					

//					gC_vs_ui.RunTe
//					gC_vs_ui.SetWhisperID("����");
		//			gC_vs_ui.AddChatToHistory("���� äƮ����..ȫȫ..", "���0", CLD_ZONECHAT);
//					gC_vs_ui.OpenInventoryToRepair();
//					gC_vs_ui.RequestDie();
//					gC_vs_ui.SetAccelMode(ACCEL_CHARINFO);
//					gC_vs_ui.RequestParty("����");

//					gC_vs_ui.OpenInventoryToSell();
/*					{
						gC_vs_ui.StartProgress();
						gC_vs_ui.SetCurrentServerName("�Ķ��Ķ����", "������", C_VS_UI_SERVER_SELECT::STATUS_VERY_GOOD);
						for (int i=0; i<=200; i++)
						{
							gC_vs_ui.SetProgress(i, 200);
							gC_vs_ui.Show();
							gC_DD.Flip();
						}

						gC_vs_ui.EndProgress();
					}*/
					//					//gC_vs_ui.HotKey_F1();
					//					gC_vs_ui.UnselectSkill();

										//					gC_vs_ui.RunEnchantSkillTree();
										//gC_vs_ui.ServerDisconnectMessage();
										//gC_vs_ui.LevelUp();
					//					gC_vs_ui.AddChatToHistory("���� äƮ����..ȫȫ..", "��ũ����");
					//					gC_vs_ui.AddChatToHistory("������ 4�� �����Դϴ�.. ���� �������̳ı���? ���� �⺻��Ʈ�� �̰� �ٲ� ���׿��.�� ���~ ���Ƴ���-_-a", "ġ��ǪǪ", CLD_ZONECHAT);
					//					gC_vs_ui.RunTutorialExit();
		break;

		case DIK_F2:
		{
			//gC_vs_ui.AddInputString("�׽�Ʈ2");
			//gC_vs_ui.AddChatToHistory("�׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ���׽�Ʈ��", "���̵���", CLD_INFO, RGB(255, 255, 255));

			//gC_vs_ui.Run_Campaign_Help_Unfortunate_Neighbors(5000); 
			//gC_vs_ui.RunModifyTax() ;
			//	gC_vs_ui.RunDelegation_Of_Power("��ä�ٺ�") ; 

			//gC_vs_ui.RunTaxRate(-20)  ; 
			//gC_vs_ui.RunPartyCancel("����");
			//gC_vs_ui.PopupNetmarbleAgreementMessage() ;

			//gC_vs_ui.RunCTFStatusWindow() ; 

			//gC_vs_ui.RunPersnalShop() ;  
			//g_pUserInformation->IsNetmarble = 1 ; 
			//g_pUserInformation->IsNetmarbleLogin = 1 ; 

			//gC_vs_ui.RunInputNameWindow(C_VS_UI_INPUT_NAME::INPUT_NAME_BREAK_UP); 
			//gC_vs_ui.RunHorn( 1006 );

			//gC_vs_ui.RunSlayerPortal(2); 
			//gC_vs_ui.PopupSummerComBack(1)  ; 
			//gC_vs_ui.RunTeamRegist(true, 100000, 1,"2002-01-01", "�������̴�",100);

			//gC_vs_ui.PopupSummerComBack(3)  ; 
			//gC_vs_ui.PopupSummerComBack(4)  ; 
			//char  strMsg[256] = "assadfsaf���Ȥ����׳���" ; 

			//SendMessage(g_hWnd , WM_COPYDATA ,  (LPARAM)(LPCTSTR)strMsg , 0 ) ;

			//gC_vs_ui.RunExchangeCancel("�ٺ�");

//					gC_vs_ui.RunBookcase();
//					if((*g_pSkillInfoTable)[SKILL_BACK_STAB].IsEnable())
//					{
//						(*g_pSkillInfoTable)[SKILL_BACK_STAB].SetEnable(false);
//						(*g_pSkillInfoTable)[SKILL_INSTALL_TRAP].SetEnable(false);
//					}
//					else
//					{
//						(*g_pSkillInfoTable)[SKILL_BACK_STAB].SetEnable(true);
//						(*g_pSkillInfoTable)[SKILL_INSTALL_TRAP].SetEnable(true);
//					}
					//gC_vs_ui.RunComputer();
//					{
//						C_VS_UI_NicknameInfo nik;
//						nik.setNickname("�ٺ�");
//						nik.setNicknameID(100);
//						nik.setNicknameIndex(10);
//						nik.setNicknameType(2);
//						gC_vs_ui.AddNickNameList((void*)&nik);
//					}
					//gC_vs_ui.RunNamingChange(NULL, "���~");
					//g_hInst = hInst ; 
					//gC_vs_ui.RunStorage();
		}
		//gC_vs_ui.RunPetStorage() ; 
		//if(gC_vs_ui.IsRunningWebBrowser())
		//	gC_vs_ui.CloseWebBrowser();
		//else
		//	gC_vs_ui.RunWebBrowser(g_hWnd, /*"http://market.darkeden.com/item/?race=COMMON&kind=RARE"*/ "http://gmk.darkeden.com/?userid=sjheon" , g_hInst) ;//(void*)g_pWebBrowser);

//					if(gC_vs_ui.IsRunningPowerjjang())
//					{
//						gC_vs_ui.PowerjjangGambleResult(rand()%7);
//					}
//					else
//						gC_vs_ui.RunPowerjjang();
//					gC_vs_ui.RunTeamMemberList();
//					gC_vs_ui.RunUsePetFood();
//					gC_vs_ui.RequestResurrect(false,false,false,false,true);

//						C_VS_UI_QUEST_STATUS::QUEST_STATUS quest;
//						quest.Title = NULL;
//						if(NULL == quest.Title)
//						{
//							char *szBuf = new char[128];
//							sprintf(szBuf, "������%d�󸶹�\\n����..%shh", 3, "����");
//							quest.Title = szBuf;
//
//
//						}
//						quest.QuestID = 49;
//						quest.quest_time = timeGetTime();
//						quest.current_point = 20;
//						gC_vs_ui.SetQuestStatus( quest );
//						gC_vs_ui.RunQuestStatusWindow();

					//gC_vs_ui.RunBringFeeWindow(1000000000,0);
//					gpC_Imm->ForceAction(SOUND_ITEM_USE_C4);
//					gpC_Imm->ForceSound("kaka");
					//gC_vs_ui.RunExchangeAsk("������~��");
//					gpC_Imm->ForceAction(CImm::FORCE_ACTION_DAMAGED);
//					gC_vs_ui.RunTeamList(false);
//					{
//						for(int i=100;i<150;i++)
//						{
//							char name[100];
//							C_VS_UI_TEAM_LIST::REGIST_TEAM_LIST son;
//							son.guild_id=i;
//							son.MEMBERS=i*50;							
//							wsprintf(name,"%d",rand()%100000);
//							son.TEAM_NAME=name;
//							wsprintf(name,"%d",rand()%100000);
//							son.LEADER_NAME=name;
//							son.RANKING=i;
//							gC_vs_ui.AddRegistTeamInfo(son);					
//						}
//				 	}					
////					gC_vs_ui.AddChatToHistory("���� äƮ����..ȫȫ..", "���0", CLD_NORMAL, RGB(0, 0, 255));
					//gC_vs_ui.HotKey_F2();
//					gC_vs_ui.RunPartyAsk("����", (C_VS_UI_REQUEST_PARTY::REQUEST_PARTY)0);
//					gC_vs_ui.RunHealSkillTree();
//					gC_vs_ui.AddChatToHistory("���ä��������..ȣȪ..", "��ũ����", CLD_GUILD);

//					gC_vs_ui.AddChatToHistory("������ 4�� �����Դϴ�.. ���� �������̳ı���? ���� �⺻��Ʈ�� �̰� �ٲ� ���׿��.�� ���~ ���Ƴ���-_-a", "ġ��ǪǪ", CLD_NORMAL);
					//gC_vs_ui.RunBookcase();
//					gC_vs_ui.RunSlayerPortal();
//					gC_vs_ui.RunPartyCancel("����");

		break;

		case DIK_F3:
			//		gC_vs_ui.OpenInventoryToRepair();
		//	gC_vs_ui.RunFileDialog(C_VS_UI_FILE_DIALOG::MODE_SENDFILE_SELECT,".bmp");
					//gC_vs_ui.RunBookcase();
					//gC_vs_ui.RunPetStorage();
					//if(!gC_vs_ui.IsRunningQuestManager())
		{
			gC_vs_ui.RunInputNameWindow(C_VS_UI_INPUT_NAME::INPUT_NAME_HOPE_COUPLE);
			//gC_vs_ui.RunSlayerPortal(1); 
			//gC_vs_ui.PopupSummerComBack(4)  ; 
			//g_pUserInformation->IsTestServer = 1 ; 

			//MItem* pItem = MItem::NewItem( ITEM_CLASS_SUB_INVENTORY );
			//pItem->SetID( rand()%10000 );
			//pItem->SetItemType( 0 );
			//gC_vs_ui.RunSubInventory( pItem );

		}
		//						gC_vs_ui.RunQuestManager();
							//else
							//	gC_vs_ui.CloseQuestManager();

		//					{
		//						MItem* pItem = MItem::NewItem( (MItem::ITEM_CLASS)(rand()%40) );
		//						
		//						pItem->SetID( rand()%10000 );
		//						pItem->SetItemType( rand()% (*g_pItemTable)[pItem->GetItemClass()].GetSize());
		//						for(int i=0;i<2;i++)
		//						{
		//							if(rand()&0x1)
		//								pItem->AddItemOption( rand() % 50 );
		//						}
		//						pItem->SetCurrentDurability( 2000 );
		//
		//						gC_vs_ui.AddItemToItemList(pItem);
		//					}
							//
							//gC_vs_ui.HotKey_F3();
		//					gC_vs_ui.RunBladeSkillTree();
							//gC_vs_ui.AddChatToHistory("\"�ӼӸ��� ������ �� �����ϴ�\"~~ -> info", "��ũ����", CLD_INFO);
		//					gC_vs_ui.AddChatToHistory("��Ƽä��������..ȣȪ..", "��ũ����", CLD_PARTY);
		//					gC_vs_ui.RunExchangeAsk("�ñ�");
							//gC_vs_ui.RunBriefing();
		//					gC_vs_ui.RunElevator();
		//					gC_vs_ui.RunExchangeCancel("�ñ�");
		//					gC_vs_ui.RunPartyManager();
		//					gC_vs_ui.RequestDie();
		//					gC_vs_ui.ResetOustersQuickItemSize();
		//					gC_vs_ui.RunQuestInventory();
		//					gC_vs_ui.RunItemListWindow();
		//					gC_vs_ui.SetDelayRequestResurrect( C_VS_UI_REQUEST_RESURRECT::RESURRECT_MODE_ETERNITY, 5000);
							//					gC_vs_ui.RunMixingForge( C_VS_UI_MIXING_FORGE::CLASS_ACCESSORY, C_VS_UI_MIXING_FORGE::TYPE_A );
		{
			//						C_VS_UI_BLOOD_BIBLE_STATUS::BLOOD_BIBLE_STATUS status;
			//						
			//						status.zone_id = 71;
			//						status.x = 100;
			//						status.y = 100;
			//						status.name = "SONEE";
			//						status.shrine_race = RACE_OUSTERS;
			//						
			//						status.status = C_VS_UI_BLOOD_BIBLE_STATUS::BLOOD_BIBLE_HAS_OUSTERS;
			//						int id=3;
			//
			//						gC_vs_ui.RunBloodBibleStatus();
			//
			//						gC_vs_ui.SetBloodBibleStatus(id, status);
		}
		break;

		case DIK_F4:

			gC_vs_ui.RunInputNameWindow(C_VS_UI_INPUT_NAME::INPUT_NAME_FORCE_BREAK_UP);
			//gC_vs_ui.RunSlayerPortal(0); 
//					gC_vs_ui.RunElevator();
					//gC_vs_ui.ServerDisconnectMessage();
//			gC_vs_ui.OpenInventoryToSell();
				//	gC_vs_ui.RunItemListWindow();

//				gC_vs_ui.AddChatToHistory("��ġ������..ȣȪ..", "��ũ����", CLD_ZONECHAT);
//					gC_vs_ui.RunSwordSkillTree();
					//gC_vs_ui.HotKey_F4();
//					gC_vs_ui.RunVampireSkillTree();
				//	gC_vs_ui.RunComputer();
//					gC_vs_ui.AddChatToHistory("�ӼӸ� �������..ȣȪ..", "��ũ����", CLD_WHISPER);
					//					gC_vs_ui.ServerDisconnectMessage();
					//					gC_vs_ui.StartTitle();
					//					gC_vs_ui.RequestParty("����");
					//					gC_vs_ui.OpenInventoryToSell();
					//gC_vs_ui.RequestParty("����");
			{
				//	g_pSlayerGear->RemoveItem((MSlayerGear::GEAR_SLAYER)10);
			}
			break;

		case DIK_F5:
		{
			// C_VS_UI_TIMECOUNT	testTimer(300000);
			//gC_vs_ui.OpenInventoryToRepair();
			//					gC_vs_ui.AddChatToHistory("�Ӹ� �Ϲ�������..ȣȪ..", "��ũ����", CLD_WHISPER);
			//	PARTY_INFO *temp_party = new PARTY_INFO;
			//	temp_party->bMale = false;
			//	temp_party->hairStyle = W_FACE1;
			//	temp_party->Name = "���߻���";
			//	g_pParty->AddMember(temp_party);
			//					gC_vs_ui.OpenInventoryToRepair();


			//					gC_vs_ui.RequestParty("����", C_VS_UI_REQUEST_PARTY::REQUEST);
			//gC_vs_ui.OpenInventoryToSell();
//						{
//							DWORD id = 101;
//							gC_vs_ui.RunImageNotice();
//							gC_vs_ui.AddNotice( "�����", id );
//							int step = 1;
////							gC_vs_ui.RunLotteryCard(step);
//						}
						//					gC_vs_ui.RunGunSkillTree();
						//gC_vs_ui.HotKey_F5();
						//					gC_vs_ui.RunSkillView();

						// pcs ������ ����Ѵ�...
						//					gC_vs_ui.RunStorageBuy(1000000);
						//gC_vs_ui.PleaseConnectPCS("KJTINC", 1234567, 1);

						/*
						// ��ġ�� ���� ���� �׽�Ʈ
					const char* pString = gC_vs_ui.GetInputString();

					if (pString!=NULL && pString[0]=='!')
					{
						if (gbl_vampire_interface)
						{
							gC_vs_ui.SetInputStringColor( RGB(50, 50, 200) );
						}
						else
						{
							gC_vs_ui.SetInputStringColor( RGB(200, 50, 50) );
						}
					}
					else
					{
						gC_vs_ui.SetInputStringColor( gpC_base->m_chatting_pi.text_color );
					}
					*/
		}
		break;

		case DIK_F6:

			gC_vs_ui.ChangeToSlayerInterface();

			/*
			{
				DWORD id = 11;
					gC_vs_ui.AddNotice( "�����", id );
			}
			gC_vs_ui.OpenInventoryToSilvering();
			{
				gC_vs_ui.RunElevator();
				if (m_pC_dialog!=NULL)
				{
					delete m_pC_dialog;
					m_pC_dialog = NULL;
				}
				else
				{
					*/
					/*
					static num = 431;
					m_pC_dialog = new C_VS_UI_NPC_DIALOG(kk, num, "����");

					DIALOG_MENU d_menu[] = {
						{"�ȱ�ϱ�ϱ�ϱ�ϱ��ϱ�ϱ�ϱ�ϱ�ϱ���?", 0},
						{"�ȱ�ϱ�ϱ��ϱ�ϱ�ϱ�ϱ�ϱ���?", 1},
						{"�ȱ��ϱ�ϱ��ϱ�ϱ�ϱ�ϱ�ϱ���?", 2},
						{"������", DIALOG_EXECID_EXIT},
						};
					m_pC_dialog->SetMenu(d_menu, 4, false);

					static char * pp_dmsg[] = { // Message�� �ݵ�� static or global�� �ؾ� �Ѵ�.
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
						"�ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� �����ƹ��ų� ��� ����",
					};

					m_pC_dialog->SetMessage(pp_dmsg, sizeof(pp_dmsg)/sizeof(char *));//, SMO_NOFIT);

					m_pC_dialog->Start();
					num++;
					/*
				}
			}
			*/



			//gC_vs_ui.HotKey_F6();
			//gC_vs_ui.PleaseConnectPCS("toggi", 3355447, 2);

//					}
			break;

		case DIK_F7:
			gC_vs_ui.ChangeToVampireInterface();
			//gC_vs_ui.HotKey_F7();
			break;

		case DIK_F8:
			//gC_vs_ui.HotKey_F8();
			gC_vs_ui.ChangeToOustersInterface();
			break;

		case DIK_F9:
			//					gC_vs_ui.ChangeToVampireInterface();
								//gC_vs_ui.RunShop();
								//gC_vs_ui.OpenInventoryToRepair();
								//gC_vs_ui.OpenInventoryToSilvering();
								//{
									//
									//gC_vs_ui.RunStorage();
			gC_vs_ui.RunExchange();
			//}
			break;

		case DIK_F10: // ���콺 �������� �Ͼ.
			gC_vs_ui.RunOtherInfo();
			//gC_vs_ui.OpenInventoryToRepair();

			//
			// F10�� �̻��ϰ� virtual key�� ���� �� ����.. ��...
			// �׷��� �̰͸� dinput���� �޴´�.
			//
			//gC_vs_ui.HotKey_F10();
//					gC_vs_ui.RunStorage();
			break;

		case DIK_F11:
			//					gC_vs_ui.OpenInventoryToSell();
			//					gC_vs_ui.RunStorage();
			gC_vs_ui.RunExchange();
			//					gC_vs_ui.ServerDisconnectMessage();
			break;

		case DIK_F12:
			//gC_vs_ui.RunShop();
//					gC_vs_ui.HotKey_F12();
			gC_vs_ui.RequestDie();
			break;

		case DIK_NUMPAD4:
			if (bl_ctrl)
				x -= 10;
			else x--;
			gC_vs_ui.SetXY(x, y);
			break;

		case DIK_NUMPAD6:
			if (bl_ctrl)
				x += 10;
			else x++;
			gC_vs_ui.SetXY(x, y);
			break;

		case DIK_NUMPAD8:
			if (bl_ctrl)
				y -= 10;
			else y--;
			gC_vs_ui.SetXY(x, y);
			break;

		case DIK_NUMPAD2:
			if (bl_ctrl)
				y += 10;
			else y++;
			gC_vs_ui.SetXY(x, y);
			break;


		case DIK_1:
			//					gC_vs_ui.SetInputStringColor(RGB_WHITE);
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorDefault();
			break;

		case DIK_2:
			//					gC_vs_ui.SetInputStringColor(RGB_RED);
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorAttack();
			break;

		case DIK_3:
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorPickUp("���� ��ũ����", RGB_YELLOW);
			break;

		case DIK_5:
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorNotMove();
			break;

		case DIK_6:
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorPortal(11);
			break;

		case DIK_7:
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorPortal(11, 10, 10);
			break;

		case DIK_8:
			if (bl_ctrl)
				gpC_mouse_pointer->SetCursorPortal(11, 10, 10, "�����׽���");
			break;

		}
		break;

	case CDirectInput::KEYUP:
		switch (scan_code)
		{
		case DIK_LCONTROL:
		case DIK_RCONTROL:
			bl_ctrl = false;
			break;
		}
		break;
	}
}

extern BOOL g_bLButtonDown;

/*-----------------------------------------------------------------------------
- MouseEventReceiver
-
-----------------------------------------------------------------------------*/
void MouseEventReceiver(CDirectInput::E_MOUSE_EVENT event, int x, int y, int z)
{
	static DWORD	last_click_time;
	static int		double_click_x, double_click_y;

	// Window mode debug �� ���� DI���� pointer�� Window ������ �����Ƿ� �̶���
	// WindowProc()���� �Ѿ���� ��ǥ�� ����Ѵ�.
#ifndef _FULLSCREEN
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(g_hWnd, &point);
	g_mouse_x = point.x;
	g_mouse_y = point.y;

	if (g_mouse_x < 0)
		g_mouse_x = 0;
	//else if (g_mouse_x >= RESOLUTION_X)
	//	g_mouse_x = RESOLUTION_X-1;

	else if (g_mouse_x >= g_pUserInformation->iResolution_x)
		g_mouse_x = g_pUserInformation->iResolution_x - 1;

	if (g_mouse_y < 0)
		g_mouse_y = 0;
	//else if (g_mouse_y >= RESOLUTION_Y)
	//	g_mouse_y = RESOLUTION_Y-1;
	else if (g_mouse_y >= g_pUserInformation->iResolution_y)
		g_mouse_y = g_pUserInformation->iResolution_y - 1;


	x = g_mouse_x;
	y = g_mouse_y;
#else
	g_mouse_x = x;
	g_mouse_y = y;
#endif

	switch (event)
	{
	case CDirectInput::MOVE:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_MOVING, x, y);
		//			gC_vs_ui.MouseControlExtra(M_MOVING, x, y);
		break;

	case CDirectInput::LEFTDOWN:
		//  double-click interval?
		if (abs(static_cast<long>(GetTickCount()) - static_cast<long>(last_click_time)) <= g_double_click_time)
		{
			if (x >= double_click_x - 1 && x <= double_click_x + 1 &&
				y >= double_click_y - 1 && y <= double_click_y + 1)
			{
				gbl_ui_input_state = gC_vs_ui.MouseControl(M_LB_DOUBLECLICK, x, y);
				last_click_time = 0;
				return;
			}
		}

		gbl_ui_input_state = gC_vs_ui.MouseControl(M_LEFTBUTTON_DOWN, x, y);
		last_click_time = GetTickCount();
		double_click_x = x;
		double_click_y = y;

		//			gC_vs_ui.ChatMouseControlExtra(M_LEFTBUTTON_DOWN, x, y);
		g_bLButtonDown = TRUE;

		break;

	case CDirectInput::LEFTUP:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_LEFTBUTTON_UP, x, y);
		g_bLButtonDown = FALSE;
		break;

	case CDirectInput::RIGHTDOWN:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_RIGHTBUTTON_DOWN, x, y);
		break;

	case CDirectInput::RIGHTUP:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_RIGHTBUTTON_UP, x, y);
		if (gbl_ui_input_state == false)g_EventButton = NULL;
		break;

	case CDirectInput::CENTERDOWN:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_CENTERBUTTON_DOWN, x, y);
		break;

	case CDirectInput::CENTERUP:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_CENTERBUTTON_UP, x, y);
		break;

	case CDirectInput::WHEELDOWN:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_WHEEL_DOWN, x, y);
		break;

	case CDirectInput::WHEELUP:
		gbl_ui_input_state = gC_vs_ui.MouseControl(M_WHEEL_UP, x, y);
		break;
	}
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
LRESULT CALLBACK
WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static char		scan_code;
	//DWORD				dwCommand, dwData;

	switch (message)
	{
	case WM_IME_NOTIFY:
	{
		int ttt = 0;
	}
	return 0;
	/*
   case WM_IME_NOTIFY:
	   dwCommand = (DWORD) wParam;
	   dwData = (DWORD) lParam;

	   if (dwCommand == IMN_SETOPENSTATUS)
	   {
		   int z = 0;
	   }
	   return 0;*/

	case WM_KEYUP:
	case WM_KEYDOWN:
	case WM_CHAR:
	case WM_IME_COMPOSITION:
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_ENDCOMPOSITION:
		gC_vs_ui.KeyboardControl(message, wParam, lParam);

		if (message == WM_IME_STARTCOMPOSITION)
			return 0;

		break; // ! break!!!!

	case WM_MOVE:
		if (gbl_active && !CDirectDraw::IsFullscreen())
			CDirectDraw::OnMove();
		return 0L;

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
		// Pause if minimized
		gbl_active = !((BOOL)HIWORD(wParam));
		//				g_pDXInput->SetAcquire(gbl_active);
		g_pDXInput->SetAcquire(true);
		g_double_click_time = GetDoubleClickTime();
		break;

		//return 0L;

	case WM_MOUSEACTIVATE:
	{
		int a = 0;
	}
	break;

	case WM_DESTROY:
		// Clean up and close the app
		gC_DD.ReleaseAll();
		PostQuitMessage(0);
		return 0L;
		/*
				case WM_KEYDOWN:
					// Handle any non-accelerated key commands
					switch (wParam)
					{
						case VK_ESCAPE:
						case VK_F12:
							PostMessage(hWnd, WM_CLOSE, 0, 0);
							return 0L;
					}
					break;*/

	case WM_SETCURSOR:
		// Turn off the cursor since this is a full-screen app
		SetCursor(NULL);
		return 0L;

	case WM_SIZE:
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//.......................................................................................
// ���� ȿ���� �ʿ��� tan ��.
float dtan(float deg) {
	if (deg > 360 || deg < 0)    return((float)tan(-1));
	return((float)((3.141592 * deg) / 180));
}
////////////////////////////////////////////////////////////////////
// ���� ȿ��(ǥ�� flip ������ ����Ѵ�)...........
// ����: Lenz( 200,200, 50 ); // ��ġ, ������...(ȭ��:640*480)...
void    Lenz(int x, int y, int radius) {
	static int sx, sy;
	static int xsize, ysize;
	static int a, b, c, d, e, f;
	static int j, i, daddr;
	static float g;
	static WORD* data;

	if (x < radius)            x = radius + 1;
	if (y < radius)            y = radius + 1;
	if (x + radius >= 640)    x = 639 - radius;
	if (y + radius >= 480)    y = 479 - radius;
	/*
	// ���� ���ƴٴϱ�...
	static int dir=0, x=300, y=200;
	switch( dir )    {
	case 0:            // move(right,down)
	x+=10;    y+=10;
	if( (640-radius)<x )    dir = 3;
	if( (400-radius)<y )    dir = 1;
	break;
	case 1:            // move(right,up )
	x+=10;    y-=10;
	if( (640-radius)<x )    dir = 2;
	if( y<radius )    dir = 0;
	break;
	case 2:            // move(left ,up )
	x-=10;    y-=10;
	if( x<radius     )    dir = 1;
	if( y<radius )    dir = 3;
	break;
	case 3:            // move(left ,down)
	x-=10;    y+=10;
	if( x<radius     )    dir = 0;
	if( (400-radius)<y )    dir = 2;
	break;
	}
	*/
	///////////////////////////////////////////////////////////////////////////

	sx = x - radius;        sy = y - radius;
	xsize = ysize = radius + radius;
	data = new WORD[xsize * xsize];

	//	gC_DD->Lock();// NULL, &m_ddsd, DDLOCK_WAIT, NULL );
	gpC_base->m_p_DDSurface_back->Lock();
	WORD* m_pdest = (WORD*)gpC_base->m_p_DDSurface_back->GetSurfacePointer();//(WORD*)m_ddsd.lpSurface;
	const int pitch = gpC_base->m_p_DDSurface_back->GetSurfacePitch() / 2;
	m_pdest += sy * pitch/*m_ddsd.lPitch>>1*/ + sx;
	daddr = 0;
	for (j = 0; j < ysize; j++) {
		memcpy(&data[daddr], m_pdest, (xsize << 1));
		m_pdest += pitch;//m_ddsd.lPitch>>1;
		daddr += xsize;
	}

	m_pdest = (WORD*)gpC_base->m_p_DDSurface_back->GetSurfacePointer();//(WORD*)m_ddsd.lpSurface;
	for (j = 0; j < radius; j++) {
		for (i = 0; i < radius; i++) {
			g = 1;
			double sum = sqrt(i * i + j * j);
			if (sum < radius)        g = dtan((float)(sum / 2.5 + 20));
			a = (radius + j) * xsize;
			b = (radius - j) * xsize;
			c = (int)(j * g);
			d = (int)(i * g);
			e = (int)(c + y) * pitch;
			f = (int)(-c + y) * pitch;
			data[a - i + radius] = m_pdest[e + (int)(-d + x)];
			data[a + i + radius] = m_pdest[e + (int)(d + x)];
			data[b - i + radius] = m_pdest[f + (int)(-d + x)];
			data[b + i + radius] = m_pdest[f + (int)(d + x)];
		}
	}
	m_pdest += sy * pitch + sx;
	daddr = 0;
	for (j = 0; j < ysize; j++) {
		memcpy(m_pdest, &data[daddr], (xsize << 1));
		m_pdest += pitch;
		daddr += xsize;
	}
	gpC_base->m_p_DDSurface_back->Unlock();//m_DDSBack->Unlock(NULL);
	delete data;
}

// ������ 1���� �����ϵ��� �Ͽ���...(�˰����� ��ü�� ���� �ĵ��� ������ �ű���-���� �����ϸ�...)
// ����,����(640,480)...
// ������� ����,�е�, ���� ��...
void Water(int xx, int yy, char Density, char Radius)
{
	gpC_base->m_p_DDSurface_back->Lock();//m_DDSBack->Unlock(NULL);
	WORD* m_pBackSpace = (WORD*)gpC_base->m_p_DDSurface_back->GetSurfacePointer();//(WORD*)m_ddsd.lpSurface;
	static int Height[2][307200], hkind = 0;    // ������� ���� ���� ������ ��	��...
	static WORD WaveScr[307200];
	static WORD Color2; // ǥ���� �ȼ��� WORD ��...
	static int cx, cy, cnt;
	static int addr1, addr2;
	static int HiCurr, HiNext;
	static int xhdif, yhdif, Chdif;
	static int XPos, YPos, OPos;
	static int WcntX1, WcntY1, WcntX2, WcntY2;
	static bool bStarted = false;

	if (bStarted) {
		// Height ���� ã�Ƽ� Waver ����...
		HiNext = Height[0][1];
		for (cnt = 1; cnt < 306560; cnt++) {
			HiCurr = HiNext;
			xhdif = HiCurr - HiNext;
			yhdif = HiCurr - Height[0][cnt + 640];
			HiNext = Height[0][cnt + 1];
			Chdif = 128 - yhdif;
			xhdif >>= 3;
			yhdif >>= 3;
			WcntY1 = cnt >> 10;
			WcntX1 = cnt - (WcntY1 << 10);
			WcntX2 = yhdif + WcntX1;
			WcntY2 = xhdif + WcntY1;
			OPos = (WcntY2 << 10) + WcntX2;
			OPos = OPos >= 0 ? OPos : 0;
			OPos = OPos < 307200 ? OPos : 307199;
			addr1 = OPos / 640; // y ��ġ ã��...
			addr2 = OPos - addr1 * 640; // x ��ġ ã��...
			WORD color = m_pBackSpace[addr1 * 800 + addr2];
			WORD rr = (((color & 0xf800) >> 8) * Chdif) >> 7;
			WORD gg = (((color & 0x7e0) >> 3) * Chdif) >> 7;
			WORD bb = (((color & 0x1f) << 3) * Chdif) >> 7;
			if (rr < 0 || bb < 0 || gg < 0) rr = gg = bb = 0;
			if (rr > 255 || bb > 255 || gg > 255) rr = gg = bb = 255;
			WaveScr[cnt] = ((rr & 0xf8) << 8) | ((gg & 0xfc) << 3) | ((bb & 0xf8) >> 3);
		}

		// ��ȣ ���, �浹 �ۿ���� ó��(Smoothing 2��...)
		// Smooth�� 2���� �޸𸮷� �ݵ�� �����...(�׷��� ������, ��ü �̹��� ��������		����...)
		switch (hkind) {
		case 0:
			for (cnt = 642; cnt < 306559; cnt++) {
				Height[0][cnt] = ((
					Height[1][cnt - 1] +
					Height[1][cnt + 1] +
					Height[1][cnt - 640] +
					Height[1][cnt + 640] +
					Height[1][cnt - 641] +
					Height[1][cnt - 639] +
					Height[1][cnt + 639] +
					Height[1][cnt + 641]
					) >> 2) - Height[0][cnt];
				Height[0][cnt] -= Height[0][cnt] >> Density;
			}
			hkind = 1;
			break;
		case 1:
			for (cnt = 642; cnt < 306559; cnt++) {
				Height[1][cnt] = ((
					Height[0][cnt - 1] +
					Height[0][cnt + 1] +
					Height[0][cnt - 640] +
					Height[0][cnt + 640] +
					Height[0][cnt - 641] +
					Height[0][cnt - 639] +
					Height[0][cnt + 639] +
					Height[0][cnt + 641]
					) >> 2) - Height[1][cnt];
				Height[1][cnt] -= Height[1][cnt] >> Density;
			}
			hkind = 0;
			break;
		}

		// �̹��� Back ���ۿ� �����Ѵ�...
		addr1 = 0;        addr2 = 0;
		for (cy = 0; cy < 480; cy++) {
			memcpy(&m_pBackSpace[addr1], &WaveScr[addr2], 1280);
			addr1 += 800;
			addr2 += 640;
		}
	}
	else {
		int left, top, right, bottom;
		int square, dist;
		int radsquare;
		double length;

		radsquare = Radius * Radius;
		length = (1024.0 / (double)Radius) * (1024.0 / (double)Radius);
		top = -Radius;        left = -Radius;
		bottom = Radius; right = Radius;

		// Perform edge clipping...
		if (xx - Radius < 1)        left -= xx - Radius - 1;
		if (yy - Radius < 1) top -= yy - Radius - 1;
		if (xx + Radius > 639) right -= xx + Radius - 640 + 1;
		if (yy + Radius > 479) bottom -= yy + Radius - 480 + 1;

		for (cy = top; cy < bottom; cy++) {
			addr1 = (cy + yy) * 640;
			for (cx = left; cx < right; cx++) {
				square = cy * cy + cx * cx;
				if (square < radsquare) {
					dist = (int)sqrt(square * length);
					Height[0][addr1 + xx + cx] += (int)((cos(dist) + 0xffff) * 480) >> 19;
				}
			}
		}
		bStarted = true;
	}
	gpC_base->m_p_DDSurface_back->Unlock();//m_DDSBack->Unlock(NULL);
}


void ProgramLoop()
{
	//	if (gC_vs_ui.UpdateState()) //!�� ���콺�����ʹ�~
	if (gbl_game_back)
	{
		static C_SPRITE_PACK m_game_back(SPK_GAME_BACK);
		m_game_back.Blt(0, 0);
	}
	else	gC_DDSurface.FillSurface(15220); // clear the screen buffer 

	// update mouse input state
	g_pDXInput->UpdateInput();

	gC_vs_ui.Process(); // at last
	gC_vs_ui.Show();
	gC_vs_ui.DrawMousePointer(); // Client�� ��û���� ������ ������.

	//	gC_vs_ui.SetZoneName("������Ͼ� NW");
	//	gC_vs_ui.SetTime("23:00:05");

	if (gbl_info_show == true)
	{
		gC_DDSurface.ShowFPS(0, 0, RGB(255, 255, 255), RGB(128, 0, 128));

		char buf[20];

		//sprintf(buf, "%dx%dx%d", RESOLUTION_X, RESOLUTION_Y, gC_DD.Get_BPP());
		sprintf(buf, "%dx%dx%d", g_pUserInformation->iResolution_x, g_pUserInformation->iResolution_y, gC_DD.Get_BPP());
		gC_DDSurface.GDI_Text(90, 0, buf, RGB(255, 255, 255), RGB(128, 0, 128), false);

		// mouse ��ǥǥ��
		sprintf(buf, "(%d, %d)", g_mouse_x, g_mouse_y);
		gC_DDSurface.GDI_Text(500, 0, buf, RGB(255, 255, 255), RGB(128, 0, 128), false);

		if (gbl_ui_input_state)
			gC_DDSurface.GDI_Text(190, 0, "UI input mode", RGB(255, 255, 255), RGB(128, 0, 128), false);
		else
			gC_DDSurface.GDI_Text(190, 0, "Background mode", RGB(255, 255, 255), RGB(128, 0, 128), false);

	}

	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	//	Water(gpC_mouse_pointer->GetX(), gpC_mouse_pointer->GetY(), 3, 100);
	gC_DD.Flip();

}

void
ReleaseAllObject()
{
	gC_vs_ui.Release();

	if (g_pQuestInfoManager != NULL)
	{
		delete g_pQuestInfoManager;
		g_pQuestInfoManager = NULL;
	}

	if (g_pFameInfoTable)
	{
		delete g_pFameInfoTable;

		g_pFameInfoTable = NULL;
	}

	if (g_pRankBonusTable)
	{
		delete g_pRankBonusTable;
		g_pRankBonusTable = NULL;
	}
	if (g_pZoneTable)
	{
		delete g_pZoneTable;
		g_pZoneTable = NULL;
	}
	if (m_pC_dialog)
	{
		delete m_pC_dialog;
		m_pC_dialog = NULL;
	}
	if (g_pUserInformation)
	{
		delete g_pUserInformation;
		g_pUserInformation = NULL;
	}

	if (g_pSoundManager)
	{
		g_pSoundManager->Release();
		delete g_pSoundManager;
		g_pSoundManager = NULL;
	}

	if (g_pProfileManager)
	{
		g_pProfileManager->DeleteProfiles();
		delete g_pProfileManager;
		g_pProfileManager = NULL;
	}

	if (g_pParty != NULL)
	{
		delete g_pParty;
		g_pParty = NULL;
	}

	if (g_pSoundTable != NULL)
	{
		delete g_pSoundTable;
		g_pSoundTable = NULL;
	}

	if (m_pC_dialog != NULL)
	{
		delete m_pC_dialog;
		m_pC_dialog = NULL;
	}

	if (g_pClientConfig != NULL)
	{
		delete g_pClientConfig;
		g_pClientConfig = NULL;
	}

	if (g_pUserOption != NULL)
	{
		delete g_pUserOption;
		g_pUserOption = NULL;
	}

	if (g_pNPCTable != NULL)
	{
		delete g_pNPCTable;
		g_pNPCTable = NULL;
	}

	if (g_pCreatureTable != NULL)
	{
		delete g_pCreatureTable;
		g_pCreatureTable = NULL;
	}

	if (g_pDXInput)
	{
		delete g_pDXInput;
		g_pDXInput = NULL;
	}

	if (g_pInventory != NULL)
	{
		delete g_pInventory;
		g_pInventory = NULL;
	}

	if (g_pSlayerGear != NULL)
	{
		delete g_pSlayerGear;
		g_pSlayerGear = NULL;
	}

	if (g_pVampireGear != NULL)
	{
		delete g_pVampireGear;
		g_pVampireGear = NULL;
	}

	if (g_pOustersGear != NULL)
	{
		delete g_pOustersGear;
		g_pOustersGear = NULL;
	}

	if (g_pGuildInfoMapper != NULL)
	{
		g_pGuildInfoMapper->Release();
		delete g_pGuildInfoMapper;
		g_pGuildInfoMapper = NULL;
	}

	if (g_pGuildMarkManager != NULL)
	{
		delete g_pGuildMarkManager;
		g_pGuildMarkManager = NULL;
	}

	if (g_pAcceleratorManager != NULL)
	{
		delete g_pAcceleratorManager;
		g_pAcceleratorManager = NULL;
	}

	if (g_pKeyAccelerator != NULL)
	{
		delete g_pKeyAccelerator;
		g_pKeyAccelerator = NULL;
	}

	if (g_pItemTable != NULL)
	{
		delete g_pItemTable;
		g_pItemTable = NULL;
	}

	if (g_pItemOptionTable != NULL)
	{
		delete g_pItemOptionTable;
		g_pItemOptionTable = NULL;
	}

	if (g_pMoneyManager != NULL)
	{
		delete g_pMoneyManager;
		g_pMoneyManager = NULL;
	}

	if (g_pPriceManager != NULL)
	{
		delete g_pPriceManager;
		g_pPriceManager = NULL;
	}

	if (g_pSkillInfoTable != NULL)
	{
		delete g_pSkillInfoTable;
		g_pSkillInfoTable = NULL;
	}

	if (g_pSkillManager != NULL)
	{
		delete g_pSkillManager;
		g_pSkillManager = NULL;
	}

	if (g_pExperienceTable != NULL)
	{
		delete g_pExperienceTable;
		g_pExperienceTable = NULL;
	}

	if (g_pSkillAvailable != NULL)
	{
		delete g_pSkillAvailable;
		g_pSkillAvailable = NULL;
	}

	if (g_pTimeItemManager != NULL)
	{
		delete g_pTimeItemManager;
		g_pTimeItemManager = NULL;
	}

	//	if( g_pGameStringTable != NULL )
	//	{
	//		delete g_pGameStringTable;
	//		g_pGameStringTable = NULL;
	//	}
	if (g_pNickNameStringTable != NULL)
	{
		g_pNickNameStringTable->Release();
		DeleteNew(g_pNickNameStringTable);
	}

	DeleteNew(g_pTradeManager);
	DeleteNew(g_pRegenTowerInfoManager);
	DeleteNew(g_pFileDef);
}


//-----------------------------------------------------------------------------

void InitResolutionConfig()
{
	Properties ResolutionConfig;
	ResolutionConfig.load(g_pFileDef->getProperty("FILE_INFO_RESOLUTION").c_str());

	int		nResolutionX = ResolutionConfig.getPropertyInt("ResolutionX");
	int		nResolutionY = ResolutionConfig.getPropertyInt("ResolutionY");

	// VS_UI에 Client 화면에서 쓸 해상도 정보 저장
//	g_pUserInformation->IsResolution1024	= ( nResolutionX == 1024 );
	g_pUserInformation->iResolution_x = nResolutionX;
	g_pUserInformation->iResolution_y = nResolutionY;
}

void SaveResolutionConfig()
{
	std::ofstream file(g_pFileDef->getProperty("FILE_INFO_RESOLUTION").c_str());
	file << "ResolutionX: " << (g_pUserOption->Resolution1024 ? "1024" : "800") << std::endl;
	file << "ResolutionY: " << (g_pUserOption->Resolution1024 ? "768" : "600") << std::endl;
}

/*-----------------------------------------------------------------------------
- WinMainf
- Windows program entry point
-----------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// for Memory Leak Detecting
	if (!iovfs_base::start_vfs("data/darkeden", O_RDONLY))
	{
		MessageBox(
			NULL,
			"Failed to start virtual file system!",
			"Error",
			MB_OK | MB_ICONERROR
		);
		return -1;
	}

	const char* step = "<start>";
	FILE* g_stepLog = fopen("winmain_step.log", "w");
	if (g_stepLog) {
		fputs("=== WinMain step log begin ===\n", g_stepLog);
		fflush(g_stepLog);
	}
	#define STEP(s) do { step = (s); if (g_stepLog) { fputs(step, g_stepLog); fputc('\n', g_stepLog); fflush(g_stepLog); } } while(0)
	try {

		STEP("new Properties + load FILE_INFO_FILEDEF (Data\\Info\\FileDef.inf)");
		g_pFileDef = new Properties;
		g_pFileDef->load(FILE_INFO_FILEDEF);

		g_pUserInformation = new UserInformation;

		InitResolutionConfig();

		g_pUserInformation->attrOperator.SetAttr(OPERATORTYPE_RELEASELOG);

		int tmpDbgFlag;
		tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
		tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(tmpDbgFlag);

		HWND hwnd;
		MSG	msg;
		WNDCLASSEX wcl;

		//-------------------------------------
		// client�� global �ʱ�ȭ by sigi
		//-------------------------------------	
		g_pClientConfig = new ClientConfig;
		//		g_pClientConfig->Use3DHAL			= TRUE;


		g_pUserOption = new UserOption;
		g_pUserOption->Use3DHAL = TRUE;
		g_pUserOption->UseSmoothCursor = FALSE;	//TRUE;
		g_pUserOption->DrawMinimap = FALSE;	// minimap�� �׸���?
		g_pUserOption->DrawZoneName = TRUE;		// Zone�̸� ���
		g_pUserOption->DrawGameTime = TRUE;		// ���� �ð� ���
		g_pUserOption->DrawInterface = FALSE;	// interface
		g_pUserOption->DrawFPS = FALSE;	// FPS
		g_pUserOption->BlendingShadow = FALSE;	//TRUE;			// �׸��� ������
		g_pUserOption->FilteringCurse = TRUE;		// ���� �� ����
		g_pUserOption->PlayMusic = TRUE;		// ���� ���
		g_pUserOption->PlaySound = TRUE;		// ȿ���� ���
		g_pUserOption->VolumeMusic = 10;		// ���� �Ҹ� ũ��
		g_pUserOption->VolumeSound = 10;		// ȿ���� �Ҹ� ũ��
		g_pUserOption->UseEnterChat = true;
		//	g_pUserOption->Resolution1024		= g_pUserInformation->IsResolution1024;

		g_pOperatorOption = new OperatorOption;
		g_pOperatorOption->SetDefault();

		STEP("InitGameStringTable()");
		g_pGameStringTable = new MStringArray;
		InitGameStringTable();

		STEP("g_pRegenTowerInfoManager->LoadRegenTowerInfo()");
		g_pRegenTowerInfoManager = new RegenTowerInfoManager;
		g_pRegenTowerInfoManager->LoadRegenTowerInfo();


		g_pInventory = new MInventory;
		g_pSlayerGear = new MSlayerGear;
		g_pVampireGear = new MVampireGear;
		g_pOustersGear = new MOustersGear;
		g_pTimeItemManager = new MTimeItemManager;

		g_pTimeItemManager->AddTimeItem(0, 70 + (60 * 60));

		STEP("new MGuildMarkManager (loads several SPKs + GuildMapper.inf)");
		g_pGuildMarkManager = new MGuildMarkManager(SPK_GUILD_MARK, FILE_INFO_GUILD_MAPPER, SPK_GRADE_SLAYER, SPK_GRADE_VAMPIRE, SPK_GRADE_OUSTERS, SPK_LEVEL_MARK, SPK_ORIGIN_MARK);
		g_pGuildInfoMapper = new MGuildInfoMapper;

		STEP("Load FILE_INFO_GUILD_MAPPER (Data\\Info\\GuildMapper.inf)");
		ivfstream guildFile(FILE_INFO_GUILD_MAPPER, std::ios::binary);
		g_pGuildInfoMapper->LoadFromFile(guildFile);
		guildFile.close();

		g_pAcceleratorManager = new AcceleratorManager;
		g_pKeyAccelerator = new KeyAccelerator;
		g_pKeyAccelerator->Init(MAX_ACCELERATOR);
		SetDefaultAccelerator();		// �ϴ���..

		g_pSystemAvailableManager = new SystemAvailabilitiesManager;

		STEP("Load FILE_INFO_ITEM_INFO (Data\\Info\\item.inf)");
		g_pItemTable = new ITEMCLASS_TABLE;
		ivfstream itemFile(FILE_INFO_ITEM_INFO, std::ios::binary);
		// --- diagnostic probe: verify file opened and peek first 16 bytes ---
		if (g_stepLog) {
			fprintf(g_stepLog, "  item.inf is_open=%d\n", (int)itemFile.is_open());
			fflush(g_stepLog);
			if (itemFile.is_open()) {
				unsigned char probe[16] = { 0 };
				itemFile.read((char*)probe, 16);
				fprintf(g_stepLog, "  item.inf first16=");
				for (int _i = 0; _i < 16; _i++) fprintf(g_stepLog, "%02X ", probe[_i]);
				unsigned int outerCount = *(unsigned int*)probe;
				unsigned int innerCount = *(unsigned int*)(probe + 4);
				fprintf(g_stepLog, "\n  outerCount=%u innerCount0=%u\n", outerCount, innerCount);
				fflush(g_stepLog);
				itemFile.seekg(0, std::ios_base::beg);
			}
		}
		g_pItemTable->LoadFromFile(itemFile);
		itemFile.close();

		STEP("Load FILE_INFO_NPC_INFO (Data\\Info\\NPC.inf)");
		g_pNPCTable = new MNPCTable;
		ivfstream npcFile(FILE_INFO_NPC_INFO, std::ios::binary);
		g_pNPCTable->LoadFromFile(npcFile);
		npcFile.close();

		STEP("Load FILE_INFO_CREATURE_INFO (Data\\Info\\Creature.inf)");
		g_pCreatureTable = new CREATURE_TABLE;
		ivfstream creatureFile(FILE_INFO_CREATURE_INFO, std::ios::binary);
		g_pCreatureTable->LoadFromFile(creatureFile);
		creatureFile.close();

		STEP("Load FILE_INFO_ZONE_TABLE (Data\\Info\\Zone.inf)");
		g_pZoneTable = new CZoneTable;
		ivfstream zoneFile(FILE_INFO_ZONE_TABLE, std::ios::binary);
		g_pZoneTable->LoadFromFile(zoneFile);
		zoneFile.close();

		STEP("Load FILE_INFO_RANK_BONUS_TABLE (Data\\Info\\RankBonus.inf)");
		g_pRankBonusTable = new RankBonusTable;
		ivfstream rankFile(FILE_INFO_RANK_BONUS_TABLE, std::ios::binary);
		g_pRankBonusTable->LoadFromFile(rankFile);
		rankFile.close();

		g_pItemOptionTable = new ITEMOPTION_TABLE;
		g_pMoneyManager = new MMoneyManager;
		g_pPriceManager = new MPriceManager;

		// infoȭ�� �̸��� MFileDef.h ����	// test
		g_pDXInput = new CDirectInput;

		g_pParty = new MParty;

		STEP("Load data\\info\\questinfo.inf");
		g_pQuestInfoManager = new MQuestInfoManager;
		DWORD ver;

		ivfstream questinfo("data\\info\\questinfo.inf", std::ios::binary);
		questinfo.read((char*)&ver, sizeof(DWORD));
		g_pQuestInfoManager->LoadFromFile(questinfo);
		questinfo.close();

		//---------------------------------------------------------------------
		// nick name string table Loading
		//---------------------------------------------------------------------
		STEP("Load data\\info\\Nickname.inf");
		g_pNickNameStringTable = new MStringArray;
		ivfstream gameStringTableTable("data\\info\\Nickname.inf", std::ios::binary);
		if (false == (*g_pNickNameStringTable).LoadFromFile_NickNameString(gameStringTableTable))
			MessageBox(NULL, "File read Error - NickName.inf", "Error", MB_OK | MB_ICONERROR);
		gameStringTableTable.close();


		//---------------------------------------------------------------------
		//
		//    SkillInfoTable�� ���� ���� ����
		//
		//---------------------------------------------------------------------
		STEP("g_pSkillInfoTable->Init() + Load FILE_INFO_SKILL_INFO (Data\\Info\\SkillInfo.inf)");
		g_pSkillInfoTable = new MSkillInfoTable;
		g_pSkillInfoTable->Init();

		//------------------------------------------------
		// Server ������ loading�Ѵ�.
		//------------------------------------------------
		ivfstream serverSkillInfoFile(FILE_INFO_SKILL_INFO, std::ios::binary);
		g_pSkillInfoTable->LoadFromFileServerSkillInfo(serverSkillInfoFile);
		serverSkillInfoFile.close();

		//---------------------------------------------------------------------
		//
		//    SkillManager�� ���� ���� ����
		//
		//---------------------------------------------------------------------

		STEP("g_pSkillManager->Init() + Load FILE_INFO_SKILL_DOMAIN_EXP (Data\\Info\\DomainExp.inf)");
		g_pSkillManager = new MSkillManager;
		g_pSkillManager->Init();

		//------------------------------------------------
		// Server ������ loading�Ѵ�.
		//------------------------------------------------
		ivfstream serverDomainInfoFile(FILE_INFO_SKILL_DOMAIN_EXP, std::ios::binary);
		g_pSkillManager->LoadFromFileServerDomainInfo(serverDomainInfoFile);
		serverDomainInfoFile.close();


		//---------------------------------------------------
		// ������ ���� ���� ���� ���� Info ������ �ε��Ѵ�.
		//---------------------------------------------------
		STEP("Load Data\\Info\\FameLimit.inf");
		g_pFameInfoTable = new FameInfoTable;
		ivfstream FameLimit("Data\\Info\\FameLimit.inf", std::ios::binary);
		g_pFameInfoTable->LoadFromFile(FameLimit);
		FameLimit.close();

		//---------------------------------------------------------------------
		//
		//    ExperienceTable�� ���� ���� ����
		//
		//---------------------------------------------------------------------

		STEP("new ExperienceTable + open all exp files");
		g_pExperienceTable = new ExperienceTable;

		//------------------------------------------------
		// Load
		//------------------------------------------------
		ivfstream strExpFile(FILE_INFO_STR_EXP, std::ios::binary);
		ivfstream dexExpFile(FILE_INFO_DEX_EXP, std::ios::binary);
		ivfstream intExpFile(FILE_INFO_INT_EXP, std::ios::binary);
		ivfstream vampireExpFile(FILE_INFO_VAMPIRE_EXP, std::ios::binary);
		ivfstream oustersExpFile(FILE_INFO_OUSTERS_EXP, std::ios::binary);
		ivfstream slayerRankExp(FILE_INFO_SLAYER_RANK_EXP, std::ios::binary);
		ivfstream vampireRankExp(FILE_INFO_VAMPIRE_RANK_EXP, std::ios::binary);
		ivfstream oustersRankExp(FILE_INFO_OUSTERS_RANK_EXP, std::ios::binary);
		ivfstream advancementExp(FILE_INFO_ADVANCEMENT_EXP, std::ios::binary);
		ivfstream petExpInfo("DATA\\INFO\\PETEXP.INF", std::ios::binary);

		STEP("ExperienceTable->LoadFromFileSTR (FILE_INFO_STR_EXP)");
		g_pExperienceTable->LoadFromFileSTR(strExpFile);
		STEP("ExperienceTable->LoadFromFileDEX (FILE_INFO_DEX_EXP)");
		g_pExperienceTable->LoadFromFileDEX(dexExpFile);
		STEP("ExperienceTable->LoadFromFileINT (FILE_INFO_INT_EXP)");
		g_pExperienceTable->LoadFromFileINT(intExpFile);
		STEP("ExperienceTable->LoadFromFileVampire (FILE_INFO_VAMPIRE_EXP)");
		g_pExperienceTable->LoadFromFileVampire(vampireExpFile);
		STEP("ExperienceTable->LoadFromFileOusters (FILE_INFO_OUSTERS_EXP)");
		g_pExperienceTable->LoadFromFileOusters(oustersExpFile);
		STEP("ExperienceTable->LoadFromFileSlayerRank (FILE_INFO_SLAYER_RANK_EXP)");
		g_pExperienceTable->LoadFromFileSlayerRank(slayerRankExp);
		STEP("ExperienceTable->LoadFromFileVampireRank (FILE_INFO_VAMPIRE_RANK_EXP)");
		g_pExperienceTable->LoadFromFileVampireRank(vampireRankExp);
		STEP("ExperienceTable->LoadFromFileOustersRank (FILE_INFO_OUSTERS_RANK_EXP)");
		g_pExperienceTable->LoadFromFileOustersRank(oustersRankExp);
		STEP("ExperienceTable->LoadFromFilePetExp (PETEXP.INF)");
		g_pExperienceTable->LoadFromFilePetExp(petExpInfo);
		STEP("ExperienceTable->LoadFromFileAdvanceMent (FILE_INFO_ADVANCEMENT_EXP)");
		g_pExperienceTable->LoadFromFileAdvanceMent(advancementExp);

		strExpFile.close();
		dexExpFile.close();
		intExpFile.close();
		vampireExpFile.close();
		oustersExpFile.close();
		slayerRankExp.close();
		vampireRankExp.close();
		oustersRankExp.close();
		petExpInfo.close();
		advancementExp.close();


		//	g_pSkillInfoTable = new MSkillInfoTable;
		//	g_pSkillManager = new SKILLDOMAIN_TABLE;
		//	g_pSkillManager = new MSkillManager;
		STEP("new MSkillSet + MTradeManager->Init()");
		g_pSkillAvailable = new MSkillSet;

		g_pTradeManager = new MTradeManager;
		g_pTradeManager->Init();
		g_pTradeManager->SetOtherName("�ʻ챳ȯ��");
		g_pTradeManager->GetOtherMoneyManager()->SetMoney(42566);
		g_pTradeManager->GetMyMoneyManager()->SetMoney(13344);


		//CoInitialize(NULL);

	//	HRESULT hr;
	//	if (hr = FAILED(CoCreateInstance(CLSID_InternetExplorer,NULL,
	//		CLSCTX_LOCAL_SERVER, IID_IWebBrowser2,(LPVOID*)&g_pWebBrowser))) 
	//	{
	//		MessageBox(NULL, "IWebBrowser2 Create failed", "ERROR", MB_OK);
	//		return 0;
	//	}

		//
		// `������� �׻� �ϳ��� ������ Ŭ������ ����Ͽ� ���������, ������ Ŭ������
		//  �� �����쿡 ���� �޽����� ó���� ������ ���ν����� �����Ѵ�.
		//
		// `�ϳ��� ������ Ŭ�������� �ϳ� �̻��� �����찡 ������� �� �ִ�.
		//
		STEP("RegisterClassEx (main window class setup)");
		g_hInstance = hInst;
		wcl.hInstance = hInst;
		wcl.lpszClassName = CLASSNAME;
		wcl.lpfnWndProc = WindowProc;
		//
		// `wcl.style =	CS_HREDRAW | CS_VREDRAW;
		//  ���������� ũ�⳪ ���������� ũ�Ⱑ ���� ������ �ٽ� �׷����� �Ѵٴ� ����
		//  ����Ų��. ���� �������� ũ�⸦ �����ϸ� WM_PAINT �޽����� ������.
		//
		wcl.style = CS_HREDRAW;// | CS_VREDRAW;
		wcl.cbSize = sizeof(WNDCLASSEX);
		wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcl.lpszMenuName = NULL; //MAKEINTRESOURCE(KJTMENU);
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		RegisterClassEx(&wcl);

		WAR_INFO s;
		s.left_time = 7200 + (timeGetTime() / 1000);
		s.war_type = 0;
		s.zone_id = 1204;
		s.zone_name = "���Ƹ�����";
		g_pUserInformation->WarInfo.push_back(s);

		InitResolutionConfig();

		STEP("CreateWindowEx (main game window)");
#ifndef _FULLSCREEN
		//* // Window mode
			// Calculate the proper size for the window given a client of 640x480
			//int cx = RESOLUTION_X+GetSystemMetrics(SM_CXSIZEFRAME)*2+2;
			//int cy = RESOLUTION_Y+GetSystemMetrics(SM_CYSIZEFRAME)*2+GetSystemMetrics(SM_CYMENU)+2;

		int cx = g_pUserInformation->iResolution_x + GetSystemMetrics(SM_CXSIZEFRAME) * 2 + 2;
		int cy = g_pUserInformation->iResolution_y + GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYMENU) + 2;


		hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
			CLASSNAME,
			TITLEBARNAME,
			WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW, // WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW  & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX ,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			cx,
			cy,
			HWND_DESKTOP,
			NULL,
			hInst,
			NULL);
		//	*/
#else
		///*	// Fullscreen mode
		hwnd = CreateWindowEx(WS_EX_TOPMOST,
			CLASSNAME,
			TITLEBARNAME,
			WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			0,
			0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CXSCREEN),
			HWND_DESKTOP,
			NULL,
			hInst,
			NULL);
		//*/
#endif

		if (!hwnd) {
			if (g_stepLog) { fputs("CreateWindowEx returned NULL\n", g_stepLog); fflush(g_stepLog); }
			return 0;
		}

		STEP("ShowWindow/UpdateWindow/SetFocus + InitSound()");
		ShowWindow(hwnd, nWinMode);
		UpdateWindow(hwnd);
		SetFocus(hwnd);

		g_hWnd = hwnd;

		InitSound();
		STEP("PAST SOUND");


		STEP("gC_DD.Init (DirectDraw)");
#ifndef _FULLSCREEN
		//
		// Init DirectDraw
		//
		//if (!gC_DD.Init(hwnd, RESOLUTION_X, RESOLUTION_Y, CDirectDraw::WINDOWMODE, false, true))
		//	return 0;

		if (!gC_DD.Init(hwnd, g_pUserInformation->iResolution_x, g_pUserInformation->iResolution_y, CDirectDraw::WINDOWMODE, false, true)) {
			if (g_stepLog) { fputs("gC_DD.Init returned false\n", g_stepLog); fflush(g_stepLog); }
			return 0;
		}

		//gC_DD.Init( hwnd, RESOLUTION_X, RESOLUTION_Y, CDirectDraw::WINDOWMODE);
#else
		//if (!gC_DD.Init(hwnd, RESOLUTION_X, RESOLUTION_Y, CDirectDraw::FULLSCREEN, false, true))
		//	return 0;
		if (!gC_DD.Init(hwnd, g_pUserInformation->iResolution_x, g_pUserInformation->iResolution_y, CDirectDraw::FULLSCREEN, false, true)) {
			if (g_stepLog) { fputs("gC_DD.Init (fullscreen) returned false\n", g_stepLog); fflush(g_stepLog); }
			return 0;
		}
#endif

		STEP("g_pDXInput->Init (DirectInput)");
#if _DEBUGGING
		g_pDXInput->Init(hwnd, hInst, CDirectInput::NONEXCLUSIVE);
#else
		g_pDXInput->Init(hwnd, hInst, CDirectInput::EXCLUSIVE);
#endif

		gC_ci = new CI_KOREAN;
		//gC_ci = new CI_CHINESE;	


		g_pDXInput->SetMouseEventReceiver(MouseEventReceiver);
		//g_pDXInput->SetMouseMoveLimit(RESOLUTION_X-1, RESOLUTION_Y-1);
		g_pDXInput->SetMouseMoveLimit(g_pUserInformation->iResolution_x - 1, g_pUserInformation->iResolution_y - 1);
		g_pDXInput->SetKeyboardEventReceiver(KeyboardEventReceiver);

		STEP("InitializeGL");
		InitializeGL(CDirectDraw::Get_BPP(),
			CDirectDraw::Get_Count_Rbit(),
			CDirectDraw::Get_Count_Gbit(),
			CDirectDraw::Get_Count_Bbit());
		//	gC_font.Initialize();

		STEP("gC_DDSurface.InitBacksurface()");
		gC_DDSurface.InitBacksurface();

		STEP("CIndexSprite::SetColorSet()");
		CIndexSprite::SetColorSet();

		STEP("CSpriteSurface::InitEffectTable()");
		CSpriteSurface::InitEffectTable();
		STEP("gC_vs_ui.Init(&gC_DDSurface, UI_ResultReceiver)");
		gC_vs_ui.Init(&gC_DDSurface, UI_ResultReceiver);


		STEP("new ProfileManager + InitProfiles()");
		g_pProfileManager = new ProfileManager;
		g_pProfileManager->InitProfiles();

		//g_pUserInformation = new UserInformation;
		//WAR_INFO s;
		//s.left_time = 7200+(timeGetTime()/1000);
		//s.war_type = 0;
		//s.zone_id = 1204;
		//s.zone_name = "���Ƹ�����";
		//g_pUserInformation->WarInfo.push_back(s);

		WAR_INFO ss;
		ss.left_time = 3600 + 212 + (timeGetTime() / 1000);
		ss.war_type = 0;
		ss.zone_id = 1201;
		ss.zone_name = "���Ƹ�����a";
		g_pUserInformation->WarInfo.push_back(ss);

		g_char_slot_ingame.m_AdvancementLevel = 10;

		//	gC_vs_ui.StartProgress();
		//	gC_vs_ui.SetProgressStyle(SLAYER_PROGRESS_1); // default 'SLAYER_PROGRESS'
		//
		//	for (int i=0; i<=300; i++)
		//	{
		//		if (i==0)
		//		{
		//			CSpriteSurface* pSurface = new CSpriteSurface;
		//			
		//			pSurface->InitOffsurface(1056, 774);
		//
		//			pSurface->SetTransparency( 0 );
		//
		//			delete pSurface;
		//		}
		//
		//		gC_vs_ui.SetProgress(i, 300);
		//		gC_vs_ui.Show();
		//		gC_DD.Flip();
		//	}

		//gC_vs_ui.EndProgress();

		//g_pUserInformation->IsNetmarble = false;

		g_pUserInformation->IsNetmarble = true;
		g_pUserInformation->IsNetmarbleLogin = true;


		// g_char_slot_ingame ���ӽ��� �� �Լ� ��������� �Ѵ�.
		g_char_slot_ingame.sz_name = "����";
		g_char_slot_ingame.sz_guild_name = "�����Ͷ�ϱ�";
		g_char_slot_ingame.GUILD_ID = 102;
		g_char_slot_ingame.Race = RACE_SLAYER;
		g_char_slot_ingame.bl_drained = true;
		g_char_slot_ingame.MP_MAX = 100;
		g_char_slot_ingame.HP_MAX = 100;
		g_char_slot_ingame.HP = 100;
		g_char_slot_ingame.MP = 230;
		g_char_slot_ingame.FAME = 1234567890;
		g_char_slot_ingame.alignment = UI_GOOD_PLUS;
		g_char_slot_ingame.alignment_num = -10000;
		g_char_slot_ingame.TOHIT = 123;
		g_char_slot_ingame.DAM = 223;
		g_char_slot_ingame.DAM2 = 123;
		g_char_slot_ingame.SILVER_DAM = 3;
		g_char_slot_ingame.SILVER_DAM2 = 1;
		g_char_slot_ingame.STR_CUR = 120;
		g_char_slot_ingame.STR_PURE = 100;
		g_char_slot_ingame.STR_MAX = 130;
		g_char_slot_ingame.STR_EXP_REMAIN = 500;
		g_char_slot_ingame.DEX_CUR = 6;
		g_char_slot_ingame.DEX_PURE = 6;
		g_char_slot_ingame.DEX_MAX = 6;
		g_char_slot_ingame.DEX_EXP_REMAIN = 300;
		g_char_slot_ingame.INT_CUR = 6;
		g_char_slot_ingame.INT_PURE = 6;
		g_char_slot_ingame.INT_MAXX = 6;
		g_char_slot_ingame.INT_EXP_REMAIN = 350;
		g_char_slot_ingame.level = 1;
		g_char_slot_ingame.EXP_REMAIN = 1000000;
		g_char_slot_ingame.SILVER_HP = 0;
		g_char_slot_ingame.GRADE = 36;
		g_char_slot_ingame.WS = 0;
		g_char_slot_ingame.WeaponSpeed = 30;
		g_char_slot_ingame.STATUS.clear();
		g_char_slot_ingame.m_SMS_Charge = 10;
		S_SLOT::UI_EFFECTSTATUS_STRUCT efs;
		/*efs.actionInfo = SKILL_BLOOD_DRAIN;
		efs.delayFrame = timeGetTime()+360000;
		g_char_slot_ingame.STATUS.push_back(efs);
		efs.actionInfo = MAGIC_GREEN_POISON;
		efs.delayFrame = timeGetTime()+360000;
		g_char_slot_ingame.STATUS.push_back(efs);
		efs.actionInfo = MAGIC_YELLOW_POISON;
		efs.delayFrame = timeGetTime()+3700;
		g_char_slot_ingame.STATUS.push_back(efs);
		efs.actionInfo = MAGIC_DARKBLUE_POISON;
		efs.delayFrame = timeGetTime()+80;
		g_char_slot_ingame.STATUS.push_back(efs);
		efs.actionInfo = MAGIC_GREEN_STALKER;
		efs.delayFrame = timeGetTime()+600;*/
		efs.actionInfo = SKILL_CLIENT_HOODLUM_STIGMA;
		efs.delay100msec = 10;
		g_char_slot_ingame.STATUS.push_back(efs);

		//efs.actionInfo = SKILL_CLIENT_CAN_ENTER_GDR_LAIR;
		//efs.delayFrame = timeGetTime()+8000;
		//g_char_slot_ingame.STATUS.push_back(efs);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(MAGIC_GREEN_STALKER);
		//g_char_slot_ingame.STATUS.push_back(SKILL_BLOOD_DRAIN);
		//g_char_slot_ingame.STATUS.push_back(6);
		//g_char_slot_ingame.STATUS.push_back(7);
		//g_char_slot_ingame.STATUS.push_back(8);
		//g_char_slot_ingame.STATUS.push_back(9);
		g_char_slot_ingame.bl_female = true;//false;
		g_char_slot_ingame.man_info.helmet = M_HELMET1;
		g_char_slot_ingame.man_info.coat = M_COAT1;
		g_char_slot_ingame.man_info.trouser = M_TROUSER1;
		g_char_slot_ingame.man_info.hair = M_HAIR1;
		g_char_slot_ingame.man_info.face = M_FACE1;
		g_char_slot_ingame.man_info.left = M_SHIELD1;//M_TR;//M_SWORD;
		g_char_slot_ingame.man_info.right = M_CROSS;//W_SWORD;//W_DRAGON_SHIELD;
		g_char_slot_ingame.skin_color = 0;
		g_char_slot_ingame.hair_color = 0;
		g_char_slot_ingame.left_color = 405;
		g_char_slot_ingame.right_color = 405;
		g_char_slot_ingame.helmet_color = 0xFFFF;
		g_char_slot_ingame.trouser_color = 0XFFFF;
		g_char_slot_ingame.coat_color = 255;
		g_char_slot_ingame.bonus_point = 5;
		g_char_slot_ingame.skill_point = 50;

		//2005.08
		g_char_slot_ingame.AttackBloodBurstPoint = 150;
		g_char_slot_ingame.DefenseBloodBurstPoint = 250;
		g_char_slot_ingame.PartyBloodBurstPoint = 350;


		//	gC_vs_ui.StartTitle();
		//	gC_vs_ui.StartCharacterManager();
		STEP("gC_vs_ui.StartGame()");
		gC_vs_ui.StartGame();
		//	gC_vs_ui.ChangeToOustersInterface();
		gC_vs_ui.ChangeToSlayerInterface();

		std::vector<C_VS_UI_NicknameInfo*>	TempNickNameList;
		C_VS_UI_NicknameInfo nik;
		nik.setNickname("�ٺ�0");
		nik.setNicknameID(0);
		nik.setNicknameIndex(0);
		nik.setNicknameType(0);
		TempNickNameList.push_back(&nik);
		//gC_vs_ui.AddNickNameList((void*)&nik);
		C_VS_UI_NicknameInfo nik1;
		nik1.setNickname("�ٺ�1");
		nik1.setNicknameID(1);
		nik1.setNicknameIndex(1);
		nik1.setNicknameType(1);
		//gC_vs_ui.AddNickNameList((void*)&nik);
		TempNickNameList.push_back(&nik1);
		C_VS_UI_NicknameInfo nik2;
		nik2.setNickname("�ٺ�2");
		nik2.setNicknameID(2);
		nik2.setNicknameIndex(2);
		nik2.setNicknameType(2);
		//gC_vs_ui.AddNickNameList((void*)&nik);
		TempNickNameList.push_back(&nik2);
		C_VS_UI_NicknameInfo nik3;
		nik3.setNickname("�ٺ�3");
		nik3.setNicknameID(3);
		nik3.setNicknameIndex(3);
		nik3.setNicknameType(3);
		//gC_vs_ui.AddNickNameList((void*)&nik);
		TempNickNameList.push_back(&nik3);
		C_VS_UI_NicknameInfo nik4;
		nik4.setNickname("�ٺ�4");
		nik4.setNicknameID(4);
		nik4.setNicknameIndex(4);
		nik4.setNicknameType(4);
		//gC_vs_ui.AddNickNameList((void*)&nik);
		TempNickNameList.push_back(&nik4);
		C_VS_UI_NicknameInfo nik5;
		nik5.setNickname("�ٺ�5");
		nik5.setNicknameID(5);
		nik5.setNicknameIndex(5);
		nik5.setNicknameType(5);
		TempNickNameList.push_back(&nik5);
		gC_vs_ui.SetNickNameList((void*)&TempNickNameList);

		g_char_slot_ingame.m_Powerjjang_Point = 0;
		//gC_vs_ui.AddNickNameList((void*)&nik);
		//	gC_vs_ui.RunQuickItemSlot();

		SIZE size = { 256, 256 };
		gC_vs_ui.SetSize(size);
		gC_vs_ui.SetZone(61);
		RECT rect = { 100, 100, 200, 200 };
		gC_vs_ui.SetSafetyZone(rect, 0);
		SetRect(&rect, 50, 50, 50, 50);
		gC_vs_ui.SetPortal(rect, 1001);
		SetRect(&rect, 50, 52, 60, 52);
		gC_vs_ui.SetPortal(rect, 2024);
		gC_vs_ui.SetNPC(50, 100, 21, "����߳���");

		gC_vs_ui.SetNPC(100, 100, 670, "���չ�");




		//	gC_vs_ui.SetZoneName("������Ͼ� NW");
		//	gC_vs_ui.SetTime("23:00:05");

		//	gC_vs_ui.ServerDisconnectMessage();

		SetCursorPos(0, 0);

		//	gC_vs_ui.SetHP( 80, 100, TRUE );

		//	SIZE size = {256, 256};
		//	gC_vs_ui.SetZone(11);
		//	gC_vs_ui.SetSize(size);


		/*
		// color test
		int color = Convert24RGBto16(180, 240, 0);
		color = Convert24RGBto16(180, 240, 10);
		color = Convert24RGBto16(180, 240, 50);
		color = Convert24RGBto16(159, 151, 146);
		color = Convert24RGBto16(192, 192, 192);
		color = Convert24RGBto16(100, 100, 100);
		*/


		STEP("LoadWorldMapInfo()");
		// ��ü�� ���� �ε�
		LoadWorldMapInfo();

		STEP("Entering main message loop");
		if (g_stepLog) { fputs("=== Reached main message loop ===\n", g_stepLog); fflush(g_stepLog); }
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (GetMessage(&msg, NULL, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					// for delete
					break;
				//return msg.wParam;
			}
			else
			{
				if (gbl_active)
				{
					ProgramLoop();
					g_CurrentFrame++;
				}
				else
					WaitMessage();
			}
		}

		delete g_pGameStringTable;

		SaveResolutionConfig();

		ReleaseAllObject();
		gC_vs_ui.Release();

		// �ػ� ���� ����

	//	if(NULL != g_pWebBrowser)
	//		g_pWebBrowser->Release();
	//	CoUninitialize();
	//	DumpUnfreed();

	}
	catch (Throwable& t) {
		char __msg[4096];
		_snprintf_s(__msg, sizeof(__msg), _TRUNCATE,
			"Step: %s\n\n%s",
			step ? step : "(null)",
			t.toString().c_str());
		if (g_stepLog) {
			fputs("\n*** Throwable caught ***\n", g_stepLog);
			fputs(__msg, g_stepLog);
			fputc('\n', g_stepLog);
			fclose(g_stepLog);
			g_stepLog = NULL;
		}
		MessageBox(NULL, __msg,
			"Fatal Throwable in WinMain", MB_OK | MB_ICONERROR);
		return -1;
	}
	catch (std::exception& e) {
		char __msg[4096];
		_snprintf_s(__msg, sizeof(__msg), _TRUNCATE,
			"Step: %s\n\nstd::exception: %s",
			step ? step : "(null)",
			e.what() ? e.what() : "(no message)");
		if (g_stepLog) {
			fputs("\n*** std::exception caught ***\n", g_stepLog);
			fputs(__msg, g_stepLog);
			fputc('\n', g_stepLog);
			fclose(g_stepLog);
			g_stepLog = NULL;
		}
		MessageBox(NULL, __msg,
			"Fatal std::exception in WinMain", MB_OK | MB_ICONERROR);
		return -1;
	}
	catch (...) {
		char __msg[4096];
		_snprintf_s(__msg, sizeof(__msg), _TRUNCATE,
			"Step: %s\n\nUnknown exception (not Throwable or std::exception)",
			step ? step : "(null)");
		if (g_stepLog) {
			fputs("\n*** Unknown exception caught ***\n", g_stepLog);
			fputs(__msg, g_stepLog);
			fputc('\n', g_stepLog);
			fclose(g_stepLog);
			g_stepLog = NULL;
		}
		MessageBox(NULL, __msg,
			"Fatal unknown exception in WinMain", MB_OK | MB_ICONERROR);
		return -1;
	}

	if (g_stepLog) {
		fputs("=== WinMain exited normally ===\n", g_stepLog);
		fclose(g_stepLog);
		g_stepLog = NULL;
	}
	#undef STEP
	return 0;
}
