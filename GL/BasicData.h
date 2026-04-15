/*-----------------------------------------------------------------------------

	BasicData.h

	Basic data class.

	2000.7.29. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __BASICDATA_H__
#define __BASICDATA_H__

//----------------------------------------------------------------------------
// Class Point
//----------------------------------------------------------------------------
class Point
{
public:
	int		x, y; // public member, no m_ prefix.

	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() : x(0), y(0) {}
	~Point() {}

	void	Set(int _x, int _y) { x = _x; y = _y; }
	void	operator=(int val)  { x = val; y = val; }
};

//----------------------------------------------------------------------------
// Class Rect
//----------------------------------------------------------------------------
class Rect
{
public:
	int		x, y, w, h; // public member, no m_ prefix.

	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
	Rect() : x(0), y(0), w(0), h(0) {}
	~Rect() {}

	void	XY(int _x, int _y)               { x = _x; y = _y; }
	void	WH(int _w, int _h)               { w = _w; h = _h; }
	void	Set(int _x, int _y, int _w, int _h) { x = _x; y = _y; w = _w; h = _h; }
	void	operator=(int val)               { x = val; y = val; w = val; h = val; }
	void	operator=(Point &point)          { x = point.x; y = point.y; }
	void	operator+=(Point &point)         { x += point.x; y += point.y; }

	bool	IsInRect(int _x, int _y) const         { return _x >= x && _x < x + w && _y >= y && _y < y + h; }
	bool	IsInRect(const Point &point) const      { return IsInRect(point.x, point.y); }

	int	Left()  const { return x; }
	int	Right() const { return x + w; }
	int	Up()    const { return y; }
	int	Down()  const { return y + h; }
};

#endif