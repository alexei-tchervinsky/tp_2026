#ifndef FRAME_RECTANGLE_HPP
#define FRAME_RECTANGLE_HPP
#include "Point.hpp"

class FrameRectangle
{
public:
	const double WIDTH{0};
	const double HEIGHT{0};
	Point pos_{0, 0};
	FrameRectangle(const double &w, const double &h, const Point &pos) : WIDTH(w), HEIGHT(h) { pos_ = pos; }
};

#endif
