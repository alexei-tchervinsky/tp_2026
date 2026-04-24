#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
    Point(float x = 0, float y = 0);
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    void move(float dx, float dy);

private:
    float x_;
    float y_;
};

#endif
