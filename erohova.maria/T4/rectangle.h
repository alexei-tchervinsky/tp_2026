#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(Point lowLeft, Point topRight);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
    std::string getName() const override;
    void print() const override;
private:
    Point center_;
    double width_;
    double height_;
};

#endif
