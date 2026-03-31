
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
void
ITEMCLASS_TABLE::InitItem3(){
	int itemType = 0;
	
	// ----------------------------------------------------------------------
	// 아우스터즈 젬 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_EFFECT_ITEM, 41
//20080305 프리미엄 카드가 추가 되기 전까지는 차지 아이템을 4로 사용한다. 
#if __CONTENTS(__2008_FIRST_CHARGE_ITEM)
		+3
#endif //__2008_FIRST_CHARGE_ITEM
#if __CONTENTS(__PREMIUM_CARD_C)
		+1
#endif //__PREMIUM_CARD_C
#if __CONTENTS(__080327_ORDINIS_VAPOR)
		+2
#endif //__080327_ORDINIS_VAPOR

#if __CONTENTS(__2008_JUNE_EVENT_EX_STONE)
		+1
#endif //__2008_JUNE_EVENT_EX_STONE

//#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
		+6
//#endif //__JAPAN_REVERSE_DEVELOP

#if __CONTENTS(__EXTREME_FORCE_SCROLL)
		+1
#endif //__EXTREME_FORCE_SCROLL

#if __CONTENTS(__PREMIUM_CARD_D)
		+1
#endif //__PREMIUM_CARD_D
#if __CONTENTS(__PREMIUM_CARD_ADAY)
		+3
#endif //__PREMIUM_CARD_D

#if __CONTENTS(__IMI_SENDGLASS)
		+6
#endif //__IMI_SENDGLASS

#if __CONTENTS(__MASTER_EFFECTS)
		+9
#endif //__MASTER_EFFECTS

#if __CONTENTS(__IMI_NEW_ENCHANT_ITEM)
		+3
#endif //__IMI_NEW_ENCHANT_ITEM

#if __CONTENTS(__TREBLE_PET_SANDGLASS)
		+2
#endif //__TREBLE_PET_SANDGLASS
#if __CONTENTS(__NONE_ADVANCEMENT_SANDGLASS)
		+3
#endif //__NONE_ADVANCEMENT_SANDGLASS
#if __CONTENTS(__20091028_ADD_ITEM)
		+4
#endif //__20091028_ADD_ITEM
		);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].HName = "확성기 1";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].EName = "Megaphone 1";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].Description = "오른쪽 버튼 클릭으로 사용하실 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].SetFrameID(710, 724, 0);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][0].SetDropFrameID(710);
	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].HName = "확성기 2";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].EName = "Megaphone 2";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].Description = "오른쪽 버튼 클릭으로 사용하실 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].SetFrameID(710, 724, 0);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][1].SetDropFrameID(710);
	 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].HName = "확성기 3";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].EName = "Megaphone 3"; 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].Description = "오른쪽 버튼 클릭으로 사용하실 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].SetFrameID(710, 724, 0);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][2].SetDropFrameID(710);

	// 2004, 5, 18 sobeit add start
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].HName = "번역기";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].EName = "Translator"; 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].Description = "오른쪽 버튼 클릭으로 사용하실 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].SetFrameID( 579, 593, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].SetDropFrameID( 579 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][3].Price = 1;
	// 2004, 5, 18 sobeit add end

	// 2005, 1, 11 sobeit add start - 경험치 보너스 모래시계
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].HName = "하급 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].EName = "L-grade Hourglass"; 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].Description = "경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].SetFrameID( 972, 1006, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].SetDropFrameID( 972 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][4].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].HName = "중급 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].EName = "M-grade Hourglass"; 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].Description = "경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].SetFrameID( 971, 1005, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].SetDropFrameID( 971 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][5].Price = 1;
	

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].HName = "상급 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].EName = "S-grade Hourglass"; 
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].Description = "경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_C4, SOUND_ITEM_MOVE_C4, SOUNDID_NULL, SOUND_ITEM_USE_C4);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].SetFrameID( 970, 1004, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].SetDropFrameID( 970 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][6].Price = 1;
	// 2004, 5, 18 sobeit add end

	// 2005.05.12 sjheon  4월 신규 마켓 아이템  add
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].HName = "베히모스 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].EName = "Behemoth Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].Description = 
#if __CONTENTS(__DESIGNED_JAPAN)
		"회피율+30 , 지속시간 12분";
#else
		"회피율+30 , 지속시간 30분";
#endif

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].SetFrameID( 991, 1025, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].SetDropFrameID( 991 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][7].SetGrid( 1, 1 );	


	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].HName = "세이프 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].EName = "Safe Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].Description =
#if __CONTENTS(__DESIGNED_JAPAN)
		"방어율+30 , 지속시간 12분";
#else
		"방어율+30 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].SetFrameID( 992, 1026, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].SetDropFrameID( 992 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][8].SetGrid( 1, 1 );	

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].HName = "카넬리언 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].EName = "Carnelian Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].Description =
#if __CONTENTS(__DESIGNED_JAPAN)
		"모든저항 +9 , 지속시간 12분";
#else
		"모든저항 +9 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].SetFrameID( 994, 1028, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].SetDropFrameID( 994 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][9].SetGrid( 1, 1 );	
	// 2005.05.12 sjheon  4월 신규 마켓 아이템 add
	
	// 2006.2.7 nanomech 일본 상용화 마켓 아이템 start
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].HName = "하급 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].EName = "Small Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][10].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].HName = "중급 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].EName = "Medium Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].SetDropFrameID( 1014 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][11].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].HName = "상급 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].EName = "Large Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].SetDropFrameID( 1015 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][12].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].HName = "하급 행운의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].EName = "Small Sandglass of Lucky";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].Description = "일정 시간 동안 아이템 루팅율을  2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].SetFrameID( 1019, 1053, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].SetDropFrameID( 1019 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][13].SetGrid( 1, 2 );

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].HName = "중급 행운의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].EName = "Medium Sandglass of Lucky";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].Description = "일정 시간 동안 아이템 루팅율을  2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].SetFrameID( 1020, 1054, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].SetDropFrameID( 1020 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][14].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].HName = "상급 행운의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].EName = "Large Sandglass of Lucky";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].Description = "일정 시간 동안 아이템 루팅율을  2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].SetFrameID( 1021, 1055, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].SetDropFrameID( 1021 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][15].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].HName = "하급 상인의 증표";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].EName = "Small Seal of Merchant";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].Description = "일정 시간 동안 개인상점의 모든 제한을 해제해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].SetFrameID( 1018, 1052, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].SetDropFrameID( 1018 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][16].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].HName = "중급 상인의 증표";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].EName = "Medium Seal of Merchant";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].Description = "일정 시간 동안 개인상점의 모든 제한을 해제해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].SetFrameID( 1018, 1052, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].SetDropFrameID( 1018 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][17].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].HName = "상급 상인의 증표";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].EName = "Large Seal of Merchant";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].Description = "일정 시간 동안 개인상점의 모든 제한을 해제해주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].SetFrameID( 1018, 1052, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].SetDropFrameID( 1018 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][18].Price = 200000;
	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].HName = "분노의 기원";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].EName = "Origin of Fury";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].Description = "일정 기간 동안 강화 폭주 스킬을 사용할 수 있다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].SetFrameID( 1017, 1051, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].SetDropFrameID( 1017 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][19].Price = 200000;
	// 2006.2.7 nanomech 일본 상용화 마켓 아이템 end
	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].HName = "광폭의 향";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].EName = "Furious Incense";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].Description = "데미지+3";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].SetFrameID( 1024, 1058, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].SetDropFrameID( 1024 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][20].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].HName = "강력의 향";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].EName = "Strengthen Incense";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].Description = "체력+20, 모든 능력치+3";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].SetFrameID( 1022, 1056, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].SetDropFrameID( 1022 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][21].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].HName = "활성의 향";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].EName = "Hyperactive Incense";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].Description = "아이템에 의한 체력/ 마나/ 영력 회복속도 30%상승";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].SetFrameID( 1029, 1063, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].SetDropFrameID( 1029 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][22].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].HName = "철벽의 향";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].EName = "Impregnable Incense";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].Description = "물리/ 마법에 의한 피해 20%감소";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].SetFrameID( 1028, 1062, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].SetDropFrameID( 1028 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][23].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;
	
	// 2006.04.22 chyaya  신규 마켓 아이템  add
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].HName = "그라이펠 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].EName = "Greyfell Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].Description =
#if __CONTENTS(__DESIGNED_JAPAN)
		"STR +9 , 지속시간 12분";
#else
		"STR +15 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].SetFrameID( 1031, 1065, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].SetDropFrameID( 1031 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][24].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].HName = "소비우스 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].EName = "Sovius Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].Description =
#if __CONTENTS(__DESIGNED_JAPAN)
		"DEX +9 , 지속시간 12분";
#else
		"DEX +15 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].SetFrameID( 1032, 1066, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].SetDropFrameID( 1032 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][25].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].HName = "미르 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].EName = "Mir Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].Description =
#if __CONTENTS(__DESIGNED_JAPAN)
		"INT +9 , 지속시간 12분";
#else
		"INT +15 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].SetFrameID( 1033, 1067, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].SetDropFrameID( 1033 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][26].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].HName = "의문의 물약";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].EName = "Mystery Potion";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].Description = "마우스 오른쪽 클릭으로 사용";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].SetFrameID( 1109, 1137, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].SetDropFrameID( 1109 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][27].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].HName = "하급 경험의 모래시계 A";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].EName = "Small Sandglass of EXP A";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].SetFrameID( 1120, 1149, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].SetDropFrameID( 1120 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][28].Price = 300;
	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].HName = "중급 경험의 모래시계 A";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].EName = "Medium Sandglass of EXP A";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].SetFrameID( 1121, 1150, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].SetDropFrameID( 1121 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][29].Price = 600;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].HName = "상급 경험의 모래시계 A";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].EName = "Large Sandglass of EXP A";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].SetFrameID( 1122, 1148, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].SetDropFrameID( 1122 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][30].Price = 1000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].HName = "장미";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].EName = "Rose";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].Description = "장미의 축복 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].SetFrameID( 1132, 1159, 0 );//1132 드롭이지미 없음
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].SetDropFrameID( 1132 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][31].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_TRADE | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;


	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].HName = "오딘 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].EName = "Odin Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].Description = 
#if __CONTENTS(__DESIGNED_JAPAN)
		"마법데미지 10%감소 , 지속시간 12분";
#else
		"마법데미지 10%감소 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].SetFrameID( 1156, 1183, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].SetDropFrameID( 1156 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][32].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].HName = "티투오스 포스 스크롤";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].EName = "Tituos Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].Description = 
#if __CONTENTS(__DESIGNED_JAPAN)
		"물리데미지 10%감소 , 지속시간 12분";
#else
		"물리데미지 10%감소 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].SetFrameID( 1157, 1184, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].SetDropFrameID( 1157 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][33].Price = 500000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].HName = "알심 송편";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].EName = "Rice Cake of Strength";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].Description = "한가위 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].SetFrameID( 1085,1119, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].SetDropFrameID( 1085 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][34].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].HName = "날렵한 송편";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].EName = "Rice Cake of Agility";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].Description = "한가위 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].SetSoundID(SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].SetFrameID( 901, 924, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].SetDropFrameID( 901 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].SetGrid( 1, 1 );	
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][35].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].HName = "알음알이 송편";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].EName = "Rice Cake of Knowledge";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].Description = "한가위 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].SetSoundID(SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].SetFrameID( 1007, 1041, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].SetDropFrameID( 1007 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][36].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].HName = "옹골진 송편";								  
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].EName = "Rice Cake of Acceleration";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].Description = "한가위 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].SetSoundID(SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].SetFrameID( 1008, 1042, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].SetDropFrameID( 1008 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][37].Price = 1;

 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].HName = "펫 경험의 모래시계";								  
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].EName = "Sandglass of Pet EXP";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].Description = "사용 시간 동안 캐릭터가 소환하는 모든 펫의 경험치를 2배로 적용시켜준다";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].SetSoundID( SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_MOVE_BOTTLE, SOUND_ITEM_USE_MPOTION);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].SetFrameID( 1168, 1195, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].SetDropFrameID( 1168 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].SetGrid(1, 2);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][38].Price = 1;


	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].HName = "프리미엄 카드 B"; 
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].EName = "Premium Card B";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].Description = "프리미엄 시간을 30일 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][39].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].HName = "프리미엄 카드 A";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].EName = "Premium Card A";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].Description = "프리미엄 시간을 24시간 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][40].Price = 1;
#if __CONTENTS(__PREMIUM_CARD_C)
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].HName = "프리미엄 카드 C";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].EName = "Premium Card C";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].Description = "프리미엄 시간을 100일 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][41].Price = 1;
#endif //__PREMIUM_CARD_C
	itemType = 42;
#if __CONTENTS(__2008_FIRST_CHARGE_ITEM)
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "에나 문 클락";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ena Moon clock";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "81레벨 이상 120 레벨 이하 캐릭터가 사용 가능합니다";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1202, 1243, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1202 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(2, 2);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "테세라 문 클락";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Tessera Moon clock";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "81레벨 이상 120 레벨 이하 캐릭터가 사용 가능합니다";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1203, 1244, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1203 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(2, 2);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "에프타 문 클락";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Epta Moon clock";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "81레벨 이상 120 레벨 이하 캐릭터가 사용 가능합니다";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1204, 1245, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1204 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(2, 2);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__2008_FIRST_CHARGE_ITEM

#if __CONTENTS(__080327_ORDINIS_VAPOR)
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "오디니스 바이퍼 레드";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ordinis Vapor Red";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "계급 경험치 보너스 아이템";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1206, 1247, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1206 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(2, 2);
//	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Race = 7;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "오디니스 바이퍼 블루";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ordinis Vapor Blue";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "계급 경험치 보너스 아이템";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1207, 1248, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1207 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(2, 2);
//	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Race = 7;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__080327_ORDINIS_VAPOR

#if __CONTENTS(__2008_JUNE_EVENT_EX_STONE)
	// itemType = 47
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "경험의 돌";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Experience Stone";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "1시간동안 획득 경험치 2배상승 (이벤트 아이템)";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1218, 1261, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1218 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Race = 7;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__2008_JUNE_EVENT_EX_STONE

	// 전제
	// 1. "ITEM_CLASS_EFFECT_ITEM"클래스로 새로운 아이템 "프리미엄 카드 D"가 추가됨. (공백으로 비어 있던 "프리미엄 카드 C"도 100일짜리로 부활)
	// 2. 본섭에도 일본아이템(아래의 아이템 6종)이 추가 됨. (DB에 들어있기때문에 맞추기 위한것)
	// 3. 일본아이템의 타입번호는 변경되지 않으며, 본섭에 그대로 적용될 예정임
	// 
	// 문제점
	// 1. "익스트림 포스 스크롤"의 인덱스 번호와 일본아이템의 "하급 영혼이 깃든 경험의 모래시계"의 인덱스 번호가 동일함
	// 
	// 해결방안
	// 1. 아이템번호를 수정하는작업이 번거로우므로, 일본아이템 이후의 인덱스에 "프리미엄 카드 D"를 추가
	// 2. 차후에 "익스트림 포스 스크롤"의 인덱스를  맨 끝으로 보낼 예정 (이를 위해서 미리 "익스트림 포스 스크롤"가 인덱스 하나를 더 잡고있다.)

//#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
	//일본용 계정 종속 경험치 두배 아이템// itemType = 48
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "하급 영혼이 깃든 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Small soul Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "중급 영혼이 깃든 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Medium soul Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1014 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "상급 영혼이 깃든 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Large soul Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1015 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 51

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "하급 프리미엄 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Small Premium Sandglass";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "중급 프리미엄 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Medium Premium Sandglass";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1014 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "상급 프리미엄 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Large Premium Sandglass";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "일정 시간 동안 경험치 획득율을 2배 상승시켜주는 아이템이다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1015 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

//#endif //__JAPAN_REVERSE_DEVELOP

#if __CONTENTS(__EXTREME_FORCE_SCROLL)
	// itemType = 54
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "익스트림 포스 스크롤";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Extreme Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = 
#if __CONTENTS(__DESIGNED_JAPAN)
		"모든 능력치 +8 , 지속시간 12분";
#else
		"모든 능력치 +8 , 지속시간 30분";
#endif
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1300, 1344, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].SetDropFrameID( 1300 );
#endif //__EXTREME_FORCE_SCROLL

