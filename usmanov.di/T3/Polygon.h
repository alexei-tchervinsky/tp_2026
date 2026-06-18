#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

struct Point {
    int x_;
    int y_;

    bool operator==(const Point& other) const;
};

struct Polygon
{
    std::vector<Point> points_;
};

double area(const Polygon& polygon);

#endif
