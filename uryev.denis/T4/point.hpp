#ifndef POINT_HPP
#define POINT_HPP

struct Point {
    double x_;
    double y_;

    Point() : x_(0.0), y_(0.0) {}
    Point(double x, double y) : x_(x), y_(y) {}
};

#endif //!POINT_HPP
