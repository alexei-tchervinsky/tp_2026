#include "circle.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

Circle::Circle(Point center, double radius):
    center_(center), radius_(radius)
{}

double Circle::getArea() const{
  const double pi = std::acos(-1.0);
  return  pi * radius_ * radius_;
}

Point Circle::getCenter() const{
  return center_;
}

void Circle::move(double dx, double dy){
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(double coefficient){
  radius_ *= coefficient;
}

std::string Circle::getName() const{
  return "CIRCLE";
}

void Circle::print() const{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "[" << getName() << ", (" << center_.x << ", " << center_.y
            << "), " << getArea() << "]" << std::endl;
}
