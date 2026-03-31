#include "Client_PCH.h"
#include "MItem.h"
#include "MItemTable.h"
#include "AddonDef.h"
#include "SkillDef.h"
#include "SoundDef.h"
#include "MGameStringTable.h"

#ifdef __GAME_CLIENT__
	#include "DebugInfo.h"
#endif



//----------------------------------------------------------------------
//
//							ITEMCLASS_TABLE
//
//----------------------------------------------------------------------
void
ITEMCLASS_TABLE::InitItem2()
{
	int itemType = 0;

	// ----------------------------------------------------------------
	// 염색약
	// ----------------------------------------------------------------
	InitClass(ITEM_CLASS_DYE_POTION, 80
//#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
		+3
//#endif //__JAPAN_REVERSE_DEVELOP
		);
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].HName = "머리염색약 1";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].EName = "Hair-Dye 1";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].SetFrameID( 523 , 537 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].SetDropFrameID( 523 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].HName = "머리염색약 2";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].EName = "Hair-Dye 2";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].SetFrameID( 524, 538, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].SetDropFrameID( 524 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][1].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].HName = "머리염색약 3";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].EName = "Hair-Dye 3";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].SetFrameID( 525, 539, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].SetDropFrameID( 525 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][2].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].HName = "머리염색약 4";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].EName = "Hair-Dye 4";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].SetFrameID( 526, 540, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].SetDropFrameID( 526 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][3].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].HName = "머리염색약 5";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].EName = "Hair-Dye 5";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].SetFrameID( 527, 541, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].SetDropFrameID( 527 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][4].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].HName = "머리염색약 6";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].EName = "Hair-Dye 6";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].SetFrameID( 528, 542, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].SetDropFrameID( 528 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][5].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].HName = "머리염색약 7";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].EName = "Hair-Dye 7";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].SetFrameID( 529 , 543, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].SetDropFrameID( 529 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][6].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].HName = "머리염색약 8";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].EName = "Hair-Dye 8";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].SetFrameID( 530, 544, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].SetDropFrameID( 530 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][7].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].HName = "머리염색약 9";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].EName = "Hair-Dye 9";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].SetFrameID( 531, 545, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].SetDropFrameID( 531);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][8].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].HName = "머리염색약 10";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].EName = "Hair-Dye 10";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].SetFrameID( 532, 546, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].SetDropFrameID( 532 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][9].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].HName = "머리염색약 11";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].EName = "Hair-Dye 11";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].SetFrameID( 533, 547, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].SetDropFrameID( 533);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][10].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].HName = "머리염색약 12";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].EName = "Hair-Dye 12";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].SetFrameID( 534, 548, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].SetDropFrameID( 534);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][11].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].HName = "머리염색약 13";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].EName = "Hair-Dye 13";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].SetFrameID( 535 , 549, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].SetDropFrameID( 535);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][12].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].HName = "머리염색약 14";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].EName = "Hair-Dye 14";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].SetFrameID( 536, 550, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].SetDropFrameID( 536);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][13].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].HName = "머리염색약 15";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].EName = "Hair-Dye 15";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].SetFrameID( 537, 551, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].SetDropFrameID( 537);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][14].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].HName = "머리염색약 16";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].EName = "Hair-Dye 16";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].SetFrameID( 538, 552, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].SetDropFrameID( 538);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][15].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].HName = "머리염색약 17";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].EName = "Hair-Dye 17";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].SetFrameID( 539 , 553, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].SetDropFrameID( 539);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][16].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].HName = "머리염색약 18";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].EName = "Hair-Dye 18";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].SetFrameID( 540, 554 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].SetDropFrameID( 540 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][17].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].HName = "머리염색약 19";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].EName = "Hair-Dye 19";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].SetFrameID( 541, 555 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].SetDropFrameID( 541 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][18].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].HName = "머리염색약 20";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].EName = "Hair-Dye 20";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].SetFrameID( 542,  556, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].SetDropFrameID( 542 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][19].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].HName = "머리염색약 21";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].EName = "Hair-Dye 21";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].SetFrameID( 543, 557 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].SetDropFrameID( 543 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][20].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].HName = "머리염색약 22";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].EName = "Hair-Dye 22";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].SetFrameID( 544, 558, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].SetDropFrameID( 544 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][21].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].HName = "머리염색약 23";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].EName = "Hair-Dye 23";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].SetFrameID( 545 , 559 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].SetDropFrameID( 545 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][22].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].HName = "머리염색약 24";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].EName = "Hair-Dye 24";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].Description = "캐릭터의 머리색을 변경해 줍니다.(뱀파이어 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].SetFrameID( 546, 560, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].SetDropFrameID( 546 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][23].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].HName = "피부염색약 1";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].EName = "Skin-Dye 1";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].SetFrameID( 547, 561, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].SetDropFrameID( 547 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][24].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].HName = "피부염색약 2";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].EName = "Skin-Dye 2";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].SetFrameID( 548,  562, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].SetDropFrameID( 548 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][25].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].HName = "피부염색약 3";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].EName = "Skin-Dye 3";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].SetFrameID( 549, 563, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].SetDropFrameID( 549);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][26].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].HName = "피부염색약 4";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].EName = "Skin-Dye 4";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].SetFrameID( 550, 564, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].SetDropFrameID( 550 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][27].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].HName = "피부염색약 5";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].EName = "Skin-Dye 5";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].SetFrameID( 551, 565, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].SetDropFrameID( 551 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][28].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].HName = "피부염색약 6";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].EName = "Skin-Dye 6";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].SetFrameID( 552, 566, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].SetDropFrameID( 552 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][29].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].HName = "피부염색약 7";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].EName = "Skin-Dye 7";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].SetFrameID( 553 , 567, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].SetDropFrameID( 553);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][30].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].HName = "피부염색약 8";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].EName = "Skin-Dye 8";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].SetFrameID( 554, 568, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].SetDropFrameID( 554 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][31].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].HName = "피부염색약 9";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].EName = "Skin-Dye 9";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].SetFrameID( 555, 569, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].SetDropFrameID( 555 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][32].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].HName = "피부염색약 10";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].EName = "Skin-Dye 10";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].SetFrameID( 556, 570, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].SetDropFrameID( 556 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][33].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].HName = "피부염색약 11";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].EName = "Skin-Dye 11";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].SetFrameID( 557, 571, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].SetDropFrameID( 557 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][34].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].HName = "피부염색약 12";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].EName = "Skin-Dye 12";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].SetFrameID( 558, 572, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].SetDropFrameID( 558 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][35].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].HName = "피부염색약 13";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].EName = "Skin-Dye 13";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].SetFrameID( 559, 573, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].SetDropFrameID( 559 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][36].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].HName = "피부염색약 14";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].EName = "Skin-Dye 14";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].SetFrameID( 560, 574 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].SetDropFrameID( 560 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][37].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].HName = "피부염색약 15";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].EName = "Skin-Dye 15";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].SetFrameID( 561, 575, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].SetDropFrameID( 561 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][38].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].HName = "피부염색약 16";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].EName = "Skin-Dye 16";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].SetFrameID( 562, 576, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].SetDropFrameID( 562 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][39].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].HName = "피부염색약 17";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].EName = "Skin-Dye 17";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].SetFrameID( 563, 577 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].SetDropFrameID( 563 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][40].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].HName = "피부염색약 18";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].EName = "Skin-Dye 18";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].SetFrameID( 564, 578, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].SetDropFrameID( 564);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][41].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].HName = "피부염색약 19";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].EName = "Skin-Dye 19";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].SetFrameID( 565, 579, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].SetDropFrameID( 565 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][42].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].HName = "피부염색약 20";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].EName = "Skin-Dye 20";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].SetFrameID( 566, 580, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].SetDropFrameID( 566 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][43].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].HName = "피부염색약 21";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].EName = "Skin-Dye 21";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].SetFrameID( 567, 581, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].SetDropFrameID( 567 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][44].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].HName = "피부염색약 22";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].EName = "Skin-Dye 22";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].SetFrameID( 568, 582, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].SetDropFrameID( 568 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][45].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].HName = "피부염색약 23";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].EName = "Skin-Dye 23";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].SetFrameID( 569, 583, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].SetDropFrameID( 569);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][46].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].HName = "피부염색약 24";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].EName = "Skin-Dye 24";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].Description = "캐릭터의 피부색을 변경해 줍니다. (아우스터즈 사용 불가능)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].SetFrameID( 570, 584, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].SetDropFrameID( 570 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][47].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].HName = "성전환 아이템";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].EName = "Change Sex Item";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].Description = "캐릭터의 성별을 변경합니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].SetFrameID( 711, 725, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].SetDropFrameID( 711 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][48].Price =0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].HName = "그린 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].EName = "Green Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].SetFrameID( 775, 798, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].SetDropFrameID( 775 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][49].SetGrid( 1, 1 );
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].HName = "블루 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].EName = "Blue Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].SetFrameID( 776, 799, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].SetDropFrameID( 776 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][50].SetGrid( 1, 1 );
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].HName = "레드 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].EName = "Red Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].SetFrameID( 777, 800, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].SetDropFrameID( 777 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][51].SetGrid( 1, 1 );

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].HName = "옐로우 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].EName = "Yellow Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].SetFrameID( 778, 801, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].SetDropFrameID( 778 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][52].SetGrid( 1, 1 );

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].HName = "화이트 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].EName = "White Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].SetFrameID( 779, 802, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].SetDropFrameID( 779 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][53].SetGrid( 1, 1 );

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].HName = "스카이 블루 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].EName = "Sky Blue Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].SetFrameID( 780, 803, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].SetDropFrameID( 780 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][54].SetGrid( 1, 1 );

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].HName = "라일락 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].EName = "Lilac Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].SetFrameID( 781, 804, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].SetDropFrameID( 781 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][55].SetGrid( 1, 1 );
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].HName = "블랙 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].EName = "Black Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].SetFrameID( 782, 805, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].SetDropFrameID( 782 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][56].SetGrid( 1, 1 );

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].HName = "네츄럴 카멜레온 포션";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].EName = "Natural Chameleon Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].Description = "";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].SetFrameID( 783, 806, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].SetDropFrameID( 783 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][57].SetGrid( 1, 1 );	

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].HName = "피어 오오라 스톤";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].EName = "Fear Aura Stone";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].Description = "99이하 캐릭터나 승직 캐릭터는 사용할 수 없습니다 ." ; //100레벨 이상 캐릭터만 사용할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].SetFrameID( 982,1016, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].SetDropFrameID( 982 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][58].SetGrid( 1, 1 );	

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].HName = "크럴 오오라 스톤";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].EName = "Cruel Aura Stone";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].Description = "99이하 캐릭터나 승직 캐릭터는 사용할 수 없습니다 ." ; //100레벨 이상 캐릭터만 사용할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].SetFrameID( 983,1017, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].SetDropFrameID( 983 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][59].SetGrid( 1, 1 );	

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].HName = "호프 오오라 스톤";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].EName = "Hope Aura Stone";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].Description = "99이하 캐릭터나 승직 캐릭터는 사용할 수 없습니다 ." ; //100레벨 이상 캐릭터만 사용할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].SetFrameID( 984,1018, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].SetDropFrameID( 984 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][60].SetGrid( 1, 1 );	

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].HName = "내츄럴 오오라 스톤";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].EName = "Natural Aura Stone";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].Description = "99이하 캐릭터나 승직 캐릭터는 사용할 수 없습니다 ." ; //100레벨 이상 캐릭터만 사용할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].SetFrameID( 981, 1015, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].SetDropFrameID( 981 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][61].SetGrid( 1, 1 );	

	
	// 2005.05.12 sjheon  4월 신규 마켓 아이템  add
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].HName = "오오라 크리스탈";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].EName = "Aura Crystal";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].Description = "호루스 등급 이상 캐릭터만 사용가능합니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].SetFrameID( 993, 1027, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].SetDropFrameID( 993 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][62].SetGrid( 1, 1 );	


	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].HName = "네츄럴 오오라 크리스탈";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].EName = "Natural Aura Crystal";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].Description = "호루스 등급 이상 캐릭터만 사용가능합니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].SetFrameID( 993, 1027, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].SetDropFrameID( 993 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][63].SetGrid( 1, 1 );	
	// 2005.05.12 sjheon  4월 신규 마켓 아이템 add
	
	// 2005.08.14 sjheon  8월 신규 마켓 아이템  add	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].HName = "계급스킬 초기화 물약 ";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].EName = "Grade Skill Cleaner Potion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].Description = "계급스킬을 초기화하는 물약입니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].SetFrameID( 999, 1033, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].SetDropFrameID( 999 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][64].SetGrid( 1, 1 );	
	// 2005.08.14 sjheon  8월 신규 마켓 아이템  End		

	// 2006.04.22 chyaya 일본 마켓 아이템 Add

