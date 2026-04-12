#include "circle.h"
#include <iostream>

Circle::Circle(Point center, double radius)
: center_(center), radius_ (radius) {}

double Circle::getArea() const
{
  return (3.14 * radius_ * radius_);

}

Point Circle::getCenter() const
{
  return center_;
}

void Circle::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Circle::scale(double koef)
{
  radius_ *= koef;
}

std::string Circle::getName() const
{
  return "CIRCLE";
}

void Circle::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}
