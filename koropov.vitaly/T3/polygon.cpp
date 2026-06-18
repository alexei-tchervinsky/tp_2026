#include "polygon.hpp"
#include <numeric>
#include <cmath>
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
  char open_bracket, semicolon, close_bracket;
  if (in >> open_bracket && open_bracket == '(' &&
      in >> p.x &&
      in >> semicolon && semicolon == ';' &&
      in >> p.y &&
      in >> close_bracket && close_bracket == ')')
  {
    return in;
  }
  in.setstate(std::ios::failbit);
  return in;
}

double getArea(const Polygon &poly)
{
  if (poly.points.size() < 3)
    return 0.0;
  size_t n = poly.points.size();

  double area = std::accumulate(poly.points.begin(), poly.points.end(), 0.0,
                                [&poly, n, i = 0](double sum, const Point &p) mutable
                                {
                                  const Point &next = poly.points[(i + 1) % n];
                                  double term = static_cast<double>(p.x) * next.y - static_cast<double>(next.x) * p.y;
                                  i++;
                                  return sum + term;
                                });

  return std::abs(area) / 2.0;
}

bool isRectangle(const Polygon &poly)
{
  if (poly.points.size() != 4)
    return false;

  auto dot_product = [](const Point &a, const Point &b, const Point &c)
  {
    long long bax = a.x - b.x;
    long long bay = a.y - b.y;
    long long bcx = c.x - b.x;
    long long bcy = c.y - b.y;
    return bax * bcx + bay * bcy;
  };

  return dot_product(poly.points[3], poly.points[0], poly.points[1]) == 0 &&
         dot_product(poly.points[0], poly.points[1], poly.points[2]) == 0 &&
         dot_product(poly.points[1], poly.points[2], poly.points[3]) == 0 &&
         dot_product(poly.points[2], poly.points[3], poly.points[0]) == 0;
}

bool parsePolygonFromStream(std::istream &ss, Polygon &poly)
{
  size_t count;
  if (!(ss >> count) || count < 3)
    return false;

  poly.points.clear();
  poly.points.resize(count);

  bool success = true;
  std::generate_n(poly.points.begin(), count, [&ss, &success]()
                  {
        Point p;
        if (!(ss >> p)) {
            success = false;
        }
        return p; });

  if (!success)
    return false;

  char trailing;
  if (ss >> trailing)
    return false;

  return true;
}
