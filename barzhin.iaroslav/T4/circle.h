//
// Created by xmdnusr on 25.03.2026.
//

#ifndef T4_CIRCLE_H
#define T4_CIRCLE_H
#include "shape.h"

class Circle : public Shape {
    Point center_;
    double radius_;
public:
    Circle(const Point& center, double radius);
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

#endif //T4_CIRCLE_H
