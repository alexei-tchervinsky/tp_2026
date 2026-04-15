#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "Point.hpp"
#include "FrameRectangle.hpp"
#include <string>

class Shape
{
public:
	virtual ~Shape() {}
	virtual double getArea() = 0;
	virtual FrameRectangle getFrameRectangle() = 0;
	virtual void move(const double k) = 0;
	virtual void move(const double x, const double y) = 0;
	virtual void scale(const double k) = 0;
	virtual Shape *clone() = 0;
	virtual std::string getName() const = 0;
};
#endif
