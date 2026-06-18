#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <set>

namespace tchervinsky
{
    bool Point::operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Point::operator!=(const Point& other) const
    {
        return !(*this == other);
    }

    bool Point::operator<(const Point& other) const
    {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    std::istream& operator>>(std::istream& in, Point& p)
    {
        char bracket1, bracket2, comma;
        in >> bracket1 >> p.x >> comma >> p.y >> bracket2;

        if (!in || bracket1 != '(' || bracket2 != ')' || (comma != ';' && comma != ','))
        {
            in.setstate(std::ios::failbit);
            p.x = 0;
            p.y = 0;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "(" << p.x << ";" << p.y << ")";
        return out;
    }

    bool Polygon::operator==(const Polygon& other) const
    {
        if (points.size() != other.points.size())
            return false;
        return std::equal(points.begin(), points.end(), other.points.begin());
    }

    std::istream& operator>>(std::istream& in, Polygon& poly)
    {
        size_t vertexCount;
        in >> vertexCount;
        if (!in) return in;

        std::vector<Point> temp;
        temp.reserve(vertexCount);

        for (size_t i = 0; i < vertexCount; ++i)
        {
            Point p;
            in >> p;
            if (!in) return in;
            temp.push_back(p);
        }

        poly.points = std::move(temp);
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Polygon& poly)
    {
        out << poly.points.size() << " ";
        for (const auto& p : poly.points)
        {
            out << p << " ";
        }
        return out;
    }

    double getArea(const Polygon& poly)
    {
        if (poly.points.size() < 3) return 0.0;

        double area = 0.0;
        size_t n = poly.points.size();

        for (size_t i = 0; i < n; ++i)
        {
            const Point& p1 = poly.points[i];
            const Point& p2 = poly.points[(i + 1) % n];
            area += (p1.x * p2.y - p2.x * p1.y);
        }

        return std::abs(area) / 2.0;
    }

    void getBoundingBox(const std::vector<Polygon>& polygons, int& minX, int& minY, int& maxX, int& maxY)
    {
        if (polygons.empty()) return;

        minX = maxX = polygons[0].points[0].x;
        minY = maxY = polygons[0].points[0].y;

        for (const auto& poly : polygons)
        {
            for (const auto& p : poly.points)
            {
                minX = std::min(minX, p.x);
                minY = std::min(minY, p.y);
                maxX = std::max(maxX, p.x);
                maxY = std::max(maxY, p.y);
            }
        }
    }

    bool isInFrame(const Polygon& poly, const std::vector<Polygon>& polygons)
    {
        int minX, minY, maxX, maxY;
        getBoundingBox(polygons, minX, minY, maxX, maxY);

        for (const auto& p : poly.points)
        {
            if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)
                return false;
        }
        return true;
    }

    bool isPermutation(const Polygon& a, const Polygon& b)
    {
        if (a.points.size() != b.points.size()) return false;

        std::multiset<Point> setA(a.points.begin(), a.points.end());
        std::multiset<Point> setB(b.points.begin(), b.points.end());

        return setA == setB;
    }

    bool isRectangle(const Polygon&)
    {
        return false;
    }

    bool hasRightAngle(const Polygon&)
    {
        return false;
    }
}
