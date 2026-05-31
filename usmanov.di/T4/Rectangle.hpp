#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape {
private:
    Point leftBottom_;
    Point rightTop_;

public:
    Rectangle();
    Rectangle(const Point& leftBottom, const Point& rightTop);

    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;

    void move(const Point& pos) override;
    void move(float dx, float dy) override;

    void scale(float k) override;

    Rectangle* clone() const override;
    const char* getName() const override;
};

#endif