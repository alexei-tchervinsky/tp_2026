#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(const Point& center, float radius)
: center(center), radius(radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive.");
    }
}

float Circle::getArea() const {
    return M_PI * radius * radius;
}

FrameRectangle Circle::getFrameRectangle() const {
    float width = 2 * radius;
    float height = 2 * radius;
    return FrameRectangle(width, height, center);
}

void Circle::move(const Point& newPos) {
    center = newPos;
}

void Circle::move(float dx, float dy) {
    center.move(dx, dy);
}

Circle* Circle::clone() const {
    return new Circle(*this);
}

std::string Circle::getName() const {
    return "CIRCLE";
}
