#include "composite_shape.h"
#include <stdexcept>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (!shape) {
        throw std::invalid_argument("Shape pointer cannot be null");
    }
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0.0;
    for (const auto& shape : shapes_) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes_.empty()) {
        return {0.0, 0.0};
    }

    double minX = shapes_[0]->getCenter().x;
    double maxX = minX;
    double minY = shapes_[0]->getCenter().y;
    double maxY = minY;

    for (const auto& shape : shapes_) {
        Point c = shape->getCenter();
        if (c.x < minX) minX = c.x;
        if (c.x > maxX) maxX = c.x;
        if (c.y < minY) minY = c.y;
        if (c.y > maxY) maxY = c.y;
    }

    return { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point baseCenter = getCenter();

    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getCenter();

        double dx = (shapeCenter.x - baseCenter.x) * (factor - 1.0);
        double dy = (shapeCenter.y - baseCenter.y) * (factor - 1.0);

        shape->move(dx, dy);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes_;
}
