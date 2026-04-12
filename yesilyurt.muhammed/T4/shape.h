#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "point.h"

class Shape
{
public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;

    virtual double getLeft() const = 0;
    virtual double getRight() const = 0;
    virtual double getBottom() const = 0;
    virtual double getTop() const = 0;

    virtual ~Shape() = default;
};

#endif
