/*-----------------------------------------------------------------------------

	UI_macro.h

	2000.2.28. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __UI_MACRO_H__
#define __UI_MACRO_H__

#define __BEGIN_UI_CLIENT_UPDATE(wid) 	S_SURFACEINFO	update_surface; \
													int				c_gap_x, c_gap_y; \
													if (!gC_ui.GetClientSurfaceInfo(wid, &update_surface, &c_gap_x, &c_gap_y)) \
														return; \

#define __END_UI_CLIENT_UPDATE(wid)		gC_ui.ReleaseClientSurfaceInfo(wid);

#endif