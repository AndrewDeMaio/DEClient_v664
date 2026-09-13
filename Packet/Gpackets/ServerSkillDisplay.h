#ifndef __SERVER_SKILL_DISPLAY_H__
#define __SERVER_SKILL_DISPLAY_H__

inline int TranslateServerSkillType(int skillType)
{
	switch (skillType)
	{
	case 506: return 479;	// SiusCrash   
	case 507: return 485;	// LycanHowl
	case 508: return 395;	// BifronzeMagic
	case 509: return 396;	// PalusMiddleRangeMagic
	case 510: return 155;	// PalusLongRangeMagic
	case 511: return 176;	// GarumMagic
	case 512: return 57;	// ClavieMagic
	case 513: return 499;	// WideWildWolf
	case 514: return 0;		// BlessofLycan
	case 515: return 500;	// SmileofDeath
	}
	return skillType;
}

#endif // __SERVER_SKILL_DISPLAY_H__
