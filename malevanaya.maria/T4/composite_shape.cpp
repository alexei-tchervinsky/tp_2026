#include "composite_shape.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

void CompositeShape::add(std::unique_ptr<Shape> s) {
    shapes.push_back(std::move(s));
}

double CompositeShape::getArea() const {
    double total = 0;
    for (const auto& s : shapes) total += s->getArea();
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) return { 0, 0 };
    double sx = 0, sy = 0;
    for (const auto& s : shapes) {
        sx += s->getCenter().x;
        sy += s->getCenter().y;
    }
    return { sx / shapes.size(), sy / shapes.size() };
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes) s->move(dx, dy);
}

void CompositeShape::scale(double koef) {
    Point pc = getCenter();
    for (auto& s : shapes) {
        Point sc = s->getCenter();
        s->move((sc.x - pc.x) * (koef - 1), (sc.y - pc.y) * (koef - 1));
        s->scale(koef);
    }
}

std::string CompositeShape::getName() const { return "COMPOSITE"; }

void CompositeShape::print() const {
    Point c = getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << getName() << ", (" << c.x << ", " << c.y << "), " << getArea() << "]:\n";
    for (const auto& s : shapes) {
        std::cout << "  ";
        s->print();
    }
}
