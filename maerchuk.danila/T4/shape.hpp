#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "framerectangle.hpp"
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual float getArea() const = 0;
    virtual FrameRectangle getFrameRectangle() const = 0;
    virtual void move(const Point& newPos) = 0;
    virtual void move(float dx, float dy) = 0;
    virtual Shape* clone() const = 0;
    virtual std::string getName() const = 0;
};

#endif
