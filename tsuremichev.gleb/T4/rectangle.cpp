#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(Point lowerLeft, Point upperRight)
: leftBottom_(lowerLeft), rightTop_ (upperRight) {}

double Rectangle::getArea() const
{
  double height = (rightTop_.y_ - leftBottom_.y_);
  double width = (rightTop_.x_ - leftBottom_.x_);
  return (height * width);
}

Point Rectangle::getCenter() const
{
  Point centre;
  double cx = (leftBottom_.x_ + rightTop_.x_) / 2.0;
  double cy = (leftBottom_.y_ + rightTop_.y_) / 2.0;
  centre.x_ = cx;
  centre.y_ = cy;
  return centre;
}

void Rectangle::move(double dx, double dy)
{
  leftBottom_.x_ += dx;
  leftBottom_.y_ += dy;
  rightTop_.x_ += dx;
  rightTop_.y_ += dy;
}

void Rectangle::scale(double koef)
{
  Point center = getCenter();

  double halfHeight = (rightTop_.y_ - leftBottom_.y_) * koef / 2.0;
  double halfWidth = (rightTop_.x_ - leftBottom_.x_) * koef / 2.0;

  rightTop_.x_ = center.x_ + halfWidth;
  rightTop_.y_ = center.y_ + halfHeight;

  leftBottom_.x_ = center.x_ - halfWidth;
  leftBottom_.y_ = center.y_ - halfHeight;
}

std::string Rectangle::getName() const
{
  return "RECTANGLE";
}

void Rectangle::print() const
{
  Point center = getCenter();
  double area = getArea();
  std::cout << "[" << getName()  << ", ("  << center.x_   << ", "  << center.y_  << "), "  << area  << "]\n";
}
