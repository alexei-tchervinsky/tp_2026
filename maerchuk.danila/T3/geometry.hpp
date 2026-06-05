#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

struct Point
{
    int x, y;
};

struct Polygon
{
    std::vector<Point> points;
};

double getArea(const Polygon& polygon);
bool isRectangle(const Polygon& polygon);
bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doSegmentsIntersect(Point p1, Point q1, Point p2, Point q2);
bool isPointInPolygon(Point pt, const Polygon& poly);
bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2);

#endif