// 2006.2.7 nanomech 일본 상용화 마켓 아이템 start
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].HName = "망각의 붉은 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].EName = "Red Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].Description = "힘 능력치를 초기화 해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].SetFrameID( 1127, 1155, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].SetDropFrameID( 1127 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].Price = 200000;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][65].ItemMoveControl = ITEMMOVE_CANNOT_DROP|ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP|ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].HName = "망각의 녹색 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].EName = "Green Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].Description = "민첩 능력치를 초기화 해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].SetFrameID( 1126, 1154, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].SetDropFrameID( 1126 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].Price = 200000;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][66].ItemMoveControl = ITEMMOVE_CANNOT_DROP|ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP|ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].HName = "망각의 푸른 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].EName = "Blue Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].Description = "지식 능력치를 초기화 해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].SetFrameID( 1128, 1156, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].SetDropFrameID( 1128 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].Price = 200000;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][67].ItemMoveControl = ITEMMOVE_CANNOT_DROP|ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP|ITEMMOVE_CANNOT_TRADE;
	// 2006.2.7 nanomech 일본 상용화 마켓 아이템 end




	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].HName = "네츄럴 컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].EName = "Nature Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].SetFrameID( 1034, 1068, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].SetDropFrameID( 1034 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][68].Price = 0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].HName = "레드컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].EName = "Red Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].SetFrameID( 1035 , 1069 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].SetDropFrameID( 1035 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][69].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].HName = "블루컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].EName = "Blue Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].SetFrameID( 1036, 1070, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].SetDropFrameID( 1036 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][70].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].HName = "그린 컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].EName = "Green Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].SetFrameID( 1037, 1071, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].SetDropFrameID( 1037 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][71].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].HName = "인디고 컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].EName = "Indigo Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].SetFrameID( 1038, 1072, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].SetDropFrameID( 1038 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][72].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].HName = "오랜지컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].EName = "Orange Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].SetFrameID( 1039, 1073, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].SetDropFrameID( 1039 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][73].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].HName = "엘로우 컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].EName = "Yellow Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].SetFrameID( 1040, 1074, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].SetDropFrameID( 1040 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][74].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].HName = "화이트 컬러 페인트";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].EName = "White Color Paint";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].SetFrameID( 1041 , 1075, 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].SetDropFrameID( 1041 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].SetGrid( 2, 2);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][75].Price = 0;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].HName = "적색 안개 가루";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].EName = "Red Fog Powder";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].Description = "박쥐 변신 색을 변경할 수 있는 소모성 아이템 (승직 전용)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].SetFrameID( 1113 , 1141 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].SetDropFrameID( 1113 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][76].Price = 1;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].HName = "청색 안개 가루";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].EName = "Blue Fog Powder";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].Description = "박쥐 변신 색을 변경할 수 있는 소모성 아이템 (승직 전용)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].SetFrameID( 1115 , 1143 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].SetDropFrameID( 1115 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][77].Price = 1;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].HName = "안개 가루";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].EName = "Fog Powder";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].Description = "박쥐 변신 색을 변경할 수 있는 소모성 아이템 (승직 전용)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].SetFrameID( 1123 , 1151 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].SetDropFrameID( 1123 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][78].Price = 1;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].HName = "녹색 안개 가루";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].EName = "Green Fog Powder";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].Description = "박쥐 변신 색을 변경할 수 있는 소모성 아이템 (승직 전용)";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].SetFrameID( 1125 , 1153 , 0);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].SetDropFrameID( 1125 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].SetValue( 3, 1, -1, -1, -1, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][79].Price = 1;

