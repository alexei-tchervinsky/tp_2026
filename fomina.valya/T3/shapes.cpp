#include "shapes.hpp"
#include <algorithm>

bool operator==(const Point &a, const Point &b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon &a, const Polygon &b)
{
  if (a.points.size() != b.points.size())
    return false;
  return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}

std::istream &operator>>(std::istream &in, Point &p)
{
  char c1 = 0, c2 = 0, c3 = 0;

  if (!(in >> c1) || c1 != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  if (!(in >> p.x))
  {
    return in;
  }
  if (!(in >> c2) || c2 != ';')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  if (!(in >> p.y))
  {
    return in;
  }
  if (!(in >> c3) || c3 != ')')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  return in;
}

std::istream &operator>>(std::istream &in, Polygon &poly)
{
  size_t num = 0;
  if (!(in >> num))
    return in;

  if (num < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  poly.points.resize(num);

  for (size_t i = 0; i < num; ++i)
  {
    if (!(in >> poly.points[i]))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  return in;
}
