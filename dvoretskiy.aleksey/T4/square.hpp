#ifndef SQUARE_H
#define SQUARE_H

#include "shape.hpp"

class Square final : public Shape
{
public:
  Square(const Point & leftBottom, double side);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  const char * getName() const override;

private:
  Point leftBottom_;
  double side_;
};

#endif