//#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].HName = "고대 망각의 붉은 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].EName = "Ancient Red Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].Description = "힘 능력치를 모두 초기화 해줍니다";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].SetFrameID( 1269, 1311, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].SetDropFrameID( 1269);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][80].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].HName = "고대 망각의 녹색 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].EName = "Ancient Green Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].Description = "민첩성 능력치를 모두 초기화 해줍니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].SetFrameID( 1268, 1310, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].SetDropFrameID( 1268);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][81].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].HName = "고대 망각의 푸른 수정";								  
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].EName = "Ancient Blue Crystal of Oblivion";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].Description = "지식 능력치를 모두 초기화 해줍니다.";
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].SetFrameID( 1270, 1312, 0 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].SetDropFrameID( 1270);
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DYE_POTION][82].Price = 200000;
//#endif //__JAPAN_REVERSE_DEVELOP

	// 2006.04.22 chyaya 일본 마켓 아이템 End
	// ----------------------------------------------------------------------
	// 부활 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_RESURRECT_ITEM, 2);
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].HName = "부활 스크롤";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].EName = "Resurrection Scroll";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].Description = "빈사 상태에서 다시 부활 할 때 사용하는 아이템 입니다";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].SetFrameID( 589, 603, 0);
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].SetDropFrameID( 589 );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][0].Price =0;

	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].HName = "엘릭서 스크롤";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].EName = "Elixir Scroll";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].Description = "빈사상태에서 부활 및 일부 이상 상태를 완전하게 회복할 수 있는 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].SetFrameID( 588, 602, 0);
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].SetDropFrameID( 588 );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].SetValue( 3,1,-1,-1,-1,0 );
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].SetGrid( 1, 1);
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_RESURRECT_ITEM][1].Price =0;
	

	// ----------------------------------------------------------------------
	// 믹싱포지 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_MIXING_ITEM, 29
#if __CONTENTS(__PET_MIXINGFORGE)
		+2
#endif //__PET_MIXINGFORGE
#if __CONTENTS(__IMI_MIXNGFORGE)
		+3
