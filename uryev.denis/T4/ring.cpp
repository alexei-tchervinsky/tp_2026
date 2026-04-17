#include "ring.hpp"
#include <stdexcept>
#include <cmath>

Ring::Ring(double x, double y, double inner, double outer) :
    center_{ x, y }, innerRadius_(inner), outerRadius_(outer) {
    if (inner <= 0.0 || outer <= inner) {
        throw std::invalid_argument("Invalid radii for ring");
    }
}

double Ring::getArea() const {
    return 3.1415926 * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

Point Ring::getCenter() const {
    return center_;
}

FrameRectangle Ring::getFrameRectangle() const {
    return { outerRadius_ * 2.0, outerRadius_ * 2.0, center_ };
}

void Ring::move(const Point& newPos) {
    center_ = newPos;
}

void Ring::move(double dx, double dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Ring::scale(double coeff) {
    if (coeff <= 0.0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }
    innerRadius_ *= coeff;
    outerRadius_ *= coeff;
}

std::string Ring::getName() const {
    return "RING";
}
