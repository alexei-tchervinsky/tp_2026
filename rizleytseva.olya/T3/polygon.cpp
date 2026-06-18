#include "polygon.h"
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <functional>

// ============ Point ============

bool Point::operator==(const Point& other) const
{
  return x == other.x && y == other.y;
}

bool Point::operator<(const Point& other) const
{
  return (x != other.x) ? (x < other.x) : (y < other.y);
}

// ============ Polygon ============

bool Polygon::operator==(const Polygon& other) const
{
  return points == other.points;
}

// ============ IO ВСПОМОГАТЕЛЬНЫЕ ОПЕРАТОРЫ ============

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, PointIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> dest.ref.x >> DelimiterIO{ ';' }
     >> dest.ref.y >> DelimiterIO{ ')' };
  return in;
}

// Функтор для чтения одной точки из потока
struct PointReader
{
  std::istream& in;

  explicit PointReader(std::istream& s) : in(s) {}

  Point operator()()
  {
    Point p{};
    in >> PointIO{ p };
    return p;
  }
};

// Читает полигон: "N (x1;y1) (x2;y2) ... (xN;yN)"
std::istream& operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::size_t n = 0;
  in >> n;
  if (!in || n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > pts(n);
  std::generate(pts.begin(), pts.end(), PointReader(in));

  if (in.fail())
  {
    return in;
  }

  dest.points = std::move(pts);
  return in;
}

// ============ OUTPUT ============

std::ostream& operator<<(std::ostream& out, const Point& src)
{
  out << '(' << src.x << ';' << src.y << ')';
  return out;
}

std::ostream& operator<<(std::ostream& out, const Polygon& src)
{
  out << src.points.size() << ' ';
  std::copy(src.points.begin(), src.points.end(),
            std::ostream_iterator< Point >(out, " "));
  return out;
}

// ============ ГЕОМЕТРИЯ ============

// Функтор для одного слагаемого формулы Гаусса: x_i*y_{i+1} - x_{i+1}*y_i
struct GaussStep
{
  const std::vector< Point >& pts;
  std::size_t size;

  explicit GaussStep(const std::vector< Point >& p)
    : pts(p), size(p.size())
  {}

  long long operator()(long long acc, const Point& p) const
  {
    std::size_t i = static_cast< std::size_t >(&p - pts.data());
    std::size_t j = (i + 1) % size;
    return acc
      + static_cast< long long >(p.x) * pts[j].y
      - static_cast< long long >(pts[j].x) * p.y;
  }
};

double getArea(const Polygon& poly)
{
  if (poly.points.size() < 3)
  {
    return 0.0;
  }
  long long twice = std::accumulate(
    poly.points.begin(), poly.points.end(), 0LL, GaussStep(poly.points));
  return std::abs(twice) / 2.0;
}

// ============ SAT (теорема разделяющей оси) ============

struct ProjectPoint
{
  double nx, ny;

  ProjectPoint(double x, double y) : nx(x), ny(y) {}

  double operator()(const Point& p) const
  {
    return static_cast< double >(p.x) * nx + static_cast< double >(p.y) * ny;
  }
};

struct Projection { double minVal, maxVal; };

Projection projectPolygon(const Polygon& poly, double nx, double ny)
{
  std::vector< double > vals(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), vals.begin(),
                 ProjectPoint(nx, ny));
  auto mm = std::minmax_element(vals.begin(), vals.end());
  return { *mm.first, *mm.second };
}

struct IsSeparatingAxis
{
  const Polygon& a;
  const Polygon& b;
  const std::vector< Point >& edgePts;

  IsSeparatingAxis(const Polygon& a, const Polygon& b,
                   const std::vector< Point >& ep)
    : a(a), b(b), edgePts(ep)
  {}

  bool operator()(const Point& p) const
  {
    std::size_t i = static_cast< std::size_t >(&p - edgePts.data());
    std::size_t j = (i + 1) % edgePts.size();
    const Point& q = edgePts[j];

    double nx = static_cast< double >(q.y - p.y);
    double ny = static_cast< double >(-(q.x - p.x));

    Projection pa = projectPolygon(a, nx, ny);
    Projection pb = projectPolygon(b, nx, ny);

    return (pa.maxVal < pb.minVal) || (pb.maxVal < pa.minVal);
  }
};

bool intersects(const Polygon& a, const Polygon& b)
{
  if (std::any_of(a.points.begin(), a.points.end(),
                  IsSeparatingAxis(a, b, a.points)))
  {
    return false;
  }
  if (std::any_of(b.points.begin(), b.points.end(),
                  IsSeparatingAxis(a, b, b.points)))
  {
    return false;
  }
  return true;
}

// ============ ФУНКТОРЫ ============

double AreaAccumulator::operator()(double acc, const Polygon& p) const
{
  return acc + getArea(p);
}

bool EvenVertexPred::operator()(const Polygon& p) const
{
  return p.points.size() % 2 == 0;
}

bool OddVertexPred::operator()(const Polygon& p) const
{
  return p.points.size() % 2 != 0;
}

VertexCountPred::VertexCountPred(std::size_t n) : count(n) {}
bool VertexCountPred::operator()(const Polygon& p) const
{
  return p.points.size() == count;
}

bool AreaLess::operator()(const Polygon& a, const Polygon& b) const
{
  return getArea(a) < getArea(b);
}

bool VertexCountLess::operator()(const Polygon& a, const Polygon& b) const
{
  return a.points.size() < b.points.size();
}

AreaLessThan::AreaLessThan(double t) : threshold(t) {}
bool AreaLessThan::operator()(const Polygon& p) const
{
  return getArea(p) < threshold;
}

IntersectsWith::IntersectsWith(const Polygon& t) : target(t) {}
bool IntersectsWith::operator()(const Polygon& p) const
{
  return intersects(p, target);
}

ConditionalAreaAccumulator::ConditionalAreaAccumulator(bool e) : even(e) {}
double ConditionalAreaAccumulator::operator()(double acc, const Polygon& p) const
{
  if ((p.points.size() % 2 == 0) == even)
  {
    return acc + getArea(p);
  }
  return acc;
}

VertexCountAreaAccumulator::VertexCountAreaAccumulator(std::size_t n) : count(n) {}
double VertexCountAreaAccumulator::operator()(double acc, const Polygon& p) const
{
  if (p.points.size() == count)
  {
    return acc + getArea(p);
  }
  return acc;
}

