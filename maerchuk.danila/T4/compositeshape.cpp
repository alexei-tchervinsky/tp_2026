#include "compositeshape.hpp"
#include <stdexcept>
#include <algorithm>

void CompositeShape::add(Shape* shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("Shape pointer cannot be null");
    }
    shapes_.push_back(shape);
}

void CompositeShape::remove(size_t index) {
    if (index >= shapes_.size()) {
        throw std::out_of_range("Index is out of range");
    }
    delete shapes_[index];
    shapes_.erase(shapes_.begin() + index);
}

float CompositeShape::getArea() const {
    float totalArea = 0.0f;
    for (const auto& shape : shapes_) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

FrameRectangle CompositeShape::getFrameRectangle() const {
    if (shapes_.empty()) {
        throw std::logic_error("CompositeShape is empty");
    }

    FrameRectangle firstFrame = shapes_[0]->getFrameRectangle();
    float minX = firstFrame.getPos().getX() - firstFrame.getWidth() / 2.0f;
    float maxX = firstFrame.getPos().getX() + firstFrame.getWidth() / 2.0f;
    float minY = firstFrame.getPos().getY() - firstFrame.getHeight() / 2.0f;
    float maxY = firstFrame.getPos().getY() + firstFrame.getHeight() / 2.0f;

    for (size_t i = 1; i < shapes_.size(); ++i) {
        FrameRectangle frame = shapes_[i]->getFrameRectangle();
        minX = std::min(minX, frame.getPos().getX() - frame.getWidth() / 2.0f);
        maxX = std::max(maxX, frame.getPos().getX() + frame.getWidth() / 2.0f);
        minY = std::min(minY, frame.getPos().getY() - frame.getHeight() / 2.0f);
        maxY = std::max(maxY, frame.getPos().getY() + frame.getHeight() / 2.0f);
    }

    float width = maxX - minX;
    float height = maxY - minY;
    Point center(minX + width / 2.0f, minY + height / 2.0f);

    return FrameRectangle(width, height, center);
}

void CompositeShape::move(const Point& newPos) {
    Point currentCenter = getFrameRectangle().getPos();
    move(newPos.getX() - currentCenter.getX(), newPos.getY() - currentCenter.getY());
}

void CompositeShape::move(float dx, float dy) {
    for (auto& shape : shapes_) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(float factor) {
    if (factor <= 0.0f) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point commonCenter = getFrameRectangle().getPos();

    for (auto& shape : shapes_) {
        Point shapeCenter = shape->getFrameRectangle().getPos();
        float dx = (shapeCenter.getX() - commonCenter.getX()) * (factor - 1.0f);
        float dy = (shapeCenter.getY() - commonCenter.getY()) * (factor - 1.0f);
        shape->move(dx, dy);
    }
}

CompositeShape* CompositeShape::clone() const {
    CompositeShape* newComposite = new CompositeShape();
    for (const auto& shape : shapes_) {
        newComposite->add(shape->clone());
    }
    return newComposite;
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
