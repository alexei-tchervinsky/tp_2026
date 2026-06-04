#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

#endif