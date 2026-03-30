#ifndef __LISTBOX__
#define __LISTBOX__

#include "dialog_base.h"

/*-----------------------------------------------------------------------------
  S_LIST_ITEM
-----------------------------------------------------------------------------*/
typedef struct
{
	char	*sz_name;	// name string
	int	i_n;			// 몇 번째 항목인가를 기록하는 data
	DWORD	dw_unique_id;// unique id
	bool	bl_delete;	// sz_name을 delete[] 해주어야 하는가?

} S_LIST_ITEM;

/*-----------------------------------------------------------------------------
  C_LISTBOX
-----------------------------------------------------------------------------*/
class C_LISTBOX : public C_DIALOG
{
public:
	// event category
	// `외부에서의 list item에 대한 처리 정의이다.
	enum EVENT_CATEGORY
	{ 
		NONE,
		ITEM_EXEC,		// when double click
		ITEM_DELETE,	// for the File Service
		ITEM_COPY,		// for the File Service
		ITEM_REFRESH,
		ITEM_SELECT,	// 단순히 선택할 경우
		ITEM_BACKSPACE,// File dialog에서 backspace 하면 이전 dir로 가게 하기 위해서.
	};

private:
	void			(*m_fp_combostate_receiver)(int);
	char **		m_p_combo_list;
	int			m_i_combo_count;
	int			m_i_combo_index;
	bool			m_bl_click_primary_comment_area;

	//
	// Primary comment line scroll offset
	// `Window 크기에 따라 path를 전부 못 보여줄 수 있으므로 scroll을 시킨다. 
	//
	UINT			m_u_primary_scroll_offset;
	bool			m_bl_forward;
	int			m_i_delay;

	S_LIST_ITEM	*m_pS_item;
	UINT			m_u_item_count; // current total item count
	UINT			m_u_real_print_count;
	int			m_i_valid_h;
	void			(*m_fp_list_update)(void);
	void			(*m_fp_event_execution)(S_LIST_ITEM *pS_item_unit, EVENT_CATEGORY category);
	UINT			m_u_item_pointer;
	UINT			m_u_prev_item_pointer;
	UINT			m_u_scrolled_item_count;
	bool			m_bl_overline;

	//
	// 갱신조건
	// `list는 계속적으로 변화하기도 하지만 때로는 그렇지 않을 수 있다. 따라서 
	//  갱신조건에 맞으면 갱신한다.
	//
	bool			m_bl_refresh;

	//
	// Comment line system (Primary, Secondary)
	//
	bool			m_bl_is_primary_cl;
	bool			m_bl_is_secondary_cl;
	char			*m_sz_primary_title;
	char			*m_sz_secondary_title;

	//
	// Common list output buffer
	// `정상적인 list 출력을 위해 모든 list box dialog가 공유하는 출력버퍼를 생성한다.
	// `list는 출력결과를 저장하지 않으므로 공유버퍼를 사용한다. 먼저 이 버퍼에 출력하고
	//  이것을 list box dialog rect에 맞춰 blt한다.
	// `이 공유버퍼는 primary surface크기와 같다. 왜냐하면 그래야지만 가장 큰 list box를
	//	 출력할 수 있기 때문이다.
	//
	static void *m_p_union_buffer;
	static int	m_res_x; // size 정보를 알기 위해 member로...
	static int	m_res_y;
	static int  m_bpp;
	static int	m_background_color;

public:
	void	SetComboStateReceiver(void (*fp)(int));
	int	GetComboIndex() const;
	void	SetComboInfo(char **list, int count, int index);
	void	UpdatePathScroll();
	void	SetRefreshFlag(bool newflag);
	void	IncreaseScrolledItemCountX(int val);
	void	IncreaseScrolledItemCountY(int val);
	void	SetScrolledItemCountY(UINT newy);
	void	SetScrolledItemCountX(UINT newx);
	UINT	Get_Y_AmountToScroll() const { return m_u_scrolled_item_count; }
	UINT	Get_X_AmountToScroll() const;
	UINT	GetRealPrintCount() const { return m_u_real_print_count; }
	UINT	Get_Y_AmountForScroll();
	UINT	Get_X_AmountForScroll();
	void	ClearItemPointer() { m_u_item_pointer = 0; m_u_prev_item_pointer = 0; }
	void	SetSecondaryCLString(char *sz_str) { m_sz_secondary_title = sz_str; }
	void	SetPrimaryCLString(char *sz_str) { m_sz_primary_title = sz_str; }
	int	GetBackgroundColor() const { return m_background_color; }
	void	SetBackgroundColor(int color);
	void	ClearAllListUnit();
	void	ExecMethodToUpdate();
	bool	AddUnit(char *sz_str, DWORD unique_id, bool delete_flag);
	bool	SetListEventExecFpointer(void (*fp_list_event_exec)(S_LIST_ITEM *pS_item_unit, EVENT_CATEGORY category));
	bool	SetListUpdateFpointer(void (*fp_list_update)());
	void	SetSize();
	bool	GetPrimaryCommentLineState() const { return m_bl_is_primary_cl; }
	bool	GetSecondaryCommentLineState() const { return m_bl_is_secondary_cl; }
	void	SetSecondaryCommentLineState(bool how) { m_bl_is_secondary_cl = how; }
	void	SetPrimaryCommentLineState(bool how) { m_bl_is_primary_cl = how; }
	void	Show();
	void	MouseControl(UINT message, int mx, int my);
	void	KeyboardControl(UINT message, UINT key);

	C_LISTBOX();
	~C_LISTBOX();

private:
	void	SetRealPrintCount();
	void	ExecListEvent(EVENT_CATEGORY categoy) const;
	void	GetSelectionBarRect(S_RECT *S_rect, UINT item_num) const;
};

#endif