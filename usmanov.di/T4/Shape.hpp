#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "FrameRectangle.hpp"

class Shape {
public:
    virtual float getArea() const = 0;
    virtual FrameRectangle getFrameRectangle() const = 0;
    virtual void move(const Point&) = 0;
    virtual void move(float, float) = 0;
    virtual void scale(float) = 0;
    virtual Shape* clone() const = 0;
    virtual const char* getName() const = 0;
    virtual ~Shape() {}
};

void printShapeInfo(Shape& shape);

#endif      