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

bool operator==(const Polygon &lhs, const Polygon &rhs);
std::istream &operator>>(std::istream &in, Point &point);
std::istream &operator>>(std::istream &in, Polygon &polygon);

#endif
