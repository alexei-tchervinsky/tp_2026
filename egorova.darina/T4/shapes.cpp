#include "shapes.hpp"
#include <cmath>
#include <stdexcept>

// Реализация класса Point
Point::Point(double x_val, double y_val) : x(x_val), y(y_val) {}

// Реализация класса FrameRectangle
FrameRectangle::FrameRectangle(double w, double h, Point c)
    : width(w), height(h), center(c) {}

Point FrameRectangle::getBottomLeft() const {
    return Point(center.x - width / 2, center.y - height / 2);
}

Point FrameRectangle::getTopRight() const {
    return Point(center.x + width / 2, center.y + height / 2);
}

// Реализация класса Rectangle
Rectangle::Rectangle(const Point &c, double w, double h)
    : center(c), width(w), height(h) {
    if (w <= 0 || h <= 0)
        throw std::invalid_argument("Incorrect data for Rectangle");
}

double Rectangle::area() const { return width * height; }

FrameRectangle Rectangle::getFrame() const {
    return FrameRectangle(width, height, center);
}

void Rectangle::move(const Point &newPos) { center = newPos; }

void Rectangle::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Rectangle::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor is incorrect for Rectangle");
    width *= factor;
    height *= factor;
}

Shape *Rectangle::clone() const { return new Rectangle(*this); }

std::string Rectangle::getName() const { return "RECTANGLE"; }

// Реализация класса Ring
Ring::Ring(const Point &c, double inner_r, double outer_r)
    : center(c), innerRadius(inner_r), outerRadius(outer_r) {
    if (inner_r <= 0 || outer_r <= 0 || inner_r >= outer_r)
        throw std::invalid_argument("Incorrect data for Ring");
}

double Ring::area() const {
    return M_PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}

FrameRectangle Ring::getFrame() const {
    double diameter = 2 * outerRadius;
    return FrameRectangle(diameter, diameter, center);
}

void Ring::move(const Point &newPos) { center = newPos; }

void Ring::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Ring::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor is incorrect for Ring");
    innerRadius *= factor;
    outerRadius *= factor;
}

Shape *Ring::clone() const { return new Ring(*this); }

std::string Ring::getName() const { return "RING"; }

// Реализация класса Square
Square::Square(const Point &c, double side_length)
    : center(c), side(side_length) {
    if (side_length <= 0)
        throw std::invalid_argument("Incorrect data for Square");
}

double Square::area() const { return side * side; }

FrameRectangle Square::getFrame() const {
    return FrameRectangle(side, side, center);
}

void Square::move(const Point &newPos) { center = newPos; }

void Square::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Square::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor is incorrect for Square");
    side *= factor;
}

Shape *Square::clone() const { return new Square(*this); }

std::string Square::getName() const { return "SQUARE"; }

// Реализация класса Circle
Circle::Circle(const Point &c, double r)
    : center(c), radius(r) {
    if (r <= 0)
        throw std::invalid_argument("Incorrect data for Circle");
}

double Circle::area() const { return M_PI * radius * radius; }

FrameRectangle Circle::getFrame() const {
    double diameter = 2 * radius;
    return FrameRectangle(diameter, diameter, center);
}

void Circle::move(const Point &newPos) { center = newPos; }

void Circle::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Circle::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor is incorrect for Circle");
    radius *= factor;
}

Shape *Circle::clone() const { return new Circle(*this); }

std::string Circle::getName() const { return "CIRCLE"; }

// Реализация класса CompositeShape
CompositeShape::CompositeShape(size_t max_s)
    : shapes(new Shape*[max_s]), count(0), maxShapes(max_s), center(0.0, 0.0) {}

CompositeShape::~CompositeShape() {
    for (size_t i = 0; i < count; ++i)
        delete shapes[i];
    delete[] shapes;
}

void CompositeShape::addShape(Shape *shape) {
    if (count >= maxShapes)
        throw std::overflow_error("Maximum number of shapes reached in CompositeShape");
    shapes[count++] = shape;
    updateCenter();
}

void CompositeShape::updateCenter() {
    if (count == 0) {
        center = Point(0.0, 0.0);
        return;
    }
    double minX = shapes[0]->getFrame().getBottomLeft().x;
    double minY = shapes[0]->getFrame().getBottomLeft().y;
    double maxX = shapes[0]->getFrame().getTopRight().x;
    double maxY = shapes[0]->getFrame().getTopRight().y;
    for (size_t i = 1; i < count; ++i) {
        FrameRectangle f = shapes[i]->getFrame();
        Point bl = f.getBottomLeft();
        Point tr = f.getTopRight();
        if (bl.x < minX)
            minX = bl.x;
        if (bl.y < minY)
            minY = bl.y;
        if (tr.x > maxX)
            maxX = tr.x;
        if (tr.y > maxY)
            maxY = tr.y;
    }
    center = Point((minX + maxX) / 2, (minY + maxY) / 2);
}

double CompositeShape::area() const {
    double totalArea = 0.0;
    for (size_t i = 0; i < count; ++i)
        totalArea += shapes[i]->area();
    return totalArea;
}

FrameRectangle CompositeShape::getFrame() const {
    if (count == 0)
        return FrameRectangle();
    double minX = shapes[0]->getFrame().getBottomLeft().x;
    double minY = shapes[0]->getFrame().getBottomLeft().y;
    double maxX = shapes[0]->getFrame().getTopRight().x;
    double maxY = shapes[0]->getFrame().getTopRight().y;
    for (size_t i = 1; i < count; ++i) {
        FrameRectangle f = shapes[i]->getFrame();
        Point bl = f.getBottomLeft();
        Point tr = f.getTopRight();
        if (bl.x < minX)
            minX = bl.x;
        if (bl.y < minY)
            minY = bl.y;
        if (tr.x > maxX)
            maxX = tr.x;
        if (tr.y > maxY)
            maxY = tr.y;
    }
    double w = maxX - minX;
    double h = maxY - minY;
    Point c((minX + maxX) / 2, (minY + maxY) / 2);
    return FrameRectangle(w, h, c);
}

void CompositeShape::move(const Point &newPos) {
    FrameRectangle oldFrame = getFrame();
    double dx = newPos.x - oldFrame.center.x;
    double dy = newPos.y - oldFrame.center.y;
    move(dx, dy);
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < count; ++i)
        shapes[i]->move(dx, dy);
    center.x += dx;
    center.y += dy;
}

void CompositeShape::scale(double factor) {
    if (factor <= 0)
        throw std::invalid_argument("Scale factor is incorrect for CompositeShape");
    FrameRectangle frame = getFrame();
    Point c = frame.center;
    for (size_t i = 0; i < count; ++i) {
        FrameRectangle f = shapes[i]->getFrame();
        double offsetX = f.center.x - c.x;
        double offsetY = f.center.y - c.y;
        double newX = c.x + offsetX * factor;
        double newY = c.y + offsetY * factor;
        shapes[i]->move(newX, newY);
        shapes[i]->scale(factor);
    }
    updateCenter();
}

Shape *CompositeShape::clone() const {
    CompositeShape *newC = new CompositeShape(maxShapes);
    for (size_t i = 0; i < count; ++i)
        newC->addShape(shapes[i]->clone());
    return newC;
}

std::string CompositeShape::getName() const { return "COMPOSITE_SHAPE"; }