#if __CONTENTS(__PREMIUM_CARD_D)
	// itemType = 55
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "프리미엄 카드 D"; 
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Premium Card D";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "프리미엄 시간을 200일 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__PREMIUM_CARD_D
#if __CONTENTS(__PREMIUM_CARD_ADAY)
	// itemType = 56
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "프리미엄 카드 A-3"; 
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Premium Card A-3";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "프리미엄 시간을 3일 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].ItemMoveControl = ITEMMOVE_PICKUP_ONCE;
	// itemType = 57
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "프리미엄 카드 A-7"; 
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Premium Card A-7";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "프리미엄 시간을 7일 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].ItemMoveControl = ITEMMOVE_PICKUP_ONCE;
	// itemType = 58
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "프리미엄 카드 A-15"; 
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Premium Card A-15";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "프리미엄 시간을 15 얻습니다.";
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUND_XMAS_STAR, SOUND_XMAS_STAR, SOUNDID_NULL, SOUND_XMAS_STAR);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Price = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].ItemMoveControl = ITEMMOVE_PICKUP_ONCE;
#endif //__PREMIUM_CARD_ADAY

#if __CONTENTS(__IMI_SENDGLASS)
	// itemType = 59
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "레비스 하급 경험의 모래시계" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Small Sandglass of Experience Levis";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 60
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "레비스 중급 경험의 모래시계" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Medium Sandglass of Experience Levis";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 61
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "레비스 상급 경험의 모래시계" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Large Sandglass of Experience Levis";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 62
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "메디 하급 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Small Sandglass of Experience Medi";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 63
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "메디 중급 경험의 모래시계";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Medium Sandglass of Experience Medi";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

	// itemType = 64
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "메디 상급 경험의 모래시계" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Large Sandglass of Experience Medi";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "100레벨 이하만 사용 가능 한 경험치 보너스 아이템";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 2 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 200000;

#endif //__IMI_SENDGLASS

#if __CONTENTS(__MASTER_EFFECTS)

	//--------------------------슬레이어-------------------------------------
	// itemType = 65
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "천사의 날개짓 데카펜타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Angel's Flutter Decapenta";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "15일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1380, 1424, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1380 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 66
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "천사의 날개짓 옥타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Angel's Flutter Octa";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "7일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1381, 1425, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1381 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 67
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "천사의 날개짓 테트라" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Angel's Flutter Tetra";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "3일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1382, 1426, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1382 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	//-------------------------뱀파이어--------------------------------------
	// itemType = 68
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "핏빛 어둠의 그림자 데카펜타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Shadow of Bloody Darkness Decapenta";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "15일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1374, 1418, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1374 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 69
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "핏빛 어둠의 그림자 옥타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Shadow of Bloody Darkness Octa";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "7일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1375, 1419, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1375 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 70
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "핏빛 어둠의 그림자 테트라" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Shadow of Bloody Darkness Tetra";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "3일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1376, 1420, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1376 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	//--------------------------아우스터즈-----------------------------------
	// itemType = 71
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "아리엘의 숨결 데카펜타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ariel`s Breathing Decapenta";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "15일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1377, 1421, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1377 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 72
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "아리엘의 숨결 옥타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ariel`s Breathing Octa";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "7일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1378, 1422, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1378 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 73
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "아리엘의 숨결 테트라" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Ariel`s Breathing Tetra";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "3일 동안 특별한 마스터 이펙트가 부여되는 1회용 효과 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1379, 1423, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1379 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

#endif	//__MASTER_EFFECTS

#if __CONTENTS(__IMI_NEW_ENCHANT_ITEM)
	// itemType = 74
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "다크 패키지 A" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Dark Package A";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "1일동안 프리미엄 혜택을 누릴 수 있는 카드입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 75
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "다크 패키지 B" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Dark Package B";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "7일동안 프리미엄 혜택을 누릴 수 있는 카드입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 76
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "다크 패키지 C" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Dark Package C";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "30일동안 프리미엄 혜택을 누릴 수 있는 카드입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1200, 1241, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1200 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__IMI_NEW_ENCHANT_ITEM

#if __CONTENTS(__TREBLE_PET_SANDGLASS)
	// itemType = 77
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "펫 경험의 모래시계 트레블-7" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Sandglass of Pet EXP Treble-7";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "소환된 펫의 경험치를 7일간 3배로 적용시켜주는 소모성 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1394, 1438, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1394 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 78
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "펫 경험의 모래시계 트레블-15" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Sandglass of Pet EXP Treble-15";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "소환된 펫의 경험치를 15일간 3배로 적용시켜주는 소모성 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1393, 1437, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1393 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__TREBLE_PET_SANDGLASS
#if __CONTENTS(__NONE_ADVANCEMENT_SANDGLASS)
	// itemType = 79
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "경험의 모래시계 모노" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Experience Sand Clock Mono";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "캐릭터의 경험치를 1일간 2배로 적용시켜주는 소모성 아이템입니다.1레벨부터 149레벨까지 사용이 가능하며, 150레벨이 되는 순간 효과가 사라집니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1013, 1047, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1013 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 80
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "경험의 모래시계 테트라" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Experience Sand Clock Tetra";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "캐릭터의 경험치를 4일간 2배로 적용시켜주는 소모성 아이템입니다.1레벨부터 149레벨까지 사용이 가능하며, 150레벨이 되는 순간 효과가 사라집니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1014, 1048, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1014 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
	
	// itemType = 81
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "경험의 모래시계 옥타" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Experience Sand Clock Octa";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "캐릭터의 경험치를 7일간 2배로 적용시켜주는 소모성 아이템입니다.1레벨부터 149레벨까지 사용이 가능하며, 150레벨이 되는 순간 효과가 사라집니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1015, 1049, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1015 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__NONE_ADVANCEMENT_SANDGLASS
#if __CONTENTS(__20091028_ADD_ITEM)
	// itemType = 82
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "경험의 모래시계 어드밴스" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Advanced Sandglass of Experience";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "30일간 경험치 50% 추가 보너스를 받을 수 있는 소모성 아이템입니다. 레벨 150이상 사용 가능";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1440, 1484, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1440 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 83
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "아큐라 포스 스크롤" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Accura Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "명중률 + 30, 지속시간 30분";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1443, 1487, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1443 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 84
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "라이프 포스 스크롤" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Life Force Scroll";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "HP + 500, 지속시간 30분";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1441, 1485, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1441 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;

	// itemType = 85
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].HName = "혼돈의 경험의 돌" ;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].EName = "Chaotic Experience Stone";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Description = "캐릭터의 경험치를 1시간 동안 13배로 적용시켜주는 소모성 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetSoundID( SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL,SOUNDID_NULL);
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetFrameID( 1444, 1488, 0 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetDropFrameID( 1444 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].SetGrid( 1, 1 );
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_EFFECT_ITEM][itemType++].Price = 1;
#endif //__20091028_ADD_ITEM

	// ----------------------------------------------------------------------
	// 아우스터즈 젬 아이템 클래스
	// ----------------------------------------------------------------------
	InitClass(ITEM_CLASS_CODE_SHEET, 2 );
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].HName = "코드표";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].EName = "Code Sheet";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].Description = "오른쪽 버튼 클릭으로 코드표를 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].SetFrameID( 491, 505, 0 );	
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].SetDropFrameID( 491 );
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][0].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE;

	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].HName = "코드표";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].EName = "Code Sheet";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].Description = "오른쪽 버튼 클릭으로 코드표를 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].SetFrameID( 491, 505, 0 );	
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].SetDropFrameID( 491 );
	m_pTypeInfo[ITEM_CLASS_CODE_SHEET][1].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE;

	//----------------------------------------------------------------------
	// 달카드 
	//----------------------------------------------------------------------
	InitClass(ITEM_CLASS_MOON_CARD, 16 
#if __CONTENTS(__CLOVER_EVENT)
		+1
#endif //__CLOVER_EVENT
		);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].HName = "반달 카드";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].EName = "The Half Moon Card";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].Description = "많이 많이 모아 보아요";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].SetFrameID( 770, 784, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][0].SetDropFrameID( 770 );

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].HName = "초승달 카드";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].EName = "The New Moon Card";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].SetFrameID( 769, 783, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][1].SetDropFrameID( 769 );

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].HName = "넷마블 카드";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].EName = "The Netmarble Card";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].Description = "많이 많이 모아 보아요";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].SetFrameID( 838, 861, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][2].SetDropFrameID( 838 );

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].HName = "네잎 클로버";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].EName = "a four-leaf clover";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].Description = "행운 이벤트용 아이템. 등수대로 상품을 드려요.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].SetFrameID( 858, 881, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][3].SetDropFrameID( 858 );
	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].HName = "손의 월계관";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].EName = "Son's Laurel Crown";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].SetFrameID( 882, 905, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][4].SetDropFrameID( 882 );

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].HName = "장미 꽃잎";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].EName = "Rose petal";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].Description = "장미의 축복 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].SetFrameID( 1131, 1158, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].SetDropFrameID( 1131 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][5].ItemMoveControl = ITEMMOVE_CANNOT_DROP;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].HName = "헬 가든의 씨앗";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].EName = "Seed Of Hellgarden";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].Description = "헬 가든의 씨앗은 감시의 수정구를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].SetFrameID( 1139, 1166, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].SetDropFrameID( 1139 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][6].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].HName = "예지의 씨앗";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].EName = "Seed Of Foresight";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].Description = "헬 가든의 씨앗은 예지의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].SetFrameID( 1140, 1167, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].SetDropFrameID( 1140 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][7].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].HName = "심안의 씨앗";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].EName = "Seed Of Min`s eye";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].Description = "헬 가든의 씨앗은 심안의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].SetFrameID( 1141, 1168, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].SetDropFrameID( 1141 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][8].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].HName = "결계의 씨앗";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].EName = "Seed Of Guard";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].Description = "헬 가든의 씨앗은 결계의 수정구를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].SetFrameID( 1142, 1169, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].SetDropFrameID( 1142 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][9].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].HName = "침묵의 씨앗";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].EName = "Seed Of Silence";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].Description = "헬 가든의 씨앗은 침묵의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].SetFrameID( 1143, 1170, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].SetDropFrameID( 1143 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][10].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].HName = "반역의 십자가";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].EName = "Cross of defiance";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].Description = "반역의 십자가는 감시의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].SetFrameID( 36, 1171, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].SetDropFrameID( 36 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][11].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].HName = "예지의 십자가";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].EName = "Cross of Foresight";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].Description = "반역의 십자가는 예지의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].SetFrameID( 36, 1172, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].SetDropFrameID( 36 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][12].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].HName = "심안의 십자가";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].EName = "Cross of Mind's Eye";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].Description = "반역의 십자가는 심안의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].SetFrameID( 36, 1173, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].SetDropFrameID( 36 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][13].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].HName = "결계의 십자가";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].EName = "Cross of Guard";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].Description = "반역의 십자가는 결계의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].SetFrameID( 36, 1174, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].SetDropFrameID( 36 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][14].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].HName = "침묵의 십자가";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].EName = "Cross of Silence";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].Description = "반역의 십자가는 침묵의 수정구를 통해 보상교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].SetFrameID( 36, 1175, 0 );	
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].SetDropFrameID( 36 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][15].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	itemType	= 16;
#if __CONTENTS(__CLOVER_EVENT)
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].HName = "황금 클로버";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].EName = "Gold clover";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].Description = "이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].SetFrameID( 1213, 1254, 0 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].SetDropFrameID( 1213 );
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType].Price = 4000000;
	m_pTypeInfo[ITEM_CLASS_MOON_CARD][itemType++].ItemMoveControl = ITEMMOVE_CANNOT_DROP;
#endif //__CLOVER_EVENT

	//--------------------------------------------------------------------------
	// 스위퍼
	//--------------------------------------------------------------------------
	InitClass(ITEM_CLASS_SWEEPER, 12 );
	
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].HName = "M-03-01";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].EName = "M-03-01";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].SetFrameID( 772,786,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][0].SetDropFrameID( 772 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].HName = "M-03-02";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].EName = "M-03-02";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].SetFrameID( 773,787,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][1].SetDropFrameID( 773 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].HName = "M-03-03";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].EName = "M-03-03";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].SetFrameID( 774,788,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][2].SetDropFrameID( 774 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].HName = "M-03-04";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].EName = "M-03-04";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].SetFrameID( 772,789,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][3].SetDropFrameID( 772 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].HName = "M-03-05";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].EName = "M-03-05";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].SetFrameID( 773,790,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][4].SetDropFrameID( 773 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].HName = "M-03-06";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].EName = "M-03-06";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].SetFrameID( 774,791,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][5].SetDropFrameID( 774 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].HName = "M-03-07";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].EName = "M-03-07";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].SetFrameID( 772,792, 0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][6].SetDropFrameID( 772 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].HName = "M-03-08";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].EName = "M-03-08";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].SetFrameID( 773,793,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][7].SetDropFrameID( 773 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].HName = "M-03-09";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].EName = "M-03-09";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].SetFrameID( 774,794,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][8].SetDropFrameID( 774 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].HName = "M-03-10";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].EName = "M-03-10";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].SetFrameID( 772,795,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][9].SetDropFrameID( 772 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].HName = "M-03-11";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].EName = "M-03-11";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].SetFrameID( 773,796,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][10].SetDropFrameID( 773 );

	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].HName = "M-03-12";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].EName = "M-03-12";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].Description = "";
	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].SetSoundID( SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].SetFrameID( 774,797,0);
	m_pTypeInfo[ITEM_CLASS_SWEEPER][11].SetDropFrameID( 774 );
	
	//----------------------------------------------------------------------
	// 펫아이템
	//----------------------------------------------------------------------
	InitClass(ITEM_CLASS_PET_ITEM, 9
#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
		+1
#endif //__NEW_PET_FIRE_ELEMENTAL
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
		+1
#endif //__2008_OCTOBER_MAKETITEM
#if __CONTENTS(__NEW_PET_INCUBUS)
		+1
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MASHIMARO)
		+1
#endif //__PET_MASHIMARO
#if __CONTENTS(__PET_CATS)
		+3
#endif //__PET_CATS
#if __CONTENTS(__PET_CATS_UPGRADED)
		+12
#endif //__PET_CATS_UPGRADED
#if __CONTENTS(__UPGRADE_MONSTER_PET)
		+13
#endif //__UPGRADE_MONSTER_PET
		+48	//add by kim
		);

	itemType = 0;

	// 0
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "가짜 배지";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Gara Bezz";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "배쯔는 물러가라~! 물러가라~!";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 797, 820, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 797 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 1
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "울프독 목줄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Wolfdog Leash";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "울프독을 소환할 때 쓰이는 개목걸이 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 797, 820, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 797 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 2
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "울버린 목줄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Wolverine Leash";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "울버린을 소환할 때 쓰이는 개목걸이 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 803, 826, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 803 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 3
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "무선 조종기";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Radio Controller";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "센타우로를 소환할 때 쓰이는 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 839, 862, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 839 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 4
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "박쥐 가죽 가방";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Stirge Bag";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "스티지를 소환할 때 쓰이는 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 840, 863, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 840 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 5
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "소환의 돌";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Summon Pixie";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "픽시를 소환할 때 쓰이는 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 845, 868, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 845 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 6
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "괴도루펭 알";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Lupeng The Phantorn Thief Egg";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "괴도루펭을 소환할 때 쓰이는 알 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1152, 1179, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1152 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 7
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "밀리터리 박스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Military box";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "밀리터리 베어를 소환할 때 사용되는 상자 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1178, 1207, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1178 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 8
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "가고일 족쇄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Gargoyle fetters";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "가고일을 소환할 때 사용되는 족쇄입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1177, 1206, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1177 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
	itemType++;	// 9
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "파이어 엘레멘탈의 낙인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Fire Elemental brand";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "파이어 엘레멘탈을 소환할 때 쓰이는 낙인입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1262, 1305, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1262 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
#endif //__NEW_PET_FIRE_ELEMENTAL

#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
	itemType++;	// 10
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "서큐버스의 반지";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Succubus ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "서큐버스를 소환 할 때 쓰이는 반지 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1298, 1342, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1298 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
#endif //__2008_OCTOBER_MAKETITEM

#if __CONTENTS(__NEW_PET_INCUBUS)
	itemType++;	// 11
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "몽마의 인장";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Incubus ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "인큐버스를 소환 할 때 쓰이는 반지 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1310, 1354, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1310 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MASHIMARO)
	itemType++;	// 12
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "마시마로";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Mashimaro";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "마시마로를 소환 할 때 쓰이는 반지 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1366, 1410, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1366 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
#endif //__PET_MASHIMARO

#if __CONTENTS(__PET_CATS)
	itemType++;	// 13
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "태비 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Tabby Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "태비 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1367, 1411, 0 );	// (ItemTile.ispk, Item.ispk, 0);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1367 );		// (ItemTile.ispk);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 14
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "웰시 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Wealthy Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "웰시 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1368, 1412, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1368 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;	// 15
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "샤밍 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Siaming Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "샤밍 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1369, 1413, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1369 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;


// 2009.09.21 업그레이드 펫 고양이 
#if __CONTENTS(__PET_CATS_UPGRADED)

	itemType++;	// 16
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 미노타우루스 태비 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Minotaurs Tabby Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 태비 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1412, 1456, 0 );	// (ItemTile.ispk, Item.ispk, 0);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1412 );		// (ItemTile.ispk);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 17
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 프타 태비 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Ptha Tabby Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 태비 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1412, 1456, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1412 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 18
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 로크 웰시 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Roc Wealthy Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 웰시 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1411, 1455, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1411 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 19
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 프타 웰시 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Ptha Wealthy Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 웰시 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1411, 1455, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1411 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 20
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 지니어스 샤밍 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Genius Siaming Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 샤밍 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1410, 1454, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1410 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 21
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "카라 프타 샤밍 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Cara Ptha Siaming Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "카라 샤밍 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1410, 1454, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1410 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 22
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 데스트로이 태비 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Destroy Tabby Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 태비 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1409, 1453, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1409 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 23
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 바루나 태비 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Varuna Tabby Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 태비 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1409, 1453, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1409 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 24
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 네크로맨시 웰시 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Necromancy Wealthy Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 웰시 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1408, 1452, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1408 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 25
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 바루나 웰시 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Varuna Wealthy Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 웰시 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1408, 1452, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1408 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 26
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 드라큘라 샤밍 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Dracula Siaming Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 샤밍 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1407, 1451, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1407 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 27
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "델라 바루나 샤밍 칼라";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Della Varuna Siaming Collar";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "델라 샤밍 캣을 소환 할 때 쓰이는 목줄 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1407, 1451, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1407 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

#endif //__PET_CATS_UPGRADED

#endif //__PET_CATS

#if __CONTENTS(__UPGRADE_MONSTER_PET)
	itemType++;	// 28
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "미노타 인큐버스 네크리스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Minota Incubus Necklace";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "미노타우루스 인큐버스를 소환할 수 있는 인큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1426, 1470, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1426 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 29
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "프타 인큐버스 네크리스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Ptha Incubus Necklace";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "프타 인큐버스를 소환할 수 있는 인큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1427, 1471, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1427 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 30
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "로크 서큐버스 링";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Roc Succubus Ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "로크 서큐버스를 소환할 수 있는 서큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1428, 1472, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1428 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 31
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "프타 서큐버스 링";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Ptha Succubus Ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "프타 서큐버스를 소환할 수 있는 서큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1429, 1473, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1429 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 32
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "지니어스 가고일 족쇄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Genius Gargoyle Fetters";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "지니어스 가고일을 소환할 수 있는 가고일 족쇄입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1430, 1480, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1430 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 33
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "프타 가고일 족쇄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Ptha Gargoyle Fetters";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "프타 가고일을 소환할 수 있는 가고일 족쇄입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1431, 1481, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1431 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 34
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "데스트로 인큐버스 네크리스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Destro Incubus Necklace";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "데스트로이 인큐버스를 소환할 수 있는 인큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1432, 1476, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1432 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 35
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "바루나 인큐버스 네크리스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Varuna Incubus Necklace";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "바루나 인큐버스를 소환할 수 있는 인큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1433, 1477, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1433 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 36
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "네크로 서큐버스 링";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Necro Succubus Ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "네크로맨시 서큐버스를 소환할 수 있는 서큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1434, 1478, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1434 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 37
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "바루나 서큐버스 링";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Varuna Succubus Ring";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "바루나 서큐버스를 소환할 수 있는 서큐버스 링입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1435, 1479, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1435 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 38
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "드라큘라 가고일 족쇄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Dracula Gargoyle Fetters";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "드라큘라 가고일을 소환할 수 있는 가고일 족쇄입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1436, 1474, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1436 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 39
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "바루나 가고일 족쇄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Varuna Gargoyle Fetters";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "바루나 가고일을 소환할 수 있는 가고일 족쇄입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1437, 1475, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1437 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;	// 40
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "미니 울프독 목줄";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Mini Wolfdog Leash";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "울프독을 소환할 때 사용되는 소환체입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1438, 1482, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1438 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
#endif //__UPGRADE_MONSTER_PET

	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "괴도루펭 알";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Lupeng The Phantorn Thief Egg";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "괴도루펭을 소환할 때 쓰이는 알 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1152, 1179, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1152 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "괴도루펭 알";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Lupeng The Phantorn Thief Egg";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "괴도루펭을 소환할 때 쓰이는 알 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1152, 1179, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1152 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "괴도루펭 알";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Lupeng The Phantorn Thief Egg";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "괴도루펭을 소환할 때 쓰이는 알 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1152, 1179, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1152 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "괴도루펭 알";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Lupeng The Phantorn Thief Egg";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "괴도루펭을 소환할 때 쓰이는 알 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1152, 1179, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1152 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "밀리터리 박스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Military box";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "밀리터리 베어를 소환할 때 사용되는 상자 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1178, 1207, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1178 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "밀리터리 박스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Military box";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "밀리터리 베어를 소환할 때 사용되는 상자 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1178, 1207, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1178 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "밀리터리 박스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Military box";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "밀리터리 베어를 소환할 때 사용되는 상자 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1178, 1207, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1178 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "밀리터리 박스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Military box";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "밀리터리 베어를 소환할 때 사용되는 상자 입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1178, 1207, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1178 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "파이어 엘레멘탈의 낙인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Fire Elemental brand";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "파이어 엘레멘탈을 소환할 때 쓰이는 낙인입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1262, 1305, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1262 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "파이어 엘레멘탈의 낙인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Fire Elemental brand";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "파이어 엘레멘탈을 소환할 때 쓰이는 낙인입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1262, 1305, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1262 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "파이어 엘레멘탈의 낙인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Fire Elemental brand";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "파이어 엘레멘탈을 소환할 때 쓰이는 낙인입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1262, 1305, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1262 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "파이어 엘레멘탈의 낙인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Fire Elemental brand";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "파이어 엘레멘탈을 소환할 때 쓰이는 낙인입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1262, 1305, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1262 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;

	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "라듐 네펜데스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Radium Nephentus";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "라듐 네펜데스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Radium Nephentus";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "라듐 네펜데스";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Radium Nephentus";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "토륨 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1538, 1582, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1538 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "토륨 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1538, 1582, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1538 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "토륨 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1538, 1582, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1538 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
// 여기 위까지 58번

	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "악티늄 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1539, 1583, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1539 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "악티늄 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1539, 1583, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1539 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "악티늄 러피언";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1539, 1583, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1539 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "데드바디";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1549, 1593, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1549 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "데드바디";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1549, 1593, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1549 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "데드바디";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1549, 1593, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1549 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "터닝데드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	// 65
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "터닝데드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "터닝데드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "키드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "키드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "키드";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "솔져";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "솔져";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "솔져";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1525, 1569, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1525 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
	// 73
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캡틴";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1551, 1595, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1551 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캡틴";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1551, 1595, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1551 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캡틴";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1551, 1595, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1551 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
		
	itemType++;
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].HName = "캐나인";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].EName = "Torum Ruffian";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetFrameID( 1630, 1674, 0 );	// 임시 그림
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetDropFrameID( 1630 );
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PET_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP;
// 여기까지 88

	//----------------------------------------------------------------------
	// 펫먹이아이템
	//----------------------------------------------------------------------
	InitClass(ITEM_CLASS_PET_FOOD, 18
#if __CONTENTS(__PET_FOOD_ITEM_ADD)
		+2
#endif //__PET_FOOD_ITEM_ADD
#if __CONTENTS(__FUNCTION_PETFOOD)
		+2
#endif //__FUNCTION_PETFOOD
#if __CONTENTS(__FUNCTION_PETFOOD_SMART)
		+2
#endif //__FUNCTION_PETFOOD_SMART
#if __CONTENTS(__20091028_ADD_ITEM)
		+1
#endif //__20091028_ADD_ITEM
		);
	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "작은 고기";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Mini Meat";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "6시간 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 792, 815, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 792 );

	itemType++; // 1
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "가벼운 고기";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Light Meat";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "22시간 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 793, 816, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 793 );

	itemType++; // 2
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "반쪽 고기";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Half Meat";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "36시간 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 794, 817, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 794 );

	itemType++; // 3
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "큰 고기";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Large Meat";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "50시간 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 795, 818, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 795 );

	itemType++; // 4
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "사료 푸대";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Fodder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "7일 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 804, 827, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 804 );

	itemType++; // 5
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "울트라 푸대";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Ultra Fodder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "15일 짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 796, 819, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 796 );

	itemType++; // 6
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "하프 파워팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Half Power Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "22시간 짜리 센타우로용 전지입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 846, 869, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 846 );

	itemType++; // 7
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "라지 파워팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Large Power Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "36시간 짜리 센타우로용 전지입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 847, 870, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 847 );

	itemType++; // 8
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "하프 슈퍼 파워팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Half Super Power Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "50시간 짜리 센타우로용 전지입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 848, 871, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 848 );

	itemType++; // 9
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "라지 슈퍼 파워팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Large Super Power Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "7일 짜리 센타우로용 전지입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 849, 872, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 849 );

	itemType++; // 10
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "블러드 팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Blood Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "22시간 짜리 스티지용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 841, 864, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 841 );

	itemType++; // 11
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "농축 블러드 팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Enriched Blood Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "36시간 짜리 스티지용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 842, 865, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 842 );

	itemType++; // 12
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "고농축 블러드 팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Super Enriched Blood Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "50시간 짜리 스티지용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 843, 866, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 843 );

	itemType++; // 13
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "초고농축 블러드 팩";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Ultra Enriched Blood Pack";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "7일 짜리 스티지용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 844, 867, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 844 );

	itemType++; // 14
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "미니듀";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Mini Dew";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "22시간 짜리 픽시용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 850, 873, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 850 );

	itemType++; // 15
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "라이트듀";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Light Dew";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "36시간 짜리 픽시용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 851, 874, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 851 );

	itemType++; // 16
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "하프듀";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Half Dew";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "50시간 짜리 픽시용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 852, 875, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 852 );

	itemType++; // 17
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "라지듀";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Large Dew";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "7일 짜리 픽시용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 853, 876, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 853 );

#if __CONTENTS(__PET_FOOD_ITEM_ADD)
	itemType++; // 18
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "마이티 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Mighty Fodder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "14일짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 1284, 1327, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 1284 );

	itemType++; // 19
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "맥스 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Max Fodder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "30일짜리 울프독/울버린용 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 1283, 1326, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 1283 );
#endif //__PET_FOOD_ITEM_ADD
#if __CONTENTS(__FUNCTION_PETFOOD)
	itemType++; // 20
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "굿포츈 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Good Fortune Fooder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "굿포츈 푸더를먹은 팻은 9일간 좋은 아이템을 찾아내는 능력이 높아집니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 1324, 1368, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID(1324);

	itemType++; // 21
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "인터프리터 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Interpreter Fooder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "사용시 9일간 타종족간 대화 통역";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 1323, 1367, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID(1323);

#endif //__FUNCTION_PETFOOD
#if __CONTENTS(__FUNCTION_PETFOOD_SMART)

	itemType++; // 22
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "라이트 스마트 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Light Smart Fooder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "24시간 짜리 울프독/울버린 등 종족 공용펫용 기능성 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID( 1335, 1379, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID( 1332);


	itemType++; // 23
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "하프 스마트 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Half Smart Fooder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "72시간 짜리 울프독/울버린 등 종족 공용펫용 기능성 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID(1334, 1378, 0);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID(1331);


#endif //__FUNCTION_PETFOOD_SMART

#if __CONTENTS(__20091028_ADD_ITEM)
	itemType++; // 24
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].HName = "맥스 스마트 푸더";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].EName = "Max Smart Fooder";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].Description = "720시간 짜리 울프독/울버린 등 종족 공용펫용 기능성 먹이입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetFrameID(1442, 1486, 0);
	m_pTypeInfo[ITEM_CLASS_PET_FOOD][itemType].SetDropFrameID(1442);
#endif //__20091028_ADD_ITEM

	//----------------------------------------------------------------------
	// 펫 인첸트
	//----------------------------------------------------------------------
	InitClass(ITEM_CLASS_PET_ENCHANT_ITEM, 33
#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
		+1
#endif //__NEW_PET_FIRE_ELEMENTAL
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
		+1
#endif //__2008_OCTOBER_MAKETITEM
#if __CONTENTS(__NEW_PET_INCUBUS)
		+1
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_VISION_AMPLE)
		+1
#endif //__PET_VISION_AMPLE
#if __CONTENTS(__PET_MASHIMARO)
		+1
#endif //__PET_MASHIMARO
#if __CONTENTS(__PET_CATS)
		+3
#endif //__PET_CATS
#if __CONTENTS(__PET_CATS_UPGRADED)
		+12
#endif //__PET_CATS_UPGRADED
#if __CONTENTS(__UPGRADE_MONSTER_PET)
		+13
#endif //__UPGRADE_MONSTER_PET
		+48	//by kim
		);

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].HName = "레드 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].EName = "Red Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].SetFrameID( 798, 821, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][0].SetDropFrameID( 798 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].HName = "힘 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].EName = "STR Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][1].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].HName = "민첩성 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].EName = "DEX Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][2].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].HName = "지식 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].EName = "INT Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][3].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].HName = "회피율 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].EName = "Defense Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][4].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].HName = "프로텍션 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].EName = "Protection Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][5].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].HName = "행운 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].EName = "Luck Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][6].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].HName = "시야 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].EName = "Vision Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][7].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].HName = "공격력 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].EName = "Damage Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][8].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].HName = "마법 공격력 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].EName = "Magic Damage Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][9].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].HName = "생명력 재생 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].EName = "HP Regen Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][10].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].HName = "생명력 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].EName = "HP Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][11].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].HName = "명중률 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].EName = "ToHit Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][12].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].HName = "리바이벌 셋";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].EName = "Revival Set";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].Description = "죽은 애완동물을 일정 확률로 살릴 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].SetFrameID( 800, 823, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][13].SetDropFrameID( 800 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].HName = "프리미엄 리바이벌 셋";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].EName = "Premium Revival Set";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].Description = "죽은 애완동물을 일정 확률로 살릴 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].SetFrameID( 801, 824, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][14].SetDropFrameID( 801 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].HName = "레드 버드";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].EName = "Red Bird";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].SetFrameID( 799, 822, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][15].SetDropFrameID( 799 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].HName = "모든 능력치 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].EName = "All Attribute Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][16].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].HName = "마법력 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].EName = "MP Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][17].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].HName = "크리티컬 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].EName = "Critical Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][18].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].HName = "공격속도 옐로우 드롭";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].EName = "Attack Speed Yellow Drop";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].Description = "애완동물을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].SetFrameID( 802, 825, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][19].SetDropFrameID( 802 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].HName = "뮤턴트 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].EName = "Mutant Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].Description = "사용하면 영구적으로 울버린으로 변신하며 되돌릴 수 없습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].SetFrameID( 857, 880, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][20].SetDropFrameID( 857 );

	// 2005.05.12 sjheon  4월 신규 마켓 아이템  add
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].HName = "폴리모프 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].EName = "Polymorph Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].Description = "울프독은 종족펫으로 종족펫은 울프펫으로 바꾸어 줍니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].SetFrameID( 996, 1030, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][21].SetDropFrameID( 996 );
	// 2005.05.12 sjheon  4월 신규 마켓 아이템  end

	// 2005.08.14 sjheon  8월 신규 마켓 아이템  add	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].HName = "펫 속성 초기화 물약";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].EName = "Pet Attribute Cleaner Potion";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].Description = "펫의 속성을 초기화 시켜주는 물약입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].SetFrameID( 1005, 1039, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][22].SetDropFrameID( 1005 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].HName = "마스크오브몬스터";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].EName = "Mask of Monster";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].Description = "6시간 동안 펫의 외형을 몬스터로 변화시켜 주는 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].SetFrameID( 1000, 1034, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][23].SetDropFrameID( 1000 );


	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].HName = "매지컬 펫 체인져";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].EName = "Magical Pet changer";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].Description = "개량 하고자 하는 펫아이템 위에 올려놓고 오른 클릭하여 사용합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].SetFrameID( 1001, 1035, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][24].SetDropFrameID( 1001 );
	// 2005.08.14 sjheon  8월 신규 마켓 아이템  add	

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].HName = "익스퍼트 펫 체인저";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].EName = "Expert Pet Changer";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].Description = "개량 하고자 하는 펫아이템 위에 올려놓고 오른 클릭하여 사용합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].SetFrameID( 1016, 1050, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][25].SetDropFrameID( 1016 );
	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].HName = "레드 버드 2";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].EName = "Red Bird 2";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].Description = "49 레벨 이상 펫에 사용 가능 합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].SetFrameID( 799, 822, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][26].SetDropFrameID( 799 );
	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].HName = "쇼크 캡슐";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].EName = "Shock Capsule";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].Description = "50 레벨 펫에 사용 가능 합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].SetFrameID( 1153, 1180, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][27].SetDropFrameID( 1153 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].HName = "클로킹 캡슐";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].EName = "Cloaking Capsule";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].Description = "50 레벨 펫에 사용 가능 합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].SetFrameID( 1154, 1181, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][28].SetDropFrameID( 1154 );

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].HName = "다이어트 캡슐";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].EName = "Diet Capsule";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].Description = "50 레벨 펫에 사용 가능 합니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].SetFrameID( 1155, 1182, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][29].SetDropFrameID( 1155 );
	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].HName = "괴도루펭 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].EName = "Lupeng Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].Description = "울프독을 괴도루펭으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].SetFrameID( 1164, 1191, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].SetDropFrameID( 1164 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][30].Price = 0;

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].HName = "밀리터리 베어 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].EName = "Military Bear Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].Description = "울프독을 밀리터리 베어로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].SetFrameID( 1179, 1208, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].SetDropFrameID( 1179 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][31].Price = 0;

	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].HName = "가고일 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].EName = "Gargoyle Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].Description = "울프독을 가고일로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].SetFrameID( 1176, 1205, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].SetDropFrameID( 1176 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][32].Price = 0;
	itemType = 33;	
