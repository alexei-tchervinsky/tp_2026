#ifndef POINT_HPP
#define POINT_HPP

#include "ics.h"

struct Point {
    float x_, y_;

    Point();
    Point(float x, float y);

    static Point min(const Point& p1, const Point& p2);
    static Point max(const Point& p1, const Point& p2);

    friend std::ostream& operator<<(std::ostream&, const Point&);
};

#endif