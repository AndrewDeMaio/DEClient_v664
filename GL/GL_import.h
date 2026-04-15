#ifndef __GL_IMPORT__
#define __GL_IMPORT__

#include "2D.h"
#include "picinfo.h"
#include "TGA.h"
#include "IMG.h"
#include "BasicData.h"

DllClass void FillRect(S_SURFACEINFO *info, Rect * rect, int color);
extern DllClass void (*filledRect)(S_SURFACEINFO *, S_RECT *, int);
extern DllClass void (*cls)(S_SURFACEINFO *, int);
extern DllClass void (*putPixel)(S_SURFACEINFO *, int, int, int); // putPixel function pointer
extern DllClass int (*getPixel)(S_SURFACEINFO *, int, int); // getPixel ...
extern DllClass void (*vertline)(S_SURFACEINFO *, int, int, int, int, int); // vertline ...
extern DllClass void (*horzline)(S_SURFACEINFO *, int, int, int, int, int); // horzline ...

extern DllClass void (*Bltz)(const S_SURFACEINFO *,
                  const S_SURFACEINFO *,
                  const S_RECT *,
                  const S_RECT *); // copy_2D_Space fp

extern DllClass void (*CkBltz)(const S_SURFACEINFO *,
                  const S_SURFACEINFO *,
                  const S_RECT *,
                  const S_RECT *,
				  const int); // copy_2D_Space_colorkey fp

DllClass void	SetSurfaceInfo(S_SURFACEINFO *surface_info, const DDSURFACEDESC2 *p_ddsd);
DllClass void	SetSurfaceInfo(S_SURFACEINFO *surface_info, const DDSURFACEDESC *p_ddsd);
DllClass void	SetSurfaceInfo(S_SURFACEINFO &surface_info, void *p_surface, int w, int h, int pitch=0);
DllClass void	SetRect(S_RECT &rect, int x, int y, int w, int h);
DllClass int	Get_ColorkeyColor(S_PICINFO *picinfo);
DllClass int	Get_ColorkeyColor(S_SURFACEINFO *surfaceinfo);
DllClass DWORD  GL_RGB(DWORD r, DWORD g, DWORD b);
DllClass void	InitializeGL(int bpp, int r_bit, int g_bit, int b_bit);
DllClass int	Convert24RGBto16(int R, int G, int B);
DllClass void	rectangle(S_SURFACEINFO *, int lx, int ly, int rx, int ry, int color);
DllClass void   rectangle(S_SURFACEINFO * info, Rect * p_rect, int color);
DllClass void	line(S_SURFACEINFO *, int x1, int y1, int x2, int y2, int color);
DllClass void	TransparentBlt16(S_SURFACEINFO *dest_surface_info,
								S_SURFACEINFO *src_surface_info,
								S_RECT *dest_rect,
								S_RECT *src_rect);

DllClass int	getPixel16(S_SURFACEINFO *info, int x, int y); // utility

DllClass bool	TestTga(const char * filename);
DllClass bool   GetTgaPicInfo(const char * sz_filename, S_PICINFO &picinfo);

#endif
