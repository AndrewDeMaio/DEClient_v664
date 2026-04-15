#ifndef __PICINFO_H__
#define __PICINFO_H__

/*-----------------------------------------------------------------------------
  Picture file info
-----------------------------------------------------------------------------*/
typedef struct
{
	int		width;
	int		height;
	int		bpp;        // bit per pixel

	std::string	p_data;    // pointer to a real image data uncompressed
	std::string	filename;  // loaded filename included file extension name

} S_PICINFO;

#endif