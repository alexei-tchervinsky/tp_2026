#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "point.hpp"
#include "shape.hpp"
#include <string>
class Rectangle : public Shape
{
private:
  Point leftBottom;
  Point rightTop;

public:
  Rectangle(Point lb, Point rt);
  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  std::string getName() const override;
  Point getMinPoint() const override;
  Point getMaxPoint() const override;
};
#endif
