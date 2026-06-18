#include "composite_shape.hpp"
#include <stdexcept> // для исключения, если нужно

namespace golovach {

    void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }

    double CompositeShape::getArea() const {
        double total = 0.0;
        for (const auto& shape : shapes_) {
            total += shape->getArea();
        }
        return total;
    }

    Point CompositeShape::getCenter() const {
        // Защита от пустой составной фигуры
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
        Point center = getCenter();
        for (auto& shape : shapes_) {
            Point c = shape->getCenter();
            shape->move((c.x - center.x) * (factor - 1.0),
                        (c.y - center.y) * (factor - 1.0));
            shape->scale(factor);
        }
    }

    const char* CompositeShape::getName() const {
        return "COMPOSITE";
    }

    const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
        return shapes_;
    }
}
