#include "ellips.h"
#include <iostream>

Ellips::Ellips(Point center, double vertRadius, double horizRadius)
: center_(center), vertRadius_ (vertRadius), horizRadius_ (horizRadius) {}

double Ellips::getArea() const
{
  return (3.14 * vertRadius_ * horizRadius_);
}

Point Ellips::getCenter() const
{
  return center_;
}

void Ellips::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Ellips::scale(double koef)
{
  vertRadius_ *= koef;
  horizRadius_ *= koef;
}

std::string Ellips::getName() const
{
  return "ELLIPS";
}

void Ellips::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}

