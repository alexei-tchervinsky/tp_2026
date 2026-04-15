#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(double x, double y, double width, double height) :
    center_{ x, y }, width_(width), height_(height) {
    if (width <= 0.0 || height <= 0.0) {
        throw std::invalid_argument("Invalid rectangle parameters");
    }
}

double Rectangle::getArea() const {
    return width_ * height_;
}

Point Rectangle::getCenter() const {
    return center_;
}

FrameRectangle Rectangle::getFrameRectangle() const {
    return { width_, height_, center_ };
}

void Rectangle::move(const Point& newPos) {
    center_ = newPos;
}

void Rectangle::move(double dx, double dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Rectangle::scale(double coeff) {
    if (coeff <= 0.0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }
    width_ *= coeff;
    height_ *= coeff;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
