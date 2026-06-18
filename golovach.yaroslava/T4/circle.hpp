#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "point.hpp"

namespace golovach {
    class Circle : public Shape {
    public:
        Circle(Point center, double radius);
        double getArea() const override;
        Point getCenter() const override;
        void move(double dx, double dy) override;
        void scale(double factor) override;
        const char* getName() const override;
    private:
        Point center_;
        double radius_;
    };
}

#endif
