#include "Polygon.hpp"
#include <numeric>
#include <algorithm>
#include <cmath>

std::istream& operator>>(std::istream& in, Point& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;
  char open = 0, ch = 0, close = 0;
  int tx = 0, ty = 0;
  in >> open >> tx >> ch >> ty >> close;
  if (in && open == '(' && ch == ';' && close == ')') {
    dest.x = tx;
    dest.y = ty;
  } else {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Polygon& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;
  
  size_t numPoints = 0;
  if (!(in >> numPoints) || numPoints < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  std::vector<Point> tempPoints(numPoints);
  // Читаем строго numPoints элементов без использования istream_iterator
  std::generate_n(tempPoints.begin(), numPoints, [&in]() {
    Point p;
    if (!(in >> p)) {
      in.setstate(std::ios::failbit);
    }
    return p;
  });

  if (in) {
    dest.points = std::move(tempPoints);
  }
  return in;
}

double getArea(const Polygon& poly) {
  if (poly.points.size() < 3) return 0.0;
  auto indices = std::vector<size_t>(poly.points.size());
  std::iota(indices.begin(), indices.end(), 0);
  double sum = std::accumulate(
    indices.begin(),
    indices.end(),
    0.0,
    [&](double acc, size_t i) {
      size_t next = (i + 1) % poly.points.size();
      return acc + (poly.points[i].x * poly.points[next].y) -
             (poly.points[next].x * poly.points[i].y);
    }
  );
  return std::abs(sum) / 2.0;
}

bool isPointsEqual(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

bool isPolygonEqual(const Polygon& a, const Polygon& b) {
  if (a.points.size() != b.points.size()) return false;
  return std::equal(
    a.points.begin(),
    a.points.end(),
    b.points.begin(),
    isPointsEqual
  );
}

Frame getCollectionFrame(const std::vector<Polygon>& polygons) {
  Frame f{{0, 0}, {0, 0}};
  if (polygons.empty()) return f;
  f.minPoint.x = polygons[0].points[0].x;
  f.minPoint.y = polygons[0].points[0].y;
  f.maxPoint.x = polygons[0].points[0].x;
  f.maxPoint.y = polygons[0].points[0].y;
  std::for_each(polygons.begin(), polygons.end(), [&f](const Polygon& poly) {
    std::for_each(poly.points.begin(), poly.points.end(), [&f](const Point& p) {
      f.minPoint.x = std::min(f.minPoint.x, p.x);
      f.minPoint.y = std::min(f.minPoint.y, p.y);
      f.maxPoint.x = std::max(f.maxPoint.x, p.x);
      f.maxPoint.y = std::max(f.maxPoint.y, p.y);
    });
  });
  return f;
}

bool isPolygonInFrame(const Polygon& poly, const Frame& frame) {
  return std::all_of(poly.points.begin(), poly.points.end(), [&frame](const Point& p) {
    return p.x >= frame.minPoint.x && p.x <= frame.maxPoint.x &&
           p.y >= frame.minPoint.y && p.y <= frame.maxPoint.y;
  });
}