#endif //__IMI_MIXNGFORGE
		);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].HName = "웨픈 믹싱 포지 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].EName = "Weapon Mixing Forge Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].SetFrameID( 582,596,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].SetDropFrameID( 582 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][0].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].HName = "웨픈 믹싱 포지 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].EName = "Weapon Mixing Forge Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].SetFrameID( 582,596,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].SetDropFrameID( 582 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][1].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].HName = "웨픈 믹싱 포지 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].EName = "Weapon Mixing Forge Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].SetFrameID( 582,596,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].SetDropFrameID( 582 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][2].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].HName = "아머 믹싱 포지 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].EName = "Armor Mixing Forge Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].SetFrameID( 584,598,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].SetDropFrameID(584);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][3].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].HName = "아머 믹싱 포지 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].EName = "Armor Mixing Forge Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].SetFrameID( 584,598,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].SetDropFrameID(584);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][4].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].HName = "아머 믹싱 포지 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].EName = "Armor Mixing Forge Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].SetFrameID( 584,598,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].SetDropFrameID(584);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][5].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].HName = "액세서리 믹싱 포지 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].EName = "Accessory Mixing Forge Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].SetFrameID( 583,597,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].SetDropFrameID(583);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][6].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].HName = "액세서리 믹싱 포지 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].EName = "Accessory Mixing Forge Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].SetFrameID( 583,597,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].SetDropFrameID(583);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][7].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].HName = "액세서리 믹싱 포지 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].EName = "Accessory Mixing Forge Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].SetFrameID( 583,597,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].SetDropFrameID(583);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][8].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].HName = "웨픈 퓨리타스 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].EName = "Weapon Puritas Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].SetFrameID( 594,608,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].SetDropFrameID( 594 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][9].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].HName = "웨픈 퓨리타스 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].EName = "Weapon Puritas Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].SetFrameID( 594,608,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].SetDropFrameID( 594 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][10].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].HName = "웨픈 퓨리타스 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].EName = "Weapon Puritas Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].SetFrameID( 594,608,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].SetDropFrameID( 594 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][11].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].HName = "아머 퓨리타스 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].EName = "Armor Puritas Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].SetFrameID( 595,609,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].SetDropFrameID(595);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][12].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].HName = "아머 퓨리타스 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].EName = "Armor Puritas Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].SetFrameID( 595,609,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].SetDropFrameID(595);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][13].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].HName = "아머 퓨리타스 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].EName = "Armor Puritas Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].SetFrameID( 595,609,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].SetDropFrameID(595);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][14].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].HName = "액세서리 퓨리타스 A형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].EName = "Accessory Puritas Type A";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].SetFrameID( 596,610,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].SetDropFrameID(596);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][15].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].HName = "액세서리 퓨리타스 B형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].EName = "Accessory Puritas Type B";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].SetFrameID( 596,610,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].SetDropFrameID(596);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][16].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].HName = "액세서리 퓨리타스 C형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].EName = "Accessory Puritas Type C";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].SetFrameID( 596,610,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].SetDropFrameID(596);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][17].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].HName = "복조리";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].EName = "bokjory";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].Description = "단일 옵션 아이템을 무옵션 아이템으로 변환시켜 줍니다";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].SetFrameID( 978,1012,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].SetDropFrameID(978);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][18].Price = 0;


	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].HName = "웨픈 믹싱 포지 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].EName = "Weapon Mixing Forge Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].SetFrameID( 582,596,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].SetDropFrameID(582);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][19].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].HName = "아머 믹싱 포지 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].EName = "Armor Mixing Forge Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].SetFrameID( 584,598,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].SetDropFrameID(584);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][20].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].HName = "액세서리 믹싱 포지 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].EName = "Accessory Mixing Forge Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].SetFrameID( 583,597,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].SetDropFrameID(583);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][21].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].HName = "웨픈 퓨리타스 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].EName = "Weapon Puritas Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].SetFrameID( 594,608,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].SetDropFrameID(594);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][22].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].HName = "아머 퓨리타스 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].EName = "Armor Puritas Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].SetFrameID( 595,609,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].SetDropFrameID(595);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][23].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].HName = "액세서리 퓨리타스 D형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].EName = "Accessory Puritas Type D";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].Description = "레어아이템의 필요없는 옵션을 제거할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].SetFrameID( 596,610,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].SetDropFrameID(596);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][24].Price = 0;

	// 2005.05.12 sjheon  4월 신규 마켓 아이템  add
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].HName = "퍼지 몬드";								  
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].EName = "Purge Mound";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].Description = "매직 아이템에서 옵션을 제거합니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].SetFrameID( 995, 1029, 0 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].SetDropFrameID( 995 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][25].SetGrid( 1, 1 );	
	// 2005.05.12 sjheon  4월 신규 마켓 아이템 add

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].HName = "웨픈 믹싱 포지 E형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].EName = "Weapon Mixing Forge Type E";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다. (승직전용)";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].SetFrameID( 582,596,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].SetDropFrameID( 582 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][26].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].HName = "아머 믹싱 포지 E형";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].EName = "Armor Mixing Forge Type E";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다. (승직전용)";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].SetFrameID( 584,598,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].SetDropFrameID(584);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][27].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].HName = "퓨리타스";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].EName = "Puritas";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].Description = "레어 아이템의 필요 없는 옵션을 제거 합니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].SetFrameID( 1158, 1185, 0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].SetDropFrameID( 1158 );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][28].Price = 0;
#if __CONTENTS(__PET_MIXINGFORGE)
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].HName = "펫 조합기";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].EName = "Pet Conpound";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].Description = "두 마리의 펫을 조합하여 새로운 옵션을 부여할 수 있는 1회용 조합기 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].SetFrameID(1343,1387,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].SetDropFrameID(1343);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][29].SetGrid(2,2);


	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].HName = "펫 조합 초기화 물약";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].EName = "Pet Separate";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].Description = "조합으로 인해 추가된 옵션을 제거해주는 1회용 초기화 물약 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].SetFrameID(1342, 1386, 0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].SetDropFrameID(1342);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][30].SetGrid(2,2);


#endif //__PET_MIXINGFORGE

#if __CONTENTS(__IMI_MIXNGFORGE)
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].HName = "웨픈 믹싱 포지";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].EName = "Weapon Mixing Forge";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].SetFrameID( 1397, 1441, 0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].SetDropFrameID(1397);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][31].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].HName = "아머 믹싱 포지";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].EName = "Armor Mixing Forge";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].SetFrameID( 1395, 1439, 0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].SetDropFrameID(1395);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].SetGrid(2,2);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][32].Price = 0;

	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].HName = "액세서리 믹싱 포지";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].EName = "Accessory Mixing Forge";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].Description = "옵션이 다른 같은 아이템을 합칠 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].SetFrameID( 1396, 1440, 0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].SetDropFrameID(1396);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].SetValue( 3,1,-1,-1,-1,0);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].SetGrid(1,1);
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MIXING_ITEM][33].Price = 0;
#endif //__IMI_MIXNGFORGE

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 암스밴드 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_ARMSBAND, 14 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)
		+1
#endif

