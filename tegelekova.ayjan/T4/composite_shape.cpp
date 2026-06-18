#include "composite_shape.h"
#include "rectangle.h"
#include <limits>
#include <cmath>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0;
    for (const auto& shape : shapes) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) return Point(0, 0);

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes) {
        Point center = shape->getCenter();
        minX = std::min(minX, center.x);
        minY = std::min(minY, center.y);
        maxX = std::max(maxX, center.x);
        maxY = std::max(maxY, center.y);
    }

    return Point((minX + maxX) / 2, (minY + maxY) / 2);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point center = getCenter();

    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();

        // Смещаем фигуру относительно центра
        double dx = (shapeCenter.x - center.x) * (factor - 1);
        double dy = (shapeCenter.y - center.y) * (factor - 1);
        shape->move(dx, dy);

        // Масштабируем саму фигуру
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
