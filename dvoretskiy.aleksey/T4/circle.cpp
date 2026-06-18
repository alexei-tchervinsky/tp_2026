#include "circle.hpp"

#include <stdexcept>

namespace
{
constexpr double PI = 3.14159265358979323846;
}

Circle::Circle(const Point & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Circle radius must be positive");
  }
}

double Circle::getArea() const
{
  return PI * radius_ * radius_;
}

Point Circle::getCenter() const
{
  return center_;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }

  radius_ *= factor;
}

const char * Circle::getName() const
{
  return "CIRCLE";
}
