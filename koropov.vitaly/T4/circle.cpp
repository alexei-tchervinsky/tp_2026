#include "circle.hpp"
Circle::Circle(Point center, double radius)
{
  this->center = center;
  this->radius = radius;
}
double Circle::getArea() const
{
  return radius * radius * 3.1415926535;
}
Point Circle::getCenter() const
{
  return center;
}
void Circle::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}
void Circle::scale(double factor)
{
  radius *= factor;
}
std::string Circle::getName() const
{
  return "CIRCLE";
}
Point Circle::getMinPoint() const
{
  Point min;
  min.x = center.x - radius;
  min.y = center.y - radius;
  return min;
}
Point Circle::getMaxPoint() const
{
  Point max;
  max.x = center.x + radius;
  max.y = center.y + radius;
  return max;
}
