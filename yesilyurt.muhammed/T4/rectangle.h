#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
    Point leftBottom;
    Point rightTop;

public:
    Rectangle(const Point& lb, const Point& rt);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    double getLeft() const override;
    double getRight() const override;
    double getBottom() const override;
    double getTop() const override;
};

#endif