#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
	//33
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "파이어 엘레멘탈 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Fire Elemental Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 파이어 엘레멘탈로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1261, 1304, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1261 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__NEW_PET_FIRE_ELEMENTAL

#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
	//34
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "서큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Succubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 서큐버스로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1297, 1341, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1297 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__2008_OCTOBER_MAKETITEM
	
#if __CONTENTS(__NEW_PET_INCUBUS)
	//35
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "인큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Incubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 인큐버스로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1312, 1356, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1312 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__NEW_PET_INCUBUS

#if __CONTENTS(__PET_VISION_AMPLE)
	//36
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "비젼 앰플";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Vision Ampul";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "펫을 훈련시킬 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1311, 1355, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1311 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__PET_VISION_AMPLE
#if __CONTENTS(__PET_MASHIMARO)
	//37
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "마시마로 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Mashimaro Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 마시마로로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1364, 1408, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1364);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__PET_MASHIMARO

#if __CONTENTS(__PET_CATS)
	//38
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "태비 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Tabby Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 태비 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1370, 1414, 0 );	// (ItemTile.ispk, Item.ispk, 0);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1370);		// (ItemTile.ispk);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//39
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "웰시 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Wealthy Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 웰시 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1371, 1415, 0 );	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1371);	
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//40
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "샤밍 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

// 2009.09.21 업그레이드 펫 고양이
#if __CONTENTS(__PET_CATS_UPGRADED)

	//41
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 미노타우루스 태비 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Minotaurs Tabby Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 태비 캣으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1406, 1450, 0 );		// (ItemTile.ispk, Item.ispk, 0);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1406);			// (ItemTile.ispk);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//42
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 프타 태비 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Ptha Tabby Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 태비 캣으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1406, 1450, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1406);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//43
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 로크 웰시 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Roc Wealthy Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 웰시 캣으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1405, 1449, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1405);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//44
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 프타 웰시 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Ptha Wealthy Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 웰시 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1405, 1449, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1405);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//45
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 지니어스 샤밍 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Genius Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1404, 1448, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1404);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//46
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "카라 프타 샤밍 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Ptha Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 카라 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1404, 1448, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1404);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//47
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 데스트로이 태비 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Destroy Tabby Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 태비 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1403, 1447, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1403);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//48
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 바루나 태비 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Varuna Tabby Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 태비 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1403, 1447, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1403);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//49
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 네크로맨시 웰시 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Necromancy Wealthy Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 웰시 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1402, 1446, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1402);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//50
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 바루나 웰시 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Varuna Wealthy Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 웰시 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1401, 1446, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1401);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//51
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 드라큘라 샤밍 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Dracula Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1400, 1445, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1400);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//52
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "델라 바루나 샤밍 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Della Varuna Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 델라 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1400, 1445, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1400);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

#endif //__PET_CATS_UPGRADED


#endif //__PET_CATS

#if __CONTENTS(__UPGRADE_MONSTER_PET)
	//53
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "미노타 인큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Minota Incubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 힘 +6의 인큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1413, 1457, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1413 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//54
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "프타 인큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Ptha Incubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치+3의 인큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1414, 1458, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1414 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//55
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "로크 서큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Roc Succubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 민첩 +6의 서큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1415, 1459, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1415 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//56
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "프타 서큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Ptha Succubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +3의 서큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1416, 1460, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1416 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//57
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "지니어스 가고일 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Cara Genius Gargoyle Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 지식 +6의 가고일로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1417, 1461, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1417 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//58
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "프타 가고일 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Ptha Gargoyle Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +3의 가고일 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1418, 1462, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1418 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//59
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "데스트로 인큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Destro Incubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 물리 공격력 +10의 인큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1419, 1463, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1419 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//60
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바루나 인큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Varuna Incubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +10의 인큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1420, 1464, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1420 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//61
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "네크로 서큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Necro Succubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 마법 데미지 +10의 서큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1421, 1465, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1421 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//62
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바루나 서큐버스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Varuna Succubus Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +10의 서큐버스로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1422, 1466, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1422 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//63
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "드라큘라 가고일 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Dracula Gargoyle Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +6의 가고일로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1423, 1467, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1423 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//64
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바루나 가고일 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Varuna Gargoyle Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +10의 가고일로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1424, 1468, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1424 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//65
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "리포지션 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Reposition Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "몬스터 펫을 1*1 크기의 울프독 목줄로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1439, 1483, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1439 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
#endif //__UPGRADE_MONSTER_PET

	//66
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바루나 괴도 루펭 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모능 +10 의 괴도 루펭으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1460, 1504, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1460);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//67
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "드라큘라 괴도 루펭 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +6의 괴도 루펭으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1461, 1505, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1461);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//68
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "프타 괴도 루펭 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모능 +3의 괴도 루펭으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1462, 1506, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1462);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//69
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "데카톤 괴도 루펭 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 회피율 +10의 괴도 루펭으로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1463, 1507, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1463);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//70
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바루나 밀리터리 베어 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모능 +10의 밀리터리 베어로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1464, 1508, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1464);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//71
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "드라큘라 밀리터리 베어 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +6의 밀리터리 베어로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1465, 1509, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1465);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//72
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "프타 밀리터리 베어 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모능 +3의 밀리터리 베어로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1466, 1510, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1466);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//73
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "피닉스 밀리터리 베어 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 명중율 +10의 밀리터리 베어로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1467, 1511, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1467);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//74
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "디스트로이 엘레멘탈 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 물리 데미지 +10의 파이어 엘레멘탈로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1468, 1512, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1468);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//75
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "네크로맨시 엘레멘탈 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "마법 데미지 +10의 파이어 엘레멘탈로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1469, 1513, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1469);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//76
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "퍼인펄 엘레멘탈 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 데미지 +6의 파이어 엘레멘탈로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1470, 1514, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1470);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//77
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "코런덤 엘레멘탈 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든저항 +11의 파이어 엘레멘탈로 전환시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1471, 1515, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1471);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//78
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "네펜데스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 라듐 네펜데스 포트로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1526, 1570, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1526);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//79
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "보후마나 라듐 네펜데스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "모든 능력치 +8의 라듐 네펜데스 포트로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1527, 1571, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1527);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//80
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "인드라 라듐 네펜데스 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +12의 라듐 네펜데스 포트로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1528, 1572, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1528);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//81
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "토륨 러피언 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "토륨 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1529, 1573, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1529);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//82
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "보후마나 토륨 러피언 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "모든 능력치 +8의 토륨 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1530, 1574, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1530);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//83
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "인드라 토륨 러피언 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +12의 토륨 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1531, 1575, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1531);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//84
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "악티늄 러피언 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 악티늄 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1532, 1576, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1532);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//85
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "보후마나 악티늄 러피언 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +8의 악티늄 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1533, 1577, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1533);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//86
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "인드라 악티늄 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +12의 악티늄 러피언으로 변환시켜주는 1회용 주사기입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1534, 1578, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1534);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//87
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바이스텐더 데드바디 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 회피율 +30의 데드바디 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1544, 1588, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1544);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//88
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "데카론 데드바디 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "회피율 +10의 데드바디 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1544, 1588, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1544);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//89
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "데드바디 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 데드바디 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1544, 1588, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1544);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//90
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "Hitholic 터닝데드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//91
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "피닉스 터딩데드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//92
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "터닝데드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//93
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "Proteus 키드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//94
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "미노타우로스 키드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//95
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "키드 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//96
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "Zeigarnik 캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//97
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "로크 캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;

	//98 여기서부터 번호 맞음, 이전까지 1개씩 밀림
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 샤밍 캣으로 변경할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1372, 1416, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1372);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//99
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "블루버드 캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 INT +18의 캡틴 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1546, 1590, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1546);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//100
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "지니어스 캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 INT +6의 캡틴 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1546, 1590, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1546);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//101
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "캡틴 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 캡틴 미니미로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1546, 1590, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1546);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//102
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "인드라 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "모든 능력치 +12의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1631, 1675, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1631);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//103
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "디스트로이 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 물리공격력 +10의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1631, 1675, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1631);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//104
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "네크로맨시 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 마법 공격력 +10의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1631, 1675, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1631);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//105
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "드라큘라 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +6의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1631, 1675, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1631);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//106
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "바이슈타 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +8의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1632, 1676, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1632);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//107
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "스파다 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +4의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1632, 1676, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1632);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//108
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "올리빈 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 저항력 +11의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1632, 1676, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1632);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//109
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "오우거 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 STR +3의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1633, 1677, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1633);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//110
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "호크 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 DEX +3의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1633, 1677, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1633);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//111
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "소서리 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 INT +3의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.a";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1633, 1677, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1633);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//112
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "와이트 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 HP흡수 +2의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1633, 1677, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1633);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	//113
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].HName = "모트 캐나인 인젝션";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].EName = "Siaming Injection";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Description = "울프독을 모든 능력치 +2의 캐나인으로 변형시킬 수 있는 1회용 인젝션입니다.";
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetFrameID( 1633, 1677, 0 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetDropFrameID( 1633);
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_PET_ENCHANT_ITEM][itemType].Price = 0;
	itemType++;
	InitClass(ITEM_CLASS_LUCKY_BAG, 4);

	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].HName = "초록색 복주머니";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].EName = "The Green Lucky Bag";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].SetFrameID( 830, 853, 0 );	
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].SetDropFrameID( 830 );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][0].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].HName = "파란색 복주머니";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].EName = "The Blue Lucky Bag";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].SetFrameID( 831, 854, 0 );	
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].SetDropFrameID( 831 );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][1].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].HName = "황금색 복주머니";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].EName = "The Gold Lucky Bag";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].SetFrameID( 832, 855, 0 );	
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].SetDropFrameID( 832 );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].HName = "프리미엄 쿠폰";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].EName = "Premium Coupon";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].Description = "50장을 모으면 새로운 세상이 열립니다.";
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].SetFrameID( 855, 878, 0 );	
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].SetDropFrameID( 855 );
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_LUCKY_BAG][3].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE;

	//------------------------------------------------------------------
	//	SMS Item
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_SMS_ITEM, 9);

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].HName = "U2A 무전기 (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].EName = "U2A Wireless Set (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].SetFrameID( 862, 885, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].SetDropFrameID( 862 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][0].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].HName = "피의 전서 (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].EName = "Blood Carrier Bat (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].SetFrameID( 863, 886, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].SetDropFrameID( 863 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][1].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].HName = "알세이데스의 나뭇잎 (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].EName = "Alseides Leef (SMS) 12";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].SetFrameID( 864, 887, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].SetDropFrameID( 864 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].HName = "U2A 무전기 (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].EName = "U2A Wireless Set (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].SetFrameID( 862, 885, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].SetDropFrameID( 862 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][3].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].HName = "피의 전서 (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].EName = "Blood Carrier Bat (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].SetFrameID( 863, 886, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].SetDropFrameID( 863 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][4].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].HName = "알세이데스의 나뭇잎 (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].EName = "Alseides Leef (SMS) 25";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].SetFrameID( 864, 887, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].SetDropFrameID( 864 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][5].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].HName = "U2A 무전기 (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].EName = "U2A Wireless Set (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].SetFrameID( 862, 885, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].SetDropFrameID( 862 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][6].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].HName = "피의 전서 (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].EName = "Blood Carrier Bat (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].SetFrameID( 863, 886, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].SetDropFrameID( 863 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][7].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].HName = "알세이데스의 나뭇잎 (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].EName = "Alseides Leef (SMS) 60";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].Description = "";
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUND_ITEM_MOVE_BOMB, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].SetFrameID( 864, 887, 0 );	
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].SetDropFrameID( 864 );
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SMS_ITEM][8].Price	= 0;

	//------------------------------------------------------------------
	//	CORE ZAP Item
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_CORE_ZAP, 4);

	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].HName = "질드레 코어잽 블랙";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].EName = "Gilles de Rais Core Zap Black";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].SetFrameID( 870, 893, 0 );	
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].SetDropFrameID( 870 );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][0].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].HName = "질드레 코어잽 레드";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].EName = "Gilles de Rais Core Zap Red";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].SetFrameID( 872, 895, 0 );	
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].SetDropFrameID( 872 );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][1].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].HName = "질드레 코어잽 블루";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].EName = "Gilles de Rais Core Zap Blue";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].SetFrameID( 869, 892, 0 );	
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].SetDropFrameID( 869 );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].HName = "질드레 코어잽 그린";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].EName = "Gilles de Rais Core Zap Green";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].SetFrameID( 871, 894, 0 );	
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].SetDropFrameID( 871 );
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CORE_ZAP][3].Price	= 0;


	//------------------------------------------------------------------
	//	ITEM_CLASS_GQUEST_ITEM
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_GQUEST_ITEM, 27
#if __CONTENTS(__QUEST_RENEWAL)
		+3
#endif
		);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].HName = "브리콜라카스의 편지";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].EName = "Bricolakas's Letter";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].SetFrameID( 108, 70, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].SetDropFrameID( 108 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][0].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].HName = "라르바의 편지";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].EName = "Larva's Letter";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].SetFrameID( 108, 70, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].SetDropFrameID( 108 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][1].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].HName = "보급표";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].EName = "Supply Ticket";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].SetSoundID(SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL,SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].SetFrameID(  118, 39, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].SetDropFrameID( 118 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].HName = "데이터 디스크";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].EName = "Data Disk";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].SetFrameID( 110, 66, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].SetDropFrameID( 110  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][3].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].HName = "집행인의 혈석 1단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].EName = "Bloody Stone 1";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].SetFrameID( 876, 899, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].SetDropFrameID( 876  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][4].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].HName = "집행인의 혈석 2단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].EName = "Bloody Stone 2";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].SetFrameID( 877, 900, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].SetDropFrameID( 877  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][5].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].HName = "집행인의 혈석 3단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].EName = "Bloody Stone 3";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].SetFrameID( 878, 901, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].SetDropFrameID( 878  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][6].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].HName = "교관 수첩 1단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].EName = "Professor License 1";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].SetFrameID( 873, 896, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].SetDropFrameID( 873  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][7].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].HName = "교관 수첩 2단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].EName = "Professor License 2";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].SetFrameID( 874, 897, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].SetDropFrameID( 874  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][8].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].HName = "교관 수첩 3단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].EName = "Professor License 3";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].SetFrameID( 875, 898, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].SetDropFrameID( 875  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][9].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].HName = "인도의 날개 1단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].EName = "Guide Wing 1";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].SetFrameID( 879, 902, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].SetDropFrameID( 879  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][10].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].HName = "인도의 날개 2단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].EName = "Guide Wing 2";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].SetFrameID( 880, 903, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].SetDropFrameID( 880  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][11].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].HName = "인도의 날개 3단계";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].EName = "Guide Wing 3";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].SetFrameID( 881, 904, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].SetDropFrameID( 881  );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][12].Price	= 0;

	// 2004, 9, 13, sobeit add start - 상자..또-_-
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].HName = "빨간색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].EName = "Red Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 10이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].SetFrameID( 833, 856, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].SetDropFrameID( 833 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][13].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].HName = "주황색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].EName = "Orange Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 20이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].SetFrameID( 899, 922, 0);	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].SetDropFrameID( 899 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][14].Price	= 5000;
	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].HName = "노란색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].EName = "Yellow Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 30이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].SetFrameID( 836, 859, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].SetDropFrameID( 836 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][15].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].HName = "초록색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].EName = "Green Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 40이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].SetFrameID( 835, 858, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].SetDropFrameID( 835 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][16].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].HName = "파란색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].EName = "Blue Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 50이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].SetFrameID( 834, 857, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].SetDropFrameID( 834 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][17].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].HName = "남색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].EName = "Deep Blue Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 60이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].SetFrameID( 897, 920, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].SetDropFrameID( 897 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][18].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].HName = "보라색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].EName = "Violet Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 70이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].SetFrameID( 898, 921, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].SetDropFrameID( 898 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][19].Price	= 5000;

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].HName = "검은색 선물상자";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].EName = "Black Present Box";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].Description = "신규 생성 캐릭터에게 적용되는 이벤트 입니다. 레벨 80이상만 열 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUNDID_NULL, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].SetFrameID( 896, 919, 0 );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].SetDropFrameID( 896 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][20].Price	= 5000;
	// 2004, 9, 13, sobeit add end - 상자..또-_-

	// 2005, 1, 14, sobeit add start

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].HName = "슬레이어의 극비문서";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].EName = "Top Secret Letter from EVE";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].SetFrameID( 976, 1010, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].SetDropFrameID( 976 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][21].SetDescriptionFrameID(952);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].HName = "뱀파이어의 회신문서";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].EName = "Reply from Vampire";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].SetFrameID( 975, 1009, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].SetDropFrameID( 975 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][22].SetDescriptionFrameID(951);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].HName = "뱀파이어의 극비문서'";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].EName = "Top Secret Letter from Vampire";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].SetFrameID( 975, 1009, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].SetDropFrameID( 975 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][23].SetDescriptionFrameID(951);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].HName = "슬레이어의 회신문서";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].EName = "Reply from EVE";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].SetFrameID( 976, 1010, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].SetDropFrameID( 976 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][24].SetDescriptionFrameID(952);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].HName = "라비니아의 증표";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].EName = "Labinia\'s Voucher";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].SetFrameID( 974, 1008, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].SetDropFrameID( 974 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][25].SetDescriptionFrameID(950);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].HName = "라르바의 전갈";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].EName = "Larba\'s Letter";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].SetFrameID( 973, 1007, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].SetDropFrameID( 973 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][26].SetDescriptionFrameID(949);

