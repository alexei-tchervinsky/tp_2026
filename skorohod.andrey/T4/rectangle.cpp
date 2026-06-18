#include "rectangle.hpp"

Rectangle::Rectangle(Point a, Point b):
vertex1_(a),
vertex2_(b),
center_({((vertex2_.x + vertex1_.x) / 2.0), ((vertex2_.y + vertex1_.y) / 2.0)})
{}

double Rectangle::getArea() const
{
    return (vertex2_.x - vertex1_.x) * (vertex2_.y - vertex1_.y);
}

Point Rectangle::getCenter() const
{
    return center_;
}

void Rectangle::move(double dx, double dy)
{
    vertex1_.x += dx;
    vertex2_.x += dx;
    vertex1_.y += dy;
    vertex2_.y += dy;
    center_.x += dx;
    center_.y += dy;
}

void Rectangle::scale(double k)
{
    double dx = center_.x - vertex1_.x;
    double dy = center_.y - vertex1_.y;

    vertex1_.x -= dx * k / 2;
    vertex2_.x += dx * k / 2;
    vertex1_.y -= dy * k / 2;
    vertex2_.y += dy * k / 2;
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}

Point Rectangle::getLeftLower() const
{
    return vertex1_;
}
Point Rectangle::getRightUpper() const
{
    return vertex2_;
}
