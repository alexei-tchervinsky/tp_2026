#include "square.hpp"

#include <stdexcept>

Square::Square(const Point & leftBottom, double side):
  leftBottom_(leftBottom),
  side_(side)
{
  if (side <= 0.0)
  {
    throw std::invalid_argument("Square side must be positive");
  }
}

double Square::getArea() const
{
  return side_ * side_;
}

Point Square::getCenter() const
{
  return Point{
    leftBottom_.x + side_ / 2.0,
    leftBottom_.y + side_ / 2.0
  };
}

void Square::move(double dx, double dy)
{
  leftBottom_.x += dx;
  leftBottom_.y += dy;
}

void Square::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }

  const Point center = getCenter();
  side_ *= factor;
  leftBottom_.x = center.x - side_ / 2.0;
  leftBottom_.y = center.y - side_ / 2.0;
}

const char * Square::getName() const
{
  return "SQUARE";
}
