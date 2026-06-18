#include "circle.h"
#include <cmath>
#include <utility>

Circle::Circle(const Point& center, double radius)
    : center(center), radius(radius) {}

Circle::Circle(const Circle& other)
    : center(other.center), radius(other.radius) {}

Circle::Circle(Circle&& other) noexcept
    : center(std::move(other.center)), radius(std::exchange(other.radius, 0.0)) {}

Circle& Circle::operator=(const Circle& other) {
    if (this != &other) {
        Circle temp(other);
        swap(temp);
    }
    return *this;
}

Circle& Circle::operator=(Circle&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

void Circle::swap(Circle& other) noexcept {
    using std::swap;
    swap(center, other.center);
    swap(radius, other.radius);
}

double Circle::getArea() const {
    return M_PI * radius * radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Circle::scale(double factor) {
    radius *= factor;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

std::unique_ptr<Shape> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}
