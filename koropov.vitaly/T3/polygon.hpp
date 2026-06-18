#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

struct Point
{
  int x, y;
};

struct Polygon
{
  std::vector<Point> points;
};

bool operator==(const Point &a, const Point &b);
bool operator==(const Polygon &a, const Polygon &b);
std::istream &operator>>(std::istream &in, Point &p);

double getArea(const Polygon &poly);
bool isRectangle(const Polygon &poly);
bool parsePolygonFromStream(std::istream &ss, Polygon &poly);

#endif // POLYGON_HPP
