#include "circle.hpp"

#include <iostream>
#include <iomanip>

Circle::Circle(Point center, double radius) : center_(center), radius_(radius) {}

double Circle::getArea() const {
    return 3.14 * radius_ * radius_;
}

Point Circle::getCenter() const {
    return center_;
}

void Circle::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Circle::scale(double koef) {
    radius_ *= koef;
}

std::string Circle::getName() const {
    return "CIRCLE";
}

void Circle::print() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << getName() << ", (" << center_.x << ", " << center_.y << "), " << getArea() << "]\n";
}
