#include "rectangle.h"
#include <iostream>
#include <iomanip>
#include <string>

Rectangle::Rectangle(Point lowLeft, Point topRight) :
  center_({(lowLeft.x + topRight.x) / 2.0, (lowLeft.y + topRight.y) / 2.0}),
  width_(topRight.x - lowLeft.x),
  height_(topRight.y - lowLeft.y)
{}

double Rectangle::getArea() const{
  return width_ * height_;
}

Point Rectangle::getCenter() const{
  return center_;
}

void Rectangle::move(double dx, double dy){
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(double coefficient){
  width_ *= coefficient;
  height_ *= coefficient;
}

std::string Rectangle::getName() const{
  return "RECTANGLE";
}

void Rectangle::print() const{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "[" << getName() << ", (" << center_.x << ", " << center_.y
            << "), " << getArea() << "]" << std::endl;
}
