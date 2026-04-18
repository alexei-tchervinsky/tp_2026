#include "composite_shape.hpp"

double CompositeShape::getArea() const {
    double area = 0;
    for (std::size_t i = 0; i<shapes_.size();++i){
        area += (*shapes_[i]).getArea();
    }
    return area;
}
Point CompositeShape::getCenter() const {
    return getFrameRect().pos_;
}
void CompositeShape::move(double dx, double dy){
    for (std::size_t i = 0; i < shapes_.size(); ++i){
        (*shapes_[i]).move(dx, dy);
    }
}
void CompositeShape::scale(double factor){
    if(factor<=0.0)return;
    if (shapes_.empty()) return;
    Point center = getCenter();
    for(std::size_t i = 0; i<shapes_.size(); ++i){
        Point shapeCenter = shapes_[i]->getCenter();
        double dx = (shapeCenter.x_ - center.x_) * (factor - 1.0);
        double dy = (shapeCenter.y_ - center.y_) * (factor - 1.0);
        shapes_[i]->move(dx, dy);
        shapes_[i]->scale(factor);
    }
}
std::string CompositeShape::getName() const{ return "COMPOSITE"; }

void CompositeShape::add(const std::shared_ptr<Shape>& shape){
    shapes_.push_back(shape);
}
FrameRect CompositeShape::getFrameRect() const {
    if (shapes_.empty()) {
        return {{0.0, 0.0}, 0.0, 0.0};
    }
    FrameRect firstRect = shapes_[0]->getFrameRect();
    double minX = firstRect.pos_.x_ - firstRect.width_ / 2.0;
    double maxX = firstRect.pos_.x_ + firstRect.width_ / 2.0;
    double minY = firstRect.pos_.y_ - firstRect.height_ / 2.0;
    double maxY = firstRect.pos_.y_ + firstRect.height_ / 2.0;

    for (std::size_t i = 1; i < shapes_.size(); ++i) {
        FrameRect rect = shapes_[i]->getFrameRect();

        double left = rect.pos_.x_ - rect.width_ / 2.0;
        double right = rect.pos_.x_ + rect.width_ / 2.0;
        double bottom = rect.pos_.y_ - rect.height_ / 2.0;
        double top = rect.pos_.y_ + rect.height_ / 2.0;

        if (left < minX) minX = left;
        if (right > maxX) maxX = right;
        if (bottom < minY) minY = bottom;
        if (top > maxY) maxY = top;
    }
    double width = maxX - minX;
    double height = maxY - minY;
    Point center = { minX + width / 2.0, minY + height / 2.0 };

    return { center, width, height };
}
