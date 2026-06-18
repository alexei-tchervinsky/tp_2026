#include "square.h"
#include <iostream>

Square::Square(Point lowerLeft, double side)
: leftBottom_(lowerLeft), side_ (side) {}

double Square::getArea() const
{
  return (side_ * side_);
}

Point Square::getCenter() const
{
  Point centre;
  double cx = leftBottom_.x_ + (side_ / 2.0);
  double cy = leftBottom_.y_ + (side_ / 2.0);
  centre.x_ = cx;
  centre.y_ = cy;
  return centre;
}

void Square::move(double dx, double dy)
{
  leftBottom_.x_ += dx;
  leftBottom_.y_ += dy;
}

void Square::scale(double koef)
{

  leftBottom_.x_ -= side_ / koef;
  leftBottom_.y_ -= side_ / koef;
  side_ *= koef;
}

std::string Square::getName() const
{
  return "SQUARE";
}

void Square::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}

