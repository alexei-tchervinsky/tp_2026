#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const Point & left_low, const Point & right_upper) :
    left_low_(left_low), right_upper_(right_upper){}
double Rectangle::getArea() const{
    return { (right_upper_.x - left_low_.x)*(right_upper_.y - left_low_.y)};
}
Point Rectangle::getCenter() const{
    return { {(right_upper_.x + left_low_.x)/2},  {(right_upper_.y + left_low_.y)/2} };
}
void Rectangle::move(double dx, double dy){
    right_upper_.x += dx;
    left_low_.x += dx;
    right_upper_.y += dy;
    left_low_.y += dy;
}

void Rectangle::scale(double coef){
    if (coef < 0.0){
        throw std::invalid_argument("Coef must pe positive");
    }
    double center_x = (right_upper_.x + left_low_.x)/2;
    double center_y = ((right_upper_.y + left_low_.y)/2);
    right_upper_.x = center_x + (right_upper_.x - center_x) * coef;
    left_low_.x = center_x + (left_low_.x - center_x) * coef;
    right_upper_.y = center_y + (right_upper_.y - center_y) * coef;
    left_low_.y = center_y + (left_low_.y - center_y) * coef;
}

std::string Rectangle::getName() const{
    return "RECTANGLE";
}
