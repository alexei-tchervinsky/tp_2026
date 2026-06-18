#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
#include "shape.h"


class Circle: public Shape
{
public:
  // Constructor
  Circle(Point center, double radius);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  void print() const override;


private:
  Point center_;
  double radius_;
};


#endif
