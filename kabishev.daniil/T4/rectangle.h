#ifndef TP_2026_RECTANGLE_H
#define TP_2026_RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    Point bottomLeft_;
    Point topRight_;

public:
    Rectangle(const Point& bottomLeft, const Point& topRight);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif
