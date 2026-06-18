#include "ring.h"
#include <iostream>


Ring::Ring(Point center, double bigRadius, double smallRadius)
: center_(center), bigRadius_ (bigRadius), smallRadius_ (smallRadius) {}

double Ring::getArea() const
{
  return (3.14 * bigRadius_ * bigRadius_) - (3.14 * smallRadius_ * smallRadius_);
}

Point Ring::getCenter() const
{
  return center_;
}

void Ring::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Ring::scale(double koef)
{
  bigRadius_ *= koef;
  smallRadius_ *= koef;
}

std::string Ring::getName() const
{
  return "RING";
}


void Ring::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}