#if __CONTENTS(__QUEST_RENEWAL)
	itemType = 27;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].HName = "썩은 박쥐의 머리";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].EName = "Rotten Bat's Head";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetFrameID( 1209, 1250, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetDropFrameID( 1209 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType++].SetDescriptionFrameID(949);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].HName = "죽은 수호자의 영혼";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].EName = "Dead Guardian's spirit";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetFrameID( 1210, 1251, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetDropFrameID( 1210 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType++].SetDescriptionFrameID(949);

	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].HName = "무공훈장";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].EName = "The Order of Military Merit";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetFrameID( 1208, 1249, 0  );	
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetDropFrameID( 1208 );
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType].Price	= 0;
	m_pTypeInfo[ITEM_CLASS_GQUEST_ITEM][itemType++].SetDescriptionFrameID(949);

#endif

	// 2005, 1, 14, sobeit add end


	//------------------------------------------------------------------
	//	ITEM_CLASS_TRAP_ITEM
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_TRAP_ITEM, 10);

	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].HName = "랜드 마인";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].EName = "Land Mine";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].SetFrameID(893, 916, 0);			
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].SetDropFrameID( 893 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][0].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].HName = "플레져 스테이션";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].EName = "Pleasure Station";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].SetFrameID(894, 917, 0);			
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].SetDropFrameID( 884 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].SetGrid(2, 3);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][1].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].HName = "크레이모어";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].EName = "Claymore Trap";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].SetFrameID(892, 915, 0);		
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].SetDropFrameID( 892 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].HName = "오토 터렛";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].EName = "Auto Turret";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].SetFrameID(891, 914, 0);	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].SetDropFrameID( 891 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].SetGrid(2, 3);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][3].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].HName = "드럼통";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].EName = "Drum";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].SetFrameID(885, 908, 0);	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].SetDropFrameID( 885 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][4].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].HName = "삼각대 A";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].EName = "Tripod A";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].SetFrameID(886, 909, 0);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].SetDropFrameID( 886 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][5].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].HName = "삼각대 B";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].EName = "Tripod B";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].SetFrameID(887, 910, 0);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].SetDropFrameID( 887 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][6].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].HName = "삼각대 C";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].EName = "Tripod C";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].SetFrameID(888, 911, 0);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].SetDropFrameID( 888 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][7].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].HName = "장애물 A";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].EName = "Obstacle A";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].SetFrameID(889, 912, 0);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].SetDropFrameID( 889 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][8].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].HName = "장애물 B";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].EName = "Obstacle B";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].Description = "";
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].SetFrameID(890, 913, 0);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].SetDropFrameID( 890 );
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_TRAP_ITEM][9].Price	= 0;
	

	//------------------------------------------------------------------
	//	ITEM_CLASS_BLOOD_BIBLE_SIGN
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_BLOOD_BIBLE_SIGN, 12
#if __CONTENTS(__CONTRIBUTE_SYSTEM_ITEM )
//#if __CONTENTS(__CONTRIBUTE_SYSTEM_ITEM)
		+ 72
#endif	//__CONTRIBUTE_SYSTEM_ITEM
		);

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].HName = "아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].EName = "Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][0].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].HName = "미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].EName = "Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][1].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].HName = "키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].EName = "Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][2].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].HName = "아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].EName = "Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][3].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].HName = "그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].EName = "Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][4].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].HName = "콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].EName = "Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][5].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].HName = "레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].EName = "Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][6].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].HName = "힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].EName = "Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][7].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].HName = "쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].EName = "Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][8].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].HName = "네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].EName = "Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][9].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].HName = "아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].EName = "Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][10].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].HName = "차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].EName = "Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][11].Price = 0;

#if __CONTENTS(__CONTRIBUTE_SYSTEM_ITEM )
//#if __CONTENTS(__CONTRIBUTE_SYSTEM_ITEM)
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].HName = "그룬 아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].EName = "Grun Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][12].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].HName = "그룬 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].EName = "Grun Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][13].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].HName = "그룬 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].EName = "Grun Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][14].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].HName = "그룬 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].EName = "Grun Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][15].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].HName = "그룬 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].EName = "Grun Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][16].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].HName = "그룬 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].EName = "Grun Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][17].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].HName = "그룬 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].EName = "Grun Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][18].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].HName = "그룬 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].EName = "Grun Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][19].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].HName = "그룬 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].EName = "Grun Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][20].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].HName = "그룬 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].EName = "Grun Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][21].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].HName = "그룬 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].EName = "Grun Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][22].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].HName = "그룬 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].EName = "Grun Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][23].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].HName = "칸 아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].EName = "Khan Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][24].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].HName = "칸 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].EName = "Khan Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][25].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].HName = "칸 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].EName = "Khan Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][26].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].HName = "칸 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].EName = "Khan Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][27].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].HName = "칸 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].EName = "Khan Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][28].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].HName = "칸 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].EName = "Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][29].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].HName = "칸 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].EName = "Khan Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][30].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].HName = "칸 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].EName = "Khan Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][31].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].HName = "칸 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].EName = "Khan Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][32].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].HName = "칸 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].EName = "Khan Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][33].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].HName = "칸 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].EName = "Khan Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][34].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].HName = "칸 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].EName = "Khan Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][35].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].HName = "가브리 아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].EName = "Gabri Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][36].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].HName = "가브리 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].EName = "Gabri Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][37].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].HName = "가브리 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].EName = "Gabri Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][38].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].HName = "가브리 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].EName = "Gabri Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][39].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].HName = "가브리 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].EName = "Gabri Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][40].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].HName = "가브리 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].EName = "Gabri Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][41].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].HName = "가브리 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].EName = "Gabri Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][42].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].HName = "가브리 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].EName = "Gabri Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][43].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].HName = "가브리 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].EName = "Gabri Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][44].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].HName = "가브리 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].EName = "Gabri Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][45].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].HName = "가브리 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].EName = "Gabri Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][46].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].HName = "가브리 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].EName = "Gabri Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][47].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].HName = "팬텀 아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].EName = "Phantom Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][48].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].HName = "팬텀 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].EName = "Phantom Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][49].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].HName = "팬텀 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].EName = "Phantom Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][50].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].HName = "팬텀 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].EName = "Phantom Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][51].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].HName = "팬텀 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].EName = "Phantom Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][52].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].HName = "팬텀 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].EName = "Phantom Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][53].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].HName = "팬텀 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].EName = "Phantom Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][54].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].HName = "팬텀 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].EName = "Phantom Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][55].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].HName = "팬텀 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].EName = "Phantom Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][56].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].HName = "팬텀 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].EName = "Phantom Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][57].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].HName = "팬텀 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].EName = "Phantom Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][58].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].HName = "팬텀 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].EName = "Phantom Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][59].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].HName = "아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].EName = "Led Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][60].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].HName = "레드 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].EName = "Led Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][61].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].HName = "레드 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].EName = "Led Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][62].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].HName = "레드 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].EName = "Led Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][63].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].HName = "레드 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].EName = "Led Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][64].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].HName = "레드 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].EName = "Led Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][65].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].HName = "레드 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].EName = "Led Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][66].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].HName = "레드 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].EName = "Led Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][67].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].HName = "레드 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].EName = "Led Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][68].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].HName = "레드 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].EName = "Led Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][69].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].HName = "레드 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].EName = "Led Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][70].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].HName = "레드 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].EName = "Led Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][71].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].HName = "오제 아르메가";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].EName = "Auge Armega";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].SetFrameID( 419, 963, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].SetDropFrameID(419 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][72].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].HName = "오제 미호레";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].EName = "Auge Mihole";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].SetFrameID( 420, 964, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].SetDropFrameID(420 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][73].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].HName = "오제 키로";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].EName = "Auge Kiro";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].SetFrameID( 421, 965, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].SetDropFrameID(421 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][74].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].HName = "오제 아이니";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].EName = "Auge Ini";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].SetFrameID( 416, 966, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].SetDropFrameID(416 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][75].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].HName = "오제 그레고리";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].EName = "Auge Gregori";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].SetFrameID( 418, 967, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].SetDropFrameID(418 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][76].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].HName = "오제 콘칠리아";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].EName = "Auge Concilia";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].SetFrameID( 417, 968, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].SetDropFrameID(417 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][77].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].HName = "오제 레지오스";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].EName = "Auge Legios";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].SetFrameID( 410, 969, 0);	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].SetDropFrameID(410 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][78].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].HName = "오제 힐릴";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].EName = "Auge Hillel";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].SetFrameID( 412, 970, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].SetDropFrameID(412 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][79].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].HName = "오제 쟈브";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].EName = "Auge Jave";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].SetFrameID( 411, 971, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].SetDropFrameID(411 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][80].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].HName = "오제 네마";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].EName = "Auge Nema";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].SetFrameID( 414, 972, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].SetDropFrameID(414 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][81].Price = 0;

	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].HName = "오제 아로사";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].EName = "Auge Arosa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].SetFrameID( 415, 973, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].SetDropFrameID(415 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][82].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].HName = "오제 차스파";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].EName = "Auge Chaspa";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].Description = "피의 성서";
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].SetFrameID( 413, 974, 0);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].SetDropFrameID(413 );
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_BLOOD_BIBLE_SIGN][83].Price = 0;




#endif	//__CONTRIBUTE_SYSTEM_ITEM


	//------------------------------------------------------------------
	//	ITEM_CLASS_WAR_ITEM
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_WAR_ITEM, 1
#if __CONTENTS(__HERO_SYSTEM_ITEM )
//#if __CONTENTS(__HERO_SYSTEM_ITEM)
		+ 6
#endif //__HERO_SYSTEM_ITEM
		);

	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].HName = "드레곤의 눈";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].EName = "Dragon Eyes";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].SetFrameID( 939, 975, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].SetDropFrameID(939 );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][0].Price = 0;

#if __CONTENTS(__HERO_SYSTEM_ITEM )
//#if __CONTENTS(__HERO_SYSTEM_ITEM)
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].HName = "세이버 쉴드";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].EName = "Saver Shield";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].SetFrameID( 1181, 1210, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].SetDropFrameID(1181 );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][1].Price = 0;
	

	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].HName = "바이어런트 스컬";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].EName = "Violent Skull";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].SetFrameID( 1180, 1209, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].SetDropFrameID(1180 );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][2].Price = 0;

	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].HName = "인피니티 쉘";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].EName = "Infinity Shell";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].SetFrameID( 1182, 1211, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].SetDropFrameID(1182);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][3].Price = 0;


	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].HName = "칼리고 세이버 쉴드";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].EName = "Caligo Saver Shield";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].SetFrameID( 1181, 1210, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].SetDropFrameID(1181 );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][4].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].HName = "칼리고 바이어런트 스컬";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].EName = "Caligo Violent Skull";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].SetFrameID( 1180, 1209, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].SetDropFrameID(1180 );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][5].Price = 0;

	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].HName = "칼리고 인피니티 쉘";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].EName = "Caligo Infinity Shell";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].Description = "아이템 습득 시 생명력(HP) 5배, 이동속도가 2배로 증가됩니다.";
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].SetFrameID( 1182, 1211, 0);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].SetDropFrameID(1182);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_WAR_ITEM][6].Price = 0;
#endif	//__HERO_SYSTEM_ITEM


//// by csm  2차 전직 용 아이템 추가 

//------------------------------------------------------------------
//	ITEM_CLASS_CARRYING_RECEIVER
//------------------------------------------------------------------
	InitClass(ITEM_CLASS_CARRYING_RECEIVER, 2);
				
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].HName = "인포 스크랩";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].EName = "Info Scrap";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].SetFrameID( 954, 990, 0);
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].SetDropFrameID(954 );
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].HName = "와이드 인콰이어러";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].EName = "Wide inquirer";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetFrameID( 1065, 1099, 0);
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetDropFrameID(1065 );
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Price = 5000;
	
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].HName = "와이드 인콰이어러";
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].EName = "Wide inquirer";
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_CARRYING_RECEIVER][1].Price = 0;

//------------------------------------------------------------------
//	ITEM_CLASS_SHOULDER_ARMOR
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_SHOULDER_ARMOR, 2);
				
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].HName = "토드 백";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].EName = "Toad Back";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].SetFrameID( 950, 986, 0);
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].SetDropFrameID(950 );
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].Price = 0;
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][0].SetAddonFrameID( AC_SHOULDER, AC_SHOULDER );
	
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].HName = "슬랜트 가드";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].EName = "Slant Guard";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetFrameID( 1066, 1100, 0);
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetDropFrameID(1066 );
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Price = 55000000;
	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetAddonFrameID( AC_SHOULDER, AC_SHOULDER );
	
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].HName = "슬랜트 가드";
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].EName = "Slant Guard";
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_SHOULDER_ARMOR][1].Price = 0;

//------------------------------------------------------------------
//	ITEM_CLASS_DERMIS
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_DERMIS, 2);
				
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].HName = "어라우즈 크레스트";
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].EName = "Arouse crest";
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].SetFrameID( 942, 978, 0);
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].SetDropFrameID(942 );
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DERMIS][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].HName = "이모탈 크레스트";
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].EName = "Immortal crest";
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetFrameID( 1071, 1105, 0);
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetDropFrameID(1071 );
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Price = 5000;
	
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].HName = "이모탈 크레스트";
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].EName = "Immortal crest";
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_DERMIS][1].Price = 0;

//------------------------------------------------------------------
//	ITEM_CLASS_PERSONA
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_PERSONA, 2);
				
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].HName = "크레프티 베일";
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].EName = "Crafty veil";
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].SetFrameID( 941, 977, 0);
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].SetDropFrameID(941 );
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_PERSONA][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].HName = "카오틱 모랄";
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].EName = "Chaotic moral";
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetFrameID( 1072, 1106, 0);
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetDropFrameID(1072 );
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Price = 55000000;
	
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].HName = "카오틱 모랄";
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].EName = "Chaotic moral";
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_PERSONA][1].Price = 0;

//------------------------------------------------------------------
//	ITEM_CLASS_FASCIA
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_FASCIA, 2);
				
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].HName = "팔마 페이샤";
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].EName = "Palma fascia";
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].SetFrameID( 965, 1001, 0);
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].SetDropFrameID(965 );
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_FASCIA][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].HName = "누투스 페이샤";
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].EName = "Nutus fascia";
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetFrameID( 1078, 1112, 0);
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetDropFrameID(1078 );
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Price = 55000000;
	
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].HName = "누투스 페이샤";
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].EName = "Nutus fascia";
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_FASCIA][1].Price = 0;	


