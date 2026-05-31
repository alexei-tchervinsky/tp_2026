#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "point.hpp"
#include "shape.hpp"
#include <string>
class Circle : public Shape
{
private:
  Point center;
  double radius;

public:
  Circle(Point center, double radius);
  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  std::string getName() const override;
  Point getMinPoint() const override;
  Point getMaxPoint() const override;
};
#endif
