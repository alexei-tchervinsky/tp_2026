#ifndef T3_POINT_HPP
#define T3_POINT_HPP

struct Point {
    int x, y;
    Point() {};
    Point(int x_, int y_) : x(x_), y(y_) {};

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

#endif //T3_POINT_HPP
