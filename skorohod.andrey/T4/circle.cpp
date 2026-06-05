#include "circle.hpp"

double PI = 3.141592;

Circle::Circle(Point center, double radius):
center_(center),
radius_(radius)
{}

double Circle::getArea() const
{
    return (PI * radius_ * radius_);
}

Point Circle::getCenter() const
{
    return center_;
}

void Circle::move(double dx, double dy)
{
    center_.x += dx;
    center_.y += dy;
}

void Circle::scale(double k)
{
    radius_ *= k;
}

std::string Circle::getName() const
{
    return "CIRCLE";
}

Point Circle::getLeftLower() const
{
    return {(center_.x - radius_), (center_.y - radius_)};
}
Point Circle::getRightUpper() const
{
    return {(center_.x + radius_), (center_.y + radius_)};
}