#if __CONTENTS(__QUEST_RENEWAL)
		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

		);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "우드 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Wood Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(617, 631, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(617);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "아율베딕 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Ayurvedic Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(618, 632, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(618);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "레인보우 웨이브 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Rainbow Wave Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(619, 633, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(619);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "컬럼 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Column Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(620, 634, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(620);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "블라즘 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Blossom Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(621, 635, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(621);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "세일지 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Selge Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(622, 636, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(622);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "프리스트 헤리허 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Priest Herihor Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(623, 637, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(623);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "자렛 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Zaret Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(624, 638, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(624);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "고르간 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Gurgan Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(625, 639, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(625);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "쿠그나스 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Kugnas Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(626, 640, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(626);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "키케다 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Cicada Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1106, 840, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1106);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "물라다라 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Muladhara Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1104, 841, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1104);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "바인드 룬 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Bindrune Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(819, 842, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(819);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "드라이어드릭 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Dryadric Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1102 , 934 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1102);
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "리르 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Lir Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1104, 841, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1104);
	itemType++;

#endif

#if __CONTENTS(__QUEST_RENEWAL)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "네이쳐스 웨이브 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Nature's Wave Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(619, 633, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(619);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Price	=  2400;
	itemType++;
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	// itemType = 16
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "플라이트 암스밴드";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Flight Armsband";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1258, 1301, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1258);
	itemType++;

	// itemType = 17
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].HName = "사이드 암즈 그라인더";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].EName = "Side Arms Grinder";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetFrameID(1102 , 934 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_ARMSBAND][itemType].SetDropFrameID(1102);
	itemType++;
#endif //__NEW_ADVANCEMENT_ITEM


	itemType = 0;

	// ----------------------------------------------------------------------
	// 아우스터즈 부츠 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_BOOTS, 14 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__QUEST_RENEWAL)
		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM
		);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "드라이어드 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Dryad\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 692, 706, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(692);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "오레아스 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Oread\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 693, 707, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID( 693);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "스프라이트 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Sprite\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 694, 708, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID( 694);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "피스트롬 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Fisthrom\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 695, 709, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID( 695);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "레프리컨 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Leprekaun\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 696, 710, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID( 696);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "데지리쉬 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Desirish\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 697, 711, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(697);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "윌 오 더 위스프 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Will O\' the Wisp\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 698, 712, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(698);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "쉐이드 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Shade\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 699, 713, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(699);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "페이트리스 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Fateris\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 811, 834, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(811);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "에페리얼 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Epereal\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 812, 835, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(812);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "아마테라스 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Amaterasu\'s Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 813, 836, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(813);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "네이픈 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Naphne Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 908 , 931,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(908);
	itemType++;

	// 12
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "프라엘리움 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Praelium boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 962, 998, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(962 );
	itemType++;
	
	// 13
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "임페리움 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Imperium boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 1076 , 1110, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(1076 );
	itemType++;
	
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "리르 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Lir Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 812, 835, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(812);
	itemType++;

#endif

#if __CONTENTS(__QUEST_RENEWAL)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "네이쳐스 스프라이트 부츠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Nature's Sprite's Boots";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 694, 708, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID( 694);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Price	=  12800;
	itemType++;
#endif

//	m_pTypeInfo[ITEM_CLASS_GAITER][1].HName = "임페리움 부츠";
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].EName = "Imperium boots";
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_GAITER][1].Price = 0;	

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	// itemType = 16
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "엘 레원 라펠";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "El Leon Lapel";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 1256, 1299, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(1256);
	itemType++;

	// itemType = 17
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].HName = "아르카디아 튜블러";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].EName = "Arkadhia Tublar";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetFrameID( 1076 , 1110, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_BOOTS][itemType].SetDropFrameID(1076 );
	itemType++;
#endif //__NEW_ADVANCEMENT_ITEM

	itemType = 0;

	// ----------------------------------------------------------------------
	// 아우스터즈 챠크람 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_CHAKRAM, 19 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__QUEST_RENEWAL)
		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

		);

	// 0
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "토우 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Tou Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(632, 646, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(632);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 1
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "퍼브 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Perv Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(633, 647, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(633);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 2
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "아베스 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Aves Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(634, 648, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(634);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 3
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "뉴보 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Nuevo Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(635, 649, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(635);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 4
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "아니마 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Anima Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(636, 650, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(636);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 5
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "리트라 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Raetra Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(700, 714, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(700);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 6
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "페슈이의 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Pesuy\'s Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(701, 715, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(701);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 7
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "브라부스 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Brabus Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(702, 716, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(702);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 8
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "메듀 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Meduh Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(703, 717, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(703);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 9
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "크루오르 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Cruor Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(704, 718, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(704);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 10
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "하이사 문 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Moon of Haisa Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(820, 843, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(820);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 11
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "아즈나 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Ajna Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(821, 844, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(821);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 12
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "윈드 갓 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Wind God Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(822, 845, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(822);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;
	
	// 13
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "루드라 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Rudra Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(914 , 937 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(914);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;
			
	// 14
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "멜리스 차크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Melis chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID( 964, 1000, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(964 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );	
	itemType++;

	// Sjheon 2005.06.02 Add
	// 15
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "브레히트 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Brecht Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(702, 716, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(702);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 16
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "아큐트 크루오르 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Acute Cruor Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(704, 718, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(704);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// 17
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "아큐트 아즈나 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Acute Ajna Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(821, 844, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(821);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

	// Sjheon 2005.06.02 Add
	// 18
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "란테아 차크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Rantea chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(1073, 1107, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(1073);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "리르 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Lir Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(821, 844, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(821);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	itemType++;

#endif

#if __CONTENTS(__QUEST_RENEWAL)	//아이템 추가		리트라 챠크람
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "네이쳐스 리트라 챠크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Naturer's Raetra Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(700, 714, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(700);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Price	= 25600;
#endif	//__QUEST_RENEWAL

	//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].HName = "란테아 차크람";
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].EName = "Rantea chakram";
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_ORBIS][1].Price = 0;	

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	itemType++; // 21
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "바라사다 차크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Barasada Chakram";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(1251, 1294, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(1251);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetValue(52000, -1, 53, 67, -1, -1, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Price = 7000000;

	itemType++; // 22
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].HName = "타르빙 차크람";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].EName = "Chakram Of Tyrfingr";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetFrameID(1073, 1107, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetDropFrameID(1073);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetAddonFrameID( 0, 0 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].SetValue(53000, -1, 63, 77, -1, -1, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CHAKRAM][itemType].Price = 8000000;	
#endif //__NEW_ADVANCEMENT_ITEM

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 써클릿 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_CIRCLET, 14 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

		);
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "실버 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Silver Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(607, 621, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(607);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "만월의 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Circlet of Full Moon";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(608, 622, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(608);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "펜타클 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Pentacle Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(609, 623, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(609);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "실바나 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Sylvana Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(610, 624, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(610);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "컬럼 오브 워터 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Column of Water Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(611, 625, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(611);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "로더 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Lothar Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(612, 626, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(612);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "서클릿 오브 소율라";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Circlet of Solyulia";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(613, 627, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(613);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "듀크의 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Duke\'s Chrystopher Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(614, 628, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(614);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "폭염의 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Prominence Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(615, 629, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(615);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "다이어덤 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Diadem Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(616, 630, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(616);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "알키오네 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Alcyone Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(814, 837, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(814);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "마스테마 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Mastema Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(815, 838, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(815);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "타이라 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Taira Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(816, 839, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(816);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "질리오트 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Gilleot Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(927 , 950 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(927);
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "리르 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Lir Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(815, 838, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(815);
	itemType++;

#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	// itemType = 14
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "시르 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Syr Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(1255, 1298,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(1255);
	itemType++;

	// itemType = 15
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].HName = "로얄 서클릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].EName = "Royal Circlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetFrameID(927 , 950 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_CIRCLET][itemType].SetDropFrameID(927);
	itemType++;
#endif //__NEW_ADVANCEMENT_ITEM

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 코트 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_COAT, 14 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__QUEST_RENEWAL)
		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

		);

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "드라이어드 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Dryad\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(662, 676, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(662);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 1, 1 );
	//m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 4, 4 );

	//m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 4, 10 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "오레아스 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Oread\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(663, 677, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(663);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 1, 1 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "스프라이트 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Sprite\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(664, 678, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(664);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 1, 1 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "피스트롬 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Fisthrom\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(665, 679, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(665);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 2, 2 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "레프리컨 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Leprekaun\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(705, 719, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(705);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 2, 2 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "데지리쉬 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Desirish\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(706, 720, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(706);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 2, 2 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "윌 오 더 위스프 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Will o\' the wisp\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(707, 721, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(707);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "셰이드 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Shade\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(708, 722, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(708);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "페이트리스 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Fateris\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(824, 846, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(824);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "에페리얼 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Epereal\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(823, 847, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(823);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "아마테라스 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Amaterasu\'s Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(825, 848, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(825);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "네이픈 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Naphne Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(909 , 932 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(909);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 4, 4 );
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "프라엘리움 베스티오";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Praelium vestio";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID( 963, 999, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(963 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;
				
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "임페리움 베스티오";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Imperium vestio";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID( 1075, 1109, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(1075 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;
	
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "리르 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Lir Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(823, 847, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(823);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

#endif

#if __CONTENTS(__QUEST_RENEWAL)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "네이쳐스 스프라이트 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Nature's Sprite's Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID(664, 678, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(664);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Price	=  16000;
	itemType++;
#endif

//	m_pTypeInfo[ITEM_CLASS_CASCA][1].HName = "임페리움 베스티오";
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].EName = "Imperium vestio";
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_CASCA][1].Price = 0;	

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	// itemType = 16
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "엘리시움 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Elysium Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID( 1257, 1300, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(1257);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;

	// itemType = 17
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].HName = "크라운 코트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].EName = "Crown Coat";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetFrameID( 1075, 1109, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetDropFrameID(1075 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_COAT][itemType].SetAddonFrameID( 3, 3 );
	itemType++;
