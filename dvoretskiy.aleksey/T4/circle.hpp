#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

class Circle final : public Shape
{
public:
  Circle(const Point & center, double radius);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  const char * getName() const override;

private:
  Point center_;
  double radius_;
};

#endif
