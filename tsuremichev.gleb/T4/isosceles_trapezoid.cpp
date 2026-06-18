#include "isosceles_trapezoid.h"
#include <iostream>

IsoscelesTrapezoid::IsoscelesTrapezoid(Point leftBottom, double lowBase, double topBase, double height)
: leftBottom_ (leftBottom), lowBase_ (lowBase), topBase_ (topBase), height_ (height) {}

double IsoscelesTrapezoid::getArea() const
{
  return ((lowBase_ + topBase_) / 2.0) * height_;
}

Point IsoscelesTrapezoid::getCenter() const
{
  Point center;
  center.y_ = leftBottom_.y_ + (height_ / 2.0);
  center.x_ = leftBottom_.x_ + (lowBase_ / 2.0);
  return center;
}

void IsoscelesTrapezoid::move(double dx, double dy)
{
  leftBottom_.x_ += dx;
  leftBottom_.y_ += dy;
}

void IsoscelesTrapezoid::scale(double koef)
{
  Point center = getCenter();
  lowBase_ *= koef;
  topBase_ *= koef;
  height_ *= koef;
  leftBottom_.x_ = center.x_ - lowBase_ / 2.0;
  leftBottom_.y_ = center.y_ - height_ / 2.0;
}

std::string IsoscelesTrapezoid::getName() const
{
  return "IOSCELES TRAPEZOID";
}

void IsoscelesTrapezoid::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}

