#include "rectangle.hpp"
Rectangle::Rectangle(Point lb, Point rt)
{
  leftBottom = lb;
  rightTop = rt;
}
double Rectangle::getArea() const
{
  double width = rightTop.x - leftBottom.x;
  double height = rightTop.y - leftBottom.y;
  return width * height;
}
Point Rectangle::getCenter() const
{
  Point center;
  center.x = (rightTop.x + leftBottom.x) / 2;
  center.y = (rightTop.y + leftBottom.y) / 2;
  return center;
}
void Rectangle::move(double dx, double dy)
{
  leftBottom.x += dx;
  leftBottom.y += dy;
  rightTop.x += dx;
  rightTop.y += dy;
}
void Rectangle::scale(double factor)
{
  Point center = getCenter();
  leftBottom.x = center.x + (leftBottom.x - center.x) * factor;
  leftBottom.y = center.y + (leftBottom.y - center.y) * factor;
  rightTop.x = center.x + (rightTop.x - center.x) * factor;
  rightTop.y = center.y + (rightTop.y - center.y) * factor;
}
std::string Rectangle::getName() const
{
  return "RECTANGLE";
}
Point Rectangle::getMinPoint() const
{
  return leftBottom;
}
Point Rectangle::getMaxPoint() const
{
  return rightTop;
}
