#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace tchervinsky
{
    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        bool operator<(const Point& other) const;
    };

    std::istream& operator>>(std::istream& in, Point& p);
    std::ostream& operator<<(std::ostream& out, const Point& p);

    struct Polygon
    {
        std::vector<Point> points;
        bool operator==(const Polygon& other) const;
    };

    std::istream& operator>>(std::istream& in, Polygon& poly);
    std::ostream& operator<<(std::ostream& out, const Polygon& poly);

    double getArea(const Polygon& poly);
    bool isRectangle(const Polygon& poly);
    bool hasRightAngle(const Polygon& poly);
    bool isInFrame(const Polygon& poly, const std::vector<Polygon>& polygons);
    bool isPermutation(const Polygon& a, const Polygon& b);
    void getBoundingBox(const std::vector<Polygon>& polygons, int& minX, int& minY, int& maxX, int& maxY);
}

#endif
