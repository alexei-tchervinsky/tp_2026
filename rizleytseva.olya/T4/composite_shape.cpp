#include "composite_shape.h"
#include <algorithm>
#include <limits>
#include <utility>

CompositeShape::CompositeShape(const CompositeShape& other) {
    for (const auto& shape : other.shapes) {
        shapes.push_back(shape->clone());
    }
}

CompositeShape::CompositeShape(CompositeShape&& other) noexcept
    : shapes(std::move(other.shapes)) {}

CompositeShape& CompositeShape::operator=(const CompositeShape& other) {
    if (this != &other) {
        CompositeShape temp(other);
        swap(temp);
    }
    return *this;
}

CompositeShape& CompositeShape::operator=(CompositeShape&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

void CompositeShape::swap(CompositeShape& other) noexcept {
    using std::swap;
    swap(shapes, other.shapes);
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& shape : shapes) {
        total += shape->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }

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

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point commonCenter = getCenter();

    for (auto& shape : shapes) {
        Point shapeCenter = shape->getCenter();

        double dx = (shapeCenter.x - commonCenter.x) * factor;
        double dy = (shapeCenter.y - commonCenter.y) * factor;

        shape->move(dx - (shapeCenter.x - commonCenter.x),
                    dy - (shapeCenter.y - commonCenter.y));

        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

std::unique_ptr<Shape> CompositeShape::clone() const {
    auto cloned = std::make_unique<CompositeShape>();
    for (const auto& shape : shapes) {
        cloned->addShape(shape->clone());
    }
    return cloned;
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes;
}
