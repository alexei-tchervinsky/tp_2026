#ifndef SHAPE_H
#define SHAPE_H

#include "point.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual Point getCenter() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double factor) = 0;
  virtual const char * getName() const = 0;
};

#endif
