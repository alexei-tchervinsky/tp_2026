#include "rhomb.h"


Rhombus::Rhombus(Point center, double hHalf, double vHalf) {
    this->center = center;
    this->hHalf = hHalf;
    this->vHalf = vHalf;
}

double Rhombus::getArea() const {
    return (hHalf * vHalf) / 2;
}
Point Rhombus::getCenter() const {
    return center;
}

FrameRect Rhombus::getFrameRect() const {
    double width = hHalf * 2.0;
    double height = vHalf * 2.0;
    Point pos = center;
    return { width, height, pos };
}


void Rhombus::move(double dx, double dy){
    center.x += dx;
    center.y += dy;
}

void Rhombus::scale(double factor){
    hHalf = hHalf * factor;
    vHalf = vHalf * factor;
}
std::string Rhombus::getName() const {
    return "RHOMBUS";
}


double Rhombus::getMinX() const { return getFrameRect().pos.x - getFrameRect().width / 2.0; }
double Rhombus::getMaxX() const { return getFrameRect().pos.x + getFrameRect().width / 2.0; }
double Rhombus::getMinY() const { return getFrameRect().pos.y - getFrameRect().height / 2.0; }
double Rhombus::getMaxY() const { return getFrameRect().pos.y + getFrameRect().height / 2.0; }
