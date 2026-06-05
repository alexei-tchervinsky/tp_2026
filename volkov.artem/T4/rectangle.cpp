#include "rectangle.hpp"

Rectangle::Rectangle(const Point &lb, const Point &rt) : leftBottom(lb), rightTop(rt) {
}

double Rectangle::getArea() const {
    return (rightTop.x - leftBottom.x) * (rightTop.y - leftBottom.y);
}

Point Rectangle::getCenter() const {
    return {(leftBottom.x + rightTop.x) / 2.0, (leftBottom.y + rightTop.y) / 2.0};
}

void Rectangle::move(double dx, double dy) {
    leftBottom.x += dx;
    leftBottom.y += dy;
    rightTop.x += dx;
    rightTop.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    double halfWidth = (rightTop.x - leftBottom.x) / 2.0 * factor;
    double halfHeight = (rightTop.y - leftBottom.y) / 2.0 * factor;

    leftBottom = {center.x - halfWidth, center.y - halfHeight};
    rightTop = {center.x + halfWidth, center.y + halfHeight};
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
