#include "Polygon.hpp"
#include <limits>
#include <numeric>
#include <algorithm>
#include <cmath>

std::istream &operator>>(std::istream &in, Point &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  char open = 0;
  char ch = 0;
  char close = 0;
  int tx = 0;
  int ty = 0;

  if (in >> open && open == '(' && in >> tx && in >> ch && ch == ';' && in >> ty && in >> close && close == ')')
  {
    dest.x = tx;
    dest.y = ty;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  size_t numPoints = 0;
  if (!(in >> numPoints) || numPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector<Point> tempPoints;
  tempPoints.reserve(numPoints);

  for (size_t i = 0; i < numPoints; ++i)
  {
    Point p;
    if (in >> p)
    {
      tempPoints.push_back(p);
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  dest.points = std::move(tempPoints);
  return in;
}

double getArea(const Polygon &poly)
{
  if (poly.points.size() < 3)
    return 0.0;
  auto indices = std::vector<size_t>(poly.points.size());
  std::iota(indices.begin(), indices.end(), 0);
  double sum = std::accumulate(
      indices.begin(),
      indices.end(),
      0.0,
      [&](double acc, size_t i)
      {
        size_t next = (i + 1) % poly.points.size();
        return acc + (poly.points[i].x * poly.points[next].y) -
               (poly.points[next].x * poly.points[i].y);
      });
  return std::abs(sum) / 2.0;
}

bool isPointsEqual(const Point &a, const Point &b)
{
  return a.x == b.x && a.y == b.y;
}

bool isPolygonEqual(const Polygon &a, const Polygon &b)
{
  if (a.points.size() != b.points.size())
    return false;
  return std::equal(
      a.points.begin(),
      a.points.end(),
      b.points.begin(),
      isPointsEqual);
}

Frame getCollectionFrame(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    return { {0, 0}, {0, 0} };
  }

  const int inf = std::numeric_limits<int>::max();
  int minX = inf, minY = inf;
  int maxX = -inf, maxY = -inf;
  bool hasPoints = false;

  for (const auto& poly : polygons)
  {
    for (const auto& p : poly.points)
    {
      if (p.x < minX) minX = p.x;
      if (p.y < minY) minY = p.y;
      if (p.x > maxX) maxX = p.x;
      if (p.y > maxY) maxY = p.y;
      hasPoints = true;
    }
  }

  if (!hasPoints) return { {0, 0}, {0, 0} };
  return { {minX, minY}, {maxX, maxY} };
}


bool isPolygonInFrame(const Polygon &poly, const Frame &frame)
{
  return std::all_of(poly.points.begin(), poly.points.end(), [&frame](const Point &p)
                     { return p.x >= frame.minPoint.x && p.x <= frame.maxPoint.x &&
                              p.y >= frame.minPoint.y && p.y <= frame.maxPoint.y; });
}
