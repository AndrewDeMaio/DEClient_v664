#ifndef __ICON_CONTROL__
#define __ICON_CONTROL__

#include "dialog_base.h"
#include "tga.h"

#define NO_SELECT							0xFFFF

/*-----------------------------------------------------------------------------
  Style
-----------------------------------------------------------------------------*/
enum E_ICONCONTROL_STYLE
{
	IS_ONLYONE,		// 같은 Style의 다른 것을 선택하기까지 계속 유효함.
	IS_UNDO,			// 한 번 다시 click하여 선택을 취소할 수 있음.
	IS_ALWAYS,		// 다시 click가능.
};

/*-----------------------------------------------------------------------------
  Selector shape
  `눌린 상태를 나타내는 모양.
-----------------------------------------------------------------------------*/
enum E_SELECTOR_SHAPE
{
	SS_TRANSPARENT, // 반투명
	SS_RECTANGLE,	 // 사각형
};

/*-----------------------------------------------------------------------------
  Class Icon control
-----------------------------------------------------------------------------*/
class C_ICON_CONTROL : public C_DIALOG
{
private:
	//
	// Icon size
	// `특별한 용도로 icon을 다른 size로 정의하고 싶을 때가 있다.
	//
	int			m_size_x; 
	int			m_size_y;

	void  		(*m_fp_do_rightbutton_up_job)();
	E_SELECTOR_SHAPE m_selector_shape;
	int			m_i_line;
	int			m_i_column;
	int			m_i_total_count; // icon count
	void			(*m_fp_exec)(EXEC_ID);

	struct S_ICONITEM
	{
		Tga *						icon_pic;
		EXEC_ID					exec_id;
		E_ICONCONTROL_STYLE	style;
		bool						bl_push;
		bool						bl_done; // 이미 눌렸는가?
	} *m_pS_item;

	int			m_last_cut_line; // 끝에서부터 n line은 출력하지 않는다.

public:
	int	GetLastCutCount() const { return m_last_cut_line; }
	void	SetLastCutLine(int count);
	void  SetRightButtonUpJobFp(void (*fp)());
	void	SetSelectorShape(E_SELECTOR_SHAPE shape);
	void	SetIconPushState(EXEC_ID exec_id);
	void	ClearIconPushState(EXEC_ID exec_id);
	void	ClearAllIconPushState();
	void	SetToUnpushState();
	int	GetColumnCount();
	int	GetLineCount();
	int	GetTotalCount();
	bool	SetExecFp(void (*fp_exec)(EXEC_ID));
	void	AddControl(char *sz_filename, EXEC_ID exec_id, E_ICONCONTROL_STYLE style);
	void	MouseControl(UINT message, int x, int y);
	void	KeyboardControl(UINT message, UINT key);
	void	Show();

	inline int GetSizeX() const
	{
		return m_size_x;
	}

	inline int GetSizeY() const
	{
		return m_size_y;
	}

	C_ICON_CONTROL(int col, int line, int size_x, int size_y);
	~C_ICON_CONTROL();
};

#endif