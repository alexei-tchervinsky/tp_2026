#include "circle.hpp"
#include <stdexcept>

Circle::Circle(const Point& center, double radius) : center_(center), radius_(radius) {}

double Circle::getArea() const{
    return 3.14*radius_*radius_;
}
Point Circle::getCenter() const{
    return center_;
}
void Circle::move(double dx, double dy){
    center_.x += dx;
    center_.y += dy;
}
void Circle::scale(double coef){
    if (coef < 0.0){
        throw std::invalid_argument("Coef must pe positive");
    }
    radius_ *= coef;
}
std::string Circle::getName() const{
    return "CIRCLE";
}