//------------------------------------------------------------------
//	ITEM_CLASS_MITTEN
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_MITTEN, 2);
				
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].HName = "프라엘리움 글로브";
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].EName = "Praelium gloves";
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].SetFrameID( 960, 996, 0);
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].SetDropFrameID(960 );
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MITTEN][0].Price = 0;
	
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].HName = "임페리움 글로브";
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].EName = "Imperium gloves";
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetFrameID( 1077, 1111, 0);
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetDropFrameID(1077 );
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Price = 5000;
	
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].HName = "임페리움 글로브";
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].EName = "Imperium gloves";
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Description = "";
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetFrameID( 939, 975, 0);
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetDropFrameID(939 );
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].SetGrid(1, 1);
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Weight = 1;
//	m_pTypeInfo[ITEM_CLASS_MITTEN][1].Price = 0;	


//------------------------------------------------------------------
//	ITEM_CLASS_SUB_INVENTORY
//------------------------------------------------------------------	

	InitClass(ITEM_CLASS_SUB_INVENTORY, 3);

	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].HName = "2x4 팩";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].EName = "2x4 Pack";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].SetFrameID( 979, 1013, 0, 1197);
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].SetDropFrameID(979 );
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][0].Price = 0;


	// 2005.08.14 sjheon  8월 신규 마켓 아이템  add	
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].HName = "4x6 팩";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].EName = "4x6 Pack";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].Description = "보조 인벤토리 아이템으로 4X6칸의 아이템 창이 확장됩니다.";
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].SetFrameID( 998, 1032, 0, 1198);
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].SetDropFrameID(998 );
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][1].Price = 0;
	// 2005.08.14 sjheon  8월 신규 마켓 아이템  End	


 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].HName = "10x6 팩";
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].EName = "10x6 Pack";
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].Description = "보조 인벤토리 아이템으로 10X6칸의 아이템 창이 확장됩니다.";
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].SetFrameID( 1167, 1194, 0, 1196);
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].SetDropFrameID(1167 );
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].SetGrid(1, 1);
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].Weight = 10000;
 	m_pTypeInfo[ITEM_CLASS_SUB_INVENTORY][2].Price = 0;


	//------------------------------------------------------------------
	//	ITEM_CLASS_COMMON_QUEST_ITEM
	//------------------------------------------------------------------
	InitClass(ITEM_CLASS_COMMON_QUEST_ITEM, 6
#if __CONTENTS(__MENEGROTH_ITEM)
		+ 12
#endif //__MENEGROTH_ITEM
#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
		+ 12
#endif // __LEVEL_WAR_RENEWAL_ITEM

#if __CONTENTS(__TIPOJYU_CASTLE_ITEM)
		+1
#endif // __TIPOJYU_CASTLE_ITEM

#if __CONTENTS(__ONIBLA_ITEM)
		+4
#endif // __ONIBLA_ITEM
#if __CONTENTS(__TREASURE_BOX)
		+17
#endif //__TREASURE_BOX
#if __CONTENTS(__MOONLIGHT_FESTIVAL_EVENT)
		+1
#endif //__MOONLIGHT_FESTIVAL_EVENT
		);

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].HName = "유실된 보급품";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].EName = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].SetFrameID( 1027,1061, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].SetDropFrameID(1027 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][0].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].HName = "뱀피오릭 코어";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].EName = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].SetFrameID( 1025,1059, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].SetDropFrameID(1025 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][1].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].HName = "고대의 기억";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].EName = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].SetFrameID( 1023,1057, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].SetDropFrameID(1023 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][2].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].HName = "무두질용 칼";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].EName = "Tanning Knife";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].Description = "가죽을 벗겨낼 때 사용하는 칼입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].SetFrameID( 1110,1138, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].SetDropFrameID(1110 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][3].Price = 10000;

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].HName = "깨끗한 가죽";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].EName = "Neat Leather";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].Description = "정교하게 벗겨낸 가죽. 매우 질이 좋은 가죽이다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].SetFrameID( 1108,1136, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].SetDropFrameID(1108 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][4].Price = 32000;

	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].HName = "손상된 가죽";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].EName = "Injury Leather";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].Description = "서투른 솜씨로 인해 찢어진 가죽.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].SetFrameID( 1111,1139, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].SetDropFrameID(1111 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][5].Price = 3000;

#if __CONTENTS(__MENEGROTH_ITEM)
	itemType =	6;


	//던전 입장 아이템 - 인장류
	// 6
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "케르베로스 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Cerberus's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "21~40 레벨까지 케르베로스 인장으로 메네그로스 던전 B1층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1193, 1234, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1193 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 7
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "맨티코아트 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Manticoret's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "41~60 레벨까지 멘티코아트 인장으로 메네그로스 던전 B2층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1184, 1225, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1184 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 8
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "보글트_H 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Boglet_H's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "61~80 레벨까지 보글트_H 인장으로 메네그로스 던전 B3층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1186, 1227, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1186 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 9
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "보글트_B 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Boglet_B's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "81~100 레벨까지 보글트_B 인장으로 메네그로스 던전 B4층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1185, 1226, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1185 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 10
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "매서커 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Massacre's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "101~120 레벨까지 매서커 인장으로 메네그로스 던전 B5층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1183, 1224, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1183 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 11
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "플럼피보어 인장";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Plumy Boar's seal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "121 레벨부터 플럼피보어 인장으로 메네그로스 던전 B6층에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1194, 1235, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1194 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;

	//보스소환 아이템 - 심장류.
	// 12
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(1층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B1";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B1층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1187, 1228, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1187 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 13
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(2층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B2";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B2층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1188, 1229, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1188 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 14
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(3층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B3";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B3층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1189, 1230, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1189 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 15
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(4층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B4";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B4층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1190, 1231, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1190 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 16
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(5층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B5";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B5층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1191, 1232, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1191 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	// 17
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "카브라캄의 심장(6층)";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Heart of Cabracam B6";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "카브라캄의 심장은 메네그로스 던전 B6층에서 보스소환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1192, 1233, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1192 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType++].Price = 50;
	
#endif //__MENEGROTH_ITEM
	

#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM )
//#if __CONTENTS(__LEVEL_WAR_RENEWAL_ITEM)

	#if __CONTENTS(__MENEGROTH_ITEM)
		itemType =	18;
	#else 
		itemType =	6;
	#endif //__MENEGROTH_ITEM

	// 18
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "칼리의 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Khali's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "칼리의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1223, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 19
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오시리스의 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Osiris's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "오시리스의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1222, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 20
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "리르의 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Lir's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "리르의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1221, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 21
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "칼리의 동색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Bronze Khali's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "칼리의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1217, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 22
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오시리스의 동색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Bronze Osiris's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "오시리스의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1216, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 23
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "리르의 동색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Bronze Lir's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "리르의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1215, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 24
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "칼리의 은색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Silver Khali's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "칼리의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1220, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 25
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오시리스의 은색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Silver Osiris's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "오시리스의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1219, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;	
	itemType++;
	// 26
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "리르의 은색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Silver Lir's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "리르의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1218, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 27
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "칼리의 금색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Gold Khali's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "칼리의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1214, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 28
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오시리스의 금색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Gold Osiris's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "오시리스의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1213, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 29
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "리르의 금색 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Gold Lir's Voucher";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "리르의 증표는 해당 NPC를 통해 보상 교환이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1138, 1212, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1138 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 0;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;

#endif	//__LEVEL_WAR_RENEWAL_ITEM

#if __CONTENTS(__TIPOJYU_CASTLE_ITEM)
	// 30
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "영험 한 서";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "A miracle epistle";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "150레벨 이상 부터 티포쥬 성 던전 2F 에 진입이 가능합니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1267, 1309, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1267 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(2, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 7;
	itemType++;
#endif // __TIPOJYU_CASTLE_ITEM

#if __CONTENTS(__ONIBLA_ITEM)
	// 31
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오니블라의 등뼈";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Onibla`s Spine";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "고급 아이템과 교환할 수 있는 아이센 던전 수집품입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SKULL, SOUND_ITEM_MOVE_SKULL, SOUNDID_NULL, SOUND_ITEM_MOVE_SKULL );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1351, 1395, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1351 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 1;
	itemType++;
	// 32
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "영웅의 증표";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Voucher of Hero";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "출석 체크 이벤트로 받을 수 있는 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1360, 1404, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1360 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;
	itemType++;
	// 33
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "오니블라의 등뼈 조각";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Onibla`s Spine-bit";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "오니블라의 선물 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SKULL, SOUND_ITEM_MOVE_SKULL, SOUNDID_NULL, SOUND_ITEM_MOVE_SKULL );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1361, 1405, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1361 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 2);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 1;
	itemType++;
	// 34
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "각성의 열쇠";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Key of Disilusion";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "아이센4층 비밀의 방을 열 수 있는 열쇠입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1345, 1388, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1345 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Price = 1;
	itemType++;
#endif // __ONIBLA_ITEM
#if __CONTENTS(__TREASURE_BOX)
	// 35
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 유니키";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Uni-key";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 보물상자를 열 수 있는 열쇠입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1365, 1409, 0);
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1365 );
	itemType++;

	//36
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 1";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 1";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//37
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 2";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 2";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//38
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 3";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 3";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//39
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 4";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 4";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//40
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 5";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 5";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//41
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 6";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 6";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//42
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 7";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 7";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//43
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 8";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 8";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//44
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 9";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 9";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//45
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 10";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 10";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//46
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 11";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 11";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//47
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 12";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 12";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//48
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 13";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 13";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//49
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 14";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 14";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//50
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 15";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 15";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;

	//51
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "일반 보물상자 16";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Normal Case 16";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "일반 유니키로만 열 수 있는 일반 보물상자입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX, SOUND_XMAS_GIFTBOX );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1373, 1417, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1373 );
	itemType++;
#endif //__TREASURE_BOX

#if __CONTENTS(__MOONLIGHT_FESTIVAL_EVENT)
	//52
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].HName = "달빛 결정";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].EName = "Moonlight Crystal";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].Description = "달빛 축제 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_KEY, SOUND_ITEM_MOVE_KEY, SOUNDID_NULL, SOUND_ITEM_MOVE_KEY );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetFrameID( 1391, 1435, 0 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].SetDropFrameID( 1391 );
	m_pTypeInfo[ITEM_CLASS_COMMON_QUEST_ITEM][itemType].ItemMoveControl = ITEMMOVE_CANNOT_DROP;
	itemType++;
#endif //__MOONLIGHT_FESTIVAL_EVENT


	//------------------------------------------------------------------
	//	ITEM_CLASS_ETHEREAL_CHAIN
	//------------------------------------------------------------------

	InitClass(ITEM_CLASS_ETHEREAL_CHAIN, 3);

	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].HName = "에테리얼 체인";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].EName = "Ethereal Chain";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].Description = "목걸이에 사용하는 소켓장비";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].SetFrameID( 1026,1060, 0);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].SetDropFrameID(1026);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].Price = 0;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][0].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_TRADE;
	

	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].HName = "장미의 축복";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].EName = "Blessing the rose";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].Description = "장미의 축복 이벤트 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].SetFrameID( 1132,1160, 0);//1132 이미지 없음
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].SetDropFrameID(1132);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].Price = 1;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][1].ItemMoveControl = ITEMMOVE_CANNOT_DROP;


	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].HName = "잊혀진 유물";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].EName = "Relic of oblivion";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].Description = "이벤트 전용 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].SetFrameID( 1166,1193, 0);//1132 이미지 없음
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].SetDropFrameID(1166);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].Price = 1;
	m_pTypeInfo[ITEM_CLASS_ETHEREAL_CHAIN][2].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;


	//------------------------------------------------------------------
	//	ITEM_CLASS_OUSTERS_HARMONIC_PENDENT
	//------------------------------------------------------------------

	InitClass(ITEM_CLASS_OUSTERS_HARMONIC_PENDENT, 1);

	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].HName = "결속의 펜던트";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].EName = "Harmonic Pendant";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].Description = "장착하신 후 오른쪽 클릭을 하시면 상대방 커플이 있는 위치로 이동할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].SetFrameID( 1048, 1082, 0);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].SetDropFrameID(1048 );
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].SetValue(3, 1, -1, -1, -1, 0);	
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].Price = 0;
	m_pTypeInfo[ITEM_CLASS_OUSTERS_HARMONIC_PENDENT][0].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_KEEP_STORAGE | ITEMMOVE_CANNOT_TRADE;

	
	//---------------------------------------------------------------------
	// ITEM_CLASS_CHECK_MONEY
	//---------------------------------------------------------------------
	InitClass(ITEM_CLASS_CHECK_MONEY, 3 );

	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].HName = "겔드 수표";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].EName = "Geld  Check";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].Description = "수표 교환 NPC를 통해 게임머니로 전환할 수 있다(상점 판매는 불가능한 아이템이다.)";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].SetSoundID( SOUND_ITEM_MOVE_MONEY, SOUND_ITEM_MOVE_MONEY, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].SetFrameID( 1051, 1085, 0 );	
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].SetDropFrameID( 1051 );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][0].ItemMoveControl = ITEMMOVE_CANNOT_DROP;

	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].HName = "레이 수표";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].EName = "Lei  Check";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].Description = "수표 교환 NPC를 통해 게임머니로 전환할 수 있다(상점 판매는 불가능한 아이템이다.)";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].SetSoundID( SOUND_ITEM_MOVE_MONEY, SOUND_ITEM_MOVE_MONEY, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].SetFrameID( 1053, 1087, 0 );	
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].SetDropFrameID( 1053 );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][1].ItemMoveControl = ITEMMOVE_CANNOT_DROP;

	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].HName = "자드 수표";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].EName = "Zard Check";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].Description = "수표 교환 NPC를 통해 게임머니로 전환할 수 있다(상점 판매는 불가능한 아이템이다.)";
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].SetSoundID( SOUND_ITEM_MOVE_MONEY, SOUND_ITEM_MOVE_MONEY, SOUNDID_NULL, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].SetFrameID( 1052, 1086, 0 );	
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].SetDropFrameID( 1052 );
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CHECK_MONEY][2].ItemMoveControl = ITEMMOVE_CANNOT_DROP;


	//---------------------------------------------------------------------
	// ITEM_CLASS_CUE_OF_ADAM
	//---------------------------------------------------------------------
	InitClass(ITEM_CLASS_CUE_OF_ADAM, 5);
	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].HName = "큐 오브 아담 레드";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].EName = "Cue Of Adam Red";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].Description = "";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].SetFrameID( 1080, 1114, 0 );	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].SetDropFrameID( 1080 );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][0].Price	= 0;
	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].HName = "큐 오브 아담 그린";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].EName = "Cue Of Adam Green";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].Description = "";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].SetFrameID( 1081, 1115, 0 );	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].SetDropFrameID( 1081 );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][1].Price	= 0;
	

	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].HName = "큐 오브 아담 블루";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].EName = "Cue Of Adam Blue";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].Description = "";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].SetFrameID( 1082, 1116, 0 );	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].SetDropFrameID( 1082 );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][2].Price	= 0;

	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].HName = "큐 오브 아담 블렉";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].EName = "Cue Of Adam Black";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].Description = "";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].SetFrameID( 1083, 1117, 0 );	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].SetDropFrameID( 1083 );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][3].Price	= 0;


	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].HName = "고대의 매듭";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].EName = "ancient knot";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].Description = "이벤트 전용 아이템 입니다.";
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].SetFrameID( 1165, 1192, 0 );	
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].SetDropFrameID( 1165 );
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CUE_OF_ADAM][4].Price	= 1;


	//---------------------------------------------------------------------
	// ITEM_CLASS_CONTRACT_OF_BLOOD
	//---------------------------------------------------------------------
	InitClass(ITEM_CLASS_CONTRACT_OF_BLOOD, 4
#if __CONTENTS(__ONIBLA_ITEM)
		+3
#endif // __ONIBLA_ITEM		
		);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].HName = "피의계약";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].EName = "Contract Of Adam";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].Description = "계약내용에 따라 주인에게 힘을 부여한다.";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].SetFrameID(1084, 1118,0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].SetDropFrameID(1084);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][0].Price = 0;

	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].HName = "헬 가든의 계약서";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].EName = "Contract Of Hellgarden";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].Description = "계약내용에 따라 주인에게 힘을 부여한다.";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].SetFrameID(1084, 1176, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].SetDropFrameID(1084);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][1].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].HName = "예지의 계약서";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].EName = "Contract Of Foresight";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].Description = "계약내용에 따라 주인에게 힘을 부여한다.";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].SetFrameID(1084, 1177, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].SetDropFrameID(1084);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][2].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;

	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].HName = "심안의 계약서";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].EName = "Contract Of Mind's Eye";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].Description = "계약내용에 따라 주인에게 힘을 부여한다.";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].SetFrameID(1084, 1178, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].SetDropFrameID(1084);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][3].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;

#if __CONTENTS(__ONIBLA_ITEM)
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].HName = "오니블라의 피의 계약서";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].EName = "Contract of Onibla`s Blood";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].Description = "";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].SetFrameID(1349, 1396, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].SetDropFrameID(1349);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][4].ItemMoveControl = ITEMMOVE_CANNOT_TRADE | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_PICKUP_ONCE | ITEMMOVE_CANNOT_DROP;
	
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].HName = "아스트랄 피의 계약서(블랙)";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].EName = "Contract of Astral Blood(Black)";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].Description = "";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].SetFrameID(1347, 1392, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].SetDropFrameID(1347);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][5].ItemMoveControl = ITEMMOVE_CANNOT_TRADE | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_PICKUP_ONCE | ITEMMOVE_CANNOT_DROP;

	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].HName = "아스트랄 피의 계약서(화이트)";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].EName = "Contract of Astral Blood(White)";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].Description = "";
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].SetFrameID(1347, 1392, 0);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].SetDropFrameID(1347);
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].SetGrid( 2, 2 );
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].Price = 0;
	m_pTypeInfo[ITEM_CLASS_CONTRACT_OF_BLOOD][6].ItemMoveControl = ITEMMOVE_CANNOT_TRADE | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_PICKUP_ONCE | ITEMMOVE_CANNOT_DROP;
