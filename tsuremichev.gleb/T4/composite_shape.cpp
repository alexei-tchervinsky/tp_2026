#include "composite_shape.h"
#include <iostream>
#include <limits>

double CompositeShape::getArea() const
{
  double area = 0.0;
  for (auto &shape : shapes_)
  {
    area += shape->getArea();
  }
  return area;
}

Point CompositeShape::getCenter() const
{
  double minX = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double minY = minX;
  double maxY = maxX;

  for (const auto& shape : shapes_)
  {
    Point center = shape->getCenter();
    minX = std::min(minX, center.x_);
    maxX = std::max(maxX, center.x_);
    minY = std::min(minY, center.y_);
    maxY = std::max(maxY, center.y_);
  }

  return {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
}


void CompositeShape::move(double dx, double dy)
{
  for (const auto &shape : shapes_)
  {
    shape->move(dx, dy);
  }
}

void CompositeShape::scale(double koef)
{
  if (shapes_.empty())
  {
    return;
  }

  Point commonCenter = getCenter();

  for (auto &shape : shapes_) {
    Point oldShapeCenter = shape->getCenter();
    shape->scale(koef);
    double dx = (oldShapeCenter.x_ - commonCenter.x_) * (koef - 1.0);
    double dy = (oldShapeCenter.y_ - commonCenter.y_) * (koef - 1.0);
    shape->move(dx, dy);
  }
}


std::string CompositeShape::getName() const
{
  return "COMPOSITE";
}

void CompositeShape::print() const
{
  std::cout << "[" << getName() << ", (" << getCenter().x_ << ", " << getCenter().y_ << "), " << getArea() << ":\n";

  for (const auto &shape : shapes_)
  {
    std::cout << "  ";
    shape->print();
  }
  std::cout << "]\n";
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
  if (!shape) return;
  shapes_.push_back(std::move(shape));
}
