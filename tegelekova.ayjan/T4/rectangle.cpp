#include "rectangle.h"
#include <algorithm>

Rectangle::Rectangle(const Point& bl, const Point& tr)
    : bottomLeft(bl), topRight(tr) {}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    return Point(
        (bottomLeft.x + topRight.x) / 2,
        (bottomLeft.y + topRight.y) / 2
    );
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    double halfWidth = (topRight.x - bottomLeft.x) * factor / 2;
    double halfHeight = (topRight.y - bottomLeft.y) * factor / 2;

    bottomLeft = Point(center.x - halfWidth, center.y - halfHeight);
    topRight = Point(center.x + halfWidth, center.y + halfHeight);
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
