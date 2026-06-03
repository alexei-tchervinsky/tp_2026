#ifndef RING_HPP
#define RING_HPP

#include "Shape.hpp"

class Ring : public Shape {
private:
    float innerRadius_;
    float outerRadius_;
    Point center_;

public:
    Ring();
    Ring(float innerRadius, float outerRadius, const Point& center);

    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;

    void move(const Point& pos) override;
    void move(float dx, float dy) override;

    void scale(float k) override;

    Ring* clone() const override;
    const char* getName() const override;
};

#endif