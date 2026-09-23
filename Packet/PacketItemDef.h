#ifndef __PACKETITEMDEF_H__
#define __PACKETITEMDEF_H__

enum HelmetType { 
	HELMET_NONE , 
	HELMET1 ,
	HELMET2 ,
	HELMET3 ,
	HELMET_OSIRIS, // 1차 승직 오시리스 투구
	HELMET_MAX
};

enum JacketType { 
	JACKET_BASIC , 
	JACKET1 , 
	JACKET2 ,
	JACKET3 ,
	JACKET4 ,
	JACKET_OSIRIS, // 1차 승직 오시리스 상의
	JACKET_MAX
};

enum PantsType { 
	PANTS_BASIC , 
	PANTS1 , 
	PANTS2 ,
	PANTS3 ,
	PANTS4 ,
	PANTS_OSIRIS,	// 1차 승직 오시리스 하의
	PANTS_MAX
};


enum WeaponType { 
	WEAPON_NONE ,
	WEAPON_SWORD ,
	WEAPON_BLADE ,
	WEAPON_SR ,
	WEAPON_AR ,
	WEAPON_SG ,
	WEAPON_SMG ,
	WEAPON_CROSS ,
	WEAPON_MACE ,
//	WEAPON_SHIELD ,
//	WEAPON_SWORD_SHIELD ,
	WEAPON_OSIRIS_SWORD ,	// 검
	WEAPON_OSIRIS_BLADE ,	// 도
	WEAPON_OSIRIS_SR ,		// 총
	WEAPON_OSIRIS_AR ,		// 총
	WEAPON_OSIRIS_CROSS ,	// 십자가
	WEAPON_OSIRIS_MACE ,	// 메이스
	WEAPON_MAX
};

enum ShieldType { 
	SHIELD_NONE ,
	SHIELD1 ,
	SHIELD2 ,
	SHIELD_OSIRIS,	// 1차 승직 오시리스 방패
	SHIELD_MAX
};

enum MotorcycleType {
	MOTORCYCLE_NONE ,
	MOTORCYCLE1 ,
	MOTORCYCLE2 ,
	MOTORCYCLE3 ,
	MOTORCYCLE4 ,
	MOTORCYCLE5 ,
	MOTORCYCLE_MAX
};

enum ShoulderType{
	SHOULDER_NONE ,
	SHOULDER1 ,
	SHOULDER_MAX
};

enum VampireCoatType 
{ 
	VAMPIRE_COAT_BASIC , 
	VAMPIRE_COAT1 , 
	VAMPIRE_COAT2 ,
	VAMPIRE_COAT3 ,
	VAMPIRE_COAT4 ,
	VAMPIRE_OSIRIS_COAT ,	//Day 2010.01.05, ID: shootkj 1차 승직 오시리스 외형
	VAMPIRE_COAT_MAX
};

enum VampireArmType
{
	VAMPIRE_ARM_NONE,
	VAMPIRE_ARM_WEAPON,
	VAMPIRE_ARM_OSIRIS_WEAPON,		// 1차 승직 오시리스 무기 외형
	VAMPIRE_ARM_TIER1_WEAPON,		// weapon art tier 1 and 2 (GetWeaponArtTier)
	VAMPIRE_ARM_TIER2_WEAPON,
	VAMPIRE_ARM_MAX
};

enum OustersCoatType 
{ 
	OUSTERS_COAT_BASIC , 
	OUSTERS_COAT1 , 
	OUSTERS_COAT2 ,
	OUSTERS_COAT3 ,
	OUSTERS_COAT4 ,
	OUSTERS_OSIRIS_COAT ,	// 1차 승직 오시리스 외형
	OUSTERS_COAT_MAX
};

enum OustersArmType
{
	OUSTERS_ARM_GAUNTLET,
	OUSTERS_ARM_CHAKRAM,
	OUSTERS_ARM_OSIRIS_CHAKRAM,		// 1차 승직 오시리스 무기 외형
	OUSTERS_ARM_TIER1_CHAKRAM,		// weapon art tier 1 and 2 (GetWeaponArtTier)
	OUSTERS_ARM_TIER2_CHAKRAM,
	OUSTERS_ARM_MAX
};

// Item types the server gives the Osiris look (server Shape.cpp getOustersCoatType, Ousters.cpp).
const int OUSTERS_OSIRIS_COAT_ITEMTYPE		= 17;	// Crown Coat
const int OUSTERS_OSIRIS_CHAKRAM_ITEMTYPE	= 22;	// Chakram of Tyrfingr
const int VAMPIRE_OSIRIS_COAT_ITEMTYPE		= 30;	// Eloq Shining Coat
const int VAMPIRE_OSIRIS_COAT2_ITEMTYPE		= 31;	// Shawl Risk Coat
const int VAMPIRE_OSIRIS_WEAPON_ITEMTYPE	= 27;	// Claw of Valakas
const int SLAYER_OSIRIS_HELM_ITEMTYPE		= 17;	// Cyclops Fluoroscope
const int SLAYER_OSIRIS_COAT_ITEMTYPE		= 34;	// Titanium Jacket M
const int SLAYER_OSIRIS_COAT2_ITEMTYPE		= 35;	// Titanium Jacket W
const int SLAYER_OSIRIS_TROUSER_ITEMTYPE	= 34;	// Titanium Leggings M
const int SLAYER_OSIRIS_TROUSER2_ITEMTYPE	= 35;	// Titanium Leggings W
const int SLAYER_OSIRIS_SHIELD_ITEMTYPE		= 17;	// Buffalo Shield

// Weapon art tier by the weapon's required advancement: 0 = the AC* look, 1 = 11+
// (advanced*), 2 = 21+ (secondadvanced* weapon), 3 = 31+ (advanced* Osiris weapon).
// The server sends other players' weapons in the same tiers.
inline int GetWeaponArtTier(int requireAdvancementLevel)
{
	if (requireAdvancementLevel >= 31)	return 3;
	if (requireAdvancementLevel >= 21)	return 2;
	if (requireAdvancementLevel >= 11)	return 1;
	return 0;
}

// Parts drawn with the Osiris look, for S_SLOT::OsirisLook on the character select screen.
enum OSIRIS_LOOK_PART
{
	OSIRIS_LOOK_COAT	= 0x01,
	OSIRIS_LOOK_WEAPON	= 0x02,
	OSIRIS_LOOK_HELMET	= 0x04,	// Slayer only
	OSIRIS_LOOK_TROUSER	= 0x08,
	OSIRIS_LOOK_SHIELD	= 0x10,
	OSIRIS_LOOK_WEAPON_TIER1	= 0x20,	// weapon art tier 1 / 2; OSIRIS_LOOK_WEAPON is tier 3
	OSIRIS_LOOK_WEAPON_TIER2	= 0x40,
};

enum OustersSylphType
{
	OUSTERS_SYLPH_OFF,
	OUSTERS_SYLPH_ON,
	OUSTERS_SYLPH_MAX
};


#endif
