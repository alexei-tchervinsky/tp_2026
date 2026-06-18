#include "rectangle.hpp"

double Rectangle::getArea() const {
    return (right_top_.x_ - left_bottom_.x_) * (right_top_.y_ - left_bottom_.y_);
}
Point Rectangle::getCenter() const {
    return Point { (right_top_.x_ + left_bottom_.x_)/2, (right_top_.y_ + left_bottom_.y_)/2 };
}
void Rectangle::move(double dx, double dy){
    right_top_.x_+=dx;
    left_bottom_.x_+=dx;
    right_top_.y_+=dy;
    left_bottom_.y_+=dy;
}
void Rectangle::scale(double factor) {
    if(factor<=0.0)return;
    Point center = getCenter();
    double halfWidth = (right_top_.x_ - left_bottom_.x_) / 2.0;
    double halfHeight = (right_top_.y_ - left_bottom_.y_) / 2.0;
    right_top_.x_ = center.x_ + halfWidth * factor;
    right_top_.y_ = center.y_ + halfHeight * factor;
    left_bottom_.x_ = center.x_ - halfWidth * factor;
    left_bottom_.y_ = center.y_ - halfHeight * factor;
}
std::string Rectangle::getName()const{ return "RECTANGLE"; }
FrameRect Rectangle::getFrameRect() const {
    double width = right_top_.x_ - left_bottom_.x_;
    double height = right_top_.y_ - left_bottom_.y_;
    return { getCenter(), width, height };
}
