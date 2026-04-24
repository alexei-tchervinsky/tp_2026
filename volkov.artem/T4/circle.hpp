#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
private:
    Point center;
    double radius;

public:
    Circle(const Point &c, double r);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;
};

#endif
