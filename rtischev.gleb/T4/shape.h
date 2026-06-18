#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "point.h"

class Shape{
public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual ~Shape() = default;
    virtual double getMinX() const = 0;
    virtual double getMaxX() const = 0;
    virtual double getMinY() const = 0;
    virtual double getMaxY() const = 0;
    virtual FrameRect getFrameRect() const = 0;
};

#endif
