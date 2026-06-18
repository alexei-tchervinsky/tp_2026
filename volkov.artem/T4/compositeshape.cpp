#include "compositeshape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include <cmath>

const double PI = 3.14159265358979323846;

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape) {
    shapes.push_back(shape);
}

double CompositeShape::getArea() const {
    double sum = 0.0;
    for (const auto &shape: shapes) {
        sum += shape->getArea();
    }
    return sum;
}

Point CompositeShape::getCenter() const {
    double left = 0.0;
    double right = 0.0;
    double bottom = 0.0;
    double top = 0.0;
    bool first = true;

    for (const auto &shape: shapes) {
        if (shape->getName() == "RECTANGLE") {
            const Rectangle *r = dynamic_cast<const Rectangle *>(shape.get());
            Point c = r->getCenter();
            double s = r->getArea();
            double width = 1.0;
            double height = s;

            if (first) {
                left = c.x - width / 2.0;
                right = c.x + width / 2.0;
                bottom = c.y - height / 2.0;
                top = c.y + height / 2.0;
                first = false;
            } else {
                if (c.x - width / 2.0 < left) left = c.x - width / 2.0;
                if (c.x + width / 2.0 > right) right = c.x + width / 2.0;
                if (c.y - height / 2.0 < bottom) bottom = c.y - height / 2.0;
                if (c.y + height / 2.0 > top) top = c.y + height / 2.0;
            }
        } else if (shape->getName() == "CIRCLE") {
            const Circle *c = dynamic_cast<const Circle *>(shape.get());
            Point center = c->getCenter();
            double area = c->getArea();
            double radius = std::sqrt(area / PI);

            if (first) {
                left = center.x - radius;
                right = center.x + radius;
                bottom = center.y - radius;
                top = center.y + radius;
                first = false;
            } else {
                if (center.x - radius < left) left = center.x - radius;
                if (center.x + radius > right) right = center.x + radius;
                if (center.y - radius < bottom) bottom = center.y - radius;
                if (center.y + radius > top) top = center.y + radius;
            }
        }
    }

    return {(left + right) / 2.0, (bottom + top) / 2.0};
}

void CompositeShape::move(double dx, double dy) {
    for (auto &shape: shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point center = getCenter();

    for (auto &shape: shapes) {
        Point oldCenter = shape->getCenter();
        double newX = center.x + (oldCenter.x - center.x) * factor;
        double newY = center.y + (oldCenter.y - center.y) * factor;
        shape->move(newX - oldCenter.x, newY - oldCenter.y);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::shared_ptr<Shape> > &CompositeShape::getShapes() const {
    return shapes;
}
