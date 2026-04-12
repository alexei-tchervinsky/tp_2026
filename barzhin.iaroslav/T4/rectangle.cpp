//
// Created by xmdnusr on 07.03.2026.
//

#include "rectangle.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

Rectangle::Rectangle(const Point &left_low, const Point &right_top):
    left_low_(left_low), right_top_(right_top)
{
    const double min_x = std::min(left_low.x, right_top.x);
    const double max_x = std::max(left_low.x, right_top.x);
    const double min_y = std::min(left_low.y, right_top.y);
    const double max_y = std::max(left_low.y, right_top.y);
    left_low_ = {min_x, min_y};
    right_top_ = {max_x, max_y};
}

double Rectangle::getArea() const {
    const double w = right_top_.x - left_low_.x;
    const double h = right_top_.y - left_low_.y;
    return w * h;
}

Point Rectangle::getCenter() const {
    return {
        (left_low_.x + right_top_.x) / 2,
        (left_low_.y + right_top_.y) / 2};
}

void Rectangle::move(const double dx, const double dy) {
    left_low_ = {left_low_.x + dx, left_low_.y + dy};
    right_top_ = {right_top_.x + dx, right_top_.y + dy};
}

void Rectangle::scale(const double coefficient) {
    if (coefficient <= 0) return;
    Point c = getCenter();

    const double new_width = (right_top_.x - left_low_.x) * coefficient;
    const double new_height = (right_top_.y - left_low_.y) * coefficient;

    left_low_ = {
        c.x - (new_width / 2),
        c.y - (new_height / 2)
    };

    right_top_ = {
        c.x + (new_width / 2),
        c.y + (new_height / 2)
    };
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}

void Rectangle::print() const {
    std::ios_base::fmtflags f(std::cout.flags());

    auto center = getCenter();
    auto area = getArea();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "["
        << getName()
        << ", ("
        << center.x
        << ", "
        << center.y
        << "), "
        << area
        << "]"
        << std::endl;

    std::cout.flags(f);
}

Point Rectangle::getLeftLow() const {
    return left_low_;
}

Point Rectangle::getRightTop() const {
    return right_top_;
}
