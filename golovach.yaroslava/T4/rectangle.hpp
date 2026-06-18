#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "point.hpp"

namespace golovach {
    class Rectangle : public Shape {
    public:
        Rectangle(Point bottomLeft, Point topRight);
        double getArea() const override;
        Point getCenter() const override;
        void move(double dx, double dy) override;
        void scale(double factor) override;
        const char* getName() const override;
    private:
        Point bottomLeft_;
        Point topRight_;
    };
}

#endif
