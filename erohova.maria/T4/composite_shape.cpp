#include "composite_shape.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void CompositeShape::addShape(std::shared_ptr<Shape> shape){
  if (shape) {
    shapes_.push_back(shape);
  }
}

double CompositeShape::getArea() const{
  double totalArea = 0.0;
  for (const auto& shape : shapes_) {
    totalArea += shape->getArea();
  }
  return totalArea;
}

Point CompositeShape::getCenter() const{
  if (shapes_.empty()) {
    return {0.0, 0.0};
  }
  double minX = shapes_[0]->getCenter().x;
  double maxX = minX;
  double minY = shapes_[0]->getCenter().y;
  double maxY = minY;

  for (const auto& shape : shapes_) {
    Point c = shape->getCenter();
    minX = std::min(minX, c.x);
    maxX = std::max(maxX, c.x);
    minY = std::min(minY, c.y);
    maxY = std::max(maxY, c.y);
  }
  return {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
}

void CompositeShape::move(double dx, double dy){
  for (auto& shape : shapes_) {
    shape->move(dx, dy);
  }
}

void CompositeShape::scale(double coefficient){
  Point commonCenter = getCenter();
  for (auto& shape : shapes_) {
    Point individualCenter = shape->getCenter();
    double dx = (individualCenter.x - commonCenter.x) * (coefficient - 1.0);
    double dy = (individualCenter.y - commonCenter.y) * (coefficient - 1.0);
    shape->move(dx, dy);
    shape->scale(coefficient);
  }
}

std::string CompositeShape::getName() const{
  return "COMPOSITE";
}

void CompositeShape::print() const{
  Point c = getCenter();
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "[COMPOSITE, (" << c.x << ", " << c.y << "), " << getArea() << ":" << std::endl;
  for (const auto& shape : shapes_) {
    std::cout << "  ";
    shape->print();
  }
  std::cout << "]" << std::endl;
}