#endif // __ONIBLA_ITEM

	
	//---------------------------------------------------------------------
	// ITEM_CLASS_CUE_OF_ADAM
	//---------------------------------------------------------------------
	InitClass(ITEM_CLASS_SKILL_BOOK, 20 
#if __CONTENTS(__SECOND_RARE_SKILL)
		+17
#endif //__SECOND_RARE_SKILL
#if __CONTENTS(__20091116_ADD_RARE_SKILL)
		+4
#endif //__20091116_ADD_RARE_SKILL
		);

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].HName = "매직 쉴드 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].EName = "Magic Shield 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].Description = "검 도메인 레벨 60이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][0].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].HName = "매직 쉴드 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].EName = "Magic Shield 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].Description = "검 도메인 레벨 120이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][1].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].HName = "이글즈 아이 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].EName = "Eagle's Eye 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].Description = "총 도메인 레벨 60이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][2].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].HName = "이글즈 아이 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].EName = "Eagle's Eye 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].Description = "총 도메인 레벨 120이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][3].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].HName = "프리즈 링 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].EName = "Freeze Ring 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].Description = "순수 INT 90이상. 힐/인첸 도메인 레벨 20이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][4].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].HName = "프리즈 링 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].EName = "Freeze Ring 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].Description = "순수 INT 150이상. 힐/인첸 도메인 레벨 80이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][5].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].HName = "뱃 스톰 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].EName = "Bat Storm 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].Description = "레벨 30이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].SetRequireLevel(30);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][6].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].HName = "뱃 스톰 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].EName = "Bat Storm 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].Description = "레벨 100이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].SetRequireLevel(100);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][7].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].HName = "커스 오브 블러드 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].EName = "Curse Of Blood 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].Description = "레벨 20이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][8].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].HName = "커스 오브 블러드 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].EName = "Curse Of Blood 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].Description = "레벨 80이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][9].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].HName = "블러드 드레인 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].EName = "Blood Drain 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].Description = "레벨 40이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][10].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].HName = "블러디 샤우트 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].EName = "Bloody Shout 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].Description = "레벨 50이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][11].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].HName = "블러디 샤우트 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].EName = "Bloody Shout 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].Description = "레벨 100이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][12].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].HName = "블러디 윙즈";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].EName = "Bloody Wings";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].Description = "순수 INT 400이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][13].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].HName = "미스트 오브 소울 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].EName = "Mist Of Soul 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].Description = "레벨 20이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][14].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].HName = "미스트 오브 소울 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].EName = "Mist Of Soul 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].Description = "레벨 80이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][15].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].HName = "에너지 버스트";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].EName = "Energy Burst";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].Description = "레벨 60이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][16].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].HName = "매직 어보이드 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].EName = "Magic Avoid 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].Description = "레벨 50이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][17].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].HName = "매직 어보이드 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].EName = "Magic Avoid 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].Description = "레벨 100이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][18].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].HName = "매직 어보이드 3";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].EName = "Magic Avoid 3";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].Description = "레벨 150이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].Price	= 100;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].DropItemNameTag = 180;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][19].ItemMoveControl = ITEMMOVE_CANNOT_DROP | ITEMMOVE_CANNOT_DISPLAY_PERSNALSHOP | ITEMMOVE_CANNOT_TRADE;

#if __CONTENTS(__SECOND_RARE_SKILL)
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].HName = "헤븐리 스파크";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].EName = "Heavenly spark";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].Description = "슬레이어 검 계열 세트 등급이상, 인피니티 선더볼트를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][20].DropItemNameTag = 180;
	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].HName = "블레이드 스톰";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].EName = "Blade Storm";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].Description = "슬레이어 도 계열 세트 등급이상, 스핏 스트림을 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][21].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].HName = "XRL";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].EName = "eXplosion Rocket Launcher";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].Description = "슬레이어 군인 계열 세트 등급이상, 플라즈마 로켓 런처를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][22].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].HName = "제네시스";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].EName = "Genesis";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].Description = "슬레이어 치료 계열 세트 등급이상, 버밍스타를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][23].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].HName = "쏜즈";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].EName = "Thorns";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].Description = "슬레이어 축복 계열 세트 등급이상, 스피릿 가드를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][24].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].HName = "리썰 클로우";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].EName = "Lethal Claw";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].Description = "뱀파이어 세트 등급이상이 되어야 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][25].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].HName = "베놈 서클";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].EName = "Venom Circle";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].Description = "뱀파이어 세트 등급이상이 되어야 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][26].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].HName = "브류나크";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].EName = "Brionac";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].Description = "아우스터즈 전사 계열 세트 등급이상, 디스트럭션 스피어를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][27].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].HName = "아스테로이드 봄버";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].EName = "Asteroid Bomber";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].Description = "아우스터즈 대지마법 계열 세트 등급이상, 승직 스킬 데스티니즈를 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][28].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].HName = "프로즌 글레셔";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].EName = "Frozen Glacier";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].Description = "아우스터즈 물마법 계열 세트 등급이상, 승직 스킬 쉐도우오브스톰을 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].SetFrameID( 1171, 1201, 0 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][29].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].HName = "인시너레이트";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].EName = "Incinerate";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].Description = "아우스터즈 불마법 계열 세트 등급이상, 승직 스킬 피어스 프레임을 습득해야만 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][30].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].HName = "인크리즈 오브 헬스1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].EName = "Increase of health1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].Description = "호루스 1등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][31].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].HName = "인크리즈 오브 헬스2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].EName = "Increase of health2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].Description = "인크리즈 오브 헬스1,세트 등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][32].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].HName = "인크리즈 오브 헬스3";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].EName = "Increase of health3";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].Description = "인크리즈 오브 헬스2,마아트 등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][33].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].HName = "인크리즈 오브 헬스4";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].EName = "Increase of health4";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].Description = "인크리즈 오브 헬스3,오시리스 등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][34].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].HName = "인크리즈 오브 헬스5";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].EName = "Increase of health5";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].Description = "인크리즈 오브 헬스4,토트 등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][35].DropItemNameTag = 180;

	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].HName = "인크리즈 오브 헬스6";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].EName = "Increase of health6";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].Description = "인크리즈 오브 헬스5,누트 등급 이상 배울 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].SetFrameID( 1171, 1201, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].SetDropFrameID( 1171 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][36].DropItemNameTag = 180;
#endif //__SECOND_RARE_SKILL
#if __CONTENTS(__20091116_ADD_RARE_SKILL)
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].HName = "마그마 데토네이션 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].EName = "Magma Detonation 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].Description = "50레벨 이상의 도 슬레이어가 배울 수 있는 스킬 북입니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][37].DropItemNameTag = 180;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].HName = "마그마 데토네이션 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].EName = "Magma Detonation 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].Description = "100레벨 이상의 도 슬레이어가 배울 수 있는 스킬 북입니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][38].DropItemNameTag = 180;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].HName = "질풍의 베리어 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].EName = "Squally Barrier 1";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].Description = "50레벨 이상, 순수 힘 + 순수 민첩의 합이 180 이상의 전사 아우스터즈가 배울 수 있는 스킬 북입니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].SetFrameID( 1169, 1199, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].SetDropFrameID( 1169 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][39].DropItemNameTag = 180;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].HName = "질풍의 베리어 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].EName = "Squally Barrier 2";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].Description = "100레벨 이상, 순수 힘 + 순수 민첩의 합이 320 이상의 전사 아우스터즈가 배울 수 있는 스킬 북입니다.";
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].SetFrameID( 1170, 1200, 0 );	
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].SetDropFrameID( 1170 );
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].Price	= 7,000,000;
	m_pTypeInfo[ITEM_CLASS_SKILL_BOOK][40].DropItemNameTag = 180;
#endif //__20091116_ADD_RARE_SKILL

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER_ITEM)
	InitClass(ITEM_CLASS_VAMPIREWING_ITEM, 1
#if __CONTENTS(__SECOND_TRANSFORTER_ITEM)
		+1
#endif //__SECOND_TRANSFORTER_ITEM
		);

	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].HName = "플리러마우스";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].EName = "Flittermouse";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Description = "뱀파이어 고속이동 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetFrameID( 1215, 1256, 0 );	
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetDropFrameID( 1215 );
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Price	= 10000;

#if __CONTENTS(__SECOND_TRANSFORTER_ITEM)
	itemType++; // 1
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].HName = "쉐이프 오브 데몬";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].EName = "Shape Of Demon";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Description = "빠른 이동을 할 수 있는 뱀파이어 전용 쉐이프 오브 데몬 입니다.";
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetFrameID( 1259, 1302, 0 );	
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetDropFrameID( 1259 );
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_VAMPIREWING_ITEM][itemType].Price	= 10000;
#endif //__SECOND_TRANSFORTER_ITEM


	InitClass(ITEM_CLASS_OUSTERSWING_ITEM, 1
#if __CONTENTS(__SECOND_TRANSFORTER_ITEM)
		+1
#endif //__SECOND_TRANSFORTER_ITEM
		);

	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].HName = "세레곤";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].EName = "Seregon";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Description = "아우스터즈 고속이동 아이템입니다.";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetFrameID( 1214, 1255, 0 );	
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetDropFrameID( 1214 );
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Price	= 10000;

#if __CONTENTS(__SECOND_TRANSFORTER_ITEM)
	itemType++;	// 1
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].HName = "유니콘";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].EName = "Unicorn";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Description = "빠른 이동을 할 수 있는 아우스터즈 전용 유니콘 입니다.";
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_CLOTH, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetFrameID( 1260, 1303, 0 );	
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetDropFrameID( 1260 );
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].SetGrid(1, 1);
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Weight = 1;
	m_pTypeInfo[ITEM_CLASS_OUSTERSWING_ITEM][itemType].Price	= 10000;
#endif //__SECOND_TRANSFORTER

#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER_ITEM

