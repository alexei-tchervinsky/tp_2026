#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "point.h"
#include "shape.h"


class Rectangle: public Shape
{
public:
  // Constructor
  Rectangle(Point lowerLeft, Point upperRight);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  virtual void print() const override;


private:
  Point leftBottom_;
  Point rightTop_;
};


#endif
