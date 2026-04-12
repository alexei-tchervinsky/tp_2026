//
// Created by xmdnusr on 07.03.2026.
//

#ifndef T4_RECTANGLE_H
#define T4_RECTANGLE_H

#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
    Point left_low_;
    Point right_top_;
public:
    Rectangle(const Point& left_low, const Point& right_top);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
    std::string getName() const override;
    void print() const override;

    // misc
    Point getLeftLow() const override;
    Point getRightTop() const override;
};

#endif //T4_RECTANGLE_H
