#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP

#include <complex>
#include <utility>
#include <string>
#include <vector>

#include "point.hpp"

class Polygon {
    std::vector<Point> points;

    public:
        const std::vector<Point>& getPoints() const;
        void addPoint(const Point p);
        double getArea() const;
        std::pair<Point, Point> getBounds() const;
        bool inBounds(std::pair<Point, Point> bounds) const;

        bool operator==(const Polygon &other) const;
};

struct DelimiterIO {
    char exp;
};

struct IntIO {
    int& ref;
};

std::istream &operator>>(std::istream &is, DelimiterIO&& dest);
std::istream &operator>>(std::istream &is, IntIO&& dest);
std::istream &operator>>(std::istream &is, Polygon& dest);
std::ostream &operator<<(std::ostream &os, const Polygon& obj);

#endif //T3_POLYGON_HPP
