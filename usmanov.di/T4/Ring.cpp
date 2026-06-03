#include "Ring.hpp"

Ring::Ring() : innerRadius_(0), outerRadius_(0) {}

Ring::Ring(float innerRadius, float outerRadius, const Point& center) : center_(center) {
    if (innerRadius <= 0 || outerRadius <= 0) {
        throw std::invalid_argument("Radius values must be positive");
    }
    if (innerRadius >= outerRadius) {
        throw std::invalid_argument("Inner radius must be smaller than outer radius");
    }
    innerRadius_ = innerRadius;
    outerRadius_ = outerRadius;
}

float Ring::getArea() const {
    float innerRadiusSqr = innerRadius_ * innerRadius_;
    float outerRadiusSqr = outerRadius_ * outerRadius_;
    return PI * (outerRadiusSqr - innerRadiusSqr);
}

FrameRectangle Ring::getFrameRectangle() const {
    return FrameRectangle(outerRadius_ * 2, outerRadius_ * 2, center_);
}

void Ring::move(const Point& pos) {
    center_.x_ = pos.x_;
    center_.y_ = pos.y_;
}

void Ring::move(float dx, float dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Ring::scale(float k) {
    if (k <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    innerRadius_ *= k;
    outerRadius_ *= k;
}

Ring* Ring::clone() const {
    return new Ring(innerRadius_, outerRadius_, center_);
}

const char* Ring::getName() const {
    return "RING";

}