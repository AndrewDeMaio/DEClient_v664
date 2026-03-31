//----------------------------------------------------------------------
// OperatorOption.h
//----------------------------------------------------------------------
// ��ڿ� �ɼ�
//----------------------------------------------------------------------

#ifndef	__OPERATOROPTION_H__
#define	__OPERATOROPTION_H__

namespace aqa { class Robot; }

class OperatorOption
{
public :
	OperatorOption();
	~OperatorOption();

	void	SetDefault();

	void	SaveToFile(const char* filename);
	bool	LoadFromFile(const char* filename);

public :
	bool	bShowModifyHP;			// HP ��ȭ�� ä��â�� ����
	bool	bShowCreatureInfo;		// ũ��ó oid ����
	bool	bShowImageObjectInfo;	// ���� ������Ʈ iid, sid, vp ����
	bool	bHideAttachEffect;		// ���� �ٴ� ����Ʈ �����
	bool	bHideSpeechBalloon;		// ��ǳ�� �����
	bool	bShowAddEffect;			// EffectStatus �߰��Ǵ°� ����
	bool	bShowModifyEXP;			// EXP ��ȭ�� ����
	bool	bSlideScreenShot;		// �����̵� ��ũ���� ���
	bool	bShowSkillRange;		// ��ų ��� ���� ����
	bool	bShowModifyRANKEXP;		// ��ް���ġ ��ȭ�� ����
	bool	bRecordCharName;		// ĳ���� �̸� txt���Ϸ� �����ϱ�
	bool	bCanRootingGhost;		// ����Ʈ ����� �� ������ ���� ����

	aqa::Robot* pAutoQARobot;		// AutoQA Robot
};


extern	OperatorOption*		g_pOperatorOption;

extern	void	UI_AddChatToHistory(const char* str, char* sz_id, int cond, DWORD color);


#endif

