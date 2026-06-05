#include "rectangle.h"

Rectangle::Rectangle(Point bottomLeft, Point topRight) : bl(bottomLeft), tr(topRight) {}

double Rectangle::getArea() const {
    return (tr.x - bl.x) * (tr.y - bl.y);
}

Point Rectangle::getCenter() const {
    return { (bl.x + tr.x) / 2, (bl.y + tr.y) / 2 };
}

void Rectangle::move(double dx, double dy) {
    bl.x += dx;
    bl.y += dy;
    tr.x += dx;
    tr.y += dy;
}

void Rectangle::scale(double factor) {
    Point c = getCenter();
    bl.x = c.x + (bl.x - c.x) * factor;
    bl.y = c.y + (bl.y - c.y) * factor;
    tr.x = c.x + (tr.x - c.x) * factor;
    tr.y = c.y + (tr.y - c.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

