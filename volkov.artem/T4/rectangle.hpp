#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
private:
    Point leftBottom;
    Point rightTop;

public:
    Rectangle(const Point &lb, const Point &rt);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;
};

#endif
