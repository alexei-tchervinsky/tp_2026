#include "ellipse.hpp"
#include <cmath>

double Ellipse::getArea() const {
    const double PI = std::acos(-1);
    return PI*horizontalRadius_*verticalRadius_;
}
Point Ellipse::getCenter() const {
    return center_;
}

void Ellipse::move(double dx, double dy){
    center_.x_ += dx;
    center_.y_ += dy;
}
void Ellipse::scale(double factor){
    if(factor<=0.0)return;
    horizontalRadius_*=factor;
    verticalRadius_*=factor;
}

std::string Ellipse::getName() const{ return "ELLIPSE"; }

FrameRect Ellipse::getFrameRect() const {
    return { center_, horizontalRadius_ * 2.0, verticalRadius_ * 2.0 };
}
