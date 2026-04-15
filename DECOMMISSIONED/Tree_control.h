#ifndef __TREE_CONTROL__
#define __TREE_CONTROL__

#include "dialog_base.h"
#include "tree.h"

/*-----------------------------------------------------------------------------
  Class Tree control
-----------------------------------------------------------------------------*/
class C_TREE_CONTROL : public C_DIALOG, public C_TREE
{
private:
	bool				m_bl_no_click; // for App

	//
	// App로 보내는 전용 Mouse control
	// `App의 입장에서는 어디서 Mouse control 메시지가 들어온지 모르므로 특별히 
	//  자신의 객체포인터를 인자로 해서 넘겨준다.
	//
	void (*m_fp_AppMouseControl)(UINT, int, int, C_TREE_CONTROL *);

	void LeftButtoneClick();

	void (*m_fp_uniqueID_receiver)(UNIQUE_ID);

	//
	// last_X
	// `scroll하기 위해서는 scroll할 양이 필요한데, 먼저 출력된 node string의 끝의
	//  좌표를 알아야 한다. 이것을 구하기 위해서 실제 string을 출력시키는 시점에서
	//  가장 큰 값(last_X)을 구한다. string을 출력시키는 시점에 start_X좌표를 알기
	//  때문이다.
	//
	int				m_last_x;
	int				m_last_y;
	
	//
	// Scroll하기 위한 변수.
	// `Scroll bar에서 Output box처럼, 이 값을 변경한다.
	// `(0 <= m_rX)
	//
	int				m_rx;
	int				m_ry;

	static bool		m_bl_edit;
	S_NODE *			m_p_click_node;	// 선택된 node
	int				m_mouse_x;			// dialog rect에서의 mouse x
	int				m_mouse_y;			// dialog rect에서의 mouse y
	LIST_LEVEL		m_selected_level; // mouse pointer가 위치하면 set.
	NODE_NUM			m_selected_node;	// mouse pointer가 위치하면 set.
	UINT				m_print_count;
	S_SURFACEINFO	m_dest_surface;

	void ShowTree(TREE_LIST *);

public:
	void SetNoClickState(bool state);
	S_NODE * GetClickNode();
	void ClearAll();
	UNIQUE_ID GetClickNodeUniqueID();
	TREE_LIST * GetRootTreeList() const;

	bool SetAppMouseControl(void (*AppMouseControl)(UINT, int, int, C_TREE_CONTROL *));
	bool SetUniqueID_receiver(void (*fp_uniqueID_receiver)(UNIQUE_ID));
	void IncreaseSrcRy(int plus_y);
	void IncreaseSrcRx(int plus_x);
	void SetSrcRy(UINT new_ry);
	void SetSrcRx(UINT new_rx);
	UINT Get_X_AmountToScroll() const;
	UINT Get_Y_AmountToScroll() const;
	UINT Get_Y_AmountForScroll() const;
	UINT Get_X_AmountForScroll() const;
	void SetSize();
	void MouseControl(UINT message, int x, int y);
	void KeyboardControl(UINT message, UINT key);
	void Show();

	C_TREE_CONTROL();
	~C_TREE_CONTROL();
};

#endif
