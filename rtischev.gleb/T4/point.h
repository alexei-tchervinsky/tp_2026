#ifndef POINT_H
#define POINT_H

struct Point{
    double x = 0;
    double y = 0;
};


struct FrameRect {
    double width;
    double height;
    Point pos;
};

#endif
