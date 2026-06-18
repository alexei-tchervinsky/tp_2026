#include "composite-shape.hpp"
#include <stdexcept>
#include <algorithm>

CompositeShape::CompositeShape(std::size_t capacity) :
    shapes_(new Shape* [capacity]), size_(0), capacity_(capacity) {
}

CompositeShape::~CompositeShape() {
    for (std::size_t i = 0; i < size_; ++i) {
        delete shapes_[i];
    }
    delete[] shapes_;
}

void CompositeShape::addShape(Shape* shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Shape cannot be null");
    }
    if (size_ >= capacity_) {
        throw std::overflow_error("CompositeShape is full");
    }
    shapes_[size_++] = shape;
}

double CompositeShape::getArea() const {
    double area = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        area += shapes_[i]->getArea();
    }
    return area;
}

FrameRectangle CompositeShape::getFrameRectangle() const {
    if (size_ == 0) {
        throw std::runtime_error("CompositeShape is empty");
    }

    FrameRectangle fr = shapes_[0]->getFrameRectangle();
    double minX = fr.pos_.x_ - fr.width_ / 2;
    double maxX = fr.pos_.x_ + fr.width_ / 2;
    double minY = fr.pos_.y_ - fr.height_ / 2;
    double maxY = fr.pos_.y_ + fr.height_ / 2;

    for (std::size_t i = 1; i < size_; ++i) {
        fr = shapes_[i]->getFrameRectangle();
        minX = std::min(minX, fr.pos_.x_ - fr.width_ / 2);
        maxX = std::max(maxX, fr.pos_.x_ + fr.width_ / 2);
        minY = std::min(minY, fr.pos_.y_ - fr.height_ / 2);
        maxY = std::max(maxY, fr.pos_.y_ + fr.height_ / 2);
    }
    return { maxX - minX, maxY - minY, { (minX + maxX) / 2, (minY + maxY) / 2 } };
}

Point CompositeShape::getCenter() const {
    return getFrameRectangle().pos_;
}

void CompositeShape::move(const Point& newPos) {
    Point current = getCenter();
    move(newPos.x_ - current.x_, newPos.y_ - current.y_);
}

void CompositeShape::move(double dx, double dy) {
    for (std::size_t i = 0; i < size_; ++i) {
        shapes_[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double coeff) {
    if (coeff <= 0.0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }
    Point center = getCenter();
    for (std::size_t i = 0; i < size_; ++i) {
        Point shapeCenter = shapes_[i]->getCenter();
        double dx = (shapeCenter.x_ - center.x_) * coeff;
        double dy = (shapeCenter.y_ - center.y_) * coeff;
        shapes_[i]->move({ center.x_ + dx, center.y_ + dy });
        shapes_[i]->scale(coeff);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
