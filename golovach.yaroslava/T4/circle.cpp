#include "circle.hpp"
#include <cmath>

namespace golovach {
    Circle::Circle(Point center, double radius)
        : center_(center), radius_(radius) {}

    double Circle::getArea() const {
        return M_PI * radius_ * radius_;
    }

    Point Circle::getCenter() const {
        return center_;
    }

    void Circle::move(double dx, double dy) {
        center_.x += dx;
        center_.y += dy;
    }

    void Circle::scale(double factor) {
        radius_ *= factor;
    }

    const char* Circle::getName() const {
        return "CIRCLE";
    }
}
