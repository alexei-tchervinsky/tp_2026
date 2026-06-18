#ifndef IOSCELES_TRAPEZOID_H
#define IOSCELES_TRAPEZOID_H
#include "point.h"
#include "shape.h"


class IsoscelesTrapezoid: public Shape
{
public:
  // Constructor
  IsoscelesTrapezoid(Point leftBottom, double lowBase, double topBase, double height);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  void print() const override;


private:
  Point leftBottom_;
  double lowBase_;
  double topBase_;
  double height_;
};


#endif
