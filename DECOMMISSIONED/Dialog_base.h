/*-----------------------------------------------------------------------------

	dialog_base.h

	Dialog base class.

	1999.8.20. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __DIALOG_BASE_H__
#define __DIALOG_BASE_H__

#include "UI_typedef.h"
#include "GL_import.h"

/*-----------------------------------------------------------------------------
- E_DIALOG_ID
- 대화상자 id
-----------------------------------------------------------------------------*/
typedef enum
{
   NOT_DID,
	ID_TEXTBUTTON,		// 1
	ID_RADIOBUTTON,	// 2
	ID_CHECKBOX,		// 3
	ID_LISTBOX,			// 4
	ID_OUTPUTBOX,		// 5
	ID_EDITBOX,			// 6
	ID_SPINBOX,			// 7
	ID_SCROLLBAR,		// 8
	ID_SCROLLBAR2,		// 8+
	ID_SINGLEMENU,		// 9
	ID_PULLDOWNMENU,	// 10
	ID_TREE_CONTROL,	// 11
	ID_ICON_CONTROL,	// 12
	ID_COMBOBOX,		// 13
	ID_STATICTEXT,		// 14

} E_DIALOG_ID;

/*-----------------------------------------------------------------------------
  S_DIALOG_POINTER - (USER DATA)

  Dialog pointer
  `대화상자를 만들 때 필요한 것.
  `대화상자의 구성요소를 생성하기 위해서 이것은 대화상자 지시자로써 사용된다.
-----------------------------------------------------------------------------*/
typedef struct
{
   E_DIALOG_ID did; // !중요
   HANDLEID    hid;

} S_DIALOG_POINTER;

/*-----------------------------------------------------------------------------
  E_BAR_TYPE - (USER DATA)

  `수직바, 수평바 정의 (for Scroll bar)

  `C_SCROLLBAR에 있어야 하지만, 현재 C_SCROLLBAR2가 생겨서 여기다 둠.
-----------------------------------------------------------------------------*/
typedef enum
{
   VERTICAL_BAR = 1,
   HORIZONTAL_BAR,

} E_BAR_TYPE;


class C_WINDOW;

class C_DIALOG
{
protected:
	int               m_x, m_y;
	int	            m_w, m_h;
	C_WINDOW	*			m_pC_window;       // pointer to window

public:
	C_DIALOG();
	~C_DIALOG();

	virtual void MouseControl(UINT message, int x, int y) = 0; // pure!
	virtual void KeyboardControl(UINT message, UINT key) = 0; // pure
	virtual void Show() = 0; // pure!

   C_WINDOW *	GetWindowHandle() const { return m_pC_window; }
   void			SetWindowHandle(C_WINDOW *whandle) { m_pC_window = whandle; }
   void			GetDialogRect(S_RECT *S_rect) const;
   void			ShowDialogRect();
};

#endif