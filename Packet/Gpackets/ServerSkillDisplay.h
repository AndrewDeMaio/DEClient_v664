#ifndef __SERVER_SKILL_DISPLAY_H__
#define __SERVER_SKILL_DISPLAY_H__

inline int TranslateServerSkillType(int skillType)
{
	switch (skillType)
	{
	case 506: return 59;	// SiusCrash
	case 507: return 77;	// LycanHowl
	case 508: return 395;	// BifronzeMagic
	case 509: return 396;	// PalusMiddleRangeMagic
	case 510: return 155;	// PalusLongRangeMagic
	case 511: return 176;	// GarumMagic
	case 512: return 57;	// ClavieMagic
	case 513: return 0;		// WideWildWolf (DK670 record is just the attack animation and a sound)
	case 514: return 0;		// BlessofLycan
	case 515: return 78;	// SmileofDeath
	case 539: return 279;	// LivingDeadBEchoEsper (slot of SKILL_WIDE_GRAY_DARKNESS, never cast)
	case 541: return 248;	// TsarBlueRoseDevil (slot of passive SKILL_DRIFTING_SOUL)
	case 542: return 222;	// FolletPoisonFrame (slot of passive SKILL_HIDE_SIGHT)
	case 543: return 249;	// FueFolletRedRoseDevil (slot of passive SKILL_CRITICAL_MAGIC)
	}
	return skillType;
}

#endif // __SERVER_SKILL_DISPLAY_H__
