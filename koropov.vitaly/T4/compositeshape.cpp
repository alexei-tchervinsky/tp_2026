#include "compositeshape.hpp"
CompositeShape::CompositeShape()
{
}
Point CompositeShape::getMinPoint() const
{
  Point min = shapes[0]->getMinPoint();
  double minX = min.x;
  double minY = min.y;
  for (const auto &shape : shapes)
  {
    Point shapeMin = shape->getMinPoint();
    if (shapeMin.x < minX)
    {
      minX = shapeMin.x;
    }
    if (shapeMin.y < minY)
    {
      minY = shapeMin.y;
    }
  }
  Point result;
  result.x = minX;
  result.y = minY;
  return result;
}
Point CompositeShape::getMaxPoint() const
{
  Point max = shapes[0]->getMaxPoint();
  double maxX = max.x;
  double maxY = max.y;
  for (const auto &shape : shapes)
  {
    Point shapeMax = shape->getMaxPoint();
    if (shapeMax.x > maxX)
    {
      maxX = shapeMax.x;
    }
    if (shapeMax.y > maxY)
    {
      maxY = shapeMax.y;
    }
  }
  Point result;
  result.x = maxX;
  result.y = maxY;

  return result;
}
double CompositeShape::getArea() const
{
  double total = 0;
  for (const auto &shape : shapes)
  {
    total += shape->getArea();
  }
  return total;
}
void CompositeShape::addShape(std::shared_ptr<Shape> shape)
{
  shapes.push_back(shape);
}
void CompositeShape::move(double dx, double dy)
{
  for (const auto &shape : shapes)
  {
    shape->move(dx, dy);
  }
}
Point CompositeShape::getCenter() const
{
  Point min = shapes[0]->getMinPoint();
  Point max = shapes[0]->getMaxPoint();
  double minX = min.x;
  double minY = min.y;
  double maxX = max.x;
  double maxY = max.y;
  for (const auto &shape : shapes)
  {
    Point shapeMin = shape->getMinPoint();
    Point shapeMax = shape->getMaxPoint();
    if (shapeMin.x < minX)
    {
      minX = shapeMin.x;
    }
    if (shapeMin.y < minY)
    {
      minY = shapeMin.y;
    }
    if (shapeMax.x > maxX)
    {
      maxX = shapeMax.x;
    }
    if (shapeMax.y > maxY)
    {
      maxY = shapeMax.y;
    }
  }
  Point center;
  center.x = (minX + maxX) / 2;
  center.y = (minY + maxY) / 2;
  return center;
}
void CompositeShape::scale(double factor)
{
  Point globalCenter = getCenter();
  for (const auto &shape : shapes)
  {
    Point shapeCenter = shape->getCenter();
    double newX = globalCenter.x + (shapeCenter.x - globalCenter.x) * factor;
    double newY = globalCenter.y + (shapeCenter.y - globalCenter.y) * factor;
    double dx = newX - shapeCenter.x;
    double dy = newY - shapeCenter.y;
    shape->move(dx, dy);
    shape->scale(factor);
  }
}
std::string CompositeShape::getName() const
{
  return "COMPOSITE_SHAPE";
}
