#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "shapes.hpp"

double getArea(const Polygon &poly);
std::pair<Point, Point> getBounds(const Polygon &poly);
bool inBounds(const Polygon &poly, const std::pair<Point, Point> &bounds);

#endif
