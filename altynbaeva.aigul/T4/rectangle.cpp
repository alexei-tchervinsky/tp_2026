#include "rectangle.h"

Rectangle::Rectangle(Point bottomLeft, Point topRight) : bl(bottomLeft), tr(topRight) {}

double Rectangle::getArea() const {
    return (tr.x - bl.x) * (tr.y - bl.y); //площадь
}

Point Rectangle::getCenter() const {
    return { (bl.x + tr.x) / 2, (bl.y + tr.y) / 2 }; //центр
}

void Rectangle::move(double dx, double dy) { //смещение
    bl.x += dx;
    bl.y += dy;
    tr.x += dx;
    tr.y += dy;
}

void Rectangle::scale(double factor) { //увеличение
    Point c = getCenter(); //находим центр
    bl.x = c.x + (bl.x - c.x) * factor; //левый нижний
    bl.y = c.y + (bl.y - c.y) * factor;
    tr.x = c.x + (tr.x - c.x) * factor; //правый верхний
    tr.y = c.y + (tr.y - c.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
