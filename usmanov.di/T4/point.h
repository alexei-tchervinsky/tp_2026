#ifndef POINT_H
#define POINT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

struct Point
{
    double x_;
    double y_;

    Point() : x_(0), y_(0) {}
    Point(double x, double y) : x_(x), y_(y) {}

    double getDistance(double x, double y) const
    {
        return std::sqrt((x_ - x) * (x_ - x) + (y_ - y) * (y_ - y));
    }

    double getDistance(const Point& other) const
    {
        return std::sqrt((x_ - other.x_) * (x_ - other.x_)
            + (y_ - other.y_) * (y_ - other.y_));
    }
};
#endif /* POINT_H */
