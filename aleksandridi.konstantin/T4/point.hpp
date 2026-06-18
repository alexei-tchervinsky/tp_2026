#ifndef POINT_H
#define POINT_H

struct Point
{
    double x_;
    double y_;
};

struct FrameRect {
    Point pos_;
    double width_;
    double height_;
};
#endif //POINT_H
