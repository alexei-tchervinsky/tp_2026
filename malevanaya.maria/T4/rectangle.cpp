#include "rectangle.hpp"

#include <iostream>
#include <iomanip>

Rectangle::Rectangle(Point bottomLeft, Point topRight) : bl_(bottomLeft), tr_(topRight) {}

double Rectangle::getArea() const {
    return (tr_.x - bl_.x) * (tr_.y - bl_.y);
}

Point Rectangle::getCenter() const {
    return { (bl_.x + tr_.x) / 2.0, (bl_.y + tr_.y) / 2.0 };
}

void Rectangle::move(double dx, double dy) {
    bl_.x += dx; bl_.y += dy;
    tr_.x += dx; tr_.y += dy;
}

void Rectangle::scale(double koef) {
    Point c = getCenter();
    bl_.x = c.x + (bl_.x - c.x) * koef;
    bl_.y = c.y + (bl_.y - c.y) * koef;
    tr_.x = c.x + (tr_.x - c.x) * koef;
    tr_.y = c.y + (tr_.y - c.y) * koef;
}

std::string Rectangle::getName() const { return "RECTANGLE"; }

void Rectangle::print() const {
    Point c = getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << getName() << ", (" << c.x << ", " << c.y << "), " << getArea() << "]\n";
}