#endif //__NEW_ADVANCEMENT_ITEM

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 펜던트 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_PENDENT, 15 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ADVANCEMENT_NEW_UNIQUE_ITEM)
		+1
#endif //__ADVANCEMENT_NEW_UNIQUE_ITEM
		);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "리버스 닷 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Revers Dot Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(597, 611, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(597);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "오리샤 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = 			"Orissa Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(598, 612, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(598);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "미스틱 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = 			"Mystic Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(599, 613, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(599);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "이져실 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = 			"Yggdrasil Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(600, 614, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(600);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "시뉴이의 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Sinui\'s Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(601, 615, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(601);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "아이즈 오브 호러스 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Eyes of Horus Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(602, 616, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(602);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "엔트 페이스 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Ent Face Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(603, 617, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(603);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "피뷸라 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Fibula Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(604, 618, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(604);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "피어리 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Fairie Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(605, 619, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(605);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "이집티안 팔콘 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Egyptian Falcon Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(606, 620, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(606);
	itemType++;

	// 10
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "피그 트리 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Fig Tree Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(826, 849, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(826);
	itemType++;
	
	// 11
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "오팔루스 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Opalus Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(827, 850, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(827);
	itemType++;
	
	// 12
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "카발라 트리 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Kabbala Tree Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(828, 851, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(828);
	itemType++;

	// 13
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "레쉬 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Leshy Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(1103 , 936 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(1103);
	itemType++;

	// 14
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "헬 가든의 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Necklace Of Hellgarden";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "헬 가든의 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(1103 , 936 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(1103);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

	// 15
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "리르 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Lir Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(827, 850, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(827);
	itemType++;

#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "룬 다이아 팬던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Runic Diamond Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(1249, 1292 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(1249);
	itemType++;	// 16

	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "아스틴 팬던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Astin Pendent";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID(1103 , 936 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID(1103);
	itemType++;	// 17
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ADVANCEMENT_NEW_UNIQUE_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].HName = "라드키아의 눈물";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].EName = "Tear of Radchia";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetFrameID( 1336, 1380 ,0 );	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].SetDropFrameID( 1336 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_PENDENT][itemType].Price = 999999;
	itemType++; // 18
#endif //__ADVANCEMENT_NEW_UNIQUE_ITEM

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 링 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_RING, 15 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+1
#endif

#if __CONTENTS(__QUEST_RENEWAL)
		+1
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ADVANCEMENT_NEW_UNIQUE_ITEM)
		+1
