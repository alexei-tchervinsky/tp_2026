#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "point.h"

class Shape
{
public:
  virtual ~Shape() {}
  virtual double getArea() const = 0;
  virtual Point getCenter() const  = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double koef) = 0;
  virtual std::string getName() const = 0;
  virtual void print() const = 0;
};



#endif
