#include "geometry.hpp"
#include <numeric>
#include <cmath>
#include <algorithm>

double getArea(const Polygon &poly)
{
  if (poly.points.size() < 3)
    return 0.0;
  double area = 0.0;
  size_t n = poly.points.size();
  const Point *base = poly.points.data();

  area = std::accumulate(poly.points.begin(), poly.points.end(), 0.0,
                         [&poly, n, base](double sum, const Point &p)
                         {
                      size_t idx = &p - base;
                      size_t next_idx = (idx + 1) % n;
                      return sum +
                          (poly.points[idx].x * poly.points[next_idx].y) -
                          (poly.points[next_idx].x * poly.points[idx].y);
                         });

  return std::abs(area) / 2.0;
}

bool isPointInsidePolygon(Point p, const Polygon &poly)
{
  size_t n = poly.points.size();
  bool inside = false;

  const Point *base = poly.points.data();
  std::for_each(poly.points.begin(), poly.points.end(),
                [&](const Point &current)
                {
        size_t i = &current - base;
        Point next = poly.points[(i + 1) % n];

        if (((current.y > p.y) != (next.y > p.y)) &&
            (p.x < (next.x - current.x) * (p.y - current.y) /
            (double)(next.y - current.y) + current.x))
        {
            inside = !inside;
        } });

  return inside;
}

bool isIntersectingPolygons(const Polygon &p1, const Polygon &p2)
{
  size_t n1 = p1.points.size();
  size_t n2 = p2.points.size();
  const Point *base1 = p1.points.data();
  const Point *base2 = p2.points.data();

  // 1. Проверяем пересечение границ
  bool boundary_intersection = std::any_of(p1.points.begin(),
                                           p1.points.end(),
                                           [&](const Point &a)
                                           {
        size_t i = &a - base1;
        Point b = p1.points[(i + 1) % n1];

        return std::any_of(p2.points.begin(), p2.points.end(),
                           [&](const Point& c)
        {
            size_t j = &c - base2;
            Point d = p2.points[(j + 1) % n2];
            return isIntersectingSegments(a, b, c, d);
        }); });

  if (boundary_intersection)
    return true;

  if (!p1.points.empty() && isPointInsidePolygon(p1.points[0], p2))
    return true;
  if (!p2.points.empty() && isPointInsidePolygon(p2.points[0], p1))
    return true;

  return false;
}
