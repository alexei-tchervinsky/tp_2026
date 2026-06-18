#include "geometry.hpp"
#include <cmath>
#include <cstddef>

bool Point::operator==(const Point& other) const
{
    return x == other.x && y == other.y;
}

double Polygon::area() const
{
    if (points.size() < 3) return 0.0;
    double sum = 0.0;
    for (std::size_t i = 0; i < points.size(); ++i)
    {
        const Point& p1 = points[i];
        const Point& p2 = points[(i+1) % points.size()];
        sum += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(sum) / 2.0;
}

bool Polygon::operator==(const Polygon& other) const
{
    if (vertexCount() != other.vertexCount()) return false;
    return std::equal(points.begin(), points.end(), other.points.begin());
}

bool Polygon::hasRightAngle() const
{
    std::size_t n = vertexCount();
    if (n < 3) return false;
    for (std::size_t i = 0; i < n; ++i)
    {
        const Point& p1 = points[i];
        const Point& p2 = points[(i+1) % n];
        const Point& p3 = points[(i+2) % n];
        int v1x = p2.x - p1.x;
        int v1y = p2.y - p1.y;
        int v2x = p3.x - p2.x;
        int v2y = p3.y - p2.y;
        if (v1x * v2x + v1y * v2y == 0)
        {
            return true;
        }
    }
    return false;
}
