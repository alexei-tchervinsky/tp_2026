#include "rectangle.h"


Rectangle::Rectangle(Point ll, Point ur) {
    this->LowerLeft = ll;
    this->UpperRight = ur;
}

double Rectangle::getArea() const {
    return (UpperRight.x - LowerLeft.x) * (UpperRight.y - LowerLeft.y);
}

Point Rectangle::getCenter() const {
    return Point{ (LowerLeft.x + UpperRight.x) / 2, (LowerLeft.y + UpperRight.y) / 2 };
}

void Rectangle::move(double dx, double dy) {
    LowerLeft.x += dx;
    UpperRight.x += dx;
    LowerLeft.y += dy;
    UpperRight.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();

    double dx = (LowerLeft.x - center.x) * factor;
    double dy = (LowerLeft.y - center.y) * factor;

    LowerLeft.x = center.x + dx;
    LowerLeft.y = center.y + dy;
    UpperRight.x = center.x - dx;
    UpperRight.y = center.y - dy;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

FrameRect Rectangle::getFrameRect() const {
    double width = UpperRight.x - LowerLeft.x;
    double height = UpperRight.y - LowerLeft.y;

    Point pos = {
        LowerLeft.x + width / 2.0,
        LowerLeft.y + height / 2.0
    };

    return { width, height, pos };
}


double Rectangle::getMinX() const { return getFrameRect().pos.x - getFrameRect().width / 2.0; }
double Rectangle::getMaxX() const { return getFrameRect().pos.x + getFrameRect().width / 2.0; }
double Rectangle::getMinY() const { return getFrameRect().pos.y - getFrameRect().height / 2.0; }
double Rectangle::getMaxY() const { return getFrameRect().pos.y + getFrameRect().height / 2.0; }
