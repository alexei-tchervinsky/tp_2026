#include "rectangle.h"

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
    : bottomLeft_(bottomLeft), topRight_(topRight) {}

double Rectangle::getArea() const {
    double width = topRight_.x - bottomLeft_.x;
    double height = topRight_.y - bottomLeft_.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    return { (bottomLeft_.x + topRight_.x) / 2.0, (bottomLeft_.y + topRight_.y) / 2.0 };
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();

    double halfWidth = (topRight_.x - bottomLeft_.x) * factor / 2.0;
    double halfHeight = (topRight_.y - bottomLeft_.y) * factor / 2.0;

    bottomLeft_ = { center.x - halfWidth, center.y - halfHeight };
    topRight_ = { center.x + halfWidth, center.y + halfHeight };
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
