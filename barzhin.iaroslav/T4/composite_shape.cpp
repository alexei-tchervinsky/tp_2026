//
// Created by xmdnusr on 07.03.2026.
//

#include "composite_shape.h"

#include <iostream>

double CompositeShape::getArea() const {
    double area = 0.0;
    for (auto &shape : vec_) {
        area += shape->getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const {
    Point ll = getLeftLow();
    Point rt = getRightTop();
    return {(ll.x + rt.x) / 2.0, (ll.y + rt.y) / 2.0};
}

void CompositeShape::move(double dx, double dy) {
    for (const auto &shape : vec_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double coefficient) {
    if (vec_.empty() || coefficient <= 0) return;

    Point commonCenter = getCenter();

    for (auto &shape : vec_) {
        Point oldShapeCenter = shape->getCenter();

        shape->scale(coefficient);

        double dx = (oldShapeCenter.x - commonCenter.x) * (coefficient - 1.0);
        double dy = (oldShapeCenter.y - commonCenter.y) * (coefficient - 1.0);
        shape->move(dx, dy);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

void CompositeShape::print() const {
    std::cout << "[" << getName() << ", (" << getCenter().x << ", " << getCenter().y
        << "), " << getArea() << ":" << std::endl;

    for (const auto &shape : vec_) {
        std::cout << "  ";
        shape->print();
    }
    std::cout << "]" << std::endl;
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (!shape) return;
    vec_.push_back(std::move(shape));
}

Point CompositeShape::getLeftLow() const {
    if (vec_.empty()) return {0.0, 0.0};

    double minX = vec_[0]->getLeftLow().x;
    double minY = vec_[0]->getLeftLow().y;

    for (const auto &shape : vec_) {
        auto ll = shape->getLeftLow();
        if (ll.x < minX) minX = ll.x;
        if (ll.y < minY) minY = ll.y;
    }
    return {minX, minY};
}

Point CompositeShape::getRightTop() const {
    if (vec_.empty()) return {0.0, 0.0};

    auto firstRT = vec_[0]->getRightTop();
    double maxX = firstRT.x;
    double maxY = firstRT.y;

    for (const auto &shape : vec_) {
        auto rt = shape->getRightTop();
        if (rt.x > maxX) maxX = rt.x;
        if (rt.y > maxY) maxY = rt.y;
    }
    return {maxX, maxY};
}
