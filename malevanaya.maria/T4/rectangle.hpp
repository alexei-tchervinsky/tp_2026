#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
public:
    Rectangle(Point bottomLeft, Point topRight);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double koef) override;
    std::string getName() const override;
    void print() const override;
private:
    Point bl_;
    Point tr_;
};

#endif