#if __CONTENTS(__TUNING_ITEM)
	// Description = %s를 다음단계로 업그레이드 할 수 있습니다. (사용조건: %s급이상)
	
	InitClass(ITEM_CLASS_TUNING_SLAYER, 64+6+6+3 );

	// 무기
	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "니들엣져 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Niddle Edger Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 946, 982, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(946 );

	itemType++;	// 1
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "피어브링어 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Fear Bringer Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1056, 1090, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1056 );

	itemType++;	// 2
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "발뭉 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Balmung Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1235, 1278, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1235 );

	itemType++;	// 3
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "소드 엠페러 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Sword Emperor Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1056, 1090, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1056 );

	itemType++;	// 4
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "듀오카포 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Duocarpo Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 947, 983, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(947 );

	itemType++;	// 5
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "앵글커터 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Angle Cutter Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1057, 1091, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1057 );

	itemType++;	// 6
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "마사무네 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Masamune Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1234, 1277, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1234 );

	itemType++;	// 7
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "퀸즈커터 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Queen's Cutter Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1057, 1091, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1057 );
	
	itemType++;	// 8
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "릴라이언트 크루시스 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Reliant Crusis Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 951, 987, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(951 );

	itemType++;	// 9
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "어큐트 크루시스 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Acute Crucis Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1059, 1093, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1059 );

	itemType++;	// 10
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "홀리 엔틱 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Holy Antique Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1246, 1289, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1246 );

	itemType++;	// 11
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "나자렛 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Nazareth Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1059, 1093, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1059 );

	itemType++;	// 12
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "S-22 웨스턴 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "S-22 Western Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1230, 1273 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1230 );

	itemType++;	// 13
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "USAS-12 오토 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "USAS-12 Auto Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 905, 928 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 905 );

	itemType++;	// 14
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "UZI 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "UZI Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID(  1239, 1282 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1239 );

	itemType++;	// 15
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "톰슨 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Tompson Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID(  904,927 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 904 );

	itemType++;	// 16
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "바탈리온 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Battalion Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 953, 989, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(953 );

	itemType++;	// 17
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "카발 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Cabal Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1055, 1089, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1055 );

	itemType++;	// 18
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "AK-47 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "AK-47 Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1228, 1271, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1228 );

	itemType++;	// 19
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "K-3 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "K-3 Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1055, 1089, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1055 );

	itemType++;	// 20
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "택티컬 스카우트 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Tactical Scout Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 955, 991, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(955);

	itemType++;	// 21
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "블레이저 LRS 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Blaser LRS Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1054, 1088, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1054 );

	itemType++;	// 22
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "드라그노프 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Dragunov Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1231, 1274, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1231 );

	itemType++;	// 23
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "PSG-1 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "PSG-1 Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUND_ITEM_MOVE_GUN, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1054, 1088, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1054 );

	itemType++;	// 24
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "세일리언스 엣서 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Salience Asser Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 948, 984, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(948 );

	itemType++;	// 25
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "클룩 앳서 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Crook Asser Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1060, 1094, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1060 );

	itemType++;	// 26
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "스톰 볼트 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Storm Volt Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1237, 1280, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1237 );

	itemType++;	// 27
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "묠니르 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Mjolnir Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUND_ITEM_MOVE_SWORD, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1060, 1094, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1060 );

	// 방어구
	itemType++;	// 28
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "매쉬 스킨 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Mesh Skin Legendry M";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 956, 992, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(956 );

	itemType++;	// 29
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "매쉬 스킨 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Mesh Skin Legendry W";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 958, 994, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(958 );

	itemType++;	// 30
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "머슬 슈트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Muscle Suit Legendry M";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1061, 1095, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1061 );

	itemType++;	// 31
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "머슬 슈트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Muscle Suit Legendry W";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1063, 1097, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1063 );

	itemType++;	// 32
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "코어링 슈트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Coring Suit Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1244, 1287, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1244);

	itemType++;	// 33
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "코어링 슈트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Coring Suit Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1245, 1288, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1245);

	itemType++;	// 34
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "티타늄 재킷 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Titanium Jacket Legendry M";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1063, 1097, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1063 );

	itemType++;	// 35
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "티타늄 재킷 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Titanium Jacket Legendry W";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1063, 1097, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1063 );

	itemType++;	// 36
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "클링 슬랙 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Cling Slack Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 957, 993, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(957 );

	itemType++;	// 37
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "클링 슬랙 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Cling Slack Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 959, 995, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(959 );

	itemType++;	// 38
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "쉘 가드 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Shell Guard Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1062, 1096, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1062 );

	itemType++;	// 39
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "쉘 가드 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Shell Guard Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1064, 1098, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1064 );

	itemType++;	// 40
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "코어링 게이트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Coring Gaiters Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1242, 1285, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1242 );

	itemType++;	// 41
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "코어링 게이트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Coring Gaiters Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1243, 1286, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1243 );

	itemType++;	// 42
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "티타늄 레깅스 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Titanium Leggings Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1064, 1098, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1064 );

	itemType++;	// 43
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "티타늄 레깅스 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Titanium Leggings Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1064, 1098, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1064 );

	itemType++;	// 44
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "헥토르 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Hektor Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SHOES, SOUND_ITEM_MOVE_SHOES, SOUND_ITEM_MOVE_SHOES, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1247 , 1290 , 0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1247 );

	itemType++;	// 45
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "케레스 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Ceres Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SHOES, SOUND_ITEM_MOVE_SHOES, SOUND_ITEM_MOVE_SHOES, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 919 , 942 , 0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 919 );

	itemType++;	// 46
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "스퍼 버클러 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Spur Buckler Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 949, 985, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(949 );

	itemType++;	// 47
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "스타우트 버클러 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Stout Buckler Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1058, 1092, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1058 );

	itemType++;	// 48
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "에스터 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Ester Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1238, 1281, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1238);

	itemType++;	// 49
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "버팔로 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Buffalo Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1058, 1092, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1058 );

	itemType++;	// 50
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "루미네선스 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Luminescence Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1233 , 1276 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1233 );

	itemType++;	// 51
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "레오파드 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Leopard Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 920 , 943 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 920 );

	itemType++;	// 52
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "마운트 고글 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Mount Goggles Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 952, 988, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(952 );

	itemType++;	// 53
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "멀티 스카우터 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Multi Scouter Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1067, 1101, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1067 );

	itemType++;	// 54
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "ESS 택티컬 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "ESS Tactical Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1229, 1272, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1229 );

	itemType++;	// 55
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "미스릴 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Mithril Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1067, 1101, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID(1067 );

	itemType++;	// 56
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "워렛트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Warret Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BELT, SOUND_ITEM_MOVE_BELT, SOUND_ITEM_MOVE_BELT, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1240, 1283, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1240 );

	itemType++;	// 57
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "다이아나 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Diana Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BELT, SOUND_ITEM_MOVE_BELT, SOUND_ITEM_MOVE_BELT, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 449, 463, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 449 );

	// 액세서리
	itemType++;	// 58
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "앵크 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Ankh Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 155, 159, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 155 );

	itemType++;	// 59
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "이스팀 링 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Esteem Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 453, 467, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 453 );

	itemType++;	// 60
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "케볼레타 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Kabollefa Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 481, 495, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 481 );
	
	itemType++;	// 61
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "볼라시오 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Volasio Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 917 , 940 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 917 );

	itemType++;	// 62
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "쥴란 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Julien Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1241 , 1284 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1241 );

	itemType++;	// 63
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "하피 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Harpy Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 917 , 940 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 917 );

	itemType++;	// 64
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "홀리 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Holy Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 158, 162, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 158 );

	itemType++;	// 65
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "솔리스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Solis Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 452, 466, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 452 );

	itemType++;	// 66
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "담피르 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Dhampir Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 480, 494, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 480 );

	itemType++;	// 67
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "크루스닉 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Krsnik Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 932 , 955 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 932 );
	
	itemType++;	// 68
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "블루 마린 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Blue Marine Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1236 , 1279 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1236 );

	itemType++;	// 69
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "아리엘 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Ariel Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 932 , 955 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 932 );

	itemType++;	// 70
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "실버 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Silver Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 162, 166, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 162 );

	itemType++;	// 71
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "트리니티 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Trinity Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 451, 465, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 451 );

	itemType++;	// 72
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "모건 르 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Morgan le Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 482, 496, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 482 );

	itemType++;	// 73
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "라마스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Lamassu Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 912 , 935 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 909 );

	itemType++;	// 74
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "디어니스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Dionys Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 1232 , 1275 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 1232 );

	itemType++;	// 75
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "골드 스파이더 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Gold Spider Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 912 , 935 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 909 );

	itemType++;	// 76
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "플래티넘 스파이럴 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Platinum Spiral Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 151, 155, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 151 );

	itemType++;	// 77
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "크로스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Cross Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 159, 163, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 159 );

	itemType++;	// 78
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].HName = "블러드 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].EName = "Blood Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetFrameID( 165, 169, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_SLAYER][itemType].SetDropFrameID( 165 );

	InitClass(ITEM_CLASS_TUNING_VAMPIRE, 22+10+10+4 );

	// 무기
	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "에시즈 네일 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Acies Nail Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 943, 979, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(943 );

	itemType++;	// 1
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "본 클리브 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Bone Cleave Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1068, 1102, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1068 );

	itemType++;	// 2
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "헬브레스 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Hell Breath Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1227, 1270, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1227 );

	itemType++;	// 3
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "발라카스 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Balakas Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUND_ITEM_MOVE_GLOVE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1068, 1102, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1068 );

	// 방어구
	itemType++;	// 4
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "디파이언스 클록 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Defiance Cloak Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 944, 980, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(944 );

	itemType++;	// 5
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "알루어 어페럴 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Allure Apparel Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 945, 981, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(945 );

	itemType++;	// 6
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "이모랄 클록 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Immoral Cloak Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1069, 1103, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1069 );

	itemType++;	// 7
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "프라우드 어페럴 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Proud Apparel Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1070, 1104, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1070 );
	
	itemType++;	// 8
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "엘록 시크 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Eloq Chic Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1224, 1267, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1224 );

	itemType++;	// 9
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "숄 카라 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Shawl Collar Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1222, 1265, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1222 );

	itemType++;	// 10
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "엘록 샤이닝 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Eloq Shining Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1069, 1103, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1069 );

	itemType++;	// 11
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "숄 리스크 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Shawl Risk Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1069, 1103, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID(1069 );

	// 액세서리
	itemType++;	// 12
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "스파이더 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Spider Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 169, 173, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 169 );

	itemType++;	// 13
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "펜릴 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Fenrir Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 459, 473, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 459 );

	itemType++;	// 14
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "아스프 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Asp Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 486, 500, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 486 );

	itemType++;	// 15
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "알렉산드라이트 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Alexandrite Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 924 , 947 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 924 );

	itemType++;	// 16
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "해저드 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Hazard Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1226 , 1269 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1226 );

	itemType++;	// 17
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "데몬 스컬 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Demon Skull Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 924 , 947 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 924 );

	itemType++;	// 18
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "어비스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Abyss Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 172, 176, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 172 );

	itemType++;	// 19
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "킨 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Keen Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 458, 472, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 458 );

	itemType++;	// 20
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "라피스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Lapis Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 487, 501, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 487 );

	itemType++;	// 21
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "벨라돈나 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Belladonna Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 915 , 938 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 915 );

	itemType++;	// 22
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "할로우 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Hallow Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1225 , 1268 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1225 );

	itemType++;	// 23
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "바스카 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Baska Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUND_ITEM_MOVE_BRACELET, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 915 , 938 ,0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 915 );

	itemType++;	// 24
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "데드 윙즈 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Dead Wing's Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 177, 184, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 177 );	

	itemType++;	// 25
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "이블 아이 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Evil Eye's Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 457, 471, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 457 );

	itemType++;	// 26
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "파프니르 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Fefnir Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 489, 503, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 489 );

	itemType++;	// 27
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "우자트 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Uzat Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 925 , 948 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 925 );

	itemType++;	// 28
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "레이어드 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Layard Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1221 , 1264 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1221 );

	itemType++;	// 29
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "토르말린 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Tourmaline Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 925 , 948 ,0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 925 );

	itemType++;	// 30
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "디스트럭션 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Destruction Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 314, 328, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 314 );

	itemType++;	// 31
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "하모니 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Harmony Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 460, 474, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 460 );

	itemType++;	// 32
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "히아신스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Hyacinth Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 490, 504, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 490 );

	itemType++;	// 33
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "카넬리안 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Carnelian Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 929 , 952 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 929 );

	itemType++;	// 34
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "아틸라 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Attila Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1223 , 1266 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1223 );

	itemType++;	// 35
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "피어즈 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Fears Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 929 , 952 ,0);	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 929 );

	itemType++;	// 36
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "다에그 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Daeg Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 345, 359, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 345 );

	itemType++;	// 37
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "이스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Is Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 461, 475, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 461 );

	itemType++;	// 38
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "페오 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Feoh Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 488, 502, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 488 );

	itemType++;	// 39
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "나이드 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Nied Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 910,	933, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 910 );

	itemType++;	// 40
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "라스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Ras Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 1220, 1263, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 1220 );

	itemType++;	// 41
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "임펠러 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Impeller Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 910,	933, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 910 );

	itemType++;	// 42
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "스컬즈 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Skulls Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 170, 174, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 170 );
	
	itemType++;	// 43
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "블랙 앵크 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Black Ankh Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUND_ITEM_MOVE_NECKLACE, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 176, 180, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 176 );

	itemType++;	// 44
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "캐츠 아이 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Cat's Eye's Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 313, 327, 0 );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 313 );

	itemType++;	// 45
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].HName = "오달 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].EName = "Odal Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetSoundID( SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUND_ITEM_MOVE_RING, SOUNDID_NULL );
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetFrameID( 344, 358, 0 );	
	m_pTypeInfo[ITEM_CLASS_TUNING_VAMPIRE][itemType].SetDropFrameID( 344 );

	InitClass(ITEM_CLASS_TUNING_OUSTERS, 36+4+2+4+2 );
	
	// 무기
	itemType = 0;
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "멜리스 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Melis Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_ITEM_MOVE_SCROLL, SOUND_ITEM_MOVE_SCROLL, SOUNDID_NULL, SOUND_ITEM_MOVE_SCROLL );
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 964, 1000, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(964 );

	itemType++;	// 1
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "란테아 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Rantea Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1073, 1107, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1073);

	itemType++;	// 2
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "바라사다 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Barasada Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1251, 1294, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1251);

	itemType++;	// 3
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "타르빙 인페르노";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Tyrfingr Inferno";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM, SOUND_OUSTERS_CHAKRAM);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1073, 1107, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1073);
	
	// 불아우
	itemType++;	// 4
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "네피림 인페르노[불]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Nepirim Inferno[Fire]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(961);

	itemType++;	// 5
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아르테나 인페르노[불]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Altena Inferno[Fire]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);
	
	itemType++;	// 6
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "사이키델릭 인페르노[불]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Psychedelic Inferno[Fire]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1253);

	itemType++;	// 7
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "인드라 인페르노[불]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Indra Inferno[Fire]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);

	// 물아우
	itemType++;	// 8
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "네피림 인페르노[물]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Nepirim Inferno[Water]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(961);

	itemType++;	// 9
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아르테나 인페르노[물]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Altena Inferno[Water]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);

	itemType++;	// 10
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "사이키델릭 인페르노[물]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Psychedelic Inferno[Water]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1253);
	
	itemType++;	// 11
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "인드라 인페르노[물]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Indra Inferno[Water]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);

	// 대지아우
	itemType++;	// 12
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "네피림 인페르노[대지]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Nepirim Inferno[Earth]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(961, 997 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(961);

	itemType++;	// 13
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아르테나 인페르노[대지]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Altena Inferno[Earth]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);
	
	itemType++;	// 14
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "사이키델릭 인페르노[대지]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Psychedelic Inferno[Earth]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1253, 1296, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1253);

	itemType++;	// 15
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "인드라 인페르노[대지]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Indra Inferno[Earth]";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET, SOUND_OUSTERS_WRISTLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1074, 1108, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1074);

	// 방어구
	itemType++;	// 16
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "플라이트 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Flight Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1258, 1301, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1258);
	
	itemType++;	// 17
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "사이드 암즈 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Side Arms Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND, SOUND_OUSTERS_ARMSBAND);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1102 , 934 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1102);
	
	itemType++; // 18
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "프라엘리움 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Praelium Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 962, 998, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(962 );
	
	itemType++; // 19
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "임페리움 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Imperium Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1076 , 1110, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1076 );

	itemType++;	// 20
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "엘레원 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "El Leon Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1256, 1299, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1256);
	
	itemType++;	// 21
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아르카디아 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Arkadhia Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS, SOUND_OUSTERS_BOOTS);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1076 , 1110, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1076 );

	itemType++;	// 22
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "시르 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Syr Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1255, 1298, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1255);
	
	itemType++;	// 23
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "로얄 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Royal Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET, SOUND_OUSTERS_CIRCLET);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(927 , 950 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(927);

	itemType++;	// 24
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "프라엘리움 베스티오 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Praelium Vestio Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 963, 999, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(963 );
	
	itemType++;	// 25
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "임페리움 베스티오 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Imperium Vestio Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1075, 1109, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1075 );

	itemType++;	// 26
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "엘리시움 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Elysium Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1257, 1300, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1257);

	itemType++;	// 27
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "크라운 레전드리";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Crown Legendry";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT, SOUND_OUSTERS_COAT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID( 1075, 1109, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1075 );

	// 액세서리
	itemType++;	// 28
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "이집티안 팔콘 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Egyptian Falcon Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(606, 620, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(606);

	itemType++;	// 29
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "피그 트리 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Fig Tree Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(826, 849, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(826);

	itemType++;	// 30
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "오팔루스 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Opalus Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(827, 850, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(827);

	itemType++;	// 31
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "레쉬 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Leshy Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1103 , 936 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1103);

	itemType++;	// 32
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "룬 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Runic Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1249, 1292 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1249);

	itemType++;	// 33
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아스틴 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Astin Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1103 , 936 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1103);

	itemType++;	// 34
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "이모르탈러티 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Immortality Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(691, 705, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(691);
	
	itemType++; // 35
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "안달루시아 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Andalusia Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(808, 831, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(808);

	itemType++;	// 36
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "마르둑 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Marduk Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(809, 832, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(809);
	
	itemType++;	// 37
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "사이렌 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Siren Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1105 , 962 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1105);

	itemType++;	// 38
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "시그니티 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Signity Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1254, 1297 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1254);

	itemType++;	// 39
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "지올로 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Geolo Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1105 , 962 ,0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1105);

	itemType++;	// 40
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "이그니스 아티클1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Ignis Article1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1252, 1295, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1252);

	itemType++;	// 41
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "이그니스 아티클2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Ignis Article2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1252, 1295, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1252);

	itemType++;	// 42
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아쿠아 아티클1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Aqua Article1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1250, 1293, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1250);

	itemType++;	// 43
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "아쿠아 아티클2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Aqua Article2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1250, 1293, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1250);

	itemType++;	// 44
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "테라 아티클1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Terra Article1";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1248, 1291, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1248);

	itemType++;	// 45
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "테라 아티클2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Terra Article2";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE, SOUND_OUSTERS_ELEMENTAL_STONE);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(1248, 1291, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(1248);

	itemType++; // 46
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "피어리 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Fairie Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(605, 619, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(605);

	itemType++; // 47
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].HName = "메크쟌 아티클";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].EName = "Macsan's Article";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].Description = "";
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetSoundID( SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING, SOUND_OUSTERS_RING);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetFrameID(690, 704, 0);
	m_pTypeInfo[ITEM_CLASS_TUNING_OUSTERS][itemType].SetDropFrameID(690);
	
#endif //__TUNING_ITEM

#if __CONTENTS(__GLOBAL_NPC)
	InitClass(ITEM_CLASS_CALLNPC_CARD, 6
#if __CONTENTS(__DCGLOBAL_NPC)//이아이템은 __GLOBAL_NPC의 작업이 없으면 추가 될수 없다.
		+ 6
#endif //__DCGLOBAL_NPC
		);
	
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].HName = "프로큐어먼트 페이저";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].EName = "Procurement Pager";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].Description = "슬레이어 상점 NPC를 호출할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].SetFrameID(1307, 1351, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][0].SetDropFrameID(1307);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].HName = "디스턴스 트레이드";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].EName = "Distance Trade";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].Description = "뱀파이어 상점 NPC를 호출할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].SetFrameID(1302, 1346, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][1].SetDropFrameID(1302);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].HName = "텔레파시 스톤";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].EName = "Telepathy Stone";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].Description = "아우스터즈 상점 NPC를 호출할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].SetFrameID(1306, 1350, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][2].SetDropFrameID(1306);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].HName = "리페어 툴";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].EName = "Repair Tool";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].Description = "슬레이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].SetFrameID(1303, 1347, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][3].SetDropFrameID(1303);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].HName = "언홀리 파츠";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].EName = "Unholy Parts";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].Description = "뱀파이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].SetFrameID(1305, 1349, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][4].SetDropFrameID(1305);
	
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].HName = "스피릿 큐브";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].EName = "Spirits Qube";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].Description = "아우스터즈 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].SetFrameID(1304, 1348, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][5].SetDropFrameID(1304);
#endif //__GLOBAL_NPC
#if __CONTENTS(__DCGLOBAL_NPC)
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].HName = "실버 리페어 툴";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].EName = "Silver Repair Tool";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].Description = "슬레이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].SetFrameID(1328, 1372, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][6].SetDropFrameID(1328);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].HName = "골드 리페어 툴";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].EName = "Gold Repair Tool";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].Description = "슬레이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].SetFrameID(1325, 1369, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][7].SetDropFrameID(1325);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].HName = "실버 언홀리 파츠";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].EName = "Silver Unholy Parts";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].Description = "뱀파이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].SetFrameID(1330, 1374, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][8].SetDropFrameID(1330);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].HName = "골드 언홀리 파츠";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].EName = "Gold Unholy Parts";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].Description = "뱀파이어 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].SetFrameID(1327, 1371, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][9].SetDropFrameID(1327);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].HName = "실버 스피릿 큐브";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].EName = "Silver Spirits Qube";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].Description = "아우스터즈 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].SetFrameID(1329, 1373, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][10].SetDropFrameID(1329);

	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].HName = "골드 스피릿 큐브";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].EName = "Gold Spirits Qube";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].Description = "아우스터즈 수리 NPC를 호출 할 수 있습니다.";
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].SetSoundID( SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT, SOUND_OUSTERS_PENDANT);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].SetFrameID(1326, 1370, 0);
	m_pTypeInfo[ITEM_CLASS_CALLNPC_CARD][11].SetDropFrameID(1326);
#endif //__DCGLOBAL_NPC

}
