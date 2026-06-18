#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

struct Polygon {
    std::vector<Point> points;
};

// Геометрические утилиты
double getArea(const Polygon& polygon);
int dotProduct(const Point& a, const Point& b, const Point& c);
bool hasRightAngle(const Polygon& polygon);
bool comparePoints(const Point& a, const Point& b);
bool isPermutation(Polygon p1, Polygon p2);

#endif
