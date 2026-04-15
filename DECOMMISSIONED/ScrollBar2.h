/*-----------------------------------------------------------------------------

	scrollbar2.h

	Upgrade된 scrollbar.
	`Outputbox를 사용하지 않는 방법이 새롭게 고안되어 그것에 맞춰 scrollbar도
	 새롭게 탄생한다. scrollbar2는 완전히 독립된 객체이며, 타 Object를 몰라도
	 된다. scrollbar에 정보를 설정하면 scrollbar를 움직일 때 변화값을 얻을 수
	 있다.

	19991223. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __SCROLLBAR2__
#define __SCROLLBAR2__

#include "dialog_base.h"

/*-----------------------------------------------------------------------------
  Scrolling 하기 위해 필요한 정보를 저장하는 구조체
-----------------------------------------------------------------------------*/
struct S_INFO_SCROLL
{
	int		start_postion; // x or y
	int		length; // width or height
	int		last_position; // x or y
};

/*-----------------------------------------------------------------------------
  Scrolling된 결과를 저장하는 구조체
-----------------------------------------------------------------------------*/
struct S_RESULT_SCROLL
{
	UINT		amount_to_scroll; // pixel단위
};

/*-----------------------------------------------------------------------------
  S_SCROLLBARCS (Scroll Bar Coordinates System)
  `스크롤바 입력 반응 구조체.
  `자세한 것은 Window coordinates system을 참조하라.   
-----------------------------------------------------------------------------*/
typedef struct
{
   WINDOWHANDLE   any_windowhandle_pushed;
   WINDOWHANDLE   any_windowhandle_indicated;
   bool           is_in_tag;
   bool           is_in_track;
   bool           is_in_button1; // 수직일 때는 up, 수평일 때는 left
   bool           is_in_button2; // 수직일 때는 down, 수평일 때는 right
   bool           bl_push_tag;
   bool           bl_push_track;
   bool           bl_push_button1;
   bool           bl_push_button2;

} S_SCROLLBAR_CS2;

/*-----------------------------------------------------------------------------
  C_SCROLLBAR
-----------------------------------------------------------------------------*/
class C_SCROLLBAR2 : public C_DIALOG
{
private:
	//
	// m_S_result_scroll
	// `scrolling 하거나 버튼을 누르면 변경된다. 새로운 값으로 계속 바뀐다.
	//  
	S_RESULT_SCROLL	m_S_result_scroll;

	//
	//	m_S_info_scroll
	// `scrolling 하기 위해 알아야 할 정보이다. 이것은 scroll bar가 생성되면서
	//	 설정될 수도 있고 나중에 변경될 수도 있다. 나중에 변경되는 경우는 
	//	 Window resize로 인해 Window 크기가 변경될 때 등이다. scroll bar는
	//	 계속 이 값을 확인해 scroll bar 상태를 변경한다(show할 때...).
	//
	S_INFO_SCROLL		m_S_info_scroll;

	//
	// m_fp_result_receiver
	// `m_S_result_scroll값이 변경되면 실행한다.
	//
	void	(*m_fp_result_receiver)(const S_RESULT_SCROLL &);

	int	ConvertABS_X_ToR(int abs_x);
	int	ConvertABS_Y_ToR(int abs_y);
	UINT	TransformY(UINT y) const;
   UINT	TransformX(UINT x) const;
	bool	Test_Button2_Coordinates(int mx, int my) const;
	bool	Test_Button1_Coordinates(int mx, int my) const;
   bool	Test_Tag_Coordinates(int mx, int my) const;
	bool	Test_Track_Coordinates(int mx, int my) const;
	void	SetScrollInfo();

   E_BAR_TYPE        m_bar_type;
   bool              m_bl_active; // 활성? 비활성?
   bool              m_bl_button2_stop;

   //
   // 트랙 길이 (Track length)
   // `트랙은 Tag가 이동하는 길이다.
   //
   int               m_track_length;
   int               m_free_track_len; // track - m_tag_length
   int               m_tag_length;
   int               m_tag_pos; // tag position
   //
   // 스크롤 할 양 (amount for scroll)
   // `(트랙길이) - (스크롤 할 양) = Tag 길이
   //
   UINT              m_amount_for_scroll;
   //
   // 스크롤 한 양 (amount to scroll)
   // `IF (m_amount_to_scroll == m_amount_for_scroll) -> 끝까지 스크롤 하였다.
   // `IF (m_amount_to_scroll == 0) -> 스크롤 하지 않았다.
   //
   //UINT              m_amount_to_scroll;

   // 몇 pixel 씩 이동하는가? (default = 1)
   int               m_move_pixel;

public:
	void		SetStartPosition(int start_position);
	void		SetLength(int length);
	bool		SetLastPosition(int last_position);
	UINT		GetAmountForScroll() const;
	bool		SetResultReceiver(void (*fp_result_receiver)(const S_RESULT_SCROLL &));
	void		SetInfoToScroll(S_INFO_SCROLL &pS_info_scroll);

	void		SetMovePixel(int newpixel);
   static	S_SCROLLBAR_CS2 S_scrollbar_cs; // this is public
	void		SetBarType(E_BAR_TYPE new_bar_type) { m_bar_type = new_bar_type; }
	void		SetSize();
	void		Show();
	void		MouseControl(UINT message, int x, int y);
	void		KeyboardControl(UINT message, UINT key);

	E_BAR_TYPE GetBarType() const { return m_bar_type; }

	C_SCROLLBAR2();
   ~C_SCROLLBAR2();
};

#endif