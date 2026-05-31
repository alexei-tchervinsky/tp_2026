#ifndef TP_2026_SHAPE_H
#define TP_2026_SHAPE_H

#include <string>
#include "point.h"

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
};

#endif
