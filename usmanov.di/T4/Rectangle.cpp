#include "Rectangle.hpp"

Rectangle::Rectangle() {}

Rectangle::Rectangle(const Point& leftBottom, const Point& rightTop)
    : leftBottom_(leftBottom), rightTop_(rightTop) {
    if (leftBottom.x_ >= rightTop.x_ || leftBottom.y_ >= rightTop.y_) {
        throw std::invalid_argument("leftBottom must be less than rightTop in both x and y coordinates");
    }
}

float Rectangle::getArea() const {
    FrameRectangle frame = getFrameRectangle();
    return frame.getWidth() * frame.getHeight();
}

FrameRectangle Rectangle::getFrameRectangle() const {
    float width = rightTop_.x_ - leftBottom_.x_;
    float height = rightTop_.y_ - leftBottom_.y_;
    Point center;
    center.x_ = (leftBottom_.x_ + rightTop_.x_) / 2;
    center.y_ = (leftBottom_.y_ + rightTop_.y_) / 2;
    return FrameRectangle(width, height, center);
}

void Rectangle::move(const Point& pos) {
    Point center = getFrameRectangle().getPosition();
    float dx = pos.x_ - center.x_;
    float dy = pos.y_ - center.y_;
    move(dx, dy);
}

void Rectangle::move(float dx, float dy) {
    leftBottom_.x_ += dx;
    leftBottom_.y_ += dy;
    rightTop_.x_ += dx;
    rightTop_.y_ += dy;
}

void Rectangle::scale(float k) {
    if (k <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    float width = (rightTop_.x_ - leftBottom_.x_) * k;
    float height = (rightTop_.y_ - leftBottom_.y_) * k;
    Point center;
    center.x_ = (leftBottom_.x_ + rightTop_.x_) / 2;
    center.y_ = (leftBottom_.y_ + rightTop_.y_) / 2;
    leftBottom_.x_ = center.x_ - width / 2;
    leftBottom_.y_ = center.y_ - height / 2;
    rightTop_.x_ = center.x_ + width / 2;
    rightTop_.y_ = center.y_ + height / 2;
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(leftBottom_, rightTop_);
}

const char* Rectangle::getName() const {
    return "RECTANGLE";
}

