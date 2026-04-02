// CImm.h - Stub implementation
//
// Logitech iFeel haptic mouse support has been removed.
// IFC22.lib (Immersion Foundation Classes SDK, c.2000) is x86-only and
// cannot be linked in an x64 build. The hardware has been discontinued.
// All methods are no-ops so call sites compile unchanged.

#ifndef __IFC_H__
#define __IFC_H__

class CImm
{
public:
	enum FORCE_UI_ID
	{
		FORCE_UI_DRAG,
		FORCE_UI_WINDOW,
		FORCE_UI_BUTTON,
		FORCE_UI_GRID,

		FORCE_UI_MAX,
	};

public:
	CImm()  {}
	~CImm() {}

	void Enable()   {}
	void Disable()  {}
	bool IsDevice() { return false; }

	void ForceUI(const unsigned int /*ID*/) const         {}
	void ForceAction(const int /*sound_id*/) const        {}
	void ForceSkill(const int /*sound_id*/) const         {}
	void ForceInventory(const int /*sound_id*/) const     {}
	void ForceUseItem(const int /*sound_id*/) const       {}
};

extern CImm *gpC_Imm;
extern HWND g_hWnd;

#endif
