#include "../include/shapeContainer.hpp"
#include <utility>
#include <stdexcept>

void ShapesContainer::add(std::unique_ptr<Shape> shape) {
    if (!shape) return;
    shapes_.push_back(std::move(shape));
}

std::size_t ShapesContainer::size() const noexcept {
    return shapes_.size();
}

void ShapesContainer::scaleAll(double factor) {
    if (!(factor > 0.0)) {
        throw std::invalid_argument("ShapesContainer::scaleAll: factor must be > 0");
    }
    for (auto &s : shapes_) {
        s->scale(factor);
    }
}

void ShapesContainer::moveAll(double dx, double dy) {
    for (auto &s : shapes_) {
        s->move(dx, dy);
    }
}