#endif //__ADVANCEMENT_NEW_UNIQUE_ITEM
		);
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "헴프의 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Hemp\'s Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(637, 651, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(637);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "셀레스타 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Celesta Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(638, 652, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(638);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "세이프가드 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Safeguard Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(639, 653, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(639);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "위스퍼 오브 엘프 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Whisper of Elf Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(640, 654, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(640);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "엠포스 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Mpos Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(641, 655, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(641);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "테일즈 오브 샤인 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Tails of Shine Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(687, 701, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(687);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "스파이더 아이즈 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Spider Eyes Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(688, 702, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(688);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "솔리터리 스타 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Solitary Star Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(689, 703, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(689);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "메크쟌의 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Macsan's Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(690, 704, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(690);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "이모르탈러티 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Immortality Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(691, 705, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(691);
	itemType++;

	// 10
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "안달루시아 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Andalusia Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(808, 831, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(808);
	itemType++;
	
	// 11
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "마르둑 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Marduk Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(809, 832, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(809);
	itemType++;
	
	// 12
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "말라카이트 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Malachite Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(810, 833, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(810);
	itemType++;

	// 13
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "사이렌 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Siren Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(1105 , 962 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(1105);
	itemType++;

	// 14
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "헬 가든의 반지";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Ring Of Hellgarden";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "헬 가든의 반지";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(1105 , 962 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(1105);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

	// 15
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "리르 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "MLir Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(809, 832, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(809);
	itemType++;

#endif

#if __CONTENTS(__QUEST_RENEWAL)

	// 16
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "네이쳐스 엠포스 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Nature's Mpos Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(641, 655, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(641);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Price = 4000;
	itemType++;
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "시그니티 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Signity Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(1254, 1297 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(1254);
	itemType++;	// 17

	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "지올로 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Geolo Ring";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID(1105 , 962 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID(1105);
	itemType++;	// 18
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ADVANCEMENT_NEW_UNIQUE_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].HName = "카리사스 영혼의 링";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].EName = "Ring of Carisase Soul";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetFrameID( 1340, 1384 ,0 );	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].SetDropFrameID( 1340 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_RING][itemType].Price = 999999;
	itemType++; // 19
#endif //__ADVANCEMENT_NEW_UNIQUE_ITEM


	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 정령석 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_STONE, 15 
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)
		+3
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2*3
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ONIBLA_ITEM)
		+6
#endif // __ONIBLA_ITEM

		);
		
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 정령석1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(652, 666, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(652);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 정령석2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(653, 667, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(653);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 정령석3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire ElementalStone 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(654, 668, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(654);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 정령석4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire ElementalStone 4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(655, 669, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(655);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 정령석5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire ElementalStone 5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(656, 670, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(656);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 정령석1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(657, 671, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(657);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 정령석2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(658, 672, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(658);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 정령석3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water ElementalStone 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(659, 673, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(659);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 정령석4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water ElementalStone 4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(660, 674, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(660);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 정령석5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water ElementalStone 5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(661, 675, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(661);
	itemType++;

	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 정령석1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(647, 661, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(647);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 정령석2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(648, 662, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(648);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 정령석3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth ElementalStone 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(649, 663, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(649);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 정령석4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth ElementalStone 4";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(650, 664, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(650);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 정령석5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth ElementalStone 5";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(651, 665, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(651);
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "불의 리르 정령석";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fire Lir ElementalStone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(654, 668, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(654);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "물의 리르 정령석";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Water Lir ElementalStone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(659, 673, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(659);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "대지의 리르 정령석";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Earth Lir ElementalStone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(649, 663, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(649);
	itemType++;

#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "이그니스 스톤1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Ignis ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1252, 1295, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1252);
	itemType++;	// 18

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "이그니스 스톤2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Ignis ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1252, 1295, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1252);
	itemType++;	// 19

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "아쿠아 스톤1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Aqua ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1250, 1293, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1250);
	itemType++;	// 20

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "아쿠아 스톤2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Aqua ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1250, 1293, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1250);
	itemType++;	// 21

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "테라 스톤 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Terra ElementalStone 1";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1248, 1291, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1248);
	itemType++;	// 22

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "테라 스톤 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Terra ElementalStone 2";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1248, 1291, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1248);
	itemType++;	// 23
#endif //__NEW_ADVANCEMENT_ITEM

#if __CONTENTS(__ONIBLA_ITEM)
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "이프리트의 불씨";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Fireseed of Efreet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1355, 1399, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1355);
	itemType++;	// 24

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "엘퀴네스의 물방울";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Waterdrop of Elquines";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1350, 1394, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1350);
	itemType++;	// 25

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "트로웰의 거석";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Megalith of Trowell";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1357, 1401, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1357);
	itemType++;	// 26

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "이그니스 스톤 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Ignis Elemental Stone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1353, 1397, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1353);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].NormalItemGrade = 75;
	itemType++;	// 27

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "아쿠아 스톤 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Aqua Elemental Stone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1349, 1393, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1349);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].NormalItemGrade = 75;
	itemType++;	// 28

	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].HName = "테라 스톤 3";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].EName = "Terra Elemental Stone";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetFrameID(1356, 1400, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].SetDropFrameID(1356);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_STONE][itemType].NormalItemGrade = 75;
	itemType++;	// 29
#endif // __ONIBLA_ITEM

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 리스틀릿 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_WRISTLET, 57
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

		+3
#endif
#if __CONTENTS(__QUEST_RENEWAL)
		+3
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
		+2*3
#endif //__NEW_ADVANCEMENT_ITEM

		);
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "내츄럴 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Natural Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(627, 641, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(627);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "바인 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Vine Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(628, 642, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(628);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라둔 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lardun Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(629, 643, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(629);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "요휀의 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Yohwen\'s Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(630, 644, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(630);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "닉스플로즈 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nixflos Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(631, 645, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(631);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라크리마 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "셈피누스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sempitrnus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(683, 697, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(683);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "먼두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Mundus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "산크투스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sanctus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(685, 699, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(685);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "토리드 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Torrid Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "내츄럴 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Natural Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(627, 641, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(627);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "바인 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Vine Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(628, 642, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(628);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라둔 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lardun Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(629, 643, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(629);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "요휀의 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Yohwen\'s Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(630, 644, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(630);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "닉스플로즈 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nixflos Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(631, 645, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(631);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라크리마 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "셈피누스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sempitrnus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(683, 697, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(683);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "먼두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Mundus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "산크투스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sanctus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(685, 699, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(685);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "토리드 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Torrid Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "내츄럴 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Natural Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(627, 641, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(627);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "바인 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Vine Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(628, 642, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(628);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라둔 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lardun Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(629, 643, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(629);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "요휀의 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Yohwen\'s Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(630, 644, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(630);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "닉스플로즈 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nixflos Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(631, 645, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(631);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "라크리마 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "셈피누스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sempitrnus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(683, 697, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(683);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "먼두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Mundus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "산크투스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Sanctus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(685, 699, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(685);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "토리드 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Torrid Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "담발라 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Damballah Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(805, 828, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(805);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네크베트 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nekhbet Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "담발라 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Damballah Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(805, 828, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(805);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네크베트 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nekhbet Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "담발라 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Damballah Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(805, 828, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(805);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네크베트 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nekhbet Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "코스믹 에그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Cosmic Egg Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(807, 830, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(807);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "코스믹 에그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Cosmic Egg Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(807, 830, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(807);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "코스믹 에그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Cosmic Egg Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(807, 830, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(807);
	itemType++;

	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "불의 팔바티 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Palvati wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(937 , 960 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(937);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "물의 팔바티 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Palvati wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(937 , 960 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(937);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "대지의  팔바티 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Palvati wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(937 , 960 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(937);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네피림 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nepirim wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(961);
	itemType++;
			
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네피림 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nepirim wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(961);
	itemType++;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네피림 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nepirim wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(961);
	itemType++;
	
	// Sjheo  2005.06.02 Add
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "나바두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nebadus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "피그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Fig Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "주리어스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "uraeus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;


	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "나바두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nebadus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "피그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Fig Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "주리어스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "uraeus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "나바두스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nebadus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(684, 698, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(684);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "피그 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Fig Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1107, 700, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1107);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "주리어스 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "uraeus Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	// Sjheo  2005.06.02 End 
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "아르테나 리스틀릿";	//54
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Altena wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "아르테나 리스틀릿";	//55
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Altena wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	itemType++;
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "아르테나 리스틀릿";	//56
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Altena wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	itemType++;

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)


	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "리르 리스틀릿";		//57		불
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lir Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "리르 리스틀릿";		//58		물
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lir Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "리르 리스틀릿";		//59		대지
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Lir Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(806, 829, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(806);
	itemType++;

#endif
	
#if __CONTENTS(__QUEST_RENEWAL)	//아이템 추가		라크리마 리스틀릿	불, 물, 대
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네이쳐스 라크리마 리스틀릿";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nature's Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 25600;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네이쳐스 라크리마 리스틀";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nature's Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 25600;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "네이쳐스 라크리마 리스틀";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Nature's Lacrima Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(682, 696, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(682);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 25600;
	itemType++;
#endif

#if __CONTENTS(__NEW_ADVANCEMENT_ITEM)
	// 불아우
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "사이키델릭 리스틀릿";	//63
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Psychedelic Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1253);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 7000000;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "인드라의 리스틀릿";		//64
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Wristlet Of Indra";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 8000000;
	itemType++;

	// 물아우
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "사이키델릭 리스틀릿";	//65
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Psychedelic Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1253);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 7000000;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "인드라의 리스틀릿";		//66
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Wristlet Of Indra";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 8000000;
	itemType++;

	// 대지아우
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "사이키델릭 리스틀릿";	//67
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Psychedelic Wristlet";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1253);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 7000000;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].HName = "인드라의 리스틀릿";		//68
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].EName = "Wristlet Of Indra";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].SetDropFrameID(1074);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_WRISTLET][itemType].Price	= 8000000;
#endif //__NEW_ADVANCEMENT_ITEM

//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].HName = "아르테나 리스틀릿";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].EName = "Altena wristlet";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][1].Price = 0;
//	
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].HName = "네피림 리스틀릿";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].EName = "Nepirim wristlet";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][2].Price = 0;
//
//		m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].HName = "아르테나 리스틀릿";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].EName = "Altena wristlet";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][3].Price = 0;
//	
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].HName = "네피림 리스틀릿";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].EName = "Nepirim wristlet";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][4].Price = 0;	
//
//
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].HName = "아르테나 리스틀릿";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].EName = "Altena wristlet";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PULSEIRA][5].Price = 0;

	
	
	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 라바 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_LARVA, 5 );
	
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].HName = "그린 라바";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].EName = "Green Larva";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetFrameID(667, 681, 0);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetDropFrameID(667);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].HName = "프레쉬 라바";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].EName = "Fresh Larva";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetFrameID(668, 682, 0);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetDropFrameID(668);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].HName = "애디큣 라바";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].EName = "Adequate Larva";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetFrameID(669, 683, 0);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetDropFrameID(669);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].HName = "앰플 라바";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].EName = "Ample Larva";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetFrameID(670, 684, 0);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetDropFrameID(670);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].HName = "스웰 라바";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].EName = "Swell Larva";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetFrameID(671, 685, 0);
	m_pTypeInfo[ITEM_CLASS_LARVA][itemType].SetDropFrameID(671);
	itemType++;

	
	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 
	// 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_PUPA, 8);
	
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "그린 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Green Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(672, 686, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(672);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "프레쉬 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Fresh Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(673, 687, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(673);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "애디큣 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Adequate Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(674, 688, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(674);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "앰플 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Ample Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(675, 689, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(675);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "스웰 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Swell Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(676, 690, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(676);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "벌지 푸파";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Bulge Pupa";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(1049, 1083, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(1049);
	itemType++;

	
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "녹색 사탕";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Green Candy";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_PUPA);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID(884, 907, 0);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID(884);
	itemType++;


	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].HName = "가멸찬 송편";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].EName = "Full Rice Cake";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Description = "한가위 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_ITEM_MOVE_POTION );
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetFrameID( 1010, 1044, 0 );//( 378, 392, 0 );	
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetDropFrameID( 1010 );//( 378 );
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_PUPA][itemType].Price	= 1;
	itemType++;

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 메이 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_COMPOS_MEI, 6 );
	
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "그린 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Green Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(677, 691, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(677);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "프레쉬 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Fresh Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(678, 692, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(678);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "애디큣 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Adequate Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(678, 692, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(678);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "앰플 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Ample Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(679, 693, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(679);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "스웰 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Swell Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(679, 693, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(679);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].HName = "벌지 메이";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].EName = "Bulge Mei";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetSoundID( SOUND_ITEM_MOVE_POTION, SOUND_ITEM_MOVE_POTION, SOUNDID_NULL, SOUND_OUSTERS_MEI);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetFrameID(1050, 1084, 0);
	m_pTypeInfo[ITEM_CLASS_COMPOS_MEI][itemType].SetDropFrameID(1050);
	itemType++;

	itemType = 0;
	// ----------------------------------------------------------------------
	// 아우스터즈 젬 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_OUSTERS_SUMMON_ITEM, 14 );
	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "실프 서몬 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Sylph Summon Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(680, 694, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(680);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "실라페 서몬 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Sylaphe Summon Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(680, 694, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(680);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "실라이론 서몬 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Sylairon Summon Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(680, 694, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(680);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "그린 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Green Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(784, 807, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(784);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "오렌지 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Orange Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(785, 808, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(785);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "레드 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Red Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(786, 809, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(786);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "옐로우 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Yellow Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(787, 810, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(787);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "화이트 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "White Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(788, 811, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(788);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "브라운 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Brown Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(789, 812, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(789);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "라일락 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Lilac Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(790, 813, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(790);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "블랙 서몬 임프 젬";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Black Summon Imp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(791, 814, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(791);
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "레드 서몬 위습잼";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Red Summon Wisp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "위습을 소환 하여 이동할 수 있습니다.(승직 전용)";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(1112, 1140, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(1112);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Price = 3000000;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].ItemCanAdvance = NONADVANCE_CANNOT_USE_ITEM;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "옐로우 서몬 위습잼";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Yellow Summon Wisp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "위습을 소환 하여 이동할 수 있습니다.(승직 전용)";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(1124, 1152, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(1124);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Price = 3000000;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].ItemCanAdvance = NONADVANCE_CANNOT_USE_ITEM;
	itemType++;

	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].HName = "에머럴드 서몬 위습잼";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].EName = "Emerald Summon Wisp Gem";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Description = "위습을 소환 하여 이동할 수 있습니다.(승직 전용)";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetFrameID(1114, 1142, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].SetDropFrameID(1114);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].Price = 3000000;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_SUMMON_ITEM][itemType].ItemCanAdvance = NONADVANCE_CANNOT_USE_ITEM;
	itemType++;

	InitItem3();
}