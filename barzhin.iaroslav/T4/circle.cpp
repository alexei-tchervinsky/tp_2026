//
// Created by xmdnusr on 25.03.2026.
//

#include "circle.h"

#include <cmath>
#include <iostream>
#include <iomanip>

Circle::Circle(const Point& center, const double radius):
    center_(center), radius_(radius)
{
    if (radius_ < 0) {
        radius_ = 0;
    }
}

double Circle::getArea() const {
    static const double pi = std::acos(-1.0);
    return pi * radius_ * radius_;
}

Point Circle::getCenter() const {
    return center_;
}

void Circle::move(const double dx, const double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Circle::scale(const double coefficient) {
    if (coefficient < 0) return;
    radius_ *= coefficient;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

void Circle::print() const {
    std::ios_base::fmtflags f(std::cout.flags());

    auto center = getCenter();
    auto area = getArea();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "["
        << getName()
        << ", ("
        << center.x
        << ", "
        << center.y
        << "), "
        << area
        << "]"
        << std::endl;

    std::cout.flags(f);
}


Point Circle::getLeftLow() const {
    return {center_.x - radius_, center_.y - radius_};
}

Point Circle::getRightTop() const {
    return {center_.x + radius_, center_.y + radius_};
}
