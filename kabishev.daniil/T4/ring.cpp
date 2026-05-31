#include "ring.h"

const double PI = 3.141592653589793;

Ring::Ring(const Point& center, double outerRadius, double innerRadius)
    : center_(center), outerRadius_(outerRadius), innerRadius_(innerRadius) {}

double Ring::getArea() const {
    return PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

Point Ring::getCenter() const {
    return center_;
}

void Ring::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Ring::scale(double factor) {
    outerRadius_ *= factor;
    innerRadius_ *= factor;
}

std::string Ring::getName() const {
    return "RING";
}
