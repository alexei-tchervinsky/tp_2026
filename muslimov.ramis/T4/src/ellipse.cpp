#include "../include/ellipse.hpp"
#include <stdexcept>

namespace{
    constexpr double EPS = 1e-12;
    constexpr double PI = 3.14159265358979323846;
}

Ellipse::Ellipse(const Point& center, double verticalRadius, double horizontalRadius)
    : center_(center), ry_(verticalRadius), rx_(horizontalRadius)
{
    validateRadius(ry_, rx_);
}

void Ellipse::validateRadius(double ry, double rx){
    if(!(ry > EPS) || !(rx > EPS)){
        throw std::invalid_argument("Ellipse::validateRadius: radii must be > EPS");
    }
}

double Ellipse::getArea() const{
    return PI * rx_ * ry_;
}

Point Ellipse::getCenter() const { return center_; }

void Ellipse::move(double dx, double dy){
    center_.x += dx; center_.y += dy;
}

double Ellipse::left() const { return center_.x - rx_; }
double Ellipse::right() const { return center_.x + rx_; }
double Ellipse::bottom() const { return center_.y - ry_; }
double Ellipse::top() const { return center_.y + ry_; }

std::string Ellipse::getName() const {
    return "ELLIPSE";
}

void Ellipse::getBoundingBox(double &left, double &bottom, double &right, double &top) const {
    left = center_.x - rx_;
    right = center_.x + rx_;
    bottom = center_.y - ry_;
    top = center_.y + ry_;
}

void Ellipse::scale(double factor) {
    if (!(factor > 0.0)) {
        throw std::invalid_argument("Ellipse::scale: factor must be > 0");
    }
    rx_ *= factor;
    ry_ *= factor;
    validateRadius(ry_, rx_);
}

