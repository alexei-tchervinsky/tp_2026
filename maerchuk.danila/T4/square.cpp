#include "square.hpp"
#include <stdexcept>

Square::Square(const Point& center, float side)
    : center(center), side(side) {
    if (side <= 0) {
        throw std::invalid_argument("Side length must be positive.");
    }
}

float Square::getArea() const {
    return side * side;
}

FrameRectangle Square::getFrameRectangle() const {
    float width = side;
    float height = side;
    return FrameRectangle(width, height, center);
}

void Square::move(const Point& newPos) {
    center = newPos;
}

void Square::move(float dx, float dy) {
    center.move(dx, dy);
}

Square* Square::clone() const {
    return new Square(*this);
}

std::string Square::getName() const {
    return "SQUARE";
}

float Square::getSide() const {
    return side;
}

Point Square::getCenter() const {
    return center;
}
