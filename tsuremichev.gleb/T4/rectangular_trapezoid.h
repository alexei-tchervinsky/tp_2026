#ifndef RECTANGULAR_TRAPEZOID_H
#define RECTANGULAR_TRAPEZOID_H
#include "point.h"
#include "shape.h"


class RectangularTrapezoid: public Shape
{
public:
  // Constructor
  RectangularTrapezoid(Point leftBottom, double lowBase, double topBase, double height);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  virtual void print() const override;

private:
  Point leftBottom_;
  double lowBase_;
  double topBase_;
  double height_;
};


#endif
