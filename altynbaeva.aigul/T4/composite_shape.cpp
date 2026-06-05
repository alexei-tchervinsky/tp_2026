#include "composite_shape.h"
#include <limits>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double sum = 0;
    for (const auto& s : shapes) {
        sum += s->getArea();
    }
    return sum;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) return { 0, 0 };

    double minX = shapes[0]->getCenter().x;
    double minY = shapes[0]->getCenter().y;
    double maxX = minX;
    double maxY = minY;

    for (const auto& s : shapes) {
        Point c = s->getCenter();
        if (c.x < minX) minX = c.x;
        if (c.y < minY) minY = c.y;
        if (c.x > maxX) maxX = c.x;
        if (c.y > maxY) maxY = c.y;
    }

    return { (minX + maxX) / 2, (minY + maxY) / 2 };
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes) {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point center = getCenter();
    for (auto& s : shapes) {
        Point c = s->getCenter();
        double dx = (c.x - center.x) * factor - (c.x - center.x);
        double dy = (c.y - center.y) * factor - (c.y - center.y);
        s->move(dx, dy);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
