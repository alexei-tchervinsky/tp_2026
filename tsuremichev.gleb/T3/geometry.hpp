#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "polygon.hpp"

double getArea(const Polygon &poly);
bool isIntersectingSegments(Point a, Point b, Point c, Point d);
bool isIntersectingPolygons(const Polygon &p1, const Polygon &p2);

#endif
