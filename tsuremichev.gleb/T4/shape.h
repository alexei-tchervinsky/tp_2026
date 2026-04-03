#ifndef SHAPE_H
#define SHAPE_H
#include <string>

class Shape()
{
  virtual ~Shape() {}
  virtual double getArea() const = 0;
  virtual double getCentre() const  = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double koef) = 0;
  virtual std::string getName() const = 0;
}



#endif
