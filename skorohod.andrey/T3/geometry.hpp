#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cstddef>
#include <vector>

struct Point
{
    int x, y;
    bool operator==(const Point& other) const;
};

struct Polygon
{
    std::vector<Point> points;
    std::size_t vertexCount() const { return points.size(); }
    double area() const;
    bool operator==(const Polygon& other) const;
    bool hasRightAngle() const;
};

#endif
