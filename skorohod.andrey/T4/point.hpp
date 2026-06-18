#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
    double x = 0, y = 0;

    friend std::ostream& operator<< (std::ostream& os, const Point& point)
    {
        os << '(' << point.x << ", " << point.y << ')';
        return os;
    }
};

#endif
