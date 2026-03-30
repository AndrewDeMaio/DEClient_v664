/*-----------------------------------------------------------------------------

	HotKeySystem.h

	Hot-key System class.

	2000.3.31. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __HOTKEYSYSTEM_H__
#define __HOTKEYSYSTEM_H__


/*-----------------------------------------------------------------------------
  Local일 경우 같은 key가 여럿 정의될 수 있는데, 그것을 구별해주기 위한
  type이다.

  hk_class_t game_window = 0, menu_window = 1
  => game_window에서의 up key는 menu_window의 up key와 다를 수 있다.
-----------------------------------------------------------------------------*/
typedef DWORD	hk_class_t;

#define HK_NO_CLASS						0

/*-----------------------------------------------------------------------------
  Class Hot-key System
-----------------------------------------------------------------------------*/
class C_HOTKEY_SYSTEM
{
public:
	enum TYPE
	{
		GLOBAL,
		LOCAL,
	};

	enum EXT_KEY
	{
		NONE,
		CTRL,
		ALT,
		SHIFT,
	};

	struct S_KEY
	{
		TYPE			type;
		hk_class_t	hk_class;
		EXT_KEY		ext_key;
		UINT			scan_code;
		void			(*fp_exec)(void);
	};

private:
	S_KEY *	m_pS_key_list;
	int		m_key_list_size;

public:
	C_HOTKEY_SYSTEM();
	~C_HOTKEY_SYSTEM();

	bool	Translate(C_HOTKEY_SYSTEM::TYPE type, hk_class_t hk_class, UINT scan_code, 
											bool ctrl=false, bool alt=false, bool shift=false);
	bool	Add(C_HOTKEY_SYSTEM::TYPE type, hk_class_t hk_class, 
								  C_HOTKEY_SYSTEM::EXT_KEY ext_key ,UINT scan_code, void (*fp_exec)(void));
	// Get...
};

#endif