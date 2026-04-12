#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "point.h"
#include "shape.h"


class Rhombus: public Shape
{
public:
  // Constructor
  Rhombus(Point center, double vertDiagonal, double horizDiagonal);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  virtual void print() const override;

private:
  Point center_;
  double vertDiagonal_;
  double horizDiagonal_;
};


#endif
