#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

namespace golovach {
  class Shape {
  public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual const char* getName() const = 0;
    virtual ~Shape() = default;
  };
}

#endif
