#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

struct Point {
  int x, y;
};

struct Polygon {
  std::vector<Point> points;
};

struct Frame {
  Point minPoint;
  Point maxPoint;
};

std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

double getArea(const Polygon& poly);
bool isPolygonEqual(const Polygon& a, const Polygon& b);
Frame getCollectionFrame(const std::vector<Polygon>& polygons);
bool isPolygonInFrame(const Polygon& poly, const Frame& frame);

#endif
