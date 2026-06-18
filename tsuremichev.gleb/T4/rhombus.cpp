#include "rhombus.h"
#include <iostream>


Rhombus::Rhombus(Point center, double vertDiagonal, double horizDiagonal)
: center_(center), vertDiagonal_ (vertDiagonal), horizDiagonal_ (horizDiagonal) {}

double Rhombus::getArea() const
{
  return (vertDiagonal_ * horizDiagonal_) / 2.0;
}

Point Rhombus::getCenter() const
{
  return center_;
}

void Rhombus::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Rhombus::scale(double koef)
{
  vertDiagonal_ *= koef;
  horizDiagonal_ *= koef;
}

std::string Rhombus::getName() const
{
  return "RHOMBUS";
}

void Rhombus::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}
