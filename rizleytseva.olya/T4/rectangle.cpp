#include "rectangle.h"
#include <algorithm>
#include <utility>

Rectangle::Rectangle(const Point& leftBottom, const Point& rightTop)
    : leftBottom(leftBottom), rightTop(rightTop) {}

Rectangle::Rectangle(const Rectangle& other)
    : leftBottom(other.leftBottom), rightTop(other.rightTop) {}

Rectangle::Rectangle(Rectangle&& other) noexcept
    : leftBottom(std::move(other.leftBottom)), rightTop(std::move(other.rightTop)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        Rectangle temp(other);
        swap(temp);
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

void Rectangle::swap(Rectangle& other) noexcept {
    using std::swap;
    swap(leftBottom, other.leftBottom);
    swap(rightTop, other.rightTop);
}

double Rectangle::getArea() const {
    double width = rightTop.x - leftBottom.x;
    double height = rightTop.y - leftBottom.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    return Point((leftBottom.x + rightTop.x) / 2.0,
                 (leftBottom.y + rightTop.y) / 2.0);
}

void Rectangle::move(double dx, double dy) {
    leftBottom.x += dx;
    leftBottom.y += dy;
    rightTop.x += dx;
    rightTop.y += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    leftBottom.x = center.x + (leftBottom.x - center.x) * factor;
    leftBottom.y = center.y + (leftBottom.y - center.y) * factor;
    rightTop.x = center.x + (rightTop.x - center.x) * factor;
    rightTop.y = center.y + (rightTop.y - center.y) * factor;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

std::unique_ptr<Shape> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}
